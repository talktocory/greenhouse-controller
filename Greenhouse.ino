// see: https://learn.adafruit.com/dht/using-a-dhtxx-sensor
#include <DHT.h>

#include <Wire.h>  // Comes with Arduino IDE

// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

#include <IRremote.h>
#include <IRremoteInt.h>

// ********************************************************
//                         Constants
// ********************************************************
#define RECV_PIN 10 // IR receiver pin
#define DHTPIN 2
#define DHTTYPE DHT11
#define RELAYLIGHTS 3
#define RELAYHEATER 5
#define RELAYHUMIDIFIER 4
#define RELAYVENTILATION 6

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// ********************************************************
//                      Global Variables
// ********************************************************
// greenhouse variables
float tempSet, tempAct, humSet, humAct, sensorValue;
int lightsOnHh, lightsOnMm, lightsOffHh, lightsOffMm;
int ventilationFrqHh, ventilationDurMm;
unsigned long lastVentilationStart, nextVentilationStart, nextVentilationEnd;
String buttonPressed;
String currentMenu;
tmElements_t tm;
  
/* initialize temp/hum sensor
 *  SDA - ANALOG Pin 4
 *  SCL - ANALOG pin 5
*/
DHT dht(DHTPIN, DHTTYPE);

// initialize IR receiver
// Digital pin 2
IRrecv irrecv(RECV_PIN);
decode_results irMessage;

// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
// see: https://arduino-info.wikispaces.com/LCD-Blue-I2C
/*
 * SDA - ANALOG Pin 4
 * SCL - ANALOG pin 5
 * On most Arduino boards, SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5
*/
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

// ********************************************************
//                     Utility Functions 
// ********************************************************
void printDigits(int digits){
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
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

  // start the // Serial monitor
  // Serial.begin(9600);
  // while (!Serial) ; // wait for Arduino // Serial Monitor
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) {
    // Serial.println("Date and time not set.  Setting it to last compile time."); 
    // get the date and time the compiler was run
    if (getDate(__DATE__) && getTime(__TIME__)) {
      RTC.write(tm);
    }
  } else {
    // Serial.println("RTC has set the system time");     
  }
  
  // Set system defaults
  tempSet = 22.0;
  tempAct = tempSet;
  humSet = 60.0;
  humAct = humSet;
  lightsOnHh = 6;
  lightsOnMm = 0;
  lightsOffHh = 22;
  lightsOffMm = 0;
  ventilationFrqHh = 1;
  ventilationDurMm = 15;
  lastVentilationStart = now();
  
  // Display the main menu
  currentMenu = "menu_0";

  // Setup Relays
  pinMode(RELAYLIGHTS, OUTPUT);
  pinMode(RELAYHEATER, OUTPUT);
  pinMode(RELAYHUMIDIFIER, OUTPUT);
  pinMode(RELAYVENTILATION, OUTPUT);
  digitalWrite(RELAYLIGHTS, HIGH);
  digitalWrite(RELAYHEATER, HIGH);
  digitalWrite(RELAYHUMIDIFIER, HIGH);
  digitalWrite(RELAYVENTILATION, HIGH);
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
      tm.Hour = tm.Hour + 1;
      RTC.write(tm);
    }
    else if (currentMenu.equals("menu_2")){
      tm.Minute = tm.Minute + 1;
      RTC.write(tm);
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
      tm.Hour = tm.Hour - 1;
      RTC.write(tm);
    }
    else if (currentMenu.equals("menu_2")){
      tm.Minute = tm.Minute - 1;
      RTC.write(tm);
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

  // Adjust Lights
  if (InTimeSpan(lightsOnHh, lightsOnMm, lightsOffHh, lightsOffMm)) {
    digitalWrite(RELAYLIGHTS, LOW); 
  } else {
    digitalWrite(RELAYLIGHTS, HIGH);   
  }

  // Adjust Humidity
 
  if ((humAct + 5) < humSet){
    digitalWrite(RELAYHUMIDIFIER, LOW);   
  } else if ((humAct - 5) > humSet) {
    digitalWrite(RELAYHUMIDIFIER, HIGH);   
  }

  // Adjust Heater
  if ((tempAct + 2) < tempSet){
    digitalWrite(RELAYHEATER, LOW);   
  } else if ((tempAct - 2) > tempSet) {
    digitalWrite(RELAYHEATER, HIGH);   
  }

  // Adjust Ventilation
  nextVentilationStart = lastVentilationStart + ventilationFrqHh * 60 * 60;
  nextVentilationEnd = nextVentilationStart + ventilationDurMm * 60;
  if ((now() > nextVentilationStart) && (now() < nextVentilationEnd)){
    lastVentilationStart = nextVentilationStart;
    digitalWrite(RELAYVENTILATION, LOW);
  } else {
    digitalWrite(RELAYVENTILATION, HIGH);
  }

}
