/* ALPHA BETA */
#ifndef _ALPHA_BETA_H
#define _ALPHA_BETA_H

#include <algorithm>

#ifdef USE_CILK

#include <cilk/cilk.h>
#include <cilk/reducer_min.h>
#include <cilk/reducer_max.h>

#endif

#include "fourinrow.hpp"

int8_t alpha_beta(FourInRow, int, int8_t, int8_t);
void alpha_beta_par(FourInRow, int, int8_t, int8_t, int8_t*);

#endif
