//----------------------------------------------------------------------------
#ifndef CONSUMER_HPP
#define CONSUMER_HPP
//----------------------------------------------------------------------------
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Lex/Preprocessor.h>
//----------------------------------------------------------------------------
#include "visitor/visitor.hpp"
#include "generator/generator.hpp"
#include "common/common.hpp"
//----------------------------------------------------------------------------
class StructASTConsumer : public clang::ASTConsumer
{
//----------------------------------------------------------------------------
public:
  StructASTConsumer(ConsumerOptions opts);
  virtual ~StructASTConsumer() = default;

  virtual void HandleTranslationUnit(clang::ASTContext & context) override;
//----------------------------------------------------------------------------
private:
  ConsumerOptions opts_;
  Visitor         visitor_;
  Generator       generator_;
//----------------------------------------------------------------------------
}; // class StructASTConsumer
//----------------------------------------------------------------------------
#endif // CONSUMER_HPP
//----------------------------------------------------------------------------