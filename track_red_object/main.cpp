#include <iostream>
#include <string>

#include <alerror/alerror.h>

#include <alproxies/altexttospeechproxy.h>

#include <alproxies/almotionproxy.h>

#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alproxies/alvideodeviceproxy.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include "median.h"
#include "segment.h"
#include "geo.h"
#include "savex.h"

using namespace cv;

int main(int argc, char* argv[])
{
    int k,N,xx,yy;

    char ip[]="192.168.1.5";
    int port=9559;
    AL::ALMotionProxy motion(ip,port);
    AL::ALTextToSpeechProxy tts(ip,port);
    AL::ALVideoDeviceProxy cameraProxy(ip,port);

    tts.say("walking");  // Call the say method

    motion.stiffnessInterpolation("HeadYaw", 1.0f, 1.0f); //motion.stiffnessInterpolation(jointName, stiffness, time);
    //motion.angleInterpolation("HeadYaw", 1.0f, 1.0f, 1);


    // The subscriberID can be altered if other instances are already running
    std::string subscriberID = "subscriberID";
    int fps = 5;
    subscriberID = cameraProxy.subscribe(subscriberID, AL::kQQVGA, AL::kBGRColorSpace, fps);





    //namedWindow("down-left",1);
    //namedWindow("down-right",1);
    namedWindow("seg-left",1);
    namedWindow("seg-right",1);




    k=1;

    cameraProxy.setParam(AL::kCameraSelectID, 1); //  1=down , 0= up

    //while ((char) cvWaitKey(30) != 27)
    yy=0;


    while(yy<70)
    {

        save_x(k,xx,yy,motion,cameraProxy,subscriberID);
        save_x(k,xx,yy,motion,cameraProxy,subscriberID);
        cvWaitKey(30);

        if(xx<60)
        {
            motion.walkInit();

            // Example showing the walkTo command
            // as length of path is less than 0.4m
            // the path will be an SE3 interpolation
            // The units for this command are meters and radians
            float x  = 0.1f;
            float y  = 0.0f;
            // pi/2 anti-clockwise (90 degrees)
            float theta = 0.3f;
            motion.walkTo(x, y, theta);
            // Will block until walk Task is finished


        }
        else if (xx<100)
        {
            motion.walkInit();

            // Example showing the walkTo command
            // as length of path is less than 0.4m
            // the path will be an SE3 interpolation
            // The units for this command are meters and radians
            float x  = 0.1f;
            float y  = 0.0f;
            // pi/2 anti-clockwise (90 degrees)
            float theta = 0.0f;
            motion.walkTo(x, y, theta);
            // Will block until walk Task is finished


        }
        else
        {
            motion.walkInit();

            // Example showing the walkTo command
            // as length of path is less than 0.4m
            // the path will be an SE3 interpolation
            // The units for this command are meters and radians
            float x  = 0.1f;
            float y  = 0.0f;
            // pi/2 anti-clockwise (90 degrees)
            float theta = -0.3f;
            motion.walkTo(x, y, theta);
            // Will block until walk Task is finished


        }


    }




    cameraProxy.unsubscribe(subscriberID);  // Cleanup

    exit(0);
}






//=============================

//addWeighted(up,0.5,down,0.5,0.0,add);  //add=(up+down)/2;
