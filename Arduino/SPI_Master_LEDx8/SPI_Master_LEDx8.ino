#include <SPI.h>
#define SPI_CS_PIN  (10)

uint8_t cnt = 1;

void setup()
{
  Serial.begin(9600);
  Serial.println("SPI_Master_LEDx8 Test");
  
  pinMode(SPI_CS_PIN, OUTPUT);
  digitalWrite(SPI_CS_PIN, HIGH);
  
  SPI.begin();
}

void loop()
{
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(SPI_CS_PIN, LOW);
  uint8_t rdata = SPI.transfer(1 << cnt);
  digitalWrite(SPI_CS_PIN, HIGH);
  SPI.endTransaction();

  cnt++;
  if (cnt > 8) {
    cnt = 0;
  }

  Serial.println(rdata);
  
  delay(100);  
}
