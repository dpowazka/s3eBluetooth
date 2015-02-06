/*
java implementation of the bluetooth extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;
import java.util.UUID;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Collections;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.DialogInterface;
import android.app.AlertDialog;

class bluetooth
{
	private final static int REQUEST_ENABLE_BT = 1;
	private static UUID uuid = UUID.fromString("c63059d5-ae46-4d8d-9698-2d9caaa08aaf");
	
	// -------------------------------------------------------------------------------------------
	
	private class Client_Connect_Thread extends Thread {
		private final BluetoothDevice device;
		public Client_Connect_Thread(BluetoothDevice device) {
			this.device = device;
			try {
				socket = device.createRfcommSocketToServiceRecord(uuid);
			} catch (IOException e) {
				bluetooth_show_message("Bluetooth Error! createRfcommSocketToServiceRecord failed. Reason: " + e);
			}
		}

		public void run() {
			// Cancel discovery because it will slow down the connection
			bluetooth_adapter.cancelDiscovery();
			if(socket == null) return;
			
			// Connect the device through the socket. This will block
			// until it succeeds or throws an exception
			try {
				socket.connect();
				data_thread = new Data_Thread(socket);
				data_thread.start();
				//System.out.println("==============> Bluetooth Connected <===================");
			} catch (IOException e) {
				try {
					socket.close();
				} catch (IOException closeException) {
					closeException.printStackTrace();
				}
				
				String message = "Error: " + e;
				if(device != null) {
					message += " Device: "+device.getName();
				}
				bluetooth_show_message(message);
			}
		
			client_connect_thread = null;
		}

		/** Will cancel an in-progress connection, and close the socket */
		public void cancel() {
			try {
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	// -------------------------------------------------------------------------------------------
	
	private class Server_Connect_Thread extends Thread {
		private final BluetoothServerSocket mmServerSocket;
		private boolean running = true;
		
		public Server_Connect_Thread() {
			BluetoothServerSocket tmp = null;
			try {
				tmp = bluetooth_adapter.listenUsingRfcommWithServiceRecord("NAME", uuid);
			} catch (IOException e) {
				bluetooth_show_message("Bluetooth Error! listenUsingRfcommWithServiceRecord failed. Reason:" + e);
			}
			mmServerSocket = tmp;
		}

		public void exit() {
			running = false;
		}
		
		public void run() {
			// Keep listening until exception occurs or a socket is returned
			while (running) {
				try {
					socket = mmServerSocket.accept();
				} catch (IOException e) {
					bluetooth_show_message("Bluetooth Error! Accepting a connection failed. Reason:" + e);
					break;
				}

				// If a connection was accepted
				// Do work to manage the connection (in a separate thread)
				if (socket != null) {
					//System.out.println("=========> Bluetooth Connected as Server <===========");
					data_thread = new Data_Thread(socket);
					data_thread.start();
					try {
						mmServerSocket.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
					break;
				}
			}
			
			bluetooth.this.server_connect_thread = null;
		}

		/** Will cancel the listening socket, and cause the thread to finish */
		public void cancel() {
			try {
				mmServerSocket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	// -------------------------------------------------------------------------------------------
	
	private class Data_Thread extends Thread {
		private final BluetoothSocket socket;
		private final InputStream input;
		private final OutputStream output;
		private boolean running = true;
		private LinkedList<ByteArrayOutputStream> messages_to_send;
		private int read_message_number = 0;
		
		public Data_Thread(BluetoothSocket socket) {
			this.socket = socket;
			this.messages_to_send = new LinkedList<ByteArrayOutputStream>();
			InputStream tmpIn = null;
			OutputStream tmpOut = null;

			// Get the input and output streams, using temp objects because
			// member streams are final
			try {
				tmpIn = socket.getInputStream();
				tmpOut = socket.getOutputStream();
			} catch (IOException e) {
				running = false;
				bluetooth_show_message("Error! Could not establish streams. Reason: " + e);
			}

			input = tmpIn;
			output = tmpOut;
		}
		
		public void exit() {
			running = false;
		}

		
		private void read() throws java.io.IOException {
			if(input.available() <= 0) return;
			//TODO: for heavy load, like sending camera data, this needs to be fixed
			//as the messages never get bigger then 990 and get cut in the middle.
			//FIX - add END_OF_MESSAGE marker so ther read can cut reading on it 
			//and produce message for the game.
			ByteArrayOutputStream stream_buffer = new ByteArrayOutputStream();
			byte[] read_buffer = new byte[1024];
			while(input.available() > 0) {
				int bytes_read = input.read(read_buffer, 0, 1024);
				stream_buffer.write(read_buffer, 0, bytes_read);
			}
			//System.out.println("------Stream buffer size:*" + stream_buffer.size());
			ByteBuffer byte_buffer = ByteBuffer.wrap(stream_buffer.toByteArray(), 0, stream_buffer.size());
			messages.add(byte_buffer);
		}
		
		private void send() throws java.io.IOException {
			if(messages_to_send.isEmpty()) return;
			
			for(;;) {
				synchronized(messages_to_send) {
					if(messages_to_send.isEmpty()) break;
					ByteArrayOutputStream message = messages_to_send.poll();
					output.write(message.toByteArray());
				}
			}
			
			output.flush();
		}
		
		public void run() {
			// Keep listening to the InputStream until an exception occurs
			while (running || !messages_to_send.isEmpty()) {
				try {
					send();
					read();
					Thread.sleep(100);
				} catch (Exception e) {
					bluetooth_show_message("Error! Sending or Reading failed. Reason: " + e);
					cancel();
					break;
				}
			}
			
			try {
				socket.close();
			} catch(IOException e) {
				e.printStackTrace();
			}
		}

		public void write(ByteArrayOutputStream message) {
			synchronized(messages_to_send) {
				messages_to_send.add(message);
			}
		}
		
		/* Call this from the main activity to shutdown the connection */
		public void cancel() {
			try {
				socket.close();
			} catch (IOException e) {
				//pass
			}
		}
	}
	
	// -------------------------------------------------------------------------------------------
	
	private BroadcastReceiver client_receiver = null;

	class Bluetooth_Device_Found_Revicer extends BroadcastReceiver {
		private final ArrayList<BluetoothDevice> devices = new ArrayList<BluetoothDevice>();

		private void show_dialog() {
			final CharSequence[] items = new CharSequence[devices.size()];
            for(int i = 0; i < devices.size();i++) {
            	BluetoothDevice device = devices.get(i);
            	items[i] = device.getName();
            }

			final AlertDialog.Builder builder = new AlertDialog.Builder(LoaderActivity.m_Activity);
        	builder.setTitle("Detected bluetooth devices");
        	builder.setItems(items, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int item) {
                	BluetoothDevice device = devices.get(item);
                	connect(device);
            	}
        	});

        	
        	LoaderActivity.m_Activity.runOnUiThread(new Runnable(){
			public void run(){
				AlertDialog alert = builder.create();
        		alert.show();
				}
			});
		}

		private void connect(BluetoothDevice device) {
			client_connect_thread = new Client_Connect_Thread(device);
			client_connect_thread.start();
			try {
				LoaderActivity.m_Activity.unregisterReceiver(client_receiver);

			} catch(Exception e) {
				System.out.println(" " + e);
			}
			client_receiver = null;
		}

		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (BluetoothDevice.ACTION_FOUND.equals(action)) {
				BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				System.out.println("Device: " + device.getName() + " MAC: " + device.getAddress());
				devices.add(device);
			} else if(BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
				show_dialog();	
			}
		}
	};
	
	// ---------------------------------------------------------------------------------------------
	
    private BluetoothAdapter bluetooth_adapter = null;
	private BluetoothSocket socket = null;
	private Data_Thread data_thread = null;
	private Server_Connect_Thread server_connect_thread = null;
	private Client_Connect_Thread client_connect_thread = null;
	private ArrayList<ByteBuffer> messages;
	
    public boolean init_bluetooth()
    {
		messages = new ArrayList<ByteBuffer>();
		bluetooth_adapter = BluetoothAdapter.getDefaultAdapter();
        return bluetooth_adapter != null;
		
    }
	
    public void enable_bluetooth()
    {
		if(bluetooth_adapter != null && !bluetooth_adapter.isEnabled()) {
			//System.out.println("Warlings Bluetooth version: 1.0.0");
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			LoaderActivity.m_Activity.startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
		}
    }
	
    public void disable_bluetooth()
    {
        if (bluetooth_adapter != null && bluetooth_adapter.isEnabled()) {
			bluetooth_adapter.disable();
		}
    }
	
	
	public boolean is_bluetooth_enabled() {
		if(bluetooth_adapter != null) {
			return bluetooth_adapter.isEnabled();
		} else {
			return false;
		}
	}
	
	public void bluetooth_close()
    {
        if(server_connect_thread != null) {
			server_connect_thread.exit();
			server_connect_thread = null;
		}
		
		if(data_thread != null) {
			data_thread.exit();
			data_thread = null;
		}
		
		if(client_connect_thread != null) {
			client_connect_thread = null;
		}
    }
	
	public void bluetooth_enable_discoverability()
    {
		//System.out.println("=====> Setuping bluetooth server..");
		
        Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
		discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
		LoaderActivity.m_Activity.startActivity(discoverableIntent);
		server_connect_thread = new Server_Connect_Thread();
		server_connect_thread.start();
		messages.clear();
    }
	
	public boolean bluetooth_is_discovering()
    {
        if(bluetooth_adapter != null) {
			return bluetooth_adapter.getScanMode() == bluetooth_adapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE;
		} else {
			return false;
		}
    }
	
    public void bluetooth_setup_client()
    {
        //System.out.println("=====> Setuping bluetooth client..");

		IntentFilter filter = new IntentFilter();
		filter.addAction(BluetoothDevice.ACTION_FOUND);
		filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
		if(client_receiver != null) {
			LoaderActivity.m_Activity.unregisterReceiver(client_receiver);
		}
		client_receiver = new Bluetooth_Device_Found_Revicer();
		LoaderActivity.m_Activity.registerReceiver(client_receiver, filter);
		bluetooth_adapter.startDiscovery();
		messages.clear();
    }
	
	public boolean is_bluetooth_connected()
    {
        return data_thread != null;
    }
	
	
	ByteArrayOutputStream bos = null;
	public void bluetooth_message_start()
	{
        bos = new ByteArrayOutputStream();
    }
   
   
    public void bluetooth_message_write_float(String str_value)
    {
        float value = new Float(str_value);
		byte[] bytes = new byte[4];
		ByteBuffer.wrap(bytes).putFloat(value);
		try {
			bos.write(bytes);
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
   
   
	public void bluetooth_message_write_int(int value)
    {
        //System.out.println("INT "+value);
		byte[] bytes = new byte[4];
		ByteBuffer.wrap(bytes).putInt(value);
		try {
			bos.write(bytes);
		} catch (IOException e) {
			e.printStackTrace();
		}
    }

	
    public void bluetooth_message_send_current()
    {
		//System.out.println("SEND");
		data_thread.write(bos);
		bos = null;
    }
	
	
	public boolean is_bluetooth_message()
    {
        return messages.size()>0;
    }
	
    public int bluetooth_message_read_int()
    {
        int value = messages.get(0).getInt();
		if(!messages.get(0).hasRemaining()) {
			messages.remove(0);
		}
		//System.out.println("READ "+value);
		return value;
    }
	
    public float bluetooth_message_read_float()
    {
		float value = messages.get(0).getFloat();
		if(!messages.get(0).hasRemaining()) {
			messages.remove(0);
		}
		
		//System.out.println("READ "+value);
		return value;
    }
	
    public void bluetooth_message_discard_current()
    {
        //messages.remove(0);
    }
	
	public void bluetooth_show_wrong_version_dialog()
    {
     	
		final AlertDialog.Builder builder1 = new AlertDialog.Builder(LoaderActivity.m_Activity);
        builder1.setMessage("Warining! Different Warling VERSIONS. Please update to current one!");
		builder1.setCancelable(true);
		builder1.setPositiveButton("Yes",
			new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				dialog.cancel();
			}
		});
		
		
		LoaderActivity.m_Activity.runOnUiThread(new Runnable(){
			public void run(){
				AlertDialog alert = builder1.create();
				alert.show();
			}
		});
    }
	
	public void bluetooth_show_message(String message)
    {
     	
		final AlertDialog.Builder builder1 = new AlertDialog.Builder(LoaderActivity.m_Activity);
        builder1.setMessage(message);
		builder1.setCancelable(true);
		builder1.setPositiveButton("OK",
			new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				dialog.cancel();
			}
		});
		
		LoaderActivity.m_Activity.runOnUiThread(new Runnable(){
			public void run(){
				AlertDialog alert = builder1.create();
				alert.show();
			}
		});
    }
	
}
