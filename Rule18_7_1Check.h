//===--- Rule18_7_1Check.h - clang-tidy -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE18_7_1CHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE18_7_1CHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra-rule18_7_1.html
class Rule18_7_1Check : public ClangTidyCheck {
public:
  Rule18_7_1Check(StringRef Name, ClangTidyContext *Context)
      :ClangTidyCheck(Name, Context), csignal_included(false) {}
  void registerPPCallbacks(const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) override;
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

  bool csignal_included;
};

} // namespace misra
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE18_7_1CHECK_H
