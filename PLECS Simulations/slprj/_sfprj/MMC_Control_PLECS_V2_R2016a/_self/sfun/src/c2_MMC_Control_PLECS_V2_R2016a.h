#ifndef __c2_MMC_Control_PLECS_V2_R2016a_h__
#define __c2_MMC_Control_PLECS_V2_R2016a_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_struct_MahUWsIF9IMg4dV7SBEcWD_tag
#define struct_struct_MahUWsIF9IMg4dV7SBEcWD_tag

struct struct_MahUWsIF9IMg4dV7SBEcWD_tag
{
  real_T D[36000];
  real_T K[396000];
  real_T phi[6000];
  real_T id[6000];
  real_T x[36000];
  real_T fsw;
};

#endif                                 /*struct_struct_MahUWsIF9IMg4dV7SBEcWD_tag*/

#ifndef typedef_c2_struct_MahUWsIF9IMg4dV7SBEcWD
#define typedef_c2_struct_MahUWsIF9IMg4dV7SBEcWD

typedef struct struct_MahUWsIF9IMg4dV7SBEcWD_tag
  c2_struct_MahUWsIF9IMg4dV7SBEcWD;

#endif                                 /*typedef_c2_struct_MahUWsIF9IMg4dV7SBEcWD*/

#ifndef typedef_SFc2_MMC_Control_PLECS_V2_R2016aInstanceStruct
#define typedef_SFc2_MMC_Control_PLECS_V2_R2016aInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_MMC_Control_PLECS_V2_R2016a;
  c2_struct_MahUWsIF9IMg4dV7SBEcWD c2_nom;
  real_T c2_D_out_val[6];
  boolean_T c2_D_out_val_not_empty;
  real_T c2_err_int_val[5];
  boolean_T c2_err_int_val_not_empty;
  c2_struct_MahUWsIF9IMg4dV7SBEcWD c2_u;
  real_T c2_b_u[396000];
  real_T c2_c_u[36000];
  c2_struct_MahUWsIF9IMg4dV7SBEcWD c2_y;
  real_T c2_dv12[396000];
  c2_struct_MahUWsIF9IMg4dV7SBEcWD c2_b_nom;
  c2_struct_MahUWsIF9IMg4dV7SBEcWD c2_r0;
  real_T c2_dv11[36000];
  real_T (*c2_x)[6];
  real_T (*c2_D_out)[6];
  real_T (*c2_Iin)[3];
  real_T (*c2_Vg_meas)[3];
  real_T *c2_trigger;
} SFc2_MMC_Control_PLECS_V2_R2016aInstanceStruct;

#endif                                 /*typedef_SFc2_MMC_Control_PLECS_V2_R2016aInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_MMC_Control_PLECS_V2_R2016a_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_MMC_Control_PLECS_V2_R2016a_get_check_sum(mxArray *plhs[]);
extern void c2_MMC_Control_PLECS_V2_R2016a_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
