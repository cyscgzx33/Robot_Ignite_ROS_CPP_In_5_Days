#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>

void counterCallback(const nav_msgs::Odometry::ConstPtr& odom_msg) {
    // please use the command "rosmsg show nav_msgs/Odometry" to check details
    ROS_INFO("%s", odom_msg->header.frame_id.c_str()); // seems like C-string is printable, but std::string is not
    ROS_INFO("%f", odom_msg->twist.twist.linear.x);
    ROS_INFO("%f", odom_msg->twist.twist.angular.z);
}

int main(int argc, char** argv) {
    
    // Initialte a Node called 'odom_subscriber'
    ros::init(argc, argv, "odom_subscriber"); 
    ros::NodeHandle nh;
    
    // Create a Subscriber object that will listen to the /odom topic and will
    // call the 'callback' function each time it reads something from the topic
    ros::Subscriber sub = nh.subscribe("odom", 1000, counterCallback);
    
    // Create a loop that will keep the program in execution
    ros::spin();
    
    return 0;
}