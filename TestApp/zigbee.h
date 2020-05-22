#ifndef ZIGBEE_H
#define ZIGBEE_H

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

#include <QObject>
#include <QDebug>

#include "timer_utils.h"
#include "polling.h"
#include "socket_interface.h"
#include "user_interface.h"
#include "network_info_engine.h"
#include "device_list_engine.h"
#include "data_structures.h"
#include "ota_engine.h"
using namespace std;
Q_DECLARE_METATYPE(string)

class zigbee : public QObject

{
    Q_OBJECT

public:

    explicit zigbee(QObject *parent = nullptr);

    ~zigbee() = default;

    void init(string nwk_manager_server_hostname, unsigned int nwk_manager_server_port, string gateway_server_hostname, unsigned int gateway_server_port, string ota_server_hostname, unsigned int ota_server_port);

signals:

    void hasBeenConnected(QVariant ds_network_status);

    void newDevice(QVariant ds_device_table);

private:

    static void register_segmentation_fault_handler(void);

    static void segmentation_fault_handler(int signum, siginfo_t *info, void *context);

    static void unregister_segmentation_fault_handler(void);
};

#endif // ZIGBEE_H
