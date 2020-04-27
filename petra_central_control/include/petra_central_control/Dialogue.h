#pragma once

#include <petra_central_control/default.h>

#include <petra_central_control/DialogueEntry.h>

class Dialogue : Component
{
public:
    std::vector<DialogueEntry> entries;
    
private:
};