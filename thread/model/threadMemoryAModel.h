#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <functional>
#include <string>
#include <condition_variable>
#include "../base/MutexEntity.h"
#include "../base/threadBase.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{
struct ByteStructA
{
    int one : 2;
    int two : 2;
};
class ThreadMemoryAModel
{
public:
    ThreadMemoryAModel();
    virtual ~ThreadMemoryAModel();
    void run();

private:
    void test01();
};


}

class ThreadMemoryAModelApp
{
public:
    ThreadMemoryAModelApp();
    virtual ~ThreadMemoryAModelApp();

    void run();

private:
};


} // namespace model
} // namespace thread
} // namespace voxlog