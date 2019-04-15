using System;
using System.IO;
using System.IO.Ports;
using System.Threading;
using System.Threading.Tasks;

namespace SerialServer
{
    class Program
    {
        static void Main(string[] args)
        {
           
            var connector = new Connector("COM8");
            connector.Connect();
            Console.WriteLine("Finished");
            Console.ReadLine();
        }

    }
}
