#include "meta_impl.h"
#include "../../il/il_argument.h"
#include "../parameter.h"
#include "../type_interface.h"
#include "../namespace.h"
#include "class_impl.h"
#include "../constructor.h"
#include "../object.h"

method * meta_find_method(vector * method_vec, const char * name, vector * args, enviroment * env, int * outIndex) {
	(*outIndex) = -1;
	//class_create_vtable(self);
	method* ret = NULL;
	int min = 1024;
	//	for (int i = 0; i < self->method_list->length; i++) {
	for (int i = 0; i < method_vec->length; i++) {
		//vector_item e = vector_at(self->method_list, i);
		vector_item e = vector_at(method_vec, i);
		method* m = (method*)e;
		//名前か引数の個数が違うので無視
		if (strcmp(m->name, name) ||
			m->parameter_list->length != args->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (args->length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = 0;
		bool illegal = false;
		for (int j = 0; j < m->parameter_list->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(m->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			//実引数が NULL なら常に許容する
			int dist = 0;
			type* argType = il_factor_eval(p->factor, env);
			type* parType = p2->type;
			if (argType != CL_NULL) {
				dist = type_distance(argType, parType);
			}
			score += dist;
			//継承関係のないパラメータ
			if (dist == -1) {
				illegal = true;
				break;
			}
		}
		if (score < min && !illegal) {
			//TEST(env->toplevel);
			min = score;
			ret = m;
			(*outIndex) = i;
		}
	}
	return ret;
}

vector * meta_find_constructors(class_ * self, vector * args, enviroment * env) {
	vector* v = vector_new();
	if (self == NULL) {
		return v;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		constructor* c = (constructor*)e;
		//引数の個数が違うので無視
		if (c->parameter_list->length != args->length) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (args->length == 0) {
			vector_push(v, c);
			continue;
		}
		bool match = true;
		for (int j = 0; j < args->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(c->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			if (!type_castable(il_factor_eval(p->factor, env), p2->type)) {
				match = false;
				break;
			}
		}
		if (match) {
			vector_push(v, c);
		}
	}
	return v;
}

vector * meta_find_rconstructors(class_ * self, vector * args) {
	vector* v = vector_new();
	if (self == NULL) {
		return v;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		constructor* c = (constructor*)e;
		//引数の個数が違うので無視
		if (c->parameter_list->length != args->length) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (args->length == 0) {
			vector_push(v, c);
			continue;
		}
		bool match = true;
		for (int j = 0; j < args->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(c->parameter_list, j);
			object* p = (object*)d;
			parameter* p2 = (parameter*)d2;
			if (!type_castable(p->type, p2->type)) {
				match = false;
				break;
			}
		}
		if (match) {
			vector_push(v, c);
		}
	}
	return v;
}
