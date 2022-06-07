#pragma once
#include <vector>
#include <future>
namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{
class PromiseModelBase
{
public:
    PromiseModelBase();
    virtual ~PromiseModelBase();


    void run();

private:
    void accumulate(std::vector<int>::iterator first,
                    std::vector<int>::iterator last,
                    std::promise<int>          accumulate_promise);

    void do_work(std::promise<void> barrier);
};

class PromiseThreadModel
{
public:
    PromiseThreadModel();
    virtual ~PromiseThreadModel();

    void run();

private:
};

}

class PromiseThreadModelApp
{
public:
    PromiseThreadModelApp();
    virtual ~PromiseThreadModelApp();

    void run();

private:
};

} // namespace model
} // namespace thread
} // namespace voxlog