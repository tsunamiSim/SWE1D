/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_FWaveTest_init = false;
#include "/home/ludwig/SWE1D/CxxTests/FWave_testsuite.t.h"

static FWaveTest suite_FWaveTest;

static CxxTest::List Tests_FWaveTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FWaveTest( "CxxTests/FWave_testsuite.t.h", 3, "FWaveTest", suite_FWaveTest, Tests_FWaveTest );

static class TestDescription_suite_FWaveTest_test_output : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FWaveTest_test_output() : CxxTest::RealTestDescription( Tests_FWaveTest, suiteDescription_FWaveTest, 6, "test_output" ) {}
 void runTest() { suite_FWaveTest.test_output(); }
} testDescription_suite_FWaveTest_test_output;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
