/* This file is generated, do not edit!
 * edit following template files instead:
 * filetemplate.txt
 * mli_krn_avepool_hwc_func_body.txt
 */
/*
* Copyright 2019-2020, Synopsys, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-3-Clause license found in
* the LICENSE file in the root directory of this source tree.
*
*/

#include "mli_krn_avepool_hwc.h"

#include "mli_config.h"
#include "mli_debug.h"
#include "mli_helpers_api.h"
#include "mli_math.h"
#include "mli_prv_tensor.h"
#include "mli_private_types.h"



#ifdef __cplusplus
extern "C" {
#endif

#pragma MLI_CODE_SECTION_START(".mli_lib")

mli_status mli_krn_avepool_hwc_fx8_k2x2_nopad(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_avepool_hwc_fx8(in, cfg, out), __func__);
    if (ret != MLI_STATUS_OK)
        return ret;

    // Extract general avepool parameters
    int stride_width = cfg->stride_width;
    int stride_height = cfg->stride_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;
    int kernel_height = cfg->kernel_height;
    int kernel_width = cfg->kernel_width;

    // Define Data dimensions
    auto in_prv = mli_prv_get_tensor_hwc<MLI_PTR(int8_t), MLI_PTR_IS_XY>(in,
            0); // channels

    // assign hard coded values for this variation to some variables
#if 0
    MLI_CHECK_AND_FIX(stride_width, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(stride_height, 0);
#endif
#if 1
    MLI_CHECK_AND_FIX(padding_top, 0);
    MLI_CHECK_AND_FIX(padding_bot, 0);
    MLI_CHECK_AND_FIX(padding_left, 0);
    MLI_CHECK_AND_FIX(padding_right, 0);
#endif
#if 2
    MLI_CHECK_AND_FIX(kernel_width, 2);
#endif
#if 2
    MLI_CHECK_AND_FIX(kernel_height, 2);
#endif

    // Define Data dimensions
    const int out_width = CEIL_DIV(in_prv.width + padding_left + padding_right - kernel_width + 1, stride_width);
    const int out_height = CEIL_DIV(in_prv.height + padding_top + padding_bot - kernel_height + 1, stride_height);

    // fill output tensor parameters
    out->el_type = in->el_type;
    out->rank = in->rank;
    out->shape[FMAP_H_DIM_HWC] = out_height;
    out->shape[FMAP_W_DIM_HWC] = out_width;
    out->shape[FMAP_C_DIM_HWC] = in_prv.ch;
    out->el_params.fx.frac_bits = in->el_params.fx.frac_bits;
    const auto out_prv = mli_prv_get_tensor_hwc<MLI_OUT_PTR(int8_t), MLI_OUT_PTR_IS_XY>(out);

    const int row_beg = 0;
    const int row_end = out_height;
    const int clmn_beg = 0;
    const int clmn_end = out_width;

    mli_prv_fx_init_dsp_ctrl();

    avepool_hwc_nopad(
        row_beg, row_end,
        clmn_beg, clmn_end,
        in_prv, out_prv,
        kernel_height, kernel_width,
        stride_height, stride_width,
        padding_top, padding_left, padding_right, padding_bot);

    return MLI_STATUS_OK;
}

mli_status mli_krn_avepool_hwc_fx8_k3x3_nopad(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_avepool_hwc_fx8(in, cfg, out), __func__);
    if (ret != MLI_STATUS_OK)
        return ret;

    // Extract general avepool parameters
    int stride_width = cfg->stride_width;
    int stride_height = cfg->stride_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;
    int kernel_height = cfg->kernel_height;
    int kernel_width = cfg->kernel_width;

    // Define Data dimensions
    auto in_prv = mli_prv_get_tensor_hwc<MLI_PTR(int8_t), MLI_PTR_IS_XY>(in,
            0); // channels

    // assign hard coded values for this variation to some variables
#if 0
    MLI_CHECK_AND_FIX(stride_width, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(stride_height, 0);
#endif
#if 1
    MLI_CHECK_AND_FIX(padding_top, 0);
    MLI_CHECK_AND_FIX(padding_bot, 0);
    MLI_CHECK_AND_FIX(padding_left, 0);
    MLI_CHECK_AND_FIX(padding_right, 0);
#endif
#if 3
    MLI_CHECK_AND_FIX(kernel_width, 3);
#endif
#if 3
    MLI_CHECK_AND_FIX(kernel_height, 3);
#endif

    // Define Data dimensions
    const int out_width = CEIL_DIV(in_prv.width + padding_left + padding_right - kernel_width + 1, stride_width);
    const int out_height = CEIL_DIV(in_prv.height + padding_top + padding_bot - kernel_height + 1, stride_height);

    // fill output tensor parameters
    out->el_type = in->el_type;
    out->rank = in->rank;
    out->shape[FMAP_H_DIM_HWC] = out_height;
    out->shape[FMAP_W_DIM_HWC] = out_width;
    out->shape[FMAP_C_DIM_HWC] = in_prv.ch;
    out->el_params.fx.frac_bits = in->el_params.fx.frac_bits;
    const auto out_prv = mli_prv_get_tensor_hwc<MLI_OUT_PTR(int8_t), MLI_OUT_PTR_IS_XY>(out);

    const int row_beg = 0;
    const int row_end = out_height;
    const int clmn_beg = 0;
    const int clmn_end = out_width;

    mli_prv_fx_init_dsp_ctrl();

    avepool_hwc_nopad(
        row_beg, row_end,
        clmn_beg, clmn_end,
        in_prv, out_prv,
        kernel_height, kernel_width,
        stride_height, stride_width,
        padding_top, padding_left, padding_right, padding_bot);

    return MLI_STATUS_OK;
}

mli_status mli_krn_avepool_hwc_fx8_k2x2_krnpad(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_avepool_hwc_fx8(in, cfg, out), __func__);
    if (ret != MLI_STATUS_OK)
        return ret;

    // Extract general avepool parameters
    int stride_width = cfg->stride_width;
    int stride_height = cfg->stride_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;
    int kernel_height = cfg->kernel_height;
    int kernel_width = cfg->kernel_width;

    // Define Data dimensions
    auto in_prv = mli_prv_get_tensor_hwc<MLI_PTR(int8_t), MLI_PTR_IS_XY>(in,
            0); // channels

    // assign hard coded values for this variation to some variables
#if 0
    MLI_CHECK_AND_FIX(stride_width, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(stride_height, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(padding_top, 0);
    MLI_CHECK_AND_FIX(padding_bot, 0);
    MLI_CHECK_AND_FIX(padding_left, 0);
    MLI_CHECK_AND_FIX(padding_right, 0);
#endif
#if 2
    MLI_CHECK_AND_FIX(kernel_width, 2);
#endif
#if 2
    MLI_CHECK_AND_FIX(kernel_height, 2);
#endif

    // Define Data dimensions
    const int out_width = CEIL_DIV(in_prv.width + padding_left + padding_right - kernel_width + 1, stride_width);
    const int out_height = CEIL_DIV(in_prv.height + padding_top + padding_bot - kernel_height + 1, stride_height);

    // fill output tensor parameters
    out->el_type = in->el_type;
    out->rank = in->rank;
    out->shape[FMAP_H_DIM_HWC] = out_height;
    out->shape[FMAP_W_DIM_HWC] = out_width;
    out->shape[FMAP_C_DIM_HWC] = in_prv.ch;
    out->el_params.fx.frac_bits = in->el_params.fx.frac_bits;
    const auto out_prv = mli_prv_get_tensor_hwc<MLI_OUT_PTR(int8_t), MLI_OUT_PTR_IS_XY>(out);

    const int row_beg = 0;
    const int row_end = out_height;
    const int clmn_beg = 0;
    const int clmn_end = out_width;

    mli_prv_fx_init_dsp_ctrl();

    avepool_hwc_krnpad(
        row_beg, row_end,
        clmn_beg, clmn_end,
        in_prv, out_prv,
        kernel_height, kernel_width,
        stride_height, stride_width,
        padding_top, padding_left, padding_right, padding_bot);

    return MLI_STATUS_OK;
}

mli_status mli_krn_avepool_hwc_fx8_k3x3_krnpad(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_avepool_hwc_fx8(in, cfg, out), __func__);
    if (ret != MLI_STATUS_OK)
        return ret;

    // Extract general avepool parameters
    int stride_width = cfg->stride_width;
    int stride_height = cfg->stride_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;
    int kernel_height = cfg->kernel_height;
    int kernel_width = cfg->kernel_width;

    // Define Data dimensions
    auto in_prv = mli_prv_get_tensor_hwc<MLI_PTR(int8_t), MLI_PTR_IS_XY>(in,
            0); // channels

    // assign hard coded values for this variation to some variables
#if 0
    MLI_CHECK_AND_FIX(stride_width, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(stride_height, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(padding_top, 0);
    MLI_CHECK_AND_FIX(padding_bot, 0);
    MLI_CHECK_AND_FIX(padding_left, 0);
    MLI_CHECK_AND_FIX(padding_right, 0);
#endif
#if 3
    MLI_CHECK_AND_FIX(kernel_width, 3);
#endif
#if 3
    MLI_CHECK_AND_FIX(kernel_height, 3);
#endif

    // Define Data dimensions
    const int out_width = CEIL_DIV(in_prv.width + padding_left + padding_right - kernel_width + 1, stride_width);
    const int out_height = CEIL_DIV(in_prv.height + padding_top + padding_bot - kernel_height + 1, stride_height);

    // fill output tensor parameters
    out->el_type = in->el_type;
    out->rank = in->rank;
    out->shape[FMAP_H_DIM_HWC] = out_height;
    out->shape[FMAP_W_DIM_HWC] = out_width;
    out->shape[FMAP_C_DIM_HWC] = in_prv.ch;
    out->el_params.fx.frac_bits = in->el_params.fx.frac_bits;
    const auto out_prv = mli_prv_get_tensor_hwc<MLI_OUT_PTR(int8_t), MLI_OUT_PTR_IS_XY>(out);

    const int row_beg = 0;
    const int row_end = out_height;
    const int clmn_beg = 0;
    const int clmn_end = out_width;

    mli_prv_fx_init_dsp_ctrl();

    avepool_hwc_krnpad(
        row_beg, row_end,
        clmn_beg, clmn_end,
        in_prv, out_prv,
        kernel_height, kernel_width,
        stride_height, stride_width,
        padding_top, padding_left, padding_right, padding_bot);

    return MLI_STATUS_OK;
}

mli_status mli_krn_avepool_hwc_fx8_generic(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_avepool_hwc_fx8(in, cfg, out), __func__);
    if (ret != MLI_STATUS_OK)
        return ret;

    // Extract general avepool parameters
    int stride_width = cfg->stride_width;
    int stride_height = cfg->stride_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;
    int kernel_height = cfg->kernel_height;
    int kernel_width = cfg->kernel_width;

    // Define Data dimensions
    auto in_prv = mli_prv_get_tensor_hwc<MLI_PTR(int8_t), MLI_PTR_IS_XY>(in,
            0); // channels

    // assign hard coded values for this variation to some variables
#if 0
    MLI_CHECK_AND_FIX(stride_width, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(stride_height, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(padding_top, 0);
    MLI_CHECK_AND_FIX(padding_bot, 0);
    MLI_CHECK_AND_FIX(padding_left, 0);
    MLI_CHECK_AND_FIX(padding_right, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(kernel_width, 0);
#endif
#if 0
    MLI_CHECK_AND_FIX(kernel_height, 0);
#endif

    // Define Data dimensions
    const int out_width = CEIL_DIV(in_prv.width + padding_left + padding_right - kernel_width + 1, stride_width);
    const int out_height = CEIL_DIV(in_prv.height + padding_top + padding_bot - kernel_height + 1, stride_height);

    // fill output tensor parameters
    out->el_type = in->el_type;
    out->rank = in->rank;
    out->shape[FMAP_H_DIM_HWC] = out_height;
    out->shape[FMAP_W_DIM_HWC] = out_width;
    out->shape[FMAP_C_DIM_HWC] = in_prv.ch;
    out->el_params.fx.frac_bits = in->el_params.fx.frac_bits;
    const auto out_prv = mli_prv_get_tensor_hwc<MLI_OUT_PTR(int8_t), MLI_OUT_PTR_IS_XY>(out);

    const int row_beg = 0;
    const int row_end = out_height;
    const int clmn_beg = 0;
    const int clmn_end = out_width;

    mli_prv_fx_init_dsp_ctrl();

    avepool_hwc_krnpad(
        row_beg, row_end,
        clmn_beg, clmn_end,
        in_prv, out_prv,
        kernel_height, kernel_width,
        stride_height, stride_width,
        padding_top, padding_left, padding_right, padding_bot);

    return MLI_STATUS_OK;
}


mli_status mli_krn_avepool_hwc_fx8(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    int kernel_w = cfg->kernel_width;
    int kernel_h = cfg->kernel_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;

    if ((kernel_w == 3) && (kernel_h == 3) && (padding_top == 0) && (padding_bot == 0) && (padding_left == 0) && (padding_right == 0)) {
        return mli_krn_avepool_hwc_fx8_k3x3_nopad(in, cfg, out);
    } else if ((kernel_w == 3) && (kernel_h == 3) && (padding_top <= 1) && (padding_bot <= 1) && (padding_left <= 1) && (padding_right <= 1)) {
        return mli_krn_avepool_hwc_fx8_k3x3_krnpad(in, cfg, out);
    } else if ((kernel_w == 2) && (kernel_h == 2) && (padding_top == 0) && (padding_bot == 0) && (padding_left == 0) && (padding_right == 0)) {
        return mli_krn_avepool_hwc_fx8_k2x2_nopad(in, cfg, out);
    } else if ((kernel_w == 2) && (kernel_h == 2) && (padding_top <= 0) && (padding_bot <= 1) && (padding_left <= 0) && (padding_right <= 1)) {
        return mli_krn_avepool_hwc_fx8_k2x2_krnpad(in, cfg, out);
    } else {
        return mli_krn_avepool_hwc_fx8_generic(in, cfg, out);
    }
}
char * mli_debug_krn_avepool_hwc_fx8(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    int kernel_w = cfg->kernel_width;
    int kernel_h = cfg->kernel_height;
    int padding_top = cfg->padding_top;
    int padding_bot = cfg->padding_bottom;
    int padding_left = cfg->padding_left;
    int padding_right = cfg->padding_right;

    if ((kernel_w == 3) && (kernel_h == 3) && (padding_top == 0) && (padding_bot == 0) && (padding_left == 0) && (padding_right == 0)) {
        return (char*)"mli_krn_avepool_hwc_fx8_k3x3_nopad";
    } else if ((kernel_w == 3) && (kernel_h == 3) && (padding_top <= 1) && (padding_bot <= 1) && (padding_left <= 1) && (padding_right <= 1)) {
        return (char*)"mli_krn_avepool_hwc_fx8_k3x3_krnpad";
    } else if ((kernel_w == 2) && (kernel_h == 2) && (padding_top == 0) && (padding_bot == 0) && (padding_left == 0) && (padding_right == 0)) {
        return (char*)"mli_krn_avepool_hwc_fx8_k2x2_nopad";
    } else if ((kernel_w == 2) && (kernel_h == 2) && (padding_top <= 0) && (padding_bot <= 1) && (padding_left <= 0) && (padding_right <= 1)) {
        return (char*)"mli_krn_avepool_hwc_fx8_k2x2_krnpad";
    } else {
        return (char*)"mli_krn_avepool_hwc_fx8_generic";
    }
}

#pragma MLI_CODE_SECTION_END()

#ifdef __cplusplus
    }
#endif
