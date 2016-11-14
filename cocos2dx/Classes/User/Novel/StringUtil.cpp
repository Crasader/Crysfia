#include "StringUtil.h"

namespace User
{
    double StringUtil::string_double( std::string const & str )
    {
        char* endptr;
        char const* s = str.c_str( );
        auto errorBuf = errno;
        errno = 0;
        auto ret = strtod( s, &endptr );
        auto error = errno;
        errno = errorBuf;
        if ( 0 != error || ( 0.0 == ret && s == endptr ) )
        {
            throw( "�����Ȑ��l�ł��B" );
        }
        return ret;
    }

    int StringUtil::string_int( std::string const & str )
    {
        char* endptr;
        char const* s = str.c_str( ); 
        auto errorBuf = errno;
        errno = 0;
        auto ret = strtol( s, &endptr, 10 );
        auto error = errno;
        errno = errorBuf;
        if ( 0 != error || ( 0 == ret && s == endptr ) )
        {
            throw( "�����Ȑ��l�ł��B" );
        }
        return ret;
    }
}
