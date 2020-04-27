/*****************************************************
 *                    ROS2 Node
 *****************************************************/
#include <petra_service_nodes/CommunicationSrvInsideSrv.h>
#include <iostream>

using namespace std;

void CommunicationSrvInsideSrv::selection_callback(const std::shared_ptr<petra_interfaces::srv::Selection::Request> request, std::shared_ptr<petra_interfaces::srv::Selection::Response> response)
{
    string options;
    for (int i = 0; i < request->options.size(); i++)
    {
        options = options + "[" + to_string(i + 1) + "]" + request->options.at(i) + " ";
    }
    RCLCPP_INFO(this->get_logger(), "Incoming request. Waiting for selection...");
    this->publish_text(options+"\nWrite number to choose >> ");



    /*
    //Problem: https://answers.ros.org/question/302037/ros2-how-to-call-a-service-from-the-callback-function-of-a-subscriber/
    //create another service call to get input back.
    auto inner_request = std::make_shared<petra_interfaces::srv::GetInput::Request>();
    inner_request->text = "[inner service] Write number to choose >> ";

    cout<<"test1";
    while (!get_input_client_->wait_for_service(1s))
    {
        if (!rclcpp::ok())
        {
            RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting. //kein return 0 mehr im Code");
        }
        RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
    }
    
    cout<<"test2";
    auto inner_future = get_input_client_->async_send_request(inner_request);
    // Wait for the result.
    cout<<"test3";
    string result_input;
    //rclcpp::executors::spin_node_until_future_complete(*executor, this->get_node_base_interface(), inner_future)
    if ( executor->spin_until_future_complete(inner_future)== rclcpp::executor::FutureReturnCode::SUCCESS)
    {
        result_input = inner_future.get()->input;
        RCLCPP_INFO(this->get_logger(), "Input: %s", result_input.c_str());
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to call service Selection");
    }
    //end inner service call
    */

    string result_input;
    cin>>result_input;
    while(!string_is_number(result_input))
    {
        this->publish_text("Input has to be an integer value! Try again >> ");
        RCLCPP_INFO(this->get_logger(), "input was no integer. Try again >> ");
        cin>>result_input;
    }
    int index = std::stoi(result_input);
    response->selected = request->options.at(index - 1);
    RCLCPP_INFO(this->get_logger(), "sending back response: [%s]", response->selected.c_str());
}

void CommunicationSrvInsideSrv::publish_text(string text)
{
    auto message = petra_interfaces::msg::DisplayText();
    message.text = text;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.text.c_str());
    display_text_publisher_->publish(message);
}

void CommunicationSrvInsideSrv::input_text_callback(const petra_interfaces::msg::InputText::SharedPtr msg) const
{
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->text.c_str());
}

bool CommunicationSrvInsideSrv::string_is_number(string string) {
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
    rclcpp::executors::MultiThreadedExecutor executor2;
    auto node = std::make_shared<CommunicationSrvInsideSrv>(&executor2);
    //executor2.add_node(node);
    //Zweite node erstellen -> Compositions
    //index ros2 doc: "Beyond Pub/Sub: We’ve not done any of this with Services, Parameters, or Actions, but we will."
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}