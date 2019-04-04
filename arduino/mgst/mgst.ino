
#define LED_PIN 2

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

 Button [] buttons;
 
// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

}

int button2led(Button button)
{
  return button+2;
}

// Add the main program code into the continuous loop() function
void loop()
{
  checkSerial();

  checkButtons();


//  digitalWrite(LED_PIN, HIGH);
//  Serial.write("on\n");
//  delay(400);
//
//  digitalWrite(LED_PIN, LOW);
//  Serial.write("off\n");
//  delay(400);
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
       int led = button2led(button);
       digitalWrite(LED_PIN, HIGH);
    }
}

void checkButtons()
{

}