/*****************************************************
 *                    ROS2 Node
 *****************************************************/
#include <petra_output_nodes/Screen.h>
#include <iostream>

void Screen::display_text_callback(const petra_interfaces::msg::DisplayText::SharedPtr msg) const
{
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->text.c_str());
}

void Screen::get_input_callback(const std::shared_ptr<petra_interfaces::srv::GetInput::Request> request, std::shared_ptr<petra_interfaces::srv::GetInput::Response> response)
{
    std::cout << request.get()->text;
    std::cin >> response->input;
    RCLCPP_INFO(this->get_logger(), "sending back response: [%s]", response->input.c_str());
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Screen>());
    return 0;
}