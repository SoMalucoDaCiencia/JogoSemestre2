//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdbool.h>
#include <string.h>

bool isMAC() {
    return __APPLE__ ? "true" : "false";
}