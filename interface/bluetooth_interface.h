/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
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
