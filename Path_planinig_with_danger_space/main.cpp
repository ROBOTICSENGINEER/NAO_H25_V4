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


#include "mymath.h"
#include "vision.h"
#include "rewards.h"
#include "fuzzy.h"
#include "mdps.h"

//#include <math.h>
#define PI 3.14159265

int main()
{
    int i,j,k;
    float xt=0.0000,yt=3.0000,phi0=0.0000;
    char ip[]="192.168.0.102";
    //char ip[]="172.16.189.36";
    int port=9559;
    AL::ALMotionProxy motion(ip,port);
    AL::ALRobotPostureProxy robotPosture(ip,port);
    AL::ALTextToSpeechProxy tts(ip,port);
    AL::ALVideoDeviceProxy cameraProxy(ip,port);

    tts.say("Danger");


    motion.setSmartStiffnessEnabled(1);
    robotPosture.goToPosture("StandInit", 0.5f);
    motion.walkInit();
    motion.angleInterpolation("HeadPitch", 0.35f, 1.0f, 1);
    motion.angleInterpolation("RShoulderPitch", 2.00f, 0.5f, 1);
    motion.angleInterpolation("LShoulderPitch", 2.00f, 0.5f, 1);


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
    float pr[5][5],py[5][5],pg[5][5],pb[5][5],R[5][5],value_function[5][5];
    float teta=0.0000,phi =0.0000,beta1=0.0000,beta2=0.0000;
    float mvf,fx,fy;
    float X,Y,Z,E2;
    float ex,ey,ephi;
    X=0;Y=0;Z=0;
    E2=10.0;
    std::vector<float> P;
    bool useSensorValues = true;
    unsigned int see_target;
    float gama=0.999;
    float gam_x=0.05,gam_y=0.05,gam=0.1;
    unsigned int flag_right=0,flag_left=0;


    P = motion.getRobotPosition(useSensorValues);
    std::cout << "Robot position is: " << P << std::endl;
    xt=xt-P[1];
    yt=yt+P[0];
    phi0=P[2];


    ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
    std::cout<< "\n\nXd = \t" << xt << "\tYd = \t" << yt ;
    std::cout<< "\nX = \t" << X << "\tY = \t" << Y << "\tphi = \t" << phi0;
    std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\tE2 = \t" << E2<<"\n\n";


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
        //dil9=seg0.clone();
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


        cvWaitKey(3000);

        mesh(dil9,pr,py,pg,pb);

        std::cout << "\nP(red) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << pr[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\nP(yellow) = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << py[i][j]<<"\t";
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
                if(pb[i][j]>0.05)
                {

                    see_target=2;
                }
            }
        }



        if(see_target==2)
        {
            std::cout << "\nI see the target\n";
            for(j=0;j<5;j++)
            {
                for(i=0;i<5;i++)
                {
                    R[i][j]=fis(pr[i][j],py[i][j],pg[i][j],pb[i][j]);
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
                    R[i][j]=fis(pr[i][j],py[i][j],pg[i][j],pb[i][j]);
                }
            }
            beta1=atan2(ey,ex); // zavie ta hadaf ba farz noqte budan robot
            beta2=phi;//-phi0; // zavieye charkhide shode ba farz shoro az zavie sefr
            ephi = beta1-beta2; // zavie hadaf dar meydan did robot

            std::cout << "\nbeta1 = " << beta1;
            std::cout << "\tbeta2 = " << beta2;
            std::cout << "\tephi = " << ephi <<"\n";

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


        //////////////////////////// Fuzzification

        float unit_value_function[5][5];
        float drastic_value_function[5][5];

        float A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A_sum;

        float rew_max=-1000,rew_min=1000,rew_dif=0;



        /*for(j=3;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                rew_max=maxf(rew_max,value_function[i][j]);
                rew_min=minf(rew_min,value_function[i][j]);
            }
        }

            for(i=1;i<4;i++)
            {
                rew_max=maxf(rew_max,value_function[i][2]);
                rew_min=minf(rew_min,value_function[i][2]);
            }*/

        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                rew_max=maxf(rew_max,value_function[i][j]);
                rew_min=minf(rew_min,value_function[i][j]);
            }
        }

       rew_dif=rew_max-rew_min;

        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                unit_value_function[i][j]=(value_function[i][j]-rew_min)/rew_dif;
            }
        }

        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                drastic_value_function[i][j]=powern(unit_value_function[i][j],21);
            }
        }



        std::cout << "\nunit_value_function = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << unit_value_function[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        std::cout << "\ndrastic_value_function = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << drastic_value_function[i][j]<<"\t";
            }
            std::cout << "\n";
        }

        A1=drastic_value_function[1][2];
        A2=drastic_value_function[2][2];
        A3=drastic_value_function[3][2];
        A4=drastic_value_function[0][3];
        A5=drastic_value_function[1][3];
        A6=drastic_value_function[2][3];
        A7=drastic_value_function[3][3];
        A8=drastic_value_function[4][3];
        A9=drastic_value_function[0][4];
        A10=drastic_value_function[1][4];
        A11=drastic_value_function[2][4];
        A12=drastic_value_function[3][4];
        A13=drastic_value_function[4][4];

     /*   std::cout  << "\n\n";
        std::cout  << A1 << "\n";
        std::cout  << A2 << "\n";
        std::cout  << A3 << "\n";
        std::cout  << A4 << "\n";
        std::cout  << A5 << "\n";
        std::cout  << A6 << "\n";
        std::cout  << A7 << "\n";
        std::cout  << A8 << "\n";
        std::cout  << A9 << "\n";
        std::cout  << A10 << "\n";
        std::cout  << A11 << "\n";
        std::cout  << A12 << "\n";
        std::cout  << A13 << "\n";
*/

        ///////////////////////////// Fuzzy inference

        float tet_z=0,tet_vs=PI/12,tet_s=PI/6,tet_m=PI/4,tet_l=PI/2;


        float t2=tet_z;
        float t6=tet_z;
        float t11=tet_z;

        float t1=tet_vs;
        float t3=-tet_vs;

        float t5=tet_s;
        float t7=-tet_s;

        float t4=tet_m;
        float t10=tet_m;
        float t8=-tet_m;
        float t12=-tet_m;

        float t9=tet_l;
        float t13=-tet_l;

        A_sum=A1+A2+A3+A4+A5+A6+A7+A8+A9+A10+A11+A12+A13;
        teta=(A1*t1+A2*t2+A3*t3+A4*t4+A5*t5+A6*t6+A7*t7+A8*t8+A9*t9+A10*t10+A11*t11+A12*t12+A13*t13)/A_sum;

        //std::cout << "\nA_sum = " << A_sum << "\tteta = " << teta << "\n\n";



        //////////////////////////// motion

        fx=-gam*sin(teta);
        fy=gam*cos(teta);

        std::cout << "\nfx = " << fx;
        std::cout << "\nfy = " << fy;
        std::cout << "\nteta = " << ((teta*180)/PI) << "\n\n";

        //motion.moveTo(fy, -fx, teta);

        P = motion.getRobotPosition(useSensorValues);
        std::cout << "Robot position is: " << P << std::endl;
        X=-P[1];
        Y=P[0];
        phi=P[2];

        ex=xt-X;    ey=yt-Y; E2=power(ex)+power(ey);
        std::cout<< "\nXd = \t" << xt << "\tYd = \t" << yt ;
        std::cout<< "\nX = \t" << X << "\tY = \t" << Y  << "\tphi = \t" << phi;
        std::cout<< "\nEx = \t" << ex << "\tEy = \t" << ey << "\tE2 = \t" << E2<<"\n\n";

    }

    tts.say("end");
    cameraProxy.unsubscribe(clientName);
    return 0;
}


///////// end
