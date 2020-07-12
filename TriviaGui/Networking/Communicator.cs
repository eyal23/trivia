using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using TriviaFront.Classes.Networking;
using Newtonsoft.Json;
using System.Windows;
using System.Runtime.Serialization.Formatters;
using System.Threading;
using System.Windows.Threading; // For Dispatcher.

using System.Collections.Generic;

using System.Windows.Interop;

namespace TriviaFront.Classes.Networking
{
    internal class Communicator
    {
        public delegate void OnResponse(Response response);

        private delegate void ListeningDelegate();

        public Dictionary<int, OnResponse> actions;

        public string UserName { get; set; }

        private static Communicator instance = null;

        private string ip = Defs.Ip;

        private IPHostEntry hostEntry = null;
        private Socket socket = null;

        private DispatcherOperation LastInvoke;
        private byte LastbyteCode;

        private Communicator()
        {
            // Get host related information.
            hostEntry = Dns.GetHostEntry(this.ip);

            actions = new Dictionary<int, OnResponse>();

            // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid
            // an exception that occurs when the host IP Address is not compatible with the address family
            // (typical in the IPv6 case).
            foreach (IPAddress address in hostEntry.AddressList)
            {
                IPEndPoint ipe = new IPEndPoint(address, Defs.Port);

                Socket tempSocket = new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                tempSocket.Connect(ipe);

                if (tempSocket.Connected)
                {
                    socket = tempSocket;
                    break;
                }

                else
                    continue;
            }

            ListeningDelegate fetcher = new ListeningDelegate(this.StartLising);

            fetcher.BeginInvoke(null, null);
        }

        public void AddEvent(Enum code, OnResponse func)
        {
            this.actions[Convert.ToInt32(code)] = func;
        }

        public void RemoveEvent(Enum code)
        {
            this.actions.Remove(Convert.ToInt32(code));
        }

        public static Communicator Instance
        {
            get
            {
                if (instance == null)
                    instance = new Communicator();

                return instance;
            }
        }

        private byte[] MsgToByte(string msg, byte code)
        {
            byte[] bytesCode = new byte[1];
            bytesCode[0] = code;
            byte[] byteSize = BitConverter.GetBytes((int)msg.Length);
            byte[] byteMsg = Encoding.ASCII.GetBytes(msg);

            byte[] rv = Combine(bytesCode, byteSize, byteMsg);

            return rv;
        }

        private static byte[] Combine(params byte[][] arrays)
        {
            byte[] rv = new byte[arrays.Sum(a => a.Length)];
            int offset = 0;
            foreach (byte[] array in arrays)
            {
                System.Buffer.BlockCopy(array, 0, rv, offset, array.Length);
                offset += array.Length;
            }
            return rv;
        }

        public byte[] Receive()
        {
            int recv;
            byte[] data = new byte[1024];
            byte[] returnMsg = new byte[0];
            while (true)
            {
                recv = socket.Receive(data);
                returnMsg = Combine(returnMsg, data);
                if (recv != 1024) break;
            }

            return returnMsg;
        }

        private void StartLising()
        {
            while (true)
            {
                byte[] retrunBytes;
                retrunBytes = Receive();
                var res = new Response(retrunBytes);
                OnResponse function = null;
                try
                {
                    if (this.actions.TryGetValue(res.code, out function))
                    {
                        var a = Application.Current.Dispatcher;

                        if (this.LastbyteCode == res.code)
                        {
                            this.LastInvoke.Wait();
                        }

                        this.LastbyteCode = res.code;
                        this.LastInvoke = a.BeginInvoke(
                        System.Windows.Threading.DispatcherPriority.Normal,
                        function,
                        res);
                    }
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.Message);
                }
            }
        }

        public void Send(object msg, byte code)
        {
            socket.Send(MsgToByte(JsonConvert.SerializeObject(msg), code));
        }

        public bool TryToSend(Requests.IRequest msg)
        {
            try
            {
                Send(msg, msg.Code);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}