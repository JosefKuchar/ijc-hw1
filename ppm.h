// ppm.h
// Řešení IJC-DU1, příklad a), 20.3.2111
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#ifndef PPM_H_INCLUDED
#define PPM_H_INCLUDED

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];  // RGB bajty, celkem 3*xsize*ysize
};

/*
 * načte obsah PPM souboru do touto funkcí dynamicky
 * alokované struktury. Při chybě formátu použije funkci warning_msg
 * a vrátí NULL.
 */
struct ppm* ppm_read(const char* filename);

/*
 * uvolní paměť dynamicky alokovanou v ppm_read
 */
void ppm_free(struct ppm* p);

#endif  // PPM_H_INCLUDED
