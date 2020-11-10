/*
  Copyright (c) 2020, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/*!
  \file    library.h
  \brief   Library header
  \version 20201110
*/

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <intrinsics.h>

#define DATATYPE uint16_t

DATATYPE math_sum(DATATYPE a, DATATYPE b);
DATATYPE math_mul(DATATYPE a, DATATYPE b);

void debug_log(const char * format, ...);
