#include <SoftwareSerial.h>
SoftwareSerial espSerial(6, 7);

#define DEBUG true 
String mySSID = "";  // WiFi SSID
String myPassword = ""; // WiFi Password
String myWriteAPI = ""; // Write API of traffic light channel
String myHost = "api.thingspeak.com"; // Host name
String myPort = "80"; // Port number
unsigned long previousMillis = 0; // Initial value for timer
const long interval = 600000; // 10 minutes interval for timer
unsigned long syncDelay = 10000; // Custom delay in order to wait for ThinkSpeak to sync 

void setup() {
  Serial.begin(115200); // Set baud rate with arduino
  espSerial.begin(115200); // Set baud rete with WiFi module
  espData("AT+RST", 1000, DEBUG); // Reset
  espData("AT+CWMODE=1", 1000, DEBUG); // Enable client mode
  espData("AT+CWJAP=\""+ mySSID +"\",\""+ myPassword +"\"", 1000, DEBUG); // Connect to WiFi
  espData("ΑΤ+CIFSR", 1000, DEBUG); // Get IP address
}

void loop() {
  unsigned long delayValue = 30000; // Initialiaze delay value
  
  // First FOR is responsible for changing the field values and depending on the field it chooses the appropriate delay
  for(int myField=1; myField<4; ++myField == 2 ? delayValue = 20000 : delayValue = 30000) {
    // Second FOR is responsible for changing the light values
    for (int lightValue=1; lightValue>-1; --lightValue == 0 ? delayValue = syncDelay : 0) {
      sendData(myWriteAPI, "field" + String(myField), String(lightValue), delayValue); // Sending data to ThinkSpeak
      if (millis() - previousMillis >= interval) { // Check timer
        previousMillis = millis(); // Reset timer
        Serial.print("Emergency yellow on\n"); 
        sendData(myWriteAPI, "field1", "0", syncDelay);
        sendData(myWriteAPI, "field3", "0", syncDelay);
        sendData(myWriteAPI, "field2", "1", 60000);
        sendData(myWriteAPI, "field2", "0", syncDelay);
        Serial.print("Emergency yellow off\n");
        break; // Continues to the next field
      }
    }
  }
}

void sendData(String tempAPI, String tempField, String tempLightValue, unsigned long tempDelayValue) {
  String data = "GET /update?api_key=" + tempAPI + "&" + String(tempField) + "=" + String(tempLightValue); // Set up GET Request
  espData("AT+CIPMUX=1", 1000, DEBUG); // Configure multiplexing
  espData("AT+CIPSTART=0,\"TCP\",\""+ myHost +"\","+ myPort, 1000, DEBUG); // Start TCP connection
  espData("AT+CIPSEND=0," +String(data.length()+4),1000,DEBUG); // Sends data
  espSerial.find(">");
  espSerial.println(data);
  Serial.print("Field: "); // Print current field 
  Serial.println(tempField);
  Serial.print("Traffic Light: "); // Print current field value
  Serial.println(tempLightValue);
  Serial.print("Delay: "); // Print current delay
  Serial.println(String(tempDelayValue));
  espData("AT+CIPCLOSE=0",1000,DEBUG); // Close TCP connection
  delay(tempDelayValue);
}

String espData(String command, const int timeout, boolean debug) {
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println(" ");
  String response = "";
  espSerial.println(command);
  long int time = millis();
  while ( (time + timeout) > millis()) {
    while (espSerial.available()) {
      char c = espSerial.read();
      response += c;
    }
  }
  if (debug) {
    //Serial.print(response);
  }
  return response;
}
