/* Include files */

#include "pv_test_sfun.h"
#include "c2_pv_test.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "pv_test_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[11] = { "Ppv", "deltaD", "nargin",
  "nargout", "Vpv", "Ipv", "D", "Dprev", "Pprev", "Vprev", "cnt" };

/* Function Declarations */
static void initialize_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void initialize_params_c2_pv_test(SFc2_pv_testInstanceStruct
  *chartInstance);
static void enable_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void disable_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_pv_test(SFc2_pv_testInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_pv_test(SFc2_pv_testInstanceStruct
  *chartInstance);
static void set_sim_state_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void sf_gateway_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void mdl_start_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void initSimStructsc2_pv_test(SFc2_pv_testInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_b_cnt, const char_T *c2_identifier, boolean_T *c2_svPtr);
static real_T c2_b_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
  *c2_svPtr);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_b_D, const char_T *c2_identifier);
static real_T c2_d_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static real_T c2_mod(SFc2_pv_testInstanceStruct *chartInstance, real_T c2_x,
                     real_T c2_y);
static void c2_scalarEg(SFc2_pv_testInstanceStruct *chartInstance);
static void c2_dimagree(SFc2_pv_testInstanceStruct *chartInstance);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_e_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_f_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_pv_test, const char_T *c2_identifier);
static uint8_T c2_g_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_pv_testInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_pv_testInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_pv_test(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_Dprev_not_empty = false;
  chartInstance->c2_Pprev_not_empty = false;
  chartInstance->c2_Vprev_not_empty = false;
  chartInstance->c2_cnt_not_empty = false;
  chartInstance->c2_is_active_c2_pv_test = 0U;
}

static void initialize_params_c2_pv_test(SFc2_pv_testInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_pv_test(SFc2_pv_testInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_pv_test(SFc2_pv_testInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_d_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_hoistedGlobal;
  real_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  uint8_T c2_f_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(6, 1), false);
  c2_hoistedGlobal = *chartInstance->c2_D;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_Dprev;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  if (!chartInstance->c2_cnt_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = chartInstance->c2_Pprev;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  if (!chartInstance->c2_cnt_not_empty) {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_d_hoistedGlobal = chartInstance->c2_Vprev;
  c2_d_u = c2_d_hoistedGlobal;
  c2_e_y = NULL;
  if (!chartInstance->c2_cnt_not_empty) {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_e_hoistedGlobal = chartInstance->c2_cnt;
  c2_e_u = c2_e_hoistedGlobal;
  c2_f_y = NULL;
  if (!chartInstance->c2_cnt_not_empty) {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_y, 4, c2_f_y);
  c2_f_hoistedGlobal = chartInstance->c2_is_active_c2_pv_test;
  c2_f_u = c2_f_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_D = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("D", c2_u, 0)), "D");
  chartInstance->c2_Dprev = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Dprev", c2_u, 1)), "Dprev",
    &chartInstance->c2_Dprev_not_empty);
  chartInstance->c2_Pprev = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Pprev", c2_u, 2)), "Pprev",
    &chartInstance->c2_Pprev_not_empty);
  chartInstance->c2_Vprev = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Vprev", c2_u, 3)), "Vprev",
    &chartInstance->c2_Vprev_not_empty);
  chartInstance->c2_cnt = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("cnt", c2_u, 4)), "cnt", &chartInstance->c2_cnt_not_empty);
  chartInstance->c2_is_active_c2_pv_test = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c2_pv_test", c2_u, 5)),
    "is_active_c2_pv_test");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_pv_test(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_Vpv;
  real_T c2_b_Ipv;
  uint32_T c2_debug_family_var_map[11];
  real_T c2_Ppv;
  real_T c2_deltaD;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_b_D;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Ipv, 1U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Vpv, 0U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_Vpv;
  c2_b_hoistedGlobal = *chartInstance->c2_Ipv;
  c2_b_Vpv = c2_hoistedGlobal;
  c2_b_Ipv = c2_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 11U, 11U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Ppv, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_deltaD, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_Vpv, 4U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_Ipv, 5U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_D, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_Dprev, 7U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_Pprev, 8U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_Vprev, 9U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_cnt, 10U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_Dprev_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
    chartInstance->c2_Dprev = 0.7;
    chartInstance->c2_Dprev_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
    chartInstance->c2_Vprev = 300.0;
    chartInstance->c2_Vprev_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
    chartInstance->c2_Pprev = 2000.0;
    chartInstance->c2_Pprev_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
    chartInstance->c2_cnt = 1.0;
    chartInstance->c2_cnt_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_Ppv = c2_b_Vpv * c2_b_Ipv;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  chartInstance->c2_cnt++;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 0, c2_mod(chartInstance,
         chartInstance->c2_cnt, 1000.0), 0.0, -1, 1U, c2_mod(chartInstance,
         chartInstance->c2_cnt, 1000.0) != 0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
    c2_b_D = chartInstance->c2_Dprev;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
    c2_deltaD = 0.0001;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
    if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 1, c2_Ppv,
          chartInstance->c2_Pprev, -1, 4U, c2_Ppv > chartInstance->c2_Pprev))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
      if (CV_EML_IF(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 2, c2_b_Vpv,
            chartInstance->c2_Vprev, -1, 4U, c2_b_Vpv > chartInstance->c2_Vprev)))
      {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
        c2_b_D = chartInstance->c2_Dprev - c2_deltaD;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
        c2_b_D = chartInstance->c2_Dprev + c2_deltaD;
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
      if (CV_EML_IF(0, 1, 4, CV_RELATIONAL_EVAL(4U, 0U, 3, c2_b_Vpv,
            chartInstance->c2_Vprev, -1, 4U, c2_b_Vpv > chartInstance->c2_Vprev)))
      {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
        c2_b_D = chartInstance->c2_Dprev + c2_deltaD;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
        c2_b_D = chartInstance->c2_Dprev - c2_deltaD;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
    if (CV_EML_IF(0, 1, 5, CV_RELATIONAL_EVAL(4U, 0U, 4, c2_b_D, 1.0, -1, 4U,
          c2_b_D > 1.0))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
      c2_b_D = 1.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
      if (CV_EML_IF(0, 1, 6, CV_RELATIONAL_EVAL(4U, 0U, 5, c2_b_D, 0.0, -1, 2U,
            c2_b_D < 0.0))) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
        c2_b_D = 0.0;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
    chartInstance->c2_Dprev = c2_b_D;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
    chartInstance->c2_Pprev = c2_Ppv;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
    chartInstance->c2_Vprev = c2_b_Vpv;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -51);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c2_D = c2_b_D;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_pv_testMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_D, 2U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
}

static void mdl_start_c2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc2_pv_test(SFc2_pv_testInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_cnt_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_b_cnt, const char_T *c2_identifier, boolean_T *c2_svPtr)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_cnt), &c2_thisId,
    c2_svPtr);
  sf_mex_destroy(&c2_b_cnt);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
  *c2_svPtr)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  if (mxIsEmpty(c2_u)) {
    *c2_svPtr = false;
  } else {
    *c2_svPtr = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d0;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_cnt;
  const char_T *c2_identifier;
  boolean_T *c2_svPtr;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)chartInstanceVoid;
  c2_b_cnt = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_svPtr = &chartInstance->c2_cnt_not_empty;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_cnt), &c2_thisId,
    c2_svPtr);
  sf_mex_destroy(&c2_b_cnt);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_b_D, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_D), &c2_thisId);
  sf_mex_destroy(&c2_b_D);
  return c2_y;
}

static real_T c2_d_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d1;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d1;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_D;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)chartInstanceVoid;
  c2_b_D = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_D), &c2_thisId);
  sf_mex_destroy(&c2_b_D);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_pv_test_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static real_T c2_mod(SFc2_pv_testInstanceStruct *chartInstance, real_T c2_x,
                     real_T c2_y)
{
  real_T c2_r;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_c_x;
  real_T c2_c_y;
  real_T c2_d_x;
  real_T c2_d_y;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_e_y;
  real_T c2_l_x;
  real_T c2_f_y;
  real_T c2_m_x;
  real_T c2_n_x;
  (void)chartInstance;
  c2_b_x = c2_x;
  c2_b_y = c2_y;
  c2_c_x = c2_b_x;
  c2_c_y = c2_b_y;
  c2_d_x = c2_c_x;
  c2_d_y = c2_c_y;
  if (c2_d_y == 0.0) {
    c2_r = c2_d_x;
  } else {
    c2_e_x = c2_d_y;
    c2_f_x = c2_e_x;
    c2_f_x = muDoubleScalarFloor(c2_f_x);
    if (c2_d_y == c2_f_x) {
      c2_g_x = c2_d_x / c2_d_y;
      c2_i_x = c2_g_x;
      c2_i_x = muDoubleScalarFloor(c2_i_x);
      c2_r = c2_d_x - c2_i_x * c2_d_y;
    } else {
      c2_r = c2_d_x / c2_d_y;
      c2_h_x = c2_r;
      c2_j_x = c2_h_x;
      c2_j_x = muDoubleScalarRound(c2_j_x);
      c2_k_x = c2_r - c2_j_x;
      c2_e_y = muDoubleScalarAbs(c2_k_x);
      c2_l_x = c2_r;
      c2_f_y = muDoubleScalarAbs(c2_l_x);
      if (c2_e_y <= 2.2204460492503131E-16 * c2_f_y) {
        c2_r = 0.0;
      } else {
        c2_m_x = c2_r;
        c2_n_x = c2_m_x;
        c2_n_x = muDoubleScalarFloor(c2_n_x);
        c2_r = (c2_r - c2_n_x) * c2_d_y;
      }
    }
  }

  return c2_r;
}

static void c2_scalarEg(SFc2_pv_testInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_dimagree(SFc2_pv_testInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_e_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i0, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i0;
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
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_pv_test, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_pv_test), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_pv_test);
  return c2_y;
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_pv_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_pv_testInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_pv_testInstanceStruct *chartInstance)
{
  chartInstance->c2_Vpv = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_D = (real_T *)ssGetOutputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c2_Ipv = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_pv_test_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3509033582U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2137178964U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1283182078U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3859808931U);
}

mxArray* sf_c2_pv_test_get_post_codegen_info(void);
mxArray *sf_c2_pv_test_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("6rb96VhxBkDlQ8y9NdndLG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_pv_test_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_pv_test_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_pv_test_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_pv_test_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_pv_test_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_pv_test(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[5],T\"D\",},{M[4],M[0],T\"Dprev\",S'l','i','p'{{M1x2[49 54],M[0],}}},{M[4],M[0],T\"Pprev\",S'l','i','p'{{M1x2[55 60],M[0],}}},{M[4],M[0],T\"Vprev\",S'l','i','p'{{M1x2[61 66],M[0],}}},{M[4],M[0],T\"cnt\",S'l','i','p'{{M1x2[67 70],M[0],}}},{M[8],M[0],T\"is_active_c2_pv_test\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_pv_test_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_pv_testInstanceStruct *chartInstance = (SFc2_pv_testInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _pv_testMachineNumber_,
           2,
           1,
           1,
           0,
           3,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_pv_testMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_pv_testMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _pv_testMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Vpv");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Ipv");
          _SFD_SET_DATA_PROPS(2,2,0,1,"D");
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
        _SFD_CV_INIT_EML(0,1,1,0,7,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,692);
        _SFD_CV_INIT_EML_IF(0,1,0,96,113,-1,185);
        _SFD_CV_INIT_EML_IF(0,1,1,291,310,382,587);
        _SFD_CV_INIT_EML_IF(0,1,2,382,397,488,587);
        _SFD_CV_INIT_EML_IF(0,1,3,402,414,447,487);
        _SFD_CV_INIT_EML_IF(0,1,4,497,509,542,582);
        _SFD_CV_INIT_EML_IF(0,1,5,589,595,608,646);
        _SFD_CV_INIT_EML_IF(0,1,6,613,619,-1,642);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,294,310,-1,1);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,386,397,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,405,414,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,500,509,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,592,595,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,5,616,619,-1,2);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _pv_testMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_pv_testInstanceStruct *chartInstance = (SFc2_pv_testInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c2_Vpv);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_D);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_Ipv);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "slAzXmd8ZhRVazlCcmcqQ2C";
}

static void sf_opaque_initialize_c2_pv_test(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_pv_testInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
  initialize_c2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_pv_test(void *chartInstanceVar)
{
  enable_c2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_pv_test(void *chartInstanceVar)
{
  disable_c2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_pv_test(void *chartInstanceVar)
{
  sf_gateway_c2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_pv_test(SimStruct* S)
{
  return get_sim_state_c2_pv_test((SFc2_pv_testInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_pv_test(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_pv_test((SFc2_pv_testInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_pv_test(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_pv_testInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_pv_test_optimization_info();
    }

    finalize_c2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_pv_test((SFc2_pv_testInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_pv_test(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_pv_test((SFc2_pv_testInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_pv_test(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_pv_test_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2472026033U));
  ssSetChecksum1(S,(3044136837U));
  ssSetChecksum2(S,(2218064789U));
  ssSetChecksum3(S,(4210939306U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_pv_test(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_pv_test(SimStruct *S)
{
  SFc2_pv_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_pv_testInstanceStruct *)utMalloc(sizeof
    (SFc2_pv_testInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_pv_testInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_pv_test;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_pv_test;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_pv_test;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_pv_test;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_pv_test;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_pv_test;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_pv_test;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_pv_test;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_pv_test;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_pv_test;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_pv_test;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_pv_test(chartInstance);
}

void c2_pv_test_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_pv_test(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_pv_test(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_pv_test(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_pv_test_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
