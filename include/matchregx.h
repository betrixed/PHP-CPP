#ifndef MatchRegx_H
#define MatchRegx_H


/**
 * Encapsulate direct access to builtin in PHP regular expression functions
 */ 

#include "value.h"

// need to forward declare this pointer to thing.

extern "C" {
typedef struct _pcre_cache_entry pcre_cache_entry;
};

namespace Php {

class PHPCPP_EXPORT MatchRegx : public Value {
	pcre_cache_entry* _pce;
public:
	MatchRegx(const Value& regx);
	virtual ~MatchRegx();

	bool getMatches(ZString& subject, Value& captures);
};

};


#endif