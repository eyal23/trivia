using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaFront.Classes.Networking
{
    internal class Response
    {
        public string json;
        public byte code;

        public Response(byte[] msg)
        {
            code = msg[0];
            int returnSize = BitConverter.ToInt32(msg, 1);
            json = System.Text.Encoding.Default.GetString(msg, 5, returnSize);
        }

        public DataType ToData<DataType>()
        {
            try
            {
                return JsonConvert.DeserializeObject<DataType>(json);
            }
            catch (Exception e)
            {
                return default(DataType);
            }
        }
    }
}