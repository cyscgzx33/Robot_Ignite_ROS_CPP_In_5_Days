#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

// in this case, the action server is using an action message definition called Fabonacci.action
// that message has been created by ROS and written into its actionlib_tutorials package
#include <actionlib_tutorials/FibonacciAction.h>


class FibonacciAction
{
    // explanation of the protected variables:
    // the node handle is constructed and passed into the action server during construction of the action
    // the action server is constructed in the constructor of the action
    // the feedback and result messages are created for publishing in the action
    protected:
        ros::NodeHandle nh_;
        
        // NodeHandle instance must be created before this line, otherwise strange error happens
        actionlib::SimpleActionServer<actionlib_tutorials::FibonacciAction> as_;
        std::string action_name_;
        
        // create messages that are used to publish feedback and result
        actionlib_tutorials::FibonacciFeedback feedback_;
        actionlib_tutorials::FibonacciResult result_;
        
    public:
        // in the class constructor, an action server is created
        FibonacciAction(std::string name);
        ~FibonacciAction();
        
        void executeCB(const actionlib_tutorials::FibonacciGoalConstPtr &goal);
        
};