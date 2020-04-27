#include <petra_input_nodes/Keyboard.h>
#include <iostream>

Keyboard::Keyboard()
{
    node_handle_ = rclcpp::Node::make_shared("Keyboard");
    input_text_publisher_ = node_handle_->create_publisher<petra_interfaces::msg::InputText>("InputText", 10);
}

Keyboard::~Keyboard()
{
    rclcpp::shutdown();
}

void Keyboard::run()
{
    while (rclcpp::ok())
    {
        auto message = petra_interfaces::msg::InputText();
        std::cin >> message.text;
        RCLCPP_INFO(node_handle_->get_logger(), "Publishing: '%s'", message.text.c_str());
        input_text_publisher_->publish(message);
        rclcpp::spin_some(node_handle_);
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    Keyboard key;
    key.run();
    return 0;
}