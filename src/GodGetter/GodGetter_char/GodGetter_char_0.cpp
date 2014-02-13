#include "GodGetter_char_0.h"
//#include "GodGetter_char_1.h"

GodGetter_charInterface* GodGetter_char_0::next() const
{
	return 0;//new GodGetter_char_1;
}

void* GodGetter_char_0::stuff( God* god )
{
	return reinterpret_cast< void* >( reinterpret_cast< char* >( god->stuff() ) + 0 );
}
