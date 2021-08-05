/*
* Copyright 2019-2021, Synopsys, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-3-Clause license found in
* the LICENSE file in the root directory of this source tree.
*
*/

#include "mli_krn_pool_hwc.h"

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

mli_status mli_krn_maxpool_hwc_fx8_k2x2(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_maxpool_hwc_fx8(in, cfg, out, POOL_FIXED_KRN_SIZE_2), __func__);
    if (ret != MLI_STATUS_OK) return ret;
    MLI_PRINT_COMPILE_OPTIONS();

    mli::krn::mli_krn_pool_hwc<mli::krn::MAXPOOL, int8_t, POOL_FIXED_KRN_SIZE_2>(in, cfg, out);
    return MLI_STATUS_OK;
}

mli_status mli_krn_maxpool_hwc_fx8_k3x3(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_maxpool_hwc_fx8(in, cfg, out, POOL_FIXED_KRN_SIZE_3), __func__);
    if (ret != MLI_STATUS_OK) return ret;
    MLI_PRINT_COMPILE_OPTIONS();

    mli::krn::mli_krn_pool_hwc<mli::krn::MAXPOOL, int8_t, POOL_FIXED_KRN_SIZE_3>(in, cfg, out);
    return MLI_STATUS_OK;
}

mli_status mli_krn_maxpool_hwc_fx8(const mli_tensor * in, const mli_pool_cfg * cfg, mli_tensor * out) {
    mli_status ret = MLI_CHECK_STATUS(mli_chk_maxpool_hwc_fx8(in, cfg, out), __func__);
    if (ret != MLI_STATUS_OK) return ret;
    MLI_PRINT_COMPILE_OPTIONS();

    mli::krn::mli_krn_pool_hwc<mli::krn::MAXPOOL, int8_t, POOL_NO_FIXED_KRN_SIZE>(in, cfg, out);
    return MLI_STATUS_OK;
}

#pragma MLI_CODE_SECTION_END()

#ifdef __cplusplus
    }
#endif
