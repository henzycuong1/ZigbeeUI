#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <poll.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <signal.h>
#include <execinfo.h>
#include <string.h>

#include <QMainWindow>
#include "mainwindow.h"

#include "timer_utils.h"
#include "polling.h"
#include "socket_interface.h"
#include "user_interface.h"
#include "network_info_engine.h"
#include "device_list_engine.h"
#include "data_structures.h"
#include "ota_engine.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/

#define CALL_STACK_TRACE_DEPTH 10

/*******************************************************************************
 * Functions
 ******************************************************************************/

void unregister_segmentation_fault_handler(void)
{
    struct sigaction action;

    action.sa_flags = 0;
    action.sa_handler = SIG_DFL;
    memset(&action.sa_mask, 0, sizeof(action.sa_mask));
    action.sa_restorer = NULL;

    sigaction(SIGSEGV, &action, NULL);
}

void segmentation_fault_handler(int signum, siginfo_t *info, void *context)
{
    void *array[CALL_STACK_TRACE_DEPTH];
    size_t size;

    fprintf(stderr, "ERROR: signal %d was trigerred:\n", signum);

    fprintf(stderr, "  Fault address: %p\n", info->si_addr);

    switch (info->si_code)
    {
        case SEGV_MAPERR:
            fprintf(stderr, "  Fault reason: address not mapped to object\n");
            break;
        case SEGV_ACCERR:
            fprintf(stderr, "  Fault reason: invalid permissions for mapped object\n");
            break;
        default:
            fprintf(stderr, "  Fault reason: %d (this value is unexpected).\n", info->si_code);
            break;
    }

    // get pointers for the stack entries
    size = backtrace(array, CALL_STACK_TRACE_DEPTH);

    if (size == 0)
    {
        fprintf(stderr, "Stack trace unavailable\n");
    }
    else
    {
        fprintf(stderr, "Stack trace folows%s:\n", (size < CALL_STACK_TRACE_DEPTH) ? "" : " (partial)");

        // print out the stack frames symbols to stderr
        backtrace_symbols_fd(array, size, STDERR_FILENO);
    }


    /* unregister this handler and let the default action execute */
    fprintf(stderr, "Executing original handler...\n");
    unregister_segmentation_fault_handler();
}

void register_segmentation_fault_handler(void)
{
    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = segmentation_fault_handler;
    memset(&action.sa_mask, 0, sizeof(action.sa_mask));
    action.sa_restorer = NULL;

    if (sigaction(SIGSEGV, &action, NULL) < 0)
    {
        perror("sigaction");
    }
}


int zigbee_init(char * nwk_manager_server_hostname, u_short nwk_manager_server_port, char * gateway_server_hostname, u_short gateway_server_port, char * ota_server_hostname, u_short ota_server_port)
{
//    printf("Hello World!\n");
    register_segmentation_fault_handler();

    ds_init();

    if (si_init(nwk_manager_server_hostname, nwk_manager_server_port, gateway_server_hostname, gateway_server_port, ota_server_hostname, ota_server_port) == 0)
    {
        while (polling_process_activity());

        //si_deinit();
    }

    unregister_segmentation_fault_handler();
    return 0;
}
