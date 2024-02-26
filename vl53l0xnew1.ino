#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

const int xshut0 = 4; //x
const int xshut1 = 5; //y
Adafruit_VL53L0X lox0 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
float yt=170;
float y3=0;
float y2=0;
float x=0;
float t1=0;
int i = 0;
void setup() {
  Serial.begin(38400);
  while (! Serial) {
    delay(1);
  }

  pinMode(xshut0, OUTPUT);
  pinMode(xshut1, OUTPUT);
  digitalWrite(xshut0, LOW);
  digitalWrite(xshut1, LOW);
  delay(10);
  digitalWrite(xshut0, HIGH);
  digitalWrite(xshut1, HIGH);
  delay(10);

  // SET SENSOR#0
  digitalWrite(xshut1, LOW);
  Serial.println("SET VL53L0X#0 ADDRESS: 0x30");
  if (!lox0.begin(0x30)) {
    Serial.println(F("Failed to boot VL53L0X#0 at 0x30"));
    while(1);
  }

  // SET SENSOR#1
  digitalWrite(xshut1, HIGH);
  Serial.println("SET VL53L0X#1 ADDRESS: 0x31");
  if (!lox1.begin(0x31)) {
    Serial.println(F("Failed to boot VL53L0X#1 at 0x31"));
    while(1);
  }

  // start continuous ranging
  lox0.startRangeContinuous();
  lox1.startRangeContinuous();

}

void loop() {
  x= lox0.readRange();
  y3= lox1.readRange();
  Serial.print("DATA,TIME,");
  Serial.print(String(x));
  Serial.print(",");
  Serial.print(String(y3));
  Serial.print(",");
  Serial.println(String(y3)+"---pad---"+String(i));
     //Serial.println("yt:"+String(yt)+" - y3: "+String(y3)+" - : "+String(y2)+" - t1: "+String(t1));
 if(x<150){ 
  if(y2<yt){
    if((y2-t1)>0){
      if((y3-y2)<0){
        if((y2 - y3) > 6 ){
        i++;
        delay(50);
        }
      }
    }
  }
  {  
     t1 = y2;
     y2 = y3;
  }
 }
  // if (lox0.isRangeComplete() && lox1.isRangeComplete()) {
  //   // Serial.print("DATA,TIME,");
  //   // Serial.print("Sensor 0 ");
  //   Serial.print(lox0.readRange());
  //   Serial.print(",");
  //   // Serial.print(", Sensor#1: ");
  //   Serial.println(lox1.readRange());
  // }
  delay(80);
}

