#include "access_level.h"
#include <stdio.h>

void PrintAccess(AccessLevel level) {
	switch (level) {
		case ACCESS_PUBLIC_T:
			printf("public");
			break;

		case ACCESS_PRIVATE_T:
			printf("private");
			break;

		case ACCESS_PROTECTED_T:
			printf("protected");
			break;

		default:
			break;
	}
}

bool IsSecureAccess(AccessLevel self, AccessLevel other) {
	int oi = (int)other;
	int si = (int)self;
	return oi > si;
}

bool IsWeakAccess(AccessLevel self, AccessLevel other) {
	int oi = (int)other;
	int si = (int)self;
	return oi < si;
}