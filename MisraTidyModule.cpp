#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "Rule15_1_3Check.h"
#include "Rule15_3_5Check.h"
#include "Rule16_2_4Check.h"
#include "Rule16_2_5Check.h"
#include "Rule18_7_1Check.h"
 
namespace clang {
namespace tidy {
namespace misra {
 
class MisraModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<Rule15_1_3Check>(
        "misra-rule15_1_3");
    CheckFactories.registerCheck<Rule15_3_5Check>(
        "misra-rule15_3_5");
    CheckFactories.registerCheck<Rule16_2_4Check>(
        "misra-rule16_2_4");
    CheckFactories.registerCheck<Rule16_2_5Check>(
        "misra-rule16_2_5");
    CheckFactories.registerCheck<Rule18_7_1Check>(
        "misra-rule18_7_1");
  }
};
} // namespace misra
// Register the MisraTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<misra::MisraModule>
    X("misra-module", "Adds misra lint checks.");
 
volatile int MisraModuleAnchorSource = 0;
 
} // namespace tidy
} // namespace clang