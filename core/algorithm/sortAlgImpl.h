#pragma
#include <iostream>
#include <algorithm>
#include <list>
#include <future>
#include <type_traits>
namespace voxlog
{
namespace core
{
namespace algorithm
{

/*
template <typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type>
spawn_task(F&& f, A&& a)
{
// 这样写没问题，但是用起来有问题

    typedef std::result_of<F(A &&)>::type result_type;
    std::packaged_task<result_type(A &&)>
                             task(std::move(f));
    std::future<result_type> res(task.get_future());
    std::thread              t(std::move(task), std::move(a));
    t.detach();
    return res;
}
//*/
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const std::list<T>& list)
{
    for (auto& i : list)
    {
        ostr << " " << i;
    }
    return ostr;
}
void listTest01()
{
    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {10, 20, 30, 40, 50};

    auto it = list1.begin();
    std::advance(it, 2);
    auto rIt = list2.begin();
    list1.splice(it, list2, list2.begin());

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";

    list2.splice(list2.begin(), list1, it, list1.end());

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
}
template <typename T> std::list<T> sequential_quick_sort(std::list<T> input)
{
    if (input.empty()) { return input; }
    std::list<T> result;
    auto         inputIt = input.begin();
    result.splice(result.begin(), input, inputIt);
    T const& pivot        = *result.begin();
    auto     divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

    //std::cout << "result: " << result << "\n";
    ////std::cout << "divide_point: " << *divide_point << "\n";
    //if (divide_point != input.end()) std::cout << "divide_point: " << *divide_point << "\n";
    //return result;

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    auto new_lower(sequential_quick_sort(std::move(lower_part)));
    auto new_higher(sequential_quick_sort(std::move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower);
    return result;
}

template <typename T> std::list<T> parallel_quick_sort(std::list<T> input)
{
    if (input.empty()) { return input; }

    std::list<T> result;
    auto         inputIt = input.begin();
    result.splice(result.begin(), input, inputIt);
    T const& pivot        = *result.begin();
    auto     divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    std::future<std::list<T>> new_lower(std::async(&parallel_quick_sort<T>, std::move(lower_part)));
    //std::future<std::list<T>> new_lower(spawn_task(parallel_quick_sort<T>, std::move(lower_part)));
    auto                      new_higher(parallel_quick_sort(std::move(input)));

    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());
    return result;
}
template <typename F, typename A>
F functionA(A&& p)
{
    F res;
    return res;
}

} // namespace algorithm
} // namespace core

} // namespace voxlog