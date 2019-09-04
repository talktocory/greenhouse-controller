void displayMenu(String newMenu){
  
    if (newMenu == "menu_0") {
      currentMenu = newMenu;
      displayMenu_0();
    }
    else if (newMenu == "menu_1") {
      currentMenu = newMenu;
      displayMenu_1();
    }
    else if (newMenu == "menu_2") {
      currentMenu = newMenu;
      displayMenu_2();
    }
    else if (newMenu == "menu_3") {
      currentMenu = newMenu;
      displayMenu_3();
    }
    else if (newMenu == "menu_5") {
      currentMenu = newMenu;
      displayMenu_5();
    }
    else if (newMenu == "menu_6") {
      currentMenu = newMenu;
      displayMenu_6();
    }
    else if (newMenu == "menu_7") {
      currentMenu = newMenu;
      displayMenu_7();
    }
    else if (newMenu == "menu_8") {
      currentMenu = newMenu;
      displayMenu_8();
    }
    else if (newMenu == "menu_9") {
      currentMenu = newMenu;
      displayMenu_9();
    }
    else if (newMenu == "menu_10") {
      currentMenu = newMenu;
      displayMenu_10();
    }
}

// Home screen displays time, humidity and temp
void displayMenu_0(){
  lcd.clear();

  if (RTC.read(tm)) {
    lcd.setCursor(0, 0);
    lcd.print("Time:   ");
    printDigits(tm.Hour);
    lcd.print(':');
    printDigits(tm.Minute);
    lcd.print(':');
    printDigits(tm.Second);
    lcd.setCursor(0, 1);
    lcd.print("T: ");
    lcd.print(tempAct, 2);
    lcd.print(" H: ");
    lcd.print(humAct, 1);
  }  else {
    if (RTC.chipPresent()) {
      // Serial.println("The DS1307 is stopped.  Please run the SetTime");
    } else {
      // Serial.println("DS1307 read error!  Please check the circuitry.");
    }
  }

}

// Time Settings
void displayMenu_1(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time hh:      ");
  printDigits(tm.Hour);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Time Settings
void displayMenu_2(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time mm:      ");
  printDigits(tm.Minute);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Temp Settings
void displayMenu_3(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:       ");
  lcd.print(tempSet, 1);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Light Settings
void displayMenu_5(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light On hh:  ");
  printDigits(lightsOnHh);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Light Settings
void displayMenu_6(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light On mm:  ");
  printDigits(lightsOnMm);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

void displayMenu_7(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light Off hh: ");
  printDigits(lightsOffHh);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Light Settings
void displayMenu_8(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light Off mm: ");
  printDigits(lightsOffMm);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Pump Settings
void displayMenu_9(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pump Frq hh:  ");
  printDigits(pumpFrqHh);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}

// Pump Settings
void displayMenu_10(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pump Dur mm: ");
  printDigits(pumpDurMm);
  lcd.setCursor(0, 1);
  lcd.print("Use + - to Adj");
}
