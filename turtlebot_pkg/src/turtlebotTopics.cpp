#include <ros/ros.h>
#include "turtlebot_pkg/turtlebotTopics.h"

turtlebotTopics::turtlebotTopics(ros::NodeHandle& nh):nh_(nh) {
    
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    
    laser_scan_sub_ = nh_.subscribe("/kobuki/laser/scan", 1000, &turtlebotTopics::callBackLaserScan, this);
    
    odom_sub_ = nh_.subscribe("/odom", 1000, &turtlebotTopics::callBackOdom, this);
    
    ROS_INFO("Successfully launched node!");
    
}

void turtlebotTopics::callBackOdom(const nav_msgs::Odometry& odom_msg) {
    ROS_INFO("callBackOdom function is called!");
    
    /* initialize the odom_direction_ */
    odom_angPos_Z_wf_ = odom_msg.pose.pose.orientation.z; 
    odom_pos_X_wf_ = odom_msg.pose.pose.position.x;
    odom_pos_Y_wf_ = odom_msg.pose.pose.position.y;
    odom_angVel_Z_lf_ = odom_msg.twist.twist.angular.z; 
    odom_vel_X_lf_ = odom_msg.twist.twist.linear.x;
    odom_vek_Y_lf_ = odom_msg.twist.twist.linear.y;
    
}

void turtlebotTopics::callBackLaserScan(const sensor_msgs::LaserScan& scan_msg) {
    ROS_INFO("callBackLaserScan function is called!");
    
    /* initialize variables related to LaserScan */
    
    // obtain the left, front and right distances
    // according to the LaserScan echo, it has 720 laser beams, 
    // ranges within [-pi, pi], with increment as 0.25 deg
    
    left_dist_ = scan_msg.ranges[0];
    front_dist_ = scan_msg.ranges[359];
    right_dist_ = scan_msg.ranges[719];
    
    // obtain the smallest distance in this time stamp
    smallest_dist_ = 30;
    smallest_dist_dir_ = 0;
    std::vector<float> scan_range = scan_msg.ranges;
    
    for (int i = 0; i < scan_range.size(); i++) {
        smallest_dist_ = smallest_dist_ > scan_range[i] ? scan_range[i] : smallest_dist_;
        smallest_dist_dir_ = smallest_dist_ > scan_range[i] ? i : smallest_dist_dir_;
    }
    
    
}

