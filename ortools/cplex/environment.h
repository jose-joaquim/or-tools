// Copyright 2010-2022 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef OR_TOOLS_CPLEX_ENVIRONMENT_H_
#define OR_TOOLS_CPLEX_ENVIRONMENT_H_

#include "absl/flags/declare.h"
#include "absl/flags/flag.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "ortools/base/dynamic_library.h"
#include "ortools/base/logging.h"

namespace operations_research {

struct cpxenv;
typedef struct cpxenv* CPXENVptr;
typedef struct cpxenv const* CPXCENVptr;

struct cpxlp;
typedef struct cpxlp* CPXLPptr;
#ifndef CPXCLPptr
typedef const struct cpxlp* CPXCLPptr;
#endif

#define CPXMESSAGEBUFSIZE 1024

#define CPX_STAT_OPTIMAL 1
#define CPX_STAT_INFEASIBLE 3
#define CPXMIP_INFEASIBLE 103
#define CPX_STAT_UNBOUNDED 2
#define CPX_STAT_INForUNBD 4
#define CPXMIP_INForUNBD 119
#define CPXERR_BAD_ARGUMENT 1003

#define CPX_PARAM_ADVIND 1001
#define CPX_PARAM_AGGFILL 1002
#define CPX_PARAM_AGGIND 1003
#define CPX_PARAM_CLOCKTYPE 1006
#define CPX_PARAM_CRAIND 1007
#define CPX_PARAM_DEPIND 1008
#define CPX_PARAM_DPRIIND 1009
#define CPX_PARAM_PRICELIM 1010
#define CPX_PARAM_EPMRK 1013
#define CPX_PARAM_EPOPT 1014
#define CPX_PARAM_EPPER 1015
#define CPX_PARAM_EPRHS 1016
#define CPX_PARAM_SIMDISPLAY 1019
#define CPX_PARAM_ITLIM 1020
#define CPX_PARAM_ROWREADLIM 1021
#define CPX_PARAM_NETFIND 1022
#define CPX_PARAM_COLREADLIM 1023
#define CPX_PARAM_NZREADLIM 1024
#define CPX_PARAM_OBJLLIM 1025
#define CPX_PARAM_OBJULIM 1026
#define CPX_PARAM_PERIND 1027
#define CPX_PARAM_PERLIM 1028
#define CPX_PARAM_PPRIIND 1029
#define CPX_PARAM_PREIND 1030
#define CPX_PARAM_REINV 1031
#define CPX_PARAM_SCAIND 1034
#define CPX_PARAM_SCRIND 1035
#define CPX_PARAM_SINGLIM 1037
#define CPX_PARAM_TILIM 1039
#define CPX_PARAM_PREDUAL 1044
#define CPX_PARAM_PREPASS 1052
#define CPX_PARAM_DATACHECK 1056
#define CPX_PARAM_REDUCE 1057
#define CPX_PARAM_PRELINEAR 1058
#define CPX_PARAM_LPMETHOD 1062
#define CPX_PARAM_QPMETHOD 1063
#define CPX_PARAM_WORKDIR 1064
#define CPX_PARAM_WORKMEM 1065
#define CPX_PARAM_THREADS 1067
#define CPX_PARAM_CONFLICTALG 1073
#define CPX_PARAM_CONFLICTDISPLAY 1074
#define CPX_PARAM_SIFTDISPLAY 1076
#define CPX_PARAM_SIFTALG 1077
#define CPX_PARAM_SIFTITLIM 1078
#define CPX_PARAM_MPSLONGNUM 1081
#define CPX_PARAM_MEMORYEMPHASIS 1082
#define CPX_PARAM_NUMERICALEMPHASIS 1083
#define CPX_PARAM_FEASOPTMODE 1084
#define CPX_PARAM_PARALLELMODE 1109
#define CPX_PARAM_TUNINGMEASURE 1110
#define CPX_PARAM_TUNINGREPEAT 1111
#define CPX_PARAM_TUNINGTILIM 1112
#define CPX_PARAM_TUNINGDISPLAY 1113
#define CPX_PARAM_WRITELEVEL 1114
#define CPX_PARAM_RANDOMSEED 1124
#define CPX_PARAM_DETTILIM 1127
#define CPX_PARAM_FILEENCODING 1129
#define CPX_PARAM_APIENCODING 1130
#define CPX_PARAM_OPTIMALITYTARGET 1131
#define CPX_PARAM_CLONELOG 1132
#define CPX_PARAM_TUNINGDETTILIM 1139
#define CPX_PARAM_CPUMASK 1144
#define CPX_PARAM_SOLUTIONTYPE 1147
#define CPX_PARAM_WARNLIM 1157
#define CPX_PARAM_SIFTSIM 1158
#define CPX_PARAM_DYNAMICROWS 1161
#define CPX_PARAM_RECORD 1162
#define CPX_PARAM_PARAMDISPLAY 1163
#define CPX_PARAM_FOLDING 1164
#define CPX_PARAM_PREREFORM 1167
#define CPX_PARAM_WORKERALG 1500
#define CPX_PARAM_BENDERSSTRATEGY 1501

#define CPX_ALG_NONE -1
#define CPX_ALG_AUTOMATIC 0
#define CPX_ALG_PRIMAL 1
#define CPX_ALG_DUAL 2
#define CPX_ALG_NET 3
#define CPX_ALG_BARRIER 4
#define CPX_ALG_SIFTING 5
#define CPX_ALG_CONCURRENT 6
#define CPX_ALG_BAROPT 7
#define CPX_ALG_PIVOTIN 8
#define CPX_ALG_PIVOTOUT 9
#define CPX_ALG_PIVOT 10
#define CPX_ALG_FEASOPT 11
#define CPX_ALG_MIP 12
#define CPX_ALG_BENDERS 13
#define CPX_ALG_MULTIOBJ 14
#define CPX_ALG_ROBUST 15

#define CPX_MIPEMPHASIS_BALANCED 0
#define CPX_MIPEMPHASIS_FEASIBILITY 1
#define CPX_MIPEMPHASIS_OPTIMALITY 2
#define CPX_MIPEMPHASIS_BESTBOUND 3
#define CPX_MIPEMPHASIS_HIDDENFEAS 4
#define CPX_MIPEMPHASIS_HEURISTIC 5

#define CPX_PARAMTYPE_NONE 0
#define CPX_PARAMTYPE_INT 1
#define CPX_PARAMTYPE_DOUBLE 2
#define CPX_PARAMTYPE_STRING 3
#define CPX_PARAMTYPE_LONG 4

#define CPX_PARAM_EPGAP 2009
#define CPX_PARAM_STARTALG 2025
#define CPX_PARAM_SUBALG 2026
#define CPXPARAM_Emphasis_MIP 2058

#define CPX_INFBOUND 1.0E+20

#define CPX_CONTINUOUS 'C'
#define CPX_BINARY 'B'
#define CPX_INTEGER 'I'
#define CPX_SEMICONT 'S'
#define CPX_SEMIINT 'N'

#define CPX_AT_LOWER 0
#define CPX_BASIC 1
#define CPX_AT_UPPER 2
#define CPX_FREE_SUPER 3

#define CPX_AUTO -1
#define CPX_ON 1
#define CPX_OFF 0
#define CPX_MAX -1
#define CPX_MIN 1

#define CPXPROB_LP 0
#define CPXPROB_MILP 1
#define CPXPROB_FIXEDMILP 3
#define CPXPROB_NODELP 4
#define CPXPROB_QP 5
#define CPXPROB_MIQP 7
#define CPXPROB_FIXEDMIQP 8
#define CPXPROB_NODEQP 9
#define CPXPROB_QCP 10
#define CPXPROB_MIQCP 11
#define CPXPROB_NODEQCP 12

#define CPX_BENDERS_ANNOTATION "cpxBendersPartition"
#define CPX_BENDERS_MASTERVALUE 0
#define CPX_BIGINT 2100000000
#define CPX_BIGLONG 9223372036800000000LL
#define CPX_CALLBACKCONTEXT_BRANCHING 0x0080
#define CPX_CALLBACKCONTEXT_CANDIDATE 0x0020
#define CPX_CALLBACKCONTEXT_GLOBAL_PROGRESS 0x0010
#define CPX_CALLBACKCONTEXT_LOCAL_PROGRESS 0x0008
#define CPX_CALLBACKCONTEXT_RELAXATION 0x0040
#define CPX_CALLBACKCONTEXT_THREAD_DOWN 0x0004
#define CPX_CALLBACKCONTEXT_THREAD_UP 0x0002
#define CPX_DUAL_OBJ 41
#define CPX_EXACT_KAPPA 51
#define CPX_KAPPA 39
#define CPX_KAPPA_ATTENTION 57
#define CPX_KAPPA_ILLPOSED 55
#define CPX_KAPPA_MAX 56
#define CPX_KAPPA_STABLE 52
#define CPX_KAPPA_SUSPICIOUS 53
#define CPX_KAPPA_UNSTABLE 54
#define CPX_LAZYCONSTRAINTCALLBACK_HEUR CPX_CALLBACK_MIP_INCUMBENT_HEURSOLN
#define CPX_LAZYCONSTRAINTCALLBACK_MIPSTART CPX_CALLBACK_MIP_INCUMBENT_MIPSTART
#define CPX_LAZYCONSTRAINTCALLBACK_NODE CPX_CALLBACK_MIP_INCUMBENT_NODESOLN
#define CPX_LAZYCONSTRAINTCALLBACK_USER CPX_CALLBACK_MIP_INCUMBENT_USERSOLN
#define CPX_MAX_COMP_SLACK 19
#define CPX_MAX_DUAL_INFEAS 5
#define CPX_MAX_DUAL_RESIDUAL 15
#define CPX_MAX_INDSLACK_INFEAS 49
#define CPX_MAX_INT_INFEAS 9
#define CPX_MAX_PI 25
#define CPX_MAX_PRIMAL_INFEAS 1
#define CPX_SUM_QCPRIMAL_RESIDUAL 44
#define CPX_SUM_QCSLACK 48
#define CPX_SUM_QCSLACK_INFEAS 46
#define CPX_SUM_RED_COST 37
#define CPX_SUM_SCALED_DUAL_INFEAS 8
#define CPX_SUM_SCALED_DUAL_RESIDUAL 18
#define CPX_SUM_SCALED_PI 34
#define CPX_SUM_SCALED_PRIMAL_INFEAS 4
#define CPX_SUM_SCALED_PRIMAL_RESIDUAL 14
#define CPX_SUM_SCALED_RED_COST 38
#define CPX_SUM_SCALED_SLACK 36
#define CPX_SUM_SCALED_X 32
#define CPX_SUM_SLACK 35
#define CPX_SUM_X 31
#define CPXERR_NODE_ON_DISK 3504
#define CPXERR_NOT_SAV_FILE 1560
#define CPXERR_NOT_UNBOUNDED 1254
#define CPXMIP_OPTIMAL 101
#define CPXMIP_OPTIMAL_INFEAS 115
#define CPXMIP_OPTIMAL_POPULATED 129
#define CPXMIP_OPTIMAL_POPULATED_TOL 130
#define CPXMIP_OPTIMAL_RELAXED_INF 123
#define CPXMIP_OPTIMAL_RELAXED_QUAD 125
#define CPXMIP_OPTIMAL_RELAXED_SUM 121
#define CPXMIP_OPTIMAL_TOL 102
#define CPXMIP_POPULATESOL_LIM 128
#define CPXMIP_SOL_LIM 104
#define CPXMIP_TIME_LIM_FEAS 107
#define CPXMIP_TIME_LIM_INFEAS 108
#define CPXMIP_UNBOUNDED 118

#ifndef CPXINT_DEFINED
#define CPXINT_DEFINED 1
typedef int CPXINT;
#endif

#ifndef CPXLONG_DEFINED
#define CPXLONG_DEFINED 1
#ifdef _MSC_VER
typedef __int64 CPXLONG;
#else
typedef long long CPXLONG;
#endif
#endif

#if CPX_APIMODEL == CPX_APIMODEL_SMALL
typedef CPXINT CPXDIM;
#elif CPX_APIMODEL == CPX_APIMODEL_LARGE
typedef CPXINT CPXDIM;
#endif

#if CPX_APIMODEL == CPX_APIMODEL_SMALL
typedef CPXINT CPXNNZ;
#elif CPX_APIMODEL == CPX_APIMODEL_LARGE
typedef CPXLONG CPXNNZ;
#endif

#if CPX_APIMODEL == CPX_APIMODEL_SMALL
typedef CPXLONG CPXCNT;
#elif CPX_APIMODEL == CPX_APIMODEL_LARGE
typedef CPXLONG CPXCNT;
#endif

typedef char* CPXCHARptr;        /* to simplify CPXPUBLIC syntax */
typedef const char* CPXCCHARptr; /* to simplify CPXPUBLIC syntax */
typedef void* CPXVOIDptr;        /* to simplify CPXPUBLIC syntax */

bool CplexIsCorrectlyInstalled();
absl::StatusOr<CPXENVptr> GetCplexEnv();
absl::Status LoadCplexDynamicLibrary(std::vector<std::string> potential_paths);

extern std::function<int(CPXCENVptr, CPXCLPptr, int*, int*, int*, int*)>
    CPXsolninfo;
extern std::function<CPXCNT(CPXCENVptr, CPXCLPptr)> CPXgetmipitcnt;
extern std::function<CPXCNT(CPXCENVptr, CPXCLPptr)> CPXgetitcnt;
extern std::function<CPXENVptr(int*)> CPXopenCPLEX;
extern std::function<int(CPXCENVptr, CPXLPptr, int const*, int const*,
                         double const*, double const*, double const*,
                         double const*)>
    CPXcopystart;
extern std::function<int(CPXCENVptr, CPXCLPptr, double*, int)> CPXgetdblquality;
extern std::function<int(CPXCENVptr, CPXLPptr*)> CPXfreeprob;
extern std::function<int(CPXENVptr*)> CPXcloseCPLEX;
extern std::function<int(CPXCENVptr, int*)> CPXversionnumber;
extern std::function<CPXLPptr(CPXCENVptr, int*, char const*)> CPXcreateprob;
extern std::function<int(CPXCENVptr, CPXLPptr, int)> CPXchgobjsen;
extern std::function<int(CPXCENVptr, CPXLPptr, int)> CPXchgprobtype;
extern std::function<int(CPXCENVptr env, CPXLPptr lp, CPXDIM cnt,
                         CPXDIM const* indices, char const* lu,
                         double const* bd)>
    CPXchgbds;
extern std::function<int(CPXENVptr, int, CPXDIM)> CPXsetintparam;
extern std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)>
    CPXgetdj;
extern std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)>
    CPXgetpi;
extern std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)>
    CPXgetx;
extern std::function<CPXDIM(CPXCENVptr, CPXCLPptr)> CPXgetnumrows;
extern std::function<CPXDIM(CPXCENVptr, CPXCLPptr)> CPXgetnumcols;
extern std::function<int(CPXCENVptr, CPXCLPptr)> CPXgetstat;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*,
                         char const*)>
    CPXchgctype;
extern std::function<int(CPXCENVptr, CPXCLPptr, double*)> CPXgetobjval;
extern std::function<int(CPXCENVptr, CPXCLPptr, double*)> CPXgetbestobjval;
extern std::function<int(CPXENVptr, int, double)> CPXsetdblparam;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*,
                         double const*)>
    CPXchgrngval;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXNNZ, CPXNNZ const*,
                         CPXNNZ const*, double const*)>
    CPXchgcoeflist;
extern std::function<int(CPXCENVptr, CPXLPptr, double)> CPXEsetobjoffset;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*,
                         char const*)>
    CPXchgsense;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*,
                         double const*)>
    CPXchgrhs;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM, double)>
    CPXchgcoef;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*,
                         double const*)>
    CPXchgobj;
extern std::function<int(CPXCENVptr, CPXCLPptr, int*, int*)> CPXgetbase;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, double const*,
                         double const*, double const*, char const*,
                         char const* const*)>
    CPXnewcols;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXNNZ, double const*,
                         CPXNNZ const*, CPXDIM const*, double const*,
                         double const*, double const*, char const* const*)>
    CPXaddcols;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM, CPXNNZ,
                         double const*, char const*, CPXNNZ const*,
                         CPXDIM const*, double const*, char const* const*,
                         char const* const*)>
    CPXaddrows;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM)> CPXdelrows;
extern std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM)> CPXdelcols;
extern std::function<int(CPXENVptr, char const*)> CPXreadcopyparam;
extern std::function<CPXCNT(CPXCENVptr, CPXLPptr)> CPXgetnodecnt;
extern std::function<int(CPXCENVptr, CPXLPptr)> CPXmipopt;
extern std::function<int(CPXCENVptr, CPXLPptr)> CPXlpopt;
extern std::function<CPXCCHARptr(CPXCENVptr, int, char*)> CPXgeterrorstring;
extern std::function<int(CPXCENVptr, char const*, int*)> CPXgetparamnum;
extern std::function<int(CPXENVptr, int, CPXINT)> CPXsetintparam;
extern std::function<int(CPXCENVptr, int, int*)> CPXgetparamtype;
extern std::function<int(CPXENVptr, int, double)> CPXsetdblparam;
extern std::function<int(CPXENVptr, int, char const*)> CPXsetstrparam;
extern std::function<int(CPXENVptr, int, CPXLONG)> CPXsetlongparam;

}  // namespace operations_research
#endif