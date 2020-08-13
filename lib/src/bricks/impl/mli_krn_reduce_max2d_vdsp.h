/*
* Copyright 2020-2020, Synopsys, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-3-Clause license found in
* the LICENSE file in the root directory of this source tree.
*
*/

#ifndef _MLI_KRN_RECUCE_MAX2D_VDSP_H_
#define _MLI_KRN_RECUCE_MAX2D_VDSP_H_

#include "mli_krn_reduce_max2d_decl.h"
#include "mli_config.h"
#include "mli_prv_dsp.h"

namespace mli {
namespace krn {
namespace vdsp {

template <typename io_T>
static inline void __attribute__((always_inline)) reduce_max2D_hwc_v(
		const MLI_PTR(io_T) in,
		MLI_PTR(io_T) out,
		const int width,
        const int height,
		const int channels,
		const int col_mem_stride,
		const int row_mem_stride,
		const bool fixed_size) {
	/* TODO */
}

template <typename io_T>
static inline void __attribute__((always_inline)) reduce_max2D_hwc(
		const MLI_PTR(io_T) in,
		MLI_PTR(io_T) out,
		const int width,
        const int height,
		const int channels,
		const int col_mem_stride,
		const int row_mem_stride,
		const bool fixed_size) {
	/* TODO */
}

} // namespace dsp
} // namespace ref
} // namespace mli

#endif // _MLI_KRN_RECUCE_MAX2D_VDSP_H_
