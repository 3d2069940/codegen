//----------------------------------------------------------------------------
#ifndef STRUCT_FRONTEND_ACTION_HPP
#define STRUCT_FRONTEND_ACTION_HPP
//----------------------------------------------------------------------------
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
//----------------------------------------------------------------------------
#include <clang/Lex/Preprocessor.h>
//----------------------------------------------------------------------------
#include "common/common.hpp"
//----------------------------------------------------------------------------
class StructFrontendAction : public clang::ASTFrontendAction 
{
//----------------------------------------------------------------------------
public:
  StructFrontendAction(const ParserOptions & pOpts);
  virtual ~StructFrontendAction() = default;

  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance & cInstance, clang::StringRef fName) override;
//----------------------------------------------------------------------------
private:
  const ParserOptions & pOpts_;
//----------------------------------------------------------------------------
}; // class StructFrontendAction
//----------------------------------------------------------------------------
#endif // STRUCT_FRONTEND_ACTION_HPP
//----------------------------------------------------------------------------
