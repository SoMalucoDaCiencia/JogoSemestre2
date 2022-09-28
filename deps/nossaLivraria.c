//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdbool.h>

bool isMAC() {
#ifdef __APPLE__
    return 1;
#endif
    return 0;
}