#ifndef MatchRegx_H
#define MatchRegx_H


/**
 * Encapsulate direct access to builtin in PHP regular expression functions
 */ 

//#include "value.h"

// need to forward declare this pointer to thing.

extern "C" {
typedef struct _pcre_cache_entry pcre_cache_entry;
};

namespace Php {

/** 
 * Value class is used to hold the regular expression.
 * ZString used to pass subject (from a string Value)
 * 
 */
class PHPCPP_EXPORT MatchRegx : public Value {
	pcre_cache_entry* _pce;
	int          global_; // match all?
	int			 flags_;

public:

	enum {
		 OFFSET_CAPTURE = (1<<8), //PREG_OFFSET_CAPTURE
	};
	
	MatchRegx(const Value& regx, int global = 0, int flags=0);
	virtual ~MatchRegx();

	void setFlags(uint setbits) {
		flags_ = flags_ | setbits;
	}

	bool getMatches(ZString& subject, Value& captures);
};

};


#endif