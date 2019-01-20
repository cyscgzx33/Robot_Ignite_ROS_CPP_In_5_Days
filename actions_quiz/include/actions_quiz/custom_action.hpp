#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actions_quiz/CustomActionMsgAction.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>

class custom_action
{
    protected:
        
        ros::NodeHandle nh_;
        
        actionlib::SimpleActionServer<actions_quiz::CustomActionMsgAction> as_;
        
        std::string action_name_;
        
        actions_quiz::CustomActionMsgFeedback feedback_;
        
        actions_quiz::CustomActionMsgResult result_;
        
        bool success_; // changed based on the solutions
        
        /* the following variables are created after checking the solutions */
        int rate_hz_;
        int side_seconds_;
        int turn_seconds_;
        std::string up_down_;
        
        ros::Rate *rate_;
        ros::Publisher move_pub_;
        geometry_msgs::Twist move_msg_;
        ros::Publisher takeoff_pub_;
        std_msgs::Empty takeoff_msg_;
        ros::Publisher land_pub_;
        std_msgs::Empty land_msg_;
        
    public:
        
        custom_action(std::string name);
        
        ~custom_action();
        
        void executeCB(const actions_quiz::CustomActionMsgGoalConstPtr& goal);
        
        /* the following functions are created after checking the solutions */
        void stop_drone();
        
        void move_forward_drone(int side_seconds);
        
        void turn_drone(int trun_seconds);
        
        void takeoff_drone();
        
        void land_drone();
};