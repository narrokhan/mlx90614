#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int numeral[10] = {
   //ABCDEFG /dp
   B11111100, // 0
   B01100000, // 1
   B11011010, // 2
   B11110010, // 3
   B01100110, // 4
   B10110110, // 5
   B00111110, // 6
   B11100000, // 7
   B11111110, // 8
   B11100110, // 9
};
const int buttonPin = A3;
int buttonState = 0; 
// pins for decimal point and each segment
// DP,G,F,E,D,C,B,A
 

const int ar_line_segmentPins[] = { 10,12,4,8,9,11,7,3 };

const int nbrDigits= 3; // the number of digits in the LED display
//dig 0 1 2 
 

const int ar_line_digitPins[nbrDigits] = { 2,5,6};


unsigned long time;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();
  for(int i=0; i < 8; i++) {
      pinMode(ar_line_segmentPins[i], OUTPUT); // set segment and DP pins to output
  }
  for(int i=0; i < nbrDigits; i++) {
      pinMode(ar_line_digitPins[i], OUTPUT);
  }
  time = millis();
  pinMode(buttonPin, INPUT);
}
void showNumber( int number)
{
   if(number == 0) {
      showDigit( 0, nbrDigits-1) ; // display 0 in the rightmost digit
   } else {
      // display the value corresponding to each digit
      // leftmost digit is 0, rightmost is one less than the number of places
      for( int digit = nbrDigits-1; digit >= 0; digit--)  {
         if(number > 0)  {
            //Serial.println( number % 10);
            showDigit( number % 10, digit) ;
            number = number / 10;
         }
      }
   }
} 
void showDigit( int number, int digit)
{
   digitalWrite( ar_line_digitPins[digit], HIGH );
   for(int segment = 7; segment >= 0; segment--)  {
      boolean isBitSet = bitRead(numeral[number], segment);
      // isBitSet will be true if given bit is 1
      // isBitSet = ! isBitSet; // Code Option*
      // uncomment the above Code Option line for common anode display
      //Serial.print( isBitSet);
      isBitSet = !isBitSet; 
      digitalWrite( ar_line_segmentPins[segment], isBitSet);
   }
   if(digit==1)
    digitalWrite( ar_line_segmentPins[0], 0);
   //Serial.println( "B");
   delay(5);
   digitalWrite( ar_line_digitPins[digit], LOW );
}
int mrOTint =0;
void loop() {
  // put your main code here, to run repeatedly:
  float mrAT ,mrOT; 
  if(time - millis()>1000) {
    mrAT = mlx.readAmbientTempC();
    mrOT = mlx.readObjectTempC();
    //Serial.println( mrOT);
    if (buttonState == HIGH)//update only button off
      mrOTint = mrOT*10;
    time = millis();
  }
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
 
  // showNumber(123);
  showNumber(mrOTint);
   //delay(1000);
}
