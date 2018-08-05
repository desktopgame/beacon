#include "access_level.h"
#include <stdio.h>

void access_print(access_level level) {
	switch (level) {
		case access_public:
			text_printf("public");
			break;

		case access_private:
			text_printf("private");
			break;

		case access_protected:
			text_printf("protected");
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