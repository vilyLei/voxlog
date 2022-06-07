#pragma once
#include "conditionVariableModel.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{

ConditionVariableThreadModelBase ::ConditionVariableThreadModelBase() :
    ready(false), processed(false)
{
}
ConditionVariableThreadModelBase::~ConditionVariableThreadModelBase()
{
}

void ConditionVariableThreadModelBase::worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&] { return ready; });

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

void ConditionVariableThreadModelBase::run()
{
    std::thread worker(&ConditionVariableThreadModelBase::worker_thread, this);

    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [&] { return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
}

} // namespace

ConditionVariableThreadModel::ConditionVariableThreadModel()
{

}
ConditionVariableThreadModel ::~ConditionVariableThreadModel()
{

}

void ConditionVariableThreadModel::multiThreadsTest()
{
    std::cout << "ConditionVariableThreadModel::multiThreadsTest() call begin." << std::endl;
    int         flag = 0;
    int         sign = 0;
    MutexEntity entity;
    std::condition_variable signCV;

    //using threadShellType = ThreadJoin;
    using threadShellType = ThreadDetacher;

    ConditionVariableComputer  computer0;
    std::thread               thr0(&ConditionVariableComputer::calcInt, &computer0, std::ref(sign), std::ref(entity), std::ref(signCV), 101);
    threadShellType ts0(thr0);

    ConditionVariableComputer  computer1;
    std::thread               thr1(&ConditionVariableComputer::calcInt, &computer1, std::ref(sign), std::ref(entity), std::ref(signCV), 102);
    threadShellType ts1(thr1);

    //ConditionVariableComputer  computer2;
    //std::thread               thr2(&ConditionVariableComputer::calcInt, &computer2, std::ref(sign), std::ref(entity), std::ref(signCV), 103);
    //threadShellType ts2(thr2);

    //ConditionVariableComputer computer3;
    //std::thread               thr3(&ConditionVariableComputer::calcInt, &computer3, std::ref(sign), std::ref(entity), std::ref(signCV), 104);
    //threadShellType           ts3(thr3);

    
    std::unique_lock<std::mutex> lk(entity.getMutex());
    signCV.wait(lk, [&] {
        std::cout << "wait a nodity sigal.\n";
        ++flag;
        return flag >= 3;
        });
    //std::shared_ptr<ConsoleCounter> counter = std::make_shared<ConsoleCounter>(18, 100, "Wait: ", "%");
    //counter->setBreaker([&]() -> bool {
    //    return counter->getCount() < 5 || sign == 9;
    //});
    //counter->play();

    std::cout << "sign: " << sign << std::endl;
    std::cout << "ConditionVariableThreadModel::multiThreadsTest() call end." << std::endl;
}
void ConditionVariableThreadModel::run()
{
    testMain();

    //multiThreadsTest();

    //ConditionVariableThreadModelBase cvtBase;
    //cvtBase.run();
}
} // namespace model
} // namespace thread
} // namespace voxlog