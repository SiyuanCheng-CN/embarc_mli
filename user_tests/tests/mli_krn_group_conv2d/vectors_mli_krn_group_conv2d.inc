/*
* Copyright 2020, Synopsys, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-3-Clause license found in
* the LICENSE file in the root directory of this source tree.
*
*/

#include <stdint.h>

#include "mli_types.h"
#include "test_tensor_quantizer.h"

using mli::tst::tensor_quantizer;


// Generated input vectors Declaration
//========================================

extern mli::tst::tensor_quantizer input_SimpleTestQuantizedPerChannel;

// Generated weights vectors Declaration
//========================================

extern mli::tst::tensor_quantizer weights_SimpleTestQuantizedPerChannel;
extern mli::tst::tensor_quantizer bias_SimpleTestQuantizedPerChannel;

// Extracted Output vectors Declaration
//===================================================

extern mli::tst::tensor_quantizer test_out_SimpleTestQuantizedPerChannel;

// Tests configuration structures Declaration
//========================================

extern const mli_conv2d_cfg test_1_cfg;

// Generated input vectors 
//========================================

static const float input_1_data[] = {
        1, 2, 7, 8, 3, 4, 9, 10, 5, 6, 11, 12
};

static const float input_1_scale = 0.5f;
static const float input_1_zero_point = 0.0f;
static const int8_t input_1_scales_frac[] = {15};
static const int input_1_sa_dim = -1;

// static const int input_1_fx8_frac = 6;

#define INPUT_1_TSR_SHARED_DESCR \
    /* .data = */ { 0 },\
    /* .mem_stride = */ {0}, \
    /* .shape = */ {3, 2, 2}, \
    /* .rank =  */ 3

// #define INPUT_1_MEMSTR_TSR_SHARED_DESCR \
//     /* .data = */ { 0 },\
//     /* .mem_stride = */ {13*6*1, 6*1, 1}, \
//     /* .shape = */ {7, 7, 9}, \
//     /* .rank =  */ 3


static const mli_tensor input_tsr_SimpleTestQuantizedPerChannel = {
    INPUT_1_TSR_SHARED_DESCR,

    /* .el_type = */ MLI_EL_SA_8,
    /* .el_params = */ { 0 }
};

// tensor_quantizer input_1_fx16(input_tsr_SimpleTestQuantizedPerChannel, input_1_fx8_frac + 8, input_1_data, 
//     sizeof(input_1_data) / sizeof(input_1_data[0]));

// tensor_quantizer input_1_memstr_fx16(input_1_tsr_fx16, input_1_fx8_frac + 8, input_1_data, 
//     sizeof(input_1_data) / sizeof(input_1_data[0]));

tensor_quantizer input_1_sa8(input_tsr_SimpleTestQuantizedPerChannel, input_1_sa_dim, input_1_data, 
    sizeof(input_1_data) / sizeof(input_1_data[0]), &input_1_scale, 1, &input_1_zero_point, 1, input_1_scales_frac, 1);

// tensor_quantizer input_1_memstr_sa8(input_1_tsr_sa8, input_1_sa_dim, input_1_data, 
//     sizeof(input_1_data) / sizeof(input_1_data[0]), &input_1_scale, 1, &input_1_zero_point, 1, input_1_scales_frac, 1);

// Generated weights vectors 
//========================================

static const float weights_1_data[] = {
    1, 2, 3, 4, -9, 10, -11, 12, 5, 6, 7, 8, 13, -14, 15, -16
};

static const float weights_1_scales[] = {0.1023622f, 0.1102362f, 0.1181102f, 0.1259843f};
static const float weights_1_zero_points[] = {0.f, 0.f, 0.f, 0.f};
static const int8_t weights_1_scales_frac[] = {18, 18, 18, 17};
static const int weights_1_sa_dim = 3;

#define WEIGHTS_1_TSR_SHARED_DESCR \
    /* .data = */ { 0 },\
    /* .mem_stride = */ { 0 }, \
    /* .shape = */ {2, 2, 1, 4}, \
    /* .rank =  */ 4

static const mli_tensor weights_tsr_SimpleTestQuantizedPerChannel = {
    WEIGHTS_1_TSR_SHARED_DESCR,

    /* .el_type = */ MLI_EL_SA_8,
    /* .el_params = */ { 0 }
};

tensor_quantizer weights_SimpleTestQuantizedPerChannel(weights_tsr_SimpleTestQuantizedPerChannel, weights_1_sa_dim, weights_1_data, 
    sizeof(weights_1_data) / sizeof(weights_1_data[0]), weights_1_scales, 
    sizeof(weights_1_scales) / sizeof(weights_1_scales[0]), weights_1_zero_points, 
    sizeof(weights_1_zero_points) / sizeof(weights_1_zero_points[0]), weights_1_scales_frac, 
    sizeof(weights_1_scales_frac) / sizeof(weights_1_scales_frac[0]));


// Generated bias vectors 
//========================================

static const float bias_1_data[] = {
    1, 2, 3, 4
};

static const float bias_1_scales[] = {0.0511811, 0.05511811, 0.05905512, 0.06299213};
static const float bias_1_zero_points[] = {0.f, 0.f, 0.f, 0.f};
static const int8_t bias_1_scales_frac[] = {19, 19, 19, 18};
static const int bias_1_sa_dim = 0;

#define BIAS_1_TSR_SHARED_DESCR \
    /* .data = */ { 0 },\
    /* .mem_stride = */ { 0 }, \
    /* .shape = */ { 4 }, \
    /* .rank =  */ 1

static const mli_tensor bias_1_tsr_SimpleTestQuantizedPerChannel = {
    BIAS_1_TSR_SHARED_DESCR,

    /* .el_type = */ MLI_EL_SA_32,
    /* .el_params = */ { 0 }
};

tensor_quantizer bias_SimpleTestQuantizedPerChannel(bias_1_tsr_SimpleTestQuantizedPerChannel, bias_1_sa_dim, bias_1_data, 
    sizeof(bias_1_data) / sizeof(bias_1_data[0]), bias_1_scales, sizeof(bias_1_scales) / sizeof(bias_1_scales[0]), 
    bias_1_zero_points, sizeof(bias_1_zero_points) / sizeof(bias_1_zero_points[0]), 
    bias_1_scales_frac, sizeof(bias_1_scales_frac) / sizeof(bias_1_scales_frac[0]));

// Generated output vectors 
//========================================

static const float test_1_out_data[] = {
    71, -34, 99, -20, 91, -26, 127, -4
};

static const float test_1_out_scale = 1.0f;
static const float test_1_out_zero_point = 0.f;
static const int8_t test_1_out_scales_frac[] = {15};
static const int test_1_out_sa_dim = -1;

#define TEST_1_OUT_TSR_SHARED_DESCR \
    /* .data = */ { 0 },\
    /* .mem_stride = */ { 0 }, \
    /* .shape = */ { 2, 1, 4 }, \
    /* .rank =  */ 3


static const mli_tensor test_1_out_tsr_sa8 = {
    TEST_1_OUT_TSR_SHARED_DESCR,

    /* .el_type = */ MLI_EL_SA_8,
    /* .el_params = */ { 0 }
};


tensor_quantizer test_1_out_sa8(test_1_out_tsr_sa8, test_1_out_sa_dim, test_1_out_data, 
    sizeof(test_1_out_data) / sizeof(test_1_out_data[0]), &test_1_out_scale, 1, 
    &test_1_out_zero_point, 1, test_1_out_scales_frac, 1);


// Tests configuration structures
//========================================

const mli_conv2d_cfg test_1_cfg = {
    /* .relu.type = */ MLI_RELU_NONE,
    /* .stride_width = */ 1,
    /* .stride_height = */ 1,
    /* .padding_left = */ 0,
    /* .padding_right = */ 0,
    /* .padding_top = */ 0,
    /* .padding_bottom = */ 0,
    /* .dilation_width = */ 0,
    /* .dilation_height = */ 0
};