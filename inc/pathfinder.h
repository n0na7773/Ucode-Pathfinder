#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

bool checknum(const char *num);
bool checkword(const char *word);
bool correct_line(const char *from, const char *to, const char *dist);

void parse(const char *filename);

#endif
