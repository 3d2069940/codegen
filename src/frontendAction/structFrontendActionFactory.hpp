//----------------------------------------------------------------------------
#ifndef STRUCT_FRONTEND_ACTION_FACTORY_HPP
#define STRUCT_FRONTEND_ACTION_FACTORY_HPP
//----------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
//----------------------------------------------------------------------------
#include "common/common.hpp"
//----------------------------------------------------------------------------
class StructFrontendActionFactory : public clang::tooling::FrontendActionFactory
{
//----------------------------------------------------------------------------
public:
  StructFrontendActionFactory(const ParserOptions & pOpts);
//----------------------------------------------------------------------------
  virtual std::unique_ptr<clang::FrontendAction> create() override;
//----------------------------------------------------------------------------
private:
  const ParserOptions & pOpts_;
//----------------------------------------------------------------------------
}; // class StructFrontendActionFactory
//----------------------------------------------------------------------------
#endif // STRUCT_FRONTEND_ACTION_FACTORY_HPP
//----------------------------------------------------------------------------