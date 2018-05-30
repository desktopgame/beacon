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

//private
static bool domain_match(access_domain src, access_domain target) {
	return (src & target);
}