#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "mymath.h"
#include "colors.h"
using namespace cv;

#ifndef GEO_H
#define GEO_H
void colorfea(int col,Mat pic,int &xl,int &xc,int &xr,int &yu,int &yc,int &yd,int &npix, int &ex)
{
int i,j;
int b,g,r;
int pc;
int si=0;
int sj=0;
npix=0;
xl=119;
xr=0;
xc=0;
yc=0;
yu=119;
yd=0;
for (i=0;i<120;i++)
{
    for(j=0;j<120;j++)
    {
        readcolor(pic,i,j,b,g,r);
        pc=getcolor(b,g,r);
        if (col==pc)
        {
            npix++;
            si=si+i;
            sj=sj+j;
            xl=min(xl,i);
            xr=max(xr,i);
            yu=min(yu,j);
            yd=min(yd,j);
        }
        if(npix!=0)
        {
            xc=si/npix;
            yc=sj/npix;
            ex=1;
        }
        else
        {
            ex=0;
        }

    }
}
}
#endif // GEO_H
