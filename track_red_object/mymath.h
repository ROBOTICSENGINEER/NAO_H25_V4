#ifndef MYMATH_H
#define MYMATH_H
int power(int in)
{
    return (in*in);
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
#endif // MYMATH_H
