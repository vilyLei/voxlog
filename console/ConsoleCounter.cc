#pragma once
#include <iostream>
#include "ConsoleCounter.h"

namespace voxlog
{
namespace console
{

ConsoleCounter::ConsoleCounter(unsigned int count, unsigned int delayMilliseconds, const std::string info, const std::string suffix) :
    Counter(count, delayMilliseconds),
    printInfo(info),
    printSuffix(suffix)
{
}

ConsoleCounter::~ConsoleCounter()
{
}

void ConsoleCounter::counterCall()
{
    // print progress
    std::cout << "                          ";
    std::cout << "\b\r";
    //std::cout << printInfo << 1 << printSuffix;
    std::cout << printInfo << getCount() << printSuffix;
    std::cout << "\b\r";
}
} // namespace console
} // namespace voxlog