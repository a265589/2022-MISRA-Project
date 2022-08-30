//===--- Rule16_0_6Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule16_0_6Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/Token.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {


class PreprocessorCallbacks : public PPCallbacks{

public:
  PreprocessorCallbacks(Rule16_0_6Check &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}

  void MacroDefined (const Token &MacroNameTok, const MacroDirective *MD) override
  {
 
   auto *MacroInfo =  MD->getMacroInfo();


   if(MacroInfo->isFunctionLike() &&  !MacroInfo->param_empty())
   {
      llvm::SmallString<128> SpellingBuffer;

      for (const auto *para : MacroInfo->params()) {


        int tokenNum = MacroInfo->getNumTokens ();
        auto token_ptr = MacroInfo->tokens_begin ();
        bool error_flag = false;
        for (int i = 1; i < tokenNum; i++) {
          auto cur = PP.getSpelling(*(token_ptr+i), SpellingBuffer);


          if(cur.equals(para->getName()))
          {
            if(i < tokenNum -1 )
            {
             auto next = PP.getSpelling(*(token_ptr+i+1), SpellingBuffer);
             
             if(!next.equals(")")&&!next.equals("#")&&!next.equals("##"))
              error_flag = true;

            }

            if( i > 0 )
            {
              auto prev = PP.getSpelling(*(token_ptr+i-1), SpellingBuffer);
              if(!prev.equals("(")&&!prev.equals("#")&&!prev.equals("##"))
               error_flag = true;
            }
            
          }
          if(error_flag)
          {
            auto loc = (*(token_ptr+i)).getLocation();
            Check.diag(loc, "In the definition of a function-like macro, each instance of a parameter shall be enclosed in parentheses, unless it is used as the operand of # or ##.");
            error_flag = false;
          }

          
        } 
      } 






   }

  }
private:
  Rule16_0_6Check &Check;
  Preprocessor &PP;
};

void Rule16_0_6Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
}


void Rule16_0_6Check::registerPPCallbacks(const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<PreprocessorCallbacks>(*this, *PP));

}

void Rule16_0_6Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
}

} // namespace misra
} // namespace tidy
} // namespace clang
