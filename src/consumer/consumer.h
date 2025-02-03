//----------------------------------------------------------------------------
#ifndef ConsumerH
#define ConsumerH
//----------------------------------------------------------------------------
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Lex/Preprocessor.h>
//----------------------------------------------------------------------------
#include "visitor.h"
//----------------------------------------------------------------------------
class StructASTConsumer : public clang::ASTConsumer
{
public:
  explicit StructASTConsumer(clang::ASTContext * context, std::shared_ptr<clang::Preprocessor> preProc);
  virtual ~StructASTConsumer() = default;

  virtual void HandleTranslationUnit(clang::ASTContext & context) override;

private:
  clang::ASTContext * context_;
  Visitor             visitor_;
};
//----------------------------------------------------------------------------
#endif // ConsumerH
//----------------------------------------------------------------------------