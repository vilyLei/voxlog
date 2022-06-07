#pragma once
#include <string>
#include <vector>

namespace voxlog
{
namespace io
{
namespace file
{

class FileWriter
{
public:
    FileWriter();
    ~FileWriter();
    void initialize(std::string file_path, std::vector<std::string> dataList);

private:
};

class ThreadFile
{
public:
    ThreadFile();
    ~ThreadFile();
    void initialize(const std::string& file_path, const std::vector<std::string>& dataList);

private:
};

} // namespace file
} // namespace io
} // namespace voxlog