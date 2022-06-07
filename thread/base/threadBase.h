#pragma once
#include <iostream>
#include <thread>
namespace voxlog
{
namespace thread
{
namespace base
{
class RAIITestObject
{
public:
    RAIITestObject()
    {
        std::cout << "RAIITestObject::constructor().\n";
    }
    virtual ~RAIITestObject()
    {
        std::cout << "RAIITestObject::deconstructor().\n";
    }

private:
};

class ThreadJoin
{
    std::thread& t;

public:
    explicit ThreadJoin(std::thread& thr) :
        t(thr)
    {
        if (t.joinable())
        {
            //t.join();
        }
    }
    virtual ~ThreadJoin()
    {
        std::cout << "ThreadJoin::deconstructor()." << std::endl;
        if (t.joinable())
        {
            t.join();
        }
    }
    // clang-format off
    ThreadJoin(ThreadJoin const&)				    = delete;
    ThreadJoin& operator=(ThreadJoin const&)        = delete;
    // clang-format on
    void moveFrom(std::thread& newThread) noexcept
    {
        t = std::move(newThread);
    }
};

class ThreadDetacher
{
    std::thread& t;

public:
    explicit ThreadDetacher(std::thread& thr) :
        t(thr)
    {
        if (t.joinable())
        {
            t.detach();
        }
    }
    virtual ~ThreadDetacher()
    {
        std::cout << "ThreadDetacher::deconstructor()." << std::endl;
        if (t.joinable())
        {
            t.detach();
        }
    }
    // clang-format off
    ThreadDetacher(ThreadDetacher const&)				    = delete;
    ThreadDetacher& operator=(ThreadDetacher const&)        = delete;
    // clang-format on
    void moveFrom(std::thread& newThread) noexcept
    {
        t = std::move(newThread);
    }
};

}
} // namespace thread
} // namespace voxlog