#pragma once

#include <petra_central_control/default.h>
#include <petra_central_control/Action.h>
#include <rclcpp/rclcpp.hpp>
#include <petra_interfaces/srv/selection.hpp>
#include <vector>

class ActionSelection : public Action
{
public:
    ActionSelection(std::shared_ptr<rclcpp::Node> &node_handle) : Action(), node_handle_(node_handle), state_(ActionState::uninitialized)
    {
        selection_client_ = node_handle_->create_client<petra_interfaces::srv::Selection>("Selection");
    }
    ~ActionSelection() {}

    void init();
    void start();
    void pause();
    void reset();
    void dialogue_entries();

    ActionState get_action_state() { return state_; }
    void select_action();

private:
    ActionState state_;
    std::vector<std::string> default_options_;
    rclcpp::Client<petra_interfaces::srv::Selection>::SharedPtr selection_client_;
    std::shared_ptr<rclcpp::Node> &node_handle_;
};
