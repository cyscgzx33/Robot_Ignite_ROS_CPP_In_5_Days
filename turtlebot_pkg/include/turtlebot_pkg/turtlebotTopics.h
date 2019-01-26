#ifndef TURTLEBOTTOPICS_H
#define TURTLEBOTTOPICS_H

#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <vector>

class turtlebotTopics {
    private:
        
        /* ROS variables */
        ros::NodeHandle nh_;
        
        ros::Publisher cmd_vel_pub_;
        
        ros::Subscriber laser_scan_sub_;
        
        ros::Subscriber odom_sub_;
        
        void callBackLaserScan(const sensor_msgs::LaserScan&);
        
        void callBackOdom(const nav_msgs::Odometry&);
        
        geometry_msgs::Twist cmd_vel_;
        
        /* Regular variables */
        
        // related to laserScan
        float smallest_dist_;
        int smallest_dist_dir_;
        float front_dist_;
        float left_dist_;
        float right_dist_;
        
        // related to Odom: *_wf_ means in world frame, *_lf means in local frame
        float odom_angPos_Z_wf_; 
        float odom_pos_X_wf_;
        float odom_pos_Y_wf_;
        float odom_angVel_Z_lf_; 
        float odom_vel_X_lf_;
        float odom_vel_Y_lf_;
        
    
    public:
        turtlebotTopics(ros::NodeHandle&);
        
        virtual ~turtlebotTopics();
};



#endif /* TURTLEBOTTOPICS_H */
