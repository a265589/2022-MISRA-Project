//===--- Rule18_7_1Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule18_7_1Check.h"
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

const char unwanted_header_name[] = "csignal";

namespace{
class PreprocessorCallbacks : public PPCallbacks{

public:
  PreprocessorCallbacks(Rule18_7_1Check &Check, Preprocessor &PP)
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
    if(FileName.equals(unwanted_header_name))
    {
      Check.csignal_included = true;
    }
  }

private:
  Rule18_7_1Check &Check;
  Preprocessor &PP;
};
} //namespace

void Rule18_7_1Check::registerPPCallbacks(
  const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) {
  PP->addPPCallbacks(
      ::std::make_unique<PreprocessorCallbacks>(*this, *PP));

}

void Rule18_7_1Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(declRefExpr(to(functionDecl(allOf(hasName("signal"),	hasParameter(0, hasType(asString("int"))), hasParameter(1, hasType(asString("__sighandler_t"))))))).bind("signal_handler"), this);
}


void Rule18_7_1Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.

  const auto *MatchedRefExpr = Result.Nodes.getNodeAs<DeclRefExpr>("signal_handler");
  if(csignal_included)
  {
    diag(MatchedRefExpr->getBeginLoc(), "The signal handling facilities of <csignal> shall not be used.")
    << FixItHint::CreateInsertion(MatchedRefExpr->getBeginLoc(),"");
  } 
}



} // namespace misra
} // namespace tidy
} // namespace clang
