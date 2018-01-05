#include "access_domain.h"

//proto
static bool domain_match(access_domain src, access_domain target);

bool domain_is_public(access_domain a) {
	return domain_match(a, domain_public);
}

bool domain_is_private(access_domain a) {
	return domain_match(a, domain_private);
}

bool domain_is_protected(access_domain a) {
	return domain_match(a, domain_protected);
}

bool domain_is_static(access_domain a) {
	return domain_match(a, domain_static);
}

bool domain_is_native(access_domain a) {
	return domain_match(a, domain_native);
}

bool domain_accept(access_domain self, modifier_type m, access_level a) {
	if (self == domain_none) {
		return true;
	}
	//staticであることを要求している
	if (domain_is_static(self)) {
		if (domain_is_static(self) != modifier_is_static(m)) {
			return false;
		}
	//していない
	} else {
		//...
	}
	//nativeであることを要求している
	if (domain_is_native(self)) {
		if (domain_is_native(self) != modifier_is_native(m)) {
			return false;
		}
	//していない
	} else {
		//...
	}
	return
		(domain_is_public(self) && a == access_public) ||
		(domain_is_private(self) && a == access_private) ||
		(domain_is_protected(self) && a == access_protected);
}

//private
static bool domain_match(access_domain src, access_domain target) {
	return (src & target);
}