// Publisher node to accept Input image and Haar Cascade Data and the perform OpenCV detection and publish to camera/image 
#include <ros/ros.h>
//image_transport/image_transport.h includes everything we need to publish and subscribe to images.
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  cv::waitKey(30);
  

void detectFaces(Mat&, vector<Rect_<int> >&, string);
void detectFacialFeaures(Mat&, const vector<Rect_<int> >);

string input_image_path;
string face_cascade_path;


    input_image_path = argv[1];
    face_cascade_path = argv[2];
    

    // Load image and cascade classifier files
    Mat image1;
    image1 = imread(input_image_path);

    // Detect faces and facial features
    vector<Rect_<int> > faces;
    detectFaces(image1, faces, face_cascade_path);
    detectFacialFeaures(image1, faces);

    imshow("Result", image1);

    waitKey(0);
    return 0;

sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image1).toImageMsg();

  ros::Rate loop_rate(5);
  
while (nh.ok()) 
{    
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
}
}

void detectFaces(Mat& img, vector<Rect_<int> >& faces, string cascade_path)
{
    CascadeClassifier face_cascade;
    face_cascade.load(cascade_path);

    face_cascade.detectMultiScale(img, faces, 1.15, 3, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
    return;
}

void detectFacialFeaures(Mat& img, const vector<Rect_<int> > faces)
{
    for(unsigned int i = 0; i < faces.size(); ++i)
    {
        // Mark the bounding box enclosing the face
        Rect face = faces[i];
        rectangle(img, Point(face.x, face.y), Point(face.x+face.width, face.y+face.height),
                Scalar(255, 0, 0), 1, 4);
 }

    return;
}

  

