#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define MAX_WIDTH 8000
#define MAX_HEIGHT 8000

void ppm_free(struct ppm* p) {
    if (p != NULL) {
        free(p);
    }
}
struct ppm* ppm_read(const char* filename) {
    FILE* ptr = fopen(filename, "rb");

    if (ptr == NULL) {
        warning_msg("Error reading file: %s\n", filename);
        return NULL;
    }

    unsigned xsize, ysize;

    if (fscanf(ptr, "P6\n%u %u\n255\n", &xsize, &ysize) != 2) {
        warning_msg("Wrong file format\n");
        fclose(ptr);
        return NULL;
    }

    if (xsize > MAX_WIDTH || ysize > MAX_HEIGHT) {
        warning_msg("Image is too big, max size: %dx%d", MAX_WIDTH, MAX_HEIGHT);
        fclose(ptr);
        return NULL;
    }

    struct ppm* ppm = malloc(sizeof(struct ppm) + xsize * ysize * 3);

    if (ppm == NULL) {
        warning_msg("Malloc failed\n");
        fclose(ptr);
        return NULL;
    }

    ppm->xsize = xsize;
    ppm->ysize = ysize;

    const unsigned data_size = xsize * ysize;
    if (fread(ppm->data, 3, data_size, ptr) != data_size || getc(ptr) != EOF) {
        warning_msg("Image data size doesn't math metadata\n");
        fclose(ptr);
        ppm_free(ppm);
        return NULL;
    }

    fclose(ptr);

    return ppm;
}
