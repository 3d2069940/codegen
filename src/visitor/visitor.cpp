//----------------------------------------------------------------------------
#include <clang/AST/Comment.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/AST/RawCommentList.h>
//----------------------------------------------------------------------------
#include <llvm/Support/raw_ostream.h>
//----------------------------------------------------------------------------
#include "visitor.hpp"
//----------------------------------------------------------------------------
Visitor::Visitor(clang::ASTContext * context) :
  context_(context)
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

  RecordInfo rInfo;
  rInfo.typeStr_ = recordDecl->getNameAsString();
  
  getQualifiedNameWithTemplates(recordDecl->getDeclContext(), rInfo);

  decl_iterator declIt = recordDecl->decls_begin();
  for (std::size_t i = 0; ; ++i)
  {
    FieldInfo fInfo;
    if (declIt == recordDecl->decls_end())
      break;
    if (i == genFlagsID)
    {
      auto * varDecl = clang::cast<clang::VarDecl>(*declIt);
      assert(varDecl != nullptr);
      processGenFlags(varDecl, rInfo.genFlags_);
    }
    else if (clang::isa<clang::FieldDecl>(*declIt))
    {
      auto * fieldDecl = clang::cast<clang::FieldDecl>(*declIt);
      assert(fieldDecl != nullptr);
      processRecordField(fieldDecl, fInfo);
      rInfo.fields_.emplace_back(std::move(fInfo));
    } 
    declIt++;
  }
  rInfos_.emplace_back(std::move(rInfo));
  return true;
}
//----------------------------------------------------------------------------
std::vector<RecordInfo> Visitor::getRecordInfos() const
{
  return rInfos_;
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
void Visitor::getQualifiedNameWithTemplates(clang::DeclContext * context, RecordInfo & rInfo) const
{
  if (context == nullptr)
    return;

  while (context)
  {
    if (clang::isa<clang::NamespaceDecl>(context))
    {
      const auto * namespaceDecl = clang::cast<clang::NamespaceDecl>(context);
      rInfo.qualName_.emplace(std::move(namespaceDecl->getNameAsString()));
    }
    else if (clang::isa<clang::CXXRecordDecl>(context))
    {
      const auto * cxxRecordDecl  = clang::cast<clang::CXXRecordDecl>(context);
      const auto * templateDecl   = cxxRecordDecl->getDescribedClassTemplate();
      std::string  templateStr    = "template<";
      std::string  kindAndNameStr = getCXXRecordKindStr(cxxRecordDecl) + " " + cxxRecordDecl->getNameAsString();
      processTemplateParams(templateDecl->getTemplateParameters(), templateStr);
      rInfo.qualName_.emplace(std::move(kindAndNameStr));
      rInfo.qualName_.emplace(std::move(templateStr));
    }
    context = context->getParent();
  }
}
//----------------------------------------------------------------------------
void Visitor::processTemplateParams(const clang::TemplateParameterList * paramList, std::string & templateStr) const
{
  if (paramList == nullptr)
    return;

  for (const auto * param : *paramList)
  {
    if (clang::isa<clang::TemplateTypeParmDecl>(param))
    {
      const auto * templateDecl = clang::cast<clang::TemplateTypeParmDecl>(param);
      templateStr += "typename" + templateDecl->getNameAsString();
    }
    else if (clang::isa<clang::TemplateTemplateParmDecl>(param))
    {
      const auto * templateTemplateDecl = clang::cast<clang::TemplateTemplateParmDecl>(param);
      templateStr += "template<";
      processTemplateParams(templateTemplateDecl->getTemplateParameters(), templateStr);
      templateStr += "> typename " + templateTemplateDecl->getNameAsString() + ">";
    }
  }
}
//----------------------------------------------------------------------------
void Visitor::processGenFlags(clang::VarDecl * decl, GenFlags & gFlags) const
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
      gFlags.eq_      = intVal[0];
      gFlags.out_     = intVal[1];
      gFlags.hash_    = intVal[2];
      gFlags.less_    = intVal[3];
      gFlags.json_    = intVal[4];
      gFlags.forEach_ = intVal[5];
    }
  }
}
//----------------------------------------------------------------------------
void Visitor::processRecordField(clang::FieldDecl * decl, FieldInfo & fInfo) const
{
  fInfo.fieldName_ = decl->getNameAsString();
  fInfo.fieldType_ = decl->getType();
}
//----------------------------------------------------------------------------
std::string Visitor::getCXXRecordKindStr(const clang::CXXRecordDecl * decl) const
{
  if (decl->isStruct())
    return "struct";
  if (decl->isUnion())
    return "union";
  if (decl->isClass())
    return "class";
  return "";
}
//----------------------------------------------------------------------------
