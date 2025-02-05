//----------------------------------------------------------------------------
#include <clang/Lex/PreprocessorOptions.h>
//----------------------------------------------------------------------------
#include "structFrontendAction.hpp"
#include "consumer/consumer.hpp"
#include "common/common.hpp"
//----------------------------------------------------------------------------
StructFrontendAction::StructFrontendAction(const ParserOptions & pOpts) :
  pOpts_(pOpts)
{
}
//----------------------------------------------------------------------------
std::unique_ptr<clang::ASTConsumer> StructFrontendAction::CreateASTConsumer(clang::CompilerInstance & cInstance, clang::StringRef fName)
{
  auto preProcOpts = cInstance.getPreprocessorOpts();
  preProcOpts.SingleFileParseMode = true;
  return std::make_unique<StructASTConsumer>(ConsumerOptions(&cInstance.getASTContext(), fName, pOpts_));
}
//----------------------------------------------------------------------------