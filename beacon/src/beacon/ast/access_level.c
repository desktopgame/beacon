#include "access_level.h"
#include <stdio.h>

void access_print(access_level level) {
	switch (level) {
		case access_public_T:
			printf("public");
			break;

		case access_private_T:
			printf("private");
			break;

		case access_protected_T:
			printf("protected");
			break;

		default:
			break;
	}
}

bool access_secure(access_level self, access_level other) {
	int oi = (int)other;
	int si = (int)self;
	return oi > si;
}

bool access_weak(access_level self, access_level other) {
	int oi = (int)other;
	int si = (int)self;
	return oi < si;
}