/* Include files */

#include "MMC_Control_PLECS_Isolated_Full_Bridge_sfun.h"
#include "c2_MMC_Control_PLECS_Isolated_Full_Bridge.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "MMC_Control_PLECS_Isolated_Full_Bridge_sfun_debug_macros.h"
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
static const char * c2_debug_family_names[39] = { "Vpv", "Ipv", "Vg_peak",
  "Nstate", "Nout", "sin_1", "sin_2", "sin_3", "phi_1", "phi_2", "phi_3",
  "tstep", "xnom", "K", "Ki", "Kp", "tcy", "D0", "yd", "y", "state", "err",
  "err_int", "dD", "D", "nargin", "nargout", "x", "Vg_meas", "trigger", "nom",
  "D_out", "Iin", "phi", "D_out_val", "err_int_val", "phi_val", "K13_flag",
  "K12_flag" };

/* Function Declarations */
static void initialize_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void initialize_params_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void enable_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void disable_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_MMC_Control_PLECS_Isolated_Full_Brid
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void set_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_st);
static void finalize_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void sf_gateway_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void mdl_start_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_chartstep_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void initSimStructsc2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_K12_flag, const char_T *c2_identifier, boolean_T
   *c2_svPtr);
static real_T c2_b_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
   *c2_svPtr);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_err_int_val, const char_T *c2_identifier, boolean_T
   *c2_svPtr, real_T c2_b_y[5]);
static void c2_d_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
   *c2_svPtr, real_T c2_b_y[5]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_D_out_val, const char_T *c2_identifier, boolean_T
   *c2_svPtr, real_T c2_b_y[6]);
static void c2_f_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
   *c2_svPtr, real_T c2_b_y[6]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_g_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_phi, const char_T *c2_identifier);
static real_T c2_h_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_Iin, const char_T *c2_identifier, real_T c2_b_y[3]);
static void c2_j_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[3]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_k_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_D_out, const char_T *c2_identifier, real_T c2_b_y[6]);
static void c2_l_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[6]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_m_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId,
   c2_struct_Ifc6eQ84AsHC0d7m6W5OFB *c2_b_y);
static void c2_n_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [36000]);
static void c2_o_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [396000]);
static void c2_p_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [6000]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_q_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [66]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_r_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[5]);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_s_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [36]);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_t_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [30]);
static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_u_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [66]);
static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static real_T c2_asin(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T c2_b_x);
static void c2_error(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
                     *chartInstance);
static real_T c2_interp1
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   real_T c2_varargin_1[6000], real_T c2_varargin_2[6000], real_T c2_varargin_3);
static void c2_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_StringToMethodID
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_b_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static boolean_T c2_isnan
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   real_T c2_b_x);
static void c2_b_error(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
  *chartInstance);
static void c2_c_error(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
  *chartInstance);
static real_T c2_ceil(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T c2_b_x);
static void c2_c_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_d_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_e_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_f_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void c2_dimagree
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_v_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_w_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge,
   const char_T *c2_identifier);
static uint8_T c2_x_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_asin(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T *c2_b_x);
static void c2_b_ceil(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T *c2_b_x);
static void init_dsm_address_info
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);
static void init_simulink_io_address
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_MMC_Control_PLECS_Isolated_Full_Bridge(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_D_out_val_not_empty = false;
  chartInstance->c2_err_int_val_not_empty = false;
  chartInstance->c2_phi_val_not_empty = false;
  chartInstance->c2_K13_flag_not_empty = false;
  chartInstance->c2_K12_flag_not_empty = false;
  chartInstance->c2_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge = 0U;
}

static void initialize_params_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  const mxArray *c2_m0 = NULL;
  const mxArray *c2_mxField;
  c2_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  c2_mxField = sf_mex_getfield(c2_m0, "D", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.D, 1,
                      0, 0U, 1, 0U, 2, 6000, 6);
  c2_mxField = sf_mex_getfield(c2_m0, "K", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.K, 1,
                      0, 0U, 1, 0U, 3, 6000, 6, 11);
  c2_mxField = sf_mex_getfield(c2_m0, "K12", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.K12, 1,
                      0, 0U, 1, 0U, 3, 6000, 6, 11);
  c2_mxField = sf_mex_getfield(c2_m0, "K13", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.K13, 1,
                      0, 0U, 1, 0U, 3, 6000, 6, 11);
  c2_mxField = sf_mex_getfield(c2_m0, "phi", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.phi, 1,
                      0, 0U, 1, 0U, 2, 1, 6000);
  c2_mxField = sf_mex_getfield(c2_m0, "id", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.id, 1,
                      0, 0U, 1, 0U, 2, 1, 6000);
  c2_mxField = sf_mex_getfield(c2_m0, "x", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), chartInstance->c2_r0.x, 1,
                      0, 0U, 1, 0U, 2, 6000, 6);
  c2_mxField = sf_mex_getfield(c2_m0, "fsw", "nom", 0);
  sf_mex_import_named("nom", sf_mex_dup(c2_mxField), &chartInstance->c2_r0.fsw,
                      1, 0, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_m0);
  chartInstance->c2_nom = chartInstance->c2_r0;
}

static void enable_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_MMC_Control_PLECS_Isolated_Full_Brid
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_b_y = NULL;
  const mxArray *c2_c_y = NULL;
  const mxArray *c2_d_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  const mxArray *c2_f_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_e_u;
  const mxArray *c2_g_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_f_u;
  const mxArray *c2_h_y = NULL;
  const mxArray *c2_i_y = NULL;
  real_T c2_d_hoistedGlobal;
  real_T c2_g_u;
  const mxArray *c2_j_y = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_h_u;
  const mxArray *c2_k_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createcellmatrix(9, 1), false);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", *chartInstance->c2_D_out, 0, 0U, 1U,
    0U, 1, 6), false);
  sf_mex_setcell(c2_b_y, 0, c2_c_y);
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", *chartInstance->c2_Iin, 0, 0U, 1U,
    0U, 1, 3), false);
  sf_mex_setcell(c2_b_y, 1, c2_d_y);
  c2_hoistedGlobal = *chartInstance->c2_phi;
  c2_d_u = c2_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_b_y, 2, c2_e_y);
  c2_f_y = NULL;
  if (!chartInstance->c2_D_out_val_not_empty) {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", chartInstance->c2_D_out_val, 0, 0U,
      1U, 0U, 1, 6), false);
  }

  sf_mex_setcell(c2_b_y, 3, c2_f_y);
  c2_b_hoistedGlobal = chartInstance->c2_K12_flag;
  c2_e_u = c2_b_hoistedGlobal;
  c2_g_y = NULL;
  if (!chartInstance->c2_K12_flag_not_empty) {
    sf_mex_assign(&c2_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_b_y, 4, c2_g_y);
  c2_c_hoistedGlobal = chartInstance->c2_K13_flag;
  c2_f_u = c2_c_hoistedGlobal;
  c2_h_y = NULL;
  if (!chartInstance->c2_K12_flag_not_empty) {
    sf_mex_assign(&c2_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_f_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_b_y, 5, c2_h_y);
  c2_i_y = NULL;
  if (!chartInstance->c2_err_int_val_not_empty) {
    sf_mex_assign(&c2_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_i_y, sf_mex_create("y", chartInstance->c2_err_int_val, 0,
      0U, 1U, 0U, 1, 5), false);
  }

  sf_mex_setcell(c2_b_y, 6, c2_i_y);
  c2_d_hoistedGlobal = chartInstance->c2_phi_val;
  c2_g_u = c2_d_hoistedGlobal;
  c2_j_y = NULL;
  if (!chartInstance->c2_K12_flag_not_empty) {
    sf_mex_assign(&c2_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_g_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_b_y, 7, c2_j_y);
  c2_e_hoistedGlobal =
    chartInstance->c2_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  c2_h_u = c2_e_hoistedGlobal;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_h_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_b_y, 8, c2_k_y);
  sf_mex_assign(&c2_st, c2_b_y, false);
  return c2_st;
}

static void set_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_st)
{
  const mxArray *c2_d_u;
  real_T c2_dv0[6];
  int32_T c2_i0;
  real_T c2_dv1[3];
  int32_T c2_i1;
  real_T c2_dv2[6];
  int32_T c2_i2;
  real_T c2_dv3[5];
  int32_T c2_i3;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_d_u = sf_mex_dup(c2_st);
  c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("D_out", c2_d_u,
    0)), "D_out", c2_dv0);
  for (c2_i0 = 0; c2_i0 < 6; c2_i0++) {
    (*chartInstance->c2_D_out)[c2_i0] = c2_dv0[c2_i0];
  }

  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("Iin", c2_d_u,
    1)), "Iin", c2_dv1);
  for (c2_i1 = 0; c2_i1 < 3; c2_i1++) {
    (*chartInstance->c2_Iin)[c2_i1] = c2_dv1[c2_i1];
  }

  *chartInstance->c2_phi = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("phi", c2_d_u, 2)), "phi");
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("D_out_val",
    c2_d_u, 3)), "D_out_val", &chartInstance->c2_D_out_val_not_empty, c2_dv2);
  for (c2_i2 = 0; c2_i2 < 6; c2_i2++) {
    chartInstance->c2_D_out_val[c2_i2] = c2_dv2[c2_i2];
  }

  chartInstance->c2_K12_flag = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("K12_flag", c2_d_u, 4)), "K12_flag",
    &chartInstance->c2_K12_flag_not_empty);
  chartInstance->c2_K13_flag = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("K13_flag", c2_d_u, 5)), "K13_flag",
    &chartInstance->c2_K13_flag_not_empty);
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("err_int_val",
    c2_d_u, 6)), "err_int_val", &chartInstance->c2_err_int_val_not_empty, c2_dv3);
  for (c2_i3 = 0; c2_i3 < 5; c2_i3++) {
    chartInstance->c2_err_int_val[c2_i3] = c2_dv3[c2_i3];
  }

  chartInstance->c2_phi_val = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("phi_val", c2_d_u, 7)), "phi_val",
    &chartInstance->c2_phi_val_not_empty);
  chartInstance->c2_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge =
    c2_w_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge", c2_d_u, 8)),
    "is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge");
  sf_mex_destroy(&c2_d_u);
  c2_update_debugger_state_c2_MMC_Control_PLECS_Isolated_Full_Brid(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_trigger, 2U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  for (c2_i4 = 0; c2_i4 < 3; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Vg_meas)[c2_i4], 1U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i5 = 0; c2_i5 < 6; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_x)[c2_i5], 0U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_MMC_Control_PLECS_Isolated_Full_Bridge(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_MMC_Control_PLECS_Isolated_Full_BridgeMachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i6 = 0; c2_i6 < 6; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_D_out)[c2_i6], 3U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i7 = 0; c2_i7 < 3; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Iin)[c2_i7], 4U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_phi, 5U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
}

static void mdl_start_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  int32_T c2_i8;
  int32_T c2_i9;
  real_T c2_b_x[6];
  real_T c2_b_trigger;
  real_T c2_b_Vg_meas[3];
  uint32_T c2_debug_family_var_map[39];
  real_T c2_Vpv;
  real_T c2_Ipv;
  real_T c2_Vg_peak;
  real_T c2_Nstate;
  real_T c2_Nout;
  real_T c2_sin_1;
  real_T c2_sin_2;
  real_T c2_sin_3;
  real_T c2_phi_1;
  real_T c2_phi_2;
  real_T c2_phi_3;
  real_T c2_tstep;
  real_T c2_xnom[6];
  real_T c2_K[66];
  real_T c2_Ki[30];
  real_T c2_Kp[36];
  real_T c2_tcy;
  real_T c2_D0[6];
  real_T c2_yd[5];
  real_T c2_b_y[5];
  real_T c2_state[6];
  real_T c2_err[5];
  real_T c2_err_int[5];
  real_T c2_dD[6];
  real_T c2_D[6];
  real_T c2_b_K[66];
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 3.0;
  real_T c2_b_D_out[6];
  real_T c2_b_Iin[3];
  real_T c2_b_phi;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  real_T c2_A;
  real_T c2_c_x;
  int32_T c2_i13;
  real_T c2_d_x;
  int32_T c2_i14;
  real_T c2_b_A;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_c_A;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_d0;
  int32_T c2_i15;
  int32_T c2_i16;
  real_T c2_c_nom[6000];
  real_T c2_d_nom[6000];
  int32_T c2_b_tstep;
  int32_T c2_i17;
  int32_T c2_c_tstep;
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_k;
  real_T c2_i_x[66];
  int32_T c2_b_k;
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  real_T c2_B;
  real_T c2_c_y;
  real_T c2_d_y;
  int32_T c2_d_tstep;
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  static int32_T c2_iv0[5] = { 0, 1, 2, 3, 5 };

  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  real_T c2_b;
  real_T c2_a[5];
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  real_T c2_b_a[36];
  int32_T c2_i39;
  real_T c2_b_b[6];
  int32_T c2_i40;
  real_T c2_e_y[6];
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  real_T c2_c_a[30];
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_c_k;
  int32_T c2_d_k;
  int32_T c2_e_k;
  real_T c2_xk;
  real_T c2_j_x;
  int32_T c2_f_k;
  real_T c2_extremum;
  int32_T c2_i50;
  real_T c2_b_xk;
  real_T c2_k_x;
  real_T c2_b_extremum;
  int32_T c2_i51;
  int32_T c2_i52;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_trigger;
  for (c2_i8 = 0; c2_i8 < 6; c2_i8++) {
    c2_b_x[c2_i8] = (*chartInstance->c2_x)[c2_i8];
  }

  for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
    c2_b_Vg_meas[c2_i9] = (*chartInstance->c2_Vg_meas)[c2_i9];
  }

  c2_b_trigger = c2_hoistedGlobal;
  chartInstance->c2_b_nom = chartInstance->c2_nom;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 39U, 40U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Vpv, 0U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Ipv, 1U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Vg_peak, 2U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nstate, 3U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nout, 4U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_sin_1, 5U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_sin_2, 6U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_sin_3, 7U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi_1, 8U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi_2, 9U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi_3, 10U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_tstep, 11U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xnom, 12U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_K, MAX_uint32_T, c2_l_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Ki, 14U, c2_k_sf_marshallOut,
    c2_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Kp, 15U, c2_j_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_tcy, 16U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_D0, 17U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_yd, 18U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_y, 19U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_state, 20U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_err, 21U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_err_int, 22U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dD, 23U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_D, 24U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_K, MAX_uint32_T, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 25U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 26U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_x, 27U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_Vg_meas, 28U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_trigger, 29U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_b_nom, 30U,
    c2_g_sf_marshallOut, c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_D_out, 31U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_Iin, 32U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_phi, 33U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_D_out_val, 34U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_err_int_val, 35U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_phi_val, 36U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_K13_flag, 37U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_K12_flag, 38U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_D_out_val_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
    chartInstance->c2_phi_val = 0.0;
    chartInstance->c2_phi_val_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
    for (c2_i10 = 0; c2_i10 < 6; c2_i10++) {
      chartInstance->c2_D_out_val[c2_i10] = 0.5;
    }

    chartInstance->c2_D_out_val_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
    for (c2_i11 = 0; c2_i11 < 5; c2_i11++) {
      chartInstance->c2_err_int_val[c2_i11] = 0.0;
    }

    chartInstance->c2_err_int_val_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
    chartInstance->c2_K13_flag = 1.0;
    chartInstance->c2_K13_flag_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
    chartInstance->c2_K12_flag = 0.0;
    chartInstance->c2_K12_flag_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_Vpv = 50.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_Ipv = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
  c2_b_Iin[0] = c2_Ipv;
  c2_b_Iin[1] = c2_Ipv;
  c2_b_Iin[2] = c2_Ipv;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  if (CV_EML_IF(0, 1, 1, c2_b_trigger != 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
    c2_Vg_peak = 40.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
    c2_Nstate = 6.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
    c2_Nout = 5.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
    c2_A = c2_b_Vg_meas[0];
    c2_c_x = c2_A;
    c2_d_x = c2_c_x;
    c2_sin_1 = c2_d_x / 40.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
    c2_b_A = c2_b_Vg_meas[1];
    c2_e_x = c2_b_A;
    c2_f_x = c2_e_x;
    c2_sin_2 = c2_f_x / 40.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
    c2_c_A = c2_b_Vg_meas[2];
    c2_g_x = c2_c_A;
    c2_h_x = c2_g_x;
    c2_sin_3 = c2_h_x / 40.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
    c2_d0 = c2_sin_1;
    c2_b_asin(chartInstance, &c2_d0);
    c2_phi_1 = c2_d0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
    c2_d0 = c2_sin_2;
    c2_b_asin(chartInstance, &c2_d0);
    c2_phi_2 = c2_d0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
    c2_d0 = c2_sin_3;
    c2_b_asin(chartInstance, &c2_d0);
    c2_phi_3 = c2_d0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
    guard2 = false;
    if (CV_EML_COND(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c2_sin_1, 0.0, -1, 5U,
          c2_sin_1 >= 0.0))) {
      if (CV_EML_COND(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 1, c2_sin_2, c2_sin_3,
            -1, 5U, c2_sin_2 >= c2_sin_3))) {
        CV_EML_MCDC(0, 1, 0, true);
        CV_EML_IF(0, 1, 2, true);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
        c2_phi_1 = 3.1415926535897931 - c2_phi_1;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2 == true) {
      CV_EML_MCDC(0, 1, 0, false);
      CV_EML_IF(0, 1, 2, false);
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
    guard1 = false;
    if (CV_EML_COND(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 2, c2_sin_1, 0.0, -1, 3U,
          c2_sin_1 <= 0.0))) {
      if (CV_EML_COND(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 3, c2_sin_2, c2_sin_3,
            -1, 5U, c2_sin_2 >= c2_sin_3))) {
        CV_EML_MCDC(0, 1, 1, true);
        CV_EML_IF(0, 1, 3, true);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
        c2_phi_1 = 3.1415926535897931 - c2_phi_1;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 == true) {
      CV_EML_MCDC(0, 1, 1, false);
      CV_EML_IF(0, 1, 3, false);
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
    if (CV_EML_IF(0, 1, 4, CV_RELATIONAL_EVAL(4U, 0U, 4, c2_phi_1, 0.0, -1, 2U,
          c2_phi_1 < 0.0))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
      c2_phi_1 += 6.2831853071795862;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
    c2_b_phi = c2_phi_1;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
    for (c2_i15 = 0; c2_i15 < 6000; c2_i15++) {
      c2_c_nom[c2_i15] = chartInstance->c2_b_nom.phi[c2_i15];
    }

    for (c2_i16 = 0; c2_i16 < 6000; c2_i16++) {
      c2_d_nom[c2_i16] = chartInstance->c2_b_nom.id[c2_i16];
    }

    c2_d0 = c2_interp1(chartInstance, c2_c_nom, c2_d_nom, c2_b_phi);
    c2_b_ceil(chartInstance, &c2_d0);
    c2_tstep = c2_d0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 57);
    c2_b_tstep = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 1051, 5, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 1051U, 5U, c2_tstep), 1, 6000) - 1;
    for (c2_i17 = 0; c2_i17 < 6; c2_i17++) {
      c2_xnom[c2_i17] = chartInstance->c2_b_nom.x[c2_b_tstep + 6000 * c2_i17];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
    c2_c_tstep = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 1077, 5, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 1077U, 5U, c2_tstep), 1, 6000) - 1;
    for (c2_i18 = 0; c2_i18 < 11; c2_i18++) {
      for (c2_i19 = 0; c2_i19 < 6; c2_i19++) {
        c2_K[c2_i19 + 6 * c2_i18] = chartInstance->c2_b_nom.K[(c2_c_tstep + 6000
          * c2_i19) + 36000 * c2_i18];
      }
    }

    _SFD_SYMBOL_SWITCH(13U, 13U);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 59);
    for (c2_i20 = 0; c2_i20 < 66; c2_i20++) {
      c2_i_x[c2_i20] = c2_K[c2_i20];
    }

    for (c2_k = 1; c2_k < 67; c2_k++) {
      c2_b_k = c2_k - 1;
      c2_b_K[c2_b_k] = c2_i_x[c2_b_k];
    }

    _SFD_SYMBOL_SWITCH(13U, 25U);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 60);
    c2_i21 = 0;
    for (c2_i22 = 0; c2_i22 < 5; c2_i22++) {
      for (c2_i23 = 0; c2_i23 < 6; c2_i23++) {
        c2_Ki[c2_i23 + c2_i21] = c2_b_K[c2_i23 + c2_i21];
      }

      c2_i21 += 6;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 61);
    c2_i24 = 0;
    for (c2_i25 = 0; c2_i25 < 6; c2_i25++) {
      for (c2_i26 = 0; c2_i26 < 6; c2_i26++) {
        c2_Kp[c2_i26 + c2_i24] = c2_b_K[(c2_i26 + c2_i24) + 30];
      }

      c2_i24 += 6;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 62);
    c2_B = chartInstance->c2_b_nom.fsw;
    c2_c_y = c2_B;
    c2_d_y = c2_c_y;
    c2_tcy = 1.0 / c2_d_y;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
    c2_d_tstep = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 1220, 5, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 1220U, 5U, c2_tstep), 1, 6000) - 1;
    for (c2_i27 = 0; c2_i27 < 6; c2_i27++) {
      c2_D0[c2_i27] = chartInstance->c2_b_nom.D[c2_d_tstep + 6000 * c2_i27];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
    if (CV_EML_IF(0, 1, 5, chartInstance->c2_K13_flag != 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 67);
      for (c2_i29 = 0; c2_i29 < 5; c2_i29++) {
        c2_yd[c2_i29] = c2_xnom[c2_iv0[c2_i29]];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 68);
      for (c2_i31 = 0; c2_i31 < 5; c2_i31++) {
        c2_b_y[c2_i31] = c2_b_x[c2_iv0[c2_i31]];
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 70);
      for (c2_i28 = 0; c2_i28 < 5; c2_i28++) {
        c2_yd[c2_i28] = c2_xnom[c2_i28];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
      for (c2_i30 = 0; c2_i30 < 5; c2_i30++) {
        c2_b_y[c2_i30] = c2_b_x[c2_i30];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
    for (c2_i32 = 0; c2_i32 < 6; c2_i32++) {
      c2_state[c2_i32] = c2_b_x[c2_i32] - c2_xnom[c2_i32];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
    for (c2_i33 = 0; c2_i33 < 5; c2_i33++) {
      c2_err[c2_i33] = c2_yd[c2_i33] - c2_b_y[c2_i33];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
    for (c2_i34 = 0; c2_i34 < 5; c2_i34++) {
      c2_a[c2_i34] = c2_err[c2_i34];
    }

    c2_b = c2_tcy;
    for (c2_i35 = 0; c2_i35 < 5; c2_i35++) {
      c2_a[c2_i35] *= c2_b;
    }

    for (c2_i36 = 0; c2_i36 < 5; c2_i36++) {
      c2_err_int[c2_i36] = c2_a[c2_i36] + chartInstance->c2_err_int_val[c2_i36];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
    for (c2_i37 = 0; c2_i37 < 36; c2_i37++) {
      c2_b_a[c2_i37] = -c2_Kp[c2_i37];
    }

    for (c2_i38 = 0; c2_i38 < 6; c2_i38++) {
      c2_b_b[c2_i38] = c2_state[c2_i38];
    }

    for (c2_i39 = 0; c2_i39 < 6; c2_i39++) {
      c2_e_y[c2_i39] = 0.0;
      c2_i41 = 0;
      for (c2_i42 = 0; c2_i42 < 6; c2_i42++) {
        c2_e_y[c2_i39] += c2_b_a[c2_i41 + c2_i39] * c2_b_b[c2_i42];
        c2_i41 += 6;
      }
    }

    for (c2_i40 = 0; c2_i40 < 30; c2_i40++) {
      c2_c_a[c2_i40] = c2_Ki[c2_i40];
    }

    for (c2_i43 = 0; c2_i43 < 5; c2_i43++) {
      c2_a[c2_i43] = c2_err_int[c2_i43];
    }

    for (c2_i44 = 0; c2_i44 < 6; c2_i44++) {
      c2_b_b[c2_i44] = 0.0;
      c2_i46 = 0;
      for (c2_i47 = 0; c2_i47 < 5; c2_i47++) {
        c2_b_b[c2_i44] += c2_c_a[c2_i46 + c2_i44] * c2_a[c2_i47];
        c2_i46 += 6;
      }
    }

    for (c2_i45 = 0; c2_i45 < 6; c2_i45++) {
      c2_dD[c2_i45] = c2_e_y[c2_i45] - c2_b_b[c2_i45];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
    for (c2_i48 = 0; c2_i48 < 6; c2_i48++) {
      c2_D[c2_i48] = c2_D0[c2_i48] + c2_dD[c2_i48];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
    for (c2_i49 = 0; c2_i49 < 6; c2_i49++) {
      c2_b_b[c2_i49] = c2_D[c2_i49];
    }

    for (c2_c_k = 1; c2_c_k < 7; c2_c_k++) {
      c2_e_k = c2_c_k - 1;
      c2_xk = c2_b_b[c2_e_k];
      c2_j_x = c2_xk;
      c2_extremum = muDoubleScalarMin(c2_j_x, 0.999);
      c2_e_y[c2_e_k] = c2_extremum;
    }

    for (c2_d_k = 1; c2_d_k < 7; c2_d_k++) {
      c2_f_k = c2_d_k - 1;
      c2_b_xk = c2_e_y[c2_f_k];
      c2_k_x = c2_b_xk;
      c2_b_extremum = muDoubleScalarMax(c2_k_x, -0.999);
      c2_D[c2_f_k] = c2_b_extremum;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
    for (c2_i50 = 0; c2_i50 < 6; c2_i50++) {
      c2_b_D_out[c2_i50] = c2_D[c2_i50];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
    for (c2_i51 = 0; c2_i51 < 6; c2_i51++) {
      chartInstance->c2_D_out_val[c2_i51] = c2_D[c2_i51];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
    for (c2_i52 = 0; c2_i52 < 5; c2_i52++) {
      chartInstance->c2_err_int_val[c2_i52] = c2_err_int[c2_i52];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
    chartInstance->c2_phi_val = c2_b_phi;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
    c2_b_phi = chartInstance->c2_phi_val;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
    for (c2_i12 = 0; c2_i12 < 6; c2_i12++) {
      c2_b_D_out[c2_i12] = chartInstance->c2_D_out_val[c2_i12];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -95);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i13 = 0; c2_i13 < 6; c2_i13++) {
    (*chartInstance->c2_D_out)[c2_i13] = c2_b_D_out[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 3; c2_i14++) {
    (*chartInstance->c2_Iin)[c2_i14] = c2_b_Iin[c2_i14];
  }

  *chartInstance->c2_phi = c2_b_phi;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
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
  real_T c2_d_u;
  const mxArray *c2_b_y = NULL;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_d_u = *(real_T *)c2_inData;
  c2_b_y = NULL;
  if (!chartInstance->c2_K12_flag_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_K12_flag, const char_T *c2_identifier, boolean_T
   *c2_svPtr)
{
  real_T c2_b_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_K12_flag),
    &c2_thisId, c2_svPtr);
  sf_mex_destroy(&c2_b_K12_flag);
  return c2_b_y;
}

static real_T c2_b_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
   *c2_svPtr)
{
  real_T c2_b_y;
  real_T c2_d1;
  (void)chartInstance;
  if (mxIsEmpty(c2_d_u)) {
    *c2_svPtr = false;
  } else {
    *c2_svPtr = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
    c2_b_y = c2_d1;
  }

  sf_mex_destroy(&c2_d_u);
  return c2_b_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_K12_flag;
  const char_T *c2_identifier;
  boolean_T *c2_svPtr;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_K12_flag = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_svPtr = &chartInstance->c2_K12_flag_not_empty;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_K12_flag),
    &c2_thisId, c2_svPtr);
  sf_mex_destroy(&c2_b_K12_flag);
  *(real_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i53;
  const mxArray *c2_b_y = NULL;
  real_T c2_d_u[5];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i53 = 0; c2_i53 < 5; c2_i53++) {
    c2_d_u[c2_i53] = (*(real_T (*)[5])c2_inData)[c2_i53];
  }

  c2_b_y = NULL;
  if (!chartInstance->c2_err_int_val_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 5),
                  false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_err_int_val, const char_T *c2_identifier, boolean_T
   *c2_svPtr, real_T c2_b_y[5])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_err_int_val), &c2_thisId,
                        c2_svPtr, c2_b_y);
  sf_mex_destroy(&c2_b_err_int_val);
}

static void c2_d_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
   *c2_svPtr, real_T c2_b_y[5])
{
  real_T c2_dv4[5];
  int32_T c2_i54;
  (void)chartInstance;
  if (mxIsEmpty(c2_d_u)) {
    *c2_svPtr = false;
  } else {
    *c2_svPtr = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv4, 1, 0, 0U, 1, 0U, 1, 5);
    for (c2_i54 = 0; c2_i54 < 5; c2_i54++) {
      c2_b_y[c2_i54] = c2_dv4[c2_i54];
    }
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_err_int_val;
  const char_T *c2_identifier;
  boolean_T *c2_svPtr;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[5];
  int32_T c2_i55;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_err_int_val = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_svPtr = &chartInstance->c2_err_int_val_not_empty;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_err_int_val), &c2_thisId,
                        c2_svPtr, c2_b_y);
  sf_mex_destroy(&c2_b_err_int_val);
  for (c2_i55 = 0; c2_i55 < 5; c2_i55++) {
    (*(real_T (*)[5])c2_outData)[c2_i55] = c2_b_y[c2_i55];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i56;
  const mxArray *c2_b_y = NULL;
  real_T c2_d_u[6];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i56 = 0; c2_i56 < 6; c2_i56++) {
    c2_d_u[c2_i56] = (*(real_T (*)[6])c2_inData)[c2_i56];
  }

  c2_b_y = NULL;
  if (!chartInstance->c2_D_out_val_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 6),
                  false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_D_out_val, const char_T *c2_identifier, boolean_T
   *c2_svPtr, real_T c2_b_y[6])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_D_out_val), &c2_thisId,
                        c2_svPtr, c2_b_y);
  sf_mex_destroy(&c2_b_D_out_val);
}

static void c2_f_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, boolean_T
   *c2_svPtr, real_T c2_b_y[6])
{
  real_T c2_dv5[6];
  int32_T c2_i57;
  (void)chartInstance;
  if (mxIsEmpty(c2_d_u)) {
    *c2_svPtr = false;
  } else {
    *c2_svPtr = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv5, 1, 0, 0U, 1, 0U, 1, 6);
    for (c2_i57 = 0; c2_i57 < 6; c2_i57++) {
      c2_b_y[c2_i57] = c2_dv5[c2_i57];
    }
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_D_out_val;
  const char_T *c2_identifier;
  boolean_T *c2_svPtr;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[6];
  int32_T c2_i58;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_D_out_val = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_svPtr = &chartInstance->c2_D_out_val_not_empty;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_D_out_val), &c2_thisId,
                        c2_svPtr, c2_b_y);
  sf_mex_destroy(&c2_b_D_out_val);
  for (c2_i58 = 0; c2_i58 < 6; c2_i58++) {
    (*(real_T (*)[6])c2_outData)[c2_i58] = c2_b_y[c2_i58];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_d_u;
  const mxArray *c2_b_y = NULL;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_d_u = *(real_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_g_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_phi, const char_T *c2_identifier)
{
  real_T c2_b_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_phi), &c2_thisId);
  sf_mex_destroy(&c2_b_phi);
  return c2_b_y;
}

static real_T c2_h_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_b_y;
  real_T c2_d2;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_b_y = c2_d2;
  sf_mex_destroy(&c2_d_u);
  return c2_b_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_phi;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_phi = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_phi), &c2_thisId);
  sf_mex_destroy(&c2_b_phi);
  *(real_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i59;
  const mxArray *c2_b_y = NULL;
  real_T c2_d_u[3];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i59 = 0; c2_i59 < 3; c2_i59++) {
    c2_d_u[c2_i59] = (*(real_T (*)[3])c2_inData)[c2_i59];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_Iin, const char_T *c2_identifier, real_T c2_b_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Iin), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_Iin);
}

static void c2_j_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[3])
{
  real_T c2_dv6[3];
  int32_T c2_i60;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv6, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i60 = 0; c2_i60 < 3; c2_i60++) {
    c2_b_y[c2_i60] = c2_dv6[c2_i60];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_Iin;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[3];
  int32_T c2_i61;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_Iin = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Iin), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_Iin);
  for (c2_i61 = 0; c2_i61 < 3; c2_i61++) {
    (*(real_T (*)[3])c2_outData)[c2_i61] = c2_b_y[c2_i61];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i62;
  const mxArray *c2_b_y = NULL;
  real_T c2_d_u[6];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i62 = 0; c2_i62 < 6; c2_i62++) {
    c2_d_u[c2_i62] = (*(real_T (*)[6])c2_inData)[c2_i62];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_k_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_D_out, const char_T *c2_identifier, real_T c2_b_y[6])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_D_out), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_b_D_out);
}

static void c2_l_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[6])
{
  real_T c2_dv7[6];
  int32_T c2_i63;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv7, 1, 0, 0U, 1, 0U, 1, 6);
  for (c2_i63 = 0; c2_i63 < 6; c2_i63++) {
    c2_b_y[c2_i63] = c2_dv7[c2_i63];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_D_out;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[6];
  int32_T c2_i64;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_D_out = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_D_out), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_b_D_out);
  for (c2_i64 = 0; c2_i64 < 6; c2_i64++) {
    (*(real_T (*)[6])c2_outData)[c2_i64] = c2_b_y[c2_i64];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i65;
  const mxArray *c2_c_y = NULL;
  int32_T c2_i66;
  const mxArray *c2_d_y = NULL;
  int32_T c2_i67;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i68;
  const mxArray *c2_f_y = NULL;
  int32_T c2_i69;
  const mxArray *c2_g_y = NULL;
  real_T c2_d_u[6000];
  int32_T c2_i70;
  const mxArray *c2_h_y = NULL;
  int32_T c2_i71;
  const mxArray *c2_i_y = NULL;
  real_T c2_e_u;
  const mxArray *c2_j_y = NULL;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  chartInstance->c2_u = *(c2_struct_Ifc6eQ84AsHC0d7m6W5OFB *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c2_i65 = 0; c2_i65 < 36000; c2_i65++) {
    chartInstance->c2_c_u[c2_i65] = chartInstance->c2_u.D[c2_i65];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", chartInstance->c2_c_u, 0, 0U, 1U, 0U,
    2, 6000, 6), false);
  sf_mex_addfield(c2_b_y, c2_c_y, "D", "D", 0);
  for (c2_i66 = 0; c2_i66 < 396000; c2_i66++) {
    chartInstance->c2_b_u[c2_i66] = chartInstance->c2_u.K[c2_i66];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", chartInstance->c2_b_u, 0, 0U, 1U, 0U,
    3, 6000, 6, 11), false);
  sf_mex_addfield(c2_b_y, c2_d_y, "K", "K", 0);
  for (c2_i67 = 0; c2_i67 < 396000; c2_i67++) {
    chartInstance->c2_b_u[c2_i67] = chartInstance->c2_u.K12[c2_i67];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", chartInstance->c2_b_u, 0, 0U, 1U, 0U,
    3, 6000, 6, 11), false);
  sf_mex_addfield(c2_b_y, c2_e_y, "K12", "K12", 0);
  for (c2_i68 = 0; c2_i68 < 396000; c2_i68++) {
    chartInstance->c2_b_u[c2_i68] = chartInstance->c2_u.K13[c2_i68];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", chartInstance->c2_b_u, 0, 0U, 1U, 0U,
    3, 6000, 6, 11), false);
  sf_mex_addfield(c2_b_y, c2_f_y, "K13", "K13", 0);
  for (c2_i69 = 0; c2_i69 < 6000; c2_i69++) {
    c2_d_u[c2_i69] = chartInstance->c2_u.phi[c2_i69];
  }

  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 1, 6000),
                false);
  sf_mex_addfield(c2_b_y, c2_g_y, "phi", "phi", 0);
  for (c2_i70 = 0; c2_i70 < 6000; c2_i70++) {
    c2_d_u[c2_i70] = chartInstance->c2_u.id[c2_i70];
  }

  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 1, 6000),
                false);
  sf_mex_addfield(c2_b_y, c2_h_y, "id", "id", 0);
  for (c2_i71 = 0; c2_i71 < 36000; c2_i71++) {
    chartInstance->c2_c_u[c2_i71] = chartInstance->c2_u.x[c2_i71];
  }

  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", chartInstance->c2_c_u, 0, 0U, 1U, 0U,
    2, 6000, 6), false);
  sf_mex_addfield(c2_b_y, c2_i_y, "x", "x", 0);
  c2_e_u = chartInstance->c2_u.fsw;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_b_y, c2_j_y, "fsw", "fsw", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_m_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId,
   c2_struct_Ifc6eQ84AsHC0d7m6W5OFB *c2_b_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[8] = { "D", "K", "K12", "K13", "phi", "id",
    "x", "fsw" };

  c2_thisId.fParent = c2_parentId;
  c2_thisId.bParentIsCell = false;
  sf_mex_check_struct(c2_parentId, c2_d_u, 8, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "D";
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "D",
    "D", 0)), &c2_thisId, c2_b_y->D);
  c2_thisId.fIdentifier = "K";
  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "K",
    "K", 0)), &c2_thisId, c2_b_y->K);
  c2_thisId.fIdentifier = "K12";
  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "K12",
    "K12", 0)), &c2_thisId, c2_b_y->K12);
  c2_thisId.fIdentifier = "K13";
  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "K13",
    "K13", 0)), &c2_thisId, c2_b_y->K13);
  c2_thisId.fIdentifier = "phi";
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "phi",
    "phi", 0)), &c2_thisId, c2_b_y->phi);
  c2_thisId.fIdentifier = "id";
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "id",
    "id", 0)), &c2_thisId, c2_b_y->id);
  c2_thisId.fIdentifier = "x";
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_d_u, "x",
    "x", 0)), &c2_thisId, c2_b_y->x);
  c2_thisId.fIdentifier = "fsw";
  c2_b_y->fsw = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_d_u, "fsw", "fsw", 0)), &c2_thisId);
  sf_mex_destroy(&c2_d_u);
}

static void c2_n_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [36000])
{
  int32_T c2_i72;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), chartInstance->c2_dv8, 1, 0, 0U,
                1, 0U, 2, 6000, 6);
  for (c2_i72 = 0; c2_i72 < 36000; c2_i72++) {
    c2_b_y[c2_i72] = chartInstance->c2_dv8[c2_i72];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_o_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [396000])
{
  int32_T c2_i73;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), chartInstance->c2_dv9, 1, 0, 0U,
                1, 0U, 3, 6000, 6, 11);
  for (c2_i73 = 0; c2_i73 < 396000; c2_i73++) {
    c2_b_y[c2_i73] = chartInstance->c2_dv9[c2_i73];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_p_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [6000])
{
  real_T c2_dv10[6000];
  int32_T c2_i74;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv10, 1, 0, 0U, 1, 0U, 2, 1,
                6000);
  for (c2_i74 = 0; c2_i74 < 6000; c2_i74++) {
    c2_b_y[c2_i74] = c2_dv10[c2_i74];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_c_nom;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_c_nom = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_nom), &c2_thisId,
                        &chartInstance->c2_y);
  sf_mex_destroy(&c2_c_nom);
  *(c2_struct_Ifc6eQ84AsHC0d7m6W5OFB *)c2_outData = chartInstance->c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i75;
  int32_T c2_i76;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i77;
  real_T c2_d_u[66];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i75 = 0;
  for (c2_i76 = 0; c2_i76 < 11; c2_i76++) {
    for (c2_i77 = 0; c2_i77 < 6; c2_i77++) {
      c2_d_u[c2_i77 + c2_i75] = (*(real_T (*)[66])c2_inData)[c2_i77 + c2_i75];
    }

    c2_i75 += 6;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 6, 11),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_q_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [66])
{
  real_T c2_dv11[66];
  int32_T c2_i78;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv11, 1, 0, 0U, 1, 0U, 2, 6,
                11);
  for (c2_i78 = 0; c2_i78 < 66; c2_i78++) {
    c2_b_y[c2_i78] = c2_dv11[c2_i78];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_K;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[66];
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_K = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_K), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_K);
  c2_i79 = 0;
  for (c2_i80 = 0; c2_i80 < 11; c2_i80++) {
    for (c2_i81 = 0; c2_i81 < 6; c2_i81++) {
      (*(real_T (*)[66])c2_outData)[c2_i81 + c2_i79] = c2_b_y[c2_i81 + c2_i79];
    }

    c2_i79 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i82;
  const mxArray *c2_b_y = NULL;
  real_T c2_d_u[5];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i82 = 0; c2_i82 < 5; c2_i82++) {
    c2_d_u[c2_i82] = (*(real_T (*)[5])c2_inData)[c2_i82];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_r_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[5])
{
  real_T c2_dv12[5];
  int32_T c2_i83;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv12, 1, 0, 0U, 1, 0U, 1, 5);
  for (c2_i83 = 0; c2_i83 < 5; c2_i83++) {
    c2_b_y[c2_i83] = c2_dv12[c2_i83];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_err_int;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[5];
  int32_T c2_i84;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_err_int = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_err_int), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_err_int);
  for (c2_i84 = 0; c2_i84 < 5; c2_i84++) {
    (*(real_T (*)[5])c2_outData)[c2_i84] = c2_b_y[c2_i84];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i85;
  int32_T c2_i86;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i87;
  real_T c2_d_u[36];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i85 = 0;
  for (c2_i86 = 0; c2_i86 < 6; c2_i86++) {
    for (c2_i87 = 0; c2_i87 < 6; c2_i87++) {
      c2_d_u[c2_i87 + c2_i85] = (*(real_T (*)[36])c2_inData)[c2_i87 + c2_i85];
    }

    c2_i85 += 6;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 6, 6),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_s_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [36])
{
  real_T c2_dv13[36];
  int32_T c2_i88;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv13, 1, 0, 0U, 1, 0U, 2, 6,
                6);
  for (c2_i88 = 0; c2_i88 < 36; c2_i88++) {
    c2_b_y[c2_i88] = c2_dv13[c2_i88];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Kp;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[36];
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_Kp = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Kp), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_Kp);
  c2_i89 = 0;
  for (c2_i90 = 0; c2_i90 < 6; c2_i90++) {
    for (c2_i91 = 0; c2_i91 < 6; c2_i91++) {
      (*(real_T (*)[36])c2_outData)[c2_i91 + c2_i89] = c2_b_y[c2_i91 + c2_i89];
    }

    c2_i89 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i92;
  int32_T c2_i93;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i94;
  real_T c2_d_u[30];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i92 = 0;
  for (c2_i93 = 0; c2_i93 < 5; c2_i93++) {
    for (c2_i94 = 0; c2_i94 < 6; c2_i94++) {
      c2_d_u[c2_i94 + c2_i92] = (*(real_T (*)[30])c2_inData)[c2_i94 + c2_i92];
    }

    c2_i92 += 6;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 6, 5),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_t_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [30])
{
  real_T c2_dv14[30];
  int32_T c2_i95;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv14, 1, 0, 0U, 1, 0U, 2, 6,
                5);
  for (c2_i95 = 0; c2_i95 < 30; c2_i95++) {
    c2_b_y[c2_i95] = c2_dv14[c2_i95];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Ki;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[30];
  int32_T c2_i96;
  int32_T c2_i97;
  int32_T c2_i98;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_Ki = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Ki), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_Ki);
  c2_i96 = 0;
  for (c2_i97 = 0; c2_i97 < 5; c2_i97++) {
    for (c2_i98 = 0; c2_i98 < 6; c2_i98++) {
      (*(real_T (*)[30])c2_outData)[c2_i98 + c2_i96] = c2_b_y[c2_i98 + c2_i96];
    }

    c2_i96 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i99;
  int32_T c2_i100;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i101;
  real_T c2_d_u[66];
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i99 = 0;
  for (c2_i100 = 0; c2_i100 < 11; c2_i100++) {
    for (c2_i101 = 0; c2_i101 < 6; c2_i101++) {
      c2_d_u[c2_i101 + c2_i99] = (*(real_T (*)[66])c2_inData)[c2_i101 + c2_i99];
    }

    c2_i99 += 6;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 3, 1, 6, 11),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_u_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y
   [66])
{
  real_T c2_dv15[66];
  int32_T c2_i102;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), c2_dv15, 1, 0, 0U, 1, 0U, 3, 1,
                6, 11);
  for (c2_i102 = 0; c2_i102 < 66; c2_i102++) {
    c2_b_y[c2_i102] = c2_dv15[c2_i102];
  }

  sf_mex_destroy(&c2_d_u);
}

static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_K;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[66];
  int32_T c2_i103;
  int32_T c2_i104;
  int32_T c2_i105;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_K = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_K), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_K);
  c2_i103 = 0;
  for (c2_i104 = 0; c2_i104 < 11; c2_i104++) {
    for (c2_i105 = 0; c2_i105 < 6; c2_i105++) {
      (*(real_T (*)[66])c2_outData)[c2_i105 + c2_i103] = c2_b_y[c2_i105 +
        c2_i103];
    }

    c2_i103 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray
  *sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static real_T c2_asin(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T c2_b_x)
{
  real_T c2_c_x;
  c2_c_x = c2_b_x;
  c2_b_asin(chartInstance, &c2_c_x);
  return c2_c_x;
}

static void c2_error(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
                     *chartInstance)
{
  const mxArray *c2_b_y = NULL;
  static char_T c2_d_u[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  const mxArray *c2_c_y = NULL;
  static char_T c2_e_u[4] = { 'a', 's', 'i', 'n' };

  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 10, 0U, 1U, 0U, 2, 1, 30),
                false);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_e_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c2_b_y, 14, c2_c_y));
}

static real_T c2_interp1
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   real_T c2_varargin_1[6000], real_T c2_varargin_2[6000], real_T c2_varargin_3)
{
  real_T c2_Vq;
  int32_T c2_i106;
  real_T c2_xi;
  real_T c2_b_y[6000];
  int32_T c2_i107;
  int32_T c2_k;
  real_T c2_b_x[6000];
  int32_T c2_b_k;
  int32_T c2_j1;
  int32_T c2_c_k;
  int32_T c2_b_j1;
  int32_T c2_c_j1;
  real_T c2_b_xi;
  real_T c2_xtmp;
  real_T c2_minx;
  int32_T c2_d_j1;
  real_T c2_maxx;
  int32_T c2_j2;
  real_T c2_c_xi;
  real_T c2_b_xtmp;
  real_T c2_b_minx;
  real_T c2_b_maxx;
  real_T c2_xik;
  real_T c2_c_x;
  boolean_T c2_b;
  real_T c2_d_xi;
  int32_T c2_low_i;
  int32_T c2_low_ip1;
  int32_T c2_high_i;
  int32_T c2_n;
  int32_T c2_b_low_i;
  real_T c2_xn;
  int32_T c2_b_high_i;
  real_T c2_xnp1;
  int32_T c2_mid_i;
  real_T c2_A;
  real_T c2_B;
  real_T c2_d_x;
  real_T c2_c_y;
  real_T c2_e_x;
  real_T c2_d_y;
  real_T c2_r;
  real_T c2_onemr;
  real_T c2_y1;
  real_T c2_y2;
  int32_T exitg1;
  for (c2_i106 = 0; c2_i106 < 6000; c2_i106++) {
    c2_b_y[c2_i106] = c2_varargin_2[c2_i106];
  }

  c2_xi = c2_varargin_3;
  for (c2_i107 = 0; c2_i107 < 6000; c2_i107++) {
    c2_b_x[c2_i107] = c2_varargin_1[c2_i107];
  }

  c2_k = 1;
  do {
    exitg1 = 0;
    if (c2_k < 6001) {
      c2_b_k = c2_k - 1;
      if (c2_isnan(chartInstance, c2_b_x[c2_b_k])) {
        c2_b_error(chartInstance);
        exitg1 = 1;
      } else {
        c2_k++;
      }
    } else {
      if (c2_b_x[1] < c2_b_x[0]) {
        for (c2_j1 = 1; c2_j1 < 3001; c2_j1++) {
          c2_c_j1 = c2_j1;
          c2_xtmp = c2_b_x[c2_c_j1 - 1];
          c2_b_x[c2_c_j1 - 1] = c2_b_x[6000 - c2_c_j1];
          c2_b_x[6000 - c2_c_j1] = c2_xtmp;
        }

        for (c2_b_j1 = 1; c2_b_j1 < 3001; c2_b_j1++) {
          c2_d_j1 = c2_b_j1 - 1;
          c2_j2 = 5999 - c2_d_j1;
          c2_b_xtmp = c2_b_y[c2_d_j1];
          c2_b_y[c2_d_j1] = c2_b_y[c2_j2];
          c2_b_y[c2_j2] = c2_b_xtmp;
        }
      }

      for (c2_c_k = 2; c2_c_k < 6001; c2_c_k++) {
        c2_b_k = c2_c_k - 2;
        if (c2_b_x[c2_b_k + 1] <= c2_b_x[c2_b_k]) {
          c2_c_error(chartInstance);
        }
      }

      c2_b_xi = c2_xi;
      c2_Vq = rtNaN;
      c2_minx = c2_b_x[0];
      c2_maxx = c2_b_x[5999];
      c2_c_xi = c2_b_xi;
      c2_b_minx = c2_minx;
      c2_b_maxx = c2_maxx;
      c2_xik = c2_c_xi;
      c2_c_x = c2_xik;
      c2_b = muDoubleScalarIsNaN(c2_c_x);
      if (c2_b) {
        c2_Vq = rtNaN;
      } else if (c2_xik > c2_b_maxx) {
      } else if (c2_xik < c2_b_minx) {
      } else {
        c2_d_xi = c2_xik;
        c2_low_i = 1;
        c2_low_ip1 = 1;
        c2_high_i = 6000;
        while (c2_high_i > c2_low_ip1 + 1) {
          c2_b_low_i = c2_low_i;
          c2_b_high_i = c2_high_i;
          c2_mid_i = (c2_b_low_i + c2_b_high_i) >> 1;
          if (c2_d_xi >= c2_b_x[c2_mid_i - 1]) {
            c2_low_i = c2_mid_i;
            c2_low_ip1 = c2_low_i;
          } else {
            c2_high_i = c2_mid_i;
          }
        }

        c2_n = c2_low_i;
        c2_xn = c2_b_x[c2_n - 1];
        c2_xnp1 = c2_b_x[c2_n];
        c2_A = c2_xik - c2_xn;
        c2_B = c2_xnp1 - c2_xn;
        c2_d_x = c2_A;
        c2_c_y = c2_B;
        c2_e_x = c2_d_x;
        c2_d_y = c2_c_y;
        c2_r = c2_e_x / c2_d_y;
        c2_onemr = 1.0 - c2_r;
        if (c2_r == 0.0) {
          c2_y1 = c2_b_y[c2_n - 1];
          c2_Vq = c2_y1;
        } else if (c2_r == 1.0) {
          c2_y2 = c2_b_y[c2_n];
          c2_Vq = c2_y2;
        } else {
          c2_y1 = c2_b_y[c2_n - 1];
          c2_y2 = c2_b_y[c2_n];
          if (c2_y1 == c2_y2) {
            c2_Vq = c2_y1;
          } else {
            c2_Vq = c2_onemr * c2_y1 + c2_r * c2_y2;
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return c2_Vq;
}

static void c2_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_StringToMethodID
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c2_isnan
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   real_T c2_b_x)
{
  (void)chartInstance;
  return muDoubleScalarIsNaN(c2_b_x);
}

static void c2_b_error(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
  *chartInstance)
{
  const mxArray *c2_b_y = NULL;
  static char_T c2_d_u[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'n', 't',
    'e', 'r', 'p', '1', ':', 'N', 'a', 'N', 'i', 'n', 'X' };

  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_b_y));
}

static void c2_c_error(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
  *chartInstance)
{
  const mxArray *c2_b_y = NULL;
  static char_T c2_d_u[35] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', 'e', 'r', 'p', '1', '_', 'n', 'o', 'n',
    'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c', 'X' };

  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_d_u, 10, 0U, 1U, 0U, 2, 1, 35),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_b_y));
}

static real_T c2_ceil(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T c2_b_x)
{
  real_T c2_c_x;
  c2_c_x = c2_b_x;
  c2_b_ceil(chartInstance, &c2_c_x);
  return c2_c_x;
}

static void c2_c_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_d_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_e_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_f_scalarEg
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_dimagree
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_d_u;
  const mxArray *c2_b_y = NULL;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_d_u = *(int32_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_d_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_v_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_b_y;
  int32_T c2_i108;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), &c2_i108, 1, 6, 0U, 0, 0U, 0);
  c2_b_y = c2_i108;
  sf_mex_destroy(&c2_d_u);
  return c2_b_y;
}

static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_b_y;
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_w_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_b_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge,
   const char_T *c2_identifier)
{
  uint8_T c2_b_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge);
  return c2_b_y;
}

static uint8_T c2_x_emlrt_marshallIn
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance,
   const mxArray *c2_d_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_d_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_b_y = c2_u0;
  sf_mex_destroy(&c2_d_u);
  return c2_b_y;
}

static void c2_b_asin(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T *c2_b_x)
{
  real_T c2_c_x;
  boolean_T c2_b0;
  boolean_T c2_b1;
  boolean_T c2_b2;
  boolean_T c2_p;
  c2_c_x = *c2_b_x;
  c2_b0 = (c2_c_x < -1.0);
  c2_b1 = (c2_c_x > 1.0);
  c2_b2 = (c2_b0 || c2_b1);
  c2_p = c2_b2;
  if (c2_p) {
    c2_error(chartInstance);
  }

  *c2_b_x = muDoubleScalarAsin(*c2_b_x);
}

static void c2_b_ceil(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *
                      chartInstance, real_T *c2_b_x)
{
  (void)chartInstance;
  *c2_b_x = muDoubleScalarCeil(*c2_b_x);
}

static void init_dsm_address_info
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address
  (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance)
{
  chartInstance->c2_x = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_D_out = (real_T (*)[6])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_Iin = (real_T (*)[3])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_Vg_meas = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_trigger = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_phi = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
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

void sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(637511722U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1962598264U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(234829212U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1992539297U);
}

mxArray* sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_post_codegen_info(void);
mxArray *sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_autoinheritance_info
  (void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Bb0zxXaZuZTOPF80OYb83D");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo =
      sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_jit_fallback_info(void)
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

mxArray *sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_updateBuildInfo_args_info
  (void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_post_codegen_info(void)
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

static const mxArray
  *sf_get_sim_state_info_c2_MMC_Control_PLECS_Isolated_Full_Bridge(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x9'type','srcId','name','auxInfo'{{M[1],M[5],T\"D_out\",},{M[1],M[6],T\"Iin\",},{M[1],M[15],T\"phi\",},{M[4],M[0],T\"D_out_val\",S'l','i','p'{{M1x2[79 88],M[0],}}},{M[4],M[0],T\"K12_flag\",S'l','i','p'{{M1x2[118 126],M[0],}}},{M[4],M[0],T\"K13_flag\",S'l','i','p'{{M1x2[109 117],M[0],}}},{M[4],M[0],T\"err_int_val\",S'l','i','p'{{M1x2[89 100],M[0],}}},{M[4],M[0],T\"phi_val\",S'l','i','p'{{M1x2[101 108],M[0],}}},{M[8],M[0],T\"is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 9, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance =
      (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MMC_Control_PLECS_Isolated_Full_BridgeMachineNumber_,
           2,
           1,
           1,
           0,
           7,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation
          (_MMC_Control_PLECS_Isolated_Full_BridgeMachineNumber_,
           chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _MMC_Control_PLECS_Isolated_Full_BridgeMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _MMC_Control_PLECS_Isolated_Full_BridgeMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"x");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Vg_meas");
          _SFD_SET_DATA_PROPS(2,1,1,0,"trigger");
          _SFD_SET_DATA_PROPS(3,2,0,1,"D_out");
          _SFD_SET_DATA_PROPS(4,2,0,1,"Iin");
          _SFD_SET_DATA_PROPS(5,2,0,1,"phi");
          _SFD_SET_DATA_PROPS(6,10,0,0,"nom");
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
        _SFD_CV_INIT_EML(0,1,1,0,6,0,0,0,0,0,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2061);
        _SFD_CV_INIT_EML_IF(0,1,0,127,148,-1,285);
        _SFD_CV_INIT_EML_IF(0,1,1,355,365,2004,2055);
        _SFD_CV_INIT_EML_IF(0,1,2,812,843,-1,870);
        _SFD_CV_INIT_EML_IF(0,1,3,872,903,-1,931);
        _SFD_CV_INIT_EML_IF(0,1,4,933,943,-1,974);
        _SFD_CV_INIT_EML_IF(0,1,5,1293,1304,1350,1457);

        {
          static int condStart[] = { 816, 830 };

          static int condEnd[] = { 824, 842 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,815,843,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 876, 890 };

          static int condEnd[] = { 884, 902 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,875,903,2,2,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,816,824,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,830,842,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,876,884,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,890,902,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,936,943,-1,2);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)
            c2_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)
            c2_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)c2_g_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _MMC_Control_PLECS_Isolated_Full_BridgeMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance =
      (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_x);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c2_D_out);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c2_Iin);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c2_Vg_meas);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_trigger);
        _SFD_SET_DATA_VALUE_PTR(6U, &chartInstance->c2_nom);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c2_phi);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "smQzJfaF8qKw5CyBpVNWOCF";
}

static void sf_opaque_initialize_c2_MMC_Control_PLECS_Isolated_Full_Bridge(void *
  chartInstanceVar)
{
  chart_debug_initialization
    (((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
      chartInstanceVar)->S,0);
  initialize_params_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     chartInstanceVar);
  initialize_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     chartInstanceVar);
}

static void sf_opaque_enable_c2_MMC_Control_PLECS_Isolated_Full_Bridge(void
  *chartInstanceVar)
{
  enable_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     chartInstanceVar);
}

static void sf_opaque_disable_c2_MMC_Control_PLECS_Isolated_Full_Bridge(void
  *chartInstanceVar)
{
  disable_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     chartInstanceVar);
}

static void sf_opaque_gateway_c2_MMC_Control_PLECS_Isolated_Full_Bridge(void
  *chartInstanceVar)
{
  sf_gateway_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     chartInstanceVar);
}

static const mxArray*
  sf_opaque_get_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge(SimStruct* S)
{
  return get_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
     sf_get_chart_instance_ptr(S));    /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_MMC_Control_PLECS_Isolated_Full_Bridge(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MMC_Control_PLECS_Isolated_Full_Bridge_optimization_info();
    }

    finalize_c2_MMC_Control_PLECS_Isolated_Full_Bridge
      ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
       chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_MMC_Control_PLECS_Isolated_Full_Bridge
    ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
     chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_MMC_Control_PLECS_Isolated_Full_Bridge
  (SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_MMC_Control_PLECS_Isolated_Full_Bridge
      ((SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*)
       sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_MMC_Control_PLECS_Isolated_Full_Bridge(SimStruct
  *S)
{
  /* Actual parameters from chart:
     nom
   */
  const char_T *rtParamNames[] = { "nom" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0],
    sf_get_param_data_type_id(S,0));

  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_MMC_Control_PLECS_Isolated_Full_Bridge_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
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
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(529605206U));
  ssSetChecksum1(S,(3474214580U));
  ssSetChecksum2(S,(600287158U));
  ssSetChecksum3(S,(184787524U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_MMC_Control_PLECS_Isolated_Full_Bridge(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_MMC_Control_PLECS_Isolated_Full_Bridge(SimStruct *S)
{
  SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *chartInstance;
  chartInstance = (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct *)
    utMalloc(sizeof(SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof
         (SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
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
  mdl_start_c2_MMC_Control_PLECS_Isolated_Full_Bridge(chartInstance);
}

void c2_MMC_Control_PLECS_Isolated_Full_Bridge_method_dispatcher(SimStruct *S,
  int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_MMC_Control_PLECS_Isolated_Full_Bridge(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_MMC_Control_PLECS_Isolated_Full_Bridge(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_MMC_Control_PLECS_Isolated_Full_Bridge(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_MMC_Control_PLECS_Isolated_Full_Bridge_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
