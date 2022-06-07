#include "SimpleFile.h"
#include "ThreadFile.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <thread>
#include <chrono>         // std::chrono::seconds

namespace voxlog
{
namespace io
{
namespace file
{
SimpleFile::SimpleFile()
{
}
SimpleFile::~SimpleFile()
{
}
void SimpleFile::test()
{
    std::cout << "\nSimpleFile::test() call begin.\n"
              << std::endl;
    
    std::string       fileSuffx   = ".txt";
    std::string       fileBaseDir = "d:\\res\\project\\";
    std::string       input_fileName = "hello";
    std::string       output_fileName = "hello_out";

    ///*

    std::vector<std::string> words0{"wood0", "ring0", "sun0"};    
    std::string fileName0 = "file0";
    ThreadFile thrFile0;
    thrFile0.initialize(fileBaseDir + fileName0 + fileSuffx, words0);

    
    std::vector<std::string> words1{"wood1", "ring1", "sun1"};
    std::string              fileName1 = "file1";
    ThreadFile               thrFile1;
    thrFile1.initialize(fileBaseDir + fileName1 + fileSuffx, words1);

    
    std::vector<std::string> words2{"wood2", "ring2", "sun2"};
    std::string              fileName2 = "file2";
    ThreadFile               thrFile2;
    thrFile2.initialize(fileBaseDir + fileName2 + fileSuffx, words2);
    //*/
    /*
    std::ifstream input_file(fileBaseDir + input_fileName + fileSuffx);
    std::ofstream outfile(fileBaseDir + output_fileName + fileSuffx, std::ios::app);
    std::string   lineString;

    if (input_file.is_open())
    {
        std::cout << "成功打开文件" << std::endl;
    }
    else
    {
        std::cout << "未成功打开文件" << std::endl;
    }
    std::vector<std::string> words{"wood", "ring", "sun"};

    //for (auto& it : words)
    //{
    //    std::cout << "getline info: " << it << std::endl;
    //    outfile << it;
    //    outfile << std::endl;
    //}

    std::for_each(words.cbegin(), words.cend(), [](std::string word) {
        std::cout << "word info: " << word << std::endl;
        });

    for (std::vector<std::string>::const_iterator it = words.cbegin(); it != words.cend(); it++)
    {
         auto& word = *it;
        std::cout << "getline info: " << word << std::endl;
         outfile << word;
        outfile << std::endl;
    }

    //while (getline(myfile, lineString))
    //{
    //    outfile << lineString;
    //    outfile << std::endl;
    //    std::cout << "getline info: " << lineString << std::endl;
    //}
    input_file.close();
    outfile.close();
    //*/

    int count = 17;
    while (count > 1)
    {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        --count;
        // print progress
        std::cout << "             ";
        std::cout << "\b\r";
        std::cout << "count: " << count << "%";
        //std::cout << "\b\r";
        std::cout << "\b\r";
    }
    std::cout << "SimpleFile::test() call  end." << std::endl;
}
} // namespace file
} // namespace io
} // namespace voxlog