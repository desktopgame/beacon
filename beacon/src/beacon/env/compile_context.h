#ifndef BEACON_ENV_CONTEXT_H
#define BEACON_ENV_CONTEXT_H
#include "../util/vector.h"
typedef struct compile_context {
	vector* namespace_vec;
	vector* type_vec;
	vector* method_vec;
	vector* ctor_vec;
	vector* receiver_vec;
	vector* type_args_vec;
	vector* while_start_vec;
	vector* while_end_vec;
	//メソッドの探索とコンストラクタの探索は
	//部分的には似ていますが、
	//コンストラクタはレシーバがいないのにインスタンスメソッドのように
	//クラスに定義された型変数を使用できるという点で特殊です。
	//パラメータが T であり、インスタンスメソッドであるなら
	//それを実行する実体化されたレシーバから型を取り出せますが、
	//(つまり、receiver_vecの先頭を参照する)
	//コンストラクタの場合ではnew演算子から参照する必要があります。
	bool toplevel;
	int find_instance;
	int find_static;
	struct class_loader* class_loader_ref;
} compile_context;
struct namespace_;
struct type;
struct method;
struct constructor;
struct label;
struct generic_type;

void cc_push();

//namespace
void ccpush_namespace(struct namespace_* e);

struct namespace_* cctop_namespace();

struct namespace_* ccpop_namespace();

//type

void ccpush_type(struct type* e);

struct type* cctop_type();

struct type* ccpop_type();

//method

void ccpush_method(struct method* e);

struct method* cctop_method();

struct method* ccpop_method();

//ctor

void ccpush_ctor(struct constructor* e);

struct constructor* cctop_ctor();

struct constructor* ccpop_ctor();

//receiver

void ccpush_receiver(struct generic_type* e);

struct generic_type* cctop_receiver();

struct generic_type* ccpop_receiver();

//typeargs

void ccpush_type_args(vector* type_args);

vector* cctop_type_args();

vector* ccpop_type_args();

//while_start

void ccpush_while_start(struct label* e);

struct label* cctop_while_start();

struct label* ccpop_while_start();

//while_end

void ccpush_while_end(struct label* e);

struct label* cctop_while_end();

struct label* ccpop_while_end();

compile_context* cc_current();

compile_context* cc_top();

void cc_pop();
#endif