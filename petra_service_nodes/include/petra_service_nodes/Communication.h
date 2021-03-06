#pragma once

//#include <petra_central_control/default.h>
#include "rclcpp/rclcpp.hpp"
#include "petra_interfaces/srv/selection.hpp"
#include "petra_interfaces/srv/get_input.hpp"
#include "petra_interfaces/msg/display_text.hpp"
#include "petra_interfaces/msg/input_text.hpp"

#include <functional>
#include <memory>
#include <string>
#include <queue>
#include <thread>
#include <iostream>

//global variable because callback function has to be const and can't edit class fields.
std::vector<std::string> input_buffer;

class Communication : public rclcpp::Node
{
public:
    Communication() : Node("Communication")
    {
        callback_group_input_ = this->create_callback_group(rclcpp::callback_group::CallbackGroupType::MutuallyExclusive);
        
        auto input_opt = rclcpp::SubscriptionOptions();
        input_opt.callback_group = callback_group_input_;

        display_text_publisher_ = this->create_publisher<petra_interfaces::msg::DisplayText>("DisplayText", 10);
        selection_service_ = this->create_service<petra_interfaces::srv::Selection>("Selection", std::bind(&Communication::selection_callback, this, std::placeholders::_1, std::placeholders::_2));
        input_text_subscription_ = this->create_subscription<petra_interfaces::msg::InputText>("InputText", 10, std::bind(&Communication::input_text_callback, this, std::placeholders::_1),input_opt);
        get_input_client_ = this->create_client<petra_interfaces::srv::GetInput>("GetInput");
    }

    void publish_text(std::string);
    bool string_is_number(std::string string);

private:
    rclcpp::callback_group::CallbackGroup::SharedPtr callback_group_input_;

    void selection_callback(const std::shared_ptr<petra_interfaces::srv::Selection::Request> request, std::shared_ptr<petra_interfaces::srv::Selection::Response> response);
    void input_text_callback(const petra_interfaces::msg::InputText::SharedPtr msg) const;
    rclcpp::Publisher<petra_interfaces::msg::DisplayText>::SharedPtr display_text_publisher_;
    rclcpp::Service<petra_interfaces::srv::Selection>::SharedPtr selection_service_;
    rclcpp::Subscription<petra_interfaces::msg::InputText>::SharedPtr input_text_subscription_;
    rclcpp::Client<petra_interfaces::srv::GetInput>::SharedPtr get_input_client_;
};