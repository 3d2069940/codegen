//----------------------------------------------------------------------------
#include "consumer.hpp"
//----------------------------------------------------------------------------
StructASTConsumer::StructASTConsumer(clang::ASTContext * context, clang::StringRef fileName) :
  visitor_(context),
  fileName_(fileName),
  context_(context)
{
}
//----------------------------------------------------------------------------
void StructASTConsumer::HandleTranslationUnit(clang::ASTContext & context) 
{
  visitor_.TraverseDecl(context.getTranslationUnitDecl());
}
//----------------------------------------------------------------------------