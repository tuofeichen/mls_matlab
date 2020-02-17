#ifndef __c2_MMC_Control_PLECS_diode_IFB_h__
#define __c2_MMC_Control_PLECS_diode_IFB_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_struct_ojzwK8Jz45Am72HbWmwUdE_tag
#define struct_struct_ojzwK8Jz45Am72HbWmwUdE_tag

struct struct_ojzwK8Jz45Am72HbWmwUdE_tag
{
  real_T D[1800];
  real_T K[19800];
  real_T phi[300];
  real_T id[300];
  real_T x[1800];
  real_T fsw;
};

#endif                                 /*struct_struct_ojzwK8Jz45Am72HbWmwUdE_tag*/

#ifndef typedef_c2_struct_ojzwK8Jz45Am72HbWmwUdE
#define typedef_c2_struct_ojzwK8Jz45Am72HbWmwUdE

typedef struct struct_ojzwK8Jz45Am72HbWmwUdE_tag
  c2_struct_ojzwK8Jz45Am72HbWmwUdE;

#endif                                 /*typedef_c2_struct_ojzwK8Jz45Am72HbWmwUdE*/

#ifndef typedef_SFc2_MMC_Control_PLECS_diode_IFBInstanceStruct
#define typedef_SFc2_MMC_Control_PLECS_diode_IFBInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_MMC_Control_PLECS_diode_IFB;
  c2_struct_ojzwK8Jz45Am72HbWmwUdE c2_nom;
  real_T c2_D_out_val[6];
  boolean_T c2_D_out_val_not_empty;
  real_T c2_err_int_val[5];
  boolean_T c2_err_int_val_not_empty;
  real_T c2_phi_val;
  boolean_T c2_phi_val_not_empty;
  c2_struct_ojzwK8Jz45Am72HbWmwUdE c2_u;
  c2_struct_ojzwK8Jz45Am72HbWmwUdE c2_y;
  c2_struct_ojzwK8Jz45Am72HbWmwUdE c2_b_nom;
  real_T (*c2_x)[6];
  real_T (*c2_D_out)[6];
  real_T (*c2_Vg_meas)[3];
  real_T *c2_trigger;
  real_T *c2_phi;
} SFc2_MMC_Control_PLECS_diode_IFBInstanceStruct;

#endif                                 /*typedef_SFc2_MMC_Control_PLECS_diode_IFBInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_MMC_Control_PLECS_diode_IFB_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_MMC_Control_PLECS_diode_IFB_get_check_sum(mxArray *plhs[]);
extern void c2_MMC_Control_PLECS_diode_IFB_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
