#ifndef __AFFINE_H__
#define __AFFINE_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#ifdef __cplusplus
extern "C" {
#endif

void translation(Surface *surface, Point axis_translated, Point *axis_prev);
void rotation(Surface *surface, Point rotation_angle, Point *prev_angle);

#ifdef __cplusplus
}
#endif

#endif  // __AFFINE_H__