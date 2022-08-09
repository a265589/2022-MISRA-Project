//===--- Rule15_3_3Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule15_3_3Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"


using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {



void Rule15_3_3Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(memberExpr(allOf(hasAncestor(cxxCatchStmt()),hasDescendant(cxxThisExpr()),anyOf(hasAncestor(cxxConstructorDecl()),hasAncestor(cxxDestructorDecl())))).bind("x"), this);
  
}

void Rule15_3_3Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Matched = Result.Nodes.getNodeAs<MemberExpr>("x");
  diag(Matched->getBeginLoc(),   "Handlers of a function-try-block implementation of a class constructor destructor shall not reference non-static members from this class or its bases");
  
}

} // namespace misra
} // namespace tidy
} // namespace clang
