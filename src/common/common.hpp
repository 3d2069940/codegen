//----------------------------------------------------------------------------
#include <vector>
#include <string>
//----------------------------------------------------------------------------
#include <clang/AST/Type.h>
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
struct RecordInfo
{
  GenFlags               genFlags_;
  std::vector<FieldInfo> fields_;
};
//----------------------------------------------------------------------------