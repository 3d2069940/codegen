//----------------------------------------------------------------------------
#ifndef GENERATOR_HPP
#define GENERATOR_HPP
//----------------------------------------------------------------------------
#include <fstream>
//----------------------------------------------------------------------------
#include "common/common.hpp"
//----------------------------------------------------------------------------
class Generator
{
//----------------------------------------------------------------------------
public:
  Generator(const ParserOptions & pOpts);
//----------------------------------------------------------------------------
  void generate(const std::vector<RecordInfo> & rInfos, clang::StringRef fName) const;
//----------------------------------------------------------------------------
private:
  const ParserOptions & pOpts_;
//----------------------------------------------------------------------------
  void generateCpp(const RecordInfo & rInfo, std::ofstream & f) const;
  void generateHeader(const RecordInfo & rInfo, std::ofstream & f) const;
//----------------------------------------------------------------------------
}; // class Generator
//----------------------------------------------------------------------------
#endif // GENERATOR_HPP
//----------------------------------------------------------------------------