#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Empty.h>

namespace srv_sqr_traj {
    
    class move_bb8 {
    
    private:
        /* ROS variables */
        ros::NodeHandle nh_;
        ros::Rate* rate_;
        
        /* ROS publishers */
        ros::Publisher pub_cmd_vel_;
        
        /* non-ROS variables */
        bool running_;
        int state_;
        int rate_hz_;
        float duration_;
        int times_;
        
    public:
        move_bb8();
        
        ~move_bb8();
        
        void rate_sleep();
        
        geometry_msgs::Twist getStateVel();
        
        void runtimeStateMachine();
        
        void changeState(int state, float duaration);
        
    };

} /* namespace srv_sqr_traj*/