#include <iostream>
#include "sortAlgorithm.h"
#include "sortAlgImpl.h"
namespace voxlog
{
namespace core
{
namespace algorithm
{
namespace
{

} // namespace

SortAlgorthmApp::SortAlgorthmApp()
{
}
SortAlgorthmApp ::~SortAlgorthmApp()
{
}

void SortAlgorthmApp::run()
{
    std::cout << "SortAlgorthmApp::run() call begin." << std::endl;

    test01();

    std::cout << "SortAlgorthmApp::run() call end." << std::endl;
}
void SortAlgorthmApp::test01()
{
    listTest01();
    std::cout << "----------------------------------------" << std::endl;
    std::list ls{
        8,
        4,
        2,
        3,
        1,
        5,
        6,
        7};
    std::cout << "sort src ls: " << ls << std::endl;
    //auto result = sequential_quick_sort(ls);
    auto result = parallel_quick_sort(ls);
    std::cout << "sort result ls: " << result << std::endl;
}
} // namespace algorithm
} // namespace core

} // namespace voxlog