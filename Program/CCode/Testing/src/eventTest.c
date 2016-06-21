#include "unity.h"
#include "unity_fixture.h"
#include "parameters.h"
#include "load_params.h"
#include "event.h"

TEST_GROUP(Event);

TEST_SETUP(Event){
}

TEST_TEAR_DOWN(Event){
}

TEST(Event, testEvent1a){
    struct parameters params;
    params = load_params("test.in");
    double tempP = 40.9;
    double endval;
    endval = event1(tempP, params);
    TEST_ASSERT_EQUAL_FLOAT(-3.3, endval);
}

TEST(Event, testEvent1b){
    struct parameters params;
    params = load_params("test.in");
    double tempP = 44.2;
    double endval;
    endval = event1(tempP, params);
    TEST_ASSERT_EQUAL_FLOAT(0, endval);
}

TEST(Event, testEvent2a){
    struct parameters params;
    params = load_params("test.in");
    double latentHeat = 0;
    double endval;
    endval = event2(latentHeat, params);
    TEST_ASSERT_EQUAL_FLOAT(-1, endval);
}

TEST(Event, testEvent2b){
    struct parameters params;
    params = load_params("test.in");
    double latentHeat = 600000;
    double endval;
    endval = event2(latentHeat, params);
    TEST_ASSERT_EQUAL_FLOAT(-0.94368344086667430068912696192813, endval);
}

TEST(Event, testEvent2c){
    struct parameters params;
    params = load_params("test.in");
    double latentHeat = 10654060;
    double endval;
    endval = event2(latentHeat, params);
    TEST_ASSERT_EQUAL_FLOAT(0, endval);
}
