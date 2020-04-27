#pragma once

#include <petra_central_control/default.h>

#include <petra_central_control/DialogueEntryType.h>

class DialogueEntry
{
public:
    std::string name;
    std::string text;
    std::string description;

    DialogueEntryType type;
    int relevance;

private:
};