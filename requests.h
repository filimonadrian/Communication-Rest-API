#ifndef _REQUESTS_
#define _REQUESTS_

#include "general_includes.h"

// computes and returns a GET request string (query_params
// and cookies can be set to NULL if not needed)
char *compute_get_request(const char *host, const char *url,
                          int flag, string cookies, string jwt_token);

char *compute_post_request(const char *host, const char *url,
                           const char *content_type,
                           json body_data,
                           string cookies,
                           string jwt_token);

#endif
