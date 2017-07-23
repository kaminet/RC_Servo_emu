#include <Arduino.h>

#include <ESP8266WiFi.h>
#include "FS.h"
#include <WiFiClient.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include "FSWebServerLib.h"
#include <Hash.h>


void  callbackJSON(AsyncWebServerRequest *request)
{
	//its possible to test the url and do different things, 
	String values = "{\"message\": \"Hello world! \" , \"url\":\"" + request->url() + "\"}";
	request->send(200, "text/plain", values);
	values = "";
}

void  callbackREST(AsyncWebServerRequest *request)
{
	//its possible to test the url and do different things, 
	String values = "message:Hello world! \nurl:" + request->url() + "\n";
	request->send(200, "text/plain", values);
	values = "";
}

void  callbackPOST(AsyncWebServerRequest *request)
{

	//its possible to test the url and do different things, 
	String values = "url:" + request->url() + "\n";
	if (request->args() > 0)  //process args
	{
		for (uint8_t i = 0; i < request->args(); i++) {
			values += request->argName(i) + ":" + request->arg(i) + "\n";
		}
	}


	request->send(200, "text/plain", values);
	values = "";
}


void setup() {
    // WiFi is started inside library
    SPIFFS.begin(); // Not really needed, checked inside library and started if needed
    ESPHTTPServer.begin(&SPIFFS);
    /* add setup code here */

	//set optioanl callback
	ESPHTTPServer.setJSONCallback(callbackJSON);

	//set optioanl callback
	ESPHTTPServer.setRESTCallback(callbackREST);

	//set optioanl callback
	ESPHTTPServer.setPOSTCallback(callbackPOST);


}

void loop() {
    /* add main program code here */

    // DO NOT REMOVE. Attend OTA update from Arduino IDE
    ESPHTTPServer.handle();	
}
