#ifndef RTWEEKEND_H
#define ETWEEKEND_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180;
}

inline double random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (max-min) * random_double();
}

inline int random_int(int min, int max)
{
    return int(random_double(min, max+1));
}

#include "ray.h"
#include "interval.h"
#include "color.h"
#include "vec3.h"


#endif