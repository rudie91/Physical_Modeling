/*
 * hw5.h
 *
 *  Created on: Mar, 2018
 *      Author: yYang
 */

#ifndef PLUCK_H_
#define PLUCK_H_
#define LENGTH 2048

typedef struct _FractionalDelayLine{
	float buffer[LENGTH];
	int currentPos;
	int M;
	float frac;
	float n;
	int method;
	float one_x;
	float one_y;
}FractionalDelayLine;

typedef struct _Filter{
	float a;
	float g;
	float delayed;
}Filter;

typedef struct _String{
	FractionalDelayLine upper, lower;
	Filter lossfilter;
}String;

/* function declaration */
void init_FractionalDelayLine (FractionalDelayLine* delayline, float delaylinelength, int method);

float delayprocess (FractionalDelayLine* dl, float x);

void init_lossfilter(Filter* H, float a,float g);

float lossfiltering (Filter* H, float x);

void genPluckShape(const int n, float pos, String* string);

void init_pluckString(float f0, float fs,String* string,Filter* filter);

#endif /* PLUCK_H_ */
