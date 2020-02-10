/**
 *  Modifiers.cpp
 *
 *  In this file an enumeration type is with the possible
 *  member modifiers
 *
 *  @author Martijn Otto <martijn.otto@copernica.com>
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 * 
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"
#include <zend_compile.h>
/**
 *  Set up namespace
 */
namespace Php {

/**
 *  The modifiers are constants
 */
const int Static    =   ZEND_ACC_STATIC;
const int Abstract  =   ZEND_ACC_ABSTRACT;
const int Final     =   ZEND_ACC_FINAL;
const int Public    =   ZEND_ACC_PUBLIC;
const int Protected =   ZEND_ACC_PROTECTED;
const int Private   =   ZEND_ACC_PRIVATE;
const int Const     =   0;

/**
 *  Modifiers that are supported for methods and properties
 */
const int MethodModifiers           =   Final | Public | Protected | Private | Static;
const int PropertyModifiers         =   Final | Public | Protected | Private | Const | Static;

/**
 *  End namespace
 */
}
