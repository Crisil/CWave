/*
 * CWave.h
 *
 *  Created on: 15-Jan-2015
 *      Author: crisil
 */

#ifndef CWAVE_H_
#define CWAVE_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef unsigned short int SHORT;

typedef struct riff_chunk{
	BYTE chunk_id[4];
	DWORD chunk_size;
	BYTE format[4];
}RIFF;

typedef struct fmt_chunk{
	BYTE subchunk1_id[4];
	DWORD subchunk1_size;
	SHORT audio_format;
	SHORT num_of_channels;
	DWORD sample_rate;
	DWORD byte_rate;
	SHORT block_align;
	SHORT bits_per_sample;
}FMT;

typedef struct data_chunk{
	BYTE subchunk2_id[4];
	DWORD subchunk2_size;
}DATAID;

class CWave {
private:
	RIFF *riff_ 			= NULL;
	FMT *fmt_ 			= NULL;
	DATAID *dataId_ 		= NULL;
	bool isOpen_()			{ return filename_ != NULL ;}
	bool readHeader_();
	bool isheader_;
	DWORD numberOfSamples_;
	FILE *filename_;

public:
	CWave();
	virtual ~CWave();
	short int getNumChannels();
	short int getBitsPerSample();
	int getSampleRate();
	int getNumOfSamples();
	float* waveRead(const char *fp);
};

#endif /* CWAVE_H_ */
