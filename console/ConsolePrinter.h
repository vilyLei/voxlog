#pragma once
#include <string>
#include <iostream>
#include <bitset>
namespace voxlog
{
namespace console
{
class ConsolePrinter
{

public:
    ConsolePrinter()          = default;
    virtual ~ConsolePrinter() = default;

    // Shortening and lengthening
    static void  newLine() noexcept;
    static void  lengthenTab(unsigned int total = 1) noexcept;
    static void  shortenTab(unsigned int total = 1) noexcept;
    unsigned int getTabsTotal() const noexcept;

    template <typename T>
    static void info(const T& p)
    {
        std::cout << std::boolalpha;
        std::cout << "[info] ";
        if (tabsTotal > 0)
        {
            std::cout << tabChars << p << std::endl;
        }
        else
        {
            std::cout << p << std::endl;
        }
    }
    template <typename T, typename... Types>
    static void info(const T& p, const Types&... args)
    {
        std::cout << std::boolalpha;
        std::cout << "[info] ";
        if (tabsTotal > 0)
        {
            std::cout << tabChars;
        }
        std::cout << p;
        showSubInfo(args...);
        std::cout << std::endl;
    }


    template <typename T>
    static void showNumberBinary(const T p, size_t bit_length = 16)
    {

        //static_assert(sizeof(T) == -1, "You have to have a specialization for Helper!");
        auto numberSize = sizeof(p);

        switch (numberSize)
        {
            case 8:
                std::cout << std::bitset<64>(p) << std::endl;
                break;
            case 4:
                std::cout << std::bitset<32>(p) << std::endl;
                break;
            case 2:
                std::cout << std::bitset<16>(p) << std::endl;
                break;
            case 1:
                std::cout << std::bitset<8>(p) << std::endl;
                break;
            case 16:
                std::cout << std::bitset<128>(p) << std::endl;
                break;
            case 32:
                std::cout << std::bitset<256>(p) << std::endl;
                break;
            default:
                std::cout << std::bitset<8>(p) << std::endl;
                break;
        }
    }
    template <typename T>
    static void showNumberHex(const T p)
    {

        std::cout << std::hex << p << std::endl;
    }

    template <typename T>
    static void showNumberDec(const T p)
    {
        std::cout << std::dec << p << std::endl;
    }

    template <typename T>
    static void showSizeofInfo(const std::string ns, const T p)
    {

        size_t t = sizeof(p);
        if (t > 1)
        {
            std::cout << "sizeof( " << ns << " ): " << t << " bytes." << std::endl;
        }
        else
        {
            std::cout << "sizeof( " << ns << " ): " << t << " byte." << std::endl;
        }
    }


protected:
    template <typename T, typename... Types>
    static void showSubInfo(const T& p)
    {
        std::cout << p;
    }
    template <typename T, typename... Types>
    static void showSubInfo(const T& p, const Types&... args)
    {
        std::cout << p;
        showSubInfo(args...);
    }

private:
    static void createTabString();
    static int  tabsTotal;
    static char tabChars[256];
};
} // namespace console
} // namespace voxlog