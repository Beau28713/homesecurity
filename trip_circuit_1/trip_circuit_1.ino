#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xA8, 0x61, 0x0A, 0xAE, 0xA9, 0xB9 };
IPAddress ip(169, 254, 104, 124);

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  
  connection_test();
}

void loop() {
  if (Ethernet.linkStatus() == LinkON){
    Serial.println("Link good");
  }

  else if (Ethernet.linkStatus() == LinkOFF){
    Serial.println("Ethernet cable unplugged");
  }
  delay(10000);
}

bool connection_test() {
  Serial.println("Initialize Ethernet with DHCP:");
  Ethernet.begin(mac, ip);

  Serial.print("  DHCP assigned IP ");
  Serial.println(Ethernet.localIP());
  
}
