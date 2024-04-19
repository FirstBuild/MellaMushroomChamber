/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef MACROS_H
#define MACROS_H

#define MIN_MAX_BOUND(_x, _min, _max)                          (((_x) >= (_min)) ? (((_x) <= (_max)) ? (_x) : (_max)) : (_min))
#define VALUE_IN_BOUNDS(_x, _min, _max)                        (((_x) >= (_min)) && ((_x) <= (_max)))
#define CHECK_BIT(_x, _pos)                                    ((_x) & (1U << (_pos)))

#endif   // MACROS_H
