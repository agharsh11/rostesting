#include "ros/ros.h"
#include "std_msgs/String.h"
#include <beginner_tutorials/hi_msg.h>
#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<beginner_tutorials::hi_msg>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
  
    beginner_tutorials::hi_msg msgs;

    //std::stringstream ss;
    //ss << "hello world " << count;
    //msg.data = ss.str();
    //ROS_INFO("%s", msg.data.c_str());
    ROS_INFO("on it");
    msgs.name='A';
    msgs.age=2;
    msgs.score=23;
    chatter_pub.publish(msgs);


    ros::spinOnce();

    loop_rate.sleep();

    ++count;
  }


  return 0;
}
