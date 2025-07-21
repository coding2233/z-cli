#include "utf8_console.h"

#ifdef _WIN32
void initialize_utf8_console_windows();
#endif

void initialize_utf8_console()
{
#ifdef _WIN32
    initialize_utf8_console_windows();
#endif
}