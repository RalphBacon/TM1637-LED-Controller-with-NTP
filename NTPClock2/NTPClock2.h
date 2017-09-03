/* A simple UDP example which connects to an NTP (Network Time Protocol) ideally in a pool (so we get
 * a random NTP server given to us from that pool).
 *
 * The reply (seconds since midnight 1970) is then converted into the date and time for use in emails.
 *
 */
#include <arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// See the Arduino Playground for this useful time synchronisation library
#include <TimeLib.h>

// Just an open port we can use for the UDP packets coming back in
unsigned int localPort = 8888;

// this is the "pool" name for any number of NTP servers in the pool.
// If you're not in the UK, use "time.nist.gov"
char timeServer[] = "uk.pool.ntp.org";

// NTP time stamp is in the first 48 bytes of the message
const int NTP_PACKET_SIZE = 48;

//buffer to hold incoming and outgoing packets
byte packetBuffer[NTP_PACKET_SIZE];

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

// Your time zone relative to GMT / UTC
const int timeZone = 1;

void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print("    ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year());
  Serial.println();
}

//-----------------------------------------------------------------------------
// send an NTP request to the time server at the given address
//-----------------------------------------------------------------------------
void sendNTPpacket(char* address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

time_t getNTPTime() {

  // Send a UDP packet to the NTP pool address
  Serial.print("Sending NTP packet to ");
  Serial.println(timeServer);
  sendNTPpacket(timeServer);

  // Wait to see if a reply is available
  delay(500);
  if (Udp.parsePacket()) {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    // The time-stamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900)
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");

    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;

    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears + 3600; // DST hardcoded for now

    // Return ms since 01/01/1900
    return epoch;
  }

  // Could not get NTP server response
  Serial.println("No response");
  return 0;
}

//-----------------------------------------------------------------------------
// DOSETUP     DOSETUP     DOSETUP     DOSETUP     DOSETUP     DOSETUP     
//-----------------------------------------------------------------------------
void doSetup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("UIP Ethernet Test for NTP");
  Serial.flush();

  Serial.println("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin ("Greypuss", "mrSeal89");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");

  // On which port will the UDP respond?
  Udp.begin(localPort);

  // What is the name of the function that retrieves the time (in milliseconds since 01/01/1900)?
  setSyncProvider(getNTPTime);
  setSyncInterval(300); // update time from NTP server every X seconds
}
