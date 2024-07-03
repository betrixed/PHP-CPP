#include <php.h>

#include "includes.h"

#include <string>
#include <string_view>

namespace Php {


void ZString::init_str(const char *string, size_t size)
{
	_string = zend_string_init(string, size, 0);
}

ZString::ZString(const Value& v)
{
	zval* z = v._val;
	// this adds a reference to the string, destructor will remove.
    _string = zval_get_string(z); 
}


ZString::ZString(const std::string &string)
{
	init_str(string.data(), string.size());
}


    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     */
ZString::ZString(const char *string)
{
	init_str(string, std::strlen(string));
} 

    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     *  @param  size    Number of bytes in the string
     */
ZString::ZString(const char *string, size_t size)
{
	init_str(string, size);
}

    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     */





 // Only defined while ZString exists
std::string_view 
ZString::vstr()  const
{
    return std::string_view(ZSTR_VAL(_string),ZSTR_LEN(_string));
} 


}; // namespace