//----------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
//----------------------------------------------------------------------------
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
//----------------------------------------------------------------------------
#include "structFrontendAction.h"
//----------------------------------------------------------------------------
int main(int argc, const char **argv)
{
  llvm::cl::OptionCategory toolCategory("CodeGen options");

  auto expectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, toolCategory);
  if (!expectedParser)
  {
    llvm::errs() << expectedParser.takeError();
    return 1;
  }
  clang::tooling::ClangTool tool(expectedParser.get().getCompilations(), expectedParser.get().getSourcePathList());

  auto action = clang::tooling::newFrontendActionFactory<StructFrontendAction>();
  return tool.run(action.get());
}
//----------------------------------------------------------------------------