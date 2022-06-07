#pragma once
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <tuple>

namespace voxlog
{
namespace samples
{
namespace templ
{
namespace scope01
{
int fn(int) { return int(); } // function
typedef int (&fn_ref)(int);   // function reference
typedef int (*fn_ptr)(int);   // function pointer
struct fn_class
{
    int operator()(int i) { return i; }
}; // function-like class

int testMain()
{
    typedef std::result_of<decltype(fn)&(int)>::type A; // int
    typedef std::result_of<fn_ref(int)>::type        B; // int
    typedef std::result_of<fn_ptr(int)>::type        C; // int
    typedef std::result_of<fn_class(int)>::type      D; // int

    std::cout << std::boolalpha;
    std::cout << "typedefs of int:" << std::endl;

    std::cout << "A: " << std::is_same<int, A>::value << std::endl;
    std::cout << "B: " << std::is_same<int, B>::value << std::endl;
    std::cout << "C: " << std::is_same<int, C>::value << std::endl;
    std::cout << "D: " << std::is_same<int, D>::value << std::endl;

    return 0;
}
} // namespace scope01
namespace scope02
{

struct S
{
    double operator()(char, int&);
    float  operator()(int) { return 1.0; }
};

template <class T>
typename std::result_of<T(int)>::type f(T& t)
{
    std::cout << "A overload of f for callable T\n";
    return t(0);
}

template <class T, class U>
int f(U u)
{
    std::cout << "B overload of f for non-callable T\n";
    return u;
}


//template<typename F, typename A>
//std::result_of<F(A)>::type spawn_task(F f, A a)
//{
//    typedef std::result_of<F(A)>::type result_type;
//    result_type                           k;
//    return k;
//}

void testMain()
{

    ///*
    // the result of invoking S with char and int& arguments is double
    std::result_of<S(char, int&)>::type d = 3.14; // d has type double
    static_assert(std::is_same<decltype(d), double>::value, "");

    // std::invoke_result uses different syntax (no parentheses)
    std::invoke_result<S, char, int&>::type b = 3.14;
    static_assert(std::is_same<decltype(b), double>::value, "");

    // the result of invoking S with int argument is float
    std::result_of<S(int)>::type x = 3.14; // x has type float
    static_assert(std::is_same<decltype(x), float>::value, "");

    // result_of can be used with a pointer to member function as follows
    struct C
    {
        double Func(char, int&);
    };
    std::result_of<decltype (&C::Func)(C, char, int&)>::type g = 3.14;
    static_assert(std::is_same<decltype(g), double>::value, "");

    f<C>(1); // may fail to compile in C++11; calls the non-callable overload in C++14
    //*/
}
} // namespace scope02
namespace scope03
{
template <typename R>
class range
{
public:
    typedef typename R::value_type value_type; // 获取R的类型
    range(R& r) :
        range_(r)
    {
    }

public:
    template <typename KeyFn, typename ValueFn>                                                                         // KeyFn为key对应的映射函数 即输入value_type类型的值 输出key ValueFn同理
    std::multimap<typename std::result_of<KeyFn(value_type)>::type, typename std::result_of<ValueFn(value_type)>::type> // multimap的key和value都采用std::result_of获取类型
    group_by(const KeyFn& keyf, const ValueFn& valuef)
    {
        typedef typename std::result_of<KeyFn(value_type)>::type   k_type;
        typedef typename std::result_of<ValueFn(value_type)>::type v_type;
        std::multimap<k_type, v_type>                              mm;
        std::for_each(std::begin(range_), std::end(range_), [&mm, &keyf, &valuef](const value_type& item) { // 这里要求rang_是容器类型
            k_type key   = keyf(item);                                                                      // 映射出key
            v_type value = valuef(item);                                                                    // 映射出value
            mm.insert(std::make_pair(key, value));
        });
        return mm;
    }

private:
    R range_;
};
struct person
{
    std::string name;
    int         age;
    std::string city;
};
// 编译时递归打印tuple
template <typename Tuple, std::size_t N>
struct printer
{
    static void print(const Tuple& t)
    {
        printer<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template <typename Tuple>
struct printer<Tuple, 1>
{
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};
//对printer函数进一步封装 支持可变参数
template <typename... Args>
void PrintTuple(const std::tuple<Args...>& t)
{
    std::cout << "(";
    printer<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}

int testMain()
{
    typedef std::vector<person> R;
    R                           vec{{"aa", 18, "bb"}, {"cc", 28, "dd"}, {"ahj", 12, "12dd"}};
    range<R>                    r(vec);
    // 第一种 按照姓名和年龄分组 向group传递lambda表达式
    auto mm = r.group_by([](const person& _person) { return std::tie(_person.name, _person.age); },
                         [](const person& _person) { return std::tie(_person.city); }); // std::tie是形成tuple的工具 即将name和age组成一个tuple或者将city组成只有1个元素的tuple

    for (auto& e : mm)
    {
        std::cout << "first==============" << std::endl;
        PrintTuple(e.first);
        std::cout << "second==============" << std::endl;
        PrintTuple(e.second);
    }
    // 第二种 按照年龄分组
    auto mm1 = r.group_by([](const person& _person) { return std::tie(_person.age); },
                          [](const person& _person) { return std::tie(_person.name, _person.city); });

    std::cout << "===========================" << std::endl;
    for (auto& e : mm1)
    {
        std::cout << "first==============" << std::endl;
        PrintTuple(e.first);
        std::cout << "second==============" << std::endl;
        PrintTuple(e.second);
    }

    return 0;
}

}
void resultofTestMain()
{
    scope02::testMain();
}

} // namespace templ
} // namespace samples
} // namespace voxlog