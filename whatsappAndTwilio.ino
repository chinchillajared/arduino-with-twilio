#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

//WiFi credentials details 
char ssid[] = ":)ared";
char pass[] = "Holamundo007";

//Twilio contact details 
String toPhonenumber = "whatsapp:50689356374";
String fromPhonenumber = "whatsapp:14155238886";
String message = "Test003";

//Twilio account credetials 
String accountSID = "AC242ae1adf53d87e8e3698a64836ea826";
String authToken = "dc5bea55b5893d151da140a380a3e998";

//body of the HTTP request 
String body = "Body=" + message + "&To=" + toPhonenumber + "&From=" + fromPhonenumber;

//endPoit of the HTTP request 
String endPoint = "/2010-04-01/Accounts/" + accountSID + "/Messages.json";

//Twilio server connection details 
char server[] = "api.twilio.com";
int port = 443;

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, server, port);



void setup() {

  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
    Serial.begin(9600);
  }

  Serial.println("The serial port has been successfully initiated!");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. 
    WiFi.begin(ssid, pass);
  }

  Serial.println("successfully connected to: " + String(ssid));

  //
  Serial.println("making POST request");
  client.beginRequest();
  client.post(endPoint);
  client.sendBasicAuth(accountSID, authToken);
  client.sendHeader("Content-Type", "application/x-www-form-urlencoded");
  client.sendHeader("Content-Length", body.length());
  client.beginBody();
  client.println(body);
  client.endRequest();


  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true)
    ;
}
