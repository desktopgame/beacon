#include "class_loader_il.h"
#include <assert.h>
#include "../ast/ast.h"
#include "../error.h"
#include "../il/il_argument.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_factor_impl.h"
#include "../il/il_field.h"
#include "../il/il_import.h"
#include "../il/il_method.h"
#include "../il/il_namespace.h"
#include "../il/il_operator_overload.h"
#include "../il/il_parameter.h"
#include "../il/il_property.h"
#include "../il/il_stmt_impl.h"
#include "../il/il_top_level.h"
#include "../il/il_type_argument.h"
#include "../il/il_type_impl.h"
#include "../il/il_type_parameter.h"
#include "class_loader.h"

static void load_import_list(bc_ClassLoader* self, bc_AST* asource);
static void load_import(bc_ClassLoader* self, bc_AST* aimport_decl);
static void load_namespace_root(bc_ClassLoader* self, bc_Vector* parent,
                                bc_AST* aNamespacedecl);
static bc_ILNamespace* load_ast_to_namespace(bc_AST* a);
static void load_namespace_child_entry(bc_ClassLoader* self,
                                       bc_ILNamespace* current,
                                       bc_Vector* parent,
                                       bc_AST* aNamespacebody);
static void load_abstract_class(bc_ClassLoader* self, bc_ILNamespace* current,
                                bc_AST* aclass_decl);
static void load_class(bc_ClassLoader* self, bc_ILNamespace* current,
                       bc_AST* aclass_decl);
static bc_ILClass* load_class_common(bc_ClassLoader* self,
                                     bc_ILNamespace* current,
                                     bc_AST* aclass_decl);
static void load_interface(bc_ClassLoader* self, bc_ILNamespace* current,
                           bc_AST* ainterface_decl);
static void load_enum(bc_ClassLoader* self, bc_ILNamespace* current,
                      bc_AST* aenum_decl);
static void load_identifier_list(bc_ClassLoader* self, bc_Vector* list,
                                 bc_AST* asource);
static void load_type_parameter(bc_ClassLoader* self, bc_AST* asource,
                                bc_Vector* dest);
static void load_type_argument(bc_ClassLoader* self, bc_AST* atype_args,
                               bc_Vector* dest);
static void load_typename_list(bc_ClassLoader* self, bc_Vector* dst,
                               bc_AST* atypename_list);
static void load_fqcn_cache(struct bc_AST* afqcn, struct bc_FQCNCache* fqcn);
static void load_fqcn_cache_impl(bc_AST* afqcn, bc_FQCNCache* fqcn, int level);
static void load_generic_cache(struct bc_AST* afqcn,
                               struct bc_GenericCache* dest);
static void load_generic_cache_impl(bc_AST* afqcn, bc_GenericCache* dest);
static void load_generic_cache_inner(bc_AST* atype_args, bc_GenericCache* dest);
static void ast_fqcn_flatten(bc_AST* afqcn, bc_Vector* dest);
static void load_member_tree(bc_ClassLoader* self, bc_ILType* current,
                             bc_AST* atree);
static void load_member_list(bc_ClassLoader* self, bc_ILType* current,
                             bc_AST* amember, bc_AccessLevel level);
static void load_field(bc_ClassLoader* self, bc_ILType* current, bc_AST* afield,
                       bc_AccessLevel level);

static void load_property(bc_ClassLoader* self, bc_ILType* current,
                          bc_AST* aprop, bc_AccessLevel level);
static bc_ILPropertyBody* load_property_body(bc_ClassLoader* self,
                                             bc_ILType* current, bc_AST* abody,
                                             bc_ILPropertyBodyTag tag,
                                             bc_AccessLevel level);
static void load_method(bc_ClassLoader* self, bc_ILType* current,
                        bc_AST* amethod, bc_AccessLevel level);

static void load_constructor(bc_ClassLoader* self, bc_ILType* current,
                             bc_AST* aconstructor, bc_AccessLevel level);

static void load_operator_overload(bc_ClassLoader* self, bc_ILType* current,
                                   bc_AST* aopov, bc_AccessLevel level);
static void load_parameter_list(bc_ClassLoader* self, bc_Vector* list,
                                bc_AST* asource);
static void load_argument_list(bc_ClassLoader* self, bc_Vector* list,
                               bc_AST* asource);
//
// load statement
//
static void load_body(struct bc_ClassLoader* self, bc_Vector* list,
                      struct bc_AST* source);
static bc_ILStatement* load_stmt(bc_ClassLoader* self, bc_AST* asource);
static bc_ILInferencedTypeInit* load_inferenced_type_init(bc_ClassLoader* self,
                                                          bc_AST* asource);
static bc_ILVariableDecl* load_variable_decl(bc_ClassLoader* self,
                                             bc_AST* asource);
static bc_ILVariableInit* load_variable_init(bc_ClassLoader* self,
                                             bc_AST* asource);
static bc_ILIf* load_if(bc_ClassLoader* self, bc_AST* asource);
static bc_ILIf* load_if_elif_list(bc_ClassLoader* self, bc_AST* asource);
static void load_elif_list(bc_ClassLoader* self, bc_Vector* list,
                           bc_AST* asource);
static bc_ILIf* load_if_else(bc_ClassLoader* self, bc_AST* asource);
static bc_ILIf* load_if_elif_list_else(bc_ClassLoader* self, bc_AST* asource);
static bc_ILWhile* load_while(bc_ClassLoader* self, bc_AST* asource);
static bc_ILReturn* load_return(bc_ClassLoader* self, bc_AST* asource);
static bc_ILTry* load_try(bc_ClassLoader* self, bc_AST* asource);
static void load_catch_list(bc_ClassLoader* self, bc_Vector* dest,
                            bc_AST* asource);
static bc_ILThrow* load_throw(bc_ClassLoader* self, bc_AST* asource);
static bc_ILAssert* load_assert(bc_ClassLoader* self, bc_AST* asource);
static bc_ILDefer* load_defer(bc_ClassLoader* self, bc_AST* asource);
static bc_ILYieldReturn* load_yield_return(bc_ClassLoader* self,
                                           bc_AST* asource);
//
// load factor
//
static bc_ILFactor* CLILFactor(bc_ClassLoader* self, bc_AST* source);
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

bc_ILToplevel* bc_LoadAST(bc_ClassLoader* self, bc_AST* a) {
        bc_ILToplevel* ret = bc_NewILToplevel();
        for (int i = 0; i < a->Children->Length; i++) {
                bc_AST* child = bc_AtVector(a->Children, i);
                // import a
                if (child->Tag == AST_IMPORT_DECL_T ||
                    child->Tag == AST_IMPORT_DECL_LIST_T) {
                        load_import_list(self, child);
                        // namespace Foo { ... }
                } else if (child->Tag == AST_NAMESPACE_DECL_T) {
                        // load_namespace_root(
                        // self, self->ILCode->NamespaceList, child);
                        // print();
                } else if (bc_IsStmtAST(child)) {
                        // load_body(self, self->ILCode->StatementList, child);
                        // def f() { ... }
                } else if (child->Tag == AST_FUNCTION_DECL_T) {
                        // class_loader_ilload_function(self, child);
                } else {
                        // fprintf(stderr, "ast is not collected\n");
                        // bc_FatalError();
                }
        }
        return ret;
}
// private
static void load_import_list(bc_ClassLoader* self, bc_AST* asource) {
        if (asource->Tag == AST_IMPORT_DECL_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_import_list(self, bc_AtAST(asource, i));
                }
        } else {
                assert(asource->Tag == AST_IMPORT_DECL_T);
                load_import(self, asource);
        }
}

static void load_import(bc_ClassLoader* self, bc_AST* aimport_decl) {
        assert(aimport_decl->Tag == AST_IMPORT_DECL_T);
        bc_AST* apath = bc_FirstAST(aimport_decl);
        bc_ILImport* ret = bc_NewILImport(apath->Attr.StringVValue);
        bc_PushVector(self->ILCode->ImportList, ret);
}

static void load_namespace_root(bc_ClassLoader* self, bc_Vector* parent,
                                bc_AST* aNamespacedecl) {
        assert(aNamespacedecl->Tag == AST_NAMESPACE_DECL_T);
        bc_AST* aNamespacepath = bc_FirstAST(aNamespacedecl);
        bc_AST* aNamespacebody = bc_SecondAST(aNamespacedecl);
        bc_ILNamespace* iln = load_ast_to_namespace(aNamespacepath);
        bc_ILNamespace* top = bc_GetRootILNamespace(iln);
        bc_PushVector(parent, top);
        load_namespace_child_entry(self, iln, iln->NamespaceList,
                                   aNamespacebody);
}

static bc_ILNamespace* load_ast_to_namespace(bc_AST* a) {
        assert(a->Tag == AST_NAMESPACE_PATH_T ||
               a->Tag == AST_NAMESPACE_PATH_LIST_T);
        if (a->Tag == AST_NAMESPACE_PATH_T) {
                bc_ILNamespace* ret = bc_NewILNamespace(a->Attr.StringVValue);
                return ret;
        } else if (a->Tag == AST_NAMESPACE_PATH_LIST_T) {
                bc_AST* al = bc_FirstAST(a);
                bc_AST* ar = bc_SecondAST(a);
                bc_ILNamespace* parent = load_ast_to_namespace(al);
                bc_ILNamespace* child = load_ast_to_namespace(ar);
                child->Parent = parent;
                bc_PushVector(parent->NamespaceList, child);
                return child;
        }
        return NULL;
}

static void load_namespace_child_entry(bc_ClassLoader* self,
                                       bc_ILNamespace* current,
                                       bc_Vector* parent,
                                       bc_AST* aNamespacebody) {
        if (bc_IsBlankAST(aNamespacebody)) {
                return;
        }
        // namespace xxx { ...
        // namespace xxx { namespace yyy { ...
        if (aNamespacebody->Tag == AST_NAMESPACE_DECL_T) {
                load_namespace_root(self, parent, aNamespacebody);
                // namespace xxx { abstract class yyy { ...
        } else if (aNamespacebody->Tag == AST_ABSTRACT_CLASS_DECL_T) {
                load_abstract_class(self, current, aNamespacebody);
                // namespace xxx { class yyy { ...
        } else if (aNamespacebody->Tag == AST_CLASS_DECL_T) {
                load_class(self, current, aNamespacebody);
                // namespace xxx { interface yyy { ...
        } else if (aNamespacebody->Tag == AST_INTERFACE_DECL) {
                load_interface(self, current, aNamespacebody);
                // namespace xxx { enum yyy { ...
        } else if (aNamespacebody->Tag == AST_ENUM_DECL_T) {
                load_enum(self, current, aNamespacebody);
                // namespace xxx { any yyy { ...
        } else if (aNamespacebody->Tag == AST_NAMESPACE_MEMBER_DECL_LIST_T) {
                for (int i = 0; i < aNamespacebody->Children->Length; i++) {
                        bc_AST* amember = bc_AtAST(aNamespacebody, i);
                        load_namespace_child_entry(self, current, parent,
                                                   amember);
                }
        }
}

static void load_abstract_class(bc_ClassLoader* self, bc_ILNamespace* current,
                                bc_AST* aclass_decl) {
        assert(aclass_decl->Tag == AST_ABSTRACT_CLASS_DECL_T);
        bc_ILClass* ilc = load_class_common(self, current, aclass_decl);
        ilc->IsAbstract = true;
}

static void load_class(bc_ClassLoader* self, bc_ILNamespace* current,
                       bc_AST* aclass_decl) {
        assert(aclass_decl->Tag == AST_CLASS_DECL_T);
        bc_ILClass* ilc = load_class_common(self, current, aclass_decl);
        ilc->IsAbstract = false;
}

static bc_ILClass* load_class_common(bc_ClassLoader* self,
                                     bc_ILNamespace* current,
                                     bc_AST* aclass_decl) {
        bc_AST* atypename = bc_FirstAST(aclass_decl);
        bc_AST* aextend_list = bc_SecondAST(aclass_decl);
        bc_AST* amember_tree = bc_AtAST(aclass_decl, 2);
        bc_ILClass* ilclassz = bc_NewILClass(atypename->Attr.StringVValue);
        bc_ILType* iltype = bc_WrapILClass(ilclassz);
        // class Foo<A, B>
        load_type_parameter(self, bc_FirstAST(atypename),
                            ilclassz->TypeParameters);
        // class Foo : X, Y
        load_typename_list(self, ilclassz->Extends, aextend_list);
        // public:
        //    ....
        //    ....
        if (!bc_IsBlankAST(amember_tree)) {
                load_member_tree(self, iltype, amember_tree);
        }
        bc_PushVector(current->TypeList, iltype);
        return ilclassz;
}

static void load_interface(bc_ClassLoader* self, bc_ILNamespace* current,
                           bc_AST* ainterface_decl) {
        bc_AST* atypename = bc_FirstAST(ainterface_decl);
        bc_AST* aextends_list = bc_SecondAST(ainterface_decl);
        bc_AST* amember_tree = bc_AtAST(ainterface_decl, 2);
        bc_ILInterface* ilinter =
            bc_NewILInterface(atypename->Attr.StringVValue);
        bc_ILType* iltype = bc_WrapILInterface(ilinter);
        // interface Foo<A, B>
        load_type_parameter(self, bc_FirstAST(atypename),
                            ilinter->TypeParameters);
        // interface Foo : XXX, YYY, CCC
        load_typename_list(self, ilinter->Extends, aextends_list);
        // public:
        //    ...
        if (!bc_IsBlankAST(amember_tree)) {
                load_member_tree(self, iltype, amember_tree);
        }
        bc_PushVector(current->TypeList, iltype);
}

static void load_enum(bc_ClassLoader* self, bc_ILNamespace* current,
                      bc_AST* aenum_decl) {
        assert(aenum_decl->Tag == AST_ENUM_DECL_T);
        bc_AST* aname_list = bc_FirstAST(aenum_decl);
        bc_ILEnum* ilenum = bc_NewILEnum(aenum_decl->Attr.StringVValue);
        load_identifier_list(self, ilenum->Items, aname_list);
        bc_PushVector(current->TypeList, bc_WrapILEnum(ilenum));
}

static void load_identifier_list(bc_ClassLoader* self, bc_Vector* list,
                                 bc_AST* asource) {
        if (asource->Tag == AST_IDENTIFIER_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_identifier_list(self, list, bc_AtAST(asource, i));
                }
        } else if (asource->Tag == AST_IDENTIFIER_T) {
                bc_StringView str = asource->Attr.StringVValue;
                bc_PushVector(list, (bc_VectorItem)str);
        }
}

static void load_type_parameter(bc_ClassLoader* self, bc_AST* asource,
                                bc_Vector* dest) {
        if (bc_IsBlankAST(asource)) {
                return;
        }
        if (asource->Tag == AST_TYPE_PARAMETER_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_type_parameter(self, bc_AtAST(asource, i), dest);
                }
                return;
        }
        assert(asource->Tag == AST_TYPE_PARAMETER_T ||
               asource->Tag == AST_TYPE_IN_PARAMETER_T ||
               asource->Tag == AST_TYPE_OUT_PARAMETER_T);
        bc_AST* arule_list = bc_FirstAST(asource);
        bc_ILTypeParameter* iltypeparam =
            bc_NewILTypeParameter(asource->Attr.StringVValue);
        if (asource->Tag == AST_TYPE_IN_PARAMETER_T)
                iltypeparam->Tag = IL_TYPE_PARAMETER_KIND_IN_T;
        if (asource->Tag == AST_TYPE_OUT_PARAMETER_T)
                iltypeparam->Tag = IL_TYPE_PARAMETER_KIND_OUT_T;
        bc_PushVector(dest, iltypeparam);
        //制約があるならそれも設定
        //制約はとりあえずなしで
        assert(bc_IsBlankAST(arule_list));
}

static void load_type_argument(bc_ClassLoader* self, bc_AST* atype_args,
                               bc_Vector* dest) {
        if (bc_IsBlankAST(atype_args)) {
                return;
        }
        if (atype_args->Tag == AST_TYPENAME_LIST_T) {
                for (int i = 0; i < atype_args->Children->Length; i++) {
                        bc_AST* e = bc_AtAST(atype_args, i);
                        load_type_argument(self, e, dest);
                }
        } else if (atype_args->Tag == AST_TYPENAME_T) {
                bc_ILTypeArgument* iltype_arg = bc_NewILTypeArgument();
                bc_PushVector(dest, iltype_arg);
                load_generic_cache(atype_args, iltype_arg->GCache);
        } else
                assert(false);
}

static void load_typename_list(bc_ClassLoader* self, bc_Vector* dst,
                               bc_AST* atypename_list) {
        if (bc_IsBlankAST(atypename_list)) {
                return;
        }
        if (atypename_list->Tag == AST_TYPENAME_T) {
                bc_GenericCache* e = bc_NewGenericCache();
                //[typename [fqcn]]
                load_generic_cache(atypename_list, e);
                bc_PushVector(dst, e);
        } else if (atypename_list->Tag == AST_TYPENAME_LIST_T) {
                for (int i = 0; i < atypename_list->Children->Length; i++) {
                        load_typename_list(self, dst,
                                           bc_AtAST(atypename_list, i));
                }
        }
}

static void load_fqcn_cache(bc_AST* afqcn, bc_FQCNCache* fqcn) {
        load_fqcn_cache_impl(afqcn, fqcn, 0);
}

static void load_fqcn_cache_impl(bc_AST* afqcn, bc_FQCNCache* fqcn, int level) {
        bc_Vector* v = bc_NewVector();
        ast_fqcn_flatten(afqcn, v);
        for (int i = 0; i < v->Length; i++) {
                bc_StringView S = (bc_StringView)bc_AtVector(v, i);
                if (i < v->Length - 1) {
                        bc_PushVector(fqcn->Scope, S);
                } else {
                        fqcn->Name = S;
                }
        }
        bc_DeleteVector(v, bc_VectorDeleterOfNull);
}

static void load_generic_cache(bc_AST* afqcn, bc_GenericCache* dest) {
        if (afqcn->Tag == AST_FQCN_CLASS_NAME_T) {
                dest->FQCN->Name = afqcn->Attr.StringVValue;
                return;
        }
        load_generic_cache_impl(afqcn, dest);
        bc_FQCNCache* body = dest->FQCN;
        // FIXME: Int のような文字パースで失敗してしまうので対策
        if (body->Name == 0 && body->Scope->Length > 0) {
                body->Name = (bc_StringView)bc_PopVector(body->Scope);
        }
}

static void load_generic_cache_impl(bc_AST* afqcn, bc_GenericCache* dest) {
        bc_FQCNCache* body = dest->FQCN;
        //型引数を解析する
        if (afqcn->Tag == AST_TYPENAME_T) {
                bc_AST* atype_args = bc_SecondAST(afqcn);
                if (!bc_IsBlankAST(atype_args)) {
                        load_generic_cache_inner(atype_args, dest);
                }
        }
        if (afqcn->Tag == AST_TYPENAME_T) {
                load_generic_cache_impl(bc_FirstAST(afqcn), dest);
                return;
        }
        if (afqcn->Tag == AST_FQCN_T || afqcn->Tag == AST_FQCN_PART_LIST_T) {
                if (afqcn->Tag == AST_FQCN_PART_LIST_T &&
                    afqcn->Children->Length == 0) {
                        // FIXME:もうちょっと高速に出来る
                        // FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
                        afqcn->Tag = AST_FQCN_CLASS_NAME_T;
                        body->Name = afqcn->Attr.StringVValue;
                        return;
                }
                for (int i = 0; i < afqcn->Children->Length; i++) {
                        bc_AST* c = bc_AtAST(afqcn, i);
                        load_generic_cache_impl(c, dest);
                }
        } else {
                // FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
                bc_PushVector(body->Scope, afqcn->Attr.StringVValue);
                afqcn->Tag = AST_FQCN_PART_T;
        }
}

static void load_generic_cache_inner(bc_AST* atype_args,
                                     bc_GenericCache* dest) {
        if (atype_args->Tag == AST_TYPENAME_LIST_T) {
                for (int i = 0; i < atype_args->Children->Length; i++) {
                        bc_AST* e = bc_AtAST(atype_args, i);
                        load_generic_cache_inner(e, dest);
                }
        } else {
                bc_GenericCache* newCache = bc_NewGenericCache();
                load_generic_cache(atype_args, newCache);
                bc_PushVector(dest->TypeArgs, newCache);
        }
}

static void ast_fqcn_flatten(bc_AST* afqcn, bc_Vector* dest) {
        if (afqcn->Tag == AST_FQCN_PART_T) {
                bc_PushVector(dest, afqcn->Attr.StringVValue);
        } else {
                for (int i = 0; i < afqcn->Children->Length; i++) {
                        ast_fqcn_flatten(bc_AtAST(afqcn, i), dest);
                }
        }
}

static void load_member_tree(bc_ClassLoader* self, bc_ILType* current,
                             bc_AST* atree) {
        if (atree->Tag == AST_ACCESS_MEMBER_TREE_T) {
                for (int i = 0; i < atree->Children->Length; i++) {
                        load_member_tree(self, current, bc_AtAST(atree, i));
                }
        } else if (atree->Tag == AST_ACCESS_MEMBER_LIST_T) {
                bc_AST* aaccess = bc_FirstAST(atree);
                bc_AST* amember_list = bc_SecondAST(atree);
                bc_AccessLevel level = bc_ASTCastToAccess(aaccess);
                load_member_list(self, current, amember_list, level);
        }
}

static void load_member_list(bc_ClassLoader* self, bc_ILType* current,
                             bc_AST* amember, bc_AccessLevel level) {
        if (amember->Tag == AST_MEMBER_DECL_LIST_T) {
                for (int i = 0; i < amember->Children->Length; i++) {
                        load_member_list(self, current, bc_AtAST(amember, i),
                                         level);
                }
        } else if (amember->Tag == AST_MEMBER_DECL_T) {
                bc_AST* achild = bc_FirstAST(amember);
                if (achild->Tag == AST_FIELD_DECL_T) {
                        load_field(self, current, achild, level);
                } else if (achild->Tag == AST_PROP_DECL_T) {
                        load_property(self, current, achild, level);
                } else if (achild->Tag == AST_METHOD_DECL_T) {
                        load_method(self, current, achild, level);
                } else if (achild->Tag == AST_CONSTRUCTOR_DECL_T) {
                        load_constructor(self, current, achild, level);
                } else if (achild->Tag == AST_OPERATOR_OVERLOAD_T) {
                        load_operator_overload(self, current, achild, level);
                }
        }
}

static void load_field(bc_ClassLoader* self, bc_ILType* current, bc_AST* afield,
                       bc_AccessLevel level) {
        // assert(current->Tag == ILTYPE_CLASS_T);
        bc_AST* amodifier = bc_FirstAST(afield);
        bc_AST* aGetTypeName = bc_SecondAST(afield);
        bc_AST* aaccess_name = bc_AtAST(afield, 2);
        bc_AST* afact = bc_AtAST(afield, 3);
        //インターフェイスはフィールドを持てない
        if (current->Tag == ILTYPE_INTERFACE_T) {
                bc_Panic(BCERROR_INTERFACE_HAS_FIELD_T,
                         bc_Ref2Str(current->Kind.Interface->Name),
                         bc_Ref2Str(aaccess_name->Attr.StringVValue));
                return;
        }
        bc_ILField* v = bc_NewILField(aaccess_name->Attr.StringVValue);
        load_generic_cache(aGetTypeName, v->GCache);
        bool error;
        v->Access = level;
        v->Modifier = bc_ASTCastToModifier(amodifier, &error);
        bc_AddFieldILType(current, v);
        //設定されているなら初期値も
        if (!bc_IsBlankAST(afact)) {
                v->InitialValue = CLILFactor(self, afact);
        }
        //重複する修飾子を検出
        if (error) {
                bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, bc_Ref2Str(v->Name));
        }
}

static void load_property(bc_ClassLoader* self, bc_ILType* current,
                          bc_AST* aprop, bc_AccessLevel level) {
        bc_AST* amod = bc_AtAST(aprop, 0);
        bc_AST* atypename = bc_AtAST(aprop, 1);
        bc_AST* aset = bc_AtAST(aprop, 2);
        bc_AST* aget = bc_AtAST(aprop, 3);
        bc_StringView propname = aprop->Attr.StringVValue;
        bc_ILProperty* ret = bc_ILNewProperty(propname);
        load_generic_cache(atypename, ret->GCache);
        if (bc_IsBlankAST(amod)) {
                ret->Modifier = MODIFIER_NONE_T;
        } else {
                bool err = false;
                ret->Modifier = bc_ASTCastToModifier(amod, &err);
                if (err) {
                        bc_Panic(BCERROR_OVERWRAP_MODIFIER_T,
                                 bc_Ref2Str(ret->Name));
                }
        }
        ret->Access = level;
        ret->Set =
            load_property_body(self, current, aset, IL_PROPERTY_SET_T, level);
        ret->Get =
            load_property_body(self, current, aget, IL_PROPERTY_GET_T, level);
        bc_AddPropertyILType(current, ret);
        if (ret->Set->IsShort != ret->Get->IsShort) {
                bc_Panic(BCERROR_INVALID_PROPERTY_DECL_T,
                         bc_Ref2Str(current->Kind.Class->Name),
                         bc_Ref2Str(propname));
        }
}

static bc_ILPropertyBody* load_property_body(bc_ClassLoader* self,
                                             bc_ILType* current, bc_AST* abody,
                                             bc_ILPropertyBodyTag tag,
                                             bc_AccessLevel level) {
        bc_ILPropertyBody* ret = bc_NewILPropertyBody(tag);
        assert(abody->Tag == AST_PROP_SET_T || abody->Tag == AST_PROP_GET_T);
        bc_AST* aacess = bc_FirstAST(abody);
        bc_AST* astmt_list = bc_SecondAST(abody);
        ret->Access = level;
        load_body(self, ret->Statements, astmt_list);
        if (!bc_IsBlankAST(aacess)) {
                ret->Access = aacess->Attr.AccessValue;
        }
        if (ret->Statements->Length == 0) {
                ret->IsShort = true;
        }
        return ret;
}

static void load_method(bc_ClassLoader* self, bc_ILType* current,
                        bc_AST* amethod, bc_AccessLevel level) {
        assert(current->Tag == ILTYPE_CLASS_T ||
               current->Tag == ILTYPE_INTERFACE_T);
        bc_AST* amodifier = bc_AtAST(amethod, 0);
        bc_AST* afunc_name = bc_AtAST(amethod, 1);
        bc_AST* ageneric = bc_AtAST(amethod, 2);
        bc_AST* aparam_list = bc_AtAST(amethod, 3);
        bc_AST* afunc_body = bc_AtAST(amethod, 4);
        bc_AST* aret_name = bc_AtAST(amethod, 5);
        bc_ILMethod* v = bc_NewILMethod(afunc_name->Attr.StringVValue);
        load_type_parameter(self, ageneric, v->TypeParameters);
        load_generic_cache(aret_name, v->ReturnGCache);
        bool error;
        v->Access = level;
        v->Modifier = bc_ASTCastToModifier(amodifier, &error);
        load_parameter_list(self, v->Parameters, aparam_list);
        load_body(self, v->Statements, afunc_body);
        //メソッドの本文が省略されているかどうか
        //例えばネイティブメソッドや抽象メソッドは省略されているべき
        if (bc_IsBlankAST(afunc_body)) {
                v->IsNoStmt = true;
        }
        bc_AddMethodILType(current, v);
        //重複する修飾子を検出
        if (error) {
                bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, bc_Ref2Str(v->Name));
        }
}

static void load_constructor(bc_ClassLoader* self, bc_ILType* current,
                             bc_AST* aconstructor, bc_AccessLevel level) {
        // assert(current->Tag == ILTYPE_CLASS_T);
        bc_AST* aparams = bc_AtAST(aconstructor, 0);
        bc_AST* achain = bc_AtAST(aconstructor, 1);
        bc_AST* abody = bc_AtAST(aconstructor, 2);
        bc_ILConstructorChain* ilchain = NULL;
        //インターフェイスはコンストラクタを持てない
        if (current->Tag == ILTYPE_INTERFACE_T) {
                bc_Panic(BCERROR_INTERFACE_HAS_CTOR_T,
                         bc_Ref2Str(current->Kind.Interface->Name));
                return;
        }
        if (!bc_IsBlankAST(achain)) {
                bc_AST* achain_type = bc_FirstAST(achain);
                bc_AST* aargs = bc_SecondAST(achain);
                ilchain = bc_NewILConstructorChain();
                ilchain->Type = bc_ASTCastToChainType(achain_type);
                load_argument_list(self, ilchain->Arguments, aargs);
        }
        bc_ILConstructor* ilcons = bc_NewILConstructor();
        ilcons->Access = level;
        ilcons->Chain = ilchain;
        load_parameter_list(self, ilcons->Parameters, aparams);
        load_body(self, ilcons->Statements, abody);
        bc_PushVector(current->Kind.Class->Constructors, ilcons);
}

static void load_operator_overload(bc_ClassLoader* self, bc_ILType* current,
                                   bc_AST* aopov, bc_AccessLevel level) {
        // assert(aopov->Tag == AST_OPERATOR_OVERLOAD_T);
        bc_OperatorType ot = aopov->Attr.OperatorValue;
        bc_AST* aparam_list = bc_AtAST(aopov, 0);
        bc_AST* abody = bc_AtAST(aopov, 1);
        bc_AST* areturn = bc_AtAST(aopov, 2);
        //インターフェイスはコンストラクタを持てない
        if (current->Tag == ILTYPE_INTERFACE_T) {
                bc_Panic(BCERROR_INTERFACE_HAS_OPOV_T,
                         bc_Ref2Str(current->Kind.Interface->Name),
                         bc_OperatorToString(ot));
                return;
        }
        bc_ILOperatorOverload* ilopov = bc_NewILOperatorOverload(ot);
        ilopov->Access = level;
        load_parameter_list(self, ilopov->Parameters, aparam_list);
        load_body(self, ilopov->Statements, abody);
        load_generic_cache(areturn, ilopov->ReturnGCache);
        bc_PushVector(current->Kind.Class->OperatorOverloads, ilopov);
}

static void load_parameter_list(bc_ClassLoader* self, bc_Vector* list,
                                bc_AST* asource) {
        if (asource->Tag == AST_PARAMETER_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_parameter_list(self, list, bc_AtAST(asource, i));
                }
        } else if (asource->Tag == AST_PARAMETER_T) {
                bc_AST* aGetTypeName = bc_FirstAST(asource);
                bc_AST* aaccess_name = bc_SecondAST(asource);
                bc_ILParameter* p =
                    bc_NewILParameter(aaccess_name->Attr.StringVValue);
                load_generic_cache(aGetTypeName, p->GCache);
                bc_PushVector(list, p);
        }
}

static void load_argument_list(bc_ClassLoader* self, bc_Vector* list,
                               bc_AST* asource) {
        if (asource->Tag == AST_ARGUMENT_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_argument_list(self, list, bc_AtAST(asource, i));
                }
        } else if (asource->Tag == AST_ARGUMENT_T) {
                bc_AST* aprimary = bc_FirstAST(asource);
                bc_ILArgument* ilarg = bc_NewILArgument();
                ilarg->Factor = CLILFactor(self, aprimary);
                bc_PushVector(list, ilarg);
        }
}

static void load_body(bc_ClassLoader* self, bc_Vector* list, bc_AST* source) {
        if (source == NULL) {
                return;
        }
        if (source->Tag == AST_STMT_LIST_T || source->Tag == AST_SCOPE_T) {
                for (int i = 0; i < source->Children->Length; i++) {
                        load_body(self, list, bc_AtAST(source, i));
                }
        } else {
                bc_ILStatement* stmt = load_stmt(self, source);
                if (stmt != NULL) {
                        stmt->Lineno = source->Lineno;
                        assert(source->Lineno >= 0);
                        bc_PushVector(list, stmt);
                }
        }
}

static bc_ILStatement* load_stmt(bc_ClassLoader* self, bc_AST* asource) {
        switch (asource->Tag) {
                case AST_STMT_T: {
                        return load_stmt(self, bc_FirstAST(asource));
                }
                case AST_PROC_T: {
                        bc_AST* afact = bc_FirstAST(asource);
                        bc_ILFactor* ilfact = CLILFactor(self, afact);
                        bc_ILProc* ilproc = bc_NewILProc();
                        ilproc->Factor = ilfact;
                        assert(ilfact != NULL);
                        return bc_WrapILProc(ilproc);
                }
                case AST_STMT_VARIABLE_DECL_T: {
                        bc_ILVariableDecl* ilvardecl =
                            load_variable_decl(self, asource);
                        return bc_WrapILVariableDecl(ilvardecl);
                }
                case AST_STMT_VARIABLE_INIT_T: {
                        bc_ILVariableInit* ilvarinit =
                            load_variable_init(self, asource);
                        return bc_WrapILVariableInit(ilvarinit);
                }
                case AST_INFERENCED_TYPE_INIT_T: {
                        bc_ILInferencedTypeInit* ilinfer =
                            load_inferenced_type_init(self, asource);
                        return bc_WrapILInferencedTypeInit(ilinfer);
                }
                case AST_IF_T: {
                        bc_ILIf* ilif = load_if(self, asource);
                        return bc_WrapILIf(ilif);
                }
                case AST_IF_ELIF_LIST_T: {
                        bc_ILIf* ilif = load_if_elif_list(self, asource);
                        return bc_WrapILIf(ilif);
                }
                case AST_IF_ELSE_T: {
                        bc_ILIf* ilif = load_if_else(self, asource);
                        return bc_WrapILIf(ilif);
                }
                case AST_IF_ELIF_LIST_ELSE_T: {
                        bc_ILIf* ilif = load_if_elif_list_else(self, asource);
                        return bc_WrapILIf(ilif);
                }
                case AST_WHILE_T: {
                        bc_ILWhile* ilwh = load_while(self, asource);
                        return bc_WrapILWhile(ilwh);
                }
                case AST_BREAK_T: {
                        return bc_WrapILBreak();
                }
                case AST_CONTINUE_T: {
                        return bc_WrapILContinue();
                }
                case AST_RETURN_T: {
                        bc_ILReturn* ilret = load_return(self, asource);
                        return bc_WrapILReturn(ilret);
                }
                case AST_RETURN_EMPTY_T: {
                        bc_ILStatement* ret =
                            bc_NewILStatement(ILSTMT_RETURN_EMPTY_T);
                        ret->Kind.ReturnEmpty = NULL;
                        return ret;
                }
                case AST_STMT_TRY_T: {
                        bc_ILTry* iltry = load_try(self, asource);
                        return bc_WrapILTry(iltry);
                }
                case AST_STMT_THROW_T: {
                        bc_ILThrow* ilthrow = load_throw(self, asource);
                        return bc_WrapILThrow(ilthrow);
                }
                case AST_STMT_ASSERT_T: {
                        bc_ILAssert* ilas = load_assert(self, asource);
                        return bc_WrapILAssert(ilas);
                }
                case AST_STMT_DEFER_T: {
                        bc_ILDefer* ildef = load_defer(self, asource);
                        return bc_WrapILDefer(ildef);
                }
                case AST_YIELD_RETURN_T: {
                        return bc_WrapILYieldReturn(
                            load_yield_return(self, asource));
                }
                case AST_YIELD_BREAK_T: {
                        bc_ILStatement* ret =
                            bc_NewILStatement(ILSTMT_YIELD_BREAK_T);
                        ret->Kind.YieldBreak = NULL;
                        return ret;
                }
                case AST_INJECT_JNI_VALUE_T: {
                        bc_ILInjectJNI* jni =
                            bc_NewILInjectJNI(asource->Attr.StringVValue);
                        bc_AST* afact = bc_FirstAST(asource);
                        jni->Value = CLILFactor(self, afact);
                        jni->Value->Lineno = 0;
                        return bc_WrapILInjectJNI(jni);
                }
                default:
                        break;
        }
        return NULL;
}

static bc_ILInferencedTypeInit* load_inferenced_type_init(bc_ClassLoader* self,
                                                          bc_AST* asource) {
        bc_AST* aname = bc_FirstAST(asource);
        bc_AST* afact = bc_SecondAST(asource);
        bc_ILInferencedTypeInit* ret =
            bc_NewILInferencedTypeInit(aname->Attr.StringVValue);
        ret->Value = CLILFactor(self, afact);
        return ret;
}

static bc_ILVariableDecl* load_variable_decl(bc_ClassLoader* self,
                                             bc_AST* asource) {
        bc_AST* afqcn = bc_FirstAST(asource);
        bc_AST* aname = bc_SecondAST(asource);
        bc_ILVariableDecl* ret = bc_NewILVariableDecl(aname->Attr.StringVValue);
        ret->Name = aname->Attr.StringVValue;
        load_generic_cache(bc_FirstAST(afqcn), ret->GCache);
        return ret;
}

static bc_ILVariableInit* load_variable_init(bc_ClassLoader* self,
                                             bc_AST* asource) {
        bc_AST* afqcn = bc_FirstAST(asource);
        bc_AST* aident = bc_SecondAST(asource);
        bc_AST* afact = bc_AtAST(asource, 2);
        bc_ILVariableInit* ret =
            bc_NewILVariableInit(aident->Attr.StringVValue);
        load_generic_cache(afqcn, ret->GCache);
        ret->Value = CLILFactor(self, afact);
        return ret;
}

static bc_ILIf* load_if(bc_ClassLoader* self, bc_AST* asource) {
        assert(asource->Tag == AST_IF_T);
        bc_ILIf* ret = bc_NewILIf();
        bc_AST* acond = bc_FirstAST(asource);
        bc_AST* abody = bc_SecondAST(asource);
        bc_ILFactor* ilcond = CLILFactor(self, acond);
        load_body(self, ret->Body, abody);
        ret->Condition = ilcond;
        return ret;
}

static bc_ILIf* load_if_elif_list(bc_ClassLoader* self, bc_AST* asource) {
        bc_AST* aif = bc_FirstAST(asource);
        bc_AST* aelif_list = bc_SecondAST(asource);
        bc_ILIf* ilif = load_if(self, aif);
        load_elif_list(self, ilif->ElifList, aelif_list);
        return ilif;
}

static bc_ILIf* load_if_else(bc_ClassLoader* self, bc_AST* asource) {
        bc_AST* aif = bc_FirstAST(asource);
        bc_AST* aelse = bc_SecondAST(asource);
        bc_AST* abody = bc_FirstAST(aelse);
        bc_ILIf* ilif = load_if(self, aif);
        load_body(self, ilif->Else->Body, abody);
        return ilif;
}

static bc_ILIf* load_if_elif_list_else(bc_ClassLoader* self, bc_AST* asource) {
        bc_AST* aif_eliflist = bc_FirstAST(asource);
        bc_AST* aelse = bc_SecondAST(asource);
        bc_ILIf* ilif = load_if_elif_list(self, aif_eliflist);
        load_body(self, ilif->Else->Body, bc_FirstAST(aelse));
        return ilif;
}

static bc_ILWhile* load_while(bc_ClassLoader* self, bc_AST* asource) {
        bc_AST* acond = bc_FirstAST(asource);
        bc_AST* abody = bc_SecondAST(asource);
        bc_ILWhile* ilwhile = bc_NewILWhile();
        ilwhile->Condition = CLILFactor(self, acond);
        load_body(self, ilwhile->Statements, abody);
        return ilwhile;
}

static void load_elif_list(bc_ClassLoader* self, bc_Vector* list,
                           bc_AST* asource) {
        if (asource->Tag == AST_ELIF_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_elif_list(self, list, bc_AtAST(asource, i));
                }
        } else if (asource->Tag == AST_ELIF_T) {
                bc_AST* acond = bc_FirstAST(asource);
                bc_AST* abody = bc_SecondAST(asource);
                bc_ILElif* ilelif = bc_NewILElif();
                ilelif->Condition = CLILFactor(self, acond);
                load_body(self, ilelif->Body, abody);
                bc_PushILElifList(list, ilelif);
        }
}

static bc_ILReturn* load_return(bc_ClassLoader* self, bc_AST* asource) {
        assert(asource->Tag == AST_RETURN_T);
        bc_AST* afact = bc_FirstAST(asource);
        bc_ILFactor* ilfact = CLILFactor(self, afact);
        bc_ILReturn* ret = bc_NewILReturn();
        ret->Factor = ilfact;
        return ret;
}

static bc_ILTry* load_try(bc_ClassLoader* self, bc_AST* asource) {
        bc_AST* abody = bc_FirstAST(asource);
        bc_AST* acatch_list = bc_SecondAST(asource);
        bc_ILTry* ret = bc_NewILTry();
        load_body(self, ret->Statements, abody);
        load_catch_list(self, ret->Catches, acatch_list);
        return ret;
}

static void load_catch_list(bc_ClassLoader* self, bc_Vector* dest,
                            bc_AST* asource) {
        if (asource->Tag == AST_STMT_CATCH_T) {
                bc_AST* atypename = bc_FirstAST(asource);
                bc_AST* aname = bc_SecondAST(asource);
                bc_AST* abody = bc_AtAST(asource, 2);
                bc_ILCatch* ilcatch = bc_NewILCatch(aname->Attr.StringVValue);
                load_generic_cache(bc_FirstAST(atypename), ilcatch->GCache);
                load_body(self, ilcatch->Statements, abody);
                bc_PushVector(dest, ilcatch);

        } else if (asource->Tag == AST_STMT_CATCH_LIST_T) {
                for (int i = 0; i < asource->Children->Length; i++) {
                        load_catch_list(self, dest, bc_AtAST(asource, i));
                }
        }
}

static bc_ILThrow* load_throw(bc_ClassLoader* self, bc_AST* asource) {
        bc_ILThrow* ret = bc_NewILThrow();
        ret->Factor = CLILFactor(self, bc_FirstAST(asource));
        return ret;
}

static bc_ILAssert* load_assert(bc_ClassLoader* self, bc_AST* asource) {
        bc_ILAssert* ret = bc_NewILAssert();
        bc_AST* afact = bc_FirstAST(asource);
        bc_AST* amsg = bc_SecondAST(asource);
        ret->Condition = CLILFactor(self, afact);
        if (bc_IsBlankAST(amsg)) {
                ret->Message = NULL;
        } else {
                ret->Message = CLILFactor(self, amsg);
        }
        return ret;
}

static bc_ILDefer* load_defer(bc_ClassLoader* self, bc_AST* asource) {
        assert(asource->Tag == AST_STMT_DEFER_T);
        bc_AST* astmt = bc_FirstAST(asource);
        bc_ILDefer* ret = bc_NewILDefer();
        ret->Task = load_stmt(self, astmt);
        return ret;
}

static bc_ILYieldReturn* load_yield_return(bc_ClassLoader* self,
                                           bc_AST* asource) {
        bc_ILYieldReturn* ret = bc_NewILYieldReturn();
        ret->Value = CLILFactor(self, bc_FirstAST(asource));
        return ret;
}

static bc_ILFactor* CLILFactor(bc_ClassLoader* self, bc_AST* source) {
        bc_ILFactor* ret = CLILFactorImpl(self, source);
        assert(source->Lineno >= 0);
        ret->Lineno = source->Lineno;
        return ret;
}

static bc_ILFactor* CLILFactorImpl(bc_ClassLoader* self, bc_AST* source) {
        if (source->Tag == AST_SHORT_T) {
                return bc_WrapILShort(bc_NewILShort(source->Attr.ShortValue));
        } else if (source->Tag == AST_INT_T) {
                return bc_WrapILInt(bc_NewILInt(source->Attr.IntValue));
        } else if (source->Tag == AST_LONG_T) {
                return bc_WrapILLong(bc_NewILLong(source->Attr.LongValue));
        } else if (source->Tag == AST_FLOAT_T) {
                return bc_WrapILFloat(bc_NewILFloat(source->Attr.FloatValue));
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
        load_fqcn_cache(afqcn, ilvar->FQCN);
        load_type_argument(self, atype_args, ilvar->TypeArgs);
        return ilvar;
}

static bc_ILNewInstance* CLIL_new_instance(bc_ClassLoader* self,
                                           bc_AST* source) {
        assert(source->Tag == AST_NEW_INSTANCE_T);
        bc_AST* afqcn = bc_FirstAST(source);
        bc_AST* atype_args = bc_SecondAST(source);
        bc_AST* aargs = bc_AtAST(source, 2);
        bc_ILNewInstance* ret = bc_NewILNewInstance();
        load_fqcn_cache(afqcn, ret->FQCNCache);
        load_type_argument(self, atype_args, ret->TypeArgs);
        load_argument_list(self, ret->Arguments, aargs);
        return ret;
}

static bc_ILAs* CLIL_as(bc_ClassLoader* self, bc_AST* source) {
        bc_ILAs* ret = bc_NewILAs();
        ret->Source = CLILFactor(self, bc_FirstAST(source));
        load_generic_cache(bc_SecondAST(source), ret->GCache);
        return ret;
}

static bc_ILCallOp* CLIL_call_op(bc_ClassLoader* self, bc_AST* source) {
        assert(source->Tag == AST_OP_CALL_T);
        bc_ILCallOp* ret = bc_NewILCallOp();
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* aargs = bc_SecondAST(source);
        ret->Receiver = CLILFactor(self, afact);
        load_argument_list(self, ret->Arguments, aargs);
        return ret;
}

static bc_ILMemberOp* CLIL_member_op(bc_ClassLoader* self, bc_AST* source) {
        assert(source->Tag == AST_FIELD_ACCESS_T);
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* aname = bc_SecondAST(source);
        bc_AST* atype_args = bc_AtAST(source, 2);
        bc_ILMemberOp* ret = bc_NewILMemberOp(aname->Attr.StringVValue);
        ret->Source = CLILFactor(self, afact);
        load_type_argument(self, atype_args, ret->TypeArgs);
        return ret;
}

static bc_ILInstanceOf* CLIL_instanceof(bc_ClassLoader* self, bc_AST* source) {
        assert(source->Tag == AST_INSTANCEOF_T);
        bc_AST* afact = bc_FirstAST(source);
        bc_AST* atype = bc_SecondAST(source);
        bc_ILInstanceOf* ret = bc_NewILInstanceOf();
        ret->Source = CLILFactor(self, afact);
        load_generic_cache(atype, ret->GCache);
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