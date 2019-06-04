#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Atmosphair/DataSet.h"
#include "../Atmosphair/ApplicationManager.h"
#include "../Atmosphair/Display.h"
#include "../Atmosphair/LogManager.h"
#include "../Atmosphair/FileManager.h"
#include <iostream>

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

		TEST_METHOD(TestOpenSaveTrue)
		{
			DataSet dsTest=DataSet();
			FileManager fmTest = FileManager();
			bool result = fmTest.openSave(&dsTest);

			Assert::AreEqual(true, result);
		}

		

		TEST_METHOD(TestSaveSensorTrue)
		{
			DataSet dsTest = DataSet();
			FileManager fmTest = FileManager();
			bool result = fmTest.save(&dsTest,"sensors2.csv", 0);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestSave2True)
		{
			DataSet dsTest = DataSet();
			FileManager fmTest = FileManager();
			bool result = fmTest.save(&dsTest,"data2.csv", 1);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestImportDataFromFileTrue)
		{
			DataSet dsTest = DataSet();
			FileManager fmTest = FileManager();
			bool result = fmTest.importDataFromFile(&dsTest, "sensors.csv", 0);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(TestImportDataFromFileFalse)
		{
			DataSet dsTest = DataSet();
			FileManager fmTest = FileManager();
			bool result = fmTest.importDataFromFile(&dsTest, "inexistant.csv", 2);

			Assert::AreEqual(false, result);
		}
	};

	TEST_CLASS(SensorTest)
	{
	public:

		TEST_METHOD(TestCalculateDistance)
		{
			int result = (int)DataSet::calculateDistance(-8.157588883, -34.76924879, -30.06473877, -76.34391476);

			Assert::AreEqual(4959, result);
		}



	};

}