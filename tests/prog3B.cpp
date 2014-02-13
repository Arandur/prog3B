#include <My_uint16_t/My_uint16_tInterface.h>
#include <My_uint16_t/My_uint16_t_0.h>
#include <My_uint16_t/My_uint16_t_1.h>

#include <cstdio>

int main()
{
	My_uint16_tInterface* a = new My_uint16_t_0;
	
	while( *(int*)(a->stuff()) < 20 )
	{
		printf( "%d\n", *(int*)(a->stuff()) );
		a = a->next();
	}
	
	return 0;
}
