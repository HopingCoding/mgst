const int _buttonCount = 8;

enum Button {
  Start = 0,
  Autostart = 1,
  SelectGame = 2,
  Info = 3,
  Red = 4,
  Black = 5,
  Payout = 6,
  Service = 7
};

enum LampMode
{
  Off = 0,
  On = 1,
  BlinkSlow = 2,
  BlinkMedium = 3,
  BlinkFast = 4
};

byte _firstByte = -1;

boolean buttonState[_buttonCount];
LampMode lampState[_buttonCount];

int button2ButtonPin(Button button)
{
  switch (button)
  {
    case Start: return A4;
    case Autostart: return A3;
    case SelectGame: return A2;
    case Info: return A1;
    case Red: return A0;
    case Black: return 10;
    case Payout: return 11;
    case Service: return 12;
  }
}

int button2LedPin(Button button)
{
  return button + 2;
}

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < _buttonCount; i++)
  {
    buttonState[i] = false;
    lampState[i] = Off;

    int ledPin = button2LedPin(i);
    pinMode(ledPin, OUTPUT);

    int buttonPin = button2ButtonPin(i);
    pinMode(buttonPin, INPUT_PULLUP);
  }
}

void loop()
{
  checkSerial();
  checkButtons();
  applyLamps();
}

void checkSerial()
{
  while (Serial.available())
  {
    byte b = Serial.read();
    processByte(b);
  }
}

void processByte(byte b)
{
  if (_firstByte != -1)
  {
    if (b == 'l')
    {

    }
    Button button = _firstByte;
    int led = button2LedPin(button);
  }
}

void checkButtons()
{
  for (int i = 0; i < _buttonCount; i++)
  {
    int sensorValue = digitalRead(button2ButtonPin(i));
    boolean down = sensorValue == HIGH;
    if (buttonState[i] != down)
    {
      buttonState[i] = down;
      Serial.write(i);
      lampState[i] = On;
    }
  }
}

void applyLamps()
{
  bool blinkSlow = millis() % 1000 > 0;
  bool blinkMedium = millis() % 1000 > 0;
  bool blinkFast = millis() % 1000 > 0;

  for (int i = 0; i < _buttonCount; i++)
  {
    int pin = button2LedPin(i);
    bool on = LOW;
    switch (lampState[i])
    {
      case On:
        on = HIGH;
        break;
      case Off:
        on = LOW;
        break;
      case BlinkSlow:
        on = blinkSlow;
        break;
      case BlinkMedium:
        on = blinkMedium;
        break;
      case BlinkFast:
        on = blinkFast;
        break;
    }

    digitalWrite(pin, on);
  }
}
