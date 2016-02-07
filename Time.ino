
boolean InTimeSpan(int startHh, int startMm, int stopHh, int stopMm){

  long startTimeInSeconds = (long) startHh * 60 * 60 + (long) startMm * 60;
  Serial.print("Start time in seconds: ");
  Serial.println(startTimeInSeconds);
  long stopTimeInSeconds = (long) stopHh * 60 * 60 + (long) stopMm * 60;
  Serial.print("Stop time in seconds: ");
  Serial.println(stopTimeInSeconds);
  long currentTimeInSeconds = (long) hour() * 60 * 60 + (long) minute() * 60;
  Serial.print("Current time in seconds: ");
  Serial.println(currentTimeInSeconds);
    
  boolean isBeforeEnd = currentTimeInSeconds < stopTimeInSeconds;
  Serial.print("Is before end time?: ");
  Serial.println(isBeforeEnd);  
  boolean isAfterStart = currentTimeInSeconds >= startTimeInSeconds;
  Serial.print("Is after start time?: ");
  Serial.println(isAfterStart);

  // Deal with timespans that go over midnight
  if (stopTimeInSeconds < startTimeInSeconds) {
    Serial.print("In Timespan: ");
    Serial.println(isAfterStart || isBeforeEnd);
    return isAfterStart || isBeforeEnd;
  } else {
    Serial.print("In Timespan: ");
    Serial.println(isAfterStart && isBeforeEnd);
    return isAfterStart && isBeforeEnd;
  }

  // Time span : 22:00 to 2:00
  // Time 21:00
  //  isBeforeEnd: false
  //  isAfterStart: false
  // Time 23:00
  //  isBeforeEnd: false
  //  isAfterStart: true
  // Time 3:00
  //  isBeforeEnd: true
  //  isAfterStart: false
  
}

