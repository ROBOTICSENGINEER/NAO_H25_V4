#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "mymath.h"
using namespace cv;

#ifndef SEGMENT_H
#define SEGMENT_H




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
            s+=input.at<Vec3b>(i,j)[0];
            s+=input.at<Vec3b>(i,j)[1];
            s+=input.at<Vec3b>(i,j)[2];
        }
    }

    s=s/19200;
    // mb=min(s,127);
    mb=255;
    mg=mb;
    mr=mb;


    for (i=0;i<120;i++)
    {
        for (j=0;j<160;j++)
        {




            b=input.at<Vec3b>(i,j)[0];
            g=input.at<Vec3b>(i,j)[1];
            r=input.at<Vec3b>(i,j)[2];



            /*
            if(b>127)
            {
                output.at<Vec3b>(i,j)[0]=255;
            }
            else
            {
                output.at<Vec3b>(i,j)[0]=0;
            }
            if(g>127)
            {
                output.at<Vec3b>(i,j)[1]=255;
            }
            else
            {
                output.at<Vec3b>(i,j)[1]=0;
            }
            if(r>127)
            {
                output.at<Vec3b>(i,j)[2]=255;
            }
            else
            {
                output.at<Vec3b>(i,j)[2]=0;
            }

*/




            db=power(mb-b)+power(g)+power(r);
            dg=power(b)+power(mg-g)+power(r);
            dr=power(b)+power(g)+power(mr-r);
            dc=power(mb-b)+power(mg-g)+power(r);
            dy=power(b)+power(mg-g)+power(mr-r);
            dm=power(mb-b)+power(g)+power(mr-r);
            dw=power(64+mb-b)+power(64+mg-g)+power(64+mr-r);
            dl=power(64+b)+power(64+g)+power(64+r);





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



void dilation(Mat input,Mat &output)
{
    int b,g,r;
    int i,j,ii,jj,iii,jjj;
    int red;


    for (i=0;i<120;i++)
    {
        for (j=0;j<160;j++)
        {

            red=0;

            for(ii=-1;ii<2;ii++)
            {
                for(jj=-1;jj<2;jj++)
                {
                    iii=min(i+ii,119);
                    iii=max(iii,0);
                    jjj=min(j+jj,159);
                    jjj=max(jjj,0);

                    b=input.at<Vec3b>(iii,jjj)[0];
                    g=input.at<Vec3b>(iii,jjj)[1];
                    r=input.at<Vec3b>(iii,jjj)[2];

                    if(b==0 && g==0 && r==255) red=1;
                }
            }

            if(red==1)
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


#endif // SEGMENT_H







