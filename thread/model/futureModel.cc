#include "futureModel.h"

namespace voxlog
{
namespace thread
{
namespace model
{

namespace
{

    
SharedFutureBase::SharedFutureBase()
{
}
SharedFutureBase::~SharedFutureBase()
{
}
void SharedFutureBase::run()
{
    test01();
}
void SharedFutureBase::test01()
{
    std::promise<void>       ready_promise, t1_ready_promise, t2_ready_promise;
    //std::shared_future<void> ready_future(ready_promise.get_future());    // ok
    std::shared_future<void> ready_future(ready_promise.get_future().share());

    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli> {
        t1_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };


    auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli> {
        t2_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };

    auto fut1 = t1_ready_promise.get_future();
    auto fut2 = t2_ready_promise.get_future();

    auto result1 = std::async(std::launch::async, fun1);
    auto result2 = std::async(std::launch::async, fun2);

    // wait for the threads to become ready
    fut1.wait();
    fut2.wait();

    // the threads are ready, start the clock
    start = std::chrono::high_resolution_clock::now();

    // signal the threads to go
    ready_promise.set_value();

    std::cout << "Thread 1 received the signal "
              << result1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << result2.get().count() << " ms after start\n";
}
void SharedFutureBase::test02()
{
}

FutureBase::FutureBase()
{
}
FutureBase ::~FutureBase()
{
}
// count down taking a second for each value:
int FutureBase::countdown(int from, int to)
{
    for (int i = from; i != to; --i)
    {
        std::cout << i << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Lift off!\n";
    return from - to;
}
void FutureBase::test01()
{
    // future from a packaged_task
    std::packaged_task<int(void)> task([] { return 7; }); // wrap the function
    std::future<int>              f1 = task.get_future(); // get a future
    std::thread                   t(std::move(task));     // launch on a thread
    //std::function<std::packaged_task<int(void)>> taskFunction{std::move(task)};
    //std::thread               t(std::move(task));     // launch on a thread

    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, [] { return 8; });
    //task();
    // future from a promise
    std::promise<int> p;
    std::future<int>  f3 = p.get_future();
    std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    t.join();
}

void FutureBase::test02()
{
    //std::packaged_task<int(int, int)> tsk([this](int a, int b) -> int { return countdown(a, b); }); // set up packaged_task
    std::packaged_task<int(int, int)> tsk(std::bind(&FutureBase::countdown, this, std::placeholders::_1, std::placeholders::_2)); // set up packaged_task
    std::future<int>                  ret = tsk.get_future();      // get future

    std::thread th(std::move(tsk), 10, 0); // spawn thread to count down from 10 to 0

    // ...

    int value = ret.get(); // wait for the task to finish and get result

    std::cout << "The countdown lasted for " << value << " seconds.\n";

    th.join();
}
void FutureBase::run()
{
    test01();
    //test02();
    //std::future<void> f2(std::packaged_task<void()>);
    //auto              fut = f2((std::packaged_task<void()>)[]{});
}
} // namespace

FutureThreadModel::FutureThreadModel()
{
}
FutureThreadModel::~FutureThreadModel()
{
}
void FutureThreadModel::run()
{
    std::cout << "FutureThreadModel::run() call begin." << std::endl;

    //FutureBase model;
    SharedFutureBase model;
    model.run();


    std::cout << "FutureThreadModel::run() call end." << std::endl;
}
} // namespace model
} // namespace thread
} // namespace voxlog