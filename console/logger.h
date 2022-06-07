#pragma once
#include "ConsolePrinter.h"
#include "ScopeObject.h"

namespace voxlog
{
namespace console
{

class Logger
{

public:
    Logger()          = default;
    virtual ~Logger() = default;

    static ConsolePrinter printer;
    static ScopeObject scopeObject;

    // Shortening and lengthening
    static void  newLine() noexcept;

    template <typename T>
    static void info(const T& p)
    {
        printer.info( p );
    }

    template <typename T, typename... Types>
    static void info(const T& p0, const Types&... args)
    {
        //printer.info("parameters total: ", 1 + sizeof...(args));
        printer.info(p0, args...);
    }

    template <typename T>
    static void numberBinary(const T& p, size_t bitLength = 16)
    {
        printer.showNumberBinary(p, bitLength);
    }
    template <typename T>
    static void numberHex(const T& p)
    {
        printer.showNumberHex(p);
    }

    template <typename T>
    static void numberDec(const T& p)
    {
        printer.showNumberDec(p);
    }

    template <typename T>
    static void sizeofInfo(const std::string ns, const T p)
    {
        printer.showSizeofInfo(ns, p);
    }

protected:
private:
};

#if defined(DEBUG) | defined(_DEBUG) | defined(CONSOLE_LOG)
#    define consoleNewLine() \
        ;                    \
        Logger::newLine();
#    define consoleShowInfo(info) \
        ;                    \
        Logger::showInfo(info);
#else
#    define consoleNewLine();
#    define consoleShowInfo(info) ;
#endif
Logger logger;
} // namespace console
} // namespace logHall
