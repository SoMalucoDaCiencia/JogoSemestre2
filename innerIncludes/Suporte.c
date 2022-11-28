//
// Created by tais on 25/11/2022.
//

#include <innerIncludes/headers/Suporte.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

String substringToFinal(String word, int start) {
    String str = (char) malloc(strlen(word));
    strncpy(str, word + start, strlen(word));
    return str;
}

String substringFromStart(String word, int end) {
    String str = (char) malloc(strlen(word));
    strncpy(str, word, end);
    return str;
}

String substring(String word, int start, int end) {
    String str = malloc((end - start));
    strncpy(str, word + start, end - start);
    return str;
}

String StringInt(int num) {
    String ret;
    sprintf(ret, "%d", num);
    return ret;
}

bool equals(String s, String s2) {
    return strcmp(s, s2)==0;
}

char append(String initial, String append) {
    String str = (char) malloc(sizeof(char)*(strlen(initial) + strlen(append)));
    sprintf(str, "%s%s", initial, append);
    return str;
}

int IntString(String str) {
    return (int) strtol(str, (String)NULL, 10);
}

double doubleString(String s) {
    String t;
    return strtof(s, &t);
}
