//===--- Rule16_2_4Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule16_2_4Check.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Lexer.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {

namespace{
class PreprocessorCallbacks : public PPCallbacks{
public:
  PreprocessorCallbacks(Rule16_2_4Check &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}
  void InclusionDirective(SourceLocation HashLoc,
                          const Token &IncludeTok,
                          StringRef FileName,
                          bool IsAngled,
                          CharSourceRange FilenameRange,
                          const FileEntry *File,
                          StringRef SearchPath,
                          StringRef RelativePath,
                          const Module *Imported,
                          SrcMgr::CharacteristicKind FileType) override
  {

    StringRef::iterator it;

    for(it = FileName.begin(); it != FileName.end() ; it++)
    {
      if( *it == '\'' ||  *it == '\"')
      {
        Check.diag(HashLoc, "The \', \", /*, // characters shall not occur in a header file name.");
        break;
      }
      else if(it != FileName.end()-1 && *it == '/' && (*(it+1)  == '/' || *(it+1) == '*') )
      {
        Check.diag(HashLoc, "The \', \", /*, // characters shall not occur in a header file name.");
        break;
      }

    }



  }

private:
  Rule16_2_4Check &Check;
  Preprocessor &PP;
};
} //namespace

void Rule16_2_4Check::registerPPCallbacks(
  const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<PreprocessorCallbacks>(*this, *PP));

}


} // namespace misra
} // namespace tidy
} // namespace clang
