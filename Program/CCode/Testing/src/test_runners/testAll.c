#include "unity_fixture.h"

static void RunAllTests(void){
    RUN_TEST_GROUP(UnrecommendedInput);
    RUN_TEST_GROUP(InvalidInput);
    RUN_TEST_GROUP(LoadParams);
    RUN_TEST_GROUP(VerifyOutput);
    RUN_TEST_GROUP(Energy);
    RUN_TEST_GROUP(CompareFortran);
    RUN_TEST_GROUP(CompareMatlab);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
