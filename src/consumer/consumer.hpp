//----------------------------------------------------------------------------
#ifndef CONSUMER_HPP
#define CONSUMER_HPP
//----------------------------------------------------------------------------
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Lex/Preprocessor.h>
//----------------------------------------------------------------------------
#include "visitor/visitor.hpp"
//----------------------------------------------------------------------------
class StructASTConsumer : public clang::ASTConsumer
{
public:
  explicit StructASTConsumer(clang::ASTContext * context, clang::StringRef fileName);
  virtual ~StructASTConsumer() = default;

  virtual void HandleTranslationUnit(clang::ASTContext & context) override;

private:
  Visitor             visitor_;
  std::string         fileName_;
  clang::ASTContext * context_;
};
//----------------------------------------------------------------------------
#endif // CONSUMER_HPP
//----------------------------------------------------------------------------