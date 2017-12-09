#include <iostream>
#include <string>

#include <alerror/alerror.h>

#include <alproxies/altexttospeechproxy.h>

#include <alproxies/almotionproxy.h>

#include <alproxies/alrobotpostureproxy.h>

#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alproxies/alvideodeviceproxy.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"




#include "segment.h"
#include "median.h"
#include "state.h"
#include "mymath.h"
#include <math.h>

#define PI 3.14159265

int main()
{
    int i,j,k;
    float xt=0,yt=1.2;
    char ip[]="192.168.1.5";
    //char ip[]="172.16.189.36";
    int port=9559;
    AL::ALMotionProxy motion(ip,port);
    AL::ALRobotPostureProxy robotPosture(ip,port);
    AL::ALTextToSpeechProxy tts(ip,port);
    AL::ALVideoDeviceProxy cameraProxy(ip,port);


    tts.say("square 2");

    robotPosture.goToPosture("StandInit", 0.5f);
    motion.walkInit();
    motion.angleInterpolation("HeadPitch", 0.28f, 1.0f, 1);



    std::string clientName = cameraProxy.subscribe("test", AL::kQQVGA, AL::kBGRColorSpace, 5);
    cameraProxy.setParam(AL::kCameraSelectID, 1); //  1=down , 0= up

    Mat center0 = Mat(cv::Size(160,120), CV_8UC3);
    Mat seg0;
    seg0.create(120,160, CV_8UC(3));

    int ii=0;
    float pr[7][5],pg[7][5],pb[7][5];
    float fx,fy,d,fd=15,fj=1,r,r2,r3,teta,phi;
    float q=100,p=10,Fx,Fy;
    float rx,ry;
    unsigned char cteta = 233;
    float X,Y,Z,E2;
    float ox,oy,ex,ey;
    X=0;Y=0;Z=0;
    E2=10.0;
    std::vector<float> P;
    bool useSensorValues = true;
    float mphi = 0.3;


    P = motion.getRobotPosition(useSensorValues);
    std::cout << "Robot position is: " << P << std::endl;
    xt=xt-P[1];
    yt=yt+P[0];


    ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
    std::cout<< "\n\nXd = \t" << xt << "\tYd = \t" << yt ;
    std::cout<< "\nX = \t" << X << "\tY = \t" << Y ;
    std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\tE2 = \t" << E2<<"\n\n";

    while(E2>0.04)
    {


        AL::ALValue img = cameraProxy.getImageRemote(clientName);
        center0.data = (uchar*) img[6].GetBinary();
        cameraProxy.releaseImage(clientName);




        seg(center0,seg0);
        med(seg0);

        imshow("orginal",center0);
        imshow("segmented",seg0);

        cvWaitKey(30000);


        state(seg0,pr,pg,pb);

        std::cout << "\nP(red) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<7;i++)
            {
                std::cout << pr[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\nP(green) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<7;i++)
            {
                std::cout << pg[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\nP(blue) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<7;i++)
            {
                std::cout << pb[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\n\n\n";





        ii++;
        //}

        //////////////////////////// start fuzzy







        Fx=0;Fy=0;

        for(j=0;j<5;j++)    for(j=0;j<5;j++)
        {
            for(i=0;i<7;i++)
            {
                ox=(i-2)*8;
                oy=(5-j)*24;
                r2=power(ox)+power(oy);
                r=sqrt(r2);
                r3=r*r2;
                fx=-(q*(ox))/r3;
                fy=-(q*(oy))/r3;
                Fx=Fx+pr[i][j]*fd*fx;
                Fy=Fy+pr[i][j]*fd*fy;
            }
        }

        teta = atan2(Fy,Fx) * 180/PI;
        std::cout << "daf':\tFx = " << Fx << "\tFy = " << Fy << "\t";
        std::cout << cteta << " = " << teta;

        ox=xt-X;
        oy=yt-Y;
        if(oy<0)
        {
            oy=oy-1;
        }
        else
        {
            oy=oy+1;
        }
        r2=power(ox)+power(oy);
        r=sqrt(r2);
        r3=r*r2;
        fx=(p*ox)/r3;
        fy=(p*oy)/r3;
        sat(fx,20);
        sat(fy,20);
        Fx=Fx+fj*fx;
        Fy=Fy+fj*fy;

        teta = atan2(fy,fx) * 180/PI;
        std::cout << "\njazb:\tFx = " << fj*fx << "\tFy = " << fj*fy << "\t";
        std::cout << cteta << " = " << teta ;


        teta = atan2(Fy,Fx) * 180/PI;
        std::cout << "\njam'\tFx = " << Fx << "\tFy = " << Fy << "\t";
        std::cout << cteta << " = " << teta << std::endl;




        //ry=mag(0.2*sin(teta));
        //rx=mag(0.2*cos(teta));

        rx=(0.05*mag(Fx))/sqrt(power(Fx)+power(Fy));
        ry=(0.06*mag(Fy))/sqrt(power(Fx)+power(Fy));

        std::cout << "\n(rx,ry) = " <<rx<<"\t"<<ry<< std::endl;

        if (teta>=0 && teta<=90)
        {
            phi=atan2(Fy,Fx)-PI/2;
            std::cout << "phi1 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(ry, -rx, phi);
        }

        if (teta>90)
        {
            phi=atan2(Fy,Fx)-PI/2;
            std::cout << "phi2 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(ry, rx, phi);
        }
        if (teta<-90)
        {
            phi=atan2(Fy,Fx)+(3*PI)/2;
            std::cout << "phi3 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(-ry, rx, phi);
        }
        if (teta>=-90 && teta<0)
        {
            phi=atan2(Fy,Fx)-PI/2;
            std::cout << "phi4 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(-ry, -rx, phi);
        }



        //bool useSensorValues = false;

        P = motion.getRobotPosition(useSensorValues);
        std::cout << "Robot position is: " << P << std::endl;
        X=-P[1];
        Y=P[0];
        Z=P[2];

        ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
        std::cout<< "\n\nXd = \t" << xt << "\tYd = \t" << yt ;
        std::cout<< "\nX = \t" << X << "\tY = \t" << Y ;
        std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\tE2 = \t" << E2<<"\n\n";


    }
    cameraProxy.unsubscribe(clientName);
    return 0;
}




///////// end


///////////  shetab

//#include <alproxies/almemoryproxy.h>
//AL::ALMemoryProxy memo(ip,port);

/*   float ax,ay,az;
   for(k=1;k<10;k++)
   {
       ax=memo.getData("Device/SubDeviceList/InertialSensor/AccX/Sensor/Value");
       ay=memo.getData("Device/SubDeviceList/InertialSensor/AccY/Sensor/Value");
       az=memo.getData("Device/SubDeviceList/InertialSensor/AccZ/Sensor/Value");
       std::cout<< "\nAx = \t" << ax << "\tAy = \t" << ay << "\tAz = \t" << az;
   }*/


