#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Event){
    RUN_TEST_CASE(Event, testEvent1a);
    RUN_TEST_CASE(Event, testEvent1b);
    RUN_TEST_CASE(Event, testEvent2a);
    RUN_TEST_CASE(Event, testEvent2b);
    RUN_TEST_CASE(Event, testEvent2c);
}
