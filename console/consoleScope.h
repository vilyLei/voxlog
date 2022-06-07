#pragma once

#include "logger.h"

namespace voxlog
{
namespace console
{
struct ConsoleScopeTabObject
{
    explicit ConsoleScopeTabObject(unsigned int ptabsTotal) :
        tabsTotal(ptabsTotal)
    {
        Logger::printer.lengthenTab(tabsTotal);
    }
    ~ConsoleScopeTabObject()
    {
        Logger::printer.shortenTab(tabsTotal);
    }

private:
    unsigned int tabsTotal;
};

struct ConsoleScopeCallObject
{
    explicit ConsoleScopeCallObject(unsigned int ptabsTotal, const std::string& info) :
        tabsTotal(ptabsTotal),
        lineInfo(info)
    {
        auto& scopeObj = Logger::scopeObject;
        scopeObj.callBegin(info, tabsTotal);
    }
    ~ConsoleScopeCallObject()
    {
        auto& scopeObj = Logger::scopeObject;
        scopeObj.callEnd(lineInfo, tabsTotal);
    }

private:
    unsigned int tabsTotal;
    //const std::string& lineInfo;//这样的实现会出现析构函数里面lineInfo的值为空
    const std::string lineInfo;
};

#if defined(DEBUG) | defined(_DEBUG) | defined(CONSOLE_LOG)
#    define consoleScopeShowInfo(info) \
        ;                              \
        Logger::scopeObject.showInfo(info);

#    define consoleScopeShowTabInfo(info, tabsTotal) \
        ;                                            \
        Logger::scopeObject.showTabInfo(info, tabsTotal);

#    define consoleScopeTab(tabsTotal)          ConsoleScopeTabObject Macro_csto_Instance(tabsTotal);
#    define consoleScopeCaller(tabsTotal, info) ConsoleScopeCallObject Macro_csco_Instance(tabsTotal, info);
#else
#    define consoleScopeShowInfo(info)
#    define consoleScopeShowTabInfo(info, tabsTotal)
#    define consoleScopeTab(tabsTotal)
#    define consoleScopeCaller(tabsTotal, info)
#endif
} // namespace console
} // namespace logHall
