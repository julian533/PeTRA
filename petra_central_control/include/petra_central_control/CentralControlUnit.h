#pragma once

#include <queue>

#include <petra_central_control/default.h>
#include <petra_central_control/CCUState.h>
#include <petra_central_control/Action.h>
#include <petra_central_control/ActionSelection.h>

#include <rclcpp/rclcpp.hpp>

class CentralControlUnit : Component//, public rclcpp::Node
{
public:
    CentralControlUnit(int argc, char **argv) : state_(CCUState::uninitialized)//, Node("CentralControlUnit")
    {
        rclcpp::init(argc, argv);
        node_handle = rclcpp::Node::make_shared("CentralControlUnit");
    }
    ~CentralControlUnit()
    {
        rclcpp::shutdown();
        std::cout << "ROS shutdown" << std::endl;
    }
    std::shared_ptr<rclcpp::Node> node_handle;
    void run();
    void init();
    void add_action(Action *);

private:
    CCUState state_;

    std::queue<Action *> action_queue_;

    std::vector<Action *> background_actions_;
};