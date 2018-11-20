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

static bc_Parser* parser_new();
static bc_Parser* gParser;

bc_Parser* bc_ParseString(const char* source) {
	assert(gParser == NULL);
	extern void yy_setstr(char *source);
	extern void yy_clearstr();
	extern int yyparse(void);
	gParser = parser_new();
	gParser->InputType = YINPUT_STRING_T;
	gParser->SourceName = NULL;
	yy_setstr(bc_Strdup(source));
	if (yyparse()) {
		yy_clearstr();
		gParser->Result = PARSE_SYNTAX_ERROR_T;
		bc_RelocationParserError(gParser);
		return gParser;
	}
	yy_clearstr();
	gParser->Result = PARSE_COMPLETE_T;
	return gParser;
}

bc_Parser* bc_ParseFile(const char* filename) {
	assert(gParser == NULL);
	extern void yy_setstr(char *source);
	extern int yyparse(void);
	extern FILE *yyin;
	yy_setstr(NULL);
	yyin = fopen(filename, "r");
	gParser = parser_new();
	gParser->InputType = YINPUT_FILE_T;
	gParser->SourceName = bc_Strdup(filename);
	//対象のファイルを開けなかった
	if(!yyin) {
		gParser->Result = PARSE_OPEN_ERROR_T;
		return gParser;
	}
	if (yyparse()) {
		gParser->Result = PARSE_SYNTAX_ERROR_T;
		bc_RelocationParserError(gParser);
		return gParser;
	}
	gParser->Result = PARSE_COMPLETE_T;
	return gParser;
}

bc_Parser* bc_GetCurrentParser() {
	return gParser;
}

void bc_DestroyParser(bc_Parser* self) {
	assert(gParser != NULL);
	if (gParser->Root) {
		bc_DeleteAST(gParser->Root);
	}
	bc_DeleteVector(gParser->LinenoTable, bc_VectorDeleterOfNull);
	MEM_FREE(gParser->LiteralBuffer);
	MEM_FREE(gParser->SourceName);
	MEM_FREE(gParser);
	gParser =  NULL;
}

void bc_ClearParserBuffer(bc_Parser* self) {
	self->LiteralBuffer = NULL;
}

void bc_AppendParserBuffer(bc_Parser* self, char ch) {
	if (self->LiteralBuffer == NULL) {
		self->LiteralBuffer = bc_NewBuffer();
	}
	bc_AppendBuffer(self->LiteralBuffer, ch);
}

bc_AST* bc_ReduceParserBuffer(bc_Parser* self) {
	//""のような空文字の場合
	if (self->LiteralBuffer == NULL) {
		return bc_NewASTString(bc_InternString(""));
	}
	bc_AST* ret = bc_NewASTString(bc_InternString2(self->LiteralBuffer));
	self->LiteralBuffer = NULL;
	return ret;
}

bc_AST* bc_ReleaseParserAST(bc_Parser* self) {
	bc_AST* ret = self->Root;
	self->Root = NULL;
	return ret;
}

void bc_RelocationParserError(bc_Parser* p) {
	bc_SetPanicFile(p->SourceName);
	bc_SetPanicLine(p->ErrorLineIndex);
	bc_SetPanicColumn(p->ErrorColumnIndex);
}

//private
static bc_Parser* parser_new() {
	bc_Parser* ret = MEM_MALLOC(sizeof(bc_Parser));
	assert(gParser == NULL);
	gParser = ret;
	ret->SourceName = NULL;
	ret->ErrorLineText = NULL;
	ret->ErrorLineIndex = -1;
	ret->ErrorColumnIndex = -1;
	ret->InputType = YINPUT_FILE_T;
	ret->Result = PARSE_AWAIT_T;
	ret->Lineno = 0;
	ret->LiteralBuffer = NULL;
	ret->LinenoTable = bc_NewVector();
	ret->Root = bc_NewAST(AST_ROOT_T);
	return ret;
}