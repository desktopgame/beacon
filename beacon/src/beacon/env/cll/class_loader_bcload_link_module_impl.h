#ifndef BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_LINK_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_LINK_MODULE_IMPL_H
#include "../class_loader.h"

void CLBC_excec_class_decl(class_loader* self);
void CLBC_excec_class_impl(class_loader* self);
void CLBC_excec_interface_decl(class_loader* self);
void CLBC_excec_interface_impl(class_loader* self);
void CLBC_yield(class_loader* parent, class_loader* target);
#endif