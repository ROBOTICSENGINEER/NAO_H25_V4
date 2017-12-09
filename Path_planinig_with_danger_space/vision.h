// readcolor , setcolor , getcolor , givecolor
// seg , med , dilation
// pixcount , mesh

#ifndef VISION_H
#define VISION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "mymath.h"
#include <iostream>

using namespace cv;

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
    if(B==255 && G==255 && R==255) cl=7; // white
    if(B==255 && G==255 && R==0) cl=6; // cyan
    if(B==255 && G==0 && R==255) cl=5; // magna
    if(B==0 && G==255 && R==255) cl=4; // yellow
    if(B==255 && G==0 && R==0) cl=3; // blue
    if(B==0 && G==255 && R==0) cl=2; // green
    if(B==0 && G==0 && R==255) cl=1; // red
    if(B==0 && G==0 && R==0) cl=0; // black

    return cl;
}

void givecolor(int color,int &B,int &G,int &R)
{
    if(color==0)
    {
        B=0;G=0;R=0; // black
    }
    if(color==1)
    {
        B=0;G=0;R=255; // red
    }
    if(color==2)
    {
        B=0;G=255;R=0; // green
    }
    if(color==3)
    {
        B=255;G=0;R=0; // blue
    }
    if(color==4)
    {
        B=0;G=255;R=255; // yellow
    }
    if(color==5)
    {
        B=255;G=0;R=255; // magna
    }
    if(color==6)
    {
        B=255;G=255;R=0; // cyan
    }
    if(color==7)
    {
        B=0;G=0;R=255;  // white
    }
}

void seg(Mat input,Mat &output)
{
    int b,g,r,i,j;
    int dr,db,dg,dy,dm,dc,dl,dw,d;
    int mb=255,mg=255,mr=255,s=0;

    b=0;g=0;r=0;


    for (i=0;i<120;i++)
    {
        for (j=0;j<160;j++)
        {
            readcolor(input,i,j,b,g,r);
            /*
            b=input.at<Vec3b>(i,j)[0];
            g=input.at<Vec3b>(i,j)[1];
            r=input.at<Vec3b>(i,j)[2];


            if(b>127)
            {
                b=255;
            }
            else
            {
                b=0;
            }
            if(g>127)
            {
                g=255;
            }
            else
            {
                g=0;
            }
            if(r>127)
            {
                r=255;
            }
            else
            {
                r=0;
            }

            readcolor(input,i,j,b,g,r);
            */


            db=power(mb-b)+power(g)+power(r);
            dg=power(b)+power(mg-g)+power(r);
            dr=power(b)+power(g)+power(mr-r);
            dc=power(mb-b)+power(mg-g)+power(r);
            dy=power(b)+power(mg-g)+power(mr-r);
            dm=power(mb-b)+power(g)+power(mr-r);
            dw=power(96+mb-b)+power(96+mg-g)+power(96+mr-r);
            dl=power(96+b)+power(96+g)+power(96+r);

            d=db;
            d=min(d,dg);
            d=min(d,dr);
            d=min(d,dy);
            d=min(d,dm);
            d=min(d,dc);
            d=min(d,dl);
            d=min(d,dw);


            if(d==db)
            {
                output.at<Vec3b>(i,j)[0]=255;
                output.at<Vec3b>(i,j)[1]=0;
                output.at<Vec3b>(i,j)[2]=0;
            }
            if(d==dg)
            {
                output.at<Vec3b>(i,j)[0]=0;
                output.at<Vec3b>(i,j)[1]=255;
                output.at<Vec3b>(i,j)[2]=0;
            }
            if(d==dr)
            {
                output.at<Vec3b>(i,j)[0]=0;
                output.at<Vec3b>(i,j)[1]=0;
                output.at<Vec3b>(i,j)[2]=255;
            }
            if(d==dy)
            {
                output.at<Vec3b>(i,j)[0]=0;
                output.at<Vec3b>(i,j)[1]=255;
                output.at<Vec3b>(i,j)[2]=255;
            }
            if(d==dm)
            {
                output.at<Vec3b>(i,j)[0]=255;
                output.at<Vec3b>(i,j)[1]=0;
                output.at<Vec3b>(i,j)[2]=255;
            }
            if(d==dc)
            {
                output.at<Vec3b>(i,j)[0]=255;
                output.at<Vec3b>(i,j)[1]=255;
                output.at<Vec3b>(i,j)[2]=0;
            }
            if(d==dl)
            {
                output.at<Vec3b>(i,j)[0]=0;
                output.at<Vec3b>(i,j)[1]=0;
                output.at<Vec3b>(i,j)[2]=0;
            }
            if(d==dw)
            {
                output.at<Vec3b>(i,j)[0]=255;
                output.at<Vec3b>(i,j)[1]=255;
                output.at<Vec3b>(i,j)[2]=255;
            }


        }
    }
}

void med(Mat &pic)
{
    int b,g,r,i,j,n,m;
    int color,nn;
    int nb,ng,nr,ny,nc,nm,nw,nl;
    Mat acc;

    acc=pic.clone();
    b=0;g=0;r=0;

    for (i=2;i<117;i++)
    {
        for (j=2;j<157;j++)
        {
            nb=0;ng=0;nr=0;nw=0;
            ny=0;nc=0;nm=0;nl=0;
            for(m=0;m<5;m++)
            {
                for(n=0;n<5;n++)
                {
                    readcolor(acc, i+m-1 , j+n-1, b,g,r);
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
            nn=max(nn,ny); nn=max(nn,nc); nn=max(nn,nm); nn=max(nn,nw);
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

void dilation(Mat input,Mat &output)
{
    int b,g,r;
    int i,j,ii,jj,iii,jjj;
    int red,blu;


    for (i=0;i<120;i++)
    {
        for (j=0;j<160;j++)
        {
            readcolor(input, i ,j, b,g,r);
            blu=0;
            if(b==255 && g==0 && r==0) blu=1;

            red=0;
            for(ii=-1;ii<2;ii++)
            {
                for(jj=-1;jj<2;jj++)
                {
                    iii=min(i+ii,119);
                    iii=max(iii,0);
                    jjj=min(j+jj,159);
                    jjj=max(jjj,0);
                    readcolor(input, iii ,jjj, b,g,r);
                    if(b==0 && g==0 && r==255) red=1;
                }
            }

            if(red==1 && blu==0)
            {
                output.at<Vec3b>(i,j)[0]=0;
                output.at<Vec3b>(i,j)[1]=0;
                output.at<Vec3b>(i,j)[2]=255;
            }
            else
            {
                output.at<Vec3b>(i,j)[0]=input.at<Vec3b>(i,j)[0];
                output.at<Vec3b>(i,j)[1]=input.at<Vec3b>(i,j)[1];
                output.at<Vec3b>(i,j)[2]=input.at<Vec3b>(i,j)[2];
            }

        }
    }
}

void pixcount(Mat &pic,int i1,int i2,int j1,int j2,float &na,float &nr,float &ny,float &ng, float &nb)
{
    int b,g,r,i,j,n,m;
    int color,nn;
    int nc,nm,nw,nl;

    b=0;g=0;r=0;
    nb=0;ng=0;nr=0;nw=0;
    ny=0;nc=0;nm=0;nl=0;
    na=0;


    for (i=i1;i<i2;i++)
    {
        for (j=j1;j<j2;j++)
        {
            na++;
            readcolor(pic,j,i,b,g,r);
            //std::cout << "loop : " <<i << " , " << j << " , " << b <<" , " <<g<<" , "<<r<<"\n";
            color=getcolor(b,g,r);
            //std::cout << "loop : color = " <<  color <<"\n";
            if(color==0) nl++;  // black
            if(color==1) nr++; // red
            if(color==2) ng++; // green
            if(color==3) nb++; // blue
            if(color==4) ny++; // yellow
            if(color==5) nm++; // magna
            //if(color==6) ng++; // green //
            if(color==6) nc++; // cyan
            if(color==7) nw++; // white
        }
    }
}

void mesh(Mat &pic,float pr[5][5],float py[5][5],float pg[5][5],float pb[5][5])
{
    int b,g,r,i,j,n,m;
    int color,nn;
    float nb,ng,nr,ny,nc,nm,nw,nl,na;
    int u1[5]={0,32,64,96,128};
    int u2[5]={31,63,95,127,159};
    int v1[5]={0,23,40,63,93};
    int v2[5]={22,39,62,92,119};

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            pixcount(pic,u1[i],u2[i],v1[j],v2[j],na,nr,ny,ng,nb);
            pr[i][j]=nr/na;
            py[i][j]=ny/na;
            pg[i][j]=ng/na;
            pb[i][j]=nb/na;
        }
    }
}

#endif // VISION_H
