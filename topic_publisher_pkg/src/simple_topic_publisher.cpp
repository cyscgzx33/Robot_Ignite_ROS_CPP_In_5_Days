#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv) {
    // Initialize a node named 'topic_publisher'
    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh;
    
    // Create a Publisher object, that publishs on 
    // the '/cmd_vel' topic message of type Twist
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000); 
    
    // set a publishing rate of 2 Hz
    ros::Rate loop_rate(2);
    
    // create a variable of type Twist
    geometry_msgs::Twist vel;
    
    // initialize 'vel' variable
    vel.linear.x = 0.5;
    vel.angular.z = 0.5;
    
    // create a loop that will go until someone stops the program execution
    while (ros::ok()) {
        // publish the message within the 'count' message
        pub.publish(vel);
        ros::spinOnce();
        // make sure the publish rate maintains at 2 Hz
        loop_rate.sleep();
    }
    
    return 0;
    
}