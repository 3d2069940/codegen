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
  llvm::outs() << "Processing [" << fileName_ << "] now...\n";
  visitor_.TraverseDecl(context.getTranslationUnitDecl());
  llvm::outs() << "Processing done. Now generating stuff\n";
  generator_.generate(visitor_.getRecordInfos(), fileName_);
  llvm::outs() << "Generating for [" << fileName_ << "] is done\n";
}
//----------------------------------------------------------------------------