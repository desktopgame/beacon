#include "access_level.h"
#include <stdio.h>

bool bc_IsWeakAccess(bc_AccessLevel self, bc_AccessLevel other) {
        int oi = (int)other;
        int si = (int)self;
        return oi < si;
}