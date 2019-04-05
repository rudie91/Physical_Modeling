#include "L138_LCDK_aic3106_init.h"
#include "math.h"
#include "pluck.h"
#include "limits.h"

int16_t Linput,Rinput;

AIC31_data_type codec_data;
volatile float right_gain = 0.5;
volatile float left_gain = 0.5;

//global variables
float u_y = 0;
float outputSample;
float outputTemp;
float filtered;
float l_y;
String string;
Filter *filter;

interrupt void interrupt4(void) // interrupt service routine
{
//input the actual data
    codec_data.uint = input_sample();

//store input sample to a variable
    Linput = codec_data.channel[LEFT];
    Rinput = codec_data.channel[RIGHT];

// Pluck System processing
    filtered = lossfiltering(filter,u_y*(-1)); // filtering after bridge
    l_y = -delayprocess(&string.lower,filtered); //after delay and nut
    u_y = delayprocess(&string.upper,l_y);
    outputTemp = u_y;
    outputSample = outputTemp + outputSample;
    
// output
    codec_data.channel[LEFT] =  outputSample*SHRT_MAX*left_gain;
    codec_data.channel[RIGHT] =  outputSample*SHRT_MAX*right_gain;

//final output stage
    output_sample(codec_data.uint);
    return;
}

int main(void)
{
	float f0 = 440; //A4
	float fs = 44100.0;
	init_pluckString(f0,fs,&string,&filter);

	// interrupt function triggers runs each time an audio sample is received
	L138_initialise_intr(FS_44100_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
	while(1);
}
