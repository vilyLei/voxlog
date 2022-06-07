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

class SharedFutureBase
{
public:
    SharedFutureBase();
    ~SharedFutureBase();

    void run();

private:
    void test01();
    void test02();
};
class FutureBase
{
public:
    FutureBase();
    ~FutureBase();

    void run();


    std::function<int(int)> function01;

private:
    int countdown(int from, int to);
    void test01();
    void test02();
};
}

class FutureThreadModel
{
public:
    FutureThreadModel();
    virtual ~FutureThreadModel();

    void run();

private:

};

} // namespace model
} // namespace thread
} // namespace voxlog