#pragma once

//#include <petra_central_control/default.h>
#include "rclcpp/rclcpp.hpp"
#include "petra_interfaces/msg/display_text.hpp"
#include "petra_interfaces/srv/get_input.hpp"
#include <memory>

using std::placeholders::_1;

class Screen : public rclcpp::Node
{
public:
    Screen() : Node("Screen")
    {
        display_text_subscription_ = this->create_subscription<petra_interfaces::msg::DisplayText>("DisplayText", 10, std::bind(&Screen::display_text_callback, this, _1));
        get_input_service_ = this->create_service<petra_interfaces::srv::GetInput>("GetInput", std::bind(&Screen::get_input_callback, this, std::placeholders::_1, std::placeholders::_2));
    }
    ~Screen()
    {
        rclcpp::shutdown();
    }

private:
    void get_input_callback(const std::shared_ptr<petra_interfaces::srv::GetInput::Request> request, std::shared_ptr<petra_interfaces::srv::GetInput::Response> response);
    void display_text_callback(const petra_interfaces::msg::DisplayText::SharedPtr msg) const;
    rclcpp::Subscription<petra_interfaces::msg::DisplayText>::SharedPtr display_text_subscription_;
    rclcpp::Service<petra_interfaces::srv::GetInput>::SharedPtr get_input_service_;
};
