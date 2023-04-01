// Created by Jared Chinchilla on 03/27/2023: @chinchillajared

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

//WiFi credentials details 
char ssid[] = "your_ssid";
char pass[] = "your_password";

//Twilio contact details 
String toPhonenumber = "to_phonenumber"; //If you want to use whatsapp first, add Whatsapp at the begining and dont enter the + sign, eg: whatsapp:14155238886
String fromPhonenumber = "from_phonenumber"; //If you want to use whatsapp first, add Whatsapp at the begining and dont enter the + sign, eg: whatsapp:14155238886
String message = "message";

//Twilio account credetials 
String accountSID = "your_account_sid";
String authToken = "your_auth_token";

//body of the HTTP request 
String body = "Body=" + message + "&To=" + toPhonenumber + "&From=" + fromPhonenumber;

//endPoit of the HTTP request 
String endPoint = "/2010-04-01/Accounts/" + accountSID + "/Messages.json";

//Twilio server connection details 
char server[] = "api.twilio.com";
int port = 443;

//Start coonection to the server 
WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, server, port);



void setup() {

  //Satart serial port 
  while (!Serial) {
    Serial.begin(9600);
  }

  Serial.println("The serial port has been successfully initiated!");

  //Start connection to the WiFi 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. 
    WiFi.begin(ssid, pass);
  }

  Serial.println("successfully connected to: " + String(ssid));

  //Make the post request to Twilio API
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
  //Do nothing ever 
  while (true)
    ;
}
