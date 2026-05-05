//Create a set of array to set to our pin layout
//Constantly reading the flex of the pins then takes the mean once the 
//button is pressed stop and read from the storage
#include <HijelHID_BLEKeyboard.h>
HijelHID_BLEKeyboard keyboard;
const int NUM_FLEX = 4;
const int NUM_FORCE = 5;
const int THRESHOLD=1000;
const int FLEX_PIN[NUM_FLEX]={34,35,32,26};
const int FORCE_PIN[NUM_FORCE]={39,25,27,33,36};
float smoothFlex[NUM_FLEX] = {0};
const float ALPHA=.2;

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
  // higher alpha faster update but less smooth  
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
    if (flex>1500){
      Serial.println("v");
      keyboard.tap(KEY_V);
    }
    else if (flex>300){
      Serial.println("f");
      keyboard.tap(KEY_F);
    }
    else if (flex>=0){
      Serial.println("r");
      keyboard.tap(KEY_R);
    }
  }
  else if(where==5){
    if (flex>2000){
      Serial.println("b");
      keyboard.tap(KEY_B);

    }
    else if (flex>400){
      Serial.println("g");
      keyboard.tap(KEY_G);
      
    }
    else if (flex>=0){
      Serial.println("t");
      keyboard.tap(KEY_T);
      
    }
  }
  else if(where==1){
    if (flex>2000){
      Serial.println("c");
      keyboard.tap(KEY_C);

    }
    else if (flex>400){
      Serial.println("d");
      keyboard.tap(KEY_D);
      
    }
    else if (flex>=0){
      Serial.println("e");
      keyboard.tap(KEY_E);
      
    }
  }
  else if(where==2){
    if (flex>2200){
      Serial.println("x");
      keyboard.tap(KEY_X);

    }
    else if (flex>1000){
      Serial.println("s");
      keyboard.tap(KEY_S);
      
    }
    else if (flex>=0){
      Serial.println("w");
      keyboard.tap(KEY_W);
      
    }
  }
  else if(where==3){
    if (flex>2000){
      Serial.println("z");
      keyboard.tap(KEY_Z);

    }
    else if (flex>1000){
      Serial.println("a");
      keyboard.tap(KEY_A);
      
    }
    else if (flex>=0){
      Serial.println("q");
      keyboard.tap(KEY_Q);
      
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
  