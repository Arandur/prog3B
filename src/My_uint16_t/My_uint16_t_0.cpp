#include "My_uint16_t_0.h"
#include "My_uint16_t_1.h"

My_uint16_tInterface* My_uint16_t_0::next() const
{
	return new My_uint16_t_1;
}

void* My_uint16_t_0::stuff( God* )
{
	return new int(0);
}