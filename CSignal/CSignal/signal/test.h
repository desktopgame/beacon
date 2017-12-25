#pragma once
#ifndef SIGNAL_TEST_H
#define SIGNAL_TEST_H

typedef struct OBJ {
	int index;
} OBJ;

typedef struct PERSON {
	char* name;
	int age;
} PERSON;

/**
 * スタックのテストを実行.
 */
void test_stack(void);

/**
 * リストのテストを実行.
 */
void test_list(void);

/**
 * ASTのテストを実行.
 */
void test_ast(void);

/**
 * ASTのテストを実行.
 */
void test_ast2(void);

/**
 * tree_mapのテストを実行.
 */
void test_tree_map(void);

/**
 * 名前空間のテストを実行.
 */
void test_namespace(void);

/**
 * IOのテストを実行.
 */
void test_io(void);

void test_io2(void);

void test_file_path(void);

void test_cll(void);

void test_struct(void);

void test_vector(void);

void test_vm(void);

void test_string_table(void);
#endif // !SIGNAL_TEST_H
