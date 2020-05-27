#include "cpp_connect_c.h"
#include "mainwindow.h"
#include "extern.h"
#ifdef __cplusplus
extern "C"{
#endif

void connect_print_log(char *format)
{
    w->print_log(format);
}

#ifdef __cplusplus
}
#endif
