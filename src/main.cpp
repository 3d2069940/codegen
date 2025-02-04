//----------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
//----------------------------------------------------------------------------
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
//----------------------------------------------------------------------------
#include "frontendAction/structFrontendAction.hpp"
//----------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  llvm::cl::OptionCategory toolCategory("CodeGen options");
  llvm::cl::opt<std::string> outputFileStr("dir", 
                                           llvm::cl::desc("Output file. Relative path"), 
                                           llvm::cl::cat(toolCategory));

  auto expectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, toolCategory);
  if (!expectedParser)
  {
    llvm::errs() << "Couldn't create common options parser. Bruh\n";
    return 1;
  }

  clang::tooling::ClangTool tool(expectedParser.get().getCompilations(), expectedParser.get().getSourcePathList());

  auto action = clang::tooling::newFrontendActionFactory<StructFrontendAction>();
  return tool.run(action.get());
}
//----------------------------------------------------------------------------