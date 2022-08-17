//
// Created by Arthur Andrade on 17/08/22.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <deps/nossaLivraria.h>

int main() {

    // Exemplo de verificação do sistema operacional usando nossa biblioteca
    printf("%d", isMAC() ? 1 : 0);
    return 0;
}
