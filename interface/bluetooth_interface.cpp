/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"
#include "s3eDevice.h"


#include "bluetooth.h"


#ifndef S3E_EXT_SKIP_LOADER_CALL_LOCK
// For MIPs (and WP8) platform we do not have asm code for stack switching
// implemented. So we make LoaderCallStart call manually to set GlobalLock
#if defined __mips || defined S3E_ANDROID_X86 || (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
#define LOADER_CALL_LOCK
#endif
#endif

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef       bool(*init_bluetooth_t)();
typedef       void(*enable_bluetooth_t)();
typedef       void(*disable_bluetooth_t)();
typedef       bool(*is_bluetooth_enabled_t)();
typedef       void(*bluetooth_close_t)();
typedef       void(*bluetooth_enable_discoverability_t)();
typedef       bool(*bluetooth_is_discovering_t)();
typedef       void(*bluetooth_setup_client_t)();
typedef       bool(*is_bluetooth_connected_t)();
typedef       void(*bluetooth_message_start_t)();
typedef       void(*bluetooth_message_write_float_t)(const char* str_value);
typedef       void(*bluetooth_message_write_int_t)(int value);
typedef       void(*bluetooth_message_send_current_t)();
typedef       bool(*is_bluetooth_message_t)();
typedef        int(*bluetooth_message_read_int_t)();
typedef      float(*bluetooth_message_read_float_t)();
typedef       void(*bluetooth_message_discard_current_t)();
typedef       void(*bluetooth_show_wrong_version_dialog_t)();

/**
 * struct that gets filled in by bluetoothRegister
 */
typedef struct bluetoothFuncs
{
    init_bluetooth_t m_init_bluetooth;
    enable_bluetooth_t m_enable_bluetooth;
    disable_bluetooth_t m_disable_bluetooth;
    is_bluetooth_enabled_t m_is_bluetooth_enabled;
    bluetooth_close_t m_bluetooth_close;
    bluetooth_enable_discoverability_t m_bluetooth_enable_discoverability;
    bluetooth_is_discovering_t m_bluetooth_is_discovering;
    bluetooth_setup_client_t m_bluetooth_setup_client;
    is_bluetooth_connected_t m_is_bluetooth_connected;
    bluetooth_message_start_t m_bluetooth_message_start;
    bluetooth_message_write_float_t m_bluetooth_message_write_float;
    bluetooth_message_write_int_t m_bluetooth_message_write_int;
    bluetooth_message_send_current_t m_bluetooth_message_send_current;
    is_bluetooth_message_t m_is_bluetooth_message;
    bluetooth_message_read_int_t m_bluetooth_message_read_int;
    bluetooth_message_read_float_t m_bluetooth_message_read_float;
    bluetooth_message_discard_current_t m_bluetooth_message_discard_current;
    bluetooth_show_wrong_version_dialog_t m_bluetooth_show_wrong_version_dialog;
} bluetoothFuncs;

static bluetoothFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0x57ee47bb, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE,                 "error loading extension: bluetooth");

        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0x57ee47bb, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool bluetoothAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

bool init_bluetooth()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[0] func: init_bluetooth"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_init_bluetooth();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

void enable_bluetooth()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[1] func: enable_bluetooth"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_enable_bluetooth();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void disable_bluetooth()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[2] func: disable_bluetooth"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_disable_bluetooth();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

bool is_bluetooth_enabled()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[3] func: is_bluetooth_enabled"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_is_bluetooth_enabled();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

void bluetooth_close()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[4] func: bluetooth_close"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_close();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void bluetooth_enable_discoverability()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[5] func: bluetooth_enable_discoverability"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_enable_discoverability();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

bool bluetooth_is_discovering()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[6] func: bluetooth_is_discovering"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_bluetooth_is_discovering();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

void bluetooth_setup_client()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[7] func: bluetooth_setup_client"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_setup_client();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

bool is_bluetooth_connected()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[8] func: is_bluetooth_connected"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_is_bluetooth_connected();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

void bluetooth_message_start()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[9] func: bluetooth_message_start"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_message_start();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void bluetooth_message_write_float(const char* str_value)
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[10] func: bluetooth_message_write_float"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_message_write_float(str_value);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void bluetooth_message_write_int(int value)
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[11] func: bluetooth_message_write_int"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_message_write_int(value);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void bluetooth_message_send_current()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[12] func: bluetooth_message_send_current"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_message_send_current();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

bool is_bluetooth_message()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[13] func: is_bluetooth_message"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_is_bluetooth_message();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

int bluetooth_message_read_int()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[14] func: bluetooth_message_read_int"));

    if (!_extLoad())
        return 0;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    int ret = g_Ext.m_bluetooth_message_read_int();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

float bluetooth_message_read_float()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[15] func: bluetooth_message_read_float"));

    if (!_extLoad())
        return 0;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    float ret = g_Ext.m_bluetooth_message_read_float();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

void bluetooth_message_discard_current()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[16] func: bluetooth_message_discard_current"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_message_discard_current();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void bluetooth_show_wrong_version_dialog()
{
    IwTrace(BLUETOOTH_VERBOSE, ("calling bluetooth[17] func: bluetooth_show_wrong_version_dialog"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_bluetooth_show_wrong_version_dialog();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}
