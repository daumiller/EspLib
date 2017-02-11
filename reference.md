##Functions##
* [EspComm_init](#espcomm_init)
* [EspComm_cleanup](#espcomm_cleanup)
* [EspComm_reset](#espcomm_reset)
* [EspComm_test](#espcomm_test)
* [EspComm_version](#espcomm_version)
* [EspComm_ip\_addr](#espcomm_ip_addr)
* [EspComm_mode\_wifi](#espcomm_mode_wifi)
* [EspComm_mode\_mux](#espcomm_mode_mux)
* [EspComm_ap\_list](#espcomm_ap_list)
* [EspComm_ap\_join](#espcomm_ap_join)
* [EspComm_ap\_quit](#espcomm_ap_quit)
* [EspComm_ap\_create](#espcomm_ap_create)
* [EspComm_connection\_list](#espcomm_connection_list)
* [EspComm_server\_open](#espcomm_server_open)
* [EspComm_server\_close](#espcomm_server_close)
* [EspComm_client\_connect](#espcomm_client_connect)
* [EspComm_client\_disconnect](#espcomm_client_disconnect)
* [EspComm_client\_send](#espcomm_client_send)
* [EspComm_begin\_read](#espcomm_begin_read)
* [EspComm_read](#espcomm_read)

##Enumerations##
* [EspWifiMode](#espwifimode)
* [EspMuxMode](#espmuxmode)
* [EspEncType](#espenctype)
* [EspProtocol](#espprotocol)
* [EspRole](#esprole)

##Structures##
* [EspComm](#espcomm)
* [EspAP](#espap)
* [EspConnection](#espconnection)

---

##EspComm_init##
```c
bool EspComm_init(EspComm *esp, void *data)
```
Initialize an EspComm structure, with platform-specific data value.

##EspComm_cleanup##
```c
bool EspComm_cleanup(EspComm *esp)
```
Do any platform-specific cleanup when done with EspComm structure.

##EspComm_reset##
```c
bool EspComm_reset(EspComm *esp)
```
Send reset command to ESP8266 (AT+RST).

##EspComm_test##
```c
bool EspComm_test(EspComm *esp)
```
Test ESP8266 for response (AT).

##EspComm_version##
```c
bool EspComm_version(EspComm *esp, uint8_t *v1, uint8_t *v2, uint8_t *v3, uint8_t *v4)
```
Query ESP8266 for version information (AT+GMR).

On success, stores version components 1.2.3.4 into supplied bytes v1, v2, v3, v4.

##EspComm_ip\_addr##
```c
bool EspComm_ip_addr(EspComm *esp, uint8_t *ip, uint8_t *mac)
```
Query ESP8266 for current IP/MAC configuration (AT+CIFSR).

On success, stores IP as four bytes in ```ip```, and MAC as six bytes in ```mac```.

##EspComm_mode\_wifi##
```c
bool EspComm_mode_wifi(EspComm *esp, EspWifiMode mode)
```
Set current wireless mode (AT+CWMODE=).

* ```ESP_WIFI_CLIENT``` to connect to an access point
* ```ESP_WIFI_ACCESSPOINT``` to create an access point

##EspComm_mode\_mux##
```c
bool EspComm_mode_mux(EspComm *esp, EspMuxMode mode)
```
Set connection multiplexing mode (AT+CIPMUX=).

* ```ESP_MUX_SINGLE``` single connection (only valid as a connection client)
* ```ESP_MUX_MULTIPLE``` multiple active connections

##EspComm_ap\_list##
```c
bool EspComm_ap_list(EspComm *esp, EspAP *list, uint8_t list_size, uint8_t *list_read)
```
List visible access points (AT+CWLAP).

* ```list_size``` count of EspAP structures available in list parameter / maximum number of APs to read.
* ```list_read``` actual number of APs found (<= list_size)
* ```list``` array of EspAP structurs

##EspComm_ap\_join##
```c
bool EspComm_ap_join(EspComm *esp, char *name, char *password)
```
Attempt to join access point (AT+CWJAP).

##EspComm_ap\_quit##
```c
bool EspComm_ap_quit(EspComm *esp)
```
Quit/disconnect-from access point (AT+CWQAP).

##EspComm_ap\_create##
```c
bool EspComm_ap_create(EspComm *esp, char *name, char *password, uint8_t channel, EspEncType encryption)
```
Create an access point (AT+CWSAP).

##EspComm_connection\_list##
```c
bool EspComm_connection_list(EspComm *esp, EspConnection *list, uint8_t list_size, uint8_t *list_read)
```
List curerntly active client/server connections (AT+CIPSTATUS).

* ```list_size``` maximum number of EspConnection structures to read/size of passed list
* ```list_read``` actual number of connections read/filled
* 

##EspComm_server\_open##
```c
bool EspComm_server_open(EspComm *esp, uint16_t port)
```
Create a listening TCP server (AT+CIPSERVER=1,).

##EspComm_server\_close##
```c
bool EspComm_server_close(EspComm *esp)
```
Stop a listening TCP server (AT+CIPSERVER=0,).

##EspComm_client\_connect##
```c
bool EspComm_client_connect(EspComm *esp, EspProtocol proto, char *host, uint16_t port)
```
Establish client TCP/UDP connection (AT+CIPSTART=).

##EspComm_client\_disconnect##
```c
bool EspComm_client_disconnect(EspComm *esp)
```
Clost client connection (AT+CIPCLOSE).

##EspComm_client\_send##
```c
bool EspComm_client_send(EspComm *esp, uint8_t mux, uint8_t length, uint8_t *buffer)
```
Send data over an established TCP/UDP connection (AT+CIPSEND=).

**This method is actually for client and server endpoints.** *(Should be renamed).*

* ```mux``` connection number, if in multiple-connection mode.

##EspComm_begin\_read##
```c
bool EspComm_begin_read(EspComm *esp, uint8_t *mux, uint16_t *length)
```
Begin data read over established TCP/UDP connection (watching for +IPD).

* ```mux``` connection number data received from
* ```length``` length of data available to read

This method will tell you the connection number and amount of data ready to read, and leave the read buffer ready for an ```EspComm_read``` call to retrieve the actual data.

##EspComm_read##
```c
bool EspComm_read(EspComm *esp, uint16_t length, uint8_t *buffer)
```
Read raw data from ESP8266. This should follow an ```EspComm_begin_read``` call.

---

##EspWifiMode##
         value                 | description
-------------------------------|----------------
**```ESP_WIFI_CLIENT```**      | connect to AP
**```ESP_WIFI_ACCESSPOINT```** | create AP

##EspMuxMode##
         value             | description
---------------------------|----------------------------------
**```ESP_MUX_SINGLE```**   | single (TCP/UDP) connection mode
**```ESP_MUX_MULTIPLE```** | multiple connection mode

##EspEncType##
         value             | description
---------------------------|----------------
**```ESP_ENC_OPEN```**     | no encryption
**```ESP_ENC_WEP```**      | WEP encryption
**```ESP_ENC_WPA```**      | WPA encryption
**```ESP_ENC_WPA2```**     | WPA2 encryption
**```ESP_ENC_WPA_WPA2```** | WPA/WPA2 encryption

##EspProtocol##
         value          | description
------------------------|----------------
**```ESP_PROTO_TCP```** | TCP connection
**```ESP_PROTO_UDP```** | UDP connection

##EspRole##
         value            | description
--------------------------|---------------------------
**```ESP_ROLE_SERVER```** | TCP/UDP connection server
**```ESP_ROLE_CLIENT```** | TCP/UDP connection client

---

##EspComm##
```c
typedef struct {
    void *data;
    uint8_t mode_wifi; /* EspWifiMode */
    uint8_t mode_mux;  /* EspMuxMode  */
    char buffer[ESP_COMM_BUFF_SIZE];
} EspComm;
```

     member     | description
----------------|---------------------------
```data```      | platform-specific data value
```mode_wifi``` | wireless mode currently set
```mode_mux```  | connection mode currently set
```buffer```    | read/write buffer (internal use only)

##EspAP##
```c
typedef struct {
    char       name[33];
    uint8_t    encryption_type; /* EspEncType */
    uint8_t    signal_strength;
    uint8_t    mac_address[6];
    uint8_t    channel;
} EspAP;
```

     member           | description
----------------------|---------------------------
```name```            | null-terminated AP name
```encryption_type``` | encryption type
```signal_strength``` | signal strength (**NOTE**: *this has the negative sign stripped; smaller values are stronger signals*)
```mac_address```     | AP MAC address
```channel```         | wireless channel number

##EspConnection##
```c
typedef struct {
    uint8_t  mux;
    uint8_t  protocol; /* EspProtocol */
    uint8_t  remote_ip[4];
    uint16_t remote_port;
    uint8_t  remote_role; /* EspRole */
} EspConnection;
```

     member        | description
-------------------|---------------------------
```mux```          | connection number
```protocol ```    | TCP or UDP
```remote_ip ```   | remote IP address
```remote_port ``` | remote port number
```remote_role ``` | remote is client or server
