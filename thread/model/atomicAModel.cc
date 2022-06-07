#include "atomicAModel.h"
#include "../../console/consoleScope.h";
namespace voxlog
{
namespace thread
{
namespace model
{

using namespace voxlog::console;

namespace
{

ThreadYieldExample::ThreadYieldExample() :
    ready(false)
{
}
ThreadYieldExample::~ThreadYieldExample()
{
}
void ThreadYieldExample::count1m(int id)
{
    while (!ready)
    { // wait until main() sets ready...
        std::this_thread::yield();
    }
    for (volatile int i = 0; i < 1000000000; ++i) {}
    std::string info = std::to_string(id) + ",";
    std::cout << info;
    //std::cout << id;
}
void ThreadYieldExample::test01()
{
    std::thread threads[10];
    std::cout << "race of 10 threads that count to 1 million:\n";
    for (int i = 0; i < 10; ++i) threads[i] = std::thread(&ThreadYieldExample::count1m, this, i);
    ready = true; // go!
    std::cout << "the ready value is true.\n";
    for (auto& th : threads) th.join();
    std::cout << '\n';
}
void ThreadYieldExample::little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end   = start + us;
    do {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
}
void ThreadYieldExample::test02()
{
    auto start = std::chrono::high_resolution_clock::now();

    little_sleep(std::chrono::microseconds(100));

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
              << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
}
void ThreadYieldExample::run()
{
    //test01();
    test02();
}

ThreadYieldExample2::ThreadYieldExample2():
    ready(false), intFlag(0), intFlag2(0), ready2(false), winner2(false), list_head(nullptr), list_head2(nullptr)
{
}

ThreadYieldExample2::~ThreadYieldExample2() 
{
}


void ThreadYieldExample2::count1m(int id)
{
    while (!ready)
    {
        std::this_thread::yield(); // 将当前线程抢到的执行时间片让给其他线程，相当于自身处于等待状态
    }                              // 等待主线程中设置 ready 为 true.

    for (int i = 0; i < 10000000; ++i)
    {
    } // 计数

    // 如果某个线程率先执行完上面的计数过程，则输出自己的 ID.
    // 此后其他线程执行 test_and_set 是 if 语句判断为 false，
    // 因此不会输出自身 ID.
    if (!winner.test_and_set())
    {
        std::string info = "thread #" + std::to_string(id) + " won!\n";
        std::cout << info;
    }
    else
    {
        std::string info = "winner is to be set!\n";
        std::cout << info;
    }
}

void ThreadYieldExample2::test01()
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(&ThreadYieldExample2::count1m, this, i));
    ready = true;

    for (auto& th : threads)
        th.join();
    //
    //std::cout << stream.str() << std::endl;
}

void ThreadYieldExample2::append_number(int x)
{
    while (lock_stream.test_and_set())
    {
    }
    stream << "thread #" << x << '\n';
    lock_stream.clear();
}
void ThreadYieldExample2::test02()
{
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(&ThreadYieldExample2::append_number, this, i));
    for (auto& th : threads)
        th.join();

    std::cout << stream.str() << std::endl;
}

void ThreadYieldExample2::spinLock(int n)
{
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        while (spinlock.test_and_set(std::memory_order_acquire)) // acquire lock
        {};                                                      
        // spin
        std::string info = "Output from thread " + std::to_string(n) + "\n";
        std::cout << info;
        spinlock.clear(std::memory_order_release); // release lock
    }
}
void ThreadYieldExample2::test03()
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n)
    {
        v.emplace_back(&ThreadYieldExample2::spinLock, this, n);
    }
    for (auto& t : v)
    {
        t.join();
    }
}
void ThreadYieldExample2::setIntFlag(int f)
{
    int a = intFlag;
    std::cout << "setIntFlag begin flag: " + std::to_string(intFlag) + "\n";
    intFlag = f;
    int b  = intFlag;
    std::cout << "setIntFlag end a: " + std::to_string(a) + ", b: " + std::to_string(b) + "\n";
}
void ThreadYieldExample2::printIntFlag()
{
    while (intFlag == 0)
    { // wait while foo == 0
        std::this_thread::yield();
    }
    std::cout << "flag: " + std::to_string(intFlag) + "\n";
}
void ThreadYieldExample2::test04()
{
    std::thread first(&ThreadYieldExample2::printIntFlag, this);
    std::thread second(&ThreadYieldExample2::setIntFlag, this, 10);
    first.join();
    second.join();
}

void ThreadYieldExample2::setIntFlag2(int f)
{

    int a = intFlag2;
    std::cout << "setIntFlag2 begin flag: " + std::to_string(intFlag) + "\n";
    intFlag2.store(f, std::memory_order_relaxed);   // 设置(store) 原子对象 flag 的值
    int b = intFlag2;
    std::cout << "setIntFlag2 end a: " + std::to_string(a) + ", b: " + std::to_string(b) + "\n";

}
void ThreadYieldExample2::printIntFlag2()
{
    int x;
    do {
        x = intFlag2.load(std::memory_order_relaxed); // 读取(load) 原子对象 flag 的值
    } while (x == 0);
    std::cout << "flag2: " + std::to_string(intFlag2) + "\n";
}
void ThreadYieldExample2::test05()
{
    std::thread first(&ThreadYieldExample2::printIntFlag2, this);
    std::thread second(&ThreadYieldExample2::setIntFlag2, this, 10);
    first.join();
    second.join();
}

void ThreadYieldExample2::count1m2(int id)
{
    while (!ready2) {}                    // wait for the ready signal
    for (int i = 0; i < 1000000; ++i) {} // go!, count to 1 million
    if (!winner2.exchange(true)) {
        std::cout << "thread #" + std::to_string(id) + " won!\n";
    }
};

void ThreadYieldExample2::test06()
{
    std::vector<std::thread> threads;
    std::cout << "test06: spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(&ThreadYieldExample2::count1m2, this, i));
    ready2 = true;
    for (auto& th : threads) th.join();
}
void ThreadYieldExample2::appendOpt(int val)
{ // append an element to the list
    AtomicAPtrNode* oldHead = list_head;
    AtomicAPtrNode* newNode = new AtomicAPtrNode{val, oldHead};

    // what follows is equivalent to: list_head = newNode, but in a thread-safe way:
    while (!list_head.compare_exchange_weak(oldHead, newNode))
        newNode->next = oldHead;
}

void ThreadYieldExample2::test07()
{
    // spawn 10 threads to fill the linked list:
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) threads.push_back(std::thread(&ThreadYieldExample2::appendOpt, this, i));
    for (auto& th : threads) th.join();

    // print contents:
    for (AtomicAPtrNode* it = list_head; it != nullptr; it = it->next)
        std::cout << ' ' << it->value;
    std::cout << '\n';

    // cleanup:
    AtomicAPtrNode* it;
    while (it = list_head)
    {
        list_head = it->next;
        delete it;
    }
}

void ThreadYieldExample2::appendOpt2(int val)
{
    // append an element to the list
    AtomicAPtrNode* newNode = new AtomicAPtrNode{val, list_head2};

    // next is the same as: list_head = newNode, but in a thread-safe way:

    while (!(list_head2.compare_exchange_strong(newNode->next, newNode)))
        ;
    // (with newNode->next updated accordingly if some other thread just appended another node)
}

void ThreadYieldExample2::test08()
{
    // spawn 10 threads to fill the linked list:
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) threads.push_back(std::thread(&ThreadYieldExample2::appendOpt2, this, i));
    for (auto& th : threads) th.join();

    // print contents:
    for (AtomicAPtrNode* it = list_head2; it != nullptr; it = it->next)
        std::cout << ' ' << it->value;

    std::cout << '\n';

    // cleanup:
    AtomicAPtrNode* it;
    while (it = list_head)
    {
        list_head = it->next;
        delete it;
    }
}
 void ThreadYieldExample2::run()
{
    //test01();
    //test02();
    //test03();
    //test04();
    //test05();
    //test06();
    //test07();
    test08();
}





AtomicAModel::AtomicAModel()
{
}

AtomicAModel::~AtomicAModel()
{
}
void AtomicAModel::run()
{
    //test01();
    //atomicAMain();
    //ThreadYieldExample demo;
    ThreadYieldExample2 demo;
    demo.run();
}
void AtomicAModel::test01()
{

}

} // namespace

AtomicAModelApp::AtomicAModelApp()
{
}

AtomicAModelApp::~AtomicAModelApp()
{
}
void AtomicAModelApp::run()
{

    std::cout << "AtomicAModelApp::run() call begin." << std::endl;

    AtomicAModel model;
    model.run();

    std::cout << "AtomicAModelApp::run() call end." << std::endl;
}

} // namespace model
} // namespace thread
} // namespace voxlog