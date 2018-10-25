#include "exception.h"
#include "object.h"
#include "namespace.h"
#include "TYPE_IMPL.h"
#include <assert.h>
#include "../util/text.h"
#include "../vm/frame.h"
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static class_* exception_class();

object * NewSimpleException(Frame* fr, const char* message) {
	class_* excClass = exception_class();
	Vector* args = NewVector();
	PushVector(args, object_string_new(message));
	object* e = NewInstanceClass(excClass, fr, args, NULL);
	DeleteVector(args, VectorDeleterOfNull);
	return e;
}

object * NewSimplefException(Frame* fr, const char * message, ...) {
	va_list ap;
	va_start(ap, message);
#define LEN 256
	char block[LEN];
	int res = vsprintf(block, message, ap);
	assert(res != -1);
#undef LEN
	va_end(ap);
	return NewSimpleException(fr, block);
}

//private
static class_* exception_class() {
	Namespace* lang = GetLangNamespace();
	class_* excClass = FindClassFromNamespace(lang, InternString("Exception"));
	assert(excClass != NULL);
	return excClass;
}