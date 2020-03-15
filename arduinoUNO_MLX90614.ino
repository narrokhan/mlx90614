#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "LedControl.h"
const int DIN_PIN = 11;
const int CLK_PIN = 13;
const int CS_PIN = 10;
// Create a new LedControl for 5 devices... 
LedControl lc=LedControl(DIN_PIN,CLK_PIN,CS_PIN,1); 


 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void displayString(const char *chars8) {
  lc.clearDisplay(0);
  for (int i = 0; i < 8 && chars8[i] != 0; i++) {
    lc.setChar(0, 7 - i, chars8[i], false);
  }
}
void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  mlx.begin(); 
}
char ir_displaychars[9] = {};
void loop() {
  memset(ir_displaychars,0,9);
  float mrAT = mlx.readAmbientTempC();
  float mrOT = mlx.readObjectTempC()+0.5;
  dtostrf(mrOT,2,2,ir_displaychars);
  Serial.print("Ambient = "); Serial.print(mrAT); 
  Serial.print("*C\tObject = "); Serial.print(mrOT); Serial.println("*C");
  Serial.print(ir_displaychars);
  displayString(ir_displaychars);
  delay(1000);
}
