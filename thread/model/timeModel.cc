

#include <vector>
#include "../../core/functionDefine.h"
#include "timeModel.h"

namespace voxlog
{
namespace thread
{
namespace model
{
namespace
{

TimeDataBase::TimeDataBase()
{
}

TimeDataBase::~TimeDataBase()
{
    std::cout << "TimeDataBase::deconstructor().\n";
}
void TimeDataBase::run()
{
    std::cout << "TimeDataBase::run().\n";
}
const char* TimeDataBase::convertStr(const char* str)
{
    return str;
}

TimeModelBase::TimeModelBase()
{
}
TimeModelBase::~TimeModelBase()
{
}
void TimeModelBase::run()
{
    //test01();
    //test02();
    test03();
}

void TimeModelBase::test01()
{
    using namespace std::literals; // enables the usage of 24h, 1ms, 1s instead of
                                   // e.g. std::chrono::hours(24), accordingly

    const std::chrono::time_point<std::chrono::system_clock> now =
        std::chrono::system_clock::now();

    const std::time_t t_c = std::chrono::system_clock::to_time_t(now - 24h);
    std::cout << "24 hours ago, the time was "
              << std::put_time(std::localtime(&t_c), "%F %T.\n") << std::flush;

    const std::chrono::time_point<std::chrono::steady_clock> start =
        std::chrono::steady_clock::now();

    slow_motion();

    const auto end = std::chrono::steady_clock::now();

    std::cout
        << "Slow calculations took "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us ¡Ö "
        << (end - start) / 1ms << "ms ¡Ö " // almost equivalent form of the above, but
        << (end - start) / 1s << "s.\n";  // using milliseconds and seconds accordingly

    const std::chrono::time_point<std::chrono::system_clock> nowEnd =
        std::chrono::system_clock::now();

    std::cout
        << "now: "
        << std::chrono::system_clock::to_time_t(now)
        << " begin."
        << std::endl; 
    std::cout
        << "now: "
        << std::chrono::system_clock::to_time_t(nowEnd)
        << " end."
        << std::endl;
}
void TimeModelBase::test02()
{

    std::cout << getCompilerIdns() + "\n";

    TimeDataBase* tdb{nullptr};
    CREATE_OBJ_NAKED_PTR(tdb, TimeDataBase);
    DELETE_OBJ_NAKED_PTR(tdb);
    DEFINE_OBJ_SHARED_PTR(sharedPtr1, TimeDataBase);
    CREATE_OBJ_SHARED_PTR(sharedPtr1, TimeDataBase);
    sharedPtr1->run();
    DELETE_OBJ_SHARED_PTR(sharedPtr1);

    std::cout << "----------------------------------------\n";
    DEFINE_AND_CREATE_OBJ_SHARED_PTR(sharedPtr2, TimeDataBase);
    sharedPtr2->run();
    
    MAKE_OBJ_SHARED_PTR(sharedPtr3, TimeDataBase);
    sharedPtr3->run();

    std::cout << "----------------------------------------\n";
    char* str = new char[9]{'a', 'b', 'c', 'd', '1', '2', '3', '4','\0'};
    //"abcd1234";
    std::string str2 = sharedPtr2->convertStr(str);

    auto flag = str == str2.c_str();
    std::cout << "---------flag: " + std::to_string(flag) + "\n";
    char* charPtr = const_cast<char*>(str);
    //charPtr[1]     = 'x';
    memset(charPtr, 'x', 1);

    std::cout << "str: " << str << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "----------------------------------------\n";

    std::cout << std::fixed << std::setprecision(9) << std::left;
    for (auto size = 1ull; size < 1000'000'000ull; size *= 100)
    {
        // record start time
        auto start = std::chrono::system_clock::now();
        // do some work
        std::vector<int> v(size, 42);
        sink = std::accumulate(v.begin(), v.end(), 0u); // make sure it's a side effect
        // record end time
        auto                          end  = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        auto                          diffMS = std::chrono::duration_cast<std::chrono::microseconds>(diff);
        std::cout << "Time to fill and iterate a vector of " << std::setw(9)
                  << size << " ints : " << diff.count() << " s\n";
        std::cout << "Time ms: " << diffMS.count() << " ms\n";
    }
}
void TimeModelBase::test03()
{
    using std::chrono::system_clock;

    std::chrono::duration<int, std::ratio<60 * 60 * 24>> one_day(1);

    system_clock::time_point today    = system_clock::now();
    system_clock::time_point tomorrow = today + one_day;

    std::time_t tt;

    tt = system_clock::to_time_t(today);
    std::cout << "today is: " << ctime(&tt);

    tt = system_clock::to_time_t(tomorrow);
    std::cout << "tomorrow will be: " << ctime(&tt);
}
void TimeModelBase::slow_motion()
{
#ifdef VOXL_CPLUSPLUS_MAJOR_20
    //static int a[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    static int a[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    while (std::ranges::next_permutation(a).found)
    {} // generates 12! permutations
#else
    std::cout << "TimeModelBase::slow_motion() emptily call.\n";
#endif
}

} // namespace
TimeModelApp::TimeModelApp()
{
}
TimeModelApp::~TimeModelApp()
{
}
void TimeModelApp::run()
{
    std::cout << "TimeModelApp::run() call begin." << std::endl;
    TimeModelBase modelBase;
    modelBase.run();
    std::cout << "TimeModelApp::run() call end." << std::endl;

}

} // namespace model
} // namespace thread
} // namespace voxlog