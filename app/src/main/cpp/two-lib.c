//
// Created by XiaopengWang on 2017/5/15.
//

#include <stdlib.h>
#include <stdio.h>
#include <jni.h>
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

//jstring
//Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
//                                                  jobject thiz )
//JNIEnv* env 是结构体JNINativeInterface 的二级指针
// JNIEnv 是结构体JNINativeInterface 的一级指针
// JNINativeInterface结构体中定义了大量的函数指针 这些函数指针在jni开发中很常用
// (*env)->
//jobject  调用本地函数的java对象 在这个例子中 就是MainActivity的实例
//c本地函数命名规则  Java_包名_类名_本地方法名
//jstring     (*NewStringUTF)(JNIEnv*, const char*);
jstring Java_com_example_xiaopengwang_ndkdemo_MainActivity_stringFromJNI2(JNIEnv* env,jobject thiz){
    char* cstr = "hello from c!";
//    LOGD("内容是：%c", (*env)->NewStringUTF(env,cstr));
//    LOGI("内容是：%s",(*env)->NewStringUTF(env,cstr));
    return (*env)->NewStringUTF(env,cstr);
}
JNIEXPORT jint JNICALL
Java_com_example_xiaopengwang_ndkdemo_MainActivity_add(
        JNIEnv *env, jobject instance, jint x, jint y) {
    return x + y;
}
/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char* _JString2CStr(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env,"GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if(alen > 0) {
        rtn = (char*)malloc(alen+1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen]=0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba,0);
    return rtn;
}
JNIEXPORT jstring JNICALL
Java_com_example_xiaopengwang_ndkdemo_MainActivity_helloC(JNIEnv *env, jobject instance,
                                                          jstring c_) {
    char *c = (*env)->GetStringUTFChars(env, c_, 0);
    int length = strlen(c);
    int i = 0;
    for(;i < length;i++){
        *(c+1) += 1;
    }
    return (*env)->NewStringUTF(env, c);
}