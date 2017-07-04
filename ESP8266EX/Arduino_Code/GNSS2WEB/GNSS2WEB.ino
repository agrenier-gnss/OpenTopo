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
//SoftwareSerial swSer(RXPin, TXPin);     //TX -> IO12 RX->IO14 on board

static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
TinyGPSCustom hdop(gps, "PUBX", 15);
TinyGPSCustom vdop(gps, "PUBX", 16);
TinyGPSCustom hAcc(gps, "PUBX", 9);
TinyGPSCustom vAcc(gps, "PUBX", 10);
TinyGPSCustom geoSep(gps, "GNGGA", 11);


ESP8266WebServer server(80);

String strData;

char strDate[16];
char strTime[16];
char strLat[32];
char strLng[32];
char strAlt[16];

unsigned long start;
char myState = 0;

void handleRoot()
{
	strData = "";

	sprintf(strDate, "%02d/%02d/%02d", gps.date.year(), gps.date.month(), gps.date.day());
	sprintf(strTime, "%02d:%02d:%02d", gps.time.hour(),gps.time.minute(), gps.time.second());

	dtostrf(gps.location.lat(), 4, 9, strLat);
	dtostrf(gps.location.lng(), 4, 9, strLng);
	dtostrf(gps.altitude.meters(), 4, 2, strAlt);

	strData += "{";

	strData = String(strData + " \"date\": \"" + strDate + "\",");
	strData = String(strData + " \"time\": \"" + strTime + "\",");
	strData = String(strData + " \"hdop\": \"" + hdop.value() + "\",");
	strData = String(strData + " \"vdop\": \"" + vdop.value() + "\",");
	strData = String(strData + " \"latitude\": \"" + strLat + "\",");
	strData = String(strData + " \"longitude\": \"" + strLng + "\",");
	strData = String(strData + " \"altitude\": \"" + strAlt + "\",");
	strData = String(strData + " \"GeoidSeparation\": \"" + geoSep.value() + "\",");
	strData = String(strData + " \"hacc\": \"" + hAcc.value() + "\",");
	strData = String(strData + " \"vacc\": \"" + vAcc.value() + "\"");
	strData += "}";
	
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
}