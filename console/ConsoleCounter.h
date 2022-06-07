#pragma once
#include <string>
#include "../common/base/Counter.h"

namespace voxlog
{
namespace console
{
using namespace voxlog::common::base;

class ConsoleCounter : public Counter
{
public:
    explicit ConsoleCounter(unsigned int count, unsigned int delayMilliseconds, const std::string info, const std::string suffix);
    virtual ~ConsoleCounter();

protected:
    virtual void counterCall() override;

private:
    const std::string printInfo;
    const std::string printSuffix;
};

} // namespace console
} // namespace voxlog