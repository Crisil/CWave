/*
 * MainWindow.cpp
 *
 *  Created on: 15-Jan-2015
 *      Author: crisil
 */
#include "CWave.h"

int main()
{
	CWave *wavefile = new CWave();
	FILE *waveData = fopen("/home/crisil/workspace/SignalProcessingLibs/src/waveData.txt","wb");
	if(wavefile)
	{
		float *ptr;
//		ptr = wavefile->waveRead("/home/crisil/workspace/SignalProcessingLibs/src/kdt_016.wav");
		ptr = wavefile->waveRead("/home/crisil/mal/readsp_an/analysis/N1/N1.wav");
		cout<<"Bits/Sample : "<<wavefile->getBitsPerSample();
		cout<<"\nSampling frequency :"<<wavefile->getSampleRate();
		cout<<"\nNumber Of Channels :"<<wavefile->getNumChannels();
		cout<<"\nNumber Of Sample : "<<wavefile->getNumOfSamples();
		unsigned int nLen = wavefile->getNumOfSamples();

		printf("\n ptr %0.5f ",(ptr[199]));

		if(waveData)
		{
			for(unsigned int i = 0; i < nLen; i++)
			{
				fprintf(waveData,"%0.5f \n",ptr[i]);
			}
		}
		else
		{
		fprintf(stderr, "Data file opening failed");
		}
		delete ptr;
	}
	else
	{
		fprintf(stderr, "Memory Allocation failed");
	}


	delete wavefile;
//	fclose(waveData);
	return 0;
}



