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
#include "subgol.h"

//#include <math.h>
#define PI 3.14159265

int main()
{
    int i,j,k;
    float xt=0.0,yt=1.5,phi0=0;
    char ip[]="192.168.0.102";
    int port=9559;
    AL::ALMotionProxy motion(ip,port);
    AL::ALRobotPostureProxy robotPosture(ip,port);
    AL::ALTextToSpeechProxy tts(ip,port);
    AL::ALVideoDeviceProxy cameraProxy(ip,port);


    tts.say("mamdan");

    robotPosture.goToPosture("StandInit", 0.5f);
    motion.walkInit();
    motion.angleInterpolation("HeadPitch", 0.35f, 1.0f, 1);



    std::string clientName = cameraProxy.subscribe("test", AL::kQQVGA, AL::kBGRColorSpace, 5);
    cameraProxy.setParam(AL::kCameraSelectID, 1); //  1=down , 0= up

    Mat center0 = Mat(cv::Size(160,120), CV_8UC3);
    Mat seg0;
    Mat dil0,dil1,dil2,dil3,dil4,dil5,dil6,dil7,dil8,dil9;

    seg0.create(120,160, CV_8UC(3));
    dil0.create(120,160, CV_8UC(3));
    dil1.create(120,160, CV_8UC(3));
    dil2.create(120,160, CV_8UC(3));
    dil3.create(120,160, CV_8UC(3));
    dil4.create(120,160, CV_8UC(3));
    dil5.create(120,160, CV_8UC(3));
    dil6.create(120,160, CV_8UC(3));
    dil7.create(120,160, CV_8UC(3));
    dil8.create(120,160, CV_8UC(3));
    dil9.create(120,160, CV_8UC(3));

    int ii=0;
    float pr[5][5],pg[5][5],pb[5][5],R[5][5];
    float teta,phi,beta1,beta2=0;
    float mvf,fx,fy;
    float X,Y,Z,E2;
    float ex,ey,ephi;
    X=0;Y=0;Z=0;
    E2=10.0;
    std::vector<float> P;
    bool useSensorValues = true;
    unsigned int see_target;
    float gama=0.999;
    float gam_x=0.05,gam_y=0.05,gam_phi=PI/16;
    unsigned int flag_right=0,flag_left=0;


    P = motion.getRobotPosition(useSensorValues);
    std::cout << "Robot position is: " << P << std::endl;
    xt=xt-P[1];
    yt=yt+P[0];
    phi0=P[2];


    ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
    std::cout<< "\n\nXd = \t" << xt << "\tYd = \t" << yt ;
    std::cout<< "\nX = \t" << X << "\tY = \t" << Y ;
    std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\tE2 = \t" << E2<< "\tphi = \t" << phi0<<"\n\n";

    ////////////

    float boz=10;

    float z=0;

    float vb_dx=3500;
    float b_dx=1800;
    float m_dx=900;
    float s_dx=400;
    float vs_dx=150;

    float vb_dy=4000;
    float b_dy=1800;
    float m_dy=1000;
    float s_dy=600;
    float vs_dy=400;


    float vb_jx=3500*boz;
    float b_jx=1800*boz;
    float m_jx=900*boz;
    float s_jx=400*boz;
    float vs_jx=150*boz;

    float vb_jy=4000*boz;
    float b_jy=1800*boz;
    float m_jy=1000*boz;
    float s_jy=600*boz;
    float vs_jy=400*boz;



    float yhj[5][5],yhd[5][5],xhj[5][5],xhd[5][5];

    xhd[0][0]=vs_dx;  xhd[1][0]=vs_dx;  xhd[2][0]=z;      xhd[3][0]=-vs_dx; xhd[4][0]=-vs_dx;
    xhd[0][1]=vs_dx;  xhd[1][1]=vs_dx;  xhd[2][1]=z;      xhd[3][1]=-vs_dx; xhd[4][1]=-vs_dx;
    xhd[0][2]=s_dx;   xhd[1][2]=s_dx;   xhd[2][2]=z;      xhd[3][2]=-s_dx;  xhd[4][2]=-s_dx;
    xhd[0][3]=m_dx;   xhd[1][3]=m_dx;   xhd[2][3]=z;      xhd[3][3]=-m_dx;  xhd[4][3]=-m_dx;
    xhd[0][4]=b_dx;   xhd[1][4]=vb_dx;  xhd[2][4]=z;      xhd[3][4]=-vb_dx; xhd[4][4]=-b_dx;

    yhd[0][0]=-vs_dy; yhd[1][0]=-vs_dy; yhd[2][0]=-vs_dy; yhd[3][0]=-vs_dy; yhd[4][0]=-vs_dy;
    yhd[0][1]=-vs_dy; yhd[1][1]=-s_dy;  yhd[2][1]=-s_dy;  yhd[3][1]=-s_dy;  yhd[4][1]=-vs_dy;
    yhd[0][2]=-s_dy;  yhd[1][2]=-m_dy;  yhd[2][2]=-m_dy;  yhd[3][2]=-m_dy;  yhd[4][2]=-s_dy;
    yhd[0][3]=-m_dy;  yhd[1][3]=-b_dy;  yhd[2][3]=-vb_dy; yhd[3][3]=-b_dy;  yhd[4][3]=-m_dy;
    yhd[0][4]=-m_dy;  yhd[1][4]=-vb_dy; yhd[2][4]=-vb_dy; yhd[3][4]=-vb_dy; yhd[4][4]=-m_dy;

    xhj[0][0]=-vs_jx; xhj[1][0]=vs_jx;  xhj[2][0]=z;      xhj[3][0]=vs_jx;  xhj[4][0]=vs_jx;
    xhj[0][1]=-vs_jx; xhj[1][1]=vs_jx;  xhj[2][1]=z;      xhj[3][1]=vs_jx;  xhj[4][1]=vs_jx;
    xhj[0][2]=-s_jx;  xhj[1][2]=-s_jx;  xhj[2][2]=z;      xhj[3][2]=s_jx;   xhj[4][2]=s_jx;
    xhj[0][3]=-m_jx;  xhj[1][3]=-m_jx;  xhj[2][3]=z;      xhj[3][3]=m_jx;   xhj[4][3]=m_jx;
    xhj[0][4]=-b_jx;  xhj[1][4]=-vb_jx; xhj[2][4]=z;      xhj[3][4]=vb_jx;  xhj[4][4]=b_jx;

    yhj[0][0]=vs_jy;  yhj[1][0]=vs_jy;  yhj[2][0]=vs_jy;  yhj[3][0]=vs_jy;  yhj[4][0]=vs_jy;
    yhj[0][1]=vs_jy;  yhj[1][1]=s_jy;   yhj[2][1]=s_jy;   yhj[3][1]=s_jy;   yhj[4][1]=vs_jy;
    yhj[0][2]=s_jy;   yhj[1][2]=m_jy;   yhj[2][2]=m_jy;   yhj[3][2]=m_jy;   yhj[4][2]=s_jy;
    yhj[0][3]=m_jy;   yhj[1][3]=b_jy;   yhj[2][3]=vb_jy;  yhj[3][3]=b_jy;   yhj[4][3]=m_jy;
    yhj[0][4]=m_jy;   yhj[1][4]=vb_jy;  yhj[2][4]=vb_jy;  yhj[3][4]=vb_jy;  yhj[4][4]=m_jy;


    float cteta,rx,ry;
    float mphi=0.3;
    //int ll=0;
    while(E2>0.04)
    {
        //ll++;
        //std::cout<<"start loop\n";


        AL::ALValue img = cameraProxy.getImageRemote(clientName);
        center0.data = (uchar*) img[6].GetBinary();
        cameraProxy.releaseImage(clientName);

        seg(center0,seg0);
        med(seg0);
        dilation(seg0,dil0);
        dilation(dil0,dil1);
        dilation(dil1,dil2);
        dilation(dil2,dil3);
        dilation(dil3,dil4);
        dilation(dil4,dil5);
        dilation(dil5,dil6);
        dilation(dil6,dil7);
        dilation(dil7,dil8);
        dilation(dil8,dil9);


        imshow("orginal",center0);
        imshow("segmented",seg0);
        imshow("dilation",dil9);



        cvWaitKey(30);

        state(dil9,pr,pg,pb);

        std::cout << "\nP(red) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << pr[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\nP(green) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << pg[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\nP(blue) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << pb[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        //std::cout << "\n\n\n";






        //////////////////////////// start Mamdany


        see_target=1;

        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                if(pb[i][j]>0.1)
                {
                    see_target=2;
                }
            }
        }




        if(see_target==1)
        {
            beta1=atan2(ey,ex); // zavie ta hadaf ba farz noqte budan robot
            beta2=Z; //-phi0; // zavieye charkhide shode ba farz shoro az zavie sefr
            ephi=beta1-beta2; // zavie hadaf dar meydan did robot
            std::cout << "\nephi =" << ephi << "\tex =" << ex <<  "\tey =" << ey <<  "\tbeta1 =" << beta1 <<  "\tbeta2 =" << beta2 << "\n";
            set_target(pb,ephi);

            std::cout << "\nnew: P(blue) = \n";
            for(j=0;j<5;j++)
            {
                for(i=0;i<5;i++)
                {
                    std::cout << pb[i][j]<<"\t";
                }
                std::cout << "\n";
            }

        }


        fx=0;fy=0;

        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                fx=fx+pr[i][j]*xhd[i][j]+pb[i][j]*xhj[i][j];
                fy=fy+pr[i][j]*yhd[i][j]+pb[i][j]*yhj[i][j];
            }
        }

    ///////////////////


        teta = atan2(fy,fx) * 180/PI;
        std::cout << "\njam\tfx = " << fx << "\tfy = " << fy << "\n";
        //std::cout << cteta << " = " << teta << std::endl;




        //ry=mag(0.2*sin(teta));
        //rx=mag(0.2*cos(teta));

        rx=(0.05*mag(fx))/sqrt(power(fx)+power(fy));
        ry=(0.05*mag(fy))/sqrt(power(fx)+power(fy));

        std::cout << "\n(rx,ry) = " <<rx<<"\t"<<ry<< std::endl;

        if (teta>=0 && teta<=90)
        {
            phi=atan2(fy,fx)-PI/2;
            std::cout << "phi1 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(ry, -rx, phi);
        }

        if (teta>90)
        {
            phi=atan2(fy,fx)-PI/2;
            std::cout << "phi2 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(ry, rx, phi);
        }
        if (teta<-90)
        {
            phi=atan2(fy,fx)+(3*PI)/2;
            std::cout << "phi3 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(-ry, rx, phi);
        }
        if (teta>=-90 && teta<0)
        {
            phi=atan2(fy,fx)-PI/2;
            std::cout << "phi4 = " << phi* 180/PI << std::endl;
            sat(phi,mphi);
            motion.moveTo(-ry, -rx, phi);
        }



        //////////////////////////// motion



        //bool useSensorValues = false;

        P = motion.getRobotPosition(useSensorValues);
        std::cout << "Robot position is: " << P << std::endl;
        X=-P[1];
        Y=P[0];
        Z=P[2];

        ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
        std::cout<< "\nXd = \t" << xt << "\tYd = \t" << yt ;
        std::cout<< "\nX = \t" << X << "\tY = \t" << Y ;
        std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\t\tE2 = \t" << E2<<"\n\n";

        //std::cout<<"end loop\n";

    }





    cameraProxy.unsubscribe(clientName);
    return 0;
}


///////// end
