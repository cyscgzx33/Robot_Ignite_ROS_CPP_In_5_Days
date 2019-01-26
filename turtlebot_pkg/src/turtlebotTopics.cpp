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
    odom_vel_Y_lf_ = odom_msg.twist.twist.linear.y;
    
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
    
    /* implemented a very simple algorithm to control the turtlebot2 */
    if (front_dist_ <= 0.2) {
        cmd_vel_.linear.x = 0.0;
        if (left_dist_ < right_dist_) cmd_vel_.angular.z = 0.5; // turn right 
        else cmd_vel_.angular.z = -0.5; // turn left
    } else {
        cmd_vel_.linear.x = 0.5; // go straight forward
        cmd_vel_.angular.z = 0.0; // do not turn
    }
    
    /* publish to /cmd_vel and output some info */
    cmd_vel_pub_.publish(cmd_vel_);
    ROS_INFO("Successfully published to /cmd_vel");
    ROS_INFO("left_dist_:%f, front_dist_:%f, right_dist_:%f", left_dist_, front_dist_, right_dist_);
    ROS_INFO("linear.x:%f, angular.z:%f", cmd_vel_.linear.x, cmd_vel_.angular.z);
}

turtlebotTopics::~turtlebotTopics() {};
