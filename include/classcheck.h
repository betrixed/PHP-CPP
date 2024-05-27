#ifndef ClassCheck_H
#define ClassCheck_H
/**
 * Made as a "friend" in Php::Value header. Allow to hold the pointer to _zend_class_entry, 
 * and check it matches another Php::Value (object)
 */ 
#ifndef ZSTRING_H
#include "zstring.h"
#endif

#ifndef PHP_VALUE_H
#include "value.h"
#endif

#ifndef ZSTRING_H
#include "zstring.h"
#endif


namespace Php {

/**
 * For repeated object class checks based on zend_class_entry identity
 */
class PHPCPP_EXPORT ClassCheck {

	const char* classname;
	void* ce_class;
public:
	ClassCheck(const char* classname) {
		this->classname = classname;
		this->ce_class = nullptr;
	}

	bool isClass(const Value& obj) {
		if (obj.type() != Php::Type::Object) {
			return false;
		}
		if (this->ce_class == nullptr) {
			Php::Value temp = this->classname;

			this->ce_class = (void*) temp.classEntry(true);
		}
		void* obj_ce = (void*) obj.classEntry(false);
		return (this->ce_class ==  obj_ce);
	}
};

// end namespace
}; 

#endif