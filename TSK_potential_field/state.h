#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "mymath.h"
#include "colors.h"
#include <iostream>

using namespace cv;

#ifndef STATE_H
#define STATE_H



void stcount(Mat &pic,int i1,int i2,int j1,int j2,float &na,float &ng, float &nr , float &nb)
{
    int b,g,r,i,j,n,m;
    int color,nn;
    int ny,nc,nm,nw,nl;

    b=0;g=0;r=0;

    nb=0;ng=0;nr=0;nw=0;
    ny=0;nc=0;nm=0;nl=0;
    na=0;


    for (i=i1;i<i2;i++)
    {
        for (j=j1;j<j2;j++)
        {
            na++;

                    readcolor(pic, j , i, b,g,r);
                    //std::cout << "loop : " <<i << " , " << j << " , " << b <<" , " <<g<<" , "<<r<<"\n";
                    color=getcolor(b,g,r);
                    //std::cout << "loop : color = " <<  color <<"\n";
                    if(color==0) nl++;
                    if(color==1) nr++;
                    if(color==2) ng++;
                    if(color==3) nb++;
                    if(color==4) ny++;
                    if(color==5) nm++;
                    if(color==6) ng++; //if(color==6) nc++;
                    if(color==7) nw++;
        }
    }



}


void state(Mat &pic,float pr[7][5],float pg[7][5],float pb[7][5])
{
    int b,g,r,i,j,n,m;
    int color,nn;
    float nb,ng,nr,ny,nc,nm,nw,nl,na;
    int u1[7]={0,12,40,64,96,121,149};
    int u2[7]={11,39,63,96,121,149,159};
    int v1[5]={0,23,40,63,93};
    int v2[5]={22,39,62,92,119};
    //float pr[7][5],pg[7][5],pb[7][5];

    for(i=0;i<7;i++)
    {
        for(j=0;j<5;j++)
        {
            stcount(pic,u1[i],u2[i],v1[j],v2[j],na,ng, nr , nb);
        /*    std::cout << "i = "<< i << "j = "<< j <<"\n";
            std::cout << "nr = \n"<< nr <<"\n";
            std::cout << "ng = \n"<< ng <<"\n";
            std::cout << "nb = \n"<< nb <<"\n";
            std::cout << "na = \n"<< na <<"\n\n\n";*/
            pr[i][j]=nr/na;
            pg[i][j]=ng/na;
            pb[i][j]=nb/na;
        }
    }

 /*   //std::cout << "P(red) = \n"<< pr[6][4]<<"\n";
   // std::cout << "P(green) = \n"<< pg[6][4]<<"\n";
    //std::cout << "P(blue) = \n"<< pb[6][4]<<"\n";
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

    std::cout << "\n\n\n";*/



}



#endif // STATE_H
