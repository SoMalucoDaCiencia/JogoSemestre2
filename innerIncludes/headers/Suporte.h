//
// Created by tais on 25/11/2022.
//

#ifndef JOGOSEMESTRE2_SUPORTE_H
#define JOGOSEMESTRE2_SUPORTE_H

#include <stdbool.h>
#include <string.h>

typedef char* String;

String substringToFinal(String word, int start);

String substringFromStart(String word, int end);

String substring(String word, int start, int end);

String StringInt(int num);

bool equals(String s, String s2);

int IntString(String str);

double doubleString(String s);

#endif //JOGOSEMESTRE2_SUPORTE_H
