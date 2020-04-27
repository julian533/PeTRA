#pragma once

#include <petra_central_control/default.h>

class DialogueEntryType
{
public:
    enum Value
    {
        number = 0,
        integer = 1,
        index = 2,
        text = 3
    };

    DialogueEntryType(Value value) : value_(value) {}
    DialogueEntryType() : DialogueEntryType(number) {}

    operator Value() const { return value_; }
    explicit operator bool() = delete;

    std::string dialogue_entry_type_to_string(DialogueEntryType state)
    {
        switch (state)
        {
        case DialogueEntryType::number:
            return "Number";
        case DialogueEntryType::integer:
            return "Integer";
        case DialogueEntryType::index:
            return "Index";
        case DialogueEntryType::text:
            return "Text";

        default:
            return "";
        }
    }

private:
    Value value_;
};