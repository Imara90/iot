/******************************************************************************
 *  This is a program to facilitatite a wireless power transfer protocol
 *  for the IOT project on TU Delft by M. Wasif & I.C.T.M. Speek
 *
 *****************************************************************************/
// Variable to save battery and pin declaration
int voltage = 0;      // variable to read voltage level battery into
int Battery = A0;     // Analog pin to read battery voltage

// RGB pins
int LEDr = 7;        // Digital pin for r from RGB LED
int LEDg = 8;        // Digital pin for g from RGB LED
int LEDb = 9;        // Digital pin for b from RGB LED

// Declare the states as an enum
enum StateVariable{
  maximum, 
  idle, 
  charging, 
  running, 
  starving, 
  dead  
};

// Map all the V variables to the analog 2^10
#define Vmap / 5 * 1023;
// Declaration of Vmax, Vfull, Vstarving and Vdead
// Varies between 0 and 5 V, but should map between 0 and 1023 for Analog
// Value might be slightly off as int rounds off
const int Vmax = 5.2 Vmap;
const int Vfull = 4.5 Vmap;
const int Vstarving = 4 Vmap;
const int Vdead = 3 Vmap;

// Initialize the state as idle
StateVariable state = idle;

// Initialize the system
void setup(){
  // set serial monitor at 115200 boudrate
  Serial.begin(115200);
 
  // Declare the battery energy level pin as input
  pinMode(Battery, INPUT);

  // declare RGB pins as output
  pinMode(LEDr, OUTPUT);
  pinMode(LEDg, OUTPUT);
  pinMode(LEDb, OUTPUT);
}

// Functional part of the system
void loop(){
  // Reads the energy level of the battery and saves it 
  // at the start of the program loop
  voltage = analogRead(Battery);                  

  // A switch case based on the state of the system
  switch (state) {
  case idle:        
    Serial.println("Idle");

    break;
  case maximum:    
    Serial.println("Maximum");
    digitalWrite(LEDg, HIGH);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, LOW);
    if ( 
    // do something
    break;
  case charging:
    Serial.println("Charging");
    // do something
    break;
  case running:
    Serial.println("Running");
    // do something
    break;
  case starving:
    Serial.println("Starving");
    // do something
    break;
  case dead:
    Serial.println("Dead");
    // something
    break; 
  }

  // Small delay to accomodate stability
  delay(1);                                    
}



