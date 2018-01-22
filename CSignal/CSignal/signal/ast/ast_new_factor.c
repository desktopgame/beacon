#include "ast_new_factor.h"
#include "ast.h"

ast * ast_new_true() {
	return ast_new(ast_true);
}

ast * ast_new_false() {
	return ast_new(ast_false);
}

ast * ast_new_cast(ast * atypename, ast * afact) {
	ast* ret = ast_new(ast_cast);
	ast_push(ret, atypename);
	ast_push(ret, afact);
	return ret;
}

ast * ast_new_pre_inc(ast * a) {
	ast* ret = ast_new(ast_pre_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_pre_dec(ast * a) {
	ast* ret = ast_new(ast_pre_dec);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_inc(ast * a) {
	ast* ret = ast_new(ast_post_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_dec(ast * a) {
	ast* ret = ast_new(ast_post_dec);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_variable(const char * name) {
	ast* ret = ast_new(ast_variable);
	ret->u.string_value = name;
	return ret;
}

ast * ast_new_call(const char * name, ast * argument_list) {
	ast* ret = ast_new(ast_call);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, aname);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_invoke(ast * receiver, const char* name, ast * argument_list) {
	ast* ret = ast_new(ast_invoke);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, receiver);
	ast_push(ret, aname);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_static_invoke(ast * fqcn, const char * name, ast * argument_list) {
	ast* ret = ast_new(ast_static_invoke);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, fqcn);
	ast_push(ret, aname);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_this() {
	return ast_new(ast_this);
}

ast * ast_new_super() {
	return ast_new(ast_super);
}

ast * ast_new_field_access(ast * afact, char * name) {
	ast* ret = ast_new(ast_field_access);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, afact);
	ast_push(ret, aname);
	return ret;
}

ast * ast_new_field_access_fqcn(ast * fqcn, char * name) {
	//	assert(fqcn->tag != ast_fqcn_part_list);
	if (fqcn->tag == ast_fqcn_part ||
		fqcn->tag == ast_fqcn_class_name) {
		//この時点では point.a のようなアクセスを
		//インスタンス point のフィールド a へのアクセスなのか
		//クラス Point の静的フィールド a へのアクセスなのか判別出来ない
		//なので、とりあえずフィールドアクセスとして扱う
		//この判別は il_factor_field_access で行う。
		ast* ret = ast_new(ast_field_access);
		ast* avar = ast_new(ast_variable);
		ast* aname = ast_new(ast_identifier);
		avar->u.string_value = fqcn->u.string_value;
		aname->u.string_value = name;
		ast_push(ret, avar);
		ast_push(ret, aname);
		return ret;
	} else if (fqcn->tag == ast_fqcn || fqcn->tag == ast_fqcn_part_list) {
		//こっちの場合は静的フィールドへのアクセスと断定できる
		ast* ret = ast_new(ast_static_field_access);
		ast* aname = ast_new(ast_identifier);
		aname->u.string_value = name;
		ast_push(ret, fqcn);
		ast_push(ret, aname);
		return ret;
	}
	return NULL;
}

ast * ast_new_new_instance(ast * afqcn, ast * argument_list) {
	ast* ret = ast_new(ast_new_instance);
	ast_push(ret, afqcn);
	ast_push(ret, argument_list);
	return ret;
}
