//----------------------------------------------------------------------------
#include "structFrontendActionFactory.hpp"
#include "structFrontendAction.hpp"
//----------------------------------------------------------------------------
StructFrontendActionFactory::StructFrontendActionFactory(const ParserOptions & pOpts) :
  pOpts_(pOpts)
{
}
//----------------------------------------------------------------------------
std::unique_ptr<clang::FrontendAction> StructFrontendActionFactory::create()
{
  return std::make_unique<StructFrontendAction>(pOpts_);
}
//----------------------------------------------------------------------------