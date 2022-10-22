//===--- Rule15_3_5Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule15_3_5Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {

void Rule15_3_5Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  //Finder->addMatcher(varDecl(allOf(hasParent(cxxCatchStmt()), hasType(cxxRecordDecl(isStruct())))).bind("class_type_exception"), this);
  Finder->addMatcher(cxxCatchStmt().bind("catch_stmt"), this);
}

void Rule15_3_5Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Matched = Result.Nodes.getNodeAs<CXXCatchStmt>("catch_stmt");
  const auto QualifiedType = Matched->getCaughtType();
  if(!QualifiedType.isNull())
  {
     const auto *TypePtr = QualifiedType.getTypePtr();
     if( TypePtr->isStructureOrClassType()&&!TypePtr->isReferenceType()  )
       diag(Matched->getBeginLoc(), "A class type exception shall always be caught by reference.");
  }
  
  

    
}

} // namespace misra
} // namespace tidy
} // namespace clang
