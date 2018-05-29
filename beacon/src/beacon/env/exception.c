#include "exception.h"
#include "object.h"
#include "namespace.h"
#include "type_impl.h"
#include <assert.h>
#include "../util/text.h"
#include "../vm/frame.h"

//proto
static class_* exception_class();

object * exception_new_simple(frame* fr, const char* message) {
	class_* excClass = exception_class();
	vector* args = vector_new();
	vector_push(args, object_string_new(message));
	object* e = class_new_instance(excClass, NULL, fr, args, NULL);
	vector_delete(args, vector_deleter_null);
	return e;
}

object * exception_new_simplef(frame * fr, const char * message, ...) {
	va_list ap;
	va_start(ap, message);
#define LEN 256
	char block[LEN];
	int res = text_vsprintf(block, LEN, message, ap);
	assert(res != -1);
#undef LEN
	va_end(ap);
	return exception_new_simple(fr, block);
}

//private
static class_* exception_class() {
	namespace_* lang = namespace_lang();
	class_* excClass = namespace_get_class(lang, "Exception");
	assert(excClass != NULL);
	return excClass;
}