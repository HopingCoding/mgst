using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;
using System.Threading;

namespace SerialServer
{
    class Connector : IDisposable
    {
        bool _connected = false;
        SerialPort _serialPort;

        public Connector()
        {
        }


        public void Connect(string comPort)
        {
            _serialPort = new SerialPort
            {
                PortName = comPort,
                BaudRate = 9600
            };

            Console.WriteLine($"Connecting on {_serialPort.PortName}");
            while (!_connected)
            {
                try
                {
                    _serialPort.Open();
                    _serialPort.DiscardInBuffer();
                    _serialPort.DiscardOutBuffer();
                    Console.WriteLine("Connected!");
                    _connected = true;
                }
                catch (Exception)
                {
                    Thread.Sleep(1);
                }
            }
            Run();
        }

        public void Dispose()
        {
            _serialPort?.Dispose();
        }

        public void Run()
        {
            while (_connected)
            {
                try
                {
                    int theByte = _serialPort.ReadByte();
                    Console.Write($"Reading byte {theByte} . ");

                    Button button = (Button)(theByte % 8);
                    ButtonMode buttonMode = theByte < 8 ? ButtonMode.Up : ButtonMode.Down;

                    Console.Write($"{button} = {buttonMode}  . ");

                    SetLamp(button, buttonMode == ButtonMode.Down? LampMode.On : LampMode.Off);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Disconnected");
                    _connected = false;
                    Thread.Sleep(1);
                }
            }
            Connect(_serialPort.PortName);
        }

        public void SetLamp(Button lamp, LampMode lampmode)
        {
            byte data = (byte) ((int)lampmode + (int)lamp * 5);

            byte[] b = new byte[] {data};

            _serialPort.Write(b, 0, b.Length);
            Console.WriteLine($"SetLamp {lamp} {lampmode} = {data}");
        }

        

    }
}
