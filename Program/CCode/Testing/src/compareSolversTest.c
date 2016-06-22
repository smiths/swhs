#include "unity.h"
#include "unity_fixture.h"
#include "parameters.h"
#include "load_params.h"
#include "PCM_ErrorC.h"


TEST_GROUP(CompareSolvers);

TEST_SETUP(CompareSolvers){
}

TEST_TEAR_DOWN(CompareSolvers){
}

TEST(CompareSolvers, testCompareSolvers1){
    struct parameters params;
    params = load_params("Testing/src/compareSolvers/cv01.in");
    double errTw, errTp, errEw, errEp;
    double delta = 0.0001;
    errTw = PCM_ErrorC("Testing/src/compareSolvers/cv01.out", "Testing/src/compareSolvers/ark01.out", "TWat", params);
    errTp = PCM_ErrorC("Testing/src/compareSolvers/cv01.out", "Testing/src/compareSolvers/ark01.out", "TPCM", params);
    errEw = PCM_ErrorC("Testing/src/compareSolvers/cv01.out", "Testing/src/compareSolvers/ark01.out", "EWat", params);
    errEp = PCM_ErrorC("Testing/src/compareSolvers/cv01.out", "Testing/src/compareSolvers/ark01.out", "EPCM", params);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTw, "Water temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTp, "PCM temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEw, "Water energy");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEp, "PCM energy");
}

TEST(CompareSolvers, testCompareSolvers2){
    struct parameters params;
    params = load_params("Testing/src/compareSolvers/cv02.in");
    double errTw, errTp, errEw, errEp;
    double delta = 0.0001;
    errTw = PCM_ErrorC("Testing/src/compareSolvers/cv02.out", "Testing/src/compareSolvers/ark02.out", "TWat", params);
    errTp = PCM_ErrorC("Testing/src/compareSolvers/cv02.out", "Testing/src/compareSolvers/ark02.out", "TPCM", params);
    errEw = PCM_ErrorC("Testing/src/compareSolvers/cv02.out", "Testing/src/compareSolvers/ark02.out", "EWat", params);
    errEp = PCM_ErrorC("Testing/src/compareSolvers/cv02.out", "Testing/src/compareSolvers/ark02.out", "EPCM", params);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTw, "Water temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTp, "PCM temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEw, "Water energy");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEp, "PCM energy");
}


TEST(CompareSolvers, testCompareSolvers3){
    struct parameters params;
    params = load_params("Testing/src/compareSolvers/cv03.in");
    double errTw, errTp, errEw, errEp;
    double delta = 0.0001;
    errTw = PCM_ErrorC("Testing/src/compareSolvers/cv03.out", "Testing/src/compareSolvers/ark03.out", "TWat", params);
    errTp = PCM_ErrorC("Testing/src/compareSolvers/cv03.out", "Testing/src/compareSolvers/ark03.out", "TPCM", params);
    errEw = PCM_ErrorC("Testing/src/compareSolvers/cv03.out", "Testing/src/compareSolvers/ark03.out", "EWat", params);
    errEp = PCM_ErrorC("Testing/src/compareSolvers/cv03.out", "Testing/src/compareSolvers/ark03.out", "EPCM", params);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTw, "Water temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTp, "PCM temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEw, "Water energy");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEp, "PCM energy");
}


TEST(CompareSolvers, testCompareSolvers4){
    struct parameters params;
    params = load_params("Testing/src/compareSolvers/cv04.in");
    double errTw, errTp, errEw, errEp;
    double delta = 0.0001;
    errTw = PCM_ErrorC("Testing/src/compareSolvers/cv04.out", "Testing/src/compareSolvers/ark04.out", "TWat", params);
    errTp = PCM_ErrorC("Testing/src/compareSolvers/cv04.out", "Testing/src/compareSolvers/ark04.out", "TPCM", params);
    errEw = PCM_ErrorC("Testing/src/compareSolvers/cv04.out", "Testing/src/compareSolvers/ark04.out", "EWat", params);
    errEp = PCM_ErrorC("Testing/src/compareSolvers/cv04.out", "Testing/src/compareSolvers/ark04.out", "EPCM", params);
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTw, "Water temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errTp, "PCM temperature");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEw, "Water energy");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, 0, errEp, "PCM energy");
}
