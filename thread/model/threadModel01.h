#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "../base/MutexEntity.h"
#include "../base/threadBase.h"
#include "../../console/ConsoleCounter.h"

namespace voxlog
{
namespace thread
{
namespace model
{
using namespace voxlog::thread::base;
using namespace voxlog::console;
namespace
{

struct func
{
    int& i;
    func(int& i_) :
        i(i_) {}
    void operator()()
    {
        //consoleColl(1, "func struct call");
        double t = 0.0;
        for (unsigned j = 0; j < 1000000; ++j)
        {
            // do something...
            t += std::cos(static_cast<double>(j * 0.5));
        }
    }
};


class ET
{
public:
    std::mutex& m;
    ET(std::mutex& m_) :
        m(m_)
    {
    }
    ~ET()
    {
        auto info = "[thread ET::deconstructor().\n";
        std::cout << info;
        m.unlock();
    }
};


#define METHOD 3
#define METHOD_1_1
class SharedComputer
{
public:
    SharedComputer()          = default;
    virtual ~SharedComputer() = default;

    void calcInt(int& sign, MutexEntity& entity, int uuid)
    {
        int cout = 3;
        while (cout > 0)
        {

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

#if (METHOD == 1)



            // method 1
            if (entity.try_lock())
            {
                calcSign(sign, entity);
                --cout;
            }
            else
            {
                auto info = "[thread " + std::to_string(uuid) + "] blocking\n";
                std::cout << info;
            }
#elif (METHOD == 2)
            // method 2
            std::lock_guard<std::mutex> lckg(entity.getMutex());
            sign++;
            --cout;
#else
            // method 3
            std::unique_lock<std::mutex> lckg(entity.getMutex());
            sign++;
            --cout;
           lckg.unlock();
#endif // DEBUG
            auto info1 = "[thread " + std::to_string(uuid) + "] FreeComputer::calcInt() calc cout: " + std::to_string(cout) + "\n";
            std::cout << info1;
        }
        //std::cout << "SharedComputer::calcInt() call end sign:" << sign << std::endl;
        if (sign == 9)
        {
            auto info = "\n[thread " + std::to_string(uuid) + "] FreeComputer::calcInt() calc sign: " + std::to_string(sign) + "\n";
            std::cout << info;
        }
    }

private:
    void calcSign(int& sign, MutexEntity& entity)
    {
#ifdef METHOD_1_1
        // method 1 - 1
        std::lock_guard<std::mutex> lckg(entity.getMutex(), std::adopt_lock);
        sign++;
#else
        // method 1 - 2
        sign++;
        entity.unlock();
#endif
    }
};

} // namespace

class SharedMemoryAndMutexLockThreadModel
{
public:
    SharedMemoryAndMutexLockThreadModel()          = default;
    virtual ~SharedMemoryAndMutexLockThreadModel() = default;

    void run()
    {
        multiThreadsTest();
    }

private:
    void multiThreadsTest()
    {
        std::cout << "SharedMemoryAndMutexLockThreadModel::multiThreadsTest() call begin." << std::endl;
        int         sign = 0;
        MutexEntity entity;

        //using threadShellType = ThreadJoin;
        using threadShellType = ThreadDetacher;

        SharedComputer  computer0;
        std::thread     thr0(&SharedComputer::calcInt, &computer0, std::ref(sign), std::ref(entity), 101);
        threadShellType ts0(thr0);

        SharedComputer  computer1;
        std::thread     thr1(&SharedComputer::calcInt, &computer1, std::ref(sign), std::ref(entity), 102);
        threadShellType ts1(thr1);

        SharedComputer  computer2;
        std::thread     thr2(&SharedComputer::calcInt, &computer2, std::ref(sign), std::ref(entity), 103);
        threadShellType ts2(thr2);

        std::shared_ptr<ConsoleCounter> counter = std::make_shared<ConsoleCounter>(18, 100, "Wait: ", "%");
        counter->setBreaker([&]() -> bool {
            return counter->getCount() < 5 || sign == 9;
        });
        counter->play();

        std::cout << "sign: " << sign << std::endl;
        std::cout << "SharedMemoryAndMutexLockThreadModel::multiThreadsTest() call end." << std::endl;
    }
};
} // namespace model
} // namespace thread
} // namespace voxlog