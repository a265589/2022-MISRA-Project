set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyMisraModule
  MisraTidyModule.cpp
  Rule15_1_3Check.cpp
  Rule15_3_5Check.cpp
  Rule16_2_4Check.cpp
  Rule16_2_5Check.cpp
  Rule18_7_1Check.cpp
  LINK_LIBS
  clangTidy
  clangTidyReadabilityModule
  clangTidyUtils

  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyMisraModule
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTooling
  )
