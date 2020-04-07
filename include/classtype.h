/**
 *  @file classtype.h
 *
 *  Internal class types enumeration.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace Php {

/**
 *  Enumeration definition.
 *
 *  The PHP-CPP library tries to hide the Zend engine internals completely from
 *  the user. Therefore, it does not include any of the Zend header files, nor
 *  can it refer to the constants defined in the Zend header files. The
 *  following constants have been copied from Zend. If the Zend engine ever
 *  changes (which we do not expect) we should also copy the constant values
 *  used here.
 *
 */
enum class ClassType {
    Regular     =   0x00,
    Abstract    =   0x40, // 0x20 ZEND_ACC_ABSTRACT (1 << 6) = (0= 0x01, 1=0x02, 2=0x04, 3=0x08 4=0x10, 5=0x20, 6=0x40)
    Final       =   0x20, // 0x04 ZEND_ACC_FINAL  (1 <<  5) 
    Interface   =   0x00, // ZEND_ACC_INTERFACE (1 <<  0)
};

/**
 *  End namespace
 */
}
