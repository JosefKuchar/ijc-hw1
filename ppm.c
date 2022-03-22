// ppm.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// Image size hard limits
#define MAX_WIDTH 8000
#define MAX_HEIGHT 8000

void ppm_free(struct ppm* p) {
    free(p);
}

struct ppm* ppm_read(const char* filename) {
    // Open file
    FILE* ptr = fopen(filename, "rb");

    // Check if file was opened
    if (ptr == NULL) {
        warning_msg("Error reading file: %s\n", filename);
        goto error_open;
    }

    // Read size of the image and check if header is valid
    unsigned xsize, ysize;
    if (fscanf(ptr, "P6\n%u %u\n255\n", &xsize, &ysize) != 2) {
        warning_msg("Wrong file format\n");
        goto error_setup;
    }

    // Check if image is too big
    if (xsize > MAX_WIDTH || ysize > MAX_HEIGHT) {
        warning_msg("Image is too big, max size: %dx%d\n", MAX_WIDTH, MAX_HEIGHT);
        goto error_setup;
    }

    // Allocate memory for ppm structure
    struct ppm* ppm = malloc(sizeof(struct ppm) + xsize * ysize * 3);
    if (ppm == NULL) {
        warning_msg("Malloc failed\n");
        goto error_setup;
    }

    ppm->xsize = xsize;
    ppm->ysize = ysize;

    // Read image data and check if everything was read
    const unsigned data_size = xsize * ysize;
    if (fread(ppm->data, 3, data_size, ptr) != data_size || getc(ptr) != EOF) {
        warning_msg("Image data size doesn't match metadata\n");
        goto error_read;
    }

    fclose(ptr);

    return ppm;

// Error handling labels
error_read:
    ppm_free(ppm);
error_setup:
    fclose(ptr);
error_open:
    return NULL;
}
