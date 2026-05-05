//Create a set of array to set to our pin layout
//Constantly reading the flex of the pins then takes the mean once the 
//button is pressed stop and read from the storage
#include <HijelHID_BLEKeyboard.h>
HijelHID_BLEKeyboard keyboard;
const int NUM_FLEX = 4;
const int NUM_FORCE = 5;
const int THRESHOLD=1500;
const int FLEX_PIN[NUM_FLEX]={26,33,35,39};
const int FORCE_PIN[NUM_FORCE]={32,25,34,36,27};
float smoothFlex[NUM_FLEX] ;
const float ALPHA=.02;


void setup()
{
  Serial.begin(115200);
  keyboard.setSecurityMode(HIDSecurity::Passkey);
  keyboard.begin();

}

void loop()

{
  read_pins();
  int where=isClick();
  if(where!=-1){
    keyStroke(where);
  }

}

void read_pins(){
  // Read all the flex sensor and uses the last reading and alpha to smooth the new reading
  //higher alpha faster update but less smooth
  for (int i = 0; i < NUM_FLEX; i++){
    smoothFlex[i] = ALPHA * analogRead(FLEX_PIN[i]) + (1 - ALPHA) * smoothFlex[i];
  }
}

int isClick(){

// checks each of the force sensor and return the index of which was above the threshold
  bool combo=false;
  for(int pin=0;pin<NUM_FORCE;pin++){
    if (analogRead(FORCE_PIN[pin])>THRESHOLD){
      while(analogRead(FORCE_PIN[pin])>100){
        // Gesture for clicking while holding the thumb down
         if(pin == 4 && analogRead(FORCE_PIN[0]) > 0){
           combo=true;
         }
       } 
       if (combo){
         return 5;
       }
      return pin;
      
    }
      
  }
  return -1;
}


//use the which force sensor was above the theshold and current flex to find th key to send
void keyStroke(int where){
  int flex;
   if (where==5){
    flex = smoothFlex[0];
   }
   else{
    flex = smoothFlex[where];
   }
  
 
  Serial.print("Flex: ");
  Serial.print(flex);
  Serial.println("  Button:");
  if(where==0){
    if (flex>2600){
      Serial.println("m");
      keyboard.tap(KEY_M);
    }
    else if (flex>1300){
      Serial.println("j");
      keyboard.tap(KEY_J);
    }
    else if (flex>=0){
      Serial.println("u");
      keyboard.tap(KEY_U);
    }
  }
  else if(where==5){
    if (flex>3000){
      Serial.println("n");
      keyboard.tap(KEY_N);

    }
    else if (flex>1000){
      Serial.println("h");
      keyboard.tap(KEY_H);
      
    }
    else if (flex>=0){
      Serial.println("y");
      keyboard.tap(KEY_Y);
      
    }
  }
  else if(where==1){
    if (flex>2600){
      Serial.println(",");
      keyboard.tap(KEY_COMMA);

    }
    else if (flex>1000){
      Serial.println("k");
      keyboard.tap(KEY_K);
      
    }
    else if (flex>=0){
      Serial.println("i");
      keyboard.tap(KEY_I);
      
    }
  }
  else if(where==2){
    if (flex>3000){
      Serial.println(".");
      keyboard.tap(KEY_DOT);

    }
    else if (flex>1000){
      Serial.println("l");
      keyboard.tap(KEY_L);
      
    }
    else if (flex>=0){
      Serial.println("o");
      keyboard.tap(KEY_O);
      
    }
  }
  else if(where==3){
    if (flex>2000){
      Serial.println("/");
      keyboard.tap(KEY_SLASH);

    }
    else if (flex>1000){
      Serial.println(";");
      keyboard.tap(KEY_SEMICOLON);
      
    }
    else if (flex>=0){
      Serial.println("p");
      keyboard.tap(KEY_P);
      
    }
  }
  else if(where==4){
    keyboard.tap(KEY_SPACE);
    if (flex>2000){
      Serial.println(" ");
    }
    else if (flex>1000){
      Serial.println(" ");
      
    }
    else if (flex>=0){
      Serial.println(" ");
      
    }
  }
}
  