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


#ifndef SAVESEG_H
#define SAVESEG_H

void save_x(int &k,int &xx,int &yy, AL::ALMotionProxy &motion,AL::ALVideoDeviceProxy &cameraProxy,std::string &subscriberID)
{
    Mat down_left,down_right;
    Mat seg_left,seg_right;
    seg_left.create(120,160, CV_8UC(3));
    seg_right.create(120,160, CV_8UC(3));

    int xl,xc,xr,yu,yc,yd,npix,ex;
    IplImage *imgdown = cvCreateImageHeader(cvSize(160, 120), 8, 3);

    k*=-1;
    motion.angleInterpolation("HeadYaw", k*0.1f, 1.0f, 1);
    AL::ALValue imgd = cameraProxy.getImageRemote(subscriberID);

    //Access the image buffer (6th field) and assign it to the opencv image container.
    imgdown->imageData = (char*)imgd[6].GetBinary();
    cameraProxy.releaseImage(subscriberID);


    if(k<0)
    {
        down_right=imgdown;
        seg(down_right,seg_right);
        med(seg_right);

    }
    else
    {

        down_left=imgdown;
        seg(down_left,seg_left);
        med(seg_left);

        //imshow("down-right",down_right);
        //imshow("down-left",down_left);
        imshow("seg-right",seg_right);
        imshow("seg-left",seg_left);
        std::cout << "\n" << "===="<<"\n";
        colorfea(1,seg_right,xl,xc,xr,yu,yc,yd,npix,ex);
        std::cout << "\n" << "right" <<"\n";
        //std::cout << "\n" << "ex = " <<  ex <<"\n";
        //std::cout << "xl = " <<  xl <<"\n";
        std::cout << "xc = " <<  xc <<"\n";
        //std::cout << "xr = " <<  xr <<"\n";
        //std::cout << "yu = " <<  yu <<"\n";
        std::cout << "yc = " <<  yc <<"\n";
        //std::cout << "yd = " <<  yd <<"\n";
        std::cout << "npix = " <<  npix <<"\n";

        xx=yc;
        yy=xc;

        colorfea(1,seg_left,xl,xc,xr,yu,yc,yd,npix,ex);
        std::cout << "\n" << "left" <<"\n";
        //std::cout << "\n" << "ex = " <<  ex <<"\n";
        //std::cout << "xl = " <<  xl <<"\n";
        std::cout << "xc = " <<  xc <<"\n";
        //std::cout << "xr = " <<  xr <<"\n";
        //std::cout << "yu = " <<  yu <<"\n";
        std::cout << "yc = " <<  yc <<"\n";
        //std::cout << "yd = " <<  yd <<"\n";
        std::cout << "npix = " <<  npix <<"\n";

    }


}



#endif // SAVESEG_H
