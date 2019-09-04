
boolean InTimeSpan(int startHh, int startMm, int stopHh, int stopMm){

  long startTimeInSeconds = (long) startHh * 60 * 60 + (long) startMm * 60;
  long stopTimeInSeconds = (long) stopHh * 60 * 60 + (long) stopMm * 60;
  long currentTimeInSeconds = (long) tm.Hour * 60 * 60 + (long) tm.Minute * 60;    
  boolean isBeforeEnd = currentTimeInSeconds < stopTimeInSeconds;
  boolean isAfterStart = currentTimeInSeconds >= startTimeInSeconds;

  // Deal with timespans that go over midnight
  if (stopTimeInSeconds < startTimeInSeconds) {
    return isAfterStart || isBeforeEnd;
  } else {
    return isAfterStart && isBeforeEnd;
  }
  
}
