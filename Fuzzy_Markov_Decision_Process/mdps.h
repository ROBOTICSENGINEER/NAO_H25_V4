#ifndef MDPs_H
#define MDPs_H
#include <iostream>
#include "mymath.h"


signed int MDPs_nextstate(unsigned int s, unsigned int a)
{
    signed int i,j;
    unsigned int ss;

    j=s/5;
    i=s-j*5;

    // action
    // 7 8 1
    // 6 0 2
    // 5 4 3

    switch(a)
    {
    case 0:
        i=i;
        j=j;
        break;
    case 1:
        j=j-1;
        i=i+1;
        break;
    case 2:
        i=i+1;
        break;
    case 3:
        j=j+1;
        i=i+1;
        break;
    case 4:
        j=j+1;
        break;
    case 5:
        j=j+1;
        i=i-1;
        break;
    case 6:
        i=i-1;
        break;
    case 7:
        i=i-1;
        j=j-1;
        break;
    case 8:
        j=j-1;
        break;
    default:
        std::cout << "error in a";
    }

    if(i==-1) i=0;
    if(i==5) i=4;
    if(j==-1) j=0;
    if(j==5) j=4;

    ss=i+j*5;

    return ss;

}

void MDPs_prstate(signed int ss,signed int aa,signed int &sp1,signed int &sp2,signed int &sp3,signed int &sp4)
{
    signed int i,j;
    unsigned int a1,a2,a3,a4;

    j=ss/5;
    i=ss-j*5;

    // action
    // 7 8 1
    // 6 0 2
    // 5 4 3

    a1=0;
    a2=0;


    switch(aa)
    {
    case 0:
        a1=0;
        a2=0;
        a3=0;
        a4=0;
        break;
    case 1:
        a1=3;
        a2=2;
        a3=8;
        a4=7;
        break;
    case 2:
        a1=4;
        a2=3;
        a3=1;
        a4=8;
        break;
    case 3:
        a1=5;
        a2=4;
        a3=2;
        a4=1;
        break;
    case 4:
        a1=6;
        a2=5;
        a3=3;
        a4=2;
        break;
    case 5:
        a1=7;
        a2=6;
        a3=4;
        a4=3;
        break;
    case 6:
        a1=8;
        a2=7;
        a3=5;
        a4=4;
        break;
    case 7:
        a1=1;
        a2=8;
        a3=6;
        a4=5;
        break;
    case 8:
        a1=2;
        a2=1;
        a3=7;
        a4=6;
        break;
    default:
        std::cout << "error in aa";
    }

    sp1 =MDPs_nextstate(ss,a1);
    sp2 =MDPs_nextstate(ss,a2);
    sp3 =MDPs_nextstate(ss,a3);
    sp4 =MDPs_nextstate(ss,a4);

}


/*
float Q(signed int s,signed int aa,float qhat)
{
    float q;
    q=R(s,a)+gama*V;
    return q;
}


float V(s,qhat)
{
    float value=0;
    float vv;
    int aa;

    for (aa=0;aa<8;aa++)
    {
        vv=Q(s,aa,qhat);
        value = max(value,vv);
    }

}
*/


void MDPs_VI(float gama, float R[5][5], float value_function[5][5])
{
    // Value iteration
    signed int i,j,k,aa,sp,sp1,sp2,sp3,sp4,ss,a;
    signed int i0,i1,i2,j0,j1,j2,i3,j3,i4,j4;
    float vm,vvv,bp;
    float Psasp=0.2;
    float Psasp1=0.2;
    float Psasp2=0.2;
    float Psasp3=0.2;
    float Psasp4=0.2;
    float b[5][5];
    //std::cout << "\nhere 1 = \n";

    // Init value function as 0
    for(j=0;j<5;j++)
    {
        for(i=0;i<5;i++)
        {
            value_function[i][j]=0.0;
        }
    }
    //std::cout << "\nhere 01 = \n";

    for (k=0;k<20;k++)
    {
        //std::cout << "\nk = \t" << k<< "\n\n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                //std::cout << "\nhere: i = " << i << "\tj = " << j << "\n";
                vm=-100;
                ss=i+j*5;
                for(aa=0;aa<9;aa++)
                {
                    //std::cout << "\nhere aa = "<< aa<<"\n";
                    sp=MDPs_nextstate(ss,aa);
                    MDPs_prstate(ss,aa,sp1,sp2,sp3,sp4);
                    j0=sp/5;
                    i0=sp-j0*5;
                    j1=sp1/5;
                    i1=sp1-j1*5;
                    j2=sp2/5;
                    i2=sp2-j2*5;
                    j3=sp3/5;
                    i3=sp3-j3*5;
                    j4=sp4/5;
                    i4=sp4-j4*5;
                    //std::cout << "\nbefore vvv \n";
                    //std::cout << "\n"<<ss<<"\t"<< sp<<"\t"<<sp1<<"\t"<< sp2<<"\n"; eslah shavada sp3 sp4
                    //std::cout << "\n\t\t\t"<<i0<<" , "<< j0<<"\t\t"<< i1<<" , "<< j1<<"\t\t"<< i2<<" , "<< j2<<"\t"<<"\n";
                    //std::cout << "\nvalue_functions\t\t"<< value_function[i0][j0];
                    //std::cout << "\t\t"<< value_function[i1][j1];
                    //std::cout << "\t\t"<< value_function[i2][j2]<<"\n";

                    vvv=Psasp*value_function[i0][j0]+Psasp1*value_function[i1][j1]+Psasp2*value_function[i2][j2]+Psasp3*value_function[i3][j3]+Psasp4*value_function[i4][j4];
                    //std::cout << "\nafter vvv \n";
                    vm=maxf(vm,vvv);
                }
                bp=R[i][j]+vm*gama;
                //std::cout << "\nvm=\t"<< vm << "\tR["<<i<<"]["<<j<<"] =\t"<<R[i][j]<< "\tbp = \t"<<bp<<"\n";
                b[i][j]=minf(bp,1.0);
                //std::cout << "\nb["<<i<<"]["<<j<<"]=\t"<< b[i][j] << "\n";


            }
        }
        //std::cout << "\nhere 2 = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                value_function[i][j]=b[i][j];
                //std::cout << "\nb[i][j]=\t"<< b[i][j] << "\n";
            }
        }

      /*  std::cout << "\nvalue_function[i][j] = \n";
        for(j=0;j<5;j++)
        {
            for(i=0;i<5;i++)
            {
                std::cout << value_function[i][j]<<"\t";
            }
            std::cout << "\n";
        } */


    }
}

#endif // MDPs_H
