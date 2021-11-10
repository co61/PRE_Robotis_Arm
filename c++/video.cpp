//g++ -o video video.cpp $(pkg-config opencv4 --cflags --libs) -I/usr/include/opencv4
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

bool orbbec = false;
int cameraId = 0;

#include <iostream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;

Mat frame, gray, dst, cdst, cdstP;


int thresh = 100;
RNG rng(12345);
void linesDetect();
void circlesDetect();
void circlesDetectProcess(const char*);
void rectanglesDetect();
void linesDetect();
void linesDetectProcess(const char*);

void cannyDetect();
void thresh_callbackMoment(int, void* );
void hullDetect();
void thresh_callbackHull(int, void* );
void nothing(int, void*){
    
}

const char* source_window = "Source";
bool lineArg, circleArg, rectArg, momentArg, hullArg, imageArg = false;
const char* file;

bool firstTimeCircle, firstTimeLine = true;
bool testtest = true;
int main(int argc, char** argv)
{   
    
    vector<string> args(argv, argv+argc);
    for (size_t i = 1; i < args.size(); ++i) {

        if (args[i] == "line") {
            lineArg=true;
        }
        else if (args[i] == "circle") {
            circleArg=true;
        }
        else if (args[i] == "rectangle") {
            rectArg=true;
        }
        else if (args[i] == "moment") {
            momentArg=true;
        }
        else if (args[i] == "hull") {
            hullArg=true;
        }

        else{
            imageArg=true;
            file = argv[i];
        }


        
    }

    
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!imageArg){
        if (!orbbec){
            if(!cap.open(cameraId)){
                return 0;
            }
        }
        /*
        else {
            if(!cap.open(CAP_OPENNI2_ASTRA)){
                return 0;
                }
        }*/
    }


    for(;;)
    {
          if(!imageArg){
            cap >> frame;
          }
          else{
            frame  = imread(file);
          }
          if( frame.empty() ) {
              break; // end of video stream
          }
          cvtColor( frame, gray, COLOR_BGR2GRAY );
          blur( gray, gray, Size(3,3) );
          //namedWindow( source_window );
          //imshow( source_window, frame );
          //imshow("Gray", gray);
                   

          if (lineArg){
              linesDetect();
          }
          if (circleArg){
              circlesDetect();
          }
          if(rectArg){
              rectanglesDetect();
          }
          if (momentArg){
              cannyDetect();
          }
          if (hullArg){
              hullDetect();
          }

          if( waitKey(10) == 27 ){
              break; // stop capturing by pressing ESC 
          }
    }
    // the camera will be closed automatically upon exit
    // cap.close();

    return 0;
}

void linesDetect(){
    const char* sourceDisplayLine = "linesDetect";
    namedWindow( sourceDisplayLine );
    const int max_thresh = 255;
        createTrackbar("rho", sourceDisplayLine, 0, max_thresh, nothing );
        createTrackbar("theta", sourceDisplayLine, 0, max_thresh, nothing );
        createTrackbar("threshold", sourceDisplayLine, 0, max_thresh, nothing );
        createTrackbar("minLineLength", sourceDisplayLine, 0, max_thresh, nothing );
        createTrackbar("maxLineGap", sourceDisplayLine, 0, max_thresh, nothing );

        if (firstTimeLine){
            setTrackbarPos("rho", sourceDisplayLine, 1);
            setTrackbarPos("theta", sourceDisplayLine, 180);
            setTrackbarPos("threshold", sourceDisplayLine, 100);
            setTrackbarPos("minLineLength", sourceDisplayLine, 50);
            setTrackbarPos("maxLineGap", sourceDisplayLine, 10);
            firstTimeLine = false;
            cout << "firstTimeLine\n"; 
        }
        //thresh_callbackMoment( 0, 0 );
        linesDetectProcess(sourceDisplayLine);
}
void linesDetectProcess(const char* sourceDisplayLine){
    int thetaSrc = getTrackbarPos("theta", sourceDisplayLine);
    if(getTrackbarPos("theta", sourceDisplayLine)==0){
        setTrackbarPos("theta", sourceDisplayLine, 1);
        thetaSrc = 1;
    }

    int rhoSrc = getTrackbarPos("rho", sourceDisplayLine);
    if(getTrackbarPos("rho", sourceDisplayLine)==0){
        setTrackbarPos("rho", sourceDisplayLine, 1);
        rhoSrc = 1;
    }

    Mat src = frame.clone();
    // Edge detection
    Canny(frame, dst, 50, 200, 3);
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();


    // Standard Hough Line Transform
    /*
    dst: Output of the edge detector. It should be a grayscale image (although in fact it is a binary one)
    lines: A vector that will store the parameters (r,θ) of the detected lines
    rho : The resolution of the parameter r in pixels. We use 1 pixel.
    theta: The resolution of the parameter θ in radians. We use 1 degree (CV_PI/180)
    threshold: The minimum number of intersections to "*detect*" a line
    srn and stn: Default parameters to zero. Check OpenCV reference for more info.
    */

    vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(dst, lines, rhoSrc, CV_PI/int(thetaSrc), getTrackbarPos("threshold", sourceDisplayLine), 0,0); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }
    // Probabilistic Line Transform
    /*
    dst: Output of the edge detector. It should be a grayscale image (although in fact it is a binary one)
    lines: A vector that will store the parameters (xstart,ystart,xend,yend) of the detected lines
    rho : The resolution of the parameter r in pixels. We use 1 pixel.
    theta: The resolution of the parameter θ in radians. We use 1 degree (CV_PI/180)
    threshold: The minimum number of intersections to "*detect*" a line
    minLineLength: The minimum number of points that can form a line. Lines with less than this number of points are disregarded.
    maxLineGap: The maximum gap between two points to be considered in the same line.
    */

    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, rhoSrc, CV_PI/int(thetaSrc), getTrackbarPos("threshold", sourceDisplayLine), getTrackbarPos("minLineLength", sourceDisplayLine), getTrackbarPos("maxLineGap", sourceDisplayLine) ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }
    // Show results
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
}

void circlesDetect(){
    const char* sourceDisplayCircle = "circleDetect";
    namedWindow( sourceDisplayCircle );
    const int max_thresh = 255;
    createTrackbar("minDist", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("param1", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("param2", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("minRadius", sourceDisplayCircle, 0, max_thresh, nothing );
    createTrackbar("maxRadius", sourceDisplayCircle, 0, max_thresh, nothing );
    // cout << firstTimeCircle;
    if (testtest){
        setTrackbarPos("minDist", sourceDisplayCircle, 4);
        setTrackbarPos("param1", sourceDisplayCircle, 100);
        setTrackbarPos("param2", sourceDisplayCircle, 30);
        setTrackbarPos("minRadius", sourceDisplayCircle, 5);
        setTrackbarPos("maxRadius", sourceDisplayCircle, 80);
        testtest = false;
        cout << "firstTimeCircle\n"; 
    }
    //thresh_callbackMoment( 0, 0 );
    circlesDetectProcess(sourceDisplayCircle);
}


void circlesDetectProcess(const char* sourceDisplayCircle){//void circlesDetectCallback(int, void*){
    int minDist = getTrackbarPos("minDist", sourceDisplayCircle);
    if(getTrackbarPos("minDist", sourceDisplayCircle)==0){
        setTrackbarPos("minDist", sourceDisplayCircle, 1);
        minDist = 1;
    }
    // cout<<getTrackbarPos("param1", sourceDisplayCircle) <<"\n";
    Mat src = frame.clone();
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/int(minDist),  // change this value to detect circles with different distances to each other
                 getTrackbarPos("param1", sourceDisplayCircle),getTrackbarPos("param2", sourceDisplayCircle),getTrackbarPos("minRadius", sourceDisplayCircle), getTrackbarPos("maxRadius", sourceDisplayCircle) // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }
    imshow("detected circles", src);
}

void rectanglesDetect(){

    Mat src = frame.clone();
    Mat edge_img;

    vector <vector<Point>> contours;

    // Convert the image into a binary image using Canny filter - threshold could be automatically determined using OTSU method
    Canny(src, edge_img, 30, 100);

    // Find all contours in the Canny image
    findContours(edge_img, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Iterate through the contours and test if contours are square
    vector<vector<Point>> all_rectangles;
    vector<Point> single_rectangle;
    for (size_t i = 0; i < contours.size(); i++)
    {

        // 1. Contours should be approximateable as a polygon
        approxPolyDP(contours[i], single_rectangle, arcLength(contours[i], true) * 0.01, true);

        // 2. Contours should have exactly 4 vertices and be convex
        if (single_rectangle.size() == 4 && isContourConvex(single_rectangle))
        {
            // 3. Determine if the polygon is really a square/rectangle using its properties (parallelity, angles etc.)
            // Not necessary for the provided image

            // Push the four points into your vector of squares (could be also vector<Rect>)
            all_rectangles.push_back(single_rectangle);
        }
    }

    if(all_rectangles.size()>0){
        cout << "rectangles detected :" << all_rectangles.size() << "\n";
    }

    for (size_t num_contour = 0; num_contour < all_rectangles.size(); ++num_contour) {
        drawContours(src, all_rectangles, num_contour, Scalar::all(-1));
    }

    imshow("detected rectangles", src);
}

void cannyDetect(){
    const int max_thresh = 255;
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callbackMoment );
    thresh_callbackMoment( 0, 0 );
}

void hullDetect(){
    const int max_thresh = 255;
    createTrackbar( "Hull Canny thresh:", source_window, &thresh, max_thresh, thresh_callbackHull );
    thresh_callbackHull( 0, 0 );
}

void thresh_callbackMoment(int, void* )
{
    if (momentArg){
        Mat canny_output;
        Canny( gray, canny_output, thresh, thresh*2, 3 );
        vector<vector<Point> > contours;
        findContours( canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );
        vector<Moments> mu(contours.size() );
        for( size_t i = 0; i < contours.size(); i++ )
        {
            mu[i] = moments( contours[i] );
        }
        vector<Point2f> mc( contours.size() );
        for( size_t i = 0; i < contours.size(); i++ )
        {
            //add 1e-5 to avoid division by zero
            mc[i] = Point2f( static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)),
                            static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)) );
            cout << "mc[" << i << "]=" << mc[i] << endl;
        }
        Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
            drawContours( drawing, contours, (int)i, color, 2 );
            circle( drawing, mc[i], 4, color, -1 );
        }
        imshow( "Contours", drawing );
        /*
        cout << "\t Info: Area and Contour Length \n";
        for( size_t i = 0; i < contours.size(); i++ )
        {
            cout << " * Contour[" << i << "] - Area (M_00) = " << fixed << setprecision(2) << mu[i].m00
                << " - Area OpenCV: " << contourArea(contours[i]) << " - Length: " << arcLength( contours[i], true ) << endl;
        }*/
    }

}

void thresh_callbackHull(int, void* )
{
    Mat canny_output;
    Canny( gray, canny_output, thresh, thresh*2 );
    vector<vector<Point> > contours;
    findContours( canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );
    vector<vector<Point> >hull( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        convexHull( contours[i], hull[i] );
    }
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color );
        drawContours( drawing, hull, (int)i, color );
    }
    imshow( "Hull", drawing );
}


