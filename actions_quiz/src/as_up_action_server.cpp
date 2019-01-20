#include <ros/ros.h>
#include <actions_quiz/custom_action.hpp>


int main(int argc, char** argv) {
    
    ros::init(argc, argv, "custom_action_node");
    
    custom_action ca("custom"); 
    
    ros::spin();
    
    return 0;
}