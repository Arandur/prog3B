#include "God.h"

#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdint>

God::God()
{
	things = calloc( 1, 4096 );
	
	0[ reinterpret_cast< char* >( things ) ] = 'a';
	
	/*	0 - 255: str
		256 - 512: filename
		513 - 516: fd
		517 - 520: i
		521 - 608: statbuf (filesize is at position ___)
		608 - 611 + 2 * sizeof( void* ): list
		612 + 2 * sizeof( void* ) - 615 + 4 * sizeof( void* ): curr
		616 + 4 * sizeof( void* ) - 619 + 6 * sizeof( void* ): temp
		620 + 6 * sizeof( void* ): map
		620 + 7 * sizeof( void* ) + 0 * sizeof( void (*)() ): printf
		620 + 7 * sizeof( void* ) + 1 * sizeof( void (*)() ): scanf
		620 + 7 * sizeof( void* ) + 2 * sizeof( void (*)() ): open
		620 + 7 * sizeof( void* ) + 3 * sizeof( void (*)() ): close
		620 + 7 * sizeof( void* ) + 4 * sizeof( void (*)() ): stat
		620 + 7 * sizeof( void* ) + 5 * sizeof( void (*)() ): exit
		620 + 7 * sizeof( void* ) + 6 * sizeof( void (*)() ): mmap
		620 + 7 * sizeof( void* ) + 7 * sizeof( void (*)() ): munmap
		620 + 7 * sizeof( void* ) + 8 * sizeof( void (*)() ): perror
		620 + 7 * sizeof( void* ) + 9 * sizeof( void (*)() ): lseek
		620 + 7 * sizeof( void* ) + 10 * sizeof( void (*)() ): write
		620 + 7 * sizeof( void* ) + 11 * sizeof( void (*)() ): putchar
	*/
	 0[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( printf );
	 1[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( scanf );
	 2[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( open );
	 3[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( close );
	 4[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( stat );
	 5[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( exit );
	 6[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( mmap );
	 7[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( munmap );
	 8[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( perror );
	 9[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( lseek );
	10[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( write );
	11[ reinterpret_cast< void (**)() >( reinterpret_cast< uint8_t* >( things ) + 620 + 7 * sizeof( void* ) ) ] = reinterpret_cast< void (*)() >( putchar );
	 
}

God::~God()
{
	free( things );
}

void* God::stuff( God* )
{
	return things;
}
