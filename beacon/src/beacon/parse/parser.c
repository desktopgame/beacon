#include "parser.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_pool.h"
#include "../ast/ast.h"
#include "../ast/ast_new_literal.h"
#include "../error.h"
#include <assert.h>
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static Parser* parser_new();
static Parser* gParser;

Parser* ParseString(const char* source) {
	assert(gParser == NULL);
	extern void yy_setstr(char *source);
	extern void yy_clearstr();
	extern int yyparse(void);
	gParser = parser_new();
	gParser->input_type = YINPUT_STRING_T;
	gParser->source_name = NULL;
	yy_setstr(Strdup(source));
	if (yyparse()) {
		yy_clearstr();
		gParser->result = PARSE_SYNTAX_ERROR_T;
		RelocationParserError(gParser);
		return gParser;
	}
	yy_clearstr();
	gParser->result = PARSE_COMPLETE_T;
	return gParser;
}

Parser* ParseFile(const char* filename) {
	assert(gParser == NULL);
	extern void yy_setstr(char *source);
	extern int yyparse(void);
	extern FILE *yyin;
	yy_setstr(NULL);
	yyin = fopen(filename, "r");
	gParser = parser_new();
	gParser->input_type = YINPUT_FILE_T;
	gParser->source_name = Strdup(filename);
	//対象のファイルを開けなかった
	if(!yyin) {
		gParser->result = PARSE_OPEN_ERROR_T;
		return gParser;
	}
	if (yyparse()) {
		gParser->result = PARSE_SYNTAX_ERROR_T;
		RelocationParserError(gParser);
		return gParser;
	}
	gParser->result = PARSE_COMPLETE_T;
	return gParser;
}

Parser* GetCurrentParser() {
	return gParser;
}

void DestroyParser(Parser* self) {
	assert(gParser != NULL);
	if (gParser->root) {
		DeleteAST(gParser->root);
	}
	DeleteVector(gParser->lineno_vec, VectorDeleterOfNull);
	MEM_FREE(gParser->literal_buffer);
	MEM_FREE(gParser->source_name);
	MEM_FREE(gParser);
	gParser =  NULL;
}

void ClearParserBuffer(Parser* self) {
	self->literal_buffer = NULL;
}

void AppendParserBuffer(Parser* self, char ch) {
	if (self->literal_buffer == NULL) {
		self->literal_buffer = NewBuffer();
	}
	AppendBuffer(self->literal_buffer, ch);
}

ast* ReduceParserBuffer(Parser* self) {
	//""のような空文字の場合
	if (self->literal_buffer == NULL) {
		return NewASTString(InternString(""));
	}
	ast* ret = NewASTString(InternString2(self->literal_buffer));
	self->literal_buffer = NULL;
	return ret;
}

ast* ReleaseParserAST(Parser* self) {
	ast* ret = self->root;
	self->root = NULL;
	return ret;
}

void RelocationParserError(Parser* p) {
	SetBCErrorFile(p->source_name);
	SetBCErrorLine(p->error_line_index);
	SetBCErrorColumn(p->error_column_index);
}

//private
static Parser* parser_new() {
	Parser* ret = MEM_MALLOC(sizeof(Parser));
	assert(gParser == NULL);
	gParser = ret;
	ret->source_name = NULL;
	ret->error_line_text = NULL;
	ret->error_line_index = -1;
	ret->error_column_index = -1;
	ret->input_type = YINPUT_FILE_T;
	ret->result = PARSE_AWAIT_T;
	ret->lineno = 0;
	ret->literal_buffer = NULL;
	ret->lineno_vec = NewVector();
	ret->root = ast_new(AST_ROOT_T);
	return ret;
}