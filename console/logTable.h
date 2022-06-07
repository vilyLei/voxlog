#pragma once
namespace voxlog
{
namespace console
{

class LogTable
{

public:
    LogTable()          = default;
    virtual ~LogTable() = default;

    static void newLine();

private:
};
} // namespace console
} // namespace voxlog