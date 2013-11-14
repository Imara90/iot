/******************************************************************************
 *  This is a pseudo code to facilitatite a wireless power transfer protocol
 *  The original code is added to the appendix
 *****************************************************************************/

// Initialize all variables to store inputs
int voltage = 0, readBtn = 0, show = 0;

// Initialize pins for Arduino Pro mini
int Battery = A0;       // Analog pin to read battery voltage
int chargeBtn = 8;      // Digital pin for the charge Button
int showDetect = 9;     // Digital pin for detecting a show
int LEDr = 10;          // Digital PWN pin for red LED
int LEDg = 11;          // Digital PWM pin for green LED
int LEDb = 6;           // Digital PWM pin for blue LED

// Declare the states as an enum variable
enum StateVariable{
  maximum, idle, charging, running, starving, dead  
} state;

// Define and declare all the V limits to compare with analog voltage input 10 bits
const int Vmax, Vfull, Vstarving;

// Initialize the system
void setup(){
  // Declare the battery energy level pin, charge button and show as an input
  // declare RGB pins as output
  
  // Initialize the state as idle and show as false
  state = idle;
  show = LOW;
}


// Functional part of the system
void loop(){
  // Read all input values at the start of the loop and debounce button
  voltage = analogRead(Battery);  
  reading = digitalRead(chargeBtn);  
  show = digitalRead(showDetect);
  
  // A switch case based on the state of the system
  // In each state perform concurring tasks and check is state translation required
  switch (state) {
  case idle:
    // no light turned on
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
    // Green light
    if (voltage < Vmax){
      state = idle; 
    } 
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
    // Blink orange light
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
    // Red light
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
    // If voltage > Vstarving, IC will startup as idle and switch to starving
    break; 
  }
  // Small delay to accomodate stability                              
}
