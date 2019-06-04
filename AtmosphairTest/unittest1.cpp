#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Atmosphair/DataSet.h"
#include "../Atmosphair/ApplicationManager.h"
#include "../Atmosphair/Display.h"
#include "../Atmosphair/LogManager.h"
#include "../Atmosphair/FileManager.h"
#include <ctime>
#include <iostream>
#include <string>

using namespace std ; 
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AtmosphairTest
{		
	TEST_CLASS(DataSetTest)
	{
	public:
		
		TEST_METHOD(TestCalculateDistance)
		{
			int result = (int)DataSet::calculateDistance(-8.157588883, -34.76924879, -30.06473877, - 76.34391476);
			
			Assert::AreEqual(4959,result);
		}



		

	};

	TEST_CLASS(FileManagerTest)
	{
	public:
		DataSet dsTest = DataSet();
		FileManager fmTest = FileManager();
		TEST_METHOD(TestOpenSaveTrue)
		{
			bool result = fmTest.openSave(&dsTest);
			Assert::AreEqual(true, result);
		}

		

		TEST_METHOD(TestSaveSensorTrue)
		{
			bool result = fmTest.save(&dsTest,"sensors2.csv", 0);
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestSave2True)
		{
			bool result = fmTest.save(&dsTest,"data2.csv", 1);
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestImportDataFromFileTrue)
		{
			bool result = fmTest.importDataFromFile(&dsTest, "sensors.csv", 0);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(TestImportDataFromFileFalse)
		{
			bool result = fmTest.importDataFromFile(&dsTest, "inexistant.csv", 2);
			Assert::AreEqual(false, result);
		}
	};
	

	TEST_CLASS(SensorTest)
	{
	public:
		
		DataSet dsTest = DataSet();

		TEST_METHOD(TestcalculateMoyenneGaz)
		{
			struct tm instant;
			instant.tm_mon = 1 - 1;
			instant.tm_mday = 1;
			instant.tm_year = 2017 - 1900;
			instant.tm_hour = 1;
			instant.tm_min = 0;
			instant.tm_sec = 0;
			time_t time = mktime(&instant);

			Data * data_0 = new Data(time, 67.9284748555273, "Sensor0", "O3");
			Data * data_1 = new Data(time, 98.979984192197, "Sensor0", "NO2");
			Data * data_2 = new Data(time, 119.423041339039, "Sensor0", "SO2");
			Data * data_3 = new Data(time, 16.7564963001065, "Sensor0", "PM10");
			instant.tm_hour += 1;
			time = mktime(&instant);
			Data * data_4 = new Data(time, 36.7797600526823, "Sensor0", "O3");
			Data * data_5 = new Data(time, 80.2280346451481, "Sensor0", "NO2");
			Data * data_6 = new Data(time, 38.151540049253, "Sensor0", "SO2");
			Data * data_7 = new Data(time, 1.99603267330184, "Sensor0", "PM10");

			Sensor sensor_0 = Sensor("Sensor0", (float)-8.15758888291083, (float)-34.7692487876719, "0");
			sensor_0.addData(data_0);
			sensor_0.addData(data_1);
			sensor_0.addData(data_2);
			sensor_0.addData(data_3);
			sensor_0.addData(data_4);
			sensor_0.addData(data_5);
			sensor_0.addData(data_6);
			sensor_0.addData(data_7);

			struct tm format_t;
			format_t.tm_mday = 1;
			format_t.tm_mon = 0;
			format_t.tm_year = 2017 - 1900;
			format_t.tm_hour = 0;
			format_t.tm_min = 0;
			format_t.tm_sec = 0;
			
			time_t date = mktime(&format_t);
			string f = "O3";
			float result = sensor_0.calculateMoyenneGaz(date,f);

			float c = 52.3541;

			Assert::AreEqual(c,result, (float)0.01, L"Basic test failed", LINE_INFO() );

		}



	};

}