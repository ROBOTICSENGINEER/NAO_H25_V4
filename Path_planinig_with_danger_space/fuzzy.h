#ifndef FUZZY_H
#define FUZZY_H
#include <math.h>
#include "mymath.h"

const float fwt=1.5;

const float F_Z=0.00;
const float F_S=0.25;
const float F_M=0.50;
const float F_B=0.75;
const float F_H=1.00;


const float F_T1=1.000*fwt;
const float F_T2=0.750*fwt;
const float F_T3=0.667*fwt;
const float F_T4=0.500*fwt;
const float F_T5=0.333*fwt;
const float F_T6=0.250*fwt;
const float F_T7=0.200*fwt;
const float F_T8=0.100*fwt;
const float F_F1=-0.40;
const float F_F2=-0.20;
const float F_D1=-2.00;
const float F_D2=-1.00;
const float F_D3=-0.50;
const float F_O1=-10.0;
const float F_O2=-8.00;
const float F_O3=-6.00;
const float F_O4=-4.00;

const float sig2=0.01;


float mebership_function(float input, float center, float sigm2)
{
    return exp(-(power(input-center)/(2*sigm2)));
}

float fis( float prr,float pry,float prg,float prb)
{
    float mu_rz,mu_rs,mu_rm,mu_rb,mu_rh;
    float mu_yz,mu_ys,mu_ym,mu_yb,mu_yh;
    float mu_gz,mu_gs,mu_gm,mu_gb,mu_gh;
    float mu_bz,mu_bs,mu_bm,mu_bb,mu_bh;
    float f_sum,f_mu;
    float mu[34],y_hat[34];
    int ic;

    mu_rz=mebership_function(prr,F_Z,sig2);
    mu_rs=mebership_function(prr,F_S,sig2);
    mu_rm=mebership_function(prr,F_M,sig2);
    mu_rb=mebership_function(prr,F_B,sig2);
    mu_rh=mebership_function(prr,F_H,sig2);

    mu_yz=mebership_function(pry,F_Z,sig2);
    mu_ys=mebership_function(pry,F_S,sig2);
    mu_ym=mebership_function(pry,F_M,sig2);
    mu_yb=mebership_function(pry,F_B,sig2);
    mu_yh=mebership_function(pry,F_H,sig2);

    mu_gz=mebership_function(prg,F_Z,sig2);
    mu_gs=mebership_function(prg,F_S,sig2);
    mu_gm=mebership_function(prg,F_M,sig2);
    mu_gb=mebership_function(prg,F_B,sig2);
    mu_gh=mebership_function(prg,F_H,sig2);

    mu_bz=mebership_function(prb,F_Z,sig2);
    mu_bs=mebership_function(prb,F_S,sig2);
    mu_bm=mebership_function(prb,F_M,sig2);
    mu_bb=mebership_function(prb,F_B,sig2);
    mu_bh=mebership_function(prb,F_H,sig2);



    mu[0] =mu_rz*mu_yz*mu_gz*mu_bh; y_hat[0] =F_T1;
    mu[1] =mu_rz*mu_yz*mu_gh*mu_bz; y_hat[1] =F_F2;
    mu[2] =mu_rz*mu_yh*mu_gz*mu_bz; y_hat[2] =F_D1;
    mu[3] =mu_rh*mu_yz*mu_gz*mu_bz; y_hat[3] =F_O1;

    mu[4] =mu_rb*mu_yz*mu_gz*mu_bs; y_hat[4] =F_T8; //?
    mu[5] =mu_rb*mu_yz*mu_gs*mu_bz; y_hat[5] =F_O2;
    mu[6] =mu_rb*mu_ys*mu_gz*mu_bz; y_hat[6] =F_O1;

    mu[7] =mu_rm*mu_yz*mu_gz*mu_bm; y_hat[7] =F_T8; //?
    mu[8] =mu_rm*mu_yz*mu_gm*mu_bz; y_hat[8] =F_O2;
    mu[9] =mu_rm*mu_ym*mu_gz*mu_bz; y_hat[9] =F_O1;
    mu[10]=mu_rm*mu_yz*mu_gs*mu_bs; y_hat[10]=F_T8; //?
    mu[11]=mu_rm*mu_ys*mu_gz*mu_bs; y_hat[11]=F_T8; //?
    mu[12]=mu_rm*mu_ys*mu_gs*mu_bz; y_hat[12]=F_O3;

    mu[13]=mu_rs*mu_yb*mu_gz*mu_bz; y_hat[13]=F_O4;
    mu[14]=mu_rs*mu_ym*mu_gs*mu_bz; y_hat[14]=F_O4;
    mu[15]=mu_rs*mu_ym*mu_gz*mu_bs; y_hat[15]=F_T8; //?
    mu[16]=mu_rs*mu_ys*mu_gm*mu_bz; y_hat[16]=F_O4;
    mu[17]=mu_rs*mu_ys*mu_gz*mu_bm; y_hat[17]=F_T7;
    mu[18]=mu_rs*mu_yz*mu_gb*mu_bz; y_hat[18]=F_D1;
    mu[19]=mu_rs*mu_yz*mu_gm*mu_bs; y_hat[19]=F_T8; //?
    mu[20]=mu_rs*mu_yz*mu_gs*mu_bm; y_hat[20]=F_T7;
    mu[21]=mu_rs*mu_yz*mu_gz*mu_bb; y_hat[21]=F_T6;


    mu[22]=mu_rz*mu_yb*mu_gs*mu_bz; y_hat[22]=F_D1;
    mu[23]=mu_rz*mu_yb*mu_gz*mu_bs; y_hat[23]=F_T5;
    mu[24]=mu_rz*mu_ym*mu_gm*mu_bz; y_hat[24]=F_D2;
    mu[25]=mu_rz*mu_ym*mu_gz*mu_bm; y_hat[25]=F_T2;
    mu[26]=mu_rz*mu_ym*mu_gs*mu_bs; y_hat[26]=F_T4;
    mu[27]=mu_rz*mu_ys*mu_gb*mu_bz; y_hat[27]=F_D3;
    mu[28]=mu_rz*mu_ys*mu_gz*mu_bb; y_hat[28]=F_T1;
    mu[29]=mu_rz*mu_ys*mu_gm*mu_bs; y_hat[29]=F_T3;
    mu[30]=mu_rz*mu_ys*mu_gs*mu_bm; y_hat[30]=F_T2;
    mu[31]=mu_rz*mu_yz*mu_gb*mu_bs; y_hat[31]=F_T2;
    mu[32]=mu_rz*mu_yz*mu_gm*mu_bm; y_hat[32]=F_T1;
    mu[33]=mu_rz*mu_yz*mu_gs*mu_bb; y_hat[33]=F_T1;


    f_sum=0;
    f_mu=0;

    for(ic=0;ic<34;ic++)
    {
        f_sum=f_sum+y_hat[ic]*mu[ic];
        f_mu=f_mu+mu[ic];
    }

    return (f_sum/f_mu);
}




#endif // FUZZY_H
