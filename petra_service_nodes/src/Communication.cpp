/*****************************************************
 *                    ROS2 Node
 *****************************************************/
#include <petra_service_nodes/Communication.h>
#include <iostream>

using namespace std;

void Communication::selection_callback(const std::shared_ptr<petra_interfaces::srv::Selection::Request> request, std::shared_ptr<petra_interfaces::srv::Selection::Response> response)
{
    string options = "Choose action to start\n";
    for (int i = 0; i < request->options.size(); i++)
    {
        options = options + "[" + to_string(i + 1) + "]" + request->options.at(i) + " ";
    }
    RCLCPP_INFO(this->get_logger(), "Incoming request. Waiting for selection...");
    this->publish_text(options+"\nWrite number between 1 - "+to_string(request->options.size())+" in Keyboard Node");

    bool exit_flag = true;
    do
    {
        int size = input_buffer.size();
        //input_text_callback fügt dem vector ein element hinzu
        while (input_buffer.size()==size)
        {
            //wait for text input from keyboard node
        }
        string input = input_buffer.back();
        input_buffer.pop_back();

        if (string_is_number(input))
        {
            int index = std::stoi(input);
            if (index<=request->options.size())
            {
                response->selected = request->options.at(index - 1);
                RCLCPP_INFO(this->get_logger(), "Sending back response: [%s]", response->selected.c_str());
                exit_flag = false;
            }else
            {
                this->publish_text("Invalid Input! Number out of range. Try again");
            }
        }else
        {
            this->publish_text("Invalid Input! Number required. Try again");
        }
    } while(exit_flag);
}

void Communication::publish_text(string text)
{
    auto message = petra_interfaces::msg::DisplayText();
    message.text = text;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.text.c_str());
    display_text_publisher_->publish(message);
}

void Communication::input_text_callback(const petra_interfaces::msg::InputText::SharedPtr msg) const
{
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->text.c_str());
    input_buffer.push_back(msg->text);
}

bool Communication::string_is_number(string string) {
    if(string=="")
    {
        return false;
    }
    const char* str=string.c_str();
    while(*str) 
    {
        if(!isdigit(*str)) {
        return false;
        }
        ++str;
    }
    return true;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor;
    auto node = std::make_shared<Communication>();
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}