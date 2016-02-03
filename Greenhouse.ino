// see: https://learn.adafruit.com/dht/using-a-dhtxx-sensor
#include <DHT.h>

/* YourDuino.com Example Software Sketch
 20 character 4 line I2C Display
 Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
 Connect Vcc and Ground, SDA to A4, SCL to A5 on Arduino
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

#include <Time.h>
#include <TimeLib.h>
#include <IRremote.h>
#include <IRremoteInt.h>

// ********************************************************
//                         Constants
// ********************************************************
#define RECV_PIN 10 // IR receiver pin
#define DHTPIN 2
#define DHTTYPE DHT11
const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

// ********************************************************
//                      Global Variables
// ********************************************************
// greenhouse variables
float tempSet, tempAct, humSet, humAct;
int lightsOnHh, lightsOnMm, lightsOffHh, lightsOffMm;
int ventilationFrqHh, ventilationDurMm;
String buttonPressed;
String currentMenu;
float sensorValue;

// initialize temp/hum sensor
DHT dht(DHTPIN, DHTTYPE);

// initialize IR receiver
IRrecv irrecv(RECV_PIN);
decode_results irMessage;

// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

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
  tempAct = tempSet;
  humSet = 80.0;
  humAct = humSet;
  lightsOnHh = 6;
  lightsOnMm = 0;
  lightsOffHh = 21;
  lightsOffMm = 00;
  ventilationFrqHh = 6;
  ventilationDurMm = 3;
  
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
      ventilationFrqHh++;
    }
    else if (currentMenu.equals("menu_10")){
      ventilationDurMm++;
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
    }
    else if (currentMenu.equals("menu_9")){
      ventilationFrqHh--;
    }
    else if (currentMenu.equals("menu_10")){
      ventilationDurMm--;
    }
  }

  // Read temp and humidity
  sensorValue = dht.readTemperature();
  if (!isnan(sensorValue)){
    tempAct = sensorValue;
  }
  sensorValue = dht.readHumidity();
  if (!isnan(sensorValue)){
    humAct = sensorValue;
  }

  
}
