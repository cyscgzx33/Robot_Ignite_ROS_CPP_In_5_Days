#include "topic_mini_proj/motionControl.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "motion_control");
    
    ros::Rate loop_rate(2);
    
    ros::NodeHandle nh("~");
    
    topic_mini_proj::motionControl mc_nh(nh);
    
    ros::spin();
    
    return 0;
}