#include <assert.h>
#include <iostream>
#include "ConsolePrinter.h"
namespace voxlog
{
namespace console
{

int   ConsolePrinter::tabsTotal{0};
char ConsolePrinter::tabChars[256]{'\0'};

void ConsolePrinter::newLine() noexcept
{

    std::cout << "\n";
}

void ConsolePrinter::lengthenTab(unsigned int total) noexcept
{
    assert(total >= 0);

    tabsTotal += total;

    createTabString();
}
void ConsolePrinter::shortenTab(unsigned int total) noexcept
{
    assert(total >= 0);

    if (tabsTotal > 0)
    {
        tabsTotal -= total;

        createTabString();
    }
}

unsigned int ConsolePrinter::getTabsTotal() const noexcept
{
    return tabsTotal;
}

void ConsolePrinter::createTabString()
{
    if (tabsTotal > 0)
    {
        if (tabsTotal > 256)
            tabsTotal = 256;
        memset(tabChars, '\t', tabsTotal);
        tabChars[tabsTotal - 1] = '\0';
    }
}
} // namespace console
} // namespace voxlog