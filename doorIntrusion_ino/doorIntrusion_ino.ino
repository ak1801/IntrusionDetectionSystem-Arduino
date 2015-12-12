
/*

Team : Bheeman, Akshit, Nayantara 

Project :  Door Intrusion Detection
Resources : PIR sensor, Bread Board, Audrino UNO, 4 cables

-----------------------------------------------------------

PIR sensor is motion detector sensor. It is detect any kind motion detection

*/
    int calibrationTime = 30;        
    
    //the time when the sensor outputs a low impulse
    long unsigned int lowIn;         
    
    //the amount of milliseconds the sensor has to be low 
    //before we assume all motion has stopped
    long unsigned int pause = 5000;  
    
    boolean lockLow = true;
    boolean takeLowTime; 

    int ledPin = 13;
    int pirPin = 3;
    
    void setup() {
     Serial.begin(9600);
     pinMode(pirPin, INPUT);
     pinMode(ledPin, OUTPUT);
     digitalWrite(pirPin, LOW);
     
     Serial.print("calibrating sensor");
     
     for(int i=0; i<calibrationTime; i++) {
       Serial.print("."); 
       delay(1000);
     }
       
       Serial.println("done");
       Serial.println("Sensor Active");
       delay(50);
    }
    
    void loop() {
     
     if(digitalRead(pirPin) == HIGH) {digitalWrite(ledPin,HIGH);
       if(lockLow) {
         lockLow = false;
        Serial.println("---");
             Serial.print("motion detected at ");
             Serial.print(millis()/1000);
             Serial.println(" sec"); 
             delay(50);
             }         
             takeLowTime = true;
        }
     } 
     
    if(digitalRead(pirPin) == LOW){       
         digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
  
         if(takeLowTime){
          lowIn = millis();          //save the time of the transition from high to LOW
          takeLowTime = false;       //make sure this is only done at the start of a LOW phase
          }
         //if the sensor is low for more than the given pause, 
         //we assume that no more motion is going to happen
         if(!lockLow && millis() - lowIn > pause){  
             //makes sure this block of code is only executed again after 
             //a new motion sequence has been detected
             lockLow = true;                        
             Serial.print("motion ended at ");      //output
             Serial.print((millis() - pause)/1000);
             Serial.println(" sec");
             delay(50);
             }
         }
    
}



