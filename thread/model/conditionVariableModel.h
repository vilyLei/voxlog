#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
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
using namespace voxlog::thread::base;
namespace
{
class ConditionVariableThreadModelBase
{
public:
    ConditionVariableThreadModelBase();
    virtual ~ConditionVariableThreadModelBase();

    std::mutex              m;
    std::condition_variable cv;
    std::string             data;
    bool                    ready;
    bool                    processed;

    void worker_thread();

    void run();

private:
};
std::condition_variable cv;
std::mutex              cv_m; // This mutex is used for three purposes:
                              // 1) to synchronize accesses to i
                              // 2) to synchronize accesses to std::cerr
                              // 3) for the condition variable cv
int i = 0;
class TestDD
{
public:
    TestDD() = default;
    ~TestDD()
    {
        std::cerr << "TestDD::deconstrutor()...\n";
    }
};
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, [] {
        std::cout << "waits does...\n";
        return i == 1;

        });
    std::cerr << "...finished waiting. i == 1\n";
}

void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        TestDD                      tdd;
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
        // 作用域可以让 lk析构完成
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk2(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}

int testMain()
{
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return EXIT_SUCCESS;
}

class ConditionVariableComputer
{
public:
    ConditionVariableComputer()          = default;
    virtual ~ConditionVariableComputer() = default;

    void calcInt(int& sign, MutexEntity& entity, std::condition_variable& signCV, int uuid)
    {
        int cout = 6;
        while (cout > 0)
        {

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // method 3
            std::unique_lock<std::mutex> lckg(entity.getMutex());
            sign++;
            --cout;
            lckg.unlock();
            auto info1 = "[thread " + std::to_string(uuid) + "] FreeComputer::calcInt() calc cout: " + std::to_string(cout) + "\n";
            std::cout << info1;
        }
        auto info01 = "          [thread " + std::to_string(uuid) + "]SharedComputer::calcInt() call end cout : " + std::to_string(cout) + "\n";
        std::cout << info01;
        //if (sign == 9)
        //{
        //    auto info = "\n[thread " + std::to_string(uuid) + "] FreeComputer::calcInt() calc sign: " + std::to_string(sign) + "\n";
        //    std::cout << info;
        //}
        std::unique_lock<std::mutex> lckg(entity.getMutex());
        // 可能存在signCV已经被销毁了
        signCV.notify_one();
    }

private:
};

} // namespace
class ConditionVariableThreadModel
{
public:
    ConditionVariableThreadModel();
    virtual ~ConditionVariableThreadModel();

    void run();

private:
    void multiThreadsTest();
};
} // namespace model
} // namespace thread
} // namespace voxlog