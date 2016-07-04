#ifndef MINMAX_H
#define MINMAX_H

#include <algorithm>
#include <set>

using namespace std;

#ifdef USE_CILK

#include <cilk/cilk.h>
#include <cilk/reducer_max.h>
#include <cilk/reducer_min.h>

#endif

#include "morpion.hpp"

int8_t min_max(Morpion);

#endif
