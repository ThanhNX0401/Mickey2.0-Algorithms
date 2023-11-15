#include<stdio.h>

int XOR(int a,int b)
{
    if(a==b)
        return 0;
    else
        return 1;
}

int AND(int a, int b)                                                  
{
    if(a==1 && b==1)
        return 1;
    else
        return 0;
}

void CLOCK_R(int r[], int Ir, int Cr)
{ 
    int rtaps[50] ={0,1,3,4,5,6,9,12,13,16,19,20,21,22,25,28,37,38,41,42,45,46,50,52,54,56,58,60,61,63,64,65,66,67,71,72,79,80,81,82,87,88,89,90,91,92,94,95,96,97}; //50
    int clock_r[100];
    int feedback_bit;
    int k=0;
    int i=0;                                                                            
    feedback_bit = XOR(r[99],Ir);
    for(i=0; i<100 ;i++)
    { 
        if(i==0) 
            clock_r[i]=0;
        else{
            clock_r[i]= r[i-1];
        }
    }
    for(i=0; i<100; i++)
    {
        for (k=0; k<50; k++)
        {
            if(i==rtaps[k])
            {
                clock_r[i]=XOR(clock_r[i],feedback_bit);
                break;
            }
        }
    }
    if(Cr==1)
    for(i=0; i<100; i++)
    {
        clock_r[i]=XOR(clock_r[i],r[i]);
    }
    for(i=0; i<100; i++)
    {
        r[i]=clock_r[i];
    }
}

void CLOCK_S(int s[],int Is,int Cs)
{
    int comp0[]={'\0',0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,1,1,'\0'};
    int comp1[]={'\0',1,0,1,1,0,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,'\0'};
    int fb0[]={1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,0};
    int fb1[]={1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1};
    int s_i[100],clock_s[100];
    int i;
    int feedback_bit=XOR(s[99],Is);
    s_i[0]=0;
    s_i[99]=s[98];
    for (i=1;i<99;i++)
    {
        s_i[i]=XOR(s[i-1],AND(XOR(s[i],comp0[i]),XOR(s[i+1],comp1[i])));
    }
    if(Cs==0)
    {
        for (i=0;i<100;i++)
        {
            clock_s[i]=XOR(s_i[i],AND(fb0[i],feedback_bit));
        }
    }
    else{
        for (i=0;i<100;i++)
        {
            clock_s[i]=XOR(s_i[i],AND(fb1[i],feedback_bit));
        }
    }
    for(i=0; i<100; i++)
    {
        s[i]=clock_s[i];
    }
}

void CLOCK_KG(int r[], int s[],int M, int I)
{ 
    int Cr=XOR(s[34], r[67]);
    int Cs=XOR(s[67], r[33]);
    int Ir;
    int Is;

    if (M==1)
        Ir=XOR(I,s[50]);
    else
        Ir=I;

    Is=I;
    CLOCK_R(r,Ir,Cr);
    CLOCK_S(s,Is,Cs);
}

int main()
{
    FILE *file = fopen("dataThanh.txt", "w");
    
    int key[80], r[100],s[100];
    int i, j, l;

    printf("Enter length of keystream: " );
    scanf("%d", &l );
    int z[l];

    printf("Enter 80-bits Key:\n" );
    for (j = 0; j < 80; j++)
        scanf("%d", &key[j]);

    int iv_length;
    printf("Enter the length of IV (0-80):");
    scanf("%d",&iv_length);
    int iv[iv_length];

    printf("Enter %d-bits IV:\n",iv_length);
    for (j=0; j < iv_length; j++)
        scanf("%d", &iv[j] );
                  
    //key loading and init
    for(i = 0; i < 100; i++)
    {
        r[i]=0;
        s[i]=0;
    }

    for (i=0;i<40;i++)                                        
        CLOCK_KG(r,s,1,iv[i]);

    for (i = 0; i < 80; i++)                                         
        CLOCK_KG(r,s,1,key[i]);

    for (i=0;i<100;i++)                                               
        CLOCK_KG(r,s,1,0);
    int number;
    for(i=0;i<l;i++)                                        
    {
        z[i]= XOR(r[0],s[0]);
        number=XOR(r[0],s[0]);
        fprintf(file, "%d", number);
        CLOCK_KG(r,s,0,0);
    }
    fclose(file);

    printf("The generated keystream is:\n");
    for(i = 0; i < l; i++)
        printf("%d",z[i]);

    return 0;
}
