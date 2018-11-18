#include "service_square_traj/move_bb8.hpp"

namespace srv_sqr_traj {
    move_bb8::move_bb8() {
        
        /* initialization for non-ROS variables */
        running_ = false;
        state_ = 0;
        rate_hz_ = 20;
        // Seems like the time elapsed of one state
        duration_ = 0; 
        times_ = 4 * 1;
        
        /* initialization for ROS variables */
        rate_ = new ros::Rate(rate_hz_);
        
        /* initialization for ROS Publishers */
        pub_cmd_vel_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
        
    }
    
    void move_bb8::rate_sleep() {
        rate_->sleep();
    };
        
    geometry_msgs::Twist move_bb8::getStateVel() {
        geometry_msgs::Twist vel;
        
        switch(state_) {
            case 0:
                // go ahead
                vel.linear.x = 0.2;
                vel.angular.z = 0;
                break;
            case 1:
                // stop
                vel.linear.x = 0;
                vel.angular.z = 0;
                break;
            case 2:
                // turn right
                vel.linear.x = 0;
                vel.angular.z = 0.2;
                break;
            case 3:
                // stop
                vel.linear.x = 0;
                vel.angular.z = 0;
                break;
        }
        
        return vel;
    };
    
    
    /* an important implementation of runtime state machine */
    void move_bb8::runtimeStateMachine() {
        geometry_msgs::Twist vel;
        
        running_ = true;
        
        if (!running_) {
            vel.linear.x = 0;
            vel.angular.z = 0;
            pub_cmd_vel_.publish(vel);
            return;
        }
        
        vel = this->getStateVel();
        
        pub_cmd_vel_.publish(vel);
        
        duration_ -= 1/(float)rate_hz_;
        
        ROS_INFO("State [%d], Vel[%.2f, %.2f], Duration [%.2f]", state_, vel.linear.x, vel.angular.z, duration_);
        
        
        // when duration_ is run out, conduct this step to step into next state
        if (duration_ <= 0) {
            float state_duration[4] = {2.0, 3.8, 4.0, 0.1}; // what does this do ???
            
            // determine what is the next state_ value
            int next_state = state_ + 1;
            if (state_ == 3) {
                next_state = 0;
                times_ -= 1 ;
            }
            
            // determine what is the next state's duration
            int next_state_duration = state_duration[next_state];
            
            // call changeState() function to conduct stepping into next state 
            this->changeState(next_state, next_state_duration);
            
        }
        
        // end the whole behaviour is times_ is run out
        if (times_ == 0) {
            running_ = false;
            vel.linear.x = 0;
            vel.angular.z = 0;
            pub_cmd_vel_.publish(vel);
        }
    }
        
    
    void move_bb8::changeState(int state, float duration) {
        state_ = state;
        duration_ = duration;
        ROS_INFO("Change to state [%d]", state_);
    };
    
    move_bb8::~move_bb8() {}
    
    
} /* namespace srv_sqr_traj */
