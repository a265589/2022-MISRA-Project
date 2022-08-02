//===--- Rule16_2_4Check.h - clang-tidy -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE16_2_4CHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE16_2_4CHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace misra {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misra-rule16_2_4.html
class Rule16_2_4Check : public ClangTidyCheck {
public:
  Rule16_2_4Check(StringRef Name, ClangTidyContext *Context)
      :ClangTidyCheck(Name, Context){}
  void registerPPCallbacks(const SourceManager &SM, Preprocessor *PP, Preprocessor *ModuleExpanderPP) override;
};

} // namespace misra
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISRA_RULE16_2_4CHECK_H
