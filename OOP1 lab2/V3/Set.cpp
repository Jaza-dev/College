#include "Set.h"

Set::Set(string& s) {
	set = s;
}

Set::Set(string&& s) {
	set = s;
}

bool Set::operator()(char c) const {
	for (unsigned i = 0; i < set.length(); i++) {
		if (tolower(set[i]) == tolower(c)) return true;
	}
	return false;
}

Set& Set::operator+=(char c) {
	if (!(*this)(c)) {
		set += c;
	}
	return *this;
}


