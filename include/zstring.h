#ifndef ZSTRING_H
#define ZSTRING_H

/**
 *  make available zend_string wrapper (strng.h) from PHP_CPP
 */


/**
 *  Dependencies
 */
#include <php.h>
#include <cstring>

/**
 *  Start namespace
 */
namespace Php {

/**
 *  Wrapper class for a zend_string
 */
class PHPCPP_EXPORT ZString
{
private:
    /**
     *  The string we are wrapping
     *  @var    zend_string*
     */
    zend_string *_string;
public:
    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     */
    ZString(zend_string *string) : _string(string)
    {
        // add another reference to the string
        zend_string_addref(_string);
    }

    // a null constructer
    ZString() {
        _string = nullptr;
    }
    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     */
    ZString(const std::string &string) : _string(zend_string_init(string.data(), string.size(), 1)) {}

    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     */
    ZString(const char *string) : _string(zend_string_init(string, std::strlen(string), 1)) {}

    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     *  @param  size    Number of bytes in the string
     */
    ZString(const char *string, size_t size) : _string(zend_string_init(string, size, 1)) {}

    /**
     *  Constructor
     *
     *  @param  string  The string to wrap
     */
    template <size_t size>
    ZString(const char (&string)[size]) : _string(zend_string_init(string, size - 1, 1)) {}

    /**
     *  Copy constructor
     *
     *  @param  that    The string to copy
     */
    ZString(const ZString &that) : _string(that._string)
    {
        // increment refcount
        zend_string_addref(_string);
    }

    /**
     *  Move constructor
     *
     *  @param  that    The string to move
     */
    ZString(ZString &&that) : _string(that._string)
    {
        // reset other string
        that._string = nullptr;
    }

    /**
     *  Destructor
     */
    virtual ~ZString()
    {
        // release the reference, freeing the
        // string if we are the last referee
        if (_string) zend_string_release(_string);
    }

    /**
     *  Retrieve the data for the string
     *
     *  @return Pointer to the string data
     */
    char *data()
    {
        return ZSTR_VAL(_string);
    }

    /**
     *  Retrieve the data for the string
     *
     *  @return Pointer to the string data
     */
    const char *data() const
    {
        return ZSTR_VAL(_string);
    }

    /**
     *  Retrieve number of characters in the string
     *
     *  @return Number of characters, not including the terminating null
     */
    size_t size() const
    {
        return ZSTR_LEN(_string);
    }

    bool valid() {
        return _string != nullptr;
    }
    /**
     *  Retrieve the underlying string
     *
     *  @return The zend string
     */
    operator zend_string * ()
    {
        // return the wrapped string
        return _string;
    }

    /**
     *  Retrieve the underlying string
     *
     *  @return The zend string
     */
    zend_string *operator->()
    {
        // return the wrapped string
        return _string;
    }
};

/**
 *  End namespace
 */
};


#endif