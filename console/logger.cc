
#include <assert.h>
#include <iostream>
#include "logger.h"

namespace voxlog
{
namespace console
{

ConsolePrinter   Logger::printer{};
ScopeObject Logger::scopeObject{};

void Logger::newLine() noexcept
{
    std::cout << "\n";
}

} // namespace console
} // namespace logHall