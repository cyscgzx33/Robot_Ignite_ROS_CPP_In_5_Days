#include <ros/ros.h>

int main(int argc, char** argv) {

    ros::init(argc, argv, "ObiWan");
    ros::NodeHandle nh;
    ROS_INFO("Help me Obi-Wan Kenobi, you're my only hope");
    ros::spinOnce();
    return 0;
}