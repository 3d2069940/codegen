//----------------------------------------------------------------------------
#include <clang/Lex/PreprocessorOptions.h>
//----------------------------------------------------------------------------
#include "structFrontendAction.h"
#include "consumer.h"
//----------------------------------------------------------------------------
std::unique_ptr<clang::ASTConsumer> StructFrontendAction::CreateASTConsumer(clang::CompilerInstance & ci, llvm::StringRef fileName)
{
  auto preProcOpts = ci.getPreprocessorOpts();
  preProcOpts.SingleFileParseMode = false;
  return std::make_unique<StructASTConsumer>(&ci.getASTContext(), ci.getPreprocessorPtr());
}
//----------------------------------------------------------------------------