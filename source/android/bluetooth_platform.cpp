/*
 * android-specific implementation of the bluetooth extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "bluetooth_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_init_bluetooth;
static jmethodID g_enable_bluetooth;
static jmethodID g_disable_bluetooth;
static jmethodID g_is_bluetooth_enabled;
static jmethodID g_bluetooth_close;
static jmethodID g_bluetooth_enable_discoverability;
static jmethodID g_bluetooth_is_discovering;
static jmethodID g_bluetooth_setup_client;
static jmethodID g_is_bluetooth_connected;
static jmethodID g_bluetooth_message_start;
static jmethodID g_bluetooth_message_write_float;
static jmethodID g_bluetooth_message_write_int;
static jmethodID g_bluetooth_message_send_current;
static jmethodID g_is_bluetooth_message;
static jmethodID g_bluetooth_message_read_int;
static jmethodID g_bluetooth_message_read_float;
static jmethodID g_bluetooth_message_discard_current;
static jmethodID g_bluetooth_show_wrong_version_dialog;

s3eResult bluetoothInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("bluetooth");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_init_bluetooth = env->GetMethodID(cls, "init_bluetooth", "()Z");
    if (!g_init_bluetooth)
        goto fail;

    g_enable_bluetooth = env->GetMethodID(cls, "enable_bluetooth", "()V");
    if (!g_enable_bluetooth)
        goto fail;

    g_disable_bluetooth = env->GetMethodID(cls, "disable_bluetooth", "()V");
    if (!g_disable_bluetooth)
        goto fail;

    g_is_bluetooth_enabled = env->GetMethodID(cls, "is_bluetooth_enabled", "()Z");
    if (!g_is_bluetooth_enabled)
        goto fail;

    g_bluetooth_close = env->GetMethodID(cls, "bluetooth_close", "()V");
    if (!g_bluetooth_close)
        goto fail;

    g_bluetooth_enable_discoverability = env->GetMethodID(cls, "bluetooth_enable_discoverability", "()V");
    if (!g_bluetooth_enable_discoverability)
        goto fail;

    g_bluetooth_is_discovering = env->GetMethodID(cls, "bluetooth_is_discovering", "()Z");
    if (!g_bluetooth_is_discovering)
        goto fail;

    g_bluetooth_setup_client = env->GetMethodID(cls, "bluetooth_setup_client", "()V");
    if (!g_bluetooth_setup_client)
        goto fail;

    g_is_bluetooth_connected = env->GetMethodID(cls, "is_bluetooth_connected", "()Z");
    if (!g_is_bluetooth_connected)
        goto fail;

    g_bluetooth_message_start = env->GetMethodID(cls, "bluetooth_message_start", "()V");
    if (!g_bluetooth_message_start)
        goto fail;

    g_bluetooth_message_write_float = env->GetMethodID(cls, "bluetooth_message_write_float", "(Ljava/lang/String;)V");
    if (!g_bluetooth_message_write_float)
        goto fail;

    g_bluetooth_message_write_int = env->GetMethodID(cls, "bluetooth_message_write_int", "(I)V");
    if (!g_bluetooth_message_write_int)
        goto fail;

    g_bluetooth_message_send_current = env->GetMethodID(cls, "bluetooth_message_send_current", "()V");
    if (!g_bluetooth_message_send_current)
        goto fail;

    g_is_bluetooth_message = env->GetMethodID(cls, "is_bluetooth_message", "()Z");
    if (!g_is_bluetooth_message)
        goto fail;

    g_bluetooth_message_read_int = env->GetMethodID(cls, "bluetooth_message_read_int", "()I");
    if (!g_bluetooth_message_read_int)
        goto fail;

    g_bluetooth_message_read_float = env->GetMethodID(cls, "bluetooth_message_read_float", "()F");
    if (!g_bluetooth_message_read_float)
        goto fail;

    g_bluetooth_message_discard_current = env->GetMethodID(cls, "bluetooth_message_discard_current", "()V");
    if (!g_bluetooth_message_discard_current)
        goto fail;

    g_bluetooth_show_wrong_version_dialog = env->GetMethodID(cls, "bluetooth_show_wrong_version_dialog", "()V");
    if (!g_bluetooth_show_wrong_version_dialog)
        goto fail;



    IwTrace(BLUETOOTH, ("BLUETOOTH init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(bluetooth, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void bluetoothTerminate_platform()
{
    // Add any platform-specific termination code here
}

bool init_bluetooth_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_init_bluetooth);
}

void enable_bluetooth_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_enable_bluetooth);
}

void disable_bluetooth_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_disable_bluetooth);
}

bool is_bluetooth_enabled_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_is_bluetooth_enabled);
}

void bluetooth_close_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_close);
}

void bluetooth_enable_discoverability_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_enable_discoverability);
}

bool bluetooth_is_discovering_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_bluetooth_is_discovering);
}

void bluetooth_setup_client_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_setup_client);
}

bool is_bluetooth_connected_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_is_bluetooth_connected);
}

void bluetooth_message_start_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_message_start);
}

void bluetooth_message_write_float_platform(const char* str_value)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring str_value_jstr = env->NewStringUTF(str_value);
    env->CallVoidMethod(g_Obj, g_bluetooth_message_write_float, str_value_jstr);
}

void bluetooth_message_write_int_platform(int value)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_message_write_int, value);
}

void bluetooth_message_send_current_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_message_send_current);
}

bool is_bluetooth_message_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_is_bluetooth_message);
}

int bluetooth_message_read_int_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_bluetooth_message_read_int);
}

float bluetooth_message_read_float_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (float)env->CallFloatMethod(g_Obj, g_bluetooth_message_read_float);
}

void bluetooth_message_discard_current_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_message_discard_current);
}

void bluetooth_show_wrong_version_dialog_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_bluetooth_show_wrong_version_dialog);
}
