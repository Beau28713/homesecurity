#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xA8, 0x61, 0x0A, 0xAE, 0xA9, 0xB9 };
IPAddress ip(169, 254, 104, 124);
unsigned int local_port = 5000;
char packet[UDP_TX_PACKET_MAX_SIZE];
int packet_size;
EthernetUDP udp; 

void setup() {

  Serial.begin(9600);
  connection();
  udp.begin(local_port); // Initialize and start listening on port for data
  delay(1500);
}

void loop() {
  packet_size = udp.parsePacket(); // Returns the size of the incomming packet

  if (packet_size > 0){
    udp.read(packet, UDP_TX_PACKET_MAX_SIZE); // Read the incomming data 
    String data(packet); // convert byte info to string

    if (data == "red"){
      udp.beginPacket(udp.remoteIP(), udp.remotePort()); // start a connection to write data
      udp.write("You are asking for red"); // Send data back to Python
      udp.endPacket();
    }

    if (data == "blue"){
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.write("You are asking for blue"); 
      udp.endPacket();
    }
  }
  memset(packet, 0, UDP_TX_PACKET_MAX_SIZE); // reset packet(data) array to be empty
}

void connection() {
  Serial.println("Initialize Ethernet with static IP:");
  Ethernet.begin(mac, ip);

  Serial.print("  IP assigned ");
  Serial.println(Ethernet.localIP());
  
}
