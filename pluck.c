#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pluck.h"
#define LENGTH 2048


/* function declaration */
void init_FractionalDelayLine(FractionalDelayLine* delayline, float delaylinelength,int method)
{
	/* initialization */
	delayline->M = floor(delaylinelength); // length in integer
	delayline->frac = delaylinelength-delayline->M;
	delayline->currentPos = 0;
	delayline->method = method; // type in integer
	delayline->n = (1-delayline->frac)/(1+delayline->frac);
    delayline->one_x = 0;
    delayline->one_y = 0;
}

float delayprocess (FractionalDelayLine* dl, float x)
{
	float xDelayed;
	int delay_amount = dl->M;
    if(dl->method == 0) //firstOrderAllpass
    {
    	if (delay_amount == 0)
    	{
    		dl->buffer[dl->currentPos%delay_amount] = x;
    		dl->currentPos++;
    		return dl->buffer[dl->currentPos%delay_amount];
    	}
    	else
    	{
    		float x_c = dl->buffer[dl->currentPos];
    		dl->buffer[dl->currentPos] = x;
    		dl->currentPos = (dl->currentPos+1)%(dl->M);
    		xDelayed = dl->n*(x_c-dl->one_y)+dl->one_x;
    		dl->one_x = dl->buffer[dl->currentPos%delay_amount];
    		dl->one_y = xDelayed;
    		return xDelayed;
    	}
    }
    else //linerInterpolation
    {
    	if (delay_amount == 0)
    	{
    		dl->buffer[dl->currentPos%delay_amount] = x;
    		dl->currentPos++;
    		return dl->buffer[dl->currentPos%delay_amount];
    	}
    	else
    	{
    		float x_c = dl->buffer[dl->currentPos];
    		dl->buffer[dl->currentPos] = x;
    		dl->currentPos = (dl->currentPos+1)%(dl->M);
    	    xDelayed = (1-dl->frac)*(x_c)+(dl->frac)*(dl->buffer[dl->currentPos]);
    	    dl->one_x = x;
    	    return xDelayed;
    	}
    }
}
void init_lossfilter(Filter* H, float a,float g)
{
	H->a = a;
	H->g = g;
	H->delayed = 0;

}

float lossfiltering (Filter* H, float x)
{
	float output;
	output = H->g*x*(1+H->a)-H->a*H->delayed;
	H->delayed = output;
	return output;
}

void genPluckShape(int n, float pos,String* string)
{
	float *x;
	x = (float*)malloc(sizeof(float)*n);
	int i,j;
	for(i=0;i<n;i++)
	{
		x[i] = ((float)i)/((float)(n-1.0));
	}
	float m1 = 1/pos;
	float m2 = -1/(x[n-1]-pos);
	float b = 1/(x[n-1]-pos);
	for(i=0;i<n;i++)
	{
		if(x[i] > pos)
		{
			string->upper.buffer[i] = m2*x[i] + b;
		}
		else
		{
			string->upper.buffer[i] = m1*x[i];
		}
	}

	for(i = n-1, j = 0; i >= 0; i--,j++ ) //reversing the buffer
	{
		string->lower.buffer[j] = string->upper.buffer[i];

	}

	free(x);

}

void init_pluckString(float f0, float fs,String *string,Filter* filter)
{
	float M = fs/(2*f0);
	init_FractionalDelayLine(&(string->upper),M,1);
	init_FractionalDelayLine(&(string->lower),M,1);
	genPluckShape(round(M),0.8,string);
	float a = -0.5;
	float g = 0.999;
	init_lossfilter(filter,a,g);
}

