#include <My_uint16_t/My_uint16_tInterface.h>
#include <My_uint16_t/My_uint16_t_0.h>
#include <My_uint16_t/My_uint16_t_1.h>
#include <God/God.h>
#include <GodGetter/GodGetter_char/GodGetter_char_0.h>

#include <cstdio>

int main()
{
	God* god = new God;
	GodGetter_charInterface* god_getter_char = new GodGetter_char_0;
	
	printf( "%c\n", *reinterpret_cast< char* >( god_getter_char->stuff( god ) ) );
	
	return 0;
}
