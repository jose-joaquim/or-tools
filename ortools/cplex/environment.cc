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

std::function<int(CPXCENVptr, CPXCLPptr, int*, int*, int*, int*)> CPXsolninfo =
    nullptr;
std::function<CPXCNT(CPXCENVptr, CPXCLPptr)> CPXgetmipitcnt = nullptr;
std::function<CPXCNT(CPXCENVptr, CPXCLPptr)> CPXgetitcnt = nullptr;
std::function<CPXENVptr(int*)> CPXopenCPLEX = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int const*, int const*, double const*,
                  double const*, double const*, double const*)>
    CPXcopystart = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, int)> CPXgetdblquality =
    nullptr;
std::function<int(CPXCENVptr, CPXLPptr*)> CPXfreeprob = nullptr;
std::function<int(CPXENVptr*)> CPXcloseCPLEX = nullptr;
std::function<int(CPXCENVptr, int*)> CPXversionnumber = nullptr;
std::function<CPXLPptr(CPXCENVptr, int*, char const*)> CPXcreateprob = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int)> CPXchgobjsen = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, int)> CPXchgprobtype = nullptr;
std::function<int(CPXCENVptr env, CPXLPptr lp, CPXDIM cnt,
                  CPXDIM const* indices, char const* lu, double const* bd)>
    CPXchgbds = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)> CPXgetdj =
    nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)> CPXgetpi =
    nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*, CPXDIM, CPXDIM)> CPXgetx =
    nullptr;
std::function<CPXDIM(CPXCENVptr, CPXCLPptr)> CPXgetnumrows = nullptr;
std::function<CPXDIM(CPXCENVptr, CPXCLPptr)> CPXgetnumcols = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr)> CPXgetstat = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, char const*)>
    CPXchgctype = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*)> CPXgetobjval = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, double*)> CPXgetbestobjval = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, double const*)>
    CPXchgrngval = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXNNZ, CPXNNZ const*, CPXNNZ const*,
                  double const*)>
    CPXchgcoeflist = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, double)> CPXEsetobjoffset = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, char const*)>
    CPXchgsense = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, double const*)>
    CPXchgrhs = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM, double)> CPXchgcoef =
    nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM const*, double const*)>
    CPXchgobj = nullptr;
std::function<int(CPXCENVptr, CPXCLPptr, int*, int*)> CPXgetbase = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, double const*, double const*,
                  double const*, char const*, char const* const*)>
    CPXnewcols = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXNNZ, double const*,
                  CPXNNZ const*, CPXDIM const*, double const*, double const*,
                  double const*, char const* const*)>
    CPXaddcols = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM, CPXNNZ, double const*,
                  char const*, CPXNNZ const*, CPXDIM const*, double const*,
                  char const* const*, char const* const*)>
    CPXaddrows = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM)> CPXdelrows = nullptr;
std::function<int(CPXCENVptr, CPXLPptr, CPXDIM, CPXDIM)> CPXdelcols = nullptr;
std::function<int(CPXENVptr, char const*)> CPXreadcopyparam = nullptr;
std::function<CPXCNT(CPXCENVptr, CPXLPptr)> CPXgetnodecnt = nullptr;
std::function<int(CPXCENVptr, CPXLPptr)> CPXmipopt = nullptr;
std::function<int(CPXCENVptr, CPXLPptr)> CPXlpopt = nullptr;
std::function<CPXCCHARptr(CPXCENVptr, int, char*)> CPXgeterrorstring = nullptr;
std::function<int(CPXCENVptr, char const*, int*)> CPXgetparamnum = nullptr;
std::function<int(CPXENVptr, int, CPXINT)> CPXsetintparam = nullptr;
std::function<int(CPXCENVptr, int, int*)> CPXgetparamtype = nullptr;
std::function<int(CPXENVptr, int, double)> CPXsetdblparam = nullptr;
std::function<int(CPXENVptr, int, char const*)> CPXsetstrparam = nullptr;
std::function<int(CPXENVptr, int, CPXLONG)> CPXsetlongparam = nullptr;

void LoadCplexFunctions(DynamicLibrary* cplex_dynamic_library) {
  cplex_dynamic_library->GetFunction(&CPXgeterrorstring, "CPXgeterrorstring");
  cplex_dynamic_library->GetFunction(&CPXgetitcnt, "CPXgetitcnt");
  cplex_dynamic_library->GetFunction(&CPXEsetobjoffset, "CPXEsetobjoffset");
  cplex_dynamic_library->GetFunction(&CPXsolninfo, "CPXsolninfo");
  cplex_dynamic_library->GetFunction(&CPXgetmipitcnt, "CPXgetmipitcnt");
  cplex_dynamic_library->GetFunction(&CPXopenCPLEX, "CPXopenCPLEX");
  cplex_dynamic_library->GetFunction(&CPXcopystart, "CPXcopystart");
  cplex_dynamic_library->GetFunction(&CPXgetdblquality, "CPXgetdblquality");
  cplex_dynamic_library->GetFunction(&CPXfreeprob, "CPXfreeprob");
  cplex_dynamic_library->GetFunction(&CPXcloseCPLEX, "CPXcloseCPLEX");
  cplex_dynamic_library->GetFunction(&CPXversionnumber, "CPXversionnumber");
  cplex_dynamic_library->GetFunction(&CPXcreateprob, "CPXcreateprob");
  cplex_dynamic_library->GetFunction(&CPXchgobjsen, "CPXchgobjsen");
  cplex_dynamic_library->GetFunction(&CPXchgprobtype, "CPXchgprobtype");
  cplex_dynamic_library->GetFunction(&CPXchgbds, "CPXchgbds");
  cplex_dynamic_library->GetFunction(&CPXgetdj, "CPXgetdj");
  cplex_dynamic_library->GetFunction(&CPXgetpi, "CPXgetpi");
  cplex_dynamic_library->GetFunction(&CPXgetx, "CPXgetx");
  cplex_dynamic_library->GetFunction(&CPXgetnumrows, "CPXgetnumrows");
  cplex_dynamic_library->GetFunction(&CPXgetnumcols, "CPXgetnumcols");
  cplex_dynamic_library->GetFunction(&CPXgetstat, "CPXgetstat");
  cplex_dynamic_library->GetFunction(&CPXchgctype, "CPXchgctype");
  cplex_dynamic_library->GetFunction(&CPXgetobjval, "CPXgetobjval");
  cplex_dynamic_library->GetFunction(&CPXgetbestobjval, "CPXgetbestobjval");
  cplex_dynamic_library->GetFunction(&CPXchgrngval, "CPXchgrngval");
  cplex_dynamic_library->GetFunction(&CPXchgcoeflist, "CPXchgcoeflist");
  cplex_dynamic_library->GetFunction(&CPXchgsense, "CPXchgsense");
  cplex_dynamic_library->GetFunction(&CPXchgrhs, "CPXchgrhs");
  cplex_dynamic_library->GetFunction(&CPXchgcoef, "CPXchgcoef");
  cplex_dynamic_library->GetFunction(&CPXchgobj, "CPXchgobj");
  cplex_dynamic_library->GetFunction(&CPXgetbase, "CPXgetbase");
  cplex_dynamic_library->GetFunction(&CPXnewcols, "CPXnewcols");
  cplex_dynamic_library->GetFunction(&CPXaddcols, "CPXaddcols");
  cplex_dynamic_library->GetFunction(&CPXaddrows, "CPXaddrows");
  cplex_dynamic_library->GetFunction(&CPXdelrows, "CPXdelrows");
  cplex_dynamic_library->GetFunction(&CPXdelcols, "CPXdelcols");
  cplex_dynamic_library->GetFunction(&CPXgetnodecnt, "CPXgetnodecnt");
  cplex_dynamic_library->GetFunction(&CPXreadcopyparam, "CPXreadcopyparam");
  cplex_dynamic_library->GetFunction(&CPXmipopt, "CPXmipopt");
  cplex_dynamic_library->GetFunction(&CPXlpopt, "CPXlpopt");
  cplex_dynamic_library->GetFunction(&CPXgetparamnum, "CPXgetparamnum");
  cplex_dynamic_library->GetFunction(&CPXsetintparam, "CPXsetintparam");
  cplex_dynamic_library->GetFunction(&CPXgetparamtype, "CPXgetparamtype");
  cplex_dynamic_library->GetFunction(&CPXsetdblparam, "CPXsetdblparam");
  cplex_dynamic_library->GetFunction(&CPXsetstrparam, "CPXsetstrparam");
  cplex_dynamic_library->GetFunction(&CPXsetlongparam, "CPXsetlongparam");
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
    potential_paths.push_back(absl::StrCat("/Applications/CPLEX_Studio", version, "cplex/bin/x86-64_osx/libcplex", version, ".dylib"));
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
  CPXENVptr env = CPXopenCPLEX(&status);

  if (status) {
    char errmsg[CPXMESSAGEBUFSIZE];
    CPXgeterrorstring(env, status, errmsg);
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

  CPXcloseCPLEX(&status.value());

  return true;
}

};  // namespace operations_research