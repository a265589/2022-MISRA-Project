//===--- Rule17_0_1Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule17_0_1Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/Token.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace clang::ast_matchers;
using namespace std;


namespace clang {
namespace tidy {
namespace misra {

namespace {
class PreprocessorCallbacks : public PPCallbacks{

public:
  PreprocessorCallbacks(Rule17_0_1Check &Check, Preprocessor &PP)
      : Check(Check), PP(PP)
    {
      string name;
      ifstream nameFile ("/home/a265589/project/17-0-1/rule17_0_1_not_allowed_macro_name.txt");
      if (nameFile.is_open())
      {
        while ( nameFile >> name )
        {
              
          if(name.rfind("#", 0) != 0)
          {
             NameNotAllowed.push_back(name);
          }

           
        }
      }
      nameFile.close(); 
    }

  void MacroDefined (const Token &MacroNameTok, const MacroDirective *MD) override
  {
    auto* idInfo = MacroNameTok.getIdentifierInfo();

    auto id = idInfo->getName();


    for(auto& s : NameNotAllowed)
    {
      if(id.equals(s))
      {
        Check.diag(MacroNameTok.getLocation(), "Reserved identifiers, macros, and functions in the standard library shall not be defined, redefined or undefined.");
        break;
      }
    }

       



  }
  void MacroUndefined (const Token &MacroNameTok, const MacroDefinition &MD, const MacroDirective *Undef) override
  {
    auto* idInfo = MacroNameTok.getIdentifierInfo();

    auto id = idInfo->getName();

    
    for(auto& s : NameNotAllowed)
    {
      if(id.equals(s))
      {
        Check.diag(MacroNameTok.getLocation(), "Reserved identifiers, macros, and functions in the standard library shall not be defined, redefined or undefined.");
        break;
      }
    }

        

  }

private:
  Rule17_0_1Check &Check;
  Preprocessor &PP;
  vector<string> NameNotAllowed;
};

}


void Rule17_0_1Check::registerPPCallbacks(const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<PreprocessorCallbacks>(*this, *PP));
}


void Rule17_0_1Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
}

void Rule17_0_1Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
}

} // namespace misra
} // namespace tidy
} // namespace clang
