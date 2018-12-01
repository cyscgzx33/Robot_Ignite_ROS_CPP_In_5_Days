#include "services_quiz/move_bb8.hpp"

int main(int argc, char** argv) {
    ros::init(argc,argv, "MoveBB8Server");
    
    srv_sqr_traj::move_bb8 mv_bb8;
    
    while(ros::ok()) {
        
        mv_bb8.runtimeStateMachine();
        
        mv_bb8.rate_sleep();
        
        ros::spinOnce();
        
    }
    
    ros::spin();
    
    return 0;
}