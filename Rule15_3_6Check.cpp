//===--- Rule15_3_6Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule15_3_6Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/StmtCXX.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {

void Rule15_3_6Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(cxxTryStmt().bind("x"), this);
}

void Rule15_3_6Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto* TryStmt = Result.Nodes.getNodeAs<CXXTryStmt>("x");

  int HandlerNum = TryStmt->getNumHandlers();

  for(int i = HandlerNum - 1; i >= 0  ; i-- )
  {
   clang::CXXRecordDecl* A = nullptr;
    if(getCxxRecordDecl(TryStmt->getHandler(i),  &A))
    {
      for(int j = i-1; j >= 0 ; j-- )
      {
          clang::CXXRecordDecl* B = nullptr;
         if(getCxxRecordDecl(TryStmt->getHandler(j), &B) && A->isDerivedFrom(B))
          diag(TryStmt->getHandler(j)->getBeginLoc(),
          "Where multiple handlers are provided in a single try-catch statement or function-try-block"\
          "for a derived class and some or all of its bases, the handlers shall be ordered most-derived to base class.");
         
      }
    
    }

 
  } 
   
}

bool Rule15_3_6Check::getCxxRecordDecl(const clang::CXXCatchStmt* Handler,  clang::CXXRecordDecl** ptr)
{
  const auto QType = Handler->getCaughtType(); 
  if(QType.isNull())
    return false;

  const auto NonReferenceQType = QType.getNonReferenceType();
  const auto* TypePtr = NonReferenceQType.getTypePtr();

   if(TypePtr->isStructureOrClassType())
   {
    *ptr = TypePtr->getAsCXXRecordDecl();
    return true;
   }
   else
    return false;
}



} // namespace misra
} // namespace tidy
} // namespace clang
