//===--- Rule16_2_2Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule16_2_2Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/Token.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <string>
#include <iostream>
using namespace clang::ast_matchers;

#define MACRO_ALLOWED_NUM 8

const char MacroAllowed [MACRO_ALLOWED_NUM][15] = { 
  "auto", "register", "static", "extern", "mutable",
  "const", "volatile", "restrict"
} ;

namespace clang {
namespace tidy {
namespace misra {

namespace {
class PreprocessorCallbacks : public PPCallbacks{

public:
  PreprocessorCallbacks(Rule16_2_2Check &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}

  void MacroDefined (const Token &MacroNameTok, const MacroDirective *MD) override
  {
    auto *MacroInfo =  MD->getMacroInfo();
  
    llvm::SmallString<128> SpellingBuffer;
    std::string MacroDefinition;
    for (const auto &T : MacroInfo->tokens()  ) {
      auto cur = PP.getSpelling(T, SpellingBuffer);  //get every tokens and concatenate them.
      MacroDefinition += cur.str();
    } 

    bool errorFlag = true;

    for(int i = 0 ; i < MACRO_ALLOWED_NUM ; i++)
    {
      if( MacroDefinition.compare(MacroAllowed[i]) == 0)
        errorFlag = false;
    }

    auto MacroName = PP.getSpelling(MacroNameTok, SpellingBuffer);
    if(MacroName.equals("__GCC_HAVE_DWARF2_CFI_ASM"))  // default macro of clang which might cause unsupressed warning.
      errorFlag = false;

    if(MacroDefinition.size() > 0 && errorFlag)
      Check.diag(MacroInfo->getDefinitionLoc(), "C++ macros shall only be used for include guards, type qualifiers, or storage class specifiers.");
    
  }
private:
  Rule16_2_2Check &Check;
  Preprocessor &PP;
};

}


void Rule16_2_2Check::registerPPCallbacks(const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<PreprocessorCallbacks>(*this, *PP));
}


} // namespace misra
} // namespace tidy
} // namespace clang
