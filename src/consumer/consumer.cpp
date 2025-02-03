//----------------------------------------------------------------------------
#include "consumer.h"
//----------------------------------------------------------------------------
StructASTConsumer::StructASTConsumer(clang::ASTContext * context, std::shared_ptr<clang::Preprocessor> preProc) :
  context_(context),
  visitor_(context, preProc)
{
}
//----------------------------------------------------------------------------
void StructASTConsumer::HandleTranslationUnit(clang::ASTContext & context) 
{
  visitor_.TraverseDecl(context.getTranslationUnitDecl());
}
//----------------------------------------------------------------------------