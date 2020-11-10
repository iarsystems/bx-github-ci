/*
  Copyright (c) 2020, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/*!
  \file    main.c
  \brief   Component 1
  \version 20201110
*/

#include "library.h"

int main()
{
  const uint16_t x = 101;
  const uint16_t y = 202;
  const uint16_t z = 303;
        uint16_t sum;
        uint16_t mul;

  debug_log("Component 1!\r\n");

  sum = math_sum(x, y);
  debug_log("Sum = %d\r\n", sum);

  mul = math_mul(sum, z);
  debug_log("Mul = %d\r\n", mul);

  debug_log("Finished execution!\r\n");

  return 0;
}
