// Decoder base class for inheritance 
#ifndef DECODE_BASE_H
#define DECODE_BASE_H

#include "chugin.h"

template<const unsigned order_>
class Decoder
{
public:

	virtual void tick(SAMPLE* in, SAMPLE* out, int nframes) = 0;
	virtual ~Decoder() = 0;

	
};

#endif /* DECODE_BASE_H */