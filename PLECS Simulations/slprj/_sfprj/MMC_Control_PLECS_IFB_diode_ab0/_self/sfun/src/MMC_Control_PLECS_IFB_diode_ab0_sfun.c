/* Include files */

#include "MMC_Control_PLECS_IFB_diode_ab0_sfun.h"
#include "MMC_Control_PLECS_IFB_diode_ab0_sfun_debug_macros.h"
#include "c2_MMC_Control_PLECS_IFB_diode_ab0.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _MMC_Control_PLECS_IFB_diode_ab0MachineNumber_;

/* Function Declarations */

/* Function Definitions */
void MMC_Control_PLECS_IFB_diode_ab0_initializer(void)
{
}

void MMC_Control_PLECS_IFB_diode_ab0_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_method_dispatcher(SimStruct
  *simstructPtr, unsigned int chartFileNumber, const char* specsCksum, int_T
  method, void *data)
{
  if (chartFileNumber==2) {
    c2_MMC_Control_PLECS_IFB_diode_ab0_method_dispatcher(simstructPtr, method,
      data);
    return 1;
  }

  return 0;
}

unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_process_check_sum_call( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2772363113U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(928268394U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3554081768U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3332951988U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_check_sum
            (mxArray *plhs[]);
          sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2175283100U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1852739243U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2327506406U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1783100865U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(67926074U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2248491147U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(697713842U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(856481896U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_autoinheritance_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(aiChksum, "yB3fuLcyliqsicVcqRyMO") == 0) {
          extern mxArray
            *sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_autoinheritance_info(void);
          plhs[0] =
            sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_get_eml_resolved_functions_info(
  int nlhs, mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        extern const mxArray
          *sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_MMC_Control_PLECS_IFB_diode_ab0_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_third_party_uses_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "sSKFdxGsi3CDMlntsf4jpYD") == 0) {
          extern mxArray
            *sf_c2_MMC_Control_PLECS_IFB_diode_ab0_third_party_uses_info(void);
          plhs[0] = sf_c2_MMC_Control_PLECS_IFB_diode_ab0_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_jit_fallback_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "sSKFdxGsi3CDMlntsf4jpYD") == 0) {
          extern mxArray
            *sf_c2_MMC_Control_PLECS_IFB_diode_ab0_jit_fallback_info(void);
          plhs[0] = sf_c2_MMC_Control_PLECS_IFB_diode_ab0_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_MMC_Control_PLECS_IFB_diode_ab0_updateBuildInfo_args_info( int
  nlhs, mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "sSKFdxGsi3CDMlntsf4jpYD") == 0) {
          extern mxArray
            *sf_c2_MMC_Control_PLECS_IFB_diode_ab0_updateBuildInfo_args_info
            (void);
          plhs[0] =
            sf_c2_MMC_Control_PLECS_IFB_diode_ab0_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void MMC_Control_PLECS_IFB_diode_ab0_debug_initialize(struct
  SfDebugInstanceStruct* debugInstance)
{
  _MMC_Control_PLECS_IFB_diode_ab0MachineNumber_ = sf_debug_initialize_machine
    (debugInstance,"MMC_Control_PLECS_IFB_diode_ab0","sfun",0,1,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _MMC_Control_PLECS_IFB_diode_ab0MachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _MMC_Control_PLECS_IFB_diode_ab0MachineNumber_,0);
}

void MMC_Control_PLECS_IFB_diode_ab0_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
typedef struct SfOptimizationInfoFlagsTag {
  boolean_T isRtwGen;
  boolean_T isModelRef;
  boolean_T isExternal;
} SfOptimizationInfoFlags;

static SfOptimizationInfoFlags sOptimizationInfoFlags;
void unload_MMC_Control_PLECS_IFB_diode_ab0_optimization_info(void);
mxArray* load_MMC_Control_PLECS_IFB_diode_ab0_optimization_info(boolean_T
  isRtwGen, boolean_T isModelRef, boolean_T isExternal)
{
  if (sOptimizationInfoFlags.isRtwGen != isRtwGen ||
      sOptimizationInfoFlags.isModelRef != isModelRef ||
      sOptimizationInfoFlags.isExternal != isExternal) {
    unload_MMC_Control_PLECS_IFB_diode_ab0_optimization_info();
  }

  sOptimizationInfoFlags.isRtwGen = isRtwGen;
  sOptimizationInfoFlags.isModelRef = isModelRef;
  sOptimizationInfoFlags.isExternal = isExternal;
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "MMC_Control_PLECS_IFB_diode_ab0", "MMC_Control_PLECS_IFB_diode_ab0");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_MMC_Control_PLECS_IFB_diode_ab0_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
