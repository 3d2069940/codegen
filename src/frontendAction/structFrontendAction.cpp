//----------------------------------------------------------------------------
#include <clang/Lex/PreprocessorOptions.h>
//----------------------------------------------------------------------------
#include "structFrontendAction.hpp"
#include "consumer/consumer.hpp"
//----------------------------------------------------------------------------
std::unique_ptr<clang::ASTConsumer> StructFrontendAction::CreateASTConsumer(clang::CompilerInstance & ci, clang::StringRef fileName)
{
  auto preProcOpts = ci.getPreprocessorOpts();
  preProcOpts.SingleFileParseMode = true;
  return std::make_unique<StructASTConsumer>(&ci.getASTContext(), fileName);
}
//----------------------------------------------------------------------------