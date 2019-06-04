#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Atmosphair/DataSet.h"
#include "../Atmosphair/ApplicationManager.h"
#include "../Atmosphair/Display.h"
#include "../Atmosphair/LogManager.h"
#include "../Atmosphair/FileManager.h"
#include <ctime>
#include <iostream>

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
		//float (time_t t, string type);
		DataSet dsTest = DataSet();
		FileManager fmTest = FileManager();
		bool openSave = fmTest.openSave(&dsTest);
		Sensor s = *dsTest.getSensorById("Sensor0");
		
		

		TEST_METHOD(TestcalculateMoyenneGaz)
		{
			struct tm format_t;
			format_t.tm_mday = 1;
			format_t.tm_mon = 0;
			format_t.tm_year = 2017 - 1900;
			time_t date = mktime(&format_t);
			float result = s.calculateMoyenneGaz(date,"SO2" );

			Assert::AreEqual(result, result);
		}



	};

}