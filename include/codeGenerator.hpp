//----------------------------------------------------------------------------
#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP
//----------------------------------------------------------------------------
#define GEN_FLAGS(_FLAGS_) \
  const static constexpr  ::gen::GenFlags<_FLAGS_> codegenFlags_
//----------------------------------------------------------------------------
#define GEN_FLAG_EQ       ::gen::Flags::EQ
#define GEN_FLAG_OUT      ::gen::Flags::OUT
#define GEN_FLAG_HASH     ::gen::Flags::HASH
#define GEN_FLAG_LESS     ::gen::Flags::LESS
#define GEN_FLAG_JSON     ::gen::Flags::JSON
#define GEN_FLAG_FOR_EACH ::gen::Flags::FOR_EACH
//----------------------------------------------------------------------------
namespace gen
{
//----------------------------------------------------------------------------
enum Flags
{
  EQ       = 1 << 0,
  OUT      = 1 << 1,
  HASH     = 1 << 2,
  LESS     = 1 << 3,
  JSON     = 1 << 4,
  FOR_EACH = 1 << 5
};
//----------------------------------------------------------------------------
template<int Flags>
struct GenFlags
{
};
//----------------------------------------------------------------------------
template<class T>
class Hidden
{

};
//----------------------------------------------------------------------------
template<class T, class VisitorFunc>
class Variant
{

};
//----------------------------------------------------------------------------
template<class T>
class Optional
{

};
//----------------------------------------------------------------------------
} // gen
//----------------------------------------------------------------------------
#endif // CODE_GENERATOR_HPP
//----------------------------------------------------------------------------