// g++ -o video video.cpp $(pkg-config opencv4 --cflags --libs) -I/usr/include/opencv4
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#include <numeric>
#include <functional>

#include "../moteur/moteur.hpp"

int cameraId = 2;

#include <iostream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;

Mat frame, gray, dst, cdst, cdstP;


extern float x_balle;
extern float y_balle;

int thresh = 100;
RNG rng(12345);
void linesDetect();
void circlesDetect();
void circlesDetectProcess(const char*);
void rectanglesDetect();
void rectanglesDetectProcess(const char*);
void plaqueDetect();

//empty fonction for trackbar callback
void nothing(int, void*){
    
}

//camera focal and object width
double focal_length = 520;
double real_item_width = 6.5;

const char* source_window = "Source";
bool circleArg, rectArg, plaqueArg, imageArg = false;
const char* file;
bool circleInitTrackbar=false;
bool  firstTimeRectangle = true;

Point point1;
Point point3;
Point point4;
Point point2;
bool exitPlaque = false;

double distance_finder(double focal_length, double real_item_width, double item_width_frame);

int camera(/*int argc, char** argv*/)
{   
    /*
    vector<string> args(argv, argv+argc);
    if (atoi( args[1].c_str() )){
        cameraId = atoi( args[1].c_str() );
    }
    else {
        cout <<"argument camera input must be an integer\n";
        return 0;
    }

    for (size_t i = 2; i < args.size(); ++i) {

        if (args[i] == "circle") {
            circleArg=true;
        }
        // else if (args[i] == "rectangle") {
        //     rectArg=true;
        // }
        else if (args[i] == "plaque") {
            plaqueArg=true;
        }
        else{
            imageArg=true;
            file = argv[i];
        }        
    }
    */
    circleArg = true;
    
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!imageArg){
        if(!cap.open(cameraId)){
            return 0;
        }
    }

    //this_thread::sleep_for(std::chrono::milliseconds(1000));
    // if (plaqueArg){
    //         while (exitPlaque == false){
    //             cap >> frame;
    //             plaqueDetect();
    //         }
              
    // }

    //this_thread::sleep_for(std::chrono::milliseconds(1000));


    for(;;) // infinite loop
    {
          if(!imageArg){ //if video
            cap >> frame;
          }
          else{
            frame  = imread(file);//else read image input
          }
          if( frame.empty() ) { //empty image
              break; // end of video stream
          }
          cvtColor( frame, gray, COLOR_BGR2GRAY );
          blur( gray, gray, Size(3,3) );                 

        //process with arg
          if (circleArg & exitPlaque == true){
              circlesDetect();
          }

        
        if (exitPlaque == false){
                plaqueDetect();
        }

        if (exitPlaque == true){
            circle(frame,point1,5,Scalar(0,0,255),-1);
            circle(frame,point2,5,Scalar(0,0,255),-1);
            circle(frame,point3,5,Scalar(0,0,255),-1);
            circle(frame,point4,5,Scalar(0,0,255),-1);
            //imshow("detected plaque", frame);
        }
        //   if(rectArg){
        //       rectanglesDetect();
        //   }

              

          
          if( waitKey(10) == 27 ){
              break; // stop capturing by pressing ESC 
          }
    }
    // the camera will be closed automatically upon exit
    // cap.close();

    return 0;
}

//calcul distance between cam and object
double distance_finder(double focal_length, double real_item_width, double item_width_frame){
    double distance = (real_item_width*focal_length)/item_width_frame;
    return distance;
}

void circlesDetect(){
    //create windows
    const char* sourceDisplayCircle = "circleDetect";
    namedWindow( sourceDisplayCircle );

    //create trackbar
    const int max_thresh = 255;
    createTrackbar("minDist", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("param1", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("param2", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("minRadius", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("maxRadius", sourceDisplayCircle, 0, max_thresh, nothing );

    //set default param
    if (!circleInitTrackbar){
        setTrackbarPos("minDist", sourceDisplayCircle, 4);
        setTrackbarPos("param1", sourceDisplayCircle, 25);
        setTrackbarPos("param2", sourceDisplayCircle, 50);
        setTrackbarPos("minRadius", sourceDisplayCircle, 40);
        setTrackbarPos("maxRadius", sourceDisplayCircle, 90);
        circleInitTrackbar = true;
        cout << "firstTimeCircle\n"; 
    }
    
    circlesDetectProcess(sourceDisplayCircle);
}


void circlesDetectProcess(const char* sourceDisplayCircle){
    int minDist = getTrackbarPos("minDist", sourceDisplayCircle);
    
    //avoid crash when 0
    if(getTrackbarPos("minDist", sourceDisplayCircle)==0){
        setTrackbarPos("minDist", sourceDisplayCircle, 1);
        minDist = 1;
    }
    
    //clone src
    Mat src = frame.clone();
    medianBlur(gray, gray, 5);

    //cout<<"circle";
    //cout<<getTrackbarPos("param1", sourceDisplayCircle)<<" "<<getTrackbarPos("param2", sourceDisplayCircle)<<" "<<getTrackbarPos("minRadius", sourceDisplayCircle)<<" "<<getTrackbarPos("maxRadius", sourceDisplayCircle)<<"\n"; 


    Point2f inputQuad[4];
    Point2f outputQuad[4];
    inputQuad[0] = Point2f(point1.x,point1.y);
    inputQuad[1] = Point2f(point2.x,point2.y);
    inputQuad[2] = Point2f(point3.x,point3.y);
    inputQuad[3] = Point2f(point4.x,point4.y);  
    
    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f( 0,0 );
    outputQuad[1] = Point2f( src.cols,0);
    outputQuad[2] = Point2f( 0,src.rows);
    outputQuad[3] = Point2f(  src.cols,src.rows);



    vector<Point>pts1 = {point1,point3,point4,point2};
    vector<Point>pts2 = {Point(0,0),Point(720,0),Point(0,720),Point(720,720)};
    
    for (int val =0; val < pts1.size(); val++){
        circle(src,pts1[val],5,Scalar(0,0,255),-1);
        
    }
    Mat M;
    M = getPerspectiveTransform(inputQuad,outputQuad);

    Mat dst;
    warpPerspective(gray,dst,M,dst.size());//Point(1000,1000));
    int min_rad = 20;
    int max_rad = 100;
    //imshow('titre',src)



    //circle detect
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/int(minDist),  
                 getTrackbarPos("param1", sourceDisplayCircle),getTrackbarPos("param2", sourceDisplayCircle),getTrackbarPos("minRadius", sourceDisplayCircle), getTrackbarPos("maxRadius", sourceDisplayCircle) 
    );
    // HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
    //              gray.rows/4,  // change this value to detect circles with different distances to each other
    //              100, 30, 5, 80// change the last two parameters
    //         // (min_radius & max_radius) to detect larger circles
    // );
    //display circles
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);

        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);

        //calculate distance
        double distance = distance_finder(focal_length, real_item_width, radius);
        //cout << "distance " << distance << "\n";
        Mat test = Mat::zeros( 3,3,M.type());
        test.at<double>(0,0) =double(c[0]);
        test.at<double>(1,0) =double(c[1]);
        test.at<double>(2,0) =1.0;
        Mat result = M*test;
        result.at<double>(0,0) /= result.at<double>(2,0); // scale
        result.at<double>(1,0) /= result.at<double>(2,0); // scale
        center.x = result.at<double>(0,0);
        center.y = result.at<double>(1,0);
        circle(dst,center,5,(0,255,0),-1);

        /*value to return
        center.x = result.at<double>(0,0);
        center.y = result.at<double>(1,0);*/
        float x = ((float)center.x*0.50f)/(dst.cols);
        float y = ((float)center.y*0.50f)/(dst.rows);

        y = 0.235 - y;
        x = 0.25-x;

        x_balle = x;
        y_balle = y;
        printf("x: %f     y:%f\n",x,y);



    }

    //display image windows
    imshow("detected circles", src);
    imshow("detected in plan", dst);

    


}

void plaqueDetect(){

    //resize(frame, frame, Size(), 0.75, 0.75);

    // clone image
    Mat image = frame.clone();
    Mat blur;
    pyrMeanShiftFiltering(image,blur,11,21);
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Mat thresh;
    threshold(gray,thresh,0,255,THRESH_BINARY_INV + THRESH_OTSU);
    Mat sortie;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(12, 12));
    morphologyEx(thresh, sortie, MORPH_OPEN, kernel);
    kernel = getStructuringElement(MORPH_RECT, Size(20, 20));
    morphologyEx(sortie, sortie, MORPH_CLOSE, kernel);

    Mat edged;    
    Canny(sortie, edged, 170, 255);

    std::vector<std::vector<Point> > cnts;
    findContours( edged, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

    std::vector<Point>  contours;
    if (cnts.size() == 2) {
        contours = cnts[0] ;
    } else {
        cnts[1];
    }
    std::vector<Point> c;
    for (int i = 0; i < cnts.size() ; i++){
        //peri = arcLength(c, True);
        vector<Point> approx;
        approxPolyDP(cnts[i],approx, 0.015 * arcLength(cnts[i], true), true);
        if (approx.size() == 4){
            cout <<"rectangle detected\n";
            point1 = approx[0];
            point3 = approx[1];
            point4 = approx[2];
            point2 = approx[3];

            cout << "point1 " << point1.x <<" "<<point1.y<<"\n";
            cout << "point2 " << point2.x <<" "<<point2.y<<"\n";
            cout << "point3 " << point3.x <<" "<<point3.y<<"\n";
            cout << "point4 " << point4.x <<" "<<point4.y<<"\n";
            //x,y,w,h = cv2.boundingRect(approx)
            //rectangle(image,(x,y),(x+w,y+h),(36,255,12),2)
            
            //circle(image,point1,5,Scalar(0,0,255),-1);
            //circle(image,point2,5,Scalar(0,0,255),-1);
            //circle(image,point3,5,Scalar(0,0,255),-1);
            //circle(image,point4,5,Scalar(0,0,255),-1);
            
            //imshow("fermeture",sortie);
            //imshow("thresh", thresh);
            
            //imshow("plaque", image);
            //imshow("contours",edged);
            exitPlaque = true;
        }

    }
    
}
    /*
    // --------------------------------Pre-traitement de l'image 
    //Prepare the image for findContours
    cvtColor(image, image, COLOR_BGR2GRAY);
    threshold(image, image, 125, 255, THRESH_BINARY);
    image = ~image; // inverse image
    //imshow( "binaire", image );
    //ellipse opening
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(40, 40));
    //matrix result
    Mat morph;
    morphologyEx(image, morph, MORPH_CLOSE, kernel);
    //line opening to delete wires
    kernel = getStructuringElement(MORPH_RECT, Size(2, 30));
    morphologyEx(morph, morph, MORPH_OPEN, kernel);
    
    //imshow( "fermeture", morph );
    //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
    std::vector<std::vector<Point> > contours;
    Mat contour = morph.clone();
    findContours( contour, contours, RETR_LIST, CHAIN_APPROX_NONE );
    Mat contourImage(morph.size(), CV_8UC3, Scalar(0,0,0));
    Mat image_contours = frame.clone();
    Scalar colors[3];
    colors[0] = Scalar(255, 0, 0);
    colors[1] = Scalar(0, 255, 0);
    colors[2] = Scalar(0, 0, 255);
    for (size_t idx = 0; idx < contours.size(); idx++) {
        drawContours(image_contours, contours, idx, colors[idx % 3]);
    }
    imshow("Contours", image_contours);
    //finding base
    float biggest_area = 0.0;
    int largest_contour_index = 1;
    Mat drawing = Mat::zeros( morph.size(), CV_8UC3 );
    for( size_t i = 1; i < contours.size(); i++ )
    {
        
        float a = contourArea( contours[i], false );
        if (a > biggest_area )
            {
             largest_contour_index = i;
             biggest_area = a;
            }
    }
    Mat image_contours2 = frame.clone();
    drawContours(image_contours2, contours, largest_contour_index, Scalar(255, 255, 255));
    imshow("Plus grand contour", image_contours2);
    Mat plaque =  Mat::zeros( morph.size(), CV_8UC3 );
    drawContours(plaque, contours, largest_contour_index, Scalar(255, 255, 255));
    cvtColor(plaque, plaque, COLOR_BGR2GRAY);
    
    imshow("plaque", plaque);
    int blockSize = 20;
    int apertureSize = 5;
    double k = 0.01;
    Mat dst = Mat::zeros( plaque.size(), CV_32FC1 );
    cornerHarris( plaque, dst, blockSize, apertureSize, k );
    
    //corners detection
    Mat dst_norm, dst_norm_scaled;
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );
    for( int i = 0; i < dst_norm.rows ; i++ )
    {
        for( int j = 0; j < dst_norm.cols; j++ )
        {
            if( (int) dst_norm.at<float>(i,j) > thresh )
            {
                circle( dst_norm_scaled, Point(j,i), 5,  Scalar(255), 2, 8, 0 );
            }
        }
    }
    const char* corners_window = "Corners detected";
    namedWindow( corners_window );
    imshow( corners_window, dst_norm_scaled );
    // //medianBlur(gray, gray, 5);
    // vector<Vec3f> circles;
    // HoughCircles(dst_norm_scaled, circles, HOUGH_GRADIENT, 1,
    //              dst_norm_scaled.rows/4,10,30,5,20// change the last two parameters
    //         // (min_radius & max_radius) to detect larger circles
    // );
    // // cout << "test " << gray.rows/int(minDist) <<"\n";
    // for( size_t i = 0; i < circles.size(); i++ )
    // {   
    //     cout << "cercles"<<"\n";
    //     Vec3i c = circles[i];
    //     Point center = Point(c[0], c[1]);
    //     // circle center
    //     circle( image_contours, center, 1, Scalar(0,100,100), 3, LINE_AA);
    //     // circle outline
    //     int radius = c[2];
    //     circle( image_contours, center, radius, Scalar(0,255,0), 3, LINE_AA);
    //     //cout << "radius" << radius << "\n";
    //     double distance = distance_finder(focal_length, real_item_width, radius);
    //     cout << "distance " << distance << "\n";
    // }
    imshow("Contours", image_contours);*/


//}



// void rectanglesDetect(){
//     const char* sourceDisplayRectangle = "rectangleDetect";
//     namedWindow( sourceDisplayRectangle );
//     const int max_thresh = 255;
//     createTrackbar("method", sourceDisplayRectangle, 0, max_thresh, nothing );
//     createTrackbar("ofset", sourceDisplayRectangle, 0, max_thresh, nothing );
//     // cout << firstTimeCircle;
//     if (firstTimeRectangle){
//         setTrackbarPos("method", sourceDisplayRectangle, 1);
//         setTrackbarPos("ofset", sourceDisplayRectangle, 1);
//         cout << "firstTimeRectangle\n";
//         firstTimeRectangle=false;
//     }
//     rectanglesDetectProcess(sourceDisplayRectangle);
// }

// void rectanglesDetectProcess(const char* sourceDisplayRectangle){

//     Mat src = frame.clone();
//     Mat edge_img;

//     vector <vector<Point>> contours;

//     // Convert the image into a binary image using Canny filter - threshold could be automatically determined using OTSU method
//     Canny(src, edge_img, 30, 100);

//     // Find all contours in the Canny image
//     findContours(edge_img, contours, RETR_LIST, getTrackbarPos("method", sourceDisplayRectangle) );//getTrackbarPos("ofset", sourceDisplayRectangle));// CHAIN_APPROX_SIMPLE);

//     // Iterate through the contours and test if contours are square
//     vector<vector<Point>> all_rectangles;
//     vector<Point> single_rectangle;
//     for (size_t i = 0; i < contours.size(); i++)
//     {

//         // 1. Contours should be approximateable as a polygon
//         approxPolyDP(contours[i], single_rectangle, arcLength(contours[i], true) * 0.2, true);

//         // 2. Contours should have exactly 4 vertices and be convex
//         if (single_rectangle.size() == 4 && isContourConvex(single_rectangle))
//         {
//             //Push the four points into your vector of squares (could be also vector<Rect>)
//             all_rectangles.push_back(single_rectangle);
//             cout << "found rect"<<"\n";
//         }

//     }

//     //cout << "rectangle detected : "<< all_rectangles.size()<<"\n";
//     Scalar color( 0, 255, 0 );
//     for (size_t num_contour = 0; num_contour < all_rectangles.size(); ++num_contour) {
//         if(all_rectangles[num_contour][1].x - all_rectangles[num_contour][0].x > 100){

//             cout << "rectangles detected :" << all_rectangles[num_contour][0] << "\n";
//             cout << "rectangles detected :" << all_rectangles[num_contour][1] << "\n";
//             cout << "rectangles detected :" << all_rectangles[num_contour][3] << "\n";
//             cout << "rectangles detected :" << all_rectangles[num_contour][2] << "\n";



//             drawContours(src, all_rectangles, num_contour, color,FILLED,LINE_AA);
//         }
//     }

//     imshow("detected rectangles", src);
// }