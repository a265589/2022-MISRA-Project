//===--- Rule15_1_3Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule15_1_3Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {

void Rule15_1_3Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(cxxThrowExpr(unless(hasAncestor(cxxCatchStmt()))).bind("throw_expr"), this);
}

void Rule15_1_3Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedExpr = Result.Nodes.getNodeAs<CXXThrowExpr>("throw_expr");
  if(!MatchedExpr->getSubExpr())
  {
    diag(MatchedExpr->getBeginLoc(), "An empty throw (throw;) shall only be used in the compound-statement of a catch handler.")
    << FixItHint::CreateInsertion(MatchedExpr->getThrowLoc(),"");
  } 

 
}

} // namespace misra
} // namespace tidy
} // namespace clang
