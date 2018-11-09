#include "topic_mini_proj/motionControl.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "motion_control");
    
    ros::NodeHandle nh("~");
    
    topic_mini_proj::motionControl mc_nh(nh);
    
    
    /* one must call ros::Rate AFTER ros::NodeHandle */
    ros::Rate loop_rate(2);
    
    
    ros::spin();
    
    return 0;
}