#include<stdio.h>
#include<limits.h>
#include<float.h>
int main(){
    // Using standard Headers
    printf("signed char     :%d to %d\n",SCHAR_MIN,SCHAR_MAX);
    printf("unsigned char   :0 to %u\n",UCHAR_MAX);
    printf("signed short    :%d to %d\n",SHRT_MIN,SHRT_MAX);
    printf("unsigned short  :0 to %u\n",USHRT_MAX);
    printf("signed int      :%d to %d\n",INT_MIN,INT_MAX);
    printf("unsigned int    :0 to %u\n",UINT_MAX);
    
    printf("signed long     :%ld to %ld\n",LONG_MIN,LONG_MAX);
    printf("unsigned long   :0 to %lu\n",ULONG_MAX);
    printf("float           :%e to %e\n",FLT_MIN,FLT_MAX);
    printf("double          :%e to %e\n",DBL_MIN,DBL_MAX);
    printf("long double     :%Le to %Le\n",LDBL_MIN,LDBL_MAX);

    //Direct Computation
    unsigned char uc = ~0;
    signed char sc = uc >>1;
    printf("signed char     :%d to %d\n",-sc-1,sc);
    printf("unsigned char   :0 to %u\n",uc);
    unsigned short us = ~0;
    signed short ss = us >>1;
    printf("signed short     :%d to %d\n",-ss-1,ss);
    printf("unsigned short   :0 to %u\n",us);
    unsigned int ui = ~0;
    signed int si = ui >>1;
    printf("signed int     :%d to %d\n",-si-1,si);
    printf("unsigned int   :0 to %u\n",ui);
    unsigned long ul = ~0;
    signed long sl = ul >>1;
    printf("signed long     :%ld to %ld\n",-sl-1,sl);
    printf("unsigned long   :0 to %lu\n",ul);
    
}