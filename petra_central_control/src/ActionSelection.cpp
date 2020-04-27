#include <petra_central_control/ActionSelection.h>

using namespace std;

void ActionSelection::init()
{
    default_options_.push_back("action1");
    default_options_.push_back("action2");
    default_options_.push_back("action3");
    default_options_.push_back("blabla");

    cout << "ActionSelection initialised" << endl;
    state_ = ActionState::initialized;
}

void ActionSelection::start()
{
    if (state_ == ActionState::uninitialized)
    {
        init();
    }

    cout << "ActionSelection active" << endl;
    state_ = ActionState::active;

    select_action();

    cout << "ActionSelection finished" << endl;
    state_ = ActionState::finished;
}

void ActionSelection::pause()
{

    cout << "ActionSelection paused" << endl;
    state_ = ActionState::paused;
}

void ActionSelection::reset()
{
}

void ActionSelection::dialogue_entries()
{
}

void ActionSelection::select_action()
{
    auto request = std::make_shared<petra_interfaces::srv::Selection::Request>();
    request->options.assign(default_options_.begin(), default_options_.end());

    while (!selection_client_->wait_for_service(1s))
    {
        if (!rclcpp::ok())
        {
            RCLCPP_ERROR(rclcpp::get_logger("ActionSelection"), "Interrupted while waiting for the service. Exiting. //kein return 0 mehr im Code");
        }
        RCLCPP_INFO(rclcpp::get_logger("ActionSelection"), "service not available, waiting again...");
    }

    auto result = selection_client_->async_send_request(request);
    RCLCPP_INFO(rclcpp::get_logger("ActionSelection"), "Sending request...");
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node_handle_, result) == rclcpp::executor::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("ActionSelection"), "Selected Action: [%s]", result.get()->selected.c_str());
    }
    else
    {
        RCLCPP_ERROR(rclcpp::get_logger("ActionSelection"), "Failed to call service Selection");
    }
}