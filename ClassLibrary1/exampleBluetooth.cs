using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using InTheHand.Net.Sockets;
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Windows.Forms;
using System.Net.Sockets;
using System.Diagnostics;
using System.Threading;

namespace dConsoleApp
{
    static class Program
    {
        // My BT USB adapter
        private static BluetoothEndPoint EP = new BluetoothEndPoint(BluetoothAddress.Parse("00:02:72:CD:9A:33"), BluetoothService.BluetoothBase);
        private static BluetoothClient BC = new BluetoothClient(EP);

        // The BT device that would connect
        private static BluetoothDeviceInfo BTDevice = new BluetoothDeviceInfo(BluetoothAddress.Parse("94:21:97:60:07:C0"));

        private static NetworkStream stream = null;

        static void Main(string[] args)
        {
            if (BluetoothSecurity.PairRequest(BTDevice.DeviceAddress, MY_PAIRING_CODE))
            {
                Console.WriteLine("PairRequest: OK");

                if (BTDevice.Authenticated)
                {
                    Console.WriteLine("Authenticated: OK");

                    BC.SetPin(MY_PAIRING_CODE);

                    BC.BeginConnect(BTDevice.DeviceAddress, BluetoothService.SerialPort, new AsyncCallback(Connect), BTDevice);
                }
                else
                {
                    Console.WriteLine("Authenticated: No");
                }
            }
            else
            {
                Console.WriteLine("PairRequest: No");
            }

            Console.ReadLine();
        }

    private static void Connect(IAsyncResult result)
    {
        if (result.IsCompleted)
        {
            // client is connected now :)
            Console.WriteLine(BC.Connected);
            stream = BC.GetStream();

            if (stream.CanRead)
            {
                byte[] myReadBuffer = new byte[1024];
                StringBuilder myCompleteMessage = new StringBuilder();
                int numberOfBytesRead = 0;

                // Incoming message may be larger than the buffer size.
                do
                {
                    numberOfBytesRead = stream.Read(myReadBuffer, 0, myReadBuffer.Length);

                    myCompleteMessage.AppendFormat("{0}", Encoding.ASCII.GetString(myReadBuffer, 0, numberOfBytesRead));
                }
                while (stream.DataAvailable);

                // Print out the received message to the console.
                Console.WriteLine("You received the following message : " + myCompleteMessage);
            }
            else
            {
                Console.WriteLine("Sorry.  You cannot read from this NetworkStream.");
            }

            Console.ReadLine();
        }
    }
}
