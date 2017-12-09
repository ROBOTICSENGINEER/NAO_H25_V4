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
#include "mdps.h"
#include "rewards.h"

//#include <math.h>
#define PI 3.14159265

int main()
{
    int i,j,k;
    float xt=-0.1,yt=1.5,phi0=0;
    char ip[]="192.168.1.9";
    //char ip[]="172.16.189.36";
    int port=9559;
    AL::ALMotionProxy motion(ip,port);
    AL::ALRobotPostureProxy robotPosture(ip,port);
    AL::ALTextToSpeechProxy tts(ip,port);
    AL::ALVideoDeviceProxy cameraProxy(ip,port);


    tts.say("M D 1");

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
    float pr[5][5],pg[5][5],pb[5][5],R[5][5],value_function[5][5];
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





        ii++;


        //////////////////////////// start MDP


        see_target=1;

        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                if(pb[i][j]>0.3)
                {

                    see_target=2;
                }
            }
        }


        ///////////////

        /*   for(j=0;j<7;j++)
        {
            R[0][j]=-0.1;
            R[6][j]=-0.1;
        }

        for(i=1;i<6;i++)
        {
            R[i][0]=-0.1;
            R[i][6]=-0.1;
        }*/

        if(see_target==2)
        {
            std::cout << "\nI see the target\n";
            for(j=0;j<5;j++)
            {
                for(i=0;i<5;i++)
                {
                    R[i+1][j+1]=pb[i][j]-5*pr[i][j]-0.1*pg[i][j];
                }
            }


        }
        else
        {
            std::cout << "\nI can not see a target\n";
            for(j=0;j<5;j++)
            {
                for(i=0;i<5;i++)
                {
                    R[i][j]=-5*pr[i][j]-0.1*pg[i][j];
                    if (R[i][j]>-3 && R[i][j]<-0.11) R[i][j+1]=-3;
                }
            }
            beta1=atan2(ey,ex); // zavie ta hadaf ba farz noqte budan robot
            beta2=phi;//-phi0; // zavieye charkhide shode ba farz shoro az zavie sefr
            ephi=beta1-beta2; // zavie hadaf dar meydan did robot

            set_target_reward(R,ephi);
            //R[0][5]=1;
        }




        std::cout << "\nReward = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << R[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        //std::cout << "\nbefore vi= \n";
        MDPs_VI(gama, R,value_function);
        //std::cout << "\nend vi = \n";


        std::cout << "\nvalue_function = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << value_function[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        //////////////////////////// motion

        mvf=maxf(value_function[1][4],value_function[2][4]);
        mvf=maxf(value_function[3][4],mvf);

        if(mvf==value_function[1][4])
        {
            if (flag_left==0)
            {
                if(mvf>=value_function[0][4])
                {
                    fx=-1*gam_x;
                    fy=gam_y;
                    teta=gam_phi;
                    flag_right=1;
                    flag_left=0;
                }
                else
                {
                    fx=-2*gam_x;
                    fy=gam_y;
                    teta=2*gam_phi;
                    flag_right=1;
                    flag_left=0;
                }
            }
            else
            {
                fx=0;
                fy=2*gam_y;
                teta=0;
                flag_right=0;
                flag_left=0;
                std::cout << "\nflag_left = 1\n";
            }
        }
        if(mvf==value_function[2][4])
        {
            fx=0;
            fy=2*gam_y;
            teta=0;
            flag_right=0;
            flag_left=0;
        }
        if(mvf==value_function[3][4])
        {
            if(flag_right==0)
            {
                if(mvf>=value_function[4][4])
                {
                    fx=gam_x;
                    fy=gam_y;
                    teta=-gam_phi;
                }
                else
                {
                    fx=2*gam_x;
                    fy=gam_y;
                    teta=-2*gam_phi;
                }
            }
            else
            {
                fx=0;
                fy=2*gam_y;
                teta=0;
                flag_right=0;
                flag_left=0;
                std::cout << "\nflag_right = 1\n";
            }

        }



        std::cout << "\nteta = " << ((teta*180)/PI) << "\n\n";
        motion.moveTo(fy, -fx, teta);


        //bool useSensorValues = false;

        P = motion.getRobotPosition(useSensorValues);
        std::cout << "Robot position is: " << P << std::endl;
        X=-P[1];
        Y=P[0];
        Z=P[2];

        ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
        std::cout<< "\nXd = \t" << xt << "\tYd = \t" << yt ;
        std::cout<< "\nX = \t" << X << "\tY = \t" << Y ;
        std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\tE2 = \t" << E2<<"\n\n";

        //std::cout<<"end loop\n";

    }





    cameraProxy.unsubscribe(clientName);
    return 0;
}


///////// end
