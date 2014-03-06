/* Include files */

#include "blascompat32.h"
#include "feedbackLineariz_sfun.h"
#include "c2_feedbackLineariz.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "feedbackLineariz_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[16] = { "kd", "qDes", "nargin",
  "nargout", "qInit", "q", "qD", "g", "gin", "kp", "M", "h", "qInitOut", "tau",
  "gOut", "e" };

/* Function Declarations */
static void initialize_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance);
static void initialize_params_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance);
static void enable_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance);
static void disable_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance);
static void set_sim_state_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance);
static void sf_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance);
static void initSimStructsc2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_e, const char_T *c2_identifier, real_T c2_y
  [25]);
static void c2_b_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[25]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_eml_scalar_eg(SFc2_feedbackLinearizInstanceStruct *chartInstance);
static void c2_eml_xgemm(SFc2_feedbackLinearizInstanceStruct *chartInstance,
  real_T c2_A[625], real_T c2_B[25], real_T c2_C[25], real_T c2_b_C[25]);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_d_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_feedbackLineariz, const
  char_T *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_eml_xgemm(SFc2_feedbackLinearizInstanceStruct *chartInstance,
  real_T c2_A[625], real_T c2_B[25], real_T c2_C[25]);
static void init_dsm_address_info(SFc2_feedbackLinearizInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_feedbackLineariz = 0U;
}

static void initialize_params_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance)
{
}

static void enable_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[25];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[25];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[25];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i3;
  real_T c2_d_u[25];
  const mxArray *c2_e_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  real_T (*c2_tau)[25];
  real_T (*c2_qInitOut)[25];
  real_T (*c2_gOut)[25];
  real_T (*c2_e)[25];
  c2_e = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_gOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_tau = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_qInitOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(5), FALSE);
  for (c2_i0 = 0; c2_i0 < 25; c2_i0++) {
    c2_u[c2_i0] = (*c2_e)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 25), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 25; c2_i1++) {
    c2_b_u[c2_i1] = (*c2_gOut)[c2_i1];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 25), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 25; c2_i2++) {
    c2_c_u[c2_i2] = (*c2_qInitOut)[c2_i2];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 25), FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  for (c2_i3 = 0; c2_i3 < 25; c2_i3++) {
    c2_d_u[c2_i3] = (*c2_tau)[c2_i3];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 25), FALSE);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_feedbackLineariz;
  c2_e_u = c2_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[25];
  int32_T c2_i4;
  real_T c2_dv1[25];
  int32_T c2_i5;
  real_T c2_dv2[25];
  int32_T c2_i6;
  real_T c2_dv3[25];
  int32_T c2_i7;
  real_T (*c2_e)[25];
  real_T (*c2_gOut)[25];
  real_T (*c2_qInitOut)[25];
  real_T (*c2_tau)[25];
  c2_e = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_gOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_tau = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_qInitOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "e",
                      c2_dv0);
  for (c2_i4 = 0; c2_i4 < 25; c2_i4++) {
    (*c2_e)[c2_i4] = c2_dv0[c2_i4];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "gOut",
                      c2_dv1);
  for (c2_i5 = 0; c2_i5 < 25; c2_i5++) {
    (*c2_gOut)[c2_i5] = c2_dv1[c2_i5];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
                      "qInitOut", c2_dv2);
  for (c2_i6 = 0; c2_i6 < 25; c2_i6++) {
    (*c2_qInitOut)[c2_i6] = c2_dv2[c2_i6];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 3)), "tau",
                      c2_dv3);
  for (c2_i7 = 0; c2_i7 < 25; c2_i7++) {
    (*c2_tau)[c2_i7] = c2_dv3[c2_i7];
  }

  chartInstance->c2_is_active_c2_feedbackLineariz = c2_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 4)),
     "is_active_c2_feedbackLineariz");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_feedbackLineariz(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance)
{
}

static void sf_c2_feedbackLineariz(SFc2_feedbackLinearizInstanceStruct
  *chartInstance)
{
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  real_T c2_qInit[25];
  int32_T c2_i21;
  real_T c2_q[25];
  int32_T c2_i22;
  real_T c2_qD[25];
  int32_T c2_i23;
  real_T c2_g[25];
  int32_T c2_i24;
  real_T c2_gin[25];
  int32_T c2_i25;
  real_T c2_kp[625];
  int32_T c2_i26;
  real_T c2_M[961];
  int32_T c2_i27;
  real_T c2_h[31];
  uint32_T c2_debug_family_var_map[16];
  real_T c2_kd;
  real_T c2_qDes[25];
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 4.0;
  real_T c2_qInitOut[25];
  real_T c2_tau[25];
  real_T c2_gOut[25];
  real_T c2_e[25];
  int32_T c2_i28;
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  real_T c2_a[625];
  int32_T c2_i33;
  real_T c2_b[25];
  int32_T c2_i34;
  real_T c2_y[25];
  int32_T c2_i35;
  real_T c2_b_a[625];
  int32_T c2_i36;
  real_T c2_b_b[25];
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  int32_T c2_i40;
  int32_T c2_i41;
  real_T (*c2_b_qInitOut)[25];
  real_T (*c2_b_tau)[25];
  real_T (*c2_b_gOut)[25];
  real_T (*c2_b_e)[25];
  real_T (*c2_b_h)[31];
  real_T (*c2_b_M)[961];
  real_T (*c2_b_kp)[625];
  real_T (*c2_b_gin)[25];
  real_T (*c2_b_g)[25];
  real_T (*c2_b_qD)[25];
  real_T (*c2_b_q)[25];
  real_T (*c2_b_qInit)[25];
  c2_b_h = (real_T (*)[31])ssGetInputPortSignal(chartInstance->S, 7);
  c2_b_M = (real_T (*)[961])ssGetInputPortSignal(chartInstance->S, 6);
  c2_b_e = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_b_kp = (real_T (*)[625])ssGetInputPortSignal(chartInstance->S, 5);
  c2_b_gOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_b_gin = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_g = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_qD = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_tau = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_qInitOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_q = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_qInit = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i8 = 0; c2_i8 < 25; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_qInit)[c2_i8], 0U);
  }

  for (c2_i9 = 0; c2_i9 < 25; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_q)[c2_i9], 1U);
  }

  for (c2_i10 = 0; c2_i10 < 25; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_qInitOut)[c2_i10], 2U);
  }

  for (c2_i11 = 0; c2_i11 < 25; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_tau)[c2_i11], 3U);
  }

  for (c2_i12 = 0; c2_i12 < 25; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_qD)[c2_i12], 4U);
  }

  for (c2_i13 = 0; c2_i13 < 25; c2_i13++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_g)[c2_i13], 5U);
  }

  for (c2_i14 = 0; c2_i14 < 25; c2_i14++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_gin)[c2_i14], 6U);
  }

  for (c2_i15 = 0; c2_i15 < 25; c2_i15++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_gOut)[c2_i15], 7U);
  }

  for (c2_i16 = 0; c2_i16 < 625; c2_i16++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_kp)[c2_i16], 8U);
  }

  for (c2_i17 = 0; c2_i17 < 25; c2_i17++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_e)[c2_i17], 9U);
  }

  for (c2_i18 = 0; c2_i18 < 961; c2_i18++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_M)[c2_i18], 10U);
  }

  for (c2_i19 = 0; c2_i19 < 31; c2_i19++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_h)[c2_i19], 11U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i20 = 0; c2_i20 < 25; c2_i20++) {
    c2_qInit[c2_i20] = (*c2_b_qInit)[c2_i20];
  }

  for (c2_i21 = 0; c2_i21 < 25; c2_i21++) {
    c2_q[c2_i21] = (*c2_b_q)[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 25; c2_i22++) {
    c2_qD[c2_i22] = (*c2_b_qD)[c2_i22];
  }

  for (c2_i23 = 0; c2_i23 < 25; c2_i23++) {
    c2_g[c2_i23] = (*c2_b_g)[c2_i23];
  }

  for (c2_i24 = 0; c2_i24 < 25; c2_i24++) {
    c2_gin[c2_i24] = (*c2_b_gin)[c2_i24];
  }

  for (c2_i25 = 0; c2_i25 < 625; c2_i25++) {
    c2_kp[c2_i25] = (*c2_b_kp)[c2_i25];
  }

  for (c2_i26 = 0; c2_i26 < 961; c2_i26++) {
    c2_M[c2_i26] = (*c2_b_M)[c2_i26];
  }

  for (c2_i27 = 0; c2_i27 < 31; c2_i27++) {
    c2_h[c2_i27] = (*c2_b_h)[c2_i27];
  }

  sf_debug_symbol_scope_push_eml(0U, 16U, 16U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_kd, 0U, c2_e_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_qDes, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_e_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_e_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_qInit, 4U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_q, 5U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_qD, 6U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_g, 7U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_gin, 8U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_kp, 9U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_M, 10U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_h, 11U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_qInitOut, 12U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_tau, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_gOut, 14U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_e, 15U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  for (c2_i28 = 0; c2_i28 < 25; c2_i28++) {
    c2_qInitOut[c2_i28] = c2_qInit[c2_i28];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_kd = 0.3;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  for (c2_i29 = 0; c2_i29 < 25; c2_i29++) {
    c2_qDes[c2_i29] = c2_qInit[c2_i29];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_qDes[2] += 0.1;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  for (c2_i30 = 0; c2_i30 < 25; c2_i30++) {
    c2_e[c2_i30] = c2_q[c2_i30] - c2_qDes[c2_i30];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  for (c2_i31 = 0; c2_i31 < 25; c2_i31++) {
    c2_gOut[c2_i31] = c2_gin[c2_i31];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  for (c2_i32 = 0; c2_i32 < 625; c2_i32++) {
    c2_a[c2_i32] = c2_kp[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 25; c2_i33++) {
    c2_b[c2_i33] = c2_e[c2_i33];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i34 = 0; c2_i34 < 25; c2_i34++) {
    c2_y[c2_i34] = 0.0;
  }

  for (c2_i35 = 0; c2_i35 < 625; c2_i35++) {
    c2_b_a[c2_i35] = c2_a[c2_i35];
  }

  for (c2_i36 = 0; c2_i36 < 25; c2_i36++) {
    c2_b_b[c2_i36] = c2_b[c2_i36];
  }

  c2_b_eml_xgemm(chartInstance, c2_b_a, c2_b_b, c2_y);
  for (c2_i37 = 0; c2_i37 < 25; c2_i37++) {
    c2_tau[c2_i37] = c2_gin[c2_i37] - (c2_y[c2_i37] + c2_kd * c2_qD[c2_i37]);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -15);
  sf_debug_symbol_scope_pop();
  for (c2_i38 = 0; c2_i38 < 25; c2_i38++) {
    (*c2_b_qInitOut)[c2_i38] = c2_qInitOut[c2_i38];
  }

  for (c2_i39 = 0; c2_i39 < 25; c2_i39++) {
    (*c2_b_tau)[c2_i39] = c2_tau[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 25; c2_i40++) {
    (*c2_b_gOut)[c2_i40] = c2_gOut[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 25; c2_i41++) {
    (*c2_b_e)[c2_i41] = c2_e[c2_i41];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  sf_debug_check_for_state_inconsistency(_feedbackLinearizMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_feedbackLineariz
  (SFc2_feedbackLinearizInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i42;
  real_T c2_b_inData[25];
  int32_T c2_i43;
  real_T c2_u[25];
  const mxArray *c2_y = NULL;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i42 = 0; c2_i42 < 25; c2_i42++) {
    c2_b_inData[c2_i42] = (*(real_T (*)[25])c2_inData)[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 25; c2_i43++) {
    c2_u[c2_i43] = c2_b_inData[c2_i43];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 25), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_e, const char_T *c2_identifier, real_T c2_y
  [25])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_e), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_e);
}

static void c2_b_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[25])
{
  real_T c2_dv4[25];
  int32_T c2_i44;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv4, 1, 0, 0U, 1, 0U, 1, 25);
  for (c2_i44 = 0; c2_i44 < 25; c2_i44++) {
    c2_y[c2_i44] = c2_dv4[c2_i44];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_e;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[25];
  int32_T c2_i45;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_e = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_e), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_e);
  for (c2_i45 = 0; c2_i45 < 25; c2_i45++) {
    (*(real_T (*)[25])c2_outData)[c2_i45] = c2_y[c2_i45];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i46;
  real_T c2_b_inData[31];
  int32_T c2_i47;
  real_T c2_u[31];
  const mxArray *c2_y = NULL;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i46 = 0; c2_i46 < 31; c2_i46++) {
    c2_b_inData[c2_i46] = (*(real_T (*)[31])c2_inData)[c2_i46];
  }

  for (c2_i47 = 0; c2_i47 < 31; c2_i47++) {
    c2_u[c2_i47] = c2_b_inData[c2_i47];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 31), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  real_T c2_b_inData[961];
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_i53;
  real_T c2_u[961];
  const mxArray *c2_y = NULL;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i48 = 0;
  for (c2_i49 = 0; c2_i49 < 31; c2_i49++) {
    for (c2_i50 = 0; c2_i50 < 31; c2_i50++) {
      c2_b_inData[c2_i50 + c2_i48] = (*(real_T (*)[961])c2_inData)[c2_i50 +
        c2_i48];
    }

    c2_i48 += 31;
  }

  c2_i51 = 0;
  for (c2_i52 = 0; c2_i52 < 31; c2_i52++) {
    for (c2_i53 = 0; c2_i53 < 31; c2_i53++) {
      c2_u[c2_i53 + c2_i51] = c2_b_inData[c2_i53 + c2_i51];
    }

    c2_i51 += 31;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 31, 31), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i54;
  int32_T c2_i55;
  int32_T c2_i56;
  real_T c2_b_inData[625];
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  real_T c2_u[625];
  const mxArray *c2_y = NULL;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i54 = 0;
  for (c2_i55 = 0; c2_i55 < 25; c2_i55++) {
    for (c2_i56 = 0; c2_i56 < 25; c2_i56++) {
      c2_b_inData[c2_i56 + c2_i54] = (*(real_T (*)[625])c2_inData)[c2_i56 +
        c2_i54];
    }

    c2_i54 += 25;
  }

  c2_i57 = 0;
  for (c2_i58 = 0; c2_i58 < 25; c2_i58++) {
    for (c2_i59 = 0; c2_i59 < 25; c2_i59++) {
      c2_u[c2_i59 + c2_i57] = c2_b_inData[c2_i59 + c2_i57];
    }

    c2_i57 += 25;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 25, 25), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_feedbackLineariz_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[9];
  c2_ResolvedFunctionInfo (*c2_b_info)[9];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i60;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_b_info = (c2_ResolvedFunctionInfo (*)[9])c2_info;
  (*c2_b_info)[0].context = "";
  (*c2_b_info)[0].name = "mtimes";
  (*c2_b_info)[0].dominantType = "double";
  (*c2_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[0].fileTimeLo = 1289519692U;
  (*c2_b_info)[0].fileTimeHi = 0U;
  (*c2_b_info)[0].mFileTimeLo = 0U;
  (*c2_b_info)[0].mFileTimeHi = 0U;
  (*c2_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[1].name = "eml_index_class";
  (*c2_b_info)[1].dominantType = "";
  (*c2_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c2_b_info)[1].fileTimeLo = 1323170578U;
  (*c2_b_info)[1].fileTimeHi = 0U;
  (*c2_b_info)[1].mFileTimeLo = 0U;
  (*c2_b_info)[1].mFileTimeHi = 0U;
  (*c2_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[2].name = "eml_scalar_eg";
  (*c2_b_info)[2].dominantType = "double";
  (*c2_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c2_b_info)[2].fileTimeLo = 1286818796U;
  (*c2_b_info)[2].fileTimeHi = 0U;
  (*c2_b_info)[2].mFileTimeLo = 0U;
  (*c2_b_info)[2].mFileTimeHi = 0U;
  (*c2_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[3].name = "eml_xgemm";
  (*c2_b_info)[3].dominantType = "char";
  (*c2_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  (*c2_b_info)[3].fileTimeLo = 1299076772U;
  (*c2_b_info)[3].fileTimeHi = 0U;
  (*c2_b_info)[3].mFileTimeLo = 0U;
  (*c2_b_info)[3].mFileTimeHi = 0U;
  (*c2_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  (*c2_b_info)[4].name = "eml_blas_inline";
  (*c2_b_info)[4].dominantType = "";
  (*c2_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  (*c2_b_info)[4].fileTimeLo = 1299076768U;
  (*c2_b_info)[4].fileTimeHi = 0U;
  (*c2_b_info)[4].mFileTimeLo = 0U;
  (*c2_b_info)[4].mFileTimeHi = 0U;
  (*c2_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  (*c2_b_info)[5].name = "mtimes";
  (*c2_b_info)[5].dominantType = "double";
  (*c2_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[5].fileTimeLo = 1289519692U;
  (*c2_b_info)[5].fileTimeHi = 0U;
  (*c2_b_info)[5].mFileTimeLo = 0U;
  (*c2_b_info)[5].mFileTimeHi = 0U;
  (*c2_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  (*c2_b_info)[6].name = "eml_index_class";
  (*c2_b_info)[6].dominantType = "";
  (*c2_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c2_b_info)[6].fileTimeLo = 1323170578U;
  (*c2_b_info)[6].fileTimeHi = 0U;
  (*c2_b_info)[6].mFileTimeLo = 0U;
  (*c2_b_info)[6].mFileTimeHi = 0U;
  (*c2_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  (*c2_b_info)[7].name = "eml_scalar_eg";
  (*c2_b_info)[7].dominantType = "double";
  (*c2_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c2_b_info)[7].fileTimeLo = 1286818796U;
  (*c2_b_info)[7].fileTimeHi = 0U;
  (*c2_b_info)[7].mFileTimeLo = 0U;
  (*c2_b_info)[7].mFileTimeHi = 0U;
  (*c2_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  (*c2_b_info)[8].name = "eml_refblas_xgemm";
  (*c2_b_info)[8].dominantType = "char";
  (*c2_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  (*c2_b_info)[8].fileTimeLo = 1299076774U;
  (*c2_b_info)[8].fileTimeHi = 0U;
  (*c2_b_info)[8].mFileTimeLo = 0U;
  (*c2_b_info)[8].mFileTimeHi = 0U;
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 9), FALSE);
  for (c2_i60 = 0; c2_i60 < 9; c2_i60++) {
    c2_r0 = &c2_info[c2_i60];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i60);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i60);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_eml_scalar_eg(SFc2_feedbackLinearizInstanceStruct *chartInstance)
{
}

static void c2_eml_xgemm(SFc2_feedbackLinearizInstanceStruct *chartInstance,
  real_T c2_A[625], real_T c2_B[25], real_T c2_C[25], real_T c2_b_C[25])
{
  int32_T c2_i61;
  int32_T c2_i62;
  real_T c2_b_A[625];
  int32_T c2_i63;
  real_T c2_b_B[25];
  for (c2_i61 = 0; c2_i61 < 25; c2_i61++) {
    c2_b_C[c2_i61] = c2_C[c2_i61];
  }

  for (c2_i62 = 0; c2_i62 < 625; c2_i62++) {
    c2_b_A[c2_i62] = c2_A[c2_i62];
  }

  for (c2_i63 = 0; c2_i63 < 25; c2_i63++) {
    c2_b_B[c2_i63] = c2_B[c2_i63];
  }

  c2_b_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_d_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i64;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i64, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i64;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_feedbackLineariz, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_feedbackLineariz), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_feedbackLineariz);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_feedbackLinearizInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_eml_xgemm(SFc2_feedbackLinearizInstanceStruct *chartInstance,
  real_T c2_A[625], real_T c2_B[25], real_T c2_C[25])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSB;
  char_T c2_TRANSA;
  c2_m = 25;
  c2_n = 1;
  c2_k = 25;
  c2_alpha1 = 1.0;
  c2_lda = 25;
  c2_ldb = 25;
  c2_beta1 = 0.0;
  c2_ldc = 25;
  c2_TRANSB = 'N';
  c2_TRANSA = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void init_dsm_address_info(SFc2_feedbackLinearizInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_feedbackLineariz_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3739199379U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2933637691U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3943103720U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(790448683U);
}

mxArray *sf_c2_feedbackLineariz_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("NCQHNK7ONwh5xYTx0nwGdE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(25);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(31);
      pr[1] = (double)(31);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(31);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(25);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_feedbackLineariz(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[13],T\"e\",},{M[1],M[11],T\"gOut\",},{M[1],M[5],T\"qInitOut\",},{M[1],M[6],T\"tau\",},{M[8],M[0],T\"is_active_c2_feedbackLineariz\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_feedbackLineariz_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_feedbackLinearizInstanceStruct *chartInstance;
    chartInstance = (SFc2_feedbackLinearizInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_feedbackLinearizMachineNumber_,
           2,
           1,
           1,
           12,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_feedbackLinearizMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_feedbackLinearizMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_feedbackLinearizMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"qInit");
          _SFD_SET_DATA_PROPS(1,1,1,0,"q");
          _SFD_SET_DATA_PROPS(2,2,0,1,"qInitOut");
          _SFD_SET_DATA_PROPS(3,2,0,1,"tau");
          _SFD_SET_DATA_PROPS(4,1,1,0,"qD");
          _SFD_SET_DATA_PROPS(5,1,1,0,"g");
          _SFD_SET_DATA_PROPS(6,1,1,0,"gin");
          _SFD_SET_DATA_PROPS(7,2,0,1,"gOut");
          _SFD_SET_DATA_PROPS(8,1,1,0,"kp");
          _SFD_SET_DATA_PROPS(9,2,0,1,"e");
          _SFD_SET_DATA_PROPS(10,1,1,0,"M");
          _SFD_SET_DATA_PROPS(11,1,1,0,"h");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,193);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 25;
          dimVector[1]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 31;
          dimVector[1]= 31;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 31;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c2_qInit)[25];
          real_T (*c2_q)[25];
          real_T (*c2_qInitOut)[25];
          real_T (*c2_tau)[25];
          real_T (*c2_qD)[25];
          real_T (*c2_g)[25];
          real_T (*c2_gin)[25];
          real_T (*c2_gOut)[25];
          real_T (*c2_kp)[625];
          real_T (*c2_e)[25];
          real_T (*c2_M)[961];
          real_T (*c2_h)[31];
          c2_h = (real_T (*)[31])ssGetInputPortSignal(chartInstance->S, 7);
          c2_M = (real_T (*)[961])ssGetInputPortSignal(chartInstance->S, 6);
          c2_e = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 4);
          c2_kp = (real_T (*)[625])ssGetInputPortSignal(chartInstance->S, 5);
          c2_gOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 3);
          c2_gin = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 4);
          c2_g = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 3);
          c2_qD = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 2);
          c2_tau = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_qInitOut = (real_T (*)[25])ssGetOutputPortSignal(chartInstance->S,
            1);
          c2_q = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 1);
          c2_qInit = (real_T (*)[25])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_qInit);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_q);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_qInitOut);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_tau);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_qD);
          _SFD_SET_DATA_VALUE_PTR(5U, *c2_g);
          _SFD_SET_DATA_VALUE_PTR(6U, *c2_gin);
          _SFD_SET_DATA_VALUE_PTR(7U, *c2_gOut);
          _SFD_SET_DATA_VALUE_PTR(8U, *c2_kp);
          _SFD_SET_DATA_VALUE_PTR(9U, *c2_e);
          _SFD_SET_DATA_VALUE_PTR(10U, *c2_M);
          _SFD_SET_DATA_VALUE_PTR(11U, *c2_h);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_feedbackLinearizMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "sPiwndRT8x2DzhUlKaHSmH";
}

static void sf_opaque_initialize_c2_feedbackLineariz(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_feedbackLinearizInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
    chartInstanceVar);
  initialize_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_feedbackLineariz(void *chartInstanceVar)
{
  enable_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_feedbackLineariz(void *chartInstanceVar)
{
  disable_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_feedbackLineariz(void *chartInstanceVar)
{
  sf_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_feedbackLineariz(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_feedbackLineariz
    ((SFc2_feedbackLinearizInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_feedbackLineariz();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_feedbackLineariz(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_feedbackLineariz();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_feedbackLineariz(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_feedbackLineariz(S);
}

static void sf_opaque_set_sim_state_c2_feedbackLineariz(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_feedbackLineariz(S, st);
}

static void sf_opaque_terminate_c2_feedbackLineariz(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_feedbackLinearizInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_feedbackLineariz_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_feedbackLineariz(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_feedbackLineariz((SFc2_feedbackLinearizInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_feedbackLineariz(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_feedbackLineariz_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,4);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(76415841U));
  ssSetChecksum1(S,(3136247116U));
  ssSetChecksum2(S,(1548725650U));
  ssSetChecksum3(S,(732401458U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_feedbackLineariz(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_feedbackLineariz(SimStruct *S)
{
  SFc2_feedbackLinearizInstanceStruct *chartInstance;
  chartInstance = (SFc2_feedbackLinearizInstanceStruct *)malloc(sizeof
    (SFc2_feedbackLinearizInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_feedbackLinearizInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_feedbackLineariz;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_feedbackLineariz;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_feedbackLineariz;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_feedbackLineariz;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_feedbackLineariz;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_feedbackLineariz;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_feedbackLineariz;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_feedbackLineariz;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_feedbackLineariz;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_feedbackLineariz;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_feedbackLineariz;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_feedbackLineariz_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_feedbackLineariz(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_feedbackLineariz(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_feedbackLineariz(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_feedbackLineariz_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}