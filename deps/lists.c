//
// Created by Arthur andrade on 07/10/22.
//
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <deps/nossaLivraria.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <unistd.h>
#include <allegro5/allegro_primitives.h>

struct HyperList {
    int listSize;
    void* volumes;
} HyperList;

struct HyperList NewHyperList() {
    struct HyperList l;
    l.listSize = 0;
    l.volumes = malloc(0);
    return l;
}

struct HyperList NewHyperList(int size) {
    struct HyperList l;
    l.listSize = size;
    l.volumes = calloc(size);
    return l;
}

void clear(struct HyperList* list) {
    for (int i=0; i<list->listSize; i++) {
        free(&list->volumes[i]);
    }
    list->listSize = 0;
}

// Insert "it" at current position
struct HyperList* add(struct HyperList *list, void* newElement) {
    void* retorno = malloc(sizeof(list) + sizeof(newElement));
    for (int i=0; i<; ++i) {

    }

    return list;
}

// Remove and return the current element
void* removeAt(struct HyperList l, int at) {

}

void* getValue(struct HyperList l, int at) {
    return &l.volumes[at];
}


