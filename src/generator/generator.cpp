//----------------------------------------------------------------------------
#include "generator.hpp"
#include "common/common.hpp"
//----------------------------------------------------------------------------
void Generator::generate(const std::vector<RecordInfo> & rInfos, clang::StringRef fName)
{
  for (const auto & rInfo : rInfos)
  {
    generateCpp(rInfo);
    generateHeader(rInfo);
  }
}
//----------------------------------------------------------------------------
void Generator::generateCpp(const RecordInfo & rInfo)
{
  
}
//----------------------------------------------------------------------------
void Generator::generateHeader(const RecordInfo & rInfo)
{

}
//----------------------------------------------------------------------------