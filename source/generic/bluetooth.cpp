/*
Generic implementation of the bluetooth extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "bluetooth_internal.h"
s3eResult bluetoothInit()
{
    //Add any generic initialisation code here
    return bluetoothInit_platform();
}

void bluetoothTerminate()
{
    //Add any generic termination code here
    bluetoothTerminate_platform();
}

bool init_bluetooth()
{
	return init_bluetooth_platform();
}

void enable_bluetooth()
{
	enable_bluetooth_platform();
}

void disable_bluetooth()
{
	disable_bluetooth_platform();
}

bool is_bluetooth_enabled()
{
	return is_bluetooth_enabled_platform();
}

void bluetooth_close()
{
	bluetooth_close_platform();
}

void bluetooth_enable_discoverability()
{
	bluetooth_enable_discoverability_platform();
}

bool bluetooth_is_discovering()
{
	return bluetooth_is_discovering_platform();
}

void bluetooth_setup_client()
{
	bluetooth_setup_client_platform();
}

bool is_bluetooth_connected()
{
	return is_bluetooth_connected_platform();
}

void bluetooth_message_start()
{
	bluetooth_message_start_platform();
}

void bluetooth_message_write_float(const char* str_value)
{
	bluetooth_message_write_float_platform(str_value);
}

void bluetooth_message_write_int(int value)
{
	bluetooth_message_write_int_platform(value);
}

void bluetooth_message_send_current()
{
	bluetooth_message_send_current_platform();
}

bool is_bluetooth_message()
{
	return is_bluetooth_message_platform();
}

int bluetooth_message_read_int()
{
	return bluetooth_message_read_int_platform();
}

float bluetooth_message_read_float()
{
	return bluetooth_message_read_float_platform();
}

void bluetooth_message_discard_current()
{
	bluetooth_message_discard_current_platform();
}

void bluetooth_show_wrong_version_dialog()
{
	bluetooth_show_wrong_version_dialog_platform();
}
