#include <assert.h>
//#include <jni.h>
#include <string.h>

#include "jni.h"
#include "udpClient.h"
//#include "JNIHelp.h"

//using namespace android;

# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

extern "C"
{
//	extern void init();
//	extern void release();
//	extern void initTimer();
//	extern bool initSocket();

	static const char *classPathName = "com/example/udpclient/Interface";

	static jint createUdpClient(JNIEnv* env, jclass clazz, jstring ip, jint port){
		const char *utf8 = (env)->GetStringUTFChars(ip, NULL);
		assert(NULL != utf8);
		int sock = init(const_cast<char*>(utf8), port);
		(env)->ReleaseStringUTFChars(ip, utf8);
		return sock;
	}

	static jint deleteUdpClient(JNIEnv* env, jclass clazz){
		int sock = release();
		return sock;
	}

	static void startSendTimer(JNIEnv* env, jclass clazz)
	{
		initTimer();
	}

	static void StopSendTimer(JNIEnv* env, jclass clazz){
		stopTimer();
	}

	static JNINativeMethod methods[] = {

		{ "nativeCreateUdpClient", "(Ljava/lang/String;I)I",
			(void *)createUdpClient },

		{ "nativeDeleteUdpClient", "()I",
			(void *)deleteUdpClient },

		{ "nativeStartSendTimer", "()V",
			(void *)startSendTimer },

		{ "nativeStopTimer", "()V",
			(void *)StopSendTimer},

	};

	jint JNI_OnLoad(JavaVM* vm, void* reserved) {
		JNIEnv* env = NULL;
		jclass clazz;
		if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
			return JNI_ERR;
		}
		clazz = env->FindClass(classPathName);
		if (clazz == NULL) {
			return JNI_ERR;
		}

		if (env->RegisterNatives(clazz, methods, NELEM(methods)) < 0) {
			return JNI_ERR;
		}

		return JNI_VERSION_1_4;
	}
}

