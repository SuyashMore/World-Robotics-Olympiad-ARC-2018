#pragma once

double Vmap(double input,double inLow,double inHigh,double outLow,double outHigh)
{
	if(input <= inLow)
		return outLow;
	if(input >= inHigh )
		return outHigh;

	return (outLow + (input-inLow) * (outHigh-outLow)/(inHigh-inLow));
}