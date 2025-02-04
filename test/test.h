#include <deque>
#include <string>
#include <vector>
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
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
namespace NamespaceA
{
//----------------------------------------------------------------------------
namespace NamespaceB
{
//----------------------------------------------------------------------------
template<template<class> class A>
struct AA
{
//----------------------------------------------------------------------------
template<template<class> class B>
struct BB
{
//----------------------------------------------------------------------------
template<template<class> class C>
struct CC
{
//----------------------------------------------------------------------------
template<template<class> class D>
struct DD
{
//----------------------------------------------------------------------------
template<class E>
struct EE
{
  GEN_FLAGS(GEN_FLAG_OUT);
//----------------------------------------------------------------------------
  A<B<C<D<E>>>> a_;
//----------------------------------------------------------------------------
};
//----------------------------------------------------------------------------
};
//----------------------------------------------------------------------------
};
//----------------------------------------------------------------------------
};
//----------------------------------------------------------------------------
};
//----------------------------------------------------------------------------
} // namespace NamespaceA
//----------------------------------------------------------------------------
} // namespace NamespaceB
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
template<typename Container>
concept IsAContainer = requires(Container c)
{
  { c.begin()  };
  { c.end()    };
  { c.cbegin() };
  { c.cend()   };
};
//----------------------------------------------------------------------------
template<IsAContainer C>
struct StructWithTemplateSpecialization;
//----------------------------------------------------------------------------
template<>
struct StructWithTemplateSpecialization<std::vector<std::string>>
{
  GEN_FLAGS(GEN_FLAG_EQ);
};
//----------------------------------------------------------------------------
template<>
struct StructWithTemplateSpecialization<std::deque<std::string>>
{
  // no gen flags
};
//----------------------------------------------------------------------------
template<typename T, template<typename> typename C>
  requires IsAContainer<C<T>>
struct AnotherStruct
{
  GEN_FLAGS(GEN_FLAG_OUT);
};
//----------------------------------------------------------------------------