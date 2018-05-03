#ifndef BEACON_CL_H
#define BEACON_CL_H

/**
 * 全てのテストを実行します.
 * @param argc
 * @param argv
 * @return
 */
int cl_test(int argc, char* argv[]);

/**
 * ASTをダンプします.
 * @param filename
 * @return
 */
int cl_ast(const char* filename);

/**
 * ASTをダンプします.
 * @param filename
 * @return
 */
int cl_il(const char* filename);

/**
 * オペコードをダンプします.
 * @param filename
 * @return
 */
int cl_op(const char* filename);

/**
 * 指定のファイルを実行します.
 * @param filename
 * @return
 */
int cl_run(const char* filename);
#endif