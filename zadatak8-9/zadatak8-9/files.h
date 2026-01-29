#pragma once
#ifndef FILES_H
#define FILES_H

#include "tree.h"
#include <stdio.h>

treePos Load(treePos root, const char* filename);
int WriteInorderFile(treePos root, const char* filename);

#endif
