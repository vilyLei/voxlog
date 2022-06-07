#include <assert.h>
#include "ScopeObject.h"
namespace voxlog
{
namespace console
{
ScopeObject::ScopeObject() :
    index(0),
    visible(true)
{
}
void ScopeObject::resetIndex(unsigned currentIndex) noexcept
{
    index = currentIndex;
}
unsigned int ScopeObject::getIndex() const noexcept
{
    return index;
}

void ScopeObject::showInfo(const std::string& info) noexcept
{
    if (visible)
    {
        printer.info("[" + std::to_string(getIndex()) + "] " + info);
    }
    else
    {
        printer.info(info);
    }
}
void ScopeObject::showTabInfo(const std::string& info, unsigned int tabsTotal) noexcept
{
    assert(tabsTotal < 256);
    printer.lengthenTab(tabsTotal);
    if (visible)
    {
        printer.info("[" + std::to_string(getIndex()) + "] " + info);
    }
    else
    {
        printer.info(info);
    }
    printer.shortenTab(tabsTotal);
}

void ScopeObject::callBegin(const std::string& info, unsigned int tabsTotal) noexcept
{
    printer.lengthenTab(tabsTotal);
    if (visible)
    {
        printer.info("[" + std::to_string(getIndex()) + "] " + info + " begin.");
    }
    else
    {
        printer.info(info + " begin.");
    }
    increase();
}
void ScopeObject::callEnd(const std::string& info, unsigned int tabsTotal) noexcept
{
    decrease();

    if (visible)
    {
        printer.info("[" + std::to_string(getIndex()) + "] " + info + " end.");
    }
    else
    {
        printer.info(info + " end.");
    }
    printer.shortenTab(tabsTotal);
}

void ScopeObject::increase() noexcept
{
    if (visible)
    {
        ++index;
    }
}
void ScopeObject::decrease() noexcept
{
    if (visible)
    {
        if (index > 0)
            --index;
    }
}
} // namespace console
} // namespace logHall