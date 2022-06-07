#include "TaskServerModel.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{
TaskServerModel::TaskServerModel(unsigned int serverUUID) noexcept
    :
    uuid(serverUUID),
    circleFlag(0)
{
}

TaskServerModel::~TaskServerModel()
{
    circleFlag = 0;
    std::cout << "TaskServerModel::deconstruct().\n";
}

void TaskServerModel::initialize()
{
}
void TaskServerModel::setUUID(unsigned int currentUUID) noexcept
{
    uuid = currentUUID;
}
unsigned int TaskServerModel::getUUID() const noexcept
{
    return uuid;
}
template <typename ThreadWrapper>
void TaskServerModel::startup(std::shared_ptr<ThreadWrapper> wrapper)
{
    //using thrWrapperType = ThreadJoin;
    //using thrWrapperType = ThreadDetacher;
    if (wrapper != nullptr)
    {
        std::cout << "TaskServerModel::startup().\n";
        circleFlag                        = 1;
        std::function<void(void)> thrFunc = std::bind(&TaskServerModel::circle, this);
        std::thread               serverCicleThr(thrFunc);
        wrapper->moveFrom(serverCicleThr);
        //thrWrapperType            thrWrapper(serverCicleThr)
    }
}
//void TaskServerModel::startup()
//{
//    //using thrWrapperType = ThreadJoin;
//    using thrWrapperType = ThreadDetacher;
//
//    circleFlag                        = 1;
//    std::function<void(void)> thrFunc = std::bind(&TaskServerModel::circle, this);
//    std::thread               serverCicleThr(thrFunc);
//    thrWrapperType            thrWrapper(serverCicleThr);
//}
void TaskServerModel::circle()
{
    while (circleFlag > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        receiveData();
        {
            //RAIITestObject              raii;
            std::lock_guard<std::mutex> lk(taskMutex);
            if (tasks.empty())
            {
                continue;
            }
            std::packaged_task<int(void)> task;
            task = std::move(tasks.front());
            tasks.pop_front();
            std::cout << "Server[" + std::to_string(uuid) + "] operate a task.\n";
            //task.s
            task();
        }
        //std::cout << "server circle end 0.\n";
    }
}

void TaskServerModel::receiveData()
{
}

template <typename Func>
std::future<int> TaskServerModel::sendTask(Func f)
{
    std::packaged_task<int(void)>  task(f);
    std::future<int>           res = task.get_future();
    std::lock_guard<std::mutex> lk(taskMutex);
    tasks.push_back(std::move(task));
    return res;
}


TaskClientModel::TaskClientModel(unsigned int clientUUID) noexcept
    :
    uuid(clientUUID),
    circleFlag(0),
    taskFlag(0),
    serverIns(nullptr)
{
}

TaskClientModel::~TaskClientModel()
{
    std::cout << "TaskClientModel::deconstruct().\n";
}
void TaskClientModel::initialize(std::shared_ptr<TaskServerModel> serverInstance)
{
    serverIns = serverInstance;
}
void TaskClientModel::setUUID(unsigned int currentUUID) noexcept
{
    uuid = currentUUID;
}
unsigned int TaskClientModel::getUUID() const noexcept
{
    return uuid;
}
template <typename ThreadWrapper>
void TaskClientModel::startup(std::shared_ptr<ThreadWrapper> wrapper)
{
    if (wrapper != nullptr && serverIns != nullptr)
    {
        std::cout << "TaskClientModel::startup().\n";
        //using thrWrapperType = ThreadJoin;
        //using thrWrapperType = ThreadDetacher;

        circleFlag                        = 1;
        std::function<void(void)> thrFunc = std::bind(&TaskClientModel::circle, this);
        std::thread               clientCicleThr(thrFunc);
        wrapper->moveFrom(clientCicleThr);
        //thrWrapperType            thrWrapper(clientCicleThr);
    }
}
//void TaskClientModel::startup()
//{
//    if (serverIns != nullptr)
//    {
//        std::cout << "TaskClientModel::startup().\n";
//        using thrWrapperType = ThreadJoin;
//        //using thrWrapperType = ThreadDetacher;
//        circleFlag                        = 1;
//        std::function<void(void)> thrFunc = std::bind(&TaskClientModel::circle, this);
//        std::thread               clientCicleThr(thrFunc);
//        thrWrapperType            thrWrapper(clientCicleThr);
//    }
//}
void TaskClientModel::circle()
{
    while (circleFlag > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
        sendData();
        //std::cout << "client call end.\n";
    }
}

void TaskClientModel::sendData()
{
    //std::cout << "TaskClientModel::sendData() begin.\n";
    //
    //responseFuture = serverIns->sendTask(ClientDataBase());
    ///*
    ClientData ct(taskFlag++, uuid);
    std::function<int(void)> taskCall = std::bind(&ClientData::calc, &ct);
    responseFuture                    = serverIns->sendTask(taskCall);

    //std::cout << "client responseFuture.valid() A: " + std::to_string(responseFuture.valid()) + ".\n";

    responseFuture.wait();
    //std::cout << "responseFuture.get(): " + std::to_string(responseFuture.get()) + ".\n";
    //std::cout << "client responseFuture.valid() B: " + std::to_string(responseFuture.valid()) + ".\n";
    //*/
    /*
    responseFuture = serverIns->sendTask([this]() -> int {
        std::cout << "call client task func" + std::to_string(taskFlag++) + ".\n";
        return 1;
    });
    responseFuture = serverIns->sendTask([this]() -> int {
        std::cout << "call client task func" + std::to_string(taskFlag++) + ".\n";
        return 2;
    });
    //*/
    //std::cout << "A responseFuture.get(): " + std::to_string(responseFuture.get()) + ".\n";
    //responseFuture.wait();
    //std::cout << "responseFuture.get(): " + std::to_string(responseFuture.get()) + ".\n";
    //std::cout << "TaskClientModel::sendData() end.\n";
}

} // namespace


TaskServerAppModel::TaskServerAppModel() :
    svrModel(nullptr),
    cltModel(nullptr)
{
}

TaskServerAppModel::~TaskServerAppModel()
{
}
void TaskServerAppModel::run()
{
    std::cout << "TaskServerAppModel::run() call begin." << std::endl;

    test01();
    //test02();

    std::cout << "TaskServerAppModel::run() call end." << std::endl;
}

void TaskServerAppModel::test01()
{

    using thrWrapperType = ThreadJoin;
    //using thrWrapperType = ThreadDetacher;

    std::thread                     thr0;
    std::thread                     thr1;
    std::shared_ptr<thrWrapperType> svrThrWapper = std::make_shared<thrWrapperType>(thr0);
    std::shared_ptr<thrWrapperType> cltThrWapper = std::make_shared<thrWrapperType>(thr1);

    std::shared_ptr<TaskServerModel> svr = std::make_shared<TaskServerModel>(2001);
    std::shared_ptr<TaskClientModel> clt = std::make_shared<TaskClientModel>(1001);
    svrModel                             = svr;
    cltModel                             = clt;

    svr->initialize();
    clt->initialize(svr);
    svr->startup(svrThrWapper);
    clt->startup(cltThrWapper);
}
void TaskServerAppModel::test02()
{

    using thrWrapperType = ThreadJoin;
    //using thrWrapperType = ThreadDetacher;

    using threadT = std::thread;

    threadT thr0([&] {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "thr0 call().\n";
        }
    });
    //thrWrapperType thrWrapper0(thr0);
    thr0.join();

    threadT thr1([&] {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "thr1 call().\n";
        }
    });
    //thrWrapperType thrWrapper1(thr1);
    thr1.join();

    //thr0.join();
    //thr1.join();
    std::cout << "TaskServerAppModel::test02() call end.\n";
}
} // namespace model
} // namespace thread
} // namespace voxlog