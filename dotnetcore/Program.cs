using System;
using System.IO;
using System.IO.Ports;
using System.Management;
using System.Threading;
using System.Threading.Tasks;

namespace SerialServer
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] ports = SerialPort.GetPortNames();

            Console.WriteLine("Serial ports connected:");
            foreach (string port in ports)
            {
                Console.WriteLine(port);
            }

            if (ports.Length > 0)
            {
                var connector = new Connector();
                connector.Connect(ports[0]);
                Console.WriteLine("Finished");
                Console.ReadLine();
            }
        }

    }
}
