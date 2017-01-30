#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/String.h>

#include <resources/topicHeader.h>

using namespace std;
using namespace cv;
using namespace ros;
using namespace image_transport;
using namespace cv_bridge;

int main(int argc,char **argv)
{

	ros::init(argc,argv,"ros_gate");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("gate,␣ROS!");
	
	cv::Mat src,thresh1,thresh2;
    cv::VideoCapture cap(0);
       if( !cap.isOpened() )
        throw "Error when reading steam_avi";

	    ros::Rate loop_rate(5);

    	cv::namedWindow("w", 1);
    	for( ; ; )
    	{
        	cap >> src;
        	int flag_green =0;
        	int flag_red=0;
        	cvtColor(src, src, CV_BGR2HSV);
        	Scalar red_min = cv::Scalar(23,41,133, 0);
			Scalar red_max = cv::Scalar(40,150,255, 0);
  			Scalar green_min = Scalar(23,41,133, 0);
  			Scalar green_max = Scalar(40,150,255, 0);
			inRange(src, red_min, red_max, thresh1);
            inRange(src, green_min, green_max, thresh2);
            GaussianBlur(thresh1, thresh1, cv::Size(9, 9), 0, 0, 0);

 			std::vector< std::vector<cv::Point> > contours;
  			
			findContours(thresh1, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);  // Find the contours

			double largest_area = 0;
			int largest_contour_id = 0;

			if(contours.empty())
    		{
        		cout<<"No green detected yet....."<<endl;
        		continue;
    		}

			for (int i = 0; i < contours.size(); i++)  // iterate through each contour.
      		{
        		double a = contourArea(contours[i], false);
        		if (a > largest_area)
        		{
          			largest_area = a;
          			largest_contour_id = i;
        		}
			}

        	imshow("w", src);
        	waitKey(20); // waits to display frame
    	}
    	waitKey(0);
        spinOnce();
       loop_rate.sleep();
  	
}
	return 0;
}