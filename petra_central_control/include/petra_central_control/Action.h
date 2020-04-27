#pragma once

#include <petra_central_control/default.h>

#include <petra_central_control/ActionState.h>

class Action : Component
{
public:
    Action() {}
    ~Action() {}

    virtual void init() {}
    virtual void start() {}
    virtual void pause() {}
    virtual void reset() {}

    virtual void dialogue_entries() {}

    virtual ActionState get_action_state() {}

protected:
    ActionState state_;
    int current_step_;
};