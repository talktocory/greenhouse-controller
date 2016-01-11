// ********************************************************
//                         Constants
// ********************************************************
const String BTN_POWER = "Power";
const String BTN_MODE = "Mode";
const String BTN_MUTE = "Mute";

const String BTN_REV = "Reverse";
const String BTN_FWD = "Forward";
const String BTN_PLAY = "Play/Pause";

const String BTN_VOL_DOWN = "Volume Down";
const String BTN_VOL_UP = "Volume Up";
const String BTN_EQ = "Equlalizer";

const String BTN_0 = "0";
const String BTN_100 = "100+";
const String BTN_BACK = "Back";

const String BTN_1 = "1";
const String BTN_2 = "2";
const String BTN_3 = "3";

const String BTN_4 = "4";
const String BTN_5 = "5";
const String BTN_6 = "6";

const String BTN_7 = "7";
const String BTN_8 = "8";
const String BTN_9 = "9";

// ********************************************************
//                         Functions
// ********************************************************

// Decode the actual button pressed on the IR remote
String decodeInput(decode_results &results){
  
  switch(results.value) {
    case 0xFFA25D:  
      return BTN_POWER;
      break;
    case 0xFF629D:  
      return BTN_MODE;
      break;
    case 0xFFE21D:  
      return BTN_MUTE;
      break;
    case 0xFF22DD:  
      return BTN_REV;
      break;
    case 0xFF02FD:  
      return BTN_FWD;
      break;
    case 0xFFC23D:  
      return BTN_PLAY;
      break;
    case 0xFFE01F:  
      return BTN_VOL_DOWN;
      break;
    case 0xFFA857:  
      return BTN_VOL_UP;
      break;
    case 0xFF906F:  
      return BTN_EQ;
      break;
    case 0xFF6897:  
      return BTN_0;
      break;
    case 0xFF9867:  
      return BTN_100;
      break;
    case 0xFFB04F:  
      return BTN_BACK;
      break;
    case 0xFF30CF:  
      return BTN_1;
      break;
    case 0xFF18E7:  
      return BTN_2;
      break;
    case 0xFF7A85:  
      return BTN_3;
      break;
    case 0xFF10EF:  
      return BTN_4;
      break;
    case 0xFF38C7:  
      return BTN_5;
      break;
    case 0xFF5AA5:  
      return BTN_6;
      break;
    case 0xFF42BD:  
      return BTN_7;
      break;
    case 0xFF4AB5:  
      return BTN_8;
      break;
    case 0xFF52AD:  
      return BTN_9;
      break;
    default:
      return "";
  }

}

// Wait for a button to be pressed on the remote
// and return the value once pressed.
String waitForInput(int maxWaitInMillis){
  String result = "";
  unsigned long previousMillis = millis();
  unsigned long currentMillis;

  while (result == ""){
    if (irrecv.decode(&irMessage)) {
      if (irMessage.value != 0xFFFFFFFF){
        result = decodeInput(irMessage); 
      }
      irrecv.resume(); // Receive the next value 
    }
    currentMillis = millis();
    if(currentMillis - previousMillis >= maxWaitInMillis){
      return result;
    }
  }

  return result;
}



