#ifndef __c2_MMC_Control_PLECS_Isolated_Full_Bridge_h__
#define __c2_MMC_Control_PLECS_Isolated_Full_Bridge_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_struct_Ifc6eQ84AsHC0d7m6W5OFB_tag
#define struct_struct_Ifc6eQ84AsHC0d7m6W5OFB_tag

struct struct_Ifc6eQ84AsHC0d7m6W5OFB_tag
{
  real_T D[36000];
  real_T K[396000];
  real_T K12[396000];
  real_T K13[396000];
  real_T phi[6000];
  real_T id[6000];
  real_T x[36000];
  real_T fsw;
};

#endif                                 /*struct_struct_Ifc6eQ84AsHC0d7m6W5OFB_tag*/

#ifndef typedef_c2_struct_Ifc6eQ84AsHC0d7m6W5OFB
#define typedef_c2_struct_Ifc6eQ84AsHC0d7m6W5OFB

typedef struct struct_Ifc6eQ84AsHC0d7m6W5OFB_tag
  c2_struct_Ifc6eQ84AsHC0d7m6W5OFB;

#endif                                 /*typedef_c2_struct_Ifc6eQ84AsHC0d7m6W5OFB*/

#ifndef typedef_SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct
#define typedef_SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_MMC_Control_PLECS_Isolated_Full_Bridge;
  c2_struct_Ifc6eQ84AsHC0d7m6W5OFB c2_nom;
  real_T c2_D_out_val[6];
  boolean_T c2_D_out_val_not_empty;
  real_T c2_err_int_val[5];
  boolean_T c2_err_int_val_not_empty;
  real_T c2_phi_val;
  boolean_T c2_phi_val_not_empty;
  real_T c2_K13_flag;
  boolean_T c2_K13_flag_not_empty;
  real_T c2_K12_flag;
  boolean_T c2_K12_flag_not_empty;
  c2_struct_Ifc6eQ84AsHC0d7m6W5OFB c2_u;
  real_T c2_b_u[396000];
  real_T c2_c_u[36000];
  c2_struct_Ifc6eQ84AsHC0d7m6W5OFB c2_y;
  real_T c2_dv9[396000];
  c2_struct_Ifc6eQ84AsHC0d7m6W5OFB c2_b_nom;
  c2_struct_Ifc6eQ84AsHC0d7m6W5OFB c2_r0;
  real_T c2_dv8[36000];
  real_T (*c2_x)[6];
  real_T (*c2_D_out)[6];
  real_T (*c2_Iin)[3];
  real_T (*c2_Vg_meas)[3];
  real_T *c2_trigger;
  real_T *c2_phi;
} SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct;

#endif                                 /*typedef_SFc2_MMC_Control_PLECS_Isolated_Full_BridgeInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_MMC_Control_PLECS_Isolated_Full_Bridge_get_check_sum(mxArray
  *plhs[]);
extern void c2_MMC_Control_PLECS_Isolated_Full_Bridge_method_dispatcher
  (SimStruct *S, int_T method, void *data);

#endif
