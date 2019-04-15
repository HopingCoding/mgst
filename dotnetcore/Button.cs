using System;
using System.Collections.Generic;
using System.Text;

namespace SerialServer
{
    enum Button
    {
        Start = 0,
        Autostart = 1,
        SelectGame = 2,
        Info = 3,
        Red = 4,
        Black = 5,
        Payout = 6,
        Service = 7
    }
    enum ButtonMode
    {
        Down = 0,
        Up = 1
    }
    enum LampMode
    {
        Off = 0,
        On = 1,
        BlinkSlow = 2,
        BlinkMedium = 3,
        BlinkFast = 4
    }
}
