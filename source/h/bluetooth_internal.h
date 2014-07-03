/*
 * Internal header for the bluetooth extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef BLUETOOTH_INTERNAL_H
#define BLUETOOTH_INTERNAL_H

#include "s3eTypes.h"
#include "bluetooth.h"
#include "bluetooth_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult bluetoothInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult bluetoothInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void bluetoothTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void bluetoothTerminate_platform();
bool init_bluetooth_platform();

void enable_bluetooth_platform();

void disable_bluetooth_platform();

bool is_bluetooth_enabled_platform();

void bluetooth_close_platform();

void bluetooth_enable_discoverability_platform();

bool bluetooth_is_discovering_platform();

void bluetooth_setup_client_platform();

bool is_bluetooth_connected_platform();

void bluetooth_message_start_platform();

void bluetooth_message_write_float_platform(const char* str_value);

void bluetooth_message_write_int_platform(int value);

void bluetooth_message_send_current_platform();

bool is_bluetooth_message_platform();

int bluetooth_message_read_int_platform();

float bluetooth_message_read_float_platform();

void bluetooth_message_discard_current_platform();

void bluetooth_show_wrong_version_dialog_platform();


#endif /* !BLUETOOTH_INTERNAL_H */