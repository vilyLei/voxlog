#pragma once

#include "ConsolePrinter.h"
namespace voxlog
{
namespace console
{
class ScopeObject
{
public:
    // clang-format off
    ScopeObject              (                                    );
    ScopeObject              (const ScopeObject&                obj)            = delete;
    ScopeObject& operator=   (const ScopeObject&                obj)            = delete;
    virtual ~ScopeObject()                                                     = default;
    // clang-format on

    ConsolePrinter printer;

    void         resetIndex(unsigned currentIndex = 0) noexcept;
    unsigned int getIndex() const noexcept;
    void         showInfo(const std::string& info) noexcept;
    void         showTabInfo(const std::string& info, unsigned int tabsTotal = 1) noexcept;
    void         callBegin(const std::string& info, unsigned int tabsTotal = 1) noexcept;
    void         callEnd(const std::string& info, unsigned int tabsTotal = 1) noexcept;
    bool         visible;

private:
    unsigned int   index;

    void increase() noexcept;
    void decrease() noexcept;
};
} // namespace console
} // namespace logHall