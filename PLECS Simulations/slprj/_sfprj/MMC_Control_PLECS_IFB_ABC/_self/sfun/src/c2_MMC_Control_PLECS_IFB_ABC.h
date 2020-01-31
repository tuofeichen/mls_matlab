#ifndef __c2_MMC_Control_PLECS_IFB_ABC_h__
#define __c2_MMC_Control_PLECS_IFB_ABC_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_struct_AR1X5dl7KK81Sky0rM4hUC_tag
#define struct_struct_AR1X5dl7KK81Sky0rM4hUC_tag

struct struct_AR1X5dl7KK81Sky0rM4hUC_tag
{
  real_T D[3600];
  real_T K[39600];
  real_T phi[600];
  real_T id[600];
  real_T x[3600];
  real_T fsw;
};

#endif                                 /*struct_struct_AR1X5dl7KK81Sky0rM4hUC_tag*/

#ifndef typedef_c2_struct_AR1X5dl7KK81Sky0rM4hUC
#define typedef_c2_struct_AR1X5dl7KK81Sky0rM4hUC

typedef struct struct_AR1X5dl7KK81Sky0rM4hUC_tag
  c2_struct_AR1X5dl7KK81Sky0rM4hUC;

#endif                                 /*typedef_c2_struct_AR1X5dl7KK81Sky0rM4hUC*/

#ifndef typedef_SFc2_MMC_Control_PLECS_IFB_ABCInstanceStruct
#define typedef_SFc2_MMC_Control_PLECS_IFB_ABCInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_MMC_Control_PLECS_IFB_ABC;
  c2_struct_AR1X5dl7KK81Sky0rM4hUC c2_nom;
  real_T c2_D_out_val[6];
  boolean_T c2_D_out_val_not_empty;
  real_T c2_err_int_val[5];
  boolean_T c2_err_int_val_not_empty;
  real_T c2_phi_val;
  boolean_T c2_phi_val_not_empty;
  c2_struct_AR1X5dl7KK81Sky0rM4hUC c2_u;
  real_T c2_b_u[39600];
  c2_struct_AR1X5dl7KK81Sky0rM4hUC c2_y;
  real_T c2_dv9[39600];
  c2_struct_AR1X5dl7KK81Sky0rM4hUC c2_b_nom;
  c2_struct_AR1X5dl7KK81Sky0rM4hUC c2_r0;
  real_T (*c2_x)[6];
  real_T (*c2_D_out)[6];
  real_T (*c2_Iin)[3];
  real_T (*c2_Vg_meas)[3];
  real_T *c2_trigger;
} SFc2_MMC_Control_PLECS_IFB_ABCInstanceStruct;

#endif                                 /*typedef_SFc2_MMC_Control_PLECS_IFB_ABCInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_MMC_Control_PLECS_IFB_ABC_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_MMC_Control_PLECS_IFB_ABC_get_check_sum(mxArray *plhs[]);
extern void c2_MMC_Control_PLECS_IFB_ABC_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
