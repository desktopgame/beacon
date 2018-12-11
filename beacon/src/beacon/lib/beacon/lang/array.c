#include "array.h"
#include <assert.h>
#include "../../../env/constructor.h"
#include "../../../env/exception.h"
#include "../../../env/field.h"
#include "../../../env/generic_type.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

// proto
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]);
static void bc_array_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_array_nativeSet(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_array_nativeGet(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_array_nativeCopy(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void delete_self(bc_VectorItem item);

bc_Object* bc_NewArray(int size, bc_GenericType* element_type) {
        // Array[T]を作成する
        bc_GenericType* array_type = bc_NewGenericType(bc_GetArrayType());
        bc_AddArgsGenericType(array_type, element_type);
        bc_Array* ret = bc_ConstructObject(sizeof(bc_Array), array_type);
        ret->Super.OnMessage = handle_obj_message;
        ret->Elements = bc_NewVector();
        for (int i = 0; i < size; i++) {
                bc_PushVector(ret->Elements, bc_GetNullObject());
        }
        return (bc_Object*)ret;
}

void bc_InitArray() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* arrayType = bc_NewPreloadClass(bc_InternString("Array"));
        bc_Class* arrayClass = BC_TYPE2CLASS(arrayType);
        arrayType->AllocSize = sizeof(bc_Array);
        bc_AddTypeNamespace(lang, arrayType);
        bc_DefineNativeMethodClass(arrayClass, "nativeInit",
                                   bc_array_nativeInit);
        bc_DefineNativeMethodClass(arrayClass, "nativeSet", bc_array_nativeSet);
        bc_DefineNativeMethodClass(arrayClass, "nativeGet", bc_array_nativeGet);
        bc_DefineNativeMethodClass(arrayClass, "nativeCopy",
                                   bc_array_nativeCopy);
}

bc_Type* bc_GetArrayType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Array"));
}

bc_Object* bc_DynamicNewArray(struct bc_GenericType* gtype, int length,
                              bc_Frame* fr) {
        bc_Type* arrayType = bc_GetArrayType();

        bc_Vector* args = bc_NewVector();
        bc_Vector* type_args = bc_NewVector();
        bc_PushVector(args, bc_NewInteger(length));
        bc_PushVector(type_args, gtype);
        bc_Object* ret =
            bc_NewInstanceClass(arrayType->Kind.Class, fr, args, type_args);
        bc_DeleteVector(args, bc_VectorDeleterOfNull);
        bc_DeleteVector(type_args, bc_VectorDeleterOfNull);

        return ret;
}

#define ARRAY_VALUE(obj) (((bc_Array*)obj)->Elements)
void bc_SetElementAt(bc_Object* arr, int index, bc_Object* o) {
        bc_AssignVector(ARRAY_VALUE(arr), index, o);
}

bc_Object* bc_GetElementAt(bc_Object* arr, int index) {
        return (bc_Object*)bc_AtVector(ARRAY_VALUE(arr), index);
}

int bc_GetArrayLength(bc_Object* arr) {
        // assert(arr->tag == OBJECT_ARRAY_T);
        return ARRAY_VALUE(arr)->Length;
}
// private
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]) {
        if (msg == OBJECT_MSG_MARKALL) {
                assert(argc == 1);
                bc_HandleObjectMessage(self, msg, argc, argv);
                bc_Vector* values = ARRAY_VALUE(self);
                for (int i = 0; i < values->Length; i++) {
                        bc_PaintAllObject((bc_Object*)bc_AtVector(values, i),
                                          argv[0].Int);
                }
                return NULL;
        } else if (msg == OBJECT_MSG_DELETE) {
                bc_DeleteVector(self->Fields, bc_VectorDeleterOfNull);
                bc_DeleteVector(ARRAY_VALUE(self), bc_VectorDeleterOfNull);
                MEM_FREE(self);
                return NULL;
        } else if (msg == OBJECT_MSG_DESTROY) {
                bc_DeleteVector(self->Fields, delete_self);
                bc_DeleteVector(ARRAY_VALUE(self), delete_self);
                self->Fields = NULL;
                ARRAY_VALUE(self) = NULL;
                bc_DeleteObject(self);
                return NULL;
        } else if (msg == OBJECT_MSG_PRINT) {
                printf("Array:%d", ARRAY_VALUE(self)->Length);
                return NULL;
        } else {
                return bc_HandleObjectMessage(self, msg, argc, argv);
        }
}

static void bc_array_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Type* tp = BC_MEMBER_TYPE(parent);
        // Array#lengthを取り出す
        int temp = 0;
        bc_Field* lengthField =
            bc_ResolveField(tp->Kind.Class, bc_InternString("length"), &temp);
        assert(lengthField != NULL && temp != -1);
        //対応する位置のオブジェクトを取り出す
        bc_Array* self = (bc_Array*)bc_AtVector(fr->VariableTable, 0);
        bc_Object* lengthObj = bc_AtVector(self->Super.Fields, temp);
        self->Super.OnMessage = handle_obj_message;
        assert(lengthObj != NULL);
        assert(self->Elements == NULL);
        self->Elements = bc_NewVector();
        bc_GenericType* targ = bc_AtVector(self->Super.GType->TypeArgs, 0);
        //配列の長さだけ確保
        int len = bc_ObjectToInt(lengthObj);
        assert(len >= 0);
        for (int i = 0; i < len; i++) {
                bc_Object* oe = bc_GetDefaultObject(targ);
                bc_PushVector(ARRAY_VALUE(self), oe);
        }
}

static void bc_array_nativeSet(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* idx = bc_AtVector(fr->VariableTable, 1);
        bc_Object* val = bc_AtVector(fr->VariableTable, 2);
        assert(bc_IsIntValue(idx));
        bc_AssignVector(ARRAY_VALUE(self), bc_ObjectToInt(idx), val);
}

static void bc_array_nativeGet(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* idx = bc_AtVector(fr->VariableTable, 1);
        //	Object* a = AtVector(vm->VariableTable, 2);
        assert(bc_IsIntValue(idx));
        bc_Object* ret =
            (bc_Object*)bc_AtVector(ARRAY_VALUE(self), bc_ObjectToInt(idx));
        // bc_Printfln("array get %d", idx->u.int_);
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_array_nativeCopy(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* src = bc_AtVector(fr->VariableTable, 1);
        bc_Object* srcOffset = bc_AtVector(fr->VariableTable, 2);
        bc_Object* dst = bc_AtVector(fr->VariableTable, 3);
        bc_Object* dstOffset = bc_AtVector(fr->VariableTable, 4);
        bc_Object* length = bc_AtVector(fr->VariableTable, 5);
        int srcLen = ARRAY_VALUE(src)->Length;
        int dstLen = ARRAY_VALUE(dst)->Length;
        int cpyLen = bc_ObjectToInt(length);
        //添え字がマイナス
        if (bc_ObjectToInt(srcOffset) < 0 || bc_ObjectToInt(dstOffset) < 0) {
                bc_ThrowVM(fr, bc_NewSimplefException(
                                   fr, "index must be positive: %d - %d",
                                   bc_ObjectToInt(srcOffset),
                                   bc_ObjectToInt(dstOffset)));
                return;
        }
        //添え字がはみ出している
        if ((bc_ObjectToInt(srcOffset) + cpyLen) > srcLen ||
            (bc_ObjectToInt(dstOffset) + cpyLen) > dstLen) {
                bc_ThrowVM(
                    fr,
                    bc_NewSimplefException(
                        fr, "index must be less than size of array: %d - %d",
                        bc_ObjectToInt(srcOffset), bc_ObjectToInt(dstOffset)));
                return;
        }
        for (int i = bc_ObjectToInt(srcOffset);
             i < (bc_ObjectToInt(srcOffset) + bc_ObjectToInt(length)); i++) {
                int a =
                    (i - bc_ObjectToInt(srcOffset)) + bc_ObjectToInt(dstOffset);
                bc_VectorItem e = bc_AtVector(ARRAY_VALUE(src), i);
                bc_AssignVector(ARRAY_VALUE(dst), a, e);
        }
}

static void delete_self(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DestroyObject(e);
}