/*
* Copyright 2021, Synopsys, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-3-Clause license found in
* the LICENSE file in the root directory of this source tree.
*
*/

#ifndef _MLI_KRN_RNN_DENSE_OP_VDSP_H_
#define _MLI_KRN_RNN_DENSE_OP_VDSP_H_

#include "mli_config.h"
#include "mli_debug.h"
#include "mli_math.h"
#include "mli_types.h"
#include "mli_prv_dsp.h"
#include "mli_krn_dotprod.h"

namespace mli {
namespace krn {
namespace vdsp {

MLI_FORCE_INLINE vNx2accint_t mli_math_add_accus(vNx2accint_t L, vNx2accint_t R) {
	return mli_math_add(L, R);
}

MLI_FORCE_INLINE vNx4accint_t mli_math_add_accus(vNx4accint_t L, vNx4accint_t R) {
	return mli_math_add(L, R);
}

MLI_FORCE_INLINE vNx4accshort_t mli_math_add_accus(vNx4accshort_t L, vNx4accshort_t R) {
#if (__Xvec_guard_bit_option == 0)
	vNx4short_t L_short = mli_math_acc_cast_fx<vNx4short_t, vNx4accshort_t>(L);
	vNx4short_t R_short = mli_math_acc_cast_fx<vNx4short_t, vNx4accshort_t>(R);

	vNx4short_t res = mli_math_add_fx<vNx4short_t>(L_short, R_short);

	return mli_math_init_accu_add<vNx4short_t, vNx4accshort_t>(res, (vNx4short_t)0);
#else
	return mli_math_add(L, R);
#endif
}

template <typename io_T, typename w_T, typename b_T, typename acc_T, typename quant_T>
static inline void rnn_dense_op(
        const MLI_PTR(io_T) __restrict * inputs,
        const MLI_PTR(w_T) __restrict * weights,
        const MLI_PTR(b_T) __restrict bias,
        MLI_CONV_OUT_PTR(io_T) __restrict out,
        const int inputs_num,
        const int * in_elements,
        const int out_elements,
        const int * w_ch_out_mem_strides,
        quant_T * in_to_out_quant_params,
        const io_T val_min_limit,
        const io_T val_max_limit) {

    int num_lanes = get_number_lanes<acc_T>();

    for (int o_idx = 0; o_idx < out_elements; o_idx += num_lanes) {
        int remaining_ch = out_elements - o_idx;
        int current_chs = MIN(remaining_ch, num_lanes); // number of channels computed in this loop iteration

        acc_T accu = mli_prv_init_accu<acc_T>();
        acc_T prev_step = mli_prv_init_accu<acc_T>();

        auto output_params = adjust_quant_params_v(&in_to_out_quant_params[0], 0);
        accu = mli::krn::bias_additive(&bias[o_idx], accu, &output_params, /* add_preshift_rnd */ false);

        for(int idx = 0; idx < inputs_num; idx++) {

            output_params = adjust_quant_params_v(&in_to_out_quant_params[idx], 0);
            accu = dotprod_inputzp_1D_v(inputs[idx], &weights[idx][o_idx], accu, in_elements[idx],
                    1, w_ch_out_mem_strides[idx], &in_to_out_quant_params[idx]);

            accu = mli_math_add_accus(accu, prev_step);

            if(inputs_num - idx != 1) {
                mli::krn::ref::adjust_quant_params(&in_to_out_quant_params[idx], o_idx);
                prev_step = mli::krn::ir_rnn_result_requantize(accu, &in_to_out_quant_params[idx], /* krn_idx= */ 0);
                accu = mli_prv_init_accu<acc_T>();
            } else {
                // Cast result to output type with scaling
                mli::krn::result_cast_relu_store_v(&out[o_idx], accu, &output_params,
                        val_min_limit, val_max_limit, current_chs, /* add_preshift_rnd */ true);
            }
        }

    }
}

} // namespace vdsp
} // namespace krn
} // namespace mli

#endif // _MLI_KRN_RNN_DENSE_OP_VDSP_H_
