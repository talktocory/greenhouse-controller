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
int lightsOnHh, lightsOnMm, lightsOffHh, lightsOffMm;
int waterFrqHh, waterDurMm;
String buttonPressed;
String currentMenu;
  
// initialize IR receiver
IRrecv irrecv(RECV_PIN);
decode_results irMessage;

// initialize the lcd 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ********************************************************
//                     Utility Functions 
// ********************************************************
void printDigits(int digits){
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void printTime(time_t t){
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(":");
  printDigits(second());
}



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
  // Serial.begin(9600);

  // Initialize the clock
  setTime(DEFAULT_TIME);

  // Set system defaults
  tempSet = 22.0;
  tempAct = 22.11;
  humSet = 80.0;
  humAct = 80.51;
  lightsOnHh = 6;
  lightsOnMm = 0;
  lightsOffHh = 21;
  lightsOffMm = 00;
  waterFrqHh = 6;
  waterDurMm = 3;
  
  // Display the main menu
  currentMenu = "menu_0";
  
}

void loop() {

  // Refresh the display
  displayMenu(currentMenu); 
  
  // Give user 1 second to press button
  buttonPressed = waitForInput(1000);

  // If menu item was pressed then change
  // the menu.  Otherwise, redisplay the 
  // current menu.
  if (buttonPressed == "Mode"){
    if (currentMenu.startsWith("menu_0")){
      currentMenu = "menu_1";
    } 
    else if (currentMenu.equals("menu_1")){
      currentMenu = "menu_2";
    }
    else if (currentMenu.equals("menu_2")){
      currentMenu = "menu_3";
    }
    else if (currentMenu.equals("menu_3")){
      currentMenu = "menu_4";
    }
    else if (currentMenu.equals("menu_4")){
      currentMenu = "menu_5";
    }
    else if (currentMenu.equals("menu_5")){
      currentMenu = "menu_6";
    }
    else if (currentMenu.equals("menu_6")){
      currentMenu = "menu_7";
    }
    else if (currentMenu.equals("menu_7")){
      currentMenu = "menu_8";
    }
    else if (currentMenu.equals("menu_8")){
      currentMenu = "menu_9";
    }
    else if (currentMenu.equals("menu_9")){
      currentMenu = "menu_10";
    }
    else if (currentMenu.equals("menu_10")){
      currentMenu = "menu_0"; 
    }
  } else if (buttonPressed == "Volume Up"){
    if (currentMenu.equals("menu_1")){
      adjustTime(60*60); 
    }
    else if (currentMenu.equals("menu_2")){
      adjustTime(60); 
    }
    else if (currentMenu.equals("menu_3")){
      tempSet += 0.1;
    }
    else if (currentMenu.equals("menu_4")){
      humSet += 1.0;
    }
    else if (currentMenu.equals("menu_5")){
      lightsOffHh++;
    }
    else if (currentMenu.equals("menu_6")){
      lightsOnMm++; 
    }
    else if (currentMenu.equals("menu_7")){
      lightsOffHh++;
    }
    else if (currentMenu.equals("menu_8")){
      lightsOffMm++;
    }
    else if (currentMenu.equals("menu_9")){
      waterFrqHh++;
    }
    else if (currentMenu.equals("menu_10")){
      waterDurMm++;
    }
  } else if (buttonPressed == "Volume Down"){
    if (currentMenu.equals("menu_1")){
      adjustTime(-60*60); 
    }
    else if (currentMenu.equals("menu_2")){
      adjustTime(-60); 
    }
    else if (currentMenu.equals("menu_3")){
      tempSet -= 0.1;
    }
    else if (currentMenu.equals("menu_4")){
      humSet -= 1.0;
    }
    else if (currentMenu.equals("menu_5")){
      lightsOffHh--;
    }
    else if (currentMenu.equals("menu_6")){
      lightsOnMm--; 
    }
    else if (currentMenu.equals("menu_7")){
      lightsOffHh--;
    }
    else if (currentMenu.equals("menu_8")){
      lightsOffMm--;
    }m
    else if (currentMenu.equals("menu_9")){
      waterFrqHh--;
    }
    else if (currentMenu.equals("menu_10")){
      waterDurMm--;
    }mm
  }
     
}
mk
