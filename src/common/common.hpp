//----------------------------------------------------------------------------
#ifndef COMMON_HPP
#define COMMON_HPP
//----------------------------------------------------------------------------
#include <stack>
#include <vector>
#include <string>
//----------------------------------------------------------------------------
#include <clang/AST/Type.h>
//----------------------------------------------------------------------------
struct ParserOptions
{
  std::string rFilePath_;
};
//----------------------------------------------------------------------------
struct ConsumerOptions
{
  clang::ASTContext   * context_;
  const ParserOptions & pOpts_;
  std::string           fName_;

  ConsumerOptions(clang::ASTContext * context, clang::StringRef fName, const ParserOptions & pOpts) :
    context_(context),
    pOpts_(pOpts),
    fName_(fName)
  {
  }
};
//----------------------------------------------------------------------------
struct GenFlags
{
  bool eq_;
  bool out_;
  bool hash_;
  bool less_;
  bool json_;
  bool forEach_;

  GenFlags() :
    eq_(false),
    out_(false),
    hash_(false),
    less_(false),
    json_(false),
    forEach_(false)
  {
  }
};
//----------------------------------------------------------------------------
struct FieldInfo
{
  std::string     fieldName_;
  clang::QualType fieldType_;
};
//----------------------------------------------------------------------------
enum class RecordType
{
  Struct,
  Class,
  Union,
  Namespace,
  Unknown
};
//----------------------------------------------------------------------------
struct QualNameInfo
{
  RecordType  type_;
  std::string templateStr_;
  std::string name_;
};
//----------------------------------------------------------------------------
struct RecordInfo
{
  std::string              typeStr_;
  std::stack<QualNameInfo> qualName_;
  GenFlags                 genFlags_;
  std::vector<FieldInfo>   fields_;
};
//----------------------------------------------------------------------------
#endif // COMMON_HPP
//----------------------------------------------------------------------------