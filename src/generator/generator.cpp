//----------------------------------------------------------------------------
#include <filesystem>
//----------------------------------------------------------------------------
#include "generator.hpp"
//----------------------------------------------------------------------------
namespace
{
//----------------------------------------------------------------------------
std::string getOutputCppFilePath(const std::string & fName)
{
  std::size_t id = fName.rfind('.');
  return fName.substr(0, std::min(id, fName.length())) + "_Gen.cpp";
}
//----------------------------------------------------------------------------
std::string getOutputHeaderFilePath(const std::string & fName)
{
  std::size_t id = fName.rfind('.');
  return fName.substr(0, std::min(id, fName.length())) + "_Gen.h";
}
//----------------------------------------------------------------------------
} // namespace
//----------------------------------------------------------------------------
Generator::Generator(const ParserOptions & pOpts) :
  pOpts_(pOpts)
{
}
//----------------------------------------------------------------------------
void Generator::generate(const std::vector<RecordInfo> & rInfos, clang::StringRef fName) const
{
  const std::string           curWDir     = std::filesystem::current_path();
  const std::filesystem::path filePath    = curWDir + "/" + pOpts_.rFilePath_;
  const std::filesystem::path genFilesDir = filePath.parent_path();

  const std::string cppFPath    = getOutputCppFilePath(filePath);
  const std::string headerFPath = getOutputHeaderFilePath(filePath);

  if (std::filesystem::exists(genFilesDir) == false)
    std::filesystem::create_directories(filePath.parent_path());

  std::ofstream cppFile(cppFPath);
  std::ofstream headerFile(headerFPath);

  for (const auto & rInfo : rInfos)
  {
    generateCpp(rInfo, cppFile);
    generateHeader(rInfo, headerFile);
  }
}
//----------------------------------------------------------------------------
void Generator::generateCpp(const RecordInfo & rInfo, std::ofstream & f) const
{
  
}
//----------------------------------------------------------------------------
void Generator::generateHeader(const RecordInfo & rInfo, std::ofstream & f) const
{
  
}
//----------------------------------------------------------------------------