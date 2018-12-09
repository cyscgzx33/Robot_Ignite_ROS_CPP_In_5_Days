#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/FibonacciAction.h>

class FibonacciAction
{
    protected:
        ros::NodeHandle nh_;
        
        // NodeHandle instance must be created before this line, otherwise strange error happens
        actionlib::SimpleActionServer<actionlib_tutorials::FibonacciAction> as_;
        std::string action_name_;
        
        // create messages that are used to publish feedback and result
        actionlib_tutorials::FibonacciFeedback feedback_;
        actionlib_tutorials::FibonacciResult result_;
        
    public:
        FibonacciAction(std::string name);
        ~FibonacciAction();
        
        void executeCB(const actionlib_tutorials::FibonacciGoalConstPtr &goal);
        
};