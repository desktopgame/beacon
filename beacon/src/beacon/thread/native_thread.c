#include "native_thread.h"
#include "../util/mem.h"
#include "../util/vector.h"
#include <assert.h>

static Vector* gThreads = NULL;
static void mount_thread(NativeThread* self);
static void unmount_thread(NativeThread* self);
static void delete_thread(VectorItem item);

void InitNativeThread() {
	assert(gThreads == NULL);
	gThreads = NewVector();
}

NativeThread* AllocNativeThread(Runnable runnable, ThreadStartArgument arg) {
	NativeThread* ret = (NativeThread*)MEM_MALLOC(sizeof(NativeThread));
	ret->Runnable = runnable;
	ret->Arg = arg;
	return ret;
}

int StartNativeThread(Runnable runnable, ThreadStartArgument arg, NativeThread** outNativeThread) {
	assert(gThreads != NULL);
	NativeThread* nt = AllocNativeThread(runnable, arg);
	nt->Index = gThreads->Length;
	(*outNativeThread) = nt;
	mount_thread(nt);

	#if defined(USE_PTHREAD)
	return pthread_create(&nt->t, NULL, runnable, arg);
	#elif defined(USE_WINTHREAD)

	#endif
}

void InitNativeMutex(NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_init(mtx, NULL);
	#elif defined(USE_WINTHREAD)

	#endif
}

void NativeMutexEnter(NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_lock(mtx);
	#elif defined(USE_WINTHREAD)

	#endif
}

void NativeMutexExit(NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_unlock(mtx);
	#elif defined(USE_WINTHREAD)

	#endif
}

void DestroyNativeMutex(NativeMutex * mtx) {
	#if defined(USE_PTHREAD)
	pthread_mutex_destroy(mtx);
	#elif defined(USE_WINTHREAD)

	#endif
}

unsigned int NativeSleep(unsigned int seconds) {
	#if defined(USE_PTHREAD)
	return sleep(seconds);
	#elif defined(USE_WINTHREAD)

	return 0;
	#endif
}

void JoinNativeThread(NativeThread* self) {
	assert(self != NULL);
	#if defined(USE_PTHREAD)
	pthread_join(self->t, NULL);
	#elif defined(USE_WINTHREAD)

	#endif
}

void DetachNativeThread(NativeThread** self) {
	NativeThread* data = (*self);
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

NativeThread* GetNativeThreadAt(int index) {
	return (NativeThread*)AtVector(gThreads, index);
}

int GetNativeThreadCount() {
	return gThreads->Length;
}

void DestroyNativeThread() {
	assert(gThreads != NULL);
	DeleteVector(gThreads, delete_thread);
}
//private
static void mount_thread(NativeThread* self) {
	PushVector(gThreads, self);
}

static void unmount_thread(NativeThread* self) {
	RemoveVector(gThreads, FindVector(gThreads, self));
}

static void delete_thread(VectorItem item) {
	NativeThread* th = (NativeThread*)item;
	DetachNativeThread(&th);
}