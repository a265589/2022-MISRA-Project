//===--- Rule5_2_1Check.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule5_2_1Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {

void Rule5_2_1Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(binaryOperator(hasOperatorName("||"),
                    anyOf(hasLHS(unaryOperator()),
                          hasRHS(unaryOperator()),
                          hasLHS((binaryOperator(unless(hasOperatorName("||"))))),
                          hasRHS((binaryOperator(unless(hasOperatorName("||")))))
                         )).bind("problematic_operator")
  , this);

    Finder->addMatcher(binaryOperator(hasOperatorName("&&"),
                    anyOf(hasLHS(unaryOperator()),
                          hasRHS(unaryOperator()),
                          hasLHS((binaryOperator(unless(hasOperatorName("&&"))))),
                          hasRHS((binaryOperator(unless(hasOperatorName("&&")))))
                         )).bind("problematic_operator")
  , this);
}

void Rule5_2_1Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Matched= Result.Nodes.getNodeAs<BinaryOperator>("problematic_operator");
  diag(Matched->getOperatorLoc(), "Each operand of a logical && or || shall be a postfix-expression.");


}

} // namespace misra
} // namespace tidy
} // namespace clang
