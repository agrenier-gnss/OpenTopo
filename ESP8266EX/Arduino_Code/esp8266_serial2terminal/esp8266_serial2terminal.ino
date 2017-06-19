
#include <SoftwareSerial.h>

#define LED_RELAY 15

SoftwareSerial swSer(14, 12, false, 256);     //TX -> IO12 RX->IO14 on board


void setup() {
  pinMode(LED_RELAY, OUTPUT);
 
  Serial.begin(115200);
  swSer.begin(115200);

  Serial.println("\nSoftware serial test started");

  for (char ch = ' '; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");

}

void loop()
{
  while (swSer.available() > 0)
  {
    Serial.write(swSer.read());
  }
  digitalWrite(LED_RELAY, LOW);  
  delay(10);   
  
  while (Serial.available() > 0)
  {
    swSer.write(Serial.read());
  }
  
  /*
  Serial.write('U');
  swSer.write('P');
  */
                  
  digitalWrite(LED_RELAY, HIGH);  
  delay(10);     
}
