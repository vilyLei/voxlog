#pragma once
#include <mutex>

namespace voxlog
{
namespace thread
{
namespace base
{

class MutexEntity
{
public:
    MutexEntity()          = default;
    virtual ~MutexEntity() = default;

    inline void lock()
    {
        currentMutex.lock();
    }
    std::mutex& getMutex()
    {
        return currentMutex;
    }
    inline bool try_lock()
    {
        return currentMutex.try_lock();
    }
    inline void unlock()
    {
        currentMutex.unlock();
    }

private:
    std::mutex currentMutex;
};

} // namespace base
} // namespace thread
} // namespace voxlog