#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std ;

ros::Publisher velocity_publisher ;
ros::Subscriber pose_subscriber ;
turtlesim::Pose turtlesim_pose ;

const double x_min = 0.0 ;
const double y_min = 0.0 ;
const double x_max = 11.0 ;
const double y_max = 11.0 ;

const double PI = 3.141592653589793238 ;

void move(double speed ,double distance,bool isForward) ;
void rotate(double angular_speed ,double angle,bool clockwise );
double degrees2radians(double angle_in_degrees) ;
void setDesiredOrientation(double desired_angle_radians) ;
void poseCallback(const turtlesim::Pose::ConstPtr & pose_message) ;
void gridClean();
void spiralClean(double rk, double wk) ;

int main(int argc ,char **argv)
{
        ros::init(argc,argv, "turtlesim_cleaner") ;
        ros::NodeHandle n;
        double speed,angular_speed ;
        double distance, angle;
        bool isForward,clockwise ;

        velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10) ;
        pose_subscriber = n.subscribe("turtle1/pose",10,poseCallback) ;
        ROS_INFO("\n\n\n******START TESTING************\n");
        ros::Rate loop_rate(0.5) ;
        gridClean();


        ros::spin() ;
        return 0;
}
void move(double speed ,double distance,bool isForward) {

        geometry_msgs::Twist vel_msg ;
        //set a random inear velocity in the x axis                                                  
        if (isForward)
                vel_msg.linear.x = abs(speed) ;
        else
                vel_msg.linear.x =-abs(speed) ;
                vel_msg.linear.y =0;
                vel_msg.linear.z =0;

                vel_msg.angular.x = 0;
                vel_msg.angular.y = 0;
                vel_msg.angular.z = 0;

        double t0 = ros::Time::now().toSec() ;
        double current_distance = 0.0 ;
        ros::Rate loop_rate(100) ;
        do{
                velocity_publisher.publish(vel_msg) ;
                double t1 = ros::Time::now().toSec();
                current_distance = speed * (t1 -t0) ;
                ros::spinOnce() ;
                loop_rate.sleep();

        }
        while(current_distance<distance);
        {
                vel_msg.linear.x=0 ;
                velocity_publisher.publish(vel_msg) ;
        }
}

