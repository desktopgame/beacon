#ifndef BEACON_UTIL_PANIC_H
#define BEACON_UTIL_PANIC_H
#include <setjmp.h>
#define EXCEPTION_EMPTY (0)
#define EXCEPTION_GENERIC (-1)

//http://www.nurs.or.jp/~sug/soft/super/longjmp.htm
/*
void sub(int n) {
	if(n == 0) {
		panic(2);
	} else {
		printf("%d\n", n);
	}
}
int main(int argc, char *argv[]) {
	int ret;
	jmpbuf_trace* se = begin_panic();
	handle_panic( 2 );
	handle_panic( 3 );
	if( (ret = setjmp( se->buf )) == 0 ) {
		for(int i = 10; ; i-- ) {
			sub( i );
		}
		end_panic();
	} else {
		MEM_FREE( se );
		if( ret == 2 ) {
			printf( "IOException occured\n" );
		} else if( ret == 3 ) {
			printf( "MyException occured\n" );
		}
	}
	finally();
	return ret;
}
*/

/**
 * 例外情報を格納するオブジェクト.
 */
typedef struct jmpbuf_trace {
	jmp_buf buf;
	int kind;
} jmpbuf_trace;

/**
 * setjmpより手前でこれを呼び出します.
 * @return
 */
jmpbuf_trace* begin_panic();

/**
 * パニックを発生させ、最寄りのキャッチへ goto します.
 * @param kind
 */
void panic(int kind);

/**
 * begin_panicよりもあとで、setjmp より前に呼び出す.
 * @param kind
 */
void handle_panic(int kind);

/**
 * 例外を補足することなく処理が終了した場合に呼び出します.
 */
void end_panic();

/**
 * 例外が発生していてもいなくても呼び出します.
 */
void finally();
#endif