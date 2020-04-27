#pragma once

#include <petra_central_control/default.h>

class ActionState
{
public:
    enum Value
    {
        uninitialized = 0,
        initialized = 1,
        active = 2,
        paused = 3,
        finished = 4
    };

    ActionState(Value value) : value_(value) {}
    ActionState() : ActionState(uninitialized) {}

    operator Value() const { return value_; }
    explicit operator bool() = delete;

    std::string action_state_to_string(ActionState state)
    {
        switch (state)
        {
        case ActionState::uninitialized:
            return "Uninitialized";
        case ActionState::initialized:
            return "Initialized";
        case ActionState::active:
            return "Active";
        case ActionState::paused:
            return "Paused";
        case ActionState::finished:
            return "Finished";

        default:
            return "";
        }
    }

private:
    Value value_;
};