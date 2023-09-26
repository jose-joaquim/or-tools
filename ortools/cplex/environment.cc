#include "ortools/cplex/environment.h"

#include <mutex>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/synchronization/mutex.h"
#include "ortools/base/file.h"
#include "ortools/base/logging.h"
#include "ortools/base/status_macros.h"

namespace operations_research {

std::function<int(CPXCENVptr, CPXCLPptr, int*, int*, int*, int*)> CPXXsolninfo =
    nullptr;
std::function<CPXCNT(CPXCENVptr, CPXCLPptr)> CPXXgetmipitcnt = nullptr;
std::function<CPXCNT(CPXCENVptr, CPXCLPptr)> CPXXgetitcnt = nullptr;
std::function<CPXENVptr(int*)> CPXXopenCPLEX = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int const*, int const*, double const*,
                  double const*, double const*, double const*)>
    CPXXcopystart = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, int)> CPXXgetdblquality =
    nullptr;
std::function<int(CPXCENVptr, CPXLPptr*)> CPXXfreeprob = nullptr;
std::function<int(CPXENVptr*)> CPXXcloseCPLEX = nullptr;
std::function<int(CPXCENVptr, int*)> CPXXversionnumber = nullptr;
std::function<CPXLPptr(CPXCENVptr, int*, char const*)> CPXXcreateprob = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int)> CPXXchgobjsen = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int)> CPXXchgprobtype = nullptr;
std::function<int(CPXCENVptr env, CPXLPptr lp, CPXDIM cnt,
                  CPXDIM const* indices, char const* lu, double const* bd)>
    CPXXchgbds = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)> CPXXgetdj =
    nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)> CPXXgetpi =
    nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)> CPXXgetx =
    nullptr;
std::function<CPXDIM(CPXCENVptr, CPXCLPptr)> CPXXgetnumrows = nullptr;
std::function<CPXDIM(CPXCENVptr, CPXCLPptr)> CPXXgetnumcols = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr)> CPXXgetstat = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, char const*)>
    CPXXchgctype = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*)> CPXXgetobjval = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*)> CPXXgetbestobjval = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, double const*)>
    CPXXchgrngval = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXNNZ, CPXDIM const*, CPXDIM const*,
                  double const*)>
    CPXXchgcoeflist = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, double)> CPXXEsetobjoffset = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, char const*)>
    CPXXchgsense = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, double const*)>
    CPXXchgrhs = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM, double)> CPXXchgcoef =
    nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, double const*)>
    CPXXchgobj = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, int*, int*)> CPXXgetbase = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, double const*, double const*,
                  double const*, char const*, char const* const*)>
    CPXXnewcols = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXNNZ, double const*,
                  CPXNNZ const*, CPXDIM const*, double const*, double const*,
                  double const*, char const* const*)>
    CPXXaddcols = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM, CPXNNZ, double const*,
                  char const*, CPXNNZ const*, CPXDIM const*, double const*,
                  char const* const*, char const* const*)>
    CPXXaddrows = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM)> CPXXdelrows = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM)> CPXXdelcols = nullptr;
std::function<int(CPXENVptr, char const*)> CPXXreadcopyparam = nullptr;
std::function<CPXCNT(CPXCENVptr, CPXLPptr)> CPXXgetnodecnt = nullptr;
std::function<int(CPXCENVptr, CPXLPptr)> CPXXmipopt = nullptr;
std::function<int(CPXCENVptr, CPXLPptr)> CPXXlpopt = nullptr;
std::function<CPXCCHARptr(CPXCENVptr, int, char*)> CPXXgeterrorstring = nullptr;
std::function<int(CPXCENVptr, char const*, int*)> CPXXgetparamnum = nullptr;
std::function<int(CPXENVptr, int, CPXINT)> CPXXsetintparam = nullptr;
std::function<int(CPXCENVptr, int, int*)> CPXXgetparamtype = nullptr;
std::function<int(CPXENVptr, int, double)> CPXXsetdblparam = nullptr;
std::function<int(CPXENVptr, int, char const*)> CPXXsetstrparam = nullptr;
std::function<int(CPXENVptr, int, CPXLONG)> CPXXsetlongparam = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int, CPXNNZ, CPXNNZ const*,
                  CPXDIM const*, double const*, int const*, char const* const*)>
    CPXXaddmipstarts = nullptr;
std::function<int(CPXCENVptr, char const*, char const*)> CPXXsetlogfilename =
    nullptr;

void LoadCplexFunctions(DynamicLibrary* cplex_dynamic_library) {
  cplex_dynamic_library->GetFunction(&CPXXsetlogfilename, "CPXXsetlogfilename");
  cplex_dynamic_library->GetFunction(&CPXXaddmipstarts, "CPXXaddmipstarts");
  cplex_dynamic_library->GetFunction(&CPXXgeterrorstring, "CPXXgeterrorstring");
  cplex_dynamic_library->GetFunction(&CPXXgetitcnt, "CPXXgetitcnt");
  cplex_dynamic_library->GetFunction(&CPXXEsetobjoffset, "CPXXEsetobjoffset");
  cplex_dynamic_library->GetFunction(&CPXXsolninfo, "CPXXsolninfo");
  cplex_dynamic_library->GetFunction(&CPXXgetmipitcnt, "CPXXgetmipitcnt");
  cplex_dynamic_library->GetFunction(&CPXXopenCPLEX, "CPXXopenCPLEX");
  cplex_dynamic_library->GetFunction(&CPXXcopystart, "CPXXcopystart");
  cplex_dynamic_library->GetFunction(&CPXXgetdblquality, "CPXXgetdblquality");
  cplex_dynamic_library->GetFunction(&CPXXfreeprob, "CPXXfreeprob");
  cplex_dynamic_library->GetFunction(&CPXXcloseCPLEX, "CPXXcloseCPLEX");
  cplex_dynamic_library->GetFunction(&CPXXversionnumber, "CPXXversionnumber");
  cplex_dynamic_library->GetFunction(&CPXXcreateprob, "CPXXcreateprob");
  cplex_dynamic_library->GetFunction(&CPXXchgobjsen, "CPXXchgobjsen");
  cplex_dynamic_library->GetFunction(&CPXXchgprobtype, "CPXXchgprobtype");
  cplex_dynamic_library->GetFunction(&CPXXchgbds, "CPXXchgbds");
  cplex_dynamic_library->GetFunction(&CPXXgetdj, "CPXXgetdj");
  cplex_dynamic_library->GetFunction(&CPXXgetpi, "CPXXgetpi");
  cplex_dynamic_library->GetFunction(&CPXXgetx, "CPXXgetx");
  cplex_dynamic_library->GetFunction(&CPXXgetnumrows, "CPXXgetnumrows");
  cplex_dynamic_library->GetFunction(&CPXXgetnumcols, "CPXXgetnumcols");
  cplex_dynamic_library->GetFunction(&CPXXgetstat, "CPXXgetstat");
  cplex_dynamic_library->GetFunction(&CPXXchgctype, "CPXXchgctype");
  cplex_dynamic_library->GetFunction(&CPXXgetobjval, "CPXXgetobjval");
  cplex_dynamic_library->GetFunction(&CPXXgetbestobjval, "CPXXgetbestobjval");
  cplex_dynamic_library->GetFunction(&CPXXchgrngval, "CPXXchgrngval");
  cplex_dynamic_library->GetFunction(&CPXXchgcoeflist, "CPXXchgcoeflist");
  cplex_dynamic_library->GetFunction(&CPXXchgsense, "CPXXchgsense");
  cplex_dynamic_library->GetFunction(&CPXXchgrhs, "CPXXchgrhs");
  cplex_dynamic_library->GetFunction(&CPXXchgcoef, "CPXXchgcoef");
  cplex_dynamic_library->GetFunction(&CPXXchgobj, "CPXXchgobj");
  cplex_dynamic_library->GetFunction(&CPXXgetbase, "CPXXgetbase");
  cplex_dynamic_library->GetFunction(&CPXXnewcols, "CPXXnewcols");
  cplex_dynamic_library->GetFunction(&CPXXaddcols, "CPXXaddcols");
  cplex_dynamic_library->GetFunction(&CPXXaddrows, "CPXXaddrows");
  cplex_dynamic_library->GetFunction(&CPXXdelrows, "CPXXdelrows");
  cplex_dynamic_library->GetFunction(&CPXXdelcols, "CPXXdelcols");
  cplex_dynamic_library->GetFunction(&CPXXgetnodecnt, "CPXXgetnodecnt");
  cplex_dynamic_library->GetFunction(&CPXXreadcopyparam, "CPXXreadcopyparam");
  cplex_dynamic_library->GetFunction(&CPXXmipopt, "CPXXmipopt");
  cplex_dynamic_library->GetFunction(&CPXXlpopt, "CPXXlpopt");
  cplex_dynamic_library->GetFunction(&CPXXgetparamnum, "CPXXgetparamnum");
  cplex_dynamic_library->GetFunction(&CPXXsetintparam, "CPXXsetintparam");
  cplex_dynamic_library->GetFunction(&CPXXgetparamtype, "CPXXgetparamtype");
  cplex_dynamic_library->GetFunction(&CPXXsetdblparam, "CPXXsetdblparam");
  cplex_dynamic_library->GetFunction(&CPXXsetstrparam, "CPXXsetstrparam");
  cplex_dynamic_library->GetFunction(&CPXXsetlongparam, "CPXXsetlongparam");
}

// TODO: add fully support to linux and macOS
std::vector<std::string> CplexDynamicLibraryPotentialPaths() {
  std::vector<std::string> potential_paths;
  const std::vector<std::string> kCplexVersions = {"2010"};

  potential_paths.reserve(kCplexVersions.size() * 3);

  for (const std::string& version : kCplexVersions) {
    const char* cplex_home_from_env = getenv("Path");
    std::vector<std::string> values = absl::StrSplit(cplex_home_from_env, ';');
    for (const std::string& path : values) {
#if defined(_MSC_VER)  // Windows
      if (path.find("cplex\\bin") != std::string::npos) {
        potential_paths.push_back(
            absl::StrCat(path, "\\cplex", version, ".dll"));
      } else if (path.find(absl::StrCat("cplex", version, "\\bin")) !=
                 std::string::npos) {
        potential_paths.push_back(
            absl::StrCat(path, "\\cplex", version, ".dll"));
      }
#else
      LOG(ERROR) << "OS Not recognized by cplex/environment.cc."
                 << " You won't be able to use Cplex.";
#endif
    }
  }

  // Search for canonical places.
  for (const std::string& version : kCplexVersions) {
#if defined(_MSC_VER)  // Windows
    potential_paths.push_back(
        absl::StrCat("C:\\Program Files\\ILOG\\CPLEX_Studio", version,
                     "\\cplex\\bin\\cplex", version, ".dll"));
    potential_paths.push_back(
        absl::StrCat("C:\\Program Files\\IBM\\ILOG\\CPLEX_Studio", version,
                     "\\cplex\\bin\\cplex", version, ".dll"));
    potential_paths.push_back(absl::StrCat("C:\\ILOG\\CPLEX_Studio", version,
                                           "\\cplex\\bin\\cplex", version,
                                           ".dll"));
    potential_paths.push_back(absl::StrCat("C:\\IBM\\ILOG\\CPLEX_Studio",
                                           version, "\\cplex\\bin\\cplex",
                                           version, ".dll"));
#elif defined(__APPLE__)  // OS X (intel processors)
    potential_paths.push_back(
        absl::StrCat("/Applications/CPLEX_Studio", version,
                     "cplex/bin/x86-64_osx/libcplex", version, ".dylib"));
#else
    LOG(ERROR) << "OS Not recognized by cplx/environment.cc."
               << " You won't be able to use Cplex.";
#endif
  }

  return potential_paths;
}

absl::Status LoadCplexDynamicLibrary(std::vector<std::string> potential_paths) {
  static std::once_flag cplex_loading_done;
  static absl::Status cplex_load_status;
  static DynamicLibrary cplex_library;
  static absl::Mutex mutex;

  absl::MutexLock lock(&mutex);

  std::call_once(cplex_loading_done, [&potential_paths]() {
    const std::vector<std::string> canonical_paths =
        CplexDynamicLibraryPotentialPaths();
    potential_paths.insert(potential_paths.end(), canonical_paths.begin(),
                           canonical_paths.end());
    for (const std::string& path : potential_paths) {
      if (cplex_library.TryToLoad(path)) {
        LOG(INFO) << "Found the Cplex library in " << path << ".";
        break;
      }
    }

    if (cplex_library.LibraryIsLoaded()) {
      LoadCplexFunctions(&cplex_library);
      cplex_load_status = absl::OkStatus();
    } else {
      cplex_load_status = absl::NotFoundError(absl::StrCat(
          "Could not find the Cplex shared library. Looked in: [",
          absl::StrJoin(potential_paths, "', '"),
          "]. If you know where it"
          " is, pass the full path to 'LoadCplexDynamicLibrary()'."));
    }
  });
  return cplex_load_status;
}

absl::StatusOr<CPXENVptr> GetCplexEnv() {
  RETURN_IF_ERROR(LoadCplexDynamicLibrary({}));

  int status = 0;
  CPXENVptr env = CPXXopenCPLEX(&status);

  if (status) {
    char errmsg[CPXMESSAGEBUFSIZE];
    CPXXgeterrorstring(env, status, errmsg);
    return absl::FailedPreconditionError(
        absl::StrCat("Found the Cplex shared library, but could not create "
                     "Cplex environment: is Cplex licensed on this machine?",
                     std::string(errmsg)));
  }
  return env;
}

bool CplexIsCorrectlyInstalled() {
  absl::StatusOr<CPXENVptr> status = GetCplexEnv();
  if (!status.ok() || status.value() == nullptr) {
    return false;
  }

  CPXXcloseCPLEX(&status.value());

  return true;
}

};  // namespace operations_research
