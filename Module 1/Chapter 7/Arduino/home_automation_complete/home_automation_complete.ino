/***************************************************
  This is a modified version of the chat_server program is part of the
  Adafruit CC3000 Library, that works in conjuction with the procedure in the 
  book 'Arduino by Example' written by Adith Jagadish Boloor and published by
  PACKT Publishing.
  Once the program has been uploaded, use a terminal such as Putty and connect to
  the IP address of the CC3000 which can be obtained from the serial monitor. Also
  switch to Telnet as the mode of communication. In addition to that, this code 
  can be controlled through the apps for smartphones as well as through speech 
  recognition.
  
  Commands:
  1 - Light in your room ON
  2 - Light in your room OFF
  3 - Fan in your room ON
  4 - Fan in your room OFF
  5 - Light in living room ON
  6 - Light in living room OFF
  7 - Television ON
  8 - Television OFF
  q - Disconnect
  
  The following text is from the originial chat_server program.
  Adafruit CC3000 Breakout/Shield TCP Chat Server
    
  This is a simple chat server which allows clients to connect
  with telnet and exchange messages.  Anything sent by one
  client will be written out to all connected clients.

  See the CC3000 tutorial on Adafruit's learning system
  for more information on setting up and using the
  CC3000:
    http://learn.adafruit.com/adafruit-cc3000-wifi  
    
  Requirements:
  
  This sketch requires the Adafruit CC3000 library.  You can
  download the library from:
    https://github.com/adafruit/Adafruit_CC3000_Library
  
  For information on installing libraries in the Arduino IDE
  see this page:
    http://arduino.cc/en/Guide/Libraries
  
  Usage:
    
  Update the SSID and, if necessary, the CC3000 hardware pin 
  information below, then run the sketch and check the 
  output of the serial port.  After connecting to the 
  wireless network successfully the sketch will output 
  the IP address of the server and start listening for 
  connections.  Once listening for connections, connect
  to the server from your computer  using a telnet client
  on port 23.  
           
  For example on Linux or Mac OSX, if your CC3000 has an
  IP address 192.168.1.100 you would execute in a command
  window:
  
    telnet 192.168.1.100 23
           
  Connect multiple clients and notice that whatever one client
  sends will be echoed to all other clients.  Press ctrl-] and 
  type quit at the prompt to close the telnet session.
           
  On Windows you'll need to download a telnet client.  PuTTY 
  is a good, free GUI client: 
    http://www.chiark.greenend.org.uk/~sgtatham/putty/
  
  License:
 
  This example is copyright (c) 2013 Tony DiCola (tony@tonydicola.com)
  and is released under an open source MIT license.  See details at:
    http://opensource.org/licenses/MIT
  
  This code was adapted from Adafruit CC3000 library example 
  code which has the following license:
  
  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution  
 ****************************************************/

#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "utility/socket.h"

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "myNetowrk"           // cannot be longer than 32 characters!
#define WLAN_PASS       "myPassword"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define LISTEN_PORT           23    // What TCP port to listen on for connections.

Adafruit_CC3000_Server chatServer(LISTEN_PORT);

int client_status = 0;
int relay_status = 0;

int light_room = A1;
int fan_room = A2;
int light_main = A3;
int tv_main = A4;

void setup(void)
{  
  Serial.begin(115200);
  Serial.println(F("Hello, CC3000!\n")); 

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
  
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  // Start listening for connections
  chatServer.begin();
  
  Serial.println(F("Listening for connections..."));
}

void loop(void)
{
  // Try to get a client which is connected.
  Adafruit_CC3000_ClientRef client = chatServer.available();
  if (client) {
     // Check if there is data available to read.
     if (client.available() > 0) {
       if(client_status == 0)
       {
         chatServer.write("HELLO!   \n");
         delay(100);
         Serial.println("Client Connected!");
         client_status = 1;
       }
       // Read a byte and write it to all clients.
       uint8_t ch = client.read();
       ch = char(ch);
       Serial.print("Message: ");
       Serial.println(ch);
       switch(ch)
       {
         case '1':
           analogWrite(light_room, 255);
           chatServer.write("ROOM LIGHT ON\n");
           delay(500);
           break;
         case '2':
         {
           analogWrite(light_room, 0);
           chatServer.write("ROOM LIGHT OFF\n");
           delay(500);
           break;
         }
         case '3':
         {
           analogWrite(fan_room, 255);
           chatServer.write("ROOM FAN ON\n");
           delay(500);
           break;
         }
         case '4':
         {
           analogWrite(fan_room, 0);
           chatServer.write("ROOM FAN OFF\n");
           delay(500);
           break;
         }
         case '5':
         {
           analogWrite(light_main, 255);
           chatServer.write("MAIN LIGHT ON\n");
           delay(500);
           break;
         }
         case '6':
         {
           analogWrite(light_main, 0);
           chatServer.write("MAIN LIGHT OFF\n");
           delay(500);
           break;
         }
         case '7':
         {
           analogWrite(tv_main, 255);
           chatServer.write("TV ON\n");
           delay(500);
           break;
         }
         case '8':
         {
           analogWrite(tv_main, 0);
           chatServer.write("TV OFF\n");
           delay(500);
           break;
         }
         case 'q':
         {
           chatServer.write("DISCONNECTED");
           cc3000.disconnect();
           break;
         }
         default:
           break;
       }
     }
  }

}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
