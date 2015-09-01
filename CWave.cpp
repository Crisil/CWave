/*
 * CWave.cpp
 *
 *  Created on: 15-Jan-2015
 *      Author: crisil
 */

#include "CWave.h"

CWave::CWave() {
	riff_ = new RIFF;
	fmt_  = new FMT;
	dataId_ = new DATAID;
	isheader_ = false;
	numberOfSamples_ = 0;
	filename_ = NULL;
}

CWave::~CWave() {
	delete riff_;
	delete fmt_;
	delete dataId_;
	fclose(filename_);
}

bool CWave::readHeader_()
{
	if(!isOpen_())
	{
		fprintf(stderr, "Failed to open file");
		return false;
	}
	fread(riff_,sizeof(RIFF),1,filename_);

	const char *Idr = "RIFF";
	if(memcmp(riff_->chunk_id,Idr,4))
	{
		fprintf(stderr, "File is not RIFF Format");
		return false;
	}

	const char *Idf = "WAVE";
	if(memcmp(riff_->format,Idf,4))
	{
		fprintf(stderr, "File is not wav format");
		return false;
	}
	fread(fmt_,sizeof(FMT),1,filename_);
	if(fmt_->audio_format != 1)
	{
		fprintf(stderr, "File is not PCM Compression");
		return false;
	}
	fread(dataId_,sizeof(DATAID),1,filename_);
	int sub_chunk2_size = dataId_->subchunk2_size;
	int temp_const = (fmt_->bits_per_sample)*(fmt_->num_of_channels);
	numberOfSamples_ = sub_chunk2_size*8/temp_const;
	return true;
}

short int CWave::getBitsPerSample()
{
	if(!isheader_)
	{
		return -1;
	}
	return fmt_->bits_per_sample;
}

short int CWave::getNumChannels(void)
{
	if(!isheader_)
	{
		return -1;
	}
	return fmt_->num_of_channels;
}

int CWave::getSampleRate(void)
{
	if(!isheader_)
	{
		return -1;
	}
	return fmt_->sample_rate;
}

int CWave::getNumOfSamples(void)
{
	if(!isheader_)
	{
		return -1;
	}
	return numberOfSamples_;
}

float* CWave::waveRead(const char *fp)
{
	filename_ = fopen(fp,"rb");
	isheader_ = readHeader_();
	DWORD dataSize = dataId_->subchunk2_size;
	BYTE *w_data = new BYTE[dataSize];
	float *wavedata = new float[numberOfSamples_];
	if(!isheader_)
	{
		return 0;
	}
	unsigned int nbits = fmt_->bits_per_sample;
	if(nbits == 8)
	{
		unsigned int normalize = 128;
		fread(w_data,sizeof(float),numberOfSamples_,filename_);
		for(unsigned int i = 0; i < numberOfSamples_; i++)
		{
			wavedata[i]	=	(float(w_data[i]) - normalize)/normalize;
		}
	}
	else if (nbits == 16)
	{
	    float normalize = 32678;
	    char tempData;
	    fread(w_data,sizeof(int),numberOfSamples_,filename_);
	    unsigned int k = 0;
	    for(unsigned int i = 0; i < dataSize; i += 2)
	    {
		tempData = (w_data[i + 1] << 8) | w_data[i];
		wavedata[k] = tempData/normalize;
		k++;
	    }
	}
	else
	{
		fprintf(stderr, "Unidentified bits per sample ");
	}

	delete [] w_data;
	return wavedata;
}


