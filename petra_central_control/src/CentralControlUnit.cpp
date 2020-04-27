/*****************************************************
 *                    ROS2 Node
 *****************************************************/
#include <petra_central_control/CentralControlUnit.h>

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;
using namespace std;

void CentralControlUnit::init()
{

    cout << "CCU initialised" << endl;
    state_ = CCUState::initialized;
}

void CentralControlUnit::run()
{
    if (state_ == CCUState::uninitialized)
    {
        init();
    }
    cout << "CCU active" << endl;
    state_ = CCUState::active;
    //log("Started");

    ActionSelection as(node_handle);
    add_action(&as);

    while (!action_queue_.empty())
    {
        if (action_queue_.front()->get_action_state() == ActionState::uninitialized | action_queue_.front()->get_action_state() == ActionState::initialized)
        {
            action_queue_.front()->start();
        }
        else if (action_queue_.front()->get_action_state() == ActionState::paused)
        {
            add_action(action_queue_.front());
            action_queue_.pop();
        }
        else if (action_queue_.front()->get_action_state() == ActionState::finished)
        {
            action_queue_.pop();
        }
        //only continue if ActionState==active
    }

    cout << "CCU finished" << endl;
    state_ = CCUState::finished;
}

void CentralControlUnit::add_action(Action *action)
{
    action_queue_.push(action);
    cout << "Action added to CCU queue" << endl;
}

int main(int argc, char **argv)
{
    CentralControlUnit ccu(argc, argv);
    ccu.run();
    return 0;
}