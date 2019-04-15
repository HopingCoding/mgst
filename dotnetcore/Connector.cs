using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;
using System.Threading;

namespace SerialServer
{
    class Connector
    {
        bool _connected = false;
        SerialPort _serialPort;

        public Connector(string comport)
        {
            _serialPort = new SerialPort
            {
                PortName = comport,
                BaudRate = 9600
            };
        }


        public void Connect()
        {
            Console.WriteLine($"Connecting on {_serialPort.PortName}");
            while (!_connected)
            {
                try
                {
                    _serialPort.Open();
                    Console.WriteLine("Connected!");
                    _connected = true;
                }
                catch (Exception ex)
                {
                    Thread.Sleep(1);
                }
            }
            Run();
        }


        public void Run()
        {
            while (_connected)
            {
                try
                {
                    int theByte = _serialPort.ReadByte();
                    Console.WriteLine(theByte);

                    Button button = (Button)(theByte % 8);
                    ButtonMode buttonMode = theByte < 8 ? ButtonMode.Up : ButtonMode.Down;

                    Console.WriteLine($"{button} = {buttonMode}");

                    SetLamp(button, LampMode.On);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Disconnected");
                    _connected = false;
                    Thread.Sleep(1);
                }
            }
            Connect();
        }

        public void SetLamp(Button lamp, LampMode lampmode)
        {
            byte data = (byte) ((int)lampmode + (int)lamp * 5);

            byte[] b = new byte[] {data};

            _serialPort.Write(b, 0, b.Length);
            Console.WriteLine($"SetLamp {lamp} {lampmode}   = {data}");
        }

    }
}
