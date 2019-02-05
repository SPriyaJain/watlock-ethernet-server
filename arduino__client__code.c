#include <SPI.h>
#include <Ethernet2.h>
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x98, 0x76, 0xB6, 0x10, 0xB6, 0xA7 };
// use the numeric IP instead of the name for the server:
IPAddress server(192,168,1,1);  
 
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 1);
 
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
 
unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers
 
//#define WIZ_RESET 9
 
#if defined(ESP8266)
  // default for ESPressif
  #define WIZ_CS 7
#elif defined(ESP32)
  #define WIZ_CS 7
#elif defined(ARDUINO_STM32_FEATHER)
  // default for WICED
  #define WIZ_CS PB4
#elif defined(TEENSYDUINO)
  #define WIZ_CS 7
#elif defined(ARDUINO_FEATHER52)
  #define WIZ_CS 7
#else   // default for 328p, 32u4, M4 and M0
  #define WIZ_CS 7
#endif
 
String Emerg = "";
String HighPrior = "";
String MedPrior = "";
String LowPrior = "";
   
void setup() {
#if defined(WIZ_RESET)
  pinMode(WIZ_RESET, OUTPUT);
  digitalWrite(WIZ_RESET, HIGH);
  delay(100);
  digitalWrite(WIZ_RESET, LOW);
  delay(100);
  digitalWrite(WIZ_RESET, HIGH);
#endif
 

 
  // Define which pin to use as the chip select pin for the wing:
  Ethernet.init(WIZ_CS);
  
  // give the ethernet module time to boot up:
  delay(1000);
 
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  
  // Connect to allow reception and transmission of messages :
  client.connect(ip, 80);
  
}
 
void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (((client.available() % 2) == 0) and (client.available())) {
    String c = String(client.read());
    if (c[0] == 1) {
      if (c[1] == 1) {
        Emerg = Emerg + c;
      }
      else if(c[1] == 0) {
        HighPrior = HighPrior + c ;
      }
      
    }
    else if (c[0] == 1) {
      if (c[1] == 1) {
        MedPrior = MedPrior + c;
      }
      else if(c[1] == 0) {
        LowPrior = LowPrior + c;
      }
      
  }
 
  }
 if (!client.connected()) {
    client.stop();
    client.connect(ip, 80);
  }
}
 
// Sends Message
void Send(String message) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
 if (!client.connected()) {
    client.println(message);
 
  }
  else {
    client.stop();
    client.connect(ip, 80);
  }
  // if there's a successful connection:
  
  
}