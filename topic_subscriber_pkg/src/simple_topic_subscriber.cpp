#include <ros/ros.h>
#include <std_msgs/Int32.h>

void counterCallback(const std_msgs::Int32::ConstPtr& msg) {
    // print the 'data' inside the 'msg' parameter
    ROS_INFO("%d", msg->data);
}

int main(int argc, char** argv) {
    
    // Initialte a Node called 'topic_subscriber'
    ros::init(argc, argv, "topic_subscriber"); 
    ros::NodeHandle nh;
    
    // Create a Subscriber object that will listen to the /counter topic and will
    // call the 'callback' function each time it reads something from the topic
    ros::Subscriber sub = nh.subscribe("counter", 1000, counterCallback);
    
    // Create a loop that will keep the program in execution
    ros::spin();
    
    return 0;
}