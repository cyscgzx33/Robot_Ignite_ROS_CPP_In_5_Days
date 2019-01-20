#include <actions_quiz/custom_action.hpp>

custom_action::custom_action(std::string name):
    as_(nh_, name, boost::bind(&custom_action::executeCB, this, _1), false),
    action_name_(name)
{
    as_.start();
    success_ = true;
    
    /* following variables are initialized based on the solutions */
    rate_hz_ = 1;
    turn_seconds_ = 2;
    
    rate_ = new ros::Rate(rate_hz_);
    move_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    takeoff_pub_ = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
    land_pub_ = nh_.advertise<std_msgs::Empty>("/drone/land", 1000);
}

custom_action::~custom_action() {}

void custom_action::executeCB(const actions_quiz::CustomActionMsgGoalConstPtr& goal) 
{
    std::string up_down = goal->as_command.data; // does goal have a member goal?
    
    ROS_INFO("%s: Executing, Goal is: %s, Feedback is: %s", action_name_.c_str(), goal->as_command, feedback_);
    
    // TODO: implement a logic to prove it will up 1 meter
    // implemented through solutions
    
    // start executing the action
    for (int i = 0; i < 4; i++) {
        // check that preempt has not been requested by the client
        if (as_.isPreemptRequested() || !ros::ok()) {
            ROS_INFO("%s: Preempted", action_name_.c_str());
            // set the action state to preempted
            as_.setPreempted();
            success_ = false;
            break;
        }
        
        if (up_down == "UP") {
            this->takeoff_drone();
        }
        
        if (up_down == "DOWN") {
            this->land_drone();
        }
        
        
        // publish the feedback
        feedback_.as_command.data = i;
        as_.publishFeedback(feedback_);
        
        rate_->sleep();
        
        // Psudo script: if the as is UP for 1 meter, set the action as succeeded 
        if (success_) {
            ROS_INFO("%s: Succeeded", action_name_.c_str());
            
            // set the action state to succeeded
            as_.setSucceeded();
        }
        
    }
    
    // Accoding to the solutions, this snippat can be deleted
    /*
        ros::Publisher move = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        geometry_msgs::Twist move_msg;
    */
    
    
    
    // TODO: implement a loop to let the as go up 1 meter
    // Accoding to the solutions, this snippat can be deleted
    /* 
        while (true) // what should be the criteria
        {
            move_msg.linear.x = 1;
            move.publish(move_msg);
            rt_.sleep();
        }
    */
} 

void custom_action::stop_drone() {
    ROS_INFO("Stopping Drone...");
    int i = 0;
    while (i < 3) {
        move_msg_.linear.x = 0;
        move_msg_.angular.z = 0;
        
        // Attention: use "ros::Publisher" to publish "geometry_msgs"
        // similar for other functions
        move_pub_.publish(move_msg_);
        rate_->sleep();
        
        i++;
    }
}

void custom_action::move_forward_drone(int side_seconds) {
    ROS_INFO("Moving forward drone ...");
    int i = 0;
    while (i < side_seconds) {
        move_msg_.linear.x = 1;
        move_msg_.angular.z = 0;
        move_pub_.publish(move_msg_);
        rate_->sleep();
        
        i++;
    }
}

void custom_action::turn_drone(int turn_seconds) {
    ROS_INFO("Turning Drone...");
    
    int i = 0;
    while (i < turn_seconds) {
        move_msg_.linear.x = 0;
        move_msg_.angular.z = 0.55;
        move_pub_.publish(move_msg_);
        rate_->sleep();
        
        i++;
    }
}

void custom_action::takeoff_drone() {
    ROS_INFO("Taking Off Drone...");
    int i = 0;
    while (i < 4) {
        takeoff_pub_.publish(takeoff_msg_);
        rate_->sleep();
        
        i++;
    }
}

void custom_action::land_drone() {
    ROS_INFO("Landing Drone...");
    int i = 0;
    while (i < 4)  {
        land_pub_.publish(land_msg_);
        rate_->sleep();
        
        i++;
    }
}