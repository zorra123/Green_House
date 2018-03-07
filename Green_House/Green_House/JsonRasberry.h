// JsonRasberry.h

#ifndef _JSONRASBERRY_h
#define _JSONRASBERRY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <MsTimer2.h>
#include "SensorData.h"
class JsonRasberry
{
public:
	String StrJson;
	JsonRasberry();
	void calc(SensorData &Sensor);
	void AddData(int, int, bool, int, int, int, int);
	bool success;
private:
	int SoilMoistureMin;
	int SoilMoistureMax;

	bool light;

	int AirTemperatureMin;
	int AirTemperatureMax;

	int SoilTemperatureMin;
	int SoilTemperatureMax;
};

#endif

