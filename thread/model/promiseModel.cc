#include <iostream>
#include <numeric>
#include "promiseModel.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{
//PromiseModelBase

PromiseModelBase::PromiseModelBase()
{
}

PromiseModelBase::~PromiseModelBase()
{
}

void PromiseModelBase::run()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int>  numbers = {1, 2, 3, 4, 5, 6};
    std::promise<int> accumulate_promise;
    std::future<int>  accumulate_future = accumulate_promise.get_future();
    std::thread       work_thread(&PromiseModelBase::accumulate, this, numbers.begin(), numbers.end(),
                                  std::move(accumulate_promise));

    // future::get() will wait until the future has a valid result and retrieves it.
    // Calling wait() before get() is not needed
    //accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join(); // wait for thread completion

    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void>  barrier_future = barrier.get_future();
    std::thread        new_work_thread(&PromiseModelBase::do_work, this, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
    std::cout << "PromiseModelBase::run() call end.\n";
}
void PromiseModelBase::accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int>          accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum); // Notify future
}

void PromiseModelBase::do_work(std::promise<void> barrier)
{
    std::cout << "do_work() call begin.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
    std::cout << "do_work() call end.\n";
}



PromiseThreadModel::PromiseThreadModel()
{
}

PromiseThreadModel::~PromiseThreadModel()
{
}

void PromiseThreadModel::run()
{
    PromiseModelBase modelBase{};
    modelBase.run();
}

}


PromiseThreadModelApp::PromiseThreadModelApp()
{
}

PromiseThreadModelApp::~PromiseThreadModelApp()
{
}

void PromiseThreadModelApp::run()
{
    std::cout << "PromiseThreadModelApp::run() call begin." << std::endl;
    PromiseThreadModel promiseModel{};
    promiseModel.run();
    std::cout << "PromiseThreadModelApp::run() call end." << std::endl;
}

} // namespace model
} // namespace thread
} // namespace voxlog