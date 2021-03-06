#ifndef GLV_SOCK_TCP_H
#define GLV_SOCK_TCP_H

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #ifdef __MINGW32__
    #undef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WIN8
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>

  typedef SOCKET glv_sock_t;
  typedef SOCKADDR_IN glv_addr_t;
#else
  #include <arpa/inet.h>
  #include <errno.h>
  #include <fcntl.h>
  #include <netdb.h>
  #include <netinet/in.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h>

  typedef int glv_sock_t;
  typedef struct sockaddr_in glv_addr_t;
#endif

#include <stdint.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "conf/conf.h"
#include "sock/ipaddr.h"
#include "util/thread.h"

#define GLV_TCP_FLAG_TYPE   1
#define GLV_TCP_FLAG_TLS    2
#define GLV_TCP_FLAG_NBIO   4

#define GLV_TCP_RECV_APPEND 1
#define GLV_TCP_RECV_BLOCK  2

typedef struct {
    glv_sock_t socket;
    glv_addr_t addr;
    uint32_t flags;
} glv_tcp_t;

glv_tcp_t* glv_tcp_create_server(uint16_t port);
glv_tcp_t* glv_tcp_create_client();

int glv_tcp_send(glv_tcp_t* sock, const char* data, unsigned int length);
int glv_tcp_recv(glv_tcp_t* sock, char* data, unsigned int length, int flags);

int glv_tcp_data_ready(glv_tcp_t* sock);
int glv_tcp_is_open(glv_tcp_t* sock);
int glv_tcp_is_secure(glv_tcp_t* sock);

ipaddr_t glv_tcp_get_ip(glv_tcp_t* sock);

void glv_tcp_destroy(glv_tcp_t* sock);

#endif
