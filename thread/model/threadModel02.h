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

class FreeComputer
{
public:
    FreeComputer()          = default;
    virtual ~FreeComputer() = default;

    void calcInt(int& sign, MutexEntity& entity, int uuid)
    {
        int cout = 3;
        while (cout > 0)
        {

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            sign++;
            --cout;

        }
        //std::cout << "FreeComputer::calcInt() call end sign:" << sign << std::endl;
        if (sign == 3)
        {
            auto info = "[thread " + std::to_string(uuid) + "] FreeComputer::calcInt() calc sign: " + std::to_string(sign) + "\n";
            std::cout << info;
        }
    }
};

} // namespace

class SeparatedMemoryAndMutexLockThreadModel
{
public:
    SeparatedMemoryAndMutexLockThreadModel()          = default;
    virtual ~SeparatedMemoryAndMutexLockThreadModel() = default;

    void run()
    {
        multiThreadsTest();
    }

private:
    void multiThreadsTest()
    {
        std::cout << "SeparatedMemoryAndMutexLockThreadModel::multiThreadsTest() call begin." << std::endl;
        int         sign0 = 0;
        int         sign1 = 0;
        int         sign2 = 0;
        MutexEntity entity;

        //using threadShellType = ThreadJoin;
        using threadShellType = ThreadDetacher;

        FreeComputer    computer0;
        std::thread thr0(&FreeComputer::calcInt, &computer0, std::ref(sign0), std::ref(entity), 101);
        threadShellType ts0(thr0);

        FreeComputer    computer1;
        std::thread thr1(&FreeComputer::calcInt, &computer1, std::ref(sign1), std::ref(entity), 102);
        threadShellType ts1(thr1);

        FreeComputer    computer2;
        std::thread thr2(&FreeComputer::calcInt, &computer2, std::ref(sign2), std::ref(entity), 103);
        threadShellType ts2(thr2);

        std::shared_ptr<ConsoleCounter> counter = std::make_shared<ConsoleCounter>(18, 100, "Wait: ", "%");
        counter->setBreaker([&]() -> bool {
            //return counter->getCount() < 5;
            int value = sign0 + sign1 + sign2;

            return value == 9;
        });
        counter->play();

        int sign = sign0 + sign1 + sign2;
        std::cout << "sign: " << sign << std::endl;
        std::cout << "SeparatedMemoryAndMutexLockThreadModel::multiThreadsTest() call end." << std::endl;
    }
};
} // namespace model
} // namespace thread
} // namespace voxlog