#ifndef __VERY_DIRTY_POST_H_
#define __VERY_DIRTY_POST_H_

#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"

/**
 * Defines for the HTTP methods.
 */
static const char* HTTP_METHOD_POST   = "POST";
static const char* HTTP_METHOD_PUT    = "PUT";
static const char* HTTP_METHOD_DELETE = "DELETE";

/**
 * This struct is used to pass additional HTTP headers such as API-keys.
 * Normally you pass this as an array. The last entry must have NULL as key.
 */
typedef struct
{
  const char* header;
  const char* value;
} http_header_t;

/**
 * HTTP Request struct.
 * hostname request host
 * path	 request path
 * port     request port
 * body	 request body
 */
typedef struct
{
  String hostname;
  IPAddress ip;
  String path;
  // TODO: Look at setting the port by default.
  //int port = 80;
  int port;
  String body;
} http_request_t;


class HttpClient {
public:
    /**
    * Public references to variables.
    */
    TCPClient client;

    /**
    * Constructor.
    */
    HttpClient(void);

    /**
    * HTTP request methods.
    * Can't use 'delete' as name since it's a C++ keyword.
    */

    void post(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, NULL, HTTP_METHOD_POST);
    }

    void put(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, NULL, HTTP_METHOD_PUT);
    }

    void del(http_request_t &aRequest, http_response_t &aResponse)
    {
        request(aRequest, aResponse, NULL, HTTP_METHOD_DELETE);
    }

    void post(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[])
    {
        request(aRequest, aResponse, headers, HTTP_METHOD_POST);
    }


private:
    /**
    * Underlying HTTP methods.
    */
    void request(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[], const char* aHttpMethod);
    void sendHeader(const char* aHeaderName, const char* aHeaderValue);
    void sendHeader(const char* aHeaderName, const int aHeaderValue);
    void sendHeader(const char* aHeaderName);
};

#endif /* __VERY_DIRTY_POST_H_ */
