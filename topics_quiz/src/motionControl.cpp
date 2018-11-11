#include <ros/ros.h>
#include "topics_quiz/motionControl.h"

namespace topic_mini_proj{

motionControl::motionControl(ros::NodeHandle& nh):nh_(nh) {
    sub_ = nh_.subscribe("/kobuki/laser/scan", 1000, &motionControl::callBack, this);
    
    // it seems like we must use "/cmd_vel" instead of "cmd_vel" 
    pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    
    ROS_INFO("Successfully launched node!");
}

void motionControl::callBack(const sensor_msgs::LaserScan &scan_msg) {
    ROS_INFO("callBack func is called!");
    
    // initialize the smallest_dist
    smallest_dist = 30;
    
    std::vector<float> scan_ranges = scan_msg.ranges;
    
    // calculate the smallest_dist in this timestep
    for (int i = 0; i < scan_ranges.size(); i++) {
        smallest_dist = smallest_dist > scan_ranges[i] ? scan_ranges[i] : smallest_dist;
    }
    
    // modify the cmd_vel_ signal based on smallest_dist
    if (smallest_dist < 3) {
        cmd_vel_.linear.x = 0.0;
        cmd_vel_.angular.z = 0.2;
    } else {
        cmd_vel_.linear.x = 0.2;
        cmd_vel_.angular.z = 0.0;
    }
    
    // publish cmd_vel_ 
    pub_.publish(cmd_vel_);
    ROS_INFO("Successfully published to cmd_vel");
    ROS_INFO("Smallest distance : %f", smallest_dist);
    ROS_INFO("Linear velocity x : %f", cmd_vel_.linear.x);
    ROS_INFO("Angular velocity z : %f", cmd_vel_.angular.z);
}

motionControl::~motionControl() {};

}