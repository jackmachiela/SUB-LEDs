 
//Simple Under-Bed LED strip lighting. Code by Jack Machiela, 2018 v1.0

int LDR_PIN = 0;                   // analog pin to which LDR sensor is connected (0 so it means A0)
int LDR_Value = 0;                 // a variable to store LDR values
bool Darkness;                     // current state of ambient light
int LightSensitivity = 200;        // This is the approx value of light detected LDR defined as "Darkness" or not (range 0-1024).

int LED_PIN = 5;                   // analog pin to which LED strip is connected
int Brightness;
int MaximumBrightness = 80;        // Don't burn the house down. 80 is ok without blinding lights in a totally dark room
int FadeSpeed = 50;                // make this higher to slow down. Beta was 35, which was a little too fast perhaps.
bool LightsOn;                     // current status of LEDs

int PIR_PIN = 12;                  // choose the input pin (for PIR sensor) (NB: 13=onboard LED)
int Movement;
 

//=================================================================================-- Setup begins --=====
void setup()
{
  Serial.begin(9600);
  
  pinMode(PIR_PIN, INPUT);                                // declare sensor as input

  pinMode(LED_PIN, OUTPUT);  
  analogWrite(LED_PIN, 0);                                // ensure LED strip is off

  LightsOn = false;

      FadeLightsOn();
      FadeLightsOff();

}
 
//=================================================================================-- Loop begins --=====
void loop() 
{
  Serial.print("[ "); 
  DarknessCheck();

  if (Darkness == true)
  {
    MovementCheck();

    if (Movement == true)
    {
      FadeLightsOn();

      while (Movement == true)
      {
        MovementCheck();
        delay(5000);
      }
      FadeLightsOff();
    }
  }
  Serial.println(" ]"); 
}
//=================================================================================-- Loop ends --=====
//=================================================================================-- DarknessCheck begins --=====

void DarknessCheck()
{
  LDR_Value = analogRead(LDR_PIN);                                       //reads the LDR’s value (range from 0 to 1024)
  Darkness = false;

  if (LDR_Value < LightSensitivity) {
    Darkness = true ;
  }

  Serial.print("LDR_Value = ");                                          // prints the LDR values to serial monitor
  Serial.print(LDR_Value);                                               // prints the LDR values to serial monitor
  Serial.print(" - Darkness = ");
  Serial.print(Darkness);

  Darkness = true;               // <------------ temp debug, remove for live code xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx DEBUG xxxxxxxxxxxxxxxxx

}
//=================================================================================-- MovementCheck begins --=====
void MovementCheck()
{
  Movement = digitalRead(PIR_PIN);                                        // read input value (0 or 1)

  Serial.print(" - Movement = ");                                         // prints the LDR values to serial monitor
  Serial.print(Movement);                                                 // prints the LDR values to serial monitor

}
//=================================================================================-- FadeLightsOn begins --=====
void FadeLightsOn()
{
  
  Serial.print(" - ON: LightsOn = ");                                     // prints the LightsOn values to serial monitor
  Serial.print(LightsOn);

  if (LightsOn == false)                                                  // Only turn them on if they're currently off
  {
    for (Brightness = 0; Brightness < MaximumBrightness; Brightness++)    // increase Brightness from 0 to Maximum Allowed Brightness
    { 
      analogWrite(LED_PIN, Brightness);
      delay(FadeSpeed);
    }
  }
  LightsOn = true;                                                        // Lights should now be on

}
//=================================================================================-- FadeLightsOff begins --=====
void FadeLightsOff()
{
  Serial.print(" - OFF: LightsOn = ");                                     // prints the LightsOn values to serial monitor
  Serial.print(LightsOn);                                                  // prints the LightsOn to serial monitor

  if (LightsOn == true)                                                    // Only turn them off if they're currently on
  {
    for  (Brightness = MaximumBrightness; Brightness > 0; Brightness--)    // decrease Brightness from Maximum Allowed Brightness to 0
    { 
      analogWrite(LED_PIN, Brightness);
      delay(FadeSpeed);
      analogWrite(LED_PIN, 0);
    }
  }
  LightsOn = false;                                                        // Lights should now be off

}


