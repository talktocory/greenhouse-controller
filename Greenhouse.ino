#include <Time.h>
#include <TimeLib.h>
#include <MenuBackend.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#include <IRremoteInt.h>

// ********************************************************
//                         Constants
// ********************************************************
int RECV_PIN = 10; // IR receiver pin
const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

// ********************************************************
//                      Global Variables
// ********************************************************
// greenhouse variables
float tempSet, tempAct, humSet, humAct;
int illumHoursOn, illumHoursOff;
int waterMinOn, waterMinOff;
unsigned long lastDisplayUpdate;
unsigned long pctime;
String buttonPressed;
  
// initialize IR receiver
IRrecv irrecv(RECV_PIN);
decode_results irMessage;

// initialize the lcd 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ********************************************************
//                           Setup
// ********************************************************
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  
  // start the ir receiver
  irrecv.enableIRIn(); 

  // start the serial monitor
  Serial.begin(9600);

  // Initialize the clock
  setTime(DEFAULT_TIME);
}

void loop() {

  buttonPressed = waitForInput();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Button Pressed:");
  lcd.setCursor(0,1);
  lcd.print(buttonPressed);
}

