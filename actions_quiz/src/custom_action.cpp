#include <actions_quiz/custom_action.hpp>

CustomActionMsgAction::CustomActionMsgAction(std::string name):
    as_(nh_, name, boost::bind(&CustomActionMsgAction::executeCB, this, _1), false),
    action_name_(name)
{
    as_.start();
    success = true;
}

CustomActionMsgAction::~CustomActionMsgAction() {}

void CustomActionMsgAction::executeCB(const actions_quiz::CustomActionMsgGoalConstPtr& goal) 
{
    // helper variables
    ros::Rate rt_(1);
    
    ROS_INFO("%s: Executing, Goal is: %s, Feedback is: %s", action_name_.c_str(), goal->as_command, feedback_);
    
    
    // TODO: implement a logic to prove it will up 1 meter
    ros::Publisher move = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    geometry_msgs::Twist move_msg;
    
    
    // TODO: implement a loop to let the as go up 1 meter
    while (true) // what should be the criteria
    {
        move_msg.linear.x = 1;
        move.publish(move_msg);
        rt_.sleep();
    }
    
    
    // Psudo script: if the as is UP for 1 meter, set the action as succeeded 
    if (success) {
        ROS_INFO("%s: Succeeded", action_name_.c_str());
        
        // set the action state to succeeded
        as_.setSucceeded();
    }
    
}
