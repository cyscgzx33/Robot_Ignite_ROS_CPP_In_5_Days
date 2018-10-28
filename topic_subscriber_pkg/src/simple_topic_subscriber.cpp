#include <ros/ros.h>
#include <std_msgs/Int32.h>

void counterCallback(const std_msgs::Int32::ConstPtr& msg) {
    ROS_INFO("%d", msg->data);
}

int main(int argc, char** argv) {
    
    ros::init(argc, argv, "topic_subscriber");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("counter", 1000, counterCallback);
    
    ros::spin();
    
    return 0;
}