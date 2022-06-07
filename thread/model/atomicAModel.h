#pragma once
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <functional>
#include <string>
#include <condition_variable>
#include <atomic>
#include "../base/MutexEntity.h"
#include "../base/threadBase.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{
struct AtomicByteStructA
{
    int one : 2;
    int two : 2;
};
class AtomicAModel
{
public:
    AtomicAModel();
    virtual ~AtomicAModel();
    void run();

private:
    void test01();
};

class ThreadYieldExample
{
public:
    ThreadYieldExample();
    virtual ~ThreadYieldExample();
    void run();

private:
    std::atomic<bool> ready;
    void              test01();
    void              test02();
    void              little_sleep(std::chrono::microseconds us);
    void              count1m(int id);
    //(false);
};
// a simple global linked list:
struct AtomicAPtrNode
{
    int   value;
    AtomicAPtrNode* next;
};

class ThreadYieldExample2
{
public:
    ThreadYieldExample2();
    virtual ~ThreadYieldExample2();
    void run();

private:

    void              append_number(int x);
    void              count1m(int id);
    void              spinLock(int n);
    void              setIntFlag(int f);
    void              printIntFlag();
    void              setIntFlag2(int f);
    void              printIntFlag2();
    void              count1m2(int id);
    void              appendOpt(int val);
    void              appendOpt2(int val);

    std::atomic<bool>            ready;                     //(false);              // can be checked without being set
    std::atomic_flag             winner = ATOMIC_FLAG_INIT; // always set when checked
    std::atomic<int>             intFlag;
    std::atomic<int>             intFlag2;
    std::atomic<bool>            ready2;
    std::atomic<bool>            winner2;
    std::atomic<AtomicAPtrNode*> list_head;
    std::atomic<AtomicAPtrNode*> list_head2;

    std::atomic_flag  lock_stream = ATOMIC_FLAG_INIT;
    std::atomic_flag  spinlock = ATOMIC_FLAG_INIT;

    std::stringstream stream;

    void              test01();
    void              test02();
    void              test03();
    void              test04();
    void              test05();
    void              test06();
    void              test07();
    void              test08();
};

}

class AtomicAModelApp
{
public:
    AtomicAModelApp();
    virtual ~AtomicAModelApp();

    void run();

private:
};


} // namespace model
} // namespace thread
} // namespace voxlog