//----------------------------------------------------------------------------
#ifndef GENERATOR_HPP
#define GENERATOR_HPP
//----------------------------------------------------------------------------
#include "common/common.hpp"
//----------------------------------------------------------------------------
class Generator
{
//----------------------------------------------------------------------------
public:
  static void generate(const std::vector<RecordInfo> & rInfos, clang::StringRef fName);
//----------------------------------------------------------------------------
private:
  static void generateCpp(const RecordInfo & rInfo);
  static void generateHeader(const RecordInfo & rInfo);
//----------------------------------------------------------------------------
}; // class Generator
//----------------------------------------------------------------------------
#endif // GENERATOR_HPP
//----------------------------------------------------------------------------