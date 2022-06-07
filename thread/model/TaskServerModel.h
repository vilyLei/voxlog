#pragma once

#include <iostream>
#include <string>
#include <future>
#include <mutex>
#include <queue>
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

struct ClientDataBase
{
public:
    ClientDataBase() = default;
    int operator() ()
    {
        std::cout << "ClientClientData::run().\n";
        return 1;
    }

private:
};
struct ClientData
{
public:
    explicit ClientData(int id, unsigned int clientUUID) :
        dataId(id),
        srcUUID(clientUUID)

    {
    }
    int calc()
    {
        auto timeNow = std::chrono::system_clock::now();
        std::cout << "Client[" + std::to_string(srcUUID) + "][id = " + std::to_string(dataId) + "]ClientData::run().\n";
        return dataId;
    }

private:
    int dataId;
    int srcUUID;
};

class TaskServerModel
{
public:
    explicit TaskServerModel(unsigned int serverUUID) noexcept;
    virtual ~TaskServerModel();

    std::mutex                             taskMutex;
    std::deque<std::packaged_task<int(void)>> tasks;

    void         initialize();
    void         setUUID(unsigned int currentUUID) noexcept;
    unsigned int getUUID() const noexcept;
    template <typename ThreadWrapper>
    void startup(std::shared_ptr<ThreadWrapper> wrapper);
    void         circle();
    template <typename Func>
    std::future<int> sendTask(Func f);

private:
    unsigned int uuid;
    unsigned int circleFlag;
    void         receiveData();
};

class TaskClientModel
{
public:
    explicit TaskClientModel(unsigned int clientUUID) noexcept;
    virtual ~TaskClientModel();

    void         initialize(std::shared_ptr<TaskServerModel> serverInstance);
    void         setUUID(unsigned int currentUUID) noexcept;
    unsigned int getUUID() const noexcept;
    template <typename ThreadWrapper>
    void         startup(std::shared_ptr<ThreadWrapper> wrapper);
    void         circle();

private:
    unsigned int uuid;
    unsigned int circleFlag;
    unsigned int taskFlag;
    std::shared_ptr<TaskServerModel>  serverIns;
    std::future<int>                 responseFuture;
    void                             sendData();
};

} // namespace
class TaskServerAppModel
{
public:
    TaskServerAppModel();
    virtual ~TaskServerAppModel();
    void run();

private:
    std::shared_ptr<TaskServerModel> svrModel;
    std::shared_ptr<TaskClientModel> cltModel;
    void test01();
    void test02();
};

} // namespace model
} // namespace thread
} // namespace voxlog