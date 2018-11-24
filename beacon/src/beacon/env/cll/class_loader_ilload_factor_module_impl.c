#include "class_loader_ilload_factor_module_impl.h"
#include <stdio.h>
#include "../../il/il_factor_impl.h"
#include "../../util/mem.h"
#include "../class_loader.h"
#include "class_loader_ilload_type_module_impl.h"
// proto
static bc_ILFactor* CLILFactorImpl(bc_ClassLoader* self, bc_AST* source);
static bc_ILBool* CLIL_true(bc_ClassLoader* self, bc_AST* source);
static bc_ILBool* CLIL_false(bc_ClassLoader* self, bc_AST* source);
static bc_ILUnaryOp* CLIL_unary(bc_ClassLoader* self, bc_AST* source,
                                bc_OperatorType type);
static bc_ILBinaryOp* CLIL_binary(bc_ClassLoader* self, bc_AST* source,
                                  bc_OperatorType type);
static bc_ILExplicitUnaryOp* CLIL_explicit_unary(bc_ClassLoader* self,
                                                 bc_AST* source,
                                                 bc_OperatorType type);
static bc_ILExplicitBinaryOp* CLIL_explicit_binary(bc_ClassLoader* self,
                                                   bc_AST* source,
                                                   bc_OperatorType type);
static bc_ILAssignOp* CLIL_assign(bc_ClassLoader* self, bc_AST* source);
static bc_ILAssignOp* CLIL_assign_arithmetic(bc_ClassLoader* self,
                                             bc_AST* source,
                                             bc_OperatorType type);
static bc_ILVariable* CLIL_variable(bc_ClassLoader* self, bc_AST* source);
static bc_ILNewInstance* CLIL_new_instance(bc_ClassLoader* self,
                                           bc_AST* source);
static bc_ILAs* CLIL_as(bc_ClassLoader* self, bc_AST* source);
static bc_ILCallOp* CLIL_call_op(bc_ClassLoader* self, bc_AST* source);
static bc_ILMemberOp* CLIL_member_op(bc_ClassLoader* self, bc_AST* source);
static bc_ILInstanceOf* CLIL_instanceof(bc_ClassLoader* self, bc_AST* source);
static bc_ILSubscript* CLIL_subscript(bc_ClassLoader* self, bc_AST* source);

bc_ILFactor* CLILFactor(bc_ClassLoader* self, bc_AST* source) {
        bc_ILFactor* ret = CLILFactorImpl(self, source);
        assert(source->Lineno >= 0);
        ret->Lineno = source->Lineno;
        return ret;
}

// private
static bc_ILFactor* CLILFactorImpl(bc_ClassLoader* self, bc_AST* source) {
        if (source->Tag == AST_INT_T) {
                return bc_WrapILInt(bc_NewILInt(source->Attr.IntValue));
        } else if (source->Tag == AST_DOUBLE_T) {
                return bc_WrapILDouble(
                    bc_NewILDouble(source->Attr.DoubleValue));
        } else if (source->Tag == AST_CHAR_T) {
                return bc_WrapILChar(bc_NewILChar(source->Attr.CharValue));
        } else if (source->Tag == AST_STRING_T) {
                return bc_WrapILString(
                    bc_NewILString(source->Attr.StringVValue));
        } else if (source->Tag == AST_VARIABLE_T) {
                return bc_WrapILVariable(CLIL_variable(self, source));
                // operator(+ - * / %)
        } else if (source->Tag == AST_ADD_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_ADD_T));
        } else if (source->Tag == AST_SUB_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_SUB_T));
        } else if (source->Tag == AST_MUL_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_MUL_T));
        } else if (source->Tag == AST_DIV_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_DIV_T));
        } else if (source->Tag == AST_MOD_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_MOD_T));
                // operator(| || & &&)
        } else if (source->Tag == AST_BIT_OR_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_BIT_OR_T));
        } else if (source->Tag == AST_LOGIC_OR_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_LOGIC_OR_T));
        } else if (source->Tag == AST_BIT_AND_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_BIT_AND_T));
        } else if (source->Tag == AST_LOGIC_AND_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_LOGIC_AND_T));
                //^
        } else if (source->Tag == AST_EXC_OR_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_EXCOR_T));
        } else if (source->Tag == AST_CHILDA_T) {
                return bc_WrapILUnaryOp(
                    CLIL_unary(self, source, OPERATOR_CHILDA_T));
                //<< >>
        } else if (source->Tag == AST_LSHIFT_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_LSHIFT_T));
        } else if (source->Tag == AST_RSHIFT_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_RSHIFT_T));
                // operator(== != > >= < <=)
        } else if (source->Tag == AST_EQUAL_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_EQ_T));
        } else if (source->Tag == AST_NOT_TEQUAL_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_NOT_EQ_T));
        } else if (source->Tag == AST_GT_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_GT_T));
        } else if (source->Tag == AST_GE_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_GE_T));
        } else if (source->Tag == AST_LT_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_LT_T));
        } else if (source->Tag == AST_LE_T) {
                return bc_WrapILBinaryOp(
                    CLIL_binary(self, source, OPERATOR_LE_T));
                // operator(= += -= *= /= %=)
        } else if (source->Tag == AST_AS_TSIGN_T) {
                return bc_WrapILAssignOp(CLIL_assign(self, source));
        } else if (source->Tag == AST_ADD_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_ADD_T));
        } else if (source->Tag == AST_SUB_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_SUB_T));
        } else if (source->Tag == AST_MUL_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_MUL_T));
        } else if (source->Tag == AST_DIV_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_DIV_T));
        } else if (source->Tag == AST_MOD_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_MOD_T));
                // instanceof
        } else if (source->Tag == AST_INSTANCEOF_T) {
                return bc_WrapILInstanceOf(CLIL_instanceof(self, source));
                //|= &=
        } else if (source->Tag == AST_OR_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_BIT_OR_T));
        } else if (source->Tag == AST_AND_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_BIT_AND_T));
                //<<= >>=
        } else if (source->Tag == AST_LSHIFT_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_LSHIFT_T));
        } else if (source->Tag == AST_RSHIFT_ASSIGN_T) {
                return bc_WrapILAssignOp(
                    CLIL_assign_arithmetic(self, source, OPERATOR_RSHIFT_T));
                //!-
        } else if (source->Tag == AST_NOT_T) {
                return bc_WrapILUnaryOp(
                    CLIL_unary(self, source, OPERATOR_NOT_T));
        } else if (source->Tag == AST_NEG_T) {
                return bc_WrapILUnaryOp(
                    CLIL_unary(self, source, OPERATOR_NEGATIVE_T));
        } else if (source->Tag == AST_EXPLICIT_UOPERATOR_T) {
                return bc_WrapILExplicitUnaryOp(CLIL_explicit_unary(
                    self, source, source->Attr.OperatorValue));
        } else if (source->Tag == AST_EXPLICIT_BIOPERATOR_T) {
                return bc_WrapILExplicitBinaryOp(CLIL_explicit_binary(
                    self, source, source->Attr.OperatorValue));
                // this super
        } else if (source->Tag == AST_THIS_T) {
                bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_THIS_T);
                bc_ILThis* th = bc_NewILThis();
                ret->Kind.This = th;
                return ret;
        } else if (source->Tag == AST_SUPER_T) {
                bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_SUPER_T);
                bc_ILSuper* sp = bc_NewILSuper();
                ret->Kind.Super = sp;
                return ret;
        } else if (source->Tag == AST_NEW_INSTANCE_T) {
                return bc_WrapILNewInstance(CLIL_new_instance(self, source));
        } else if (source->Tag == AST_TRUE_T) {
                return bc_WrapILBool(CLIL_true(self, source));
        } else if (source->Tag == AST_FALSE_T) {
                return bc_WrapILBool(CLIL_false(self, source));
        } else if (source->Tag == AST_NULL_T) {
                bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_NULL_T);
                ret->Kind.Null = NULL;
                return ret;
        } else if (source->Tag == AST_AS_T) {
                return bc_WrapILAs(CLIL_as(self, source));
        } else if (source->Tag == AST_OP_CALL_T) {
                return bc_WrapCallOp(CLIL_call_op(self, source));
        } else if (source->Tag == AST_FIELD_ACCESS_T) {
                return bc_WrapILMemberOp(CLIL_member_op(self, source));
        } else if (source->Tag == AST_SUBSCRIPT_ACCESS_T) {
                return bc_WrapILSubscript(CLIL_subscript(self, source));
        }
        bc_ILFactor* fact = bc_NewILFactor(ILFACTOR_UNARY_OP_T);
        return fact;
}

static bc_ILBool* CLIL_true(bc_ClassLoader* self, bc_AST* source) {
        return bc_NewILBool(true);
}

static bc_ILBool* CLIL_false(bc_ClassLoader* self, bc_AST* source) {
        return bc_NewILBool(false);
}

static bc_ILUnaryOp* CLIL_unary(bc_ClassLoader* self, bc_AST* source,
                                bc_OperatorType type) {
        bc_ILUnaryOp* ret = bc_NewILUnaryOp(type);
        bc_AST* a = bc_FirstAST(source);
        ret->Arg = CLILFactor(self, a);
        return ret;
}

static bc_ILBinaryOp* CLIL_binary(bc_ClassLoader* self, bc_AST* source,
                                  bc_OperatorType type) {
        bc_ILBinaryOp* ret = bc_NewILBinaryOp(type);
        bc_AST* aleft = bc_FirstAST(source);
        bc_AST* aright = bc_SecondAST(source);
        ret->Left = CLILFactor(self, aleft);
        ret->Right = CLILFactor(self, aright);
        return ret;
}

static bc_ILExplicitUnaryOp* CLIL_explicit_unary(bc_ClassLoader* self,
                                                 bc_AST* source,
                                                 bc_OperatorType type) {
        bc_ILExplicitUnaryOp* ret = bc_NewILExplicitUnaryOp(type);
        ret->Receiver = CLILFactor(self, bc_FirstAST(source));
        return ret;
}

static bc_ILExplicitBinaryOp* CLIL_explicit_binary(bc_ClassLoader* self,
                                                   bc_AST* source,
                                                   bc_OperatorType type) {
        bc_ILExplicitBinaryOp* ret = bc_NewILExplicitBinaryOp(type);
        ret->Receiver = CLILFactor(self, bc_FirstAST(source));
        ret->Arg = CLILFactor(self, bc_SecondAST(source));
        return ret;
}

static bc_ILAssignOp* CLIL_assign(bc_ClassLoader* self, bc_AST* source) {
        bc_ILAssignOp* ret = bc_NewILAssignOp();
        bc_AST* aleft = bc_FirstAST(source);
        bc_AST* aright = bc_SecondAST(source);
        ret->Left = CLILFactor(self, aleft);
        ret->Right = CLILFactor(self, aright);
        return ret;
}

static bc_ILAssignOp* CLIL_assign_arithmetic(bc_ClassLoader* self,
                                             bc_AST* source,
                                             bc_OperatorType type) {
        // a += b
        bc_ILAssignOp* ret = bc_NewILAssignOp();
        bc_ILBinaryOp* bin = bc_NewILBinaryOp(type);
        bc_AST* aleft = bc_FirstAST(source);
        bc_AST* aright = bc_SecondAST(source);
        bin->Left = CLILFactor(self, aleft);
        bin->Right = CLILFactor(self, aright);
        ret->Left = CLILFactor(self, aleft);
        ret->Right = bc_WrapILBinaryOp(bin);
        ret->Right->Lineno = aright->Lineno;
        return ret;
}

static bc_ILVariable* CLIL_variable(bc_ClassLoader* self, bc_AST* source) {
        bc_AST* afqcn = bc_FirstAST(source);
        bc_AST* atype_args = bc_SecondAST(source);

        bc_ILVariable* ilvar = bc_NewILVariable();
        CLILFQCNCache(afqcn, ilvar->FQCN);
        CLILTypeArgument(self, atype_args, ilvar->TypeArgs);
        return ilvar;
}

static bc_ILNewInstance* CLIL_new_instance(bc_ClassLoader* self,
                                           bc_AST* source) {
        assert(source->Tag == AST_NEW_INSTANCE_T);
        bc_AST* afqcn = bc_FirstAST(source);
        bc_AST* atype_args = bc_SecondAST(source);
        bc_AST* aargs = bc_AtAST(source, 2);
        bc_ILNewInstance* ret = bc_NewILNewInstance();
        CLILFQCNCache(afqcn, ret->FQCNCache);
        CLILTypeArgument(self, atype_args, ret->TypeArgs);
        CLILArgumentList(self, ret->Arguments, aargs);
        return ret;
}

static bc_ILAs* CLIL_as(bc_ClassLoader* self, bc_AST* source) {
        bc_ILAs* ret = bc_NewILAs();
        ret->Source = CLILFactor(self, bc_FirstAST(source));
        CLILGenericCache(bc_SecondAST(source), ret->GCache);
        return ret;
}

static bc_ILCallOp* CLIL_call_op(bc_ClassLoader* self, bc_AST* source) {
        assert(source->Tag == AST_OP_CALL_T);
        bc_ILCallOp* ret = bc_NewILCallOp();
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* aargs = bc_SecondAST(source);
        ret->Receiver = CLILFactor(self, afact);
        CLILArgumentList(self, ret->Arguments, aargs);
        return ret;
}

static bc_ILMemberOp* CLIL_member_op(bc_ClassLoader* self, bc_AST* source) {
        assert(source->Tag == AST_FIELD_ACCESS_T);
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* aname = bc_SecondAST(source);
        bc_AST* atype_args = bc_AtAST(source, 2);
        bc_ILMemberOp* ret = bc_NewILMemberOp(aname->Attr.StringVValue);
        ret->Source = CLILFactor(self, afact);
        CLILTypeArgument(self, atype_args, ret->TypeArgs);
        return ret;
}

static bc_ILInstanceOf* CLIL_instanceof(bc_ClassLoader* self, bc_AST* source) {
        assert(source->Tag == AST_INSTANCEOF_T);
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* atype = bc_SecondAST(source);
        bc_ILInstanceOf* ret = bc_NewILInstanceOf();
        ret->Source = CLILFactor(self, afact);
        CLILGenericCache(atype, ret->GCache);
        return ret;
}

static bc_ILSubscript* CLIL_subscript(bc_ClassLoader* self, bc_AST* source) {
        bc_ILSubscript* ret = bc_NewILSubscript();
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* apos = bc_SecondAST(source);
        ret->Receiver = CLILFactor(self, afact);
        ret->Position = CLILFactor(self, apos);
        return ret;
}