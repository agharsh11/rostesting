#include <ros/ros.h>
#include <std_msgs/String.h>
#include<beginner_tutorials/hi_msg.h>
using namespace std;
int counts;
void chatterCallback(const beginner_tutorials::hi_msg& msg)
{
  ++counts;
  cout<<"name "<<(char)msg.name<<endl;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  
  counts=0;
  
	 ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

	while (ros::ok())
	{
        ROS_INFO("on reading");
        ++counts;
	ros::spinOnce();
	sleep(1.0);
	//printf("\n%d\n",counts);
	}
	return 0;
  

  return 0;
}

