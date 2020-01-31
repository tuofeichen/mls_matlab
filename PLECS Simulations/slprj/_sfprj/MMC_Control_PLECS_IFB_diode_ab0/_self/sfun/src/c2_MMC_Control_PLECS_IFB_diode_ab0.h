#ifndef __c2_MMC_Control_PLECS_IFB_diode_ab0_h__
#define __c2_MMC_Control_PLECS_IFB_diode_ab0_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_struct_79RcP5EcTNsP7tqTmiBesB_tag
#define struct_struct_79RcP5EcTNsP7tqTmiBesB_tag

struct struct_79RcP5EcTNsP7tqTmiBesB_tag
{
  real_T D[7200];
  real_T K[79200];
  real_T phi[1200];
  real_T id[1200];
  real_T x[7200];
  real_T fsw;
};

#endif                                 /*struct_struct_79RcP5EcTNsP7tqTmiBesB_tag*/

#ifndef typedef_c2_struct_79RcP5EcTNsP7tqTmiBesB
#define typedef_c2_struct_79RcP5EcTNsP7tqTmiBesB

typedef struct struct_79RcP5EcTNsP7tqTmiBesB_tag
  c2_struct_79RcP5EcTNsP7tqTmiBesB;

#endif                                 /*typedef_c2_struct_79RcP5EcTNsP7tqTmiBesB*/

#ifndef typedef_SFc2_MMC_Control_PLECS_IFB_diode_ab0InstanceStruct
#define typedef_SFc2_MMC_Control_PLECS_IFB_diode_ab0InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_MMC_Control_PLECS_IFB_diode_ab0;
  c2_struct_79RcP5EcTNsP7tqTmiBesB c2_nom;
  real_T c2_D_out_val[6];
  boolean_T c2_D_out_val_not_empty;
  real_T c2_err_int_val[5];
  boolean_T c2_err_int_val_not_empty;
  real_T c2_phi_val;
  boolean_T c2_phi_val_not_empty;
  real_T c2_Di_out_val[6];
  boolean_T c2_Di_out_val_not_empty;
  real_T c2_Ds_out_val[6];
  boolean_T c2_Ds_out_val_not_empty;
  c2_struct_79RcP5EcTNsP7tqTmiBesB c2_u;
  real_T c2_b_u[79200];
  c2_struct_79RcP5EcTNsP7tqTmiBesB c2_y;
  real_T c2_dv14[79200];
  c2_struct_79RcP5EcTNsP7tqTmiBesB c2_b_nom;
  c2_struct_79RcP5EcTNsP7tqTmiBesB c2_r0;
  real_T (*c2_x)[6];
  real_T (*c2_D_out)[6];
  real_T (*c2_Vg_meas)[3];
  real_T *c2_trigger;
  real_T (*c2_err_int)[5];
  real_T (*c2_dDs)[6];
  real_T (*c2_dDi)[6];
} SFc2_MMC_Control_PLECS_IFB_diode_ab0InstanceStruct;

#endif                                 /*typedef_SFc2_MMC_Control_PLECS_IFB_diode_ab0InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_check_sum(mxArray *plhs[]);
extern void c2_MMC_Control_PLECS_IFB_diode_ab0_method_dispatcher(SimStruct *S,
  int_T method, void *data);

#endif
