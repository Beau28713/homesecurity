#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xA8, 0x61, 0x0A, 0xAE, 0xA9, 0xB9 };
IPAddress arduino_ip(169, 254, 104, 124);
IPAddress computer_ip(169, 254, 104, 125);
unsigned int local_port = 5000;
char packet[UDP_TX_PACKET_MAX_SIZE];
int packet_size;
EthernetUDP udp;

int gate_switch = 9;
int gate_state = 0;

void setup() {

  Serial.begin(115200);
  connection();
  udp.begin(local_port);  // Initialize and start listening on port for data
  pinMode(gate_switch, INPUT_PULLUP);
  delay(1500);
}

void loop() {
  packet_size = udp.parsePacket();  // Returns the size of the incomming packet
  gate_state = digitalRead(gate_switch);

  // Read data from user
  if (packet_size > 0) {
    Serial.println(packet_size);
    read_user_data();
  }

  if (gate_state == 0) {
    web_cam();
  }
}

void web_cam() {
  udp.beginPacket(computer_ip, local_port);  // use this method to start a connection to send data to the recieving computer
  udp.write("True");                             // Send data back to Python
  udp.endPacket();
}

void read_user_data() {
  udp.read(packet, UDP_TX_PACKET_MAX_SIZE);  // Read the incomming data
  String data(packet);                       // incoming data from user convert byte info to string

  if (data == "red") {
    udp.beginPacket(udp.remoteIP(), udp.remotePort());  // use this method to recieve data from sending computer
    udp.write("You are asking for red");                // Send data back to Python
    udp.endPacket();
  }

  memset(packet, 0, UDP_TX_PACKET_MAX_SIZE);  // reset packet(data) array to be empty
}

void connection() {
  Serial.println("Initialize Ethernet with static IP:");
  Ethernet.begin(mac, arduino_ip);

  Serial.print("  IP assigned ");
  Serial.println(Ethernet.localIP());
}
