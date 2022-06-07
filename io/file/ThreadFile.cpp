#include "../../thread/base/threadBase.h"

#include "ThreadFile.h"

#include <thread>
#include <iostream>
#include <fstream>

namespace voxlog
{
namespace io
{
namespace file
{
    
using namespace voxlog::thread::base;

FileWriter::FileWriter()
{
}
FileWriter::~FileWriter()
{
}

void FileWriter::initialize(std::string filePath, std::vector<std::string> dataList)
{

    //std::vector<std::string> words{"wood", "ring", "sun"};

    std::cout << filePath + "\n ";
    std::ofstream outfile(filePath, std::ios::app);

    for (auto& info : dataList)
    {
        outfile << info;
        outfile << std::endl;
        //std::cout << "write info: " << info << std::endl;
    }
    outfile.close();

    std::cout << "write file end.\n";
}


ThreadFile::ThreadFile()
{
}

ThreadFile::~ThreadFile()
{
}

void ThreadFile::initialize(const std::string& filePath, const std::vector<std::string>& dataList)
{

    //using threadShellType = ThreadJoin;
    using threadShellType = ThreadDetacher;

    FileWriter  fWriter;
    std::thread     writeThr(&FileWriter::initialize, &fWriter, filePath, dataList);
    threadShellType tsIns(writeThr);
}

} // namespace file
} // namespace io
} // namespace voxlog