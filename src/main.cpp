//----------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
//----------------------------------------------------------------------------
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
//----------------------------------------------------------------------------
#include "frontendAction/structFrontendActionFactory.hpp"
#include "common/common.hpp"
//----------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  llvm::cl::OptionCategory toolCategory("CodeGen options");
  llvm::cl::opt<std::string> relativeFPath("relative-path",
                                           llvm::cl::desc("File path relative to the project root"),
                                           llvm::cl::cat(toolCategory));

  auto expectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, toolCategory);
  if (!expectedParser)
  {
    llvm::errs() << "Couldn't create common options parser. Bruh\n";
    return 1;
  }
  clang::tooling::ClangTool tool(expectedParser.get().getCompilations(), expectedParser.get().getSourcePathList());

  ParserOptions pOpts;
  pOpts.rFilePath_ = relativeFPath;
  StructFrontendActionFactory action(pOpts);
  return tool.run(&action);
}
//----------------------------------------------------------------------------