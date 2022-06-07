#pragma once
#include <functional>
#include "../../core/coreDefine.h"
namespace voxlog
{
namespace common
{
namespace base
{
class Counter
{
public:
    explicit Counter(unsigned int count, unsigned int delayMilliseconds);
    virtual ~Counter();

    void static delayMilliseconds(unsigned int delayMilliseconds);
    /// <summary>
    /// if the breaker function return true, the counter will break;
    /// </summary>
    /// <param name="breaker"></param>
    void             setBreaker(std::function<bool(void)> breaker);
    void             play();
    VOXL_INLINE void stop() noexcept;
    VOXL_INLINE bool isPlayable() const noexcept;
    /// <summary>
    /// remaining times count
    /// </summary>
    /// <returns></returns>
    unsigned int getCount() const noexcept;

protected:
    virtual void counterCall();

private:
    bool                      playable;
    unsigned int              timesCount;
    unsigned int              timeDelayMilliseconds;
    std::function<bool(void)> countBreaker;
};

} // namespace base
} // namespace common
} // namespace voxlog