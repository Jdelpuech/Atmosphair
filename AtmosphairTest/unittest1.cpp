#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Atmosphair/DataSet.h"
#include "../Atmosphair/ApplicationManager.h"
#include "../Atmosphair/Display.h"
#include "../Atmosphair/LogManager.h"
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

		/*TEST_METHOD(TestImportFiles)
		{
		 

		}*/

	};
}