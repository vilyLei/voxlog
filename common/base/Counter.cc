#include <thread>
#include <chrono>
#include <iostream>
#include "Counter.h"
namespace voxlog
{
namespace common
{
namespace base
{

Counter::Counter(unsigned int count, unsigned int delayMilliseconds) :
    playable(false),
    timesCount(count),
    timeDelayMilliseconds(delayMilliseconds),
    countBreaker(nullptr)
{
}

Counter::~Counter()
{
    if (countBreaker != nullptr)
    {
        countBreaker = nullptr;
    }
}

void Counter::delayMilliseconds(unsigned int delayMilliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds > 0 ? delayMilliseconds : 1));
}

void Counter::setBreaker(std::function<bool(void)> breaker)
{
    countBreaker = breaker;
}

void Counter::play()
{
    if (!playable && timesCount > 1 && timeDelayMilliseconds > 0)
    {
        playable = true;
        while (timesCount > 1)
        {
            delayMilliseconds(timeDelayMilliseconds);
            --timesCount;

            counterCall();
            auto flag = !playable || (countBreaker != nullptr && countBreaker());
            if (flag)
                break;
        }
        playable = false;
        std::cout << std::endl;
    }
}
VOXL_INLINE void Counter::stop() noexcept
{
    playable = false;
}
VOXL_INLINE bool Counter::isPlayable() const noexcept
{
    return playable;
}

inline unsigned int Counter::getCount() const noexcept
{
    return timesCount;
}

void Counter::counterCall()
{
    auto k = getCount();
}
} // namespace base
} // namespace common
} // namespace voxlog