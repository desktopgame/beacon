#include "exception.h"
#include "object.h"
#include "namespace.h"
#include "type_impl.h"
#include <assert.h>
#include "../util/text.h"

//proto
static class_* exception_class();

object * exception_new_simple(struct vm* vmc, const char* message) {
	class_* excClass = exception_class();
	object* e = class_new_rinstance(excClass, vmc, 1, object_string_new(message));
	return e;
}

object * exception_new_simplef(vm * vmc, const char * message, ...) {
	va_list ap;
	va_start(ap, message);
#define LEN 256
	char block[LEN];
	int res = text_vsprintf(block, LEN, message, ap);
	assert(res != -1);
#undef LEN
	va_end(ap);
	return exception_new_simple(vmc, block);
}

//private
static class_* exception_class() {
	namespace_* lang = namespace_lang();
	class_* excClass = namespace_get_class(lang, "Exception");
	assert(excClass != NULL);
	return excClass;
}