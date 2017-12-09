#ifndef MYMATH_H
#define MYMATH_H
int power(int in)
{
    return (in*in);
}

float power(float in)
{
    return (in*in);
}

int power3(int in)
{
    return (power(in)*in);
}


float powern (float in, unsigned int nnnn)
{
  int iinn;
  float outn=1;
  for(iinn=0;iinn<nnnn;iinn++)
  {
    outn=in*outn;    
  }
  return outn;
}

int min(int a, int b)
{
    int c;
    if(a<b) c=a;
    else c=b;
    return c;
}

int max(int a, int b)
{
    int c;
    if(a<b) c=b;
    else c=a;
    return c;
}

float minf(float a, float b)
{
    float c;
    if(a<b) c=a;
    else c=b;
    return c;
}

float maxf(float a, float b)
{
    float c;
    if(a<b) c=b;
    else c=a;
    return c;
}

float mag(float a)
{
    float b;
    if (a>=0)
    {
        b=a;
    }
    else
    {
        b=-a;
    }
    return b;
}

void sat(float &x, float a)
{
    float b=mag(a);
    if (x>b)
    {
        x=b;
    }
    else if (x<-b)
    {
        x=-b;
    }
}

#endif // MYMATH_H
