#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/FibonacciAction.h>
#include <action_server_pkg/fibonacci_action.h>

int main(int argc, char** argv) {
    
    ros::init(argc, argv, "fibonacci_node");
    
    FibonacciAction fb("fibonacci");
    ros::spin();
    
    return 0;
}
