/******************************************************************************
 *  This is a program to facilitatite a wireless power transfer protocol
 *  for the IOT project on TU Delft by M. Wasif & I.C.T.M. Speek
 *****************************************************************************/
 
// Variable to save battery and pin declaration
int voltage = 0;      // variable to read voltage level battery into
int Battery = A0;     // Analog pin to read battery voltage

// Variables for debouncing the button
int chargeBtn = 10;          // Digital pin for the charge Button
int reading = 0;             // Variable to store reading Button
int buttonState;             // Current reading of the Button
int lastButtonState = LOW;   // Previous reading of the Button

// Time measured in miliseconds to debounce the buttons
long lastDebounceTime = 0;   // Last time the the Button was pressed
long debounceDelay = 50;     // The Debounce time

// Variables for detecting the show
int showDetect = 11;         // Digital pin upon which the show is detected
int show;                // Boolean to save the show state in

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
} 
state;

// Map all the V variables to the analog 2^10
#define Vmap / 3.2 * 1023
// Declaration of Vmax, Vfull, Vstarving and Vdead
// Varies between 0 and 5 V, but should map between 0 and 1023 for Analog
// Value might be slightly off as int rounds off
const int Vmax = 3.2 Vmap;
const int Vfull = 3.0 Vmap;
const int Vstarving = 2.4 Vmap;
const int Vdead = 2.2 Vmap;

// Initialize the system
void setup(){
  // set serial monitor at 115200 boudrate
  Serial.begin(115200);
  // Declare the battery energy level pin as (analog) input
  pinMode(Battery, INPUT);
  // Declare the charge button as input
  pinMode(chargeBtn, INPUT);  
  // Declare the show as an input value
  pinMode(showDetect, INPUT);
  // declare RGB pins as output
  pinMode(LEDr, OUTPUT);
  pinMode(LEDg, OUTPUT);
  pinMode(LEDb, OUTPUT);
  // Initialize the state as idle and show as false
  // as you receive a wristband at the entrance of the festival
  state = idle;
  show = LOW;
}

// Functional part of the system
void loop(){
  // Reads the energy level and buttonstate of the battery and saves it 
  // at the start of the program loop
  voltage = analogRead(Battery);  
  reading = digitalRead(chargeBtn);  
  show = digitalRead(showDetect);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;
  }

  // A switch case based on the state of the system
  switch (state) {
  case idle:
    // Perform idle tasks  
    Serial.println("Idle");
    digitalWrite(LEDg, LOW);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, LOW);
    // Check if state translation is necessary
    if (voltage >= Vmax){
      state = maximum;
      break; 
    }
    else if (buttonState == HIGH){
      state = charging;          
      break;    
    }
    else if (show == HIGH){
      state = running;
      break;
    }
    else if (voltage < Vfull){
      state = starving;
      break;
    }
    break;
  case maximum:    
    // Perform maximum tasks
    Serial.println("Maximum");
    digitalWrite(LEDg, HIGH);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, LOW);
    // Check if state translation is necessary
    if (voltage < Vmax){
      state = idle; 
    } 
    // if user wants to charge, break state and charge
    else if (buttonState == HIGH){
      state = charging;          
      break;    
    }
    else if (show == HIGH){
      state = running;
      break; 
    }
    break;
  case charging:
    // Perform charging tasks
    Serial.println("Charging");
    digitalWrite(LEDg, LOW);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, HIGH);
    delay(500);
    digitalWrite(LEDg, LOW);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, LOW);
    delay(500);   
    // Check if state translation is necessary
    if (buttonState == LOW){
      state = idle;
      break; 
    }
    else if (voltage < Vfull){
      state = starving;
      break;  
    }
    break;
  case running:
    // Perform running tasks
    Serial.println("Running");
    digitalWrite(LEDg, LOW);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, LOW);
    // Check if state translation is necessary
    if (show == LOW){
      state = idle;
      break; 
    }
    else if (voltage < Vfull){
      state = starving;
      break; 
    }
    break;
  case starving:
    // Perform starving tasks
    Serial.println("Starving");
    digitalWrite(LEDg, LOW);
    digitalWrite(LEDr, HIGH);
    digitalWrite(LEDb, LOW);
    // Check if state translation is necessary
    if (voltage >= Vfull){
      state = idle;
      break; 
    }
    else if (voltage < Vstarving){
      // not necessary in actual implementation
      // the IC will not receive any power anymore by now
      state = dead; 
      break; 
    }
    break;
  case dead:
    // Play Dead - not necessary as IC is not powered
    Serial.println("Dead");
    digitalWrite(LEDg, LOW);
    digitalWrite(LEDr, LOW);
    digitalWrite(LEDb, LOW);    
    // Check if state translation is necessary
    if (voltage >= Vstarving){
      state = starving;
      break; 
    }
    break; 
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;  

  // Small delay to accomodate stability
  delay(1);                                    
}










