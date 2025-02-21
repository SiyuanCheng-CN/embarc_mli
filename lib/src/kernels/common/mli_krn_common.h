/*
* Copyright 2019-2021, Synopsys, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-3-Clause license found in
* the LICENSE file in the root directory of this source tree.
*
*/

#ifndef _MLI_KRN_COMMON_H_
#define _MLI_KRN_COMMON_H_

#include "mli_api.h"
#include "mli_check.h"
#include "mli_helpers_api.h"
#include "mli_krn_eltwise.h"
#include "mli_prv_dsp.h"
#include "mli_math.h"
#include "mli_types.h"
#include "mli_prv_activation_lut.h"

static MLI_FORCE_INLINE accum40_t mli_prv_ashift_accu(accum40_t accu, const int shift_right)
{
    return fx_asr_a40(accu, shift_right);
}

static MLI_FORCE_INLINE int32_t mli_prv_ashift_accu(int32_t accu, const int shift_right)
{
    accu = fx_asr_rnd_q31(accu, shift_right);
    _setacc(accu,1);
    return accu; 
}

namespace mli {

template <typename io_T, typename w_T>
static MLI_FORCE_INLINE void rnn_dense_op_fx(
        const MLI_PTR (io_T) __restrict in,
        const MLI_PTR (io_T) __restrict state,
        const MLI_PTR (w_T) __restrict weights,
        const MLI_PTR (w_T) __restrict biases,
        MLI_CONV_OUT_PTR (io_T) __restrict out,
        const int inp_size,
        const int s_size,
        const int ch_out,
        const int bias_shift,
        const int in_to_state_fraq_dif,
        const int out_shift)
{

    if (_Rarely (inp_size < 8 && s_size < 8)) {
        for (int i = 0; i < ch_out; i++) {
            const MLI_PTR (io_T) __restrict in_ptr = in;
            const MLI_PTR (io_T) __restrict s_ptr = state;

            auto ip_out = mli_prv_init_accu_with_bias(in_ptr, *biases++, bias_shift);

            for (int j = 0; j < inp_size; j++) {
                mli_prv_load_mac(&ip_out, in_ptr++, weights++);
            }

            ip_out = mli_prv_ashift_accu(ip_out, in_to_state_fraq_dif);
        
            for (int k = 0; k < s_size; k++) {
                mli_prv_load_mac(&ip_out, s_ptr++, weights++);
            }
        
            mli_prv_clip_and_store_output(out++, &ip_out, out_shift);
        }
    } else if ((inp_size%4 == 0) && (s_size%4 == 0)) {
        for (int i = 0; i < ch_out; i++) {
            const MLI_PTR (io_T) __restrict in_ptr = in;
            const MLI_PTR (io_T) __restrict s_ptr = state;

            auto ip_out = mli_prv_init_accu_with_bias(in_ptr, *biases++, bias_shift);

LOOP_PIPELINE_ENABLE
LOOP_PIPELINE_ENABLE_BACKTRACKING
            for (int jj = 0; jj < (inp_size/4); jj++) {
                mli_prv_load_mac_vec4(&ip_out, in_ptr, weights);
                in_ptr += 4;
                weights += 4;
            }

            ip_out = mli_prv_ashift_accu(ip_out, in_to_state_fraq_dif);

LOOP_PIPELINE_ENABLE
LOOP_PIPELINE_ENABLE_BACKTRACKING
            for (int kk = 0; kk < (s_size/4); kk++) {
                mli_prv_load_mac_vec4(&ip_out, s_ptr, weights);
                s_ptr += 4;
                weights += 4;
            }
            s_ptr -= s_size;

            mli_prv_clip_and_store_output(out++, &ip_out, out_shift);
        }
    } else {
        for (int i = 0; i < ch_out; i++) {
            const MLI_PTR (io_T) __restrict in_ptr = in;
            const MLI_PTR (io_T) __restrict s_ptr = state;

            auto ip_out = mli_prv_init_accu_with_bias(in_ptr, *biases++, bias_shift);

            for (int j = 0; j < (inp_size&3); j++) {
                mli_prv_load_mac(&ip_out, in_ptr++, weights++);
            }

LOOP_PIPELINE_ENABLE
LOOP_PIPELINE_ENABLE_BACKTRACKING
            for (int jj = 0; jj < (inp_size/4); jj++) {
                mli_prv_load_mac_vec4(&ip_out, in_ptr, weights);
                in_ptr += 4;
                weights += 4;
            }

            ip_out = mli_prv_ashift_accu(ip_out, in_to_state_fraq_dif);

            for (int k = 0; k < (s_size&3); k++) {
                mli_prv_load_mac(&ip_out, s_ptr++, weights++);
            }

LOOP_PIPELINE_ENABLE
LOOP_PIPELINE_ENABLE_BACKTRACKING
            for (int kk = 0; kk < (s_size/4); kk++) {
                mli_prv_load_mac_vec4(&ip_out, s_ptr, weights);
                s_ptr += 4;
                weights += 4;
            }

            mli_prv_clip_and_store_output(out++, &ip_out, out_shift);
        }
    }
}
//==================================================================////==================================================================
//==================================================================
//
//==================================================================
template <typename io_T, typename w_T>
static MLI_FORCE_INLINE void lstm_cell_prepare_and_run_fx(
        const mli_tensor *in,
        const mli_tensor *prev_out,
        const mli_tensor *weights,
        const mli_tensor *bias,
        const mli_lut *tanh_lut,
        const mli_lut *sigm_lut,
        const mli_rnn_cell_cfg_depr *cfg,
        mli_tensor *cell,
        mli_tensor *out) {
    const int lstm_out_elements = static_cast<int>(mli_prv_count_elem_num(prev_out));
    const int dense_out_elements = static_cast<int>(mli_prv_count_elem_num(bias));
    const int batch_sz = static_cast<int>((cfg->mode == RNN_ONE_TO_ONE) ? 1 : in->shape[0]);
    const int in_elements = static_cast<int>((cfg->mode == RNN_ONE_TO_ONE) ? mli_prv_count_elem_num (in) : mli_prv_count_elem_num_part(in, 1));

    const MLI_PTR (w_T) w_ptr = mli_prv_tensor_data_ptr<MLI_PTR (w_T)>(weights);
    const MLI_PTR (w_T) b_ptr = mli_prv_tensor_data_ptr<MLI_PTR (w_T)>(bias);
    const MLI_PTR (io_T) in_ptr = mli_prv_tensor_data_ptr<MLI_PTR (io_T)>(in);
    const MLI_PTR (io_T) prev_ptr = mli_prv_tensor_data_ptr<MLI_PTR (io_T)>(prev_out);
    MLI_CONV_OUT_PTR (io_T) dense_out_ptr = mli_prv_tensor_data_ptr<MLI_CONV_OUT_PTR (io_T)>(cfg->ir_tsr);

    // Fill intermediate tensor of dense output
    mli_tensor *ir_tensor = cfg->ir_tsr;
    ir_tensor->rank = bias->rank;
    ir_tensor->shape[0] = bias->shape[0];
    ir_tensor->shape[1] = bias->shape[1];
    ir_tensor->mem_stride[0] = 0;
    ir_tensor->mem_stride[1] = 0;
    ir_tensor->el_type = in->el_type;
    // 1sign and 3 integer bits for TANH/SIGM input is enough
    ir_tensor->el_params.fx.frac_bits = (sizeof(io_T) * 8) - 1 - 3;

    // Define shift values
    const int dense_bias_shift = mli_prv_calc_shift(in, weights, bias);
    const int in_to_state_dif = in->el_params.fx.frac_bits - prev_out->el_params.fx.frac_bits;
    const int dense_out_shift = mli_prv_calc_shift(prev_out, weights, ir_tensor);

    // Paricular subtensors of intermediate tensor (mli_tensor.mem_stride[] should be zero and cannot be left uninitialized)
    mli_tensor in_gate = {{ 0 }}, forget_gate = {{ 0 }}, out_gate = {{ 0 }}; // Various gates to controll info flow
    mli_tensor g_tsr = {{ 0 }}; // Information tensors

    // Init subtensors
    mli_point_to_subtsr_cfg iterator = {.start_coord = {0}, .coord_num=1, .first_out_dim_size=1};
    mli_hlp_point_to_subtensor(ir_tensor, &iterator, &in_gate); iterator.start_coord[0]++;
    mli_hlp_point_to_subtensor(ir_tensor, &iterator, &g_tsr); iterator.start_coord[0]++;
    mli_hlp_point_to_subtensor(ir_tensor, &iterator, &forget_gate); iterator.start_coord[0]++;
    mli_hlp_point_to_subtensor(ir_tensor, &iterator, &out_gate);

    // lstm output for one step
    mli_tensor rnn_out = {
        .data = out->data,
        .shape = {static_cast<unsigned>(lstm_out_elements)},
        .rank = 1,
        .el_type = in->el_type};
    if (cfg->act == RNN_ACT_NONE)   // fx Parameters in case of No activation
        rnn_out.el_params.fx.frac_bits = prev_out->el_params.fx.frac_bits;

    io_T *f_g = mli_prv_tensor_data_ptr<io_T *>(forget_gate);
    io_T *i_g = mli_prv_tensor_data_ptr<io_T *>(in_gate);
    io_T *g = mli_prv_tensor_data_ptr<io_T *>(g_tsr);
    io_T *c = mli_prv_tensor_data_ptr<io_T *>(cell);

    // For elementwise (assuming gates have 7 (fx8) or 15 (fx16) fractional bits)
    int eltwise_ir_shift = ((sizeof(io_T) * 8) - 1) - (int) cell->el_params.fx.frac_bits;
    int eltwise_o_shift = (sizeof(io_T) * 8) - 1;

    for (int batch = 0; batch < batch_sz; batch++) {

        // Step 1: Applying Dense
        //=======================================
        rnn_dense_op_fx(in_ptr, prev_ptr, w_ptr, b_ptr, dense_out_ptr,
                in_elements, lstm_out_elements, dense_out_elements, dense_bias_shift, in_to_state_dif, dense_out_shift);

        // Step2: Applying non-linearity
        //=======================================
        in_gate.el_params.fx.frac_bits = out_gate.el_params.fx.frac_bits = ir_tensor->el_params.fx.frac_bits;
        g_tsr.el_params.fx.frac_bits = forget_gate.el_params.fx.frac_bits = ir_tensor->el_params.fx.frac_bits;

        if (sizeof(io_T)==sizeof(int8_t)) {
            mli_krn_sigm_fx8(&in_gate, sigm_lut, &in_gate);
            mli_krn_tanh_fx8(&g_tsr, tanh_lut, &g_tsr);
            mli_krn_sigm_fx8(&forget_gate, sigm_lut, &forget_gate);
            mli_krn_sigm_fx8(&out_gate, sigm_lut, &out_gate);
        }
        else {
            mli_krn_sigm_fx16(&in_gate, sigm_lut, &in_gate);
            mli_krn_tanh_fx16(&g_tsr, tanh_lut, &g_tsr);
            mli_krn_sigm_fx16(&forget_gate, sigm_lut, &forget_gate);
            mli_krn_sigm_fx16(&out_gate, sigm_lut, &out_gate);
        }

        // Step3: Pointwise operations
        //=======================================
//      LOGICALY (NOT BITWISE) EQUAL TO THE NEXT:
//      //Forget some old info
//      mli::krn::eltwise_prepare_and_run<io_T, ELTWISE_MUL>(&forget_gate, cell, cell);
//      // Decide what new info we want to add to the mem cell
//      mli::krn::eltwise_prepare_and_run<io_T, ELTWISE_MUL>(&in_gate, &g_tsr, &new_cell_info);
//      //Adding new info into cell
//      mli::krn::eltwise_prepare_and_run<io_T, ELTWISE_ADD>(cell, &new_cell_info, cell);
        for (int idx = 0; idx < lstm_out_elements; idx++) {
            mli_acc32_t new_val = mli_math_mul_fx<io_T, mli_acc32_t>(i_g[idx], g[idx]);
            new_val = mli_math_acc_ashift_fx(new_val, eltwise_ir_shift);
            new_val = mli_math_mac_fx(new_val, f_g[idx], c[idx]);
            c[idx] = mli_math_acc_cast_fx<io_T, mli_acc32_t>(new_val, eltwise_o_shift);
        }

        // Step4: Calculate output: Activation + pointwise operation
        //===========================================================
        if (cfg->act == RNN_ACT_NONE) {
            mli::krn::eltwise_prepare_and_run<io_T, ELTWISE_MUL>(cell, &out_gate, &rnn_out);
        } else {             // Non - Linear activation
            if (sizeof(io_T)==sizeof(int8_t)) {
                if (cfg->act == RNN_ACT_TANH)
                    mli_krn_tanh_fx8(cell, tanh_lut, &rnn_out);
                else            // RNN_ACT_SIGM:
                    mli_krn_sigm_fx8(cell, sigm_lut, &rnn_out);
            } else {
                if (cfg->act == RNN_ACT_TANH)
                    mli_krn_tanh_fx16(cell, tanh_lut, &rnn_out);
                else            // RNN_ACT_SIGM:
                    mli_krn_sigm_fx16(cell, sigm_lut, &rnn_out);
            }

            mli::krn::eltwise_prepare_and_run<io_T, ELTWISE_MUL>(&rnn_out, &out_gate, &rnn_out);
        }

        // Step 5: Update pointers and tensors for next batch
        //=======================================
        in_ptr += in_elements;
        prev_ptr = mli_prv_tensor_data_ptr<MLI_PTR (io_T)>(rnn_out);
        if (cfg->mode == RNN_BATCH_TO_BATCH) {
            mli_prv_tensor_inc_data_ptr<io_T*>(&rnn_out, lstm_out_elements);
        }
    }

    // Fill output tensor params
    out->el_type = rnn_out.el_type;
    out->el_params.fx.frac_bits = rnn_out.el_params.fx.frac_bits;
    if (cfg->mode == RNN_ONE_TO_ONE || cfg->mode == RNN_BATCH_TO_LAST) {
        out->rank = 1;
        out->shape[0] = lstm_out_elements;
    } else {
        out->rank = 2;
        out->shape[0] = batch_sz;
        out->shape[1] = lstm_out_elements;
    }
}

}

#endif // _MLI_KRN_COMMON_H_
