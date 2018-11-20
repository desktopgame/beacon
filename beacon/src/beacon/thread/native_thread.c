#include "native_thread.h"
#include "../util/mem.h"
#include "../util/vector.h"
#include <assert.h>
#include <string.h>

static bc_Vector* gThreads = NULL;
static bc_NativeMutex gThreadsMTX;
static void mount_thread(bc_NativeThread* self);
static void unmount_thread(bc_NativeThread* self);

void bc_InitNativeThread() {
	assert(gThreads == NULL);
	gThreads = bc_NewVector();
	bc_InitNativeMutex(&gThreadsMTX);
	//最初のスレッドを作成
	bc_NativeThread* main = bc_AllocNativeThread(NULL, NULL);
	main->t = pthread_self();
	mount_thread(main);
}

bc_NativeThread* bc_AllocNativeThread(bc_Runnable runnable, bc_ThreadStartArgument arg) {
	bc_NativeThread* ret = (bc_NativeThread*)MEM_MALLOC(sizeof(bc_NativeThread));
	memset((void*)ret, 0, sizeof(bc_NativeThread));
	ret->Runnable = runnable;
	ret->Arg = arg;
	return ret;
}

int bc_StartNativeThread(bc_Runnable runnable, bc_ThreadStartArgument arg, bc_NativeThread** outNativeThread) {
	assert(gThreads != NULL);
	bc_NativeThread* nt = bc_AllocNativeThread(runnable, arg);
	(*outNativeThread) = nt;
	mount_thread(nt);

	#if defined(USE_PTHREAD)
	return pthread_create(&nt->t, NULL, runnable, arg);
	#elif defined(USE_WINTHREAD)

	#endif
}

void bc_InitNativeMutex(bc_NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_init(mtx, NULL);
	#elif defined(USE_WINTHREAD)

	#endif
}

void bc_NativeMutexEnter(bc_NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_lock(mtx);
	#elif defined(USE_WINTHREAD)

	#endif
}

void bc_NativeMutexExit(bc_NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_unlock(mtx);
	#elif defined(USE_WINTHREAD)

	#endif
}

void bc_DestroyNativeMutex(bc_NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_destroy(mtx);
	#elif defined(USE_WINTHREAD)

	#endif
}

unsigned int bc_NativeSleep(unsigned int seconds) {
	#if defined(USE_PTHREAD)
	return sleep(seconds);
	#elif defined(USE_WINTHREAD)

	return 0;
	#endif
}

void bc_JoinNativeThread(bc_NativeThread* self) {
	assert(self != NULL);
	#if defined(USE_PTHREAD)
	pthread_join(self->t, NULL);
	#elif defined(USE_WINTHREAD)

	#endif
}

void bc_DetachNativeThread(bc_NativeThread** self) {
	bc_NativeThread* data = (*self);
	assert(data != NULL);
	unmount_thread(data);

	#if defined(USE_PTHREAD)
	pthread_detach(data->t);
	MEM_FREE(data);
	(*self) = NULL;
	#elif defined(USE_WINTHREAD)
	MEM_FREE(data);
	(*self) = NULL;
	#endif
}

bc_NativeThread* bc_GetNativeThreadAt(int index) {
	return (bc_NativeThread*)bc_AtVector(gThreads, index);
}

bc_NativeThread* bc_GetMainThread() {
	return bc_GetNativeThreadAt(0);
}

bc_NativeThread* bc_GetActiveThread() {
	#if defined(USE_PTHREAD)
	pthread_t self = pthread_self();
	for(int i=0; i<gThreads->Length; i++) {
		bc_NativeThread* th = (bc_NativeThread*)bc_AtVector(gThreads, i);
		pthread_t other = th->t;
		if(pthread_equal(self, other)) {
			return th;
		}
	}
	#endif
	return NULL;
}

int bc_GetNativeThreadCount() {
	return gThreads->Length;
}

void bc_DestroyNativeThread() {
	assert(gThreads != NULL);
	while(gThreads->Length > 0) {
		bc_NativeThread* nt = (bc_NativeThread*)bc_AtVector(gThreads, 0);
		bc_DetachNativeThread(&nt);
	}
	bc_DeleteVector(gThreads, bc_VectorDeleterOfNull);
	bc_DestroyNativeMutex(&gThreadsMTX);
}
//private
static void mount_thread(bc_NativeThread* self) {
	bc_NativeMutexEnter(&gThreadsMTX);
	{
		self->Index = gThreads->Length;
		bc_PushVector(gThreads, self);
	}
	bc_NativeMutexExit(&gThreadsMTX);
}

static void unmount_thread(bc_NativeThread* self) {
	bc_NativeMutexEnter(&gThreadsMTX);
	{
		bc_RemoveVector(gThreads, bc_FindVector(gThreads, self));
	}
	bc_NativeMutexExit(&gThreadsMTX);
}