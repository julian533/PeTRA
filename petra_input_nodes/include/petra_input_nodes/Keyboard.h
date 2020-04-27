#pragma once

#include "rclcpp/rclcpp.hpp"
#include "petra_interfaces/msg/input_text.hpp"

class Keyboard
{
private:
    std::shared_ptr<rclcpp::Node> node_handle_;
    rclcpp::Publisher<petra_interfaces::msg::InputText>::SharedPtr input_text_publisher_;

public:
    Keyboard();
    ~Keyboard();
    void run();
};