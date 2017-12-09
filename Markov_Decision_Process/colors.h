#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "mymath.h"
using namespace cv;

#ifndef COLORS_H
#define COLORS_H

void readcolor(Mat pic, int i , int j, int &B,int &G,int &R)
{
    B=pic.at<Vec3b>(i,j)[0];
    G=pic.at<Vec3b>(i,j)[1];
    R=pic.at<Vec3b>(i,j)[2];
}

void setcolor(Mat &pic, int i , int j , int B , int G ,int R)
{
    pic.at<Vec3b>(i,j)[0]=B;
    pic.at<Vec3b>(i,j)[1]=G;
    pic.at<Vec3b>(i,j)[2]=R;
}

int getcolor(int B,int G,int R)
{
    int cl;
    if(B==255 && G==255 && R==255) cl=7;
    if(B==255 && G==255 && R==0) cl=6;
    if(B==255 && G==0 && R==255) cl=5;
    if(B==0 && G==255 && R==255) cl=4;
    if(B==255 && G==0 && R==0) cl=3;
    if(B==0 && G==255 && R==0) cl=2;
    if(B==0 && G==0 && R==255) cl=1;
    if(B==0 && G==0 && R==0) cl=0;

    return cl;
}

void givecolor(int color,int &B,int &G,int &R)
{
    if(color==0)
    {
        B=0;G=0;R=0;
    }
    if(color==1)
    {
        B=0;G=0;R=255;
    }
    if(color==2)
    {
        B=0;G=255;R=0;
    }
    if(color==3)
    {
        B=255;G=0;R=0;
    }
    if(color==4)
    {
        B=0;G=255;R=255;
    }
    if(color==5)
    {
        B=255;G=0;R=255;
    }
    if(color==6)
    {
        B=255;G=255;R=0;
    }
    if(color==7)
    {
        B=0;G=0;R=255;
    }


}

#endif // COLORS_H
