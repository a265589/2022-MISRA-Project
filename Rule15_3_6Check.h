//===--- Rule15_3_6Check.h - clang-tidy -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE15_3_6CHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE15_3_6CHECK_H

#include "../ClangTidyCheck.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/StmtCXX.h"

namespace clang {
namespace tidy {
namespace misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra-rule15_3_6.html
class Rule15_3_6Check : public ClangTidyCheck {
public:
  Rule15_3_6Check(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
private:
 bool getCxxRecordDecl(const clang::CXXCatchStmt* Handler,  clang::CXXRecordDecl** ptr);

};

} // namespace misra
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE15_3_6CHECK_H
