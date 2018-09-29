#include "access_level.h"
#include <stdio.h>

void PrintAccess(access_level level) {
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

bool IsSecureAccess(access_level self, access_level other) {
	int oi = (int)other;
	int si = (int)self;
	return oi > si;
}

bool IsWeakAccess(access_level self, access_level other) {
	int oi = (int)other;
	int si = (int)self;
	return oi < si;
}