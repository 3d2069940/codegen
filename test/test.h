#include <string>
#include <variant>
#include <optional>
//----------------------------------------------------------------------------
#include "include/codeGenerator.hpp"
//----------------------------------------------------------------------------
using MyVariantType = std::variant<
  int,
  char,
  std::string
>;
//----------------------------------------------------------------------------
using OptionalStr = std::optional<std::string>;
//----------------------------------------------------------------------------
inline void MyVisitor(const MyVariantType & variantType)
{
  std::visit([](auto && type){
    // do something
  }, variantType);
}
//----------------------------------------------------------------------------
using MyVisitorT = decltype(MyVisitor);
//----------------------------------------------------------------------------
template<class T>
struct StructEqHashLess
{
  GEN_FLAGS(GEN_FLAG_EQ | GEN_FLAG_HASH | GEN_FLAG_LESS);

  int                                     a_;
  char                                    b_;
  T                                       c_;
  std::string                             d_;
  gen::Hidden<std::string>                password_; // won't show in OUT
  gen::Variant<MyVariantType, MyVisitorT> variant_;
  gen::Optional<OptionalStr>              optional_;
};
//----------------------------------------------------------------------------