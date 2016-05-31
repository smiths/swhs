#include <stdio.h>
#include <stdlib.h>
#include "verify_params.h"

int main()
{
    struct parameters params;
    params = load_params("test.in");

    verify_params(params);

    return 0;
}
