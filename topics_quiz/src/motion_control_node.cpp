#include "topics_quiz/motionControl.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "topics_quiz_node");
    
    ros::NodeHandle nh("~");
    
    topic_mini_proj::motionControl mc_nh(nh);
    
    
    /* one must call ros::Rate AFTER ros::NodeHandle */
    ros::Rate loop_rate(2);
    
    
    ros::spin();
    
    return 0;
}