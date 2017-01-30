#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/String.h>

//#include <resources/topicHeader.h>

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

	    Rate loop_rate(5);

    	namedWindow("w", 1);
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

 		std::vector< std::vector<cv::Point> > contours1;
  			
		findContours(thresh1, contours1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);  // Find the contours

		double largest_area1 = 0;
		int largest_contour_id1 = 0;

		if(contours1.empty())
    		{
        		cout<<"No red detected yet....."<<endl;
        		continue;
    		}

		for (int i = 0; i < contours1.size(); i++)  // iterate through each contour.
      	        {
       		  	double a1 = contourArea(contours1[i], false);
       		  	if (a1 > largest_area1)
       		  	{
        			largest_area1 = a1;
          			largest_contour_id1 = i;
        	       	}
		}
   		vector<Point2f> center1(1);
		vector<float> radius1(1);
		minEnclosingCircle(contours1[largest_contour_id1], center1[0], radius1[0]);
                
		std::vector< std::vector<cv::Point> > contours2;
  			
		findContours(thresh2, contours2, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);  // Find the contours

		double largest_area2 = 0;
		int largest_contour_id2 = 0;

		if(contours2.empty())
    		{
        		cout<<"No green detected yet....."<<endl;
        		continue;
    		}

		for (int i = 0; i < contours2.size(); i++)  // iterate through each contour.
      	        {
       		  	double a2 = contourArea(contours2[i], false);
       		  	if (a2 > largest_area2)
       		  	{
        			largest_area2 = a2;
          			largest_contour_id2 = i;
        	       	}
		}
   		vector<Point2f> center2(1);
		vector<float> radius2(1);
		minEnclosingCircle(contours2[largest_contour_id2], center2[0], radius2[0]);	
		circle(thresh1, center1[0], radius1[0], cv::Scalar(0, 250, 0), 1, 8, 0);  // minenclosing circle
      		circle(thresh1, center1[0], 4, cv::Scalar(0, 250, 0), -1, 8, 0);         // center is made on the screen
		circle(thresh2, center2[0], radius2[0], cv::Scalar(0, 250, 0), 1, 8, 0);  // minenclosing circle
      		circle(thresh2, center2[0], 4, cv::Scalar(0, 250, 0), -1, 8, 0);         // center is made on the screen
	        namedWindow("k",1);
		namedWindow("l",1);
        	imshow("w", src);
                imshow("k",thresh1);
 		imshow("l",thresh2);
                cout<<"center1"<<center1[0].x<<center1[0].y<<endl;
		cout<<"center1"<<center2[0].x<<center2[0].y<<endl;
        	waitKey(20); // waits to display frame
    	}
    	waitKey(0);
        spinOnce();
       loop_rate.sleep();
return 0;
  	
}
	
