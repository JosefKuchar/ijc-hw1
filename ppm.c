#include "ppm.h"
#include <stdio.h>
#include "error.h"

struct ppm* ppm_read(const char* filename) {
    FILE* ptr = fopen(filename, "rb");

    if (ptr == NULL) {
        warning_msg("Nepodarilo se otevrit soubor: %s\n", filename);
        return NULL;
    }
}

void ppm_free(struct ppm* p) {
    free(p->data);
    free(p);
}
