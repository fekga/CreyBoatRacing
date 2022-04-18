#pragma once

#include <assert.h>
#include <sstream>

#if defined SF_DEBUG
#	define SFASSERT( TST ) assert( TST );
#else
#	define SFASSERT( void )
#endif

#if defined SF_LOGGING_ENABLED
#define SFLOG( ... ) sflogImpl( __VA_ARGS__ )
template < typename ...Args >
void sflogImpl( Args&& ...args )
{
    std::ostringstream stream;
	( stream << ... << std::forward< Args >( args ) );
    printf( stream.str().c_str() );
}
#else
#	define SFLOG( void )
#endif