#pragma once
#ifndef SIGNAL_IL_IL_STMT_IMPL_H
#define SIGNAL_IL_IL_STMT_IMPL_H
//このファイルはヘッダーファイルからはインクルードしないでください。
//代わりに il_stmt_interface.h をインクルードします。

#include "stmt/il_stmt_proc_impl.h"
#include "stmt/il_stmt_if_impl.h"
#include "stmt/il_stmt_while_impl.h"
#include "stmt/il_stmt_variable_decl_impl.h"
#include "stmt/il_stmt_variable_init_impl.h"
#include "stmt/il_stmt_return_impl.h"
#include "stmt/il_stmt_break_impl.h"
#include "stmt/il_stmt_continue_impl.h"
#include "stmt/il_stmt_inferenced_type_init_impl.h"
#include "stmt/il_stmt_try_impl.h"
#include "stmt/il_stmt_throw_impl.h"
#endif // !SIGNAL_IL_IL_STMT_IMPL_H