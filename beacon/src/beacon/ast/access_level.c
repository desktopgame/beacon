#include "access_level.h"
#include <stdio.h>

void bc_PrintAccess(bc_AccessLevel level) {
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

bool bc_IsSecureAccess(bc_AccessLevel self, bc_AccessLevel other) {
	int oi = (int)other;
	int si = (int)self;
	return oi > si;
}

bool bc_IsWeakAccess(bc_AccessLevel self, bc_AccessLevel other) {
	int oi = (int)other;
	int si = (int)self;
	return oi < si;
}