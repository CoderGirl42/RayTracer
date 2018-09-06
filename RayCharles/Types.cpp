#include "Types.hpp"

real32 AsReal32(uint32 i)
{
	union
	{
		uint32 i;
		float f;
	} 
	
	pun = { i };
	return pun.f;
}

real64 AsReal64(uint64 i)
{
	union
	{
		uint64 i;
		double f;
	} 
	
	pun = { i };
	return pun.f;
}