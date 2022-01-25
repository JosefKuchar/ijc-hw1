#include "eratosthenes.h"
#include "ppm.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        // TODO error
    }

    struct ppm* ppm = ppm_read(argv[1]);

    ppm_free(ppm);
    return 0;
}
