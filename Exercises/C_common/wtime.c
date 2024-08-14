
#ifdef _OPENMP
#include <omp.h>
#else
#include <windows.h>
#endif

#include <stdlib.h>

double wtime()
{
#ifdef _OPENMP
    /* Use omp_get_wtime() if we can */
    return omp_get_wtime();
#else
    /* Use a Windows-specific timer */
    static LARGE_INTEGER start;
    static LARGE_INTEGER frequency;
    static int initialized = 0;

    if (!initialized) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        initialized = 1;
    }

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (double)(now.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
#endif
}

    
