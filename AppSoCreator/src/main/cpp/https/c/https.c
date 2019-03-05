#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

#include "https.h"
#include "socket.h"
#include <android/log.h>

#define  LOG "JNILOG_xunxun"


#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__)

#define  LOGD_TAG(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG,tag,__VA_ARGS__)
#define  LOGI_TAG(tag, ...)  __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)
#define  LOGW_TAG(tag, ...)  __android_log_print(ANDROID_LOG_WARN,tag,__VA_ARGS__)
#define LOGE_TAG(tag, ...)  __android_log_print(ANDROID_LOG_ERROR,tag,__VA_ARGS__)
#define LOGF_TAG(tag, ...)  __android_log_print(ANDROID_LOG_FATAL,tag,__VA_ARGS__)
/*
 * @type: GET or POST
 * @host: the remote host
 * @port: the remote host port
 * @path: the path to request
 * @body: the body to request
 * @resp: response buffer
 * @len: the length of response buffer
 */
int https_send_request(enum request type, const char *host, uint16_t port, const char *path, const char* body, char *resp, int len)
{
	char header[1024*100];
	int req_len;

	if (type == GET)
		req_len = http_build_get_header(host, path, header,body);
	else if (type == POST)
		req_len = http_build_post_header(host, path, header, body);
	else
		return -1;

    SSL_library_init();
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL)
        return -1;

	SSL *ssl = SSL_new(ctx);
    if (ssl == NULL)
		goto free_ssl_ctx;
	
	int sockfd = socket_connect(host, port);
	if (sockfd < 0)
		goto free_ssl;

    if (SSL_set_fd(ssl, sockfd) == 0)
		goto free_sockfd;

    if (SSL_connect(ssl) != 1)
		goto free_all;

	int nleft = req_len;
    printf("nleft=%d \n, all: %s \n", nleft, header);
	LOGE("nleft=%d , all: %s ", nleft, header);
	int nwritten;
	char *ptr = header;
	while (nleft > 0) {
		if ((nwritten = SSL_write(ssl, ptr, nleft)) <= 0) {
			goto free_all;
		}
		nleft -= nwritten;
		ptr   += nwritten;
	}

	/* read response */
	int nread;
	ptr = resp;
	for (;;) {
		nread = SSL_read(ssl, ptr, len);
		if (nread == 0) {	
			break;
		} else if (nread < 0) {
			goto free_all;
		}
		len -= nread;
		ptr += nread;
		if (len < 0)	
			goto free_all;
	}

	return 0/*ptr - resp*/;

free_ssl_ctx:
    SSL_CTX_free(ctx);
	return -1;

free_ssl:
    SSL_CTX_free(ctx);
    SSL_free(ssl);
	return -1;

free_sockfd:
    SSL_CTX_free(ctx);
    SSL_free(ssl);
	close(sockfd);
	return -1;

free_all:
    SSL_CTX_free(ctx);
    SSL_free(ssl);
	close(sockfd);
	SSL_shutdown(ssl);
	return -1;
}
