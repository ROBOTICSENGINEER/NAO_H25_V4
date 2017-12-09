#ifndef REWARDS_H
#define REWARDS_H

#include <iostream>

void set_target_reward(float R[5][5],float ephi)
{
    unsigned int i,j;
    signed int minrr=-1;

    if (-1.5708<=ephi && ephi<0.64350)
    {
        if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else
        {
            i=4;
            j=4;
            std::cout<<"\nError on set_target_reward \t -1.5708<=ephi && ephi<0.64350";
        }
    }
    else if (0.64350<=ephi && ephi<0.89606)
    {
        if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else
        {
            i=4;
            j=3;
            std::cout<<"\nError on set_target_reward \t 0.64350<=ephi && ephi<0.89606";
        }
    }
    else if (0.89606<=ephi && ephi<1.0517)
    {
        if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else
        {
            i=4;
            j=2;
            std::cout<<"\nError on set_target_reward \t 0.89606<=ephi && ephi<1.0517";
        }
    }
    else if (1.0517<=ephi && ephi<1.1526)
    {
        if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else
        {
            i=4;
            j=1;
            std::cout<<"\nError on set_target_reward \t 1.0517<=ephi && ephi<1.1526";
        }
    }
    else if (1.1526<=ephi && ephi<1.2793)
    {
        if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else
        {
            i=4;
            j=0;
            std::cout<<"\nError on set_target_reward \t 1.1526<=ephi && ephi<1.2793";
        }

    }
    else if (1.2793<=ephi && ephi<1.4711)
    {
        if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else
        {
            i=3;
            j=0;
            std::cout<<"\nError on set_target_reward \t 1.2793<=ephi && ephi<1.4711";
        }
    }
    else if (1.4711<=ephi && ephi<1.6705) ///vasat
    {
        if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if((R[1][0]>minrr) && (R[1][0]>=R[3][0]))
        {
            i=1;
            j=0;
        }
        else if((R[3][0]>minrr) && (R[3][0]>=R[1][0]))
        {
            i=3;
            j=0;
        }
        else if((R[0][0]>minrr) && (R[0][0]>=R[4][0]))
        {
            i=0;
            j=0;
        }
        else if((R[4][0]>minrr) && (R[4][0]>=R[0][0]))
        {
            i=4;
            j=0;
        }
        else if((R[0][1]>minrr) && (R[0][1]>=R[4][1]))
        {
            i=0;
            j=1;
        }
        else if((R[4][1]>minrr) && (R[4][1]>=R[0][1]))
        {
            i=4;
            j=1;
        }
        else if((R[0][2]>minrr) && (R[0][2]>=R[4][2]))
        {
            i=0;
            j=2;
        }
        else if((R[4][2]>minrr) && (R[4][2]>=R[0][2]))
        {
            i=4;
            j=2;
        }
        else if((R[0][3]>minrr) && (R[0][3]>=R[4][3]))
        {
            i=0;
            j=3;
        }
        else if((R[4][3]>minrr) && (R[4][3]>=R[0][3]))
        {
            i=4;
            j=3;
        }
        else if((R[0][4]>minrr) && (R[0][4]>=R[4][4]))
        {
            i=0;
            j=4;
        }
        else if((R[4][4]>minrr) && (R[4][4]>=R[0][4]))
        {
            i=4;
            j=4;
        }
        else
        {
            i=2;
            j=0;
            std::cout<<"\nError on set_target_reward \t 1.4711<=ephi && ephi<1.6705";
        }
    }
    else if (1.6705<=ephi && ephi<1.8623)
    {
        if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else if(R[0][2]>minrr)
        {
            i=0;
            j=2;
        }
        else if(R[0][3]>minrr)
        {
            i=0;
            j=3;
        }
        else if(R[0][4]>minrr)
        {
            i=0;
            j=4;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else
        {
            i=1;
            j=0;
            std::cout<<"\nError on set_target_reward \t 1.6705<=ephi && ephi<1.8623";
        }
    }
    else if (1.8623<=ephi && ephi<1.9890)
    {
        if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[0][2]>minrr)
        {
            i=0;
            j=2;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else
        {
            i=0;
            j=0;
            std::cout<<"\nError on set_target_reward \t 1.8623<=ephi && ephi<1.9890";
        }
    }
    else if (1.9890<=ephi && ephi<2.0899)
    {
        if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[0][2]>minrr)
        {
            i=0;
            j=2;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[0][3]>minrr)
        {
            i=0;
            j=3;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[0][4]>minrr)
        {
            i=0;
            j=4;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else
        {
            i=0;
            j=1;
            std::cout<<"\nError on set_target_reward \t 1.9890<=ephi && ephi<2.0899";
        }
    }
    else if (2.0899<=ephi && ephi<2.2455)
    {
        if(R[0][2]>minrr)
        {
            i=0;
            j=2;
        }
        else if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else if(R[0][3]>minrr)
        {
            i=0;
            j=3;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[0][4]>minrr)
        {
            i=0;
            j=4;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else
        {
            i=0;
            j=2;
            std::cout<<"\nError on set_target_reward \t 2.0899<=ephi && ephi<2.2455";
        }
    }
    else if (2.2455<=ephi && ephi<2.4981)
    {
        if(R[0][3]>minrr)
        {
            i=0;
            j=3;
        }
        else if(R[0][2]>minrr)
        {
            i=0;
            j=2;
        }
        else if(R[0][4]>minrr)
        {
            i=0;
            j=4;
        }
        else if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else
        {
            i=0;
            j=3;
            std::cout<<"\nError on set_target_reward \t 2.2455<=ephi && ephi<2.4981";
        }
    }
    else if (ephi>=2.4981)
    {
        if(R[0][4]>minrr)
        {
            i=0;
            j=4;
        }
        else if(R[0][3]>minrr)
        {
            i=0;
            j=3;
        }
        else if(R[0][2]>minrr)
        {
            i=0;
            j=2;
        }
        else if(R[0][1]>minrr)
        {
            i=0;
            j=1;
        }
        else if(R[0][0]>minrr)
        {
            i=0;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else
        {
            i=0;
            j=4;
            std::cout<<"\nError on set_target_reward \t ephi>=2.4981";
        }
    }
    else if (ephi<-1.5708)
    {
        if(R[4][4]>minrr)
        {
            i=4;
            j=4;
        }
        else if(R[4][3]>minrr)
        {
            i=4;
            j=3;
        }
        else if(R[4][2]>minrr)
        {
            i=4;
            j=2;
        }
        else if(R[4][1]>minrr)
        {
            i=4;
            j=1;
        }
        else if(R[4][0]>minrr)
        {
            i=4;
            j=0;
        }
        else if(R[3][0]>minrr)
        {
            i=3;
            j=0;
        }
        else if(R[2][0]>minrr)
        {
            i=2;
            j=0;
        }
        else if(R[1][0]>minrr)
        {
            i=1;
            j=0;
        }
        else
        {
            i=4;
            j=4;
            std::cout<<"\nError on set_target_reward \t ephi<-1.5708";
        }
    }

    //std::cout << "i,j = \t" << i << "," << j <<"\n";
    R[i][j]=R[i][j]+1;


}




#endif // REWARDS_H
