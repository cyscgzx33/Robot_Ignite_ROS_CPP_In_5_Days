#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H

#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <cmath>
#include <vector>

namespace topic_mini_proj{

    class motionControl {
    
    private:
        ros::NodeHandle nh_;
        
        ros::Subscriber sub_;
        ros::Publisher pub_;
        
        void callBack(const sensor_msgs::LaserScan&);
        
        /* some other variables*/
        
        int smallest_dist;
        geometry_msgs::Twist cmd_vel_;
        
    public:
        motionControl(ros::NodeHandle&);
        virtual ~motionControl();
    };

}
#endif /* MOTIONCONTROL_H */