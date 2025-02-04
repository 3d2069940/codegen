//----------------------------------------------------------------------------
#ifndef VISITOR_HPP
#define VISITOR_HPP
//----------------------------------------------------------------------------
#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
//----------------------------------------------------------------------------
#include "common/common.hpp"
//----------------------------------------------------------------------------
class Visitor : public clang::RecursiveASTVisitor<Visitor>
{
//----------------------------------------------------------------------------
public:
  explicit Visitor(clang::ASTContext * context);
  virtual ~Visitor() = default;
//----------------------------------------------------------------------------
  bool VisitCXXRecordDecl(clang::CXXRecordDecl * recordDecl);

  std::vector<RecordInfo> getRecordInfos() const;
//----------------------------------------------------------------------------
private:
  using decl_iterator = clang::DeclContext::decl_iterator;
//----------------------------------------------------------------------------
  clang::ASTContext     * context_;
  std::vector<RecordInfo> rInfos_;
//----------------------------------------------------------------------------
  bool checkForGenFlags(decl_iterator beg, decl_iterator end, std::size_t & id) const;

  void getQualifiedNameWithTemplates(clang::DeclContext * context, RecordInfo & rInfo) const;

  void processTemplateParams(const clang::TemplateParameterList * paramList, std::string & templateStr) const;
  void processGenFlags(clang::VarDecl * decl, GenFlags & gFlags) const;
  void processRecordField(clang::FieldDecl * decl, FieldInfo & fInfo) const;

  std::string getCXXRecordKindStr(const clang::CXXRecordDecl * decl) const;
//----------------------------------------------------------------------------
}; // class Visitor
//----------------------------------------------------------------------------
#endif // VISITOR_HPP
//----------------------------------------------------------------------------