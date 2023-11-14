#include<stdio.h>
#include<string.h>
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
void clock_r(int r[], int input_bit_r, int control_bit_r)
{ 
    int rtaps[50] ={0,1,3,4,5,6,9,12,13,16,19,20,21,22,25,28,37,38,41,42,45,46,50,52,54,56,58,60,61,63,64,65,66,67,71,72,79,80,81,82,87,88,89,90,91,92,94,95,96,97}; //50
    int r_clocked[100];
    int feedback_bit;
    int k=0;
    int i=0;                                                                            
    feedback_bit = XOR(r[99],input_bit_r);
    for(i=0; i<100 ;i++)
    { 
        if(i==0) 
            r_clocked[i]=0;
        else{
            r_clocked[i]= r[i-1];
        }
    }
    for(i=0; i<100; i++)
    {
        for (k=0; k<50; k++)
        {
            if(i==rtaps[k])
            {
                r_clocked[i]=XOR(r_clocked[i],feedback_bit);
                break;
            }
        }
    }
    if(control_bit_r==1)
    for(i=0; i<100; i++)
    {
        r_clocked[i]=XOR(r_clocked[i],r[i]);
    }
    for(i=0; i<100; i++)
    {
        r[i]=r_clocked[i];
    }
}

void clock_s(int s[],int input_bit_s,int control_bit_s)
{
    int comp0[]={'\0',0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,1,1,'\0'};
    int comp1[]={'\0',1,0,1,1,0,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,'\0'};
    int fb0[]={1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,0};
    int fb1[]={1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1};
    int s_i[100],s_clocked[100];
    int i;
    int feedback_bit=XOR(s[99],input_bit_s);
    s_i[0]=0;
    s_i[99]=s[98];
    for (i=1;i<99;i++)
    {
        s_i[i]=XOR(s[i-1],AND(XOR(s[i],comp0[i]),XOR(s[i+1],comp1[i])));
    }
    if(control_bit_s==0)
    {
        for (i=0;i<100;i++)
        {
            s_clocked[i]=XOR(s_i[i],AND(fb0[i],feedback_bit));
        }
    }
    else{
        for (i=0;i<100;i++)
        {
            s_clocked[i]=XOR(s_i[i],AND(fb1[i],feedback_bit));
        }
    }
    for(i=0; i<100; i++)
    {
        s[i]=s_clocked[i];
    }
}

void clock_kg(int r[], int s[],int mixing, int input_bit)
{ 
    int control_bit_r=XOR(s[34], r[67]);
    int control_bit_s=XOR(s[67], r[33]);
    int input_bit_r;
    int input_bit_s;

    if (mixing==1)
        input_bit_r=XOR(input_bit,s[50]);
    else
        input_bit_r=input_bit;

    input_bit_s=input_bit;
    clock_r(r,input_bit_r,control_bit_r);
    clock_s(s,input_bit_s,control_bit_s);
}

int main()
{
    FILE *file = fopen("dataThanh.txt", "w");
    
    int key[80], iv[80], i, j, l, r[100],s[100];

    printf("Enter length of keystream: " );
    scanf("%d", &l );
    int z[l];

    printf("Enter The 80-bit key:\n" );
    for (j = 0; j < 80; j++)
        scanf("%d", &key[j]);

    /*for (j = 0; j < 80; j++)
        printf("%d ", key[j]);*/

    printf("Enter the value for iv (40-bit):\n" );
    for (j=0; j < 40; j++)
        scanf("%d", &iv[j] );
                  
    //key loading and init
    for(i = 0; i < 100; i++)
    {
        r[i]=0;
        s[i]=0;
    }

    for (i=0;i<40;i++)                                        
        clock_kg(r,s,1,iv[i]);

    for (i = 0; i < 80; i++)                                         
        clock_kg(r,s,1,key[i]);

    for (i=0;i<100;i++)                                               
        clock_kg(r,s,1,0);
    int number;
    for(i=0;i<l;i++)                                        
    {
        z[i]= XOR(r[0],s[0]);
        number=XOR(r[0],s[0]);
        fprintf(file, "%d", number);
        clock_kg(r,s,0,0);
    }
    fclose(file);

    printf("The generated keystream is:\n");
    for(i = 0; i < l; i++)
        printf("%d",z[i]);

    return 0;
}