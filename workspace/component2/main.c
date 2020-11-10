/*
  Copyright (c) 2020, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/*!
  \file    main.c
  \brief   Component 2
  \version 20201110
*/

#include "library.h"

int main()
{
  const DATATYPE x = 10000;
  const DATATYPE y = 20000;
  const DATATYPE z = 30000;
        DATATYPE sum;
        DATATYPE mul;

  debug_log("Component 2!\r\n");

  sum = math_sum(x, y);
  debug_log("Sum = %d\r\n", sum);

  mul = math_mul(sum, z);
  debug_log("Mul = %d\r\n", mul);

  debug_log("Finished Execution!\r\n");

  return 0;
}
