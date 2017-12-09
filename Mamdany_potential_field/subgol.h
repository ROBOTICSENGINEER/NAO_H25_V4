#ifndef SUBGOL_H
#define SUBGOL_H


#include <iostream>

void set_target(float R[5][5],float ephi)
{
    unsigned int i,j;

    if (-1.5708<=ephi && ephi<0.64350)
    {
        i=4;
        j=4;
    }
    else if (0.64350<=ephi && ephi<0.89606)
    {
        i=4;
        j=3;
    }
    else if (0.89606<=ephi && ephi<1.0517)
    {
        i=4;
        j=2;
    }
    else if (1.0517<=ephi && ephi<1.1526)
    {
        i=4;
        j=1;
    }
    else if (1.1526<=ephi && ephi<1.2793)
    {
        i=4;
        j=0;
    }
    else if (1.2793<=ephi && ephi<1.4711)
    {
        i=3;
        j=0;
    }
    else if (1.4711<=ephi && ephi<1.6705)
    {
        i=2;
        j=0;
    }
    else if (1.6705<=ephi && ephi<1.8623)
    {
        i=1;
        j=0;
    }
    else if (1.8623<=ephi && ephi<1.9890)
    {
        i=0;
        j=0;
    }
    else if (1.9890<=ephi && ephi<2.0899)
    {
        i=0;
        j=1;
    }
    else if (2.0899<=ephi && ephi<2.2455)
    {
        i=0;
        j=2;
    }
    else if (2.2455<=ephi && ephi<2.4981)
    {
        i=0;
        j=3;
    }
    else if (ephi>=2.4981)
    {
        i=0;
        j=4;
    }
    else if (ephi<-1.5708)
    {
        i=0;
        j=4;
    }

    R[i][j]=1;


}




#endif // SUBGOL_H
