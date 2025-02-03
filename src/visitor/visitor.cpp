//----------------------------------------------------------------------------
#include <clang/AST/Comment.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/AST/RawCommentList.h>
//----------------------------------------------------------------------------
#include <llvm/Support/raw_ostream.h>
//----------------------------------------------------------------------------
#include "visitor.h"
//----------------------------------------------------------------------------
Visitor::Visitor(clang::ASTContext * context, std::shared_ptr<clang::Preprocessor> preProc) :
  context_(context),
  preProc_(preProc)
{
}
//----------------------------------------------------------------------------
bool Visitor::VisitCXXRecordDecl(clang::CXXRecordDecl * recordDecl)
{
  if ((recordDecl->isStruct() || recordDecl->isClass()) == false)
    return true;

  std::size_t genFlagsID;
  if (checkForGenFlags(recordDecl->decls_begin(), recordDecl->decls_end(), genFlagsID) == false)
    return true;

  decl_iterator declIt = recordDecl->decls_begin();
  for (std::size_t i = 0; ; ++i)
  {
    if (declIt == recordDecl->decls_end())
      break;
    if (i == genFlagsID)
    {
      auto * varDecl = clang::cast<clang::VarDecl>(*declIt);
      assert(varDecl != nullptr);
      processGenFlags(varDecl);
    }
    else if (clang::isa<clang::FieldDecl>(*declIt))
    {
      FieldInfo fInfo;
      auto * fieldDecl = clang::cast<clang::FieldDecl>(*declIt);
      assert(fieldDecl != nullptr);
      processRecordField(fieldDecl, fInfo);
    } 
    declIt++;
  }
  return true;
}
//----------------------------------------------------------------------------
bool Visitor::checkForGenFlags(decl_iterator beg, decl_iterator end, std::size_t & id) const
{
  std::size_t i = 0;
  return std::any_of(beg, end, [&](const clang::Decl * decl){
    ++i;
    if (clang::isa<clang::VarDecl>(decl) == false)
      return false;
    const auto * varDecl = clang::cast<clang::VarDecl>(decl);
    if ((varDecl->isConstexpr() && varDecl->isStaticDataMember()) == false)
      return false;
    if (varDecl->getName() != "codegenFlags_")
      return false;
    id = i - 1;
    return true;
  });
}
//----------------------------------------------------------------------------
void Visitor::processGenFlags(clang::VarDecl * decl)
{
  clang::QualType varType = decl->getType();

  if (varType->isRecordType() == false)
    return;

  const clang::RecordType * recordType = varType->getAs<clang::RecordType>();
  if (recordType == nullptr)
    return;

  clang::RecordDecl * recordDecl = recordType->getDecl();
  if (recordDecl == nullptr)
    return;

  if (clang::isa<clang::ClassTemplateSpecializationDecl>(recordDecl) == false)
    return;
  auto * specDecl = clang::cast<clang::ClassTemplateSpecializationDecl>(recordDecl);

  const auto & argList = specDecl->getTemplateArgs();
  for (std::size_t i = 0; i < argList.size(); ++i)
  {
    const clang::TemplateArgument & arg = argList[i];
    if (arg.getKind() == clang::TemplateArgument::Integral)
    {
      llvm::APInt intVal = arg.getAsIntegral();
      llvm::outs() << intVal << '\n';
    }
  }
}
//----------------------------------------------------------------------------
void Visitor::processRecordField(clang::FieldDecl * decl, FieldInfo & fInfo)
{
  fInfo.fieldName_ = decl->getNameAsString();
  fInfo.fieldType_ = decl->getType().getAsString();
}
//----------------------------------------------------------------------------
