#pragma once
#pragma warning(disable : 4996)
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "../../core/coreDefine.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{
class TimeDataBase
{
public:
    TimeDataBase();
    ~TimeDataBase();

    void run();
    const char* convertStr(const char* str);

private:
};

    class TimeModelBase
    {
    public:
        TimeModelBase();
        virtual ~TimeModelBase();
        void run();
    private:
        volatile int sink;

        void test01();
        void test02();
        void test03();
        void slow_motion();
    };
}

class TimeModelApp
{
public:
    TimeModelApp();
    virtual ~TimeModelApp();
    void run();
};
} // namespace model
} // namespace thread
} // namespace voxlog
