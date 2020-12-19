//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-19
// PURPOSE: unit tests for the DHT12 library
//          https://github.com/RobTillaart/DHT12
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
#define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
#define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "DHT12.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  DHT12 DHT;
  fprintf(stderr, DHT12_LIB_VERSION);

  assertEqualFLoat(0, DHT.getTemperature(), 0.001);
  assertEqualFLoat(0, DHT.getHumidity(), 0.001);
  assertEqualFLoat(0, DHT.getTempOffset(), 0.001);
  assertEqualFLoat(0, DHT.getHumOffset(), 0.001);

  DHT.begin();
  assertEqual(0, DHT.read());

  assertEqualFLoat(0, DHT.getTemperature(), 0.001);
  assertEqualFLoat(0, DHT.getHumidity(), 0.001);
  assertEqualFLoat(0, DHT.getTempOffset(), 0.001);
  assertEqualFLoat(0, DHT.getHumOffset(), 0.001);
}


unittest(test_offset)
{
  DHT12 DHT;
  DHT.begin();
  
  assertEqualFLoat(0, DHT.getTempOffset(), 0.001);
  assertEqualFLoat(0, DHT.getHumOffset(), 0.001);

  for (float offset = -1.5; offset < 1.5; offset += 0.5)
  {
    DHT.setHumOffset(offset);
    DHT.setTempOffset(offset);

    assertEqualFLoat(offset, DHT.getTempOffset(), 0.001);
    assertEqualFLoat(offset, DHT.getHumOffset(), 0.001);

    assertEqualFLoat(offset, DHT.getTemperature(), 0.001);
    assertEqualFLoat(offset, DHT.getHumidity(), 0.001);
  }
}

unittest_main()

// --------
