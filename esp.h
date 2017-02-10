#ifndef ESPLIB_H
#define ESPLIB_H

#include <stdint.h>
#include <stdbool.h>

#define ESP_COMM_BUFF_SIZE 64

typedef enum {
    ESP_WIFI_CLIENT      = 1,
    ESP_WIFI_ACCESSPOINT = 2
} EspWifiMode;

typedef enum {
    ESP_MUX_SINGLE,
    ESP_MUX_MULTIPLE
} EspMuxMode;

typedef enum {
    ESP_ENC_OPEN     = 0,
    ESP_ENC_WEP      = 1,
    ESP_ENC_WPA      = 2,
    ESP_ENC_WPA2     = 3,
    ESP_ENC_WPA_WPA2 = 4,
} EspEncType;

typedef enum {
  ESP_PROTO_TCP,
  ESP_PROTO_UDP
} EspProtocol;

typedef enum {
    ESP_ROLE_SERVER = 0,
    ESP_ROLE_CLIENT
} EspRole;

typedef struct {
    void *data;
    uint8_t mode_wifi; /* EspWifiMode */
    uint8_t mode_mux;  /* EspMuxMode  */
    char buffer[ESP_COMM_BUFF_SIZE];
} EspComm;

typedef struct {
    char       name[33];
    uint8_t    encryption_type; /* EspEncType */
    uint8_t    signal_strength;
    uint8_t    mac_address[6];
    uint8_t    channel;
} EspAP;

typedef struct {
    uint8_t  mux;
    uint8_t  protocol; /* EspProtocol */
    uint8_t  remote_ip[4];
    uint16_t remote_port;
    uint8_t  remote_role; /* EspRole */
} EspConnection;

bool EspComm_init(EspComm *esp, void *data);
bool EspComm_cleanup(EspComm *esp);

bool EspComm_reset(EspComm *esp);
bool EspComm_test(EspComm *esp);
bool EspComm_version(EspComm *esp, uint8_t *v1, uint8_t *v2, uint8_t *v3, uint8_t *v4);
bool EspComm_ip_addr(EspComm *esp, uint8_t *ip, uint8_t *mac);
bool EspComm_mode_wifi(EspComm *esp, EspWifiMode mode);
bool EspComm_mode_mux(EspComm *esp, EspMuxMode mode);

bool EspComm_ap_list(EspComm *esp, EspAP *list, uint8_t list_size, uint8_t *list_read);
bool EspComm_ap_join(EspComm *esp, char *name, char *password);
bool EspComm_ap_quit(EspComm *esp);
bool EspComm_ap_create(EspComm *esp, char *name, char *password, uint8_t channel, EspEncType encryption);

bool EspComm_connection_list(EspComm *esp, EspConnection *list, uint8_t list_size, uint8_t *list_read);
bool EspComm_server_open(EspComm *esp, uint16_t port);
bool EspComm_server_close(EspComm *esp);
bool EspComm_client_connect(EspComm *esp, EspProtocol proto, char *host, uint16_t port);
bool EspComm_client_disconnect(EspComm *esp);
bool EspComm_client_send(EspComm *esp, uint8_t mux, uint8_t length, uint8_t *buffer);
bool EspComm_begin_read(EspComm *esp, uint8_t *mux, uint16_t *length);
bool EspComm_read(EspComm *esp, uint16_t length, uint8_t *buffer);

#endif // ESPLIB_H
