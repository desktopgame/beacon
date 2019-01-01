#include "string.h"
#include <assert.h>
#include <string.h>
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

// proto
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]);
static void bc_string_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);

bc_Object* bc_NewString(const char* str) {
        bc_Object* ret =
            bc_ConstructObject(NULL, sizeof(bc_String), BC_GENERIC_STRING);
        ret->OnMessage = handle_obj_message;
        // ret->u.string_ = s;
        // ret->u.field_vec = NewVector();
        // ret->GType = GENERIC_STRING;
        // ret->VPtr = GetVTableType(TYPE_STRING);

        //配列を生成
        bc_Object* arr = bc_NewArray(strlen(str), BC_GENERIC_CHAR);
        // arr->Tag = OBJECT_ARRAY_T;
        bc_Type* arrType = bc_GetArrayType();
        bc_Type* strType = bc_FindTypeFromNamespace(bc_GetLangNamespace(NULL),
                                                    bc_InternString("String"));
        // arr->GType = NewGenericType(arrType);
        // arr->VPtr = GetVTableType(arrType);
        // arr->Tag = OBJECT_ARRAY_T;
        // AddArgsGenericType(arr->GType, GENERIC_CHAR);
        //ボックス化
        const char* itr = str;
        bc_Buffer* sb = bc_NewBuffer();
        for (int i = 0;; i++) {
                char c = str[i];
                if (c == '\0') {
                        break;
                }
                bc_SetElementAt((bc_Object*)arr, i, (bc_Object*)bc_NewChar(c));
                bc_AppendBuffer(sb, c);
        }
        bc_ShrinkBuffer(sb);
        // String#charArrayを埋める
        int temp = 0;
        bc_ResolveField(strType->Kind.Class, bc_InternString("charArray"),
                        &temp);
        bc_AssignVector(ret->Fields, temp, arr);
        bc_VectorItem* test = bc_AtVector(ret->Fields, temp);
        assert(test != NULL);
        // Array#lengthを埋める
        temp = 0;
        bc_ResolveField(arrType->Kind.Class, bc_InternString("length"), &temp);
        bc_AssignVector(arr->Fields, temp, bc_NewInteger(sb->Length));
        // C形式の文字列でも保存
        // AssignVector(ret->NativeSlotVec, 0, sb);
        ((bc_String*)ret)->Buffer = sb;
        return (bc_Object*)ret;
}

void bc_InitString() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* stringType = bc_NewPreloadClass(bc_InternString("String"));
        bc_Class* stringClass = BC_TYPE2CLASS(stringType);
        stringType->AllocSize = sizeof(bc_String);
        bc_AddTypeNamespace(lang, stringType);
        bc_DefineNativeMethodClass(stringClass, "nativeInit",
                                   bc_string_nativeInit);
}

bc_Buffer* bc_GetRawString(bc_Object* self) {
        // VectorItem e = AtVector(self->NativeSlotVec, 0);
        // assert(self->Tag == OBJECT_STRING_T);
        return ((bc_String*)self)->Buffer;
}

bc_Type* bc_GetStringType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("String"));
}

// private
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]) {
        bc_String* str = ((bc_String*)self);
        if (msg == OBJECT_MSG_DELETE) {
                bc_DeleteBuffer(str->Buffer);
                str->Buffer = NULL;
                return bc_HandleObjectMessage(self, msg, argc, argv);
        } else if (msg == OBJECT_MSG_DESTROY) {
                bc_DeleteBuffer(str->Buffer);
                str->Buffer = NULL;
                return bc_HandleObjectMessage(self, msg, argc, argv);
        } else {
                return bc_HandleObjectMessage(self, msg, argc, argv);
        }
}

static void bc_string_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        //プログラムの中で ダブルクォート("HelloWorld") によって
        //文字列が作成された場合には Object_string_new()
        //によって生成されます。
        //こちらの場合では Object#nativeSlotVec に C形式の文字列を格納します。
        //これはコンストラクタによって String が作成された場合には
        //呼び出されないので、その部分の処理をここで行います。
        self->OnMessage = handle_obj_message;
        // String#charArrayを取得
        int temp = 0;
        bc_ResolveField(BC_TYPE_STRING->Kind.Class,
                        bc_InternString("charArray"), &temp);
        bc_Array* charArr = (bc_Array*)bc_AtVector(self->Fields, temp);
        //これを char* へ変換
        bc_Buffer* sb = bc_NewBuffer();
        for (int i = 0; i < charArr->Elements->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(charArr->Elements, i);
                assert(bc_IsCharValue(e));
                bc_AppendBuffer(sb, ((bc_Char*)e)->Value);
        }
        // AssignVector(self->NativeSlotVec, 0, sb);
        ((bc_String*)self)->Buffer = sb;
        // self->Tag = OBJECT_STRING_T;
}