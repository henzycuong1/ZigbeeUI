#include "zigbee.h"
#include "user_interface.h"
#define CALL_STACK_TRACE_DEPTH 10
Q_DECLARE_METATYPE(network_info_t)
Q_DECLARE_METATYPE(device_info_t)
zigbee::zigbee(QObject *parent) : QObject(parent)
{

}

void zigbee::register_segmentation_fault_handler()
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

void zigbee::segmentation_fault_handler(int signum, siginfo_t *info, void *context)
{
    void *array[CALL_STACK_TRACE_DEPTH];
    size_t size;

    fprintf(stderr, "ERROR: signal %d was trigerred:\n", signum);

    char *p = strdup("ERROR: signal %d was trigerred:\n");

//    UI_PRINT_LOG(p,signum);

    fprintf(stderr, "  Fault address: %p\n", info->si_addr);

    p = strdup("  Fault address: %p\n");

//    UI_PRINT_LOG(p,info->si_addr);

    switch (info->si_code)
    {
        case SEGV_MAPERR:
            fprintf(stderr, "  Fault reason: address not mapped to object\n");
            p = strdup("  Fault reason: address not mapped to object\n");
//            UI_PRINT_LOG(p);
            break;
        case SEGV_ACCERR:
            fprintf(stderr, "  Fault reason: invalid permissions for mapped object\n");
            p = strdup("  Fault reason: invalid permissions for mapped object\n");
//            UI_PRINT_LOG(p);
            break;
        default:
            fprintf(stderr, "  Fault reason: %d (this value is unexpected).\n", info->si_code);
            p = strdup("  Fault reason: %d (this value is unexpected).\n");
//            UI_PRINT_LOG(p, info->si_code);
            break;
    }

    // get pointers for the stack entries
    size = backtrace(array, CALL_STACK_TRACE_DEPTH);

    if (size == 0)
    {
        fprintf(stderr, "Stack trace unavailable\n");
        p = strdup("Stack trace unavailable\n");
 //       UI_PRINT_LOG(p);
    }
    else
    {
        fprintf(stderr, "Stack trace folows%s:\n", (size < CALL_STACK_TRACE_DEPTH) ? "" : " (partial)");
        p = strdup("Stack trace folows%s:\n");
        // print out the stack frames symbols to stderr
//        UI_PRINT_LOG(p, (size < CALL_STACK_TRACE_DEPTH) ? "" : " (partial)");
        backtrace_symbols_fd(array, size, STDERR_FILENO);
    }


    /* unregister this handler and let the default action execute */
    fprintf(stderr, "Executing original handler...\n");
    p = strdup("Executing original handler...\n");
 //   UI_PRINT_LOG(p);
    unregister_segmentation_fault_handler();
}

void zigbee::unregister_segmentation_fault_handler()
{
    struct sigaction action;

    action.sa_flags = 0;
    action.sa_handler = SIG_DFL;
    memset(&action.sa_mask, 0, sizeof(action.sa_mask));
    action.sa_restorer = NULL;

    sigaction(SIGSEGV, &action, NULL);
}

void zigbee::init(string nwk_manager_server_hostname, unsigned int nwk_manager_server_port, string gateway_server_hostname, unsigned int gateway_server_port, string ota_server_hostname, unsigned int ota_server_port)
{
    int i;
    char char_nwk_manager_server_hostname[nwk_manager_server_hostname.length() + 1];
    char char_gateway_server_hostname[gateway_server_hostname.length() + 1];
    char char_ota_server_hostname[ota_server_hostname.length() + 1];

    strcpy(char_nwk_manager_server_hostname,nwk_manager_server_hostname.c_str());
    strcpy(char_gateway_server_hostname,gateway_server_hostname.c_str());
    strcpy(char_ota_server_hostname,ota_server_hostname.c_str());
    register_segmentation_fault_handler();

    ds_init();

    if (si_init(char_nwk_manager_server_hostname, htons( nwk_manager_server_port), char_gateway_server_hostname, htons( gateway_server_port), char_ota_server_hostname, htons( ota_server_port)) == 0)
    {

        while (polling_process_activity()){
            if(ds_network_status.ext_pan_id != 0){
                QVariant data_ds_network_status;
                QVariant data_ds_device_tabble;
                data_ds_network_status.setValue(ds_network_status);
                emit hasBeenConnected(data_ds_network_status);
                for(i = 0; i < 20; i++){
                    if(ds_device_table[i].valid){
                        data_ds_device_tabble.setValue(ds_device_table[i]);
                        emit newDevice(data_ds_device_tabble);
                    }
                }
                i = 0;
            }
        }
        //si_deinit();
    }

    unregister_segmentation_fault_handler();
}
