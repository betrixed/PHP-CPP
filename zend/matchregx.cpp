
#include "includes.h"

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
#include "ext/pcre/php_pcre.h"
};


using namespace Php;

MatchRegx::MatchRegx(const Value& regx) : Value(regx), _pce(nullptr) {

}

MatchRegx::~MatchRegx() {
	if (_pce != nullptr) {
		php_pcre_pce_decref(_pce);
	}
}

bool MatchRegx::getMatches(ZString& subject, Value& captures) {
	if (_pce == nullptr) 
	{
		zval* z = _val;
		zend_string* zs = zval_get_string(z);
		_pce = pcre_get_compiled_regex_cache(zs);
		php_pcre_pce_incref(_pce);
		zend_string_release(zs);
	}
	zval matches;
	zval mreturn;

	ZVAL_NULL(&matches);
	ZVAL_NULL(&mreturn);

	php_pcre_match_impl(_pce, subject, &mreturn, &matches, 
		/*global*/ 0, /*use flags*/ 1, /*flags*/0,  /*offset*/ 0);

	if ( Z_LVAL(mreturn) != 0)
	{
		captures = Value(&matches);
		return true;
	}

	return false;
}