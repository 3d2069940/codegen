//----------------------------------------------------------------------------
#include "consumer.hpp"
//----------------------------------------------------------------------------
StructASTConsumer::StructASTConsumer(ConsumerOptions opts) :
  opts_(std::move(opts)),
  visitor_(opts_.context_, opts_.pOpts_),
  generator_(opts_.pOpts_)
{
}
//----------------------------------------------------------------------------
void StructASTConsumer::HandleTranslationUnit(clang::ASTContext & context) 
{
  visitor_.TraverseDecl(context.getTranslationUnitDecl());
  generator_.generate(visitor_.getRecordInfos(), opts_.fName_);
}
//----------------------------------------------------------------------------