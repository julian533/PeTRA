#pragma once

#include <petra_core/default.h>

#include <petra_core/tools/LogLevel.h>
#include <petra_core/tools/ChronoTime.h>

struct LogEntry
{
public:
    std::string message;
    unsigned int hierarchy;
    LogLevel level;
    ChronoTime time;
};
