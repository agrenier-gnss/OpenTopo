#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <stdio.h>

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define LED_RELAY 15

const char *ssid = "ESPap";
const char *password = "thereisnospoon";

//static const int RXPin = 14, TXPin = 12;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
TinyGPSCustom vdop(gps, "PUBX", 16);
TinyGPSCustom hAcc(gps, "PUBX", 9);
TinyGPSCustom vAcc(gps, "PUBX", 10);


//SoftwareSerial swSer(RXPin, TXPin);     //TX -> IO12 RX->IO14 on board
ESP8266WebServer server(80);

String strData;

char strDate[16];
char strTime[16];
char strLat[16];
char strLng[16];
//char strAlt[16];

unsigned long start;
char myState = 0;

void handleRoot()
{
	strData = "";

	sprintf(strDate, "%02d/%02d/%02d", gps.date.year(), gps.date.month(), gps.date.day());
	sprintf(strDate, "%02d:%02d:%02d", gps.time.hour(),gps.time.minute(), gps.time.second());

	sprintf


	/*
	strData += "{";

	strData = String(strData + " \"date\": \"" + gps.date.year() + "/" + gps.date.month() + "/" + gps.date.day() + "\",");
	strData = String(strData + " \"time\": \"" + gps.time.hour() + ":" + gps.time.minute() + ":" + gps.time.second() + "\",");
	strData = String(strData + " \"hdop\": \"" + gps.hdop.value() + "\",");
	strData = String(strData + " \"vdop\": \"" + vdop.value() + "\",");
	strData = String(strData + " \"latitude\": \"" + gps.location.lat() + "\",");
	strData = String(strData + " \"longitude\": \"" + gps.location.lng() + "\",");
	strData = String(strData + " \"altitude\": \"" + gps.altitude.meters() + "\",");
	strData = String(strData + " \"hacc\": \"" + hAcc.value() + "\",");
	strData = String(strData + " \"vacc\": \"" + vAcc.value() + "\"");
	strData += "}";*/
	
	//strData = "{\"latitude\": \"51.508131\", \"longitude\": \"-0.128002\"}";

	server.send(200, "application/json; charset=utf-8", strData);
}

void setup()
{
	delay(1000);

	pinMode(LED_RELAY, OUTPUT);

	Serial.begin(GPSBaud);
	WiFi.softAP(ssid, password);

	server.on("/", handleRoot);
	server.begin();

	Serial.println("HTTP server started");

}

void loop()
{
	smartDelay(800);

	server.handleClient();
}

static void smartDelay(unsigned long ms)
{
	switch (myState)
	{
	case 1:
		if (Serial.available())
		{
			gps.encode(Serial.read());
		}
		if (millis() - start >= ms)
		{
			myState = 2;
		}
		break;
	case 2:
		digitalWrite(LED_RELAY, HIGH);
		myState = 0;
		break;
	default:
		digitalWrite(LED_RELAY, LOW);
		start = millis();
		myState = 1;
		break;
	}

	/*
	unsigned long start = millis();
	do
	{
		while (swSer.available())
			gps.encode(swSer.read());
	} while (millis() - start < ms);*/
}