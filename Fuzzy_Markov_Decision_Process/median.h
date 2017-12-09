#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "mymath.h"
#include "colors.h"
#include <iostream>

using namespace cv;

#ifndef MEDIAN_H
#define MEDIAN_H





void med(Mat &pic)
{
    int b,g,r,i,j,n,m;
    int color,nn;
    int nb,ng,nr,ny,nc,nm,nw,nl;
    Mat acc;

    acc=pic.clone();
    b=0;g=0;r=0;

    for (i=1;i<118;i++)
    {
        for (j=1;j<158;j++)
        {
            nb=0;ng=0;nr=0;nw=0;
            ny=0;nc=0;nm=0;nl=0;
            for(m=0;m<5;m++)
            {
                for(n=0;n<5;n++)
                {
                    readcolor(acc, i+m-2 , j+n-2, b,g,r);
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
            nn=0;
            nn=max(nn,nl); nn=max(nn,nr); nn=max(nn,ng); nn=max(nn,nb);
            nn=max(nn,nc); nn=max(nn,nl); nn=max(nn,nl); nn=max(nn,nw);
            //std::cout << "\n" << "nn = " <<  nn <<"\n";
            //std::cout << "nr = " <<  nr <<"\n";
            //std::cout << "ng = " <<  ng <<"\n";
            //std::cout << "nb = " <<  nb <<"\n";
            //std::cout << "nw = " <<  nw <<"\n";
            //std::cout << "nl = " <<  nl <<"\n";
            //std::cout << "ny = " <<  ny <<"\n";
            //std::cout << "nm = " <<  nm <<"\n";
            //std::cout << "nc = " <<  nc <<"\n";


            if(nn==nl) color=0;
            if(nn==nw) color=7;
            if(nn==ny) color=4;
            if(nn==nm) color=5;
            if(nn==nc) color=6;
            if(nn==nr) color=1;
            if(nn==ng) color=2;
            if(nn==nb) color=3;
            //std::cout << "color = " <<  color <<"\n";
            givecolor(color,b,g,r);
            //std::cout <<i << " , " << j << " , " << b <<" , " <<g<<" , "<<r<<"\n";
            setcolor(pic,i,j,b,g,r);


        }
    }

}
#endif // MEDIAN_H
