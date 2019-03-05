#ifndef _HTTPS_H_
#define _HTTPS_H_

#include <stdint.h>

#include "http.h"
extern "C" {
int https_send_request(enum request type, const char *host, uint16_t port, const char *path,
                       const char *body, char *resp, int len);
}

#endif /* _HTTPS_H_ */
