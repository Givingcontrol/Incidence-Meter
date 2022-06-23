//https://richard-ramos.github.io/esp-01-oled/
//
// Works
//Wire.pins(2, 0);   //This works
// displays angles on OLED
//swap X and Y to fit build on PCB

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <MPU6050_light.h>

unsigned long timer = 0;

//I2C ESP32:: SCL = GPIO22 SDA= GPIO21
MPU6050 mpu(Wire);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//MPU variables

int16_t pitch, roll, yaw; //from mpu6050light
int16_t Pitch, Roll, Yaw; //from mpu6050light

void setup() {
  Serial.begin(115200);

   Wire.begin();
 
  //Wire.pins(0, 2);
  Wire.pins(2, 0);   //This works        // set I2C pins (SDA = GPIO2, SCL = GPIO0), default clock is 100kHz
 
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } // stop everything if could not connect to MPU6050
   // draw the first ~12 characters in the font
 // testdrawchar();
   

 Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   mpu.calcOffsets(); // gyro and accelero 
  
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(10, 0);
  display.write("Calculating offsets,");
  display.setCursor(10,16 );
  display.write(" do not move MPU6050");
  display.display();
  delay(2000); 
  
}
void loop() {

  mpu.update();
  Pitch = mpu.getAngleX() ;
  Roll = mpu.getAngleY();
  Yaw = mpu.getAngleZ();
 if ((millis() - timer) > 10) { // print data every 10ms

//display.cp437(false);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);
  display.print("P:");
  display.println (mpu.getAngleY(),1);
  display.print(" R: ");
  display.println (mpu.getAngleX(),1);
  display.print(" Y:");
  display.println (mpu.getAngleZ(),1);
   display.display();
     Serial.print(" X : ");
     Serial.print(mpu.getAngleX());
     Serial.print("\tY : ");
     Serial.print(mpu.getAngleY());
     Serial.print("\tZ : ");
     Serial.println(mpu.getAngleZ());
     timer = millis();
   }
 }
    
   


void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
 // display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}
