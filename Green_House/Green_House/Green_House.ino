#include "SensorData.h"
#include "JsonRasberry.h"
#include "SensorData.h"
#include "JsonRasberry.h"
#include <ArduinoJson.h>
#include <MsTimer2.h>
#include "String.h"
//#include "SensorData.h"
#include "JsonRasberry.h"

SensorData Sensor;
JsonRasberry JR;//????????????? ?????? ??? ?????????? JSON ?? Rasberry

boolean stringComplete = false;
//SensorData SensorDat;
void setup(void)
{
	Serial.begin(9600);
	MsTimer2::set(5000, function); // ?????? 5 ? ???????? ???????, ?????????? ?????????? ? ???????? ? ??????????
								   // JSON ? Serial.
	pinMode(3, OUTPUT);
	pinMode(8, OUTPUT);
	digitalWrite(3, LOW);
	digitalWrite(8, LOW);
	MsTimer2::start();

}

void function()
{
	if (JR.success)
		JR.calc(Sensor);
	Sensor.calc();
}

void serialEvent()
{
	//Serial.println(JR.StrJson);
	while (Serial.available())
	{
		MsTimer2::stop();
		char inChar = (char)Serial.read();
		// Serial.println(JR.StrJson);
		JR.StrJson += inChar;
		if (inChar == '}')
		{
			// Serial.println(JR.StrJson);
			stringComplete = true;
			// return;
		}
	}
}
void inputJson()
{
	//Serial.println(JR.StrJson.length());
	JR.StrJson.remove(0, JR.StrJson.indexOf('\'') + 1);
	JR.StrJson.remove(JR.StrJson.indexOf('\'', 1), JR.StrJson.length());
	//Serial.println(JR.StrJson);
	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(JR.StrJson);
	if (!root.success()) {
		//Serial.println("parseObject() failed");
	}
	else
	{
		//Serial.println("parseObject success");
		JR.AddData((int)root["SoilMoistureLimits"][0], (int)root["SoilMoistureLimits"][1], (bool)root["Light"],
			(int)root["AirTemperatureLimits"][0], (int)root["AirTemperatureLimits"][1],
			(int)root["SoilTemperatureLimits"][0], (int)root["SoilTemperatureLimits"][1]);
		MsTimer2::start();
	}
}
void loop(void) {
	//8 ????? 3 ???????????

	//  digitalWrite(pin, value)
	if (stringComplete) {
		inputJson();// ????????? ???????????? json, ??? ?? ????? ?????????? ???????.
		JR.StrJson = "";// ??????? ??????:
		stringComplete = false;
	}
}

