#include "cpp_connect_c.h"
#include "mainwindow.h"
#include "extern.h"
#ifdef __cplusplus
extern "C"{
#endif

static MainWindow *mainwindow_instance = NULL;

void lazyConnect(){
    if(mainwindow_instance == NULL){
        mainwindow_instance = new MainWindow;
    }
}

void connect_print_log(char *format)
{
    w->print_log(format);
}

#ifdef __cplusplus
}
#endif
