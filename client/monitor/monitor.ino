#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

#include "secrets.h" 
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
char url[]  = CLOUD_URL; 

WiFiClient wifi;
HttpClient client = HttpClient(wifi, url);

int indicator = LED_BUILTIN;
int sentinel = 12;
int status = WL_IDLE_STATUS;
bool messageSent = false;

void setup() {
  // set up on-board input and outpin pins
  pinMode(sentinel, INPUT);
  pinMode(indicator, OUTPUT);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(2000); // hope we get the serial port within 2 seconds, otherwise continue without it

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  digitalWrite(indicator, HIGH);  // turn the LED on (HIGH is the voltage level)
  printCurrentNet();
  printWifiData();

}

void loop() {
  while (digitalRead(sentinel) == HIGH) {}
  
  Serial.println("Disconnect detected");
  
  if (!messageSent) {
    Serial.println("making POST request");
    String contentType = "application/json";

    client.post("/test-arduino-fn", contentType, "{}");

    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);

    messageSent = true;
  }
}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
