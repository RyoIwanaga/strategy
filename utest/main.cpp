#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

// targets
#include "../Util.h"
#include "../hex.h"

#include <stdio.h>
#include <set>

NS_USING_STRATEGY;

/*** Template
 
class utilTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(utilTest);
	CPPUNIT_TEST(addCircle);
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}
	void testDown()
	{
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(utilTest);
  */
#ifdef a
class utilTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(utilTest);
//	CPPUNIT_TEST(addCircle);
	CPPUNIT_TEST_SUITE_END();

protected:
	void addCircle()
	{
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, 1, 5), 1);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, 6, 5), 0);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(3, 5, 5), 2);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(3, 12, 5), 3);
		
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, 1, 4, -1), 1);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, 5, 4, -1), -1);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, 12, 4, -1), 0);

		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(3, -1, 5), 2);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(3, -6, 5), 3);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(3, -12, 5), 3);

		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, -1, 3, -1), -1);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, -5, 3, -1), 0);
		CPPUNIT_ASSERT_EQUAL(util::math::addCircle(0, -10, 3, -1), 0);

		//CPPUNIT_ASSERT_EQUAL(util::addCircle(3, -2, 5), 1);
		//CPPUNIT_ASSERT_EQUAL(util::addCircle(3, -5, 5), 4);
	}

public:
	void setUp()
	{
	}
	void testDown()
	{
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(utilTest);
#endif

class TestHex : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TestHex);
	CPPUNIT_TEST(testToV2);
	CPPUNIT_TEST(testFromV2);
	CPPUNIT_TEST_SUITE_END();

	static const uint HEIGHT = 8;
	static const uint WIDTH = 10;

protected:
	void testToV2()
	{
		CPPUNIT_ASSERT(hex::HexVec2(3, 0) == hex::HexVec2(3, 0));
		CPPUNIT_ASSERT(hex::HexVec2(0, 0) == hex::toV2(0, HEIGHT, WIDTH));
		CPPUNIT_ASSERT(hex::HexVec2(3, 0) == hex::toV2(3, HEIGHT, WIDTH));
		CPPUNIT_ASSERT(hex::HexVec2(3, 1) == hex::toV2(13, HEIGHT, WIDTH));
	}

	void testFromV2()
	{
		CPPUNIT_ASSERT(0 == hex::fromV2(hex::HexVec2(0, 0), HEIGHT, WIDTH));
		CPPUNIT_ASSERT(3 == hex::fromV2(hex::HexVec2(3, 0), HEIGHT, WIDTH));
		CPPUNIT_ASSERT(13 == hex::fromV2(hex::HexVec2(3, 1), HEIGHT, WIDTH));
	}

//	void neighbor()
//	{
//		/*  width = 3
//		 *
//		 *     0 1 2
//		 *	 +-------
//		 * 0 | 0 1 2
//		 * 1 |  3 4 5
//		 * 2 | 6 7 8
//		 * 3 |  9 a b 
//		 */
//		const int height = 4;
//		const int width = 3;
//
//		std::set<int> result;
//		std::set<int> a;
//
//
//		auto l = hex::neighbors(0, height, width, false);
//
//		result = listToSet(hex::neighbors(0, height, width, false));
//		a = std::set<int>{ 1, 3 };		
//		CPPUNIT_ASSERT(result == a);
//
//		for (auto item : result)
//			printf("%d ", item);
//		printf("\n");
//
//		//std::cout << result << std::endl;
//	}
//
//	std::set<int> listToSet(const std::list<int>& lst)
//	{
//		std::set<int> s;
//
//		for (auto item : lst)
//			s.insert(item);
//
//		return s;
//	} */

public:
	void setUp()
	{
	
	}
	void testDown()
	{
	
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestHex);



int main(int argc, char const *argv[]){

	CPPUNIT_NS::TestResult controller;

	//結果収集
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener(&result);

	//途中結果の収集
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener(&progress);

	//テストを走らせる。テストを入れて走る
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run(controller);

	//結果を標準出力にする。
	CPPUNIT_NS::CompilerOutputter outputter(&result,CPPUNIT_NS::stdCOut());
	outputter.write();

	return result.wasSuccessful() ? 0 : 1;
}
