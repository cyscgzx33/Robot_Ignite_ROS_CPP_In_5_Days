#include "turtlebot_pkg/turtlebotTopics.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "turtlebot_topic_node");
    
    ros::NodeHandle nh("~");
    
    turtlebotTopics tb_nh(nh);
    
    ros::Rate loop_rate(2);
    
    ros::spin();
    
    return 0;
}