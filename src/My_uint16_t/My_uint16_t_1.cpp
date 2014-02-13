#include "My_uint16_t_1.h"
#include "My_uint16_t_2.h"

My_uint16_tInterface* My_uint16_t_1::next() const
{
	return new My_uint16_t_2;
}

void* My_uint16_t_1::stuff( God* )
{
	return new int(1);
}