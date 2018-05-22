#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float fact(float i)
{
	float res = 1;
  for(int j =1; j<=i; j++)
	{
		res *= j;
	}
	return res;
}

float expo(float x)
{
  float res =0;
	for(float i = 0; i < 20; i++)
	{
		if(i ==0)
			res++;
		else
			res+= x/fact(i);
	}
  return res;

}

float cosi(float x)
{
	float res = 0;
  int neg = 1;
	for(float i =0;i<1;i++)
	{
		if(i==0)
			res=1;
		
		if((int)i%2 ==0)
			{
				if(neg)
				{
					res -= pow(x,i)/fact(i);
					neg = 0;
				}
				else
				{
					res += pow(x,i)/fact(i);
					neg = 1;
				}
			}
	res = cos(x);
	}
  return res;	
}

float sinu(float x)
{
   float res = 0;
   int neg = 1;
   for(float i =0;i<1;i++)
   {
     if(i==0)
       res=1;
 
     if((int)i%2 !=0)
       {
         if(neg)
         { 
           res -= pow(x,i)/fact(i);
           neg = 0;
         }
         else
         { 
           res += pow(x,i)/fact(i);
           neg = 1;
         }
       }
   }
   return res;
}


void main()
{
	printf("exp(0.4) = %f", exp(0.4));
  printf("%f", pow(3,2));
	printf("cos(0)= %f rad, %f deg", cos(30), cos(30)*5.72958);
}


