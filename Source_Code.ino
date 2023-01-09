#include <SoftwareSerial.h>
SoftwareSerial espSerial(6, 7);

#define DEBUG true 
String mySSID = "VODAFONE_4354_GUEST";  // WiFi SSID
String myPassword = "urxf7QNeZY"; // WiFi Password
String myWriteAPI = "CQNT7P4EF9X2GQWG"; // Write API of traffic light channel
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



/*
  Not used code

  for(int myField=1; myField<4; myField++) {
    if(myField == 2) {
      delayValue=20000;
    }
    else {
      delayValue=30000;
    }
    for (int lightValue=1; lightValue>-1; lightValue--) {
      if(lightValue == 0) { 
        delayValue=10000;
      }
      sendData(myWriteAPI, "field" + String(myField), String(lightValue), delayValue);
    }
  }
*/


/*
{"channel":{"id":2000973,"name":"Traffic Light","latitude":"0.0","longitude":"0.0",
"field1":"Field Label 1","field2":"Field Label 2","field3":"Field Label 3","field8":"Field Label 8",
"created_at":"2023-01-05T16:53:49Z","updated_at":"2023-01-06T21:03:00Z","last_entry_id":11},
"feeds":[{"created_at":"2023-01-06T21:13:33Z","entry_id":1,"field1":null,"field2":null,"field3":null,
"field8":"0"},{"created_at":"2023-01-06T21:13:49Z","entry_id":2,"field1":null,"field2":null,"field3":null,"field8":"0"},
{"created_at":"2023-01-06T21:14:47Z","entry_id":3,"field1":null,"field2":null,"field3":null,"field8":"0"},
{"created_at":"2023-01-06T21:15:15Z","entry_id":4,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:15:30Z","entry_id":5,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:15:45Z","entry_id":6,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:16:56Z","entry_id":7,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:17:11Z","entry_id":8,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:17:37Z","entry_id":9,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:17:52Z","entry_id":10,"field1":null,"field2":null,"field3":null,"field8":"198"},
{"created_at":"2023-01-06T21:18:07Z","entry_id":11,"field1":null,"field2":null,"field3":null,"field8":"198"}]}
*/
