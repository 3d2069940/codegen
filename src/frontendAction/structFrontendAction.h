//----------------------------------------------------------------------------
#ifndef StructFrontendActionH
#define StructFrontendActionH
//----------------------------------------------------------------------------
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
//----------------------------------------------------------------------------
class StructFrontendAction : public clang::ASTFrontendAction 
{
public:
  StructFrontendAction() = default;
  virtual ~StructFrontendAction() = default;

  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef fileName) override;
};
//----------------------------------------------------------------------------
#endif // StructFrontendActionH
//----------------------------------------------------------------------------
