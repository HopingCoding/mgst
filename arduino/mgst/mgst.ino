static const int _buttonCount = 8;
static const int _lampModeCount = 5;

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
};
enum ButtonMode 
{
  Down = 0,
  Up = 1
};
enum LampMode
{
  Off = 0,
  On = 1,
  BlinkSlow = 2,
  BlinkMedium = 3,
  BlinkFast = 4
};

boolean buttonState[_buttonCount];
LampMode lampState[_buttonCount];

int button2ButtonPin(const Button button)
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

int button2LedPin(const Button button)
{
  return button + 2;
}

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < _buttonCount; i++)
  {
    buttonState[i] = Up;
    lampState[i] = Off;

    const int ledPin = button2LedPin(i);
    pinMode(ledPin, OUTPUT);

    const int buttonPin = button2ButtonPin(i);
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
    const byte b = Serial.read();
    if (b >= 0 && b <_buttonCount * _lampModeCount)
    {
      const Button button = b / _lampModeCount;
      const LampMode lampMode = b % _lampModeCount;
      lampState[button] = lampMode;
    }
  }
}

void checkButtons()
{
  for (int i = 0; i < _buttonCount; i++)
  {
    const int sensorValue = digitalRead(button2ButtonPin(i));
    const ButtonMode buttonMode = sensorValue == HIGH ? Down : Up;

    if (buttonState[i] != buttonMode)
    {
      buttonState[i] = buttonMode;
      const byte b = buttonMode == Down ? i : i + 8;
      Serial.write(b);
    }
  }
}

void applyLamps()
{
  const bool blinkSlow = millis() % 1000 < 500;
  const bool blinkMedium = millis() % 500 < 250;
  const bool blinkFast = millis() % 250 < 125;

  for (int i = 0; i < _buttonCount; i++)
  {
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

    const int pin = button2LedPin(i);
    digitalWrite(pin, on);
  }
}
