#include "access_level.h"
#include <stdio.h>

void access_print(access_level level) {
	switch (level) {
		case access_public:
			printf("public");
			break;

		case access_private:
			printf("private");
			break;

		case access_protected:
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