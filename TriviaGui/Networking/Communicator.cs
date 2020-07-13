using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using TriviaFront.Classes.Networking;
using Newtonsoft.Json;
using Newtonsoft.Json.Bson;
using System.Windows;
using System.Runtime.Serialization.Formatters;
using System.Threading;
using System.IO;
using System.Windows.Threading;
using System.Windows.Interop;

namespace TriviaFront.Classes.Networking
{
    class Communicator
    {
        private TcpClient client = new TcpClient();

        public Communicator()
        {
            StreamReader clientIn;
            StreamWriter clientOut;

            client.BeginConnect(Defs.Ip, Defs.Port, null, null);

            if (client.Connected)
            {
                clientIn = new StreamReader(client.GetStream());
                clientOut = new StreamWriter(client.GetStream());

                clientOut.AutoFlush = true;
            }
        }

        private byte[] constructRequest<Request>(Request request, byte code)
        {
            using (MemoryStream ms = new MemoryStream())
            using (BsonDataWriter datawriter = new BsonDataWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(datawriter, request);
                byte[] bson = ms.ToArray();

                byte[] dataSize = BitConverter.GetBytes(bson.Length);

                byte[] bsonRequest = new byte[5 + bson.Length];

                bsonRequest[0] = code;
                System.Buffer.BlockCopy(dataSize, 0, bsonRequest, 1, 4);
                System.Buffer.BlockCopy(bson, 0, bsonRequest, 5, bson.Length);

                return bsonRequest;
            }
        }

        private byte[] constructRequest(byte code)
        {
            byte[] bsonRequest = new byte[] { code, 0, 0, 0, 0 };

            return bsonRequest;
        }

        private Response parseResponse<Response>(byte[] bsonResponse)
        {
            using (MemoryStream ms = new MemoryStream(bsonResponse.Skip(5).Take(bsonResponse.Length - 5).ToArray()))
            using (BsonDataReader reader = new BsonDataReader(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                return serializer.Deserialize<Response>(reader);
            }
        }

        private byte[] sendAndRecive(byte[] bsonRequest)
        {
            client.GetStream().Write(bsonRequest, 0, bsonRequest.Length);
            byte[] bsonResponse = new byte[client.ReceiveBufferSize];
            client.GetStream().Read(bsonResponse, 0, client.ReceiveBufferSize);

            return bsonResponse;
        }

        public Response submitRequest<Request, Response>(Request request, int code)
        {
            return parseResponse<Response>(sendAndRecive(constructRequest<Request>(request, (byte)code)));
        }

        public Response submitRequest<Response>(int code)
        {
            return parseResponse<Response>(sendAndRecive(constructRequest((byte)code)));
        }
    }
}