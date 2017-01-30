#include<ros/ros.h>
#include<opencv2/highgui/highgui.hpp>
int main(int argc,char **argv)
{
	ros::init(argc,argv,"hello_ros");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("Hello,␣ROS!");
	
	cv::Mat src;
    cv::VideoCapture cap(0);
       if( !cap.isOpened() )
        throw "Error when reading steam_avi";

	    ros::Rate loop_rate(5);

    	cv::namedWindow("w", 1);
    	for( ; ; )
    	{
        	cap >> src;
        	//if(!frame)
        	//    break;
        	cv::imshow("w", src);
        	cv::waitKey(20); // waits to display frame
    	}
    	cv::waitKey(0);
       ros::spinOnce();
       loop_rate.sleep();
  	
}
