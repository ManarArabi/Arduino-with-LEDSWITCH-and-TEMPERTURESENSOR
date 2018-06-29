
//___________________ Global variables ___________________


const int bttn = 2; // button is connected to pin 2
const int led = 12; // LED is connected to pin 12
int bttnState = 0;  //expresses button reading during execution
int ledState = 0;  //expresses LED reading during execution
// initially zero as the button isn't pushed and the LED isn't on

int temp = 0; // temperture sensor is connected to pin A0
int currentTemp ;


int currRead = 0;
int lastRead = 0;
const int rate = 3000;
//___________________ functions ___________________
//check push button state then commit it to the LED
void commitPushBttnAction (); 
void printLedState (int state);
float readTemperture();
void printTemperture(float t);
void setup()
{
	pinMode(led, OUTPUT);
  	pinMode(bttn, INPUT);
  	
  	Serial.begin(9600); // to deal with serial and should be called once at the beginning . 
  	//9600 suitable baud rate to deal with computer .
  	//baud rate >> the data rate in bits per second 
}

void loop()
{
    //delay(10); // Delay a little bit to improve simulation performance
	commitPushBttnAction ();
	delay(100); //slower reading
  
  	//why we can't use just delay function 
 	//in order to execute the whole loop in the gaps between 2 successive printTemperture function
  	currRead = millis();
	currentTemp = readTemperture();
    if (currRead - lastRead >= rate) {
      Serial.print(currRead - lastRead);
      lastRead = currRead;
      printTemperture (currentTemp) ;
    }
}

void commitPushBttnAction ()
{
	bttnState = digitalRead(bttn);
  	// check push button state
  	if (bttnState == HIGH) {
    	// turn LED on:
    	digitalWrite(led, HIGH);
    	ledState = 1;
  	} else {
 	   // turn LED off:
 	   digitalWrite(led, LOW);
 	   ledState = 0;
  	}
  	printLedState(ledState);
}

void printLedState (int state)
{
	Serial.print("The LED is ");
    if (state == 1){
      Serial.println("ON .");
    }else{
      Serial.println("OFF .");
    }

}

float readTemperture()
{
	currentTemp = analogRead(temp);
  	float mv = (currentTemp/1024.0)*5000; 
	float cel = mv/10; //temperture in celsius
	return cel ;
}

void printTemperture(float t)
{
	Serial.print("Temperture is ");
    Serial.print(t);
  	Serial.println("*c");
}

