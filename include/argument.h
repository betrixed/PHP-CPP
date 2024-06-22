/**
 *  @file argument.h
 *
 *  Class holds information about an argument that is passed to a function.
 *  You'll need this class when you're defining your own functions.
 *
 *  The constructor of the argument is protected. Use the ByVal or ByRef
 *  classes instead.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2013 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace Php {

/**
 *  Class definition
 */
class PHPCPP_EXPORT Argument
{
public:
    /**
     *  Destructor
     */
    virtual ~Argument()
    {
        // we should not do this, 
        // as memory buffer must be preserved for the duration of the program
        // if (_nullable) delete[] _classname;
    }

protected:
    /**
     *  Constructor
     *  @param  name        Name of the argument
     *  @param  type        Argument type
     *  @param  required    Is this argument required?
     *  @param  byref       Is this a reference argument
     */
    Argument(const char *name, Type type, bool required = true, bool byref = false) :
        _name(name), _type(type), _required(required), _byReference(byref) {
            if (!_required) {
                _nullable = true; // if not required , then it can be null?
            }
        }

    /**
     *  Constructor
     *  @param  name        Name of the argument
     *  @param  classname   Name of the class
     *  @param  nullable    Can it be null?
     *  @param  required    Is this argument required?
     *  @param  byref       Is this a reference argument?
     */
    Argument(const char *name, const char *classname, bool nullable = true, bool required = true, bool byref = false) :
        _name(name), _type(Type::Object), _classname(classname), _nullable(nullable), _required(required), _byReference(byref) 
    {
        // For some reason NO IDEA WHY, memory allocators? gcc? always making buffered copy of classname
        // seems to prevent a segfault when nullable is false
        // this may be when argument values passed
        // declared as const char*, or static const char*
        /* OFFENDING CODE
        if (!_nullable) 
            return;

        auto slen = ::strlen(_classname);
        auto cbuf = new char[slen + 2]; // room for ? and NULL
        char* dest = cbuf;
        strcpy(dest, "?");
        dest++;
        strcpy(dest, _classname);
        _classname = cbuf;
        */

        // THIS WORKS OK. Always making a classname copy seems to avert segfault on PHP load.
        // Had to recompile all classes using this as well.
        auto slen = ::strlen(classname);
        if (_nullable) {
            slen++; // for ?
        }
        // make a buffer
        auto cbuf = new char[slen + 1]; // NULL
        char* dest = cbuf; // moving pointer

        if (_nullable) {
            strcpy(dest, "?");
            dest++;
        }
        strcpy(dest, classname);
        _classname = cbuf;

    }

public:
    /**
     *  Is this a required argument?
     *  @return bool
     *  @internalsudo
     */
    bool required() const
    {
        return _required;
    }

    /**
     *  Name of the argument
     *  @return const char *
     */
    const char *name() const
    {
        return _name;
    }

    /**
     *  Type-hint for the argument
     *  @return Type
     */
    Type type() const
    {
        return _type;
    }

    /**
     *  If the type is a class, the name of the class
     *  @return const char *
     */
    const char *classname() const
    {
        return _nullable ? _classname + 1 : _classname;
    }
    
    /**
     *  The internal classname, with the encoding whether it is nullable
     *  @return const char *
     */
    const char *encoded() const
    {
        return _classname;
    }

    /**
     *  Is it allowed to pass parameter with a null value?
     *  @return bool
     */
    bool allowNull() const
    {
        return _nullable;
    }

    /**
     *  Is this a parameter-by-reference?
     *  @return bool
     */
    bool byReference() const
    {
        return _byReference;
    }

private:
    /**
     *  Name of the argument
     *  @var const char *
     */
    const char *_name = nullptr;

    /**
     *  Type of argument
     *  @var Type
     */
    Type _type = Type::Null;

    /**
     *  Classname, if this is a parameter that is supposed to be an instance of a class
     *  @var std::string
     */
    const char *_classname = nullptr;

    /**
     *  May the parameter be null?
     *  @var bool
     */
    bool _nullable = false;

    /**
     *  Is this a required argument
     *  @var    bool
     */
    bool _required = true;

    /**
     *  Is this a 'by-reference' parameter?
     *  @var    bool
     */
    bool _byReference = false;
};

/**
 *  Old Visual C++ environments do not support initializer lists
 */
#if defined(_MSC_VER) && _MSC_VER < 1800

/**
 *  For old visual c++ compilers, arguments should be passed as vectors
 */
using Arguments = std::vector<Argument>;

/**
 *  Other compilers, and visual C++ 2013 do support initializer lists
 */
#else

/**
 *  A list of arguments can be supplied to methods
 *  @type   Arguments
 */
using Arguments = std::initializer_list<Argument>;

/**
 *  End of visual C++ check
 */
#endif


/**
 *  End of namespace
 */
}
