
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void digitalClockDisplay(){
  // digital clock display of the time  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MICHAEL!!!!");
  lcd.setCursor(0, 1);
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
}

