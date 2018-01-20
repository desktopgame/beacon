#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_IMPL_H
#define SIGNAL_IL_IL_FACTOR_IMPL_H
#include "il_factor_interface.h"
//このファイルはヘッダーファイルからはインクルードしないでください。
//代わりに il_factor_interface.h をインクルードします。

#include "factor/il_factor_int_impl.h"
#include "factor/il_factor_double_impl.h"
#include "factor/il_factor_char_impl.h"
#include "factor/il_factor_string_impl.h"
#include "factor/il_factor_call_impl.h"
#include "factor/il_factor_invoke_impl.h"
#include "factor/il_factor_named_invoke_impl.h"
#include "factor/il_factor_variable_impl.h"
#include "factor/il_factor_unary_op_impl.h"
#include "factor/il_factor_binary_op_impl.h"
#include "factor/il_factor_this_impl.h"
#include "factor/il_factor_super_impl.h"
#include "factor/il_factor_new_instance_impl.h"
#include "factor/il_factor_field_access_impl.h"
#include "factor/il_factor_static_field_access_impl.h"
#include "factor/il_factor_cast_impl.h"
#include "factor/il_factor_bool_impl.h"
#endif // !SIGNAL_IL_IL_FACTOR_IMPL_H
