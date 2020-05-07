// #include "requests.h"
// #include "helpers.h"
// #include <arpa/inet.h>
// #include <netdb.h>      /* struct hostent, gethostbyname */
// #include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
// #include <stdio.h>
// #include <stdlib.h>     /* exit, atoi, malloc, free */
// #include <string.h>     /* memcpy, memset */
// #include <sys/socket.h> /* socket, connect */
// #include <unistd.h>     /* read, write, close */

#include "general_includes.h"

char *compute_get_request(const char *host, const char *url,
                          int flag, string cookies, string jwt_token) {

    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));
    string help_query, help_cookie;
    // help_query = query_params.dump();
    // help_cookie = cookies.dump();
    help_cookie = cookies;

    // Step 1: write the method name, URL, request params (if any) and protocol type

    if (flag == DELETE) {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    // Step 2: add the host
    if (host != NULL) {
        sprintf(line, "Host: %s", host);
    }
    compute_message(message, line);

    // Step 3 (optional): add headers and/or cookies, according to the protocol format

    // if (cookies != NULL) {
    // sprintf(line, "Cookie: %s", help_cookie.c_str());
    sprintf(line, "Cookie: %s", cookies.c_str());

    compute_message(message, line);
    // }

    if (!jwt_token.empty()) {
        sprintf(line, "Authorization: Bearer %s", jwt_token.c_str());
        compute_message(message, line);
    }

    // Step 4: add final new line
    compute_message(message, "");
    return message;
}

char *compute_post_request(const char *host, const char *url,
                           const char *content_type,
                           json body_data,
                           string cookies,
                           string jwt_token) {

    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));
    string help_body, help_cookie;
    help_body = body_data.dump();
    // help_cookie = cookies.dump();
    help_cookie = cookies;

    if (body_data == NULL)
        help_body = "";
    else
        help_body = body_data.dump();

    if (!cookies.empty())
        help_cookie = cookies;
    else
        // help_cookie = cookies.dump();
        help_cookie = "";

    // Step 1: write the method name, URL and protocol type
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    // Step 2: add the host
    if (host != NULL) {
        sprintf(line, "Host: %s", host);
    }
    compute_message(message, line);

    /* Step 3: add necessary headers (Content-Type and Content-Length are mandatory)
            in order to write Content-Length you must first compute the message size
    */

    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

    sprintf(line, "Content-Length: %ld", help_body.size());
    compute_message(message, line);

    // Step 4 (optional): add cookies
    if (!cookies.empty()) {
        sprintf(line, "Cookie: %s", help_cookie.c_str());
        compute_message(message, line);
    }

    if (!jwt_token.empty()) {
        sprintf(line, "Authorization: Bearer %s", jwt_token.c_str());
        compute_message(message, line);
    }

    // Step 5: add new line at end of header
    compute_message(message, "");

    // Step 6: add the actual payload data
    compute_message(message, help_body.c_str());

    free(line);
    return message;
}

// char *compute_post_request(const char *host, const char *url, const char *content_type, char **body_data,
//                            int body_data_fields_count, char **cookies, int cookies_count) {
//     char *message = (char*)calloc(BUFLEN, sizeof(char));
//     char *line = (char*)calloc(LINELEN, sizeof(char));
//     //user name = student&password = student;
//     char *body_data_buffer = (char*)calloc(LINELEN, sizeof(char));

//     /*body_data[0] = "a=b", body_data[0] = "b=c" , concatenez cu &*/
//     /*content type = application ... */
//     /*lenght = length(line1) + .. + (n - 1) (&) */

//     // Step 1: write the method name, URL and protocol type
//     sprintf(line, "POST %s HTTP/1.1", url);
//     compute_message(message, line);

//     // Step 2: add the host
//     if (host != NULL) {
//         sprintf(line, "Host: %s", host);
//     }
//     compute_message(message, line);

//     /* Step 3: add necessary headers (Content-Type and Content-Length are mandatory)
//             in order to write Content-Length you must first compute the message size
//     */

//     sprintf(line, "Content-Type: %s", content_type);
//     compute_message(message, line);

//     int content_length = 0;
//     for (int i = 0; i < body_data_fields_count; i++) {
//         strcat(body_data_buffer, body_data[i]);
//         if (i < body_data_fields_count - 1) {
//             strcat(body_data_buffer, "&");
//         }
//         content_length += strlen(body_data[i]);
//     }

//     content_length += body_data_fields_count - 1;

//     sprintf(line, "Content-Length: %d", content_length);
//     compute_message(message, line);

//     // Step 4 (optional): add cookies
//     if (cookies != NULL) {
//         for (int i = 0; i < cookies_count; i++) {
//             sprintf(line, "Cookie: %s", cookies[i]);
//             compute_message(message, line);
//         }
//     }
//     // Step 5: add new line at end of header
//     compute_message(message, "");

//     // Step 6: add the actual payload data

//     // memset(line, 0, LINELEN);
//     compute_message(message, body_data_buffer);

//     free(line);
//     return message;
// }
