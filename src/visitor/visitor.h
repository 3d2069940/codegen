//----------------------------------------------------------------------------
#ifndef VisitorH
#define VisitorH
//----------------------------------------------------------------------------
#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
//----------------------------------------------------------------------------
#include "common/common.hpp"
//----------------------------------------------------------------------------
class Visitor : public clang::RecursiveASTVisitor<Visitor>
{
public:
  explicit Visitor(clang::ASTContext * context, std::shared_ptr<clang::Preprocessor> preProc);
  virtual ~Visitor() = default;

  bool VisitCXXRecordDecl(clang::CXXRecordDecl * recordDecl);

private:
  using decl_iterator = clang::DeclContext::decl_iterator;

  clang::ASTContext                  * context_;
  std::shared_ptr<clang::Preprocessor> preProc_;

  bool checkForGenFlags(decl_iterator beg, decl_iterator end, std::size_t & id) const;

  void processGenFlags(clang::VarDecl * decl);
  void processRecordField(clang::FieldDecl * decl, FieldInfo & fInfo);
};
//----------------------------------------------------------------------------
#endif // VisitorH
//----------------------------------------------------------------------------