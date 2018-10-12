#ifndef BEACON_CL_H
#define BEACON_CL_H

/**
 * 全てのテストを実行します.
 * @param argc
 * @param argv
 * @return
 */
int TestCmd(int argc, char* argv[]);

/**
 * ASTをダンプします.
 * @param filename
 * @return
 */
int DumpASTCmd(const char* filename);

/**
 * ASTをダンプします.
 * @param filename
 * @return
 */
int DumpILCmd(const char* filename);

/**
 * オペコードをダンプします.
 * @param filename
 * @return
 */
int DumpOpCodeCmd(const char* filename);

/**
 * 指定のファイルを実行します.
 * @param filename
 * @return
 */
int RunCmd(const char* filename);
#endif