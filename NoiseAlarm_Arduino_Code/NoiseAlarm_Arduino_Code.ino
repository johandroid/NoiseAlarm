#include <TM1637Display.h>

const int MIC = 0; //the microphone amplifier output is connected to pin A0
const int MIC_DO = 11; 
const int LED = 10; 
const int CLK = 9; //Set the CLK pin connection to the display
const int DIO = 8; //Set the DIO pin connection to the display
const int buzzerPin = 3; //Define buzzerPin
const int COUNTER_VAL = 10; 

int adc;
int dB, PdB; //the variable that will hold the value read from the microphone each time
int counter = 0; 

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.


void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 1); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  
}

void setup() {
  display.setBrightness(0x00);  //set the diplay to minimum brightness
  pinMode(LED, OUTPUT);
  pinMode(MIC_DO, INPUT);
}

void printDataScreen()
{
  if(counter <= 0)
  {
    int roundedVal = (dB/10.0) * 100; 
    display.showNumberDecEx(roundedVal,0b00100000); //Display the Variable value;
    //display.showNumberDecEx(adc);
    counter = COUNTER_VAL; 
  }else{
    counter--; 
  }
}
void loop(){

  PdB = dB; //Store the previous of dB here
  adc= analogRead(MIC); //Read the ADC value from amplifer 
  dB = (adc+83.2073) / 11.003; //Convert ADC value to dB using Regression values

  if(digitalRead(MIC_DO) == HIGH)
  {
    digitalWrite(LED, HIGH); 
    delay(1);  
    digitalWrite(LED, LOW); 
  }
  
  printDataScreen();  
}


