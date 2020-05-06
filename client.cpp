#include "client.h"
#include <stdlib.h>

void register_client(char **credentials, int no_credentials) {
    compute_post_request(HOSTNAME, REGISTER, CONTENT_TYPE, credentials, no_credentials, NULL, 0);
}

int main(int argc, char *argv[]) {
    char *message;
    char *response;
    int sockfd;

    char **arr = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++) {
        arr[i] = (char *)malloc(100 * sizeof(char));
    }

    char **cookies = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++) {
        cookies[i] = (char *)malloc(100 * sizeof(char));
    }

    char *host_ip;
    host_ip = (char *)malloc(20 * sizeof(char));

    strcpy(arr[0], "username=student");
    strcpy(arr[1], "password=student");

    hostname_to_ip(HOSTNAME, host_ip);

    sockfd = open_connection(host_ip, PORT, AF_INET, SOCK_STREAM, 0);

    //    message = compute_get_request(HOSTNAME, LOGIN, NULL, NULL, 0);

    message = compute_post_request(HOSTNAME, LOGIN,
                                   "application/x-www-form-urlencoded", arr, 2, NULL, 0);

    puts(message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    puts(response);

    // Ex 2: POST dummy and print response from main server

    // message = compute_post_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com",
    //                                "/api/v1/dummy", "application/x-www-form-urlencoded", arr, 2, NULL, 0);
    // puts(message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // puts(response);

    // Ex 3 --------login--------

    // message = compute_post_request(HOSTNAME, "/api/v1/auth/login",
    //                              "application/x-www-form-urlencoded", arr, 2, NULL, 0);

    // puts(message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // puts(response);

    //Ex 4 -------key--------

    // strcpy(cookies[0], "connect.sid=s%3Ap2t6iH16XgvJsHncfM6dDSecwCeBiuW9.BhGhjQQpdQHWkhodkr5%2BBXr1Bnacko8l870Ksn8cd%2Fc");

    // message = compute_get_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com",
    //                               "/api/v1/weather/key ", NULL, cookies, 1);
    // puts(message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // puts(response);

    // {"key":"b912dd495585fbf756dc6d8f415a7649"}

    //Ex 5 ------logout-------

    // strcpy(cookies[0], "connect.sid=s%3AAyQyj_vo5dwAws0q1isjGfIzIWnyI86F.9O6AKt6pIrYWUWU3XBzsYU0eM3vEyYJJdRwybs1x0Nc");
    // message = compute_get_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com",
    //                               "/api/v1/auth/logout", NULL, cookies, 1);
    // puts(message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // puts(response);

    // BONUS: make the main server return "Already logged in!"

    // asta inseamna ca trebuie sa ma conectez din nou cu acelasi cookie, desi sunt conectat
    // Already logged in!

    // strcpy(cookies[0], "connect.sid=s%3Ap2t6iH16XgvJsHncfM6dDSecwCeBiuW9.BhGhjQQpdQHWkhodkr5%2BBXr1Bnacko8l870Ksn8cd%2Fc");
    // message = compute_post_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com",
    //                                " /api/v1/auth/login", "application/x-www-form-urlencoded", arr, 2, cookies, 1);

    // puts(message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // puts(response);

    // BONUS: GET catre API-ul de la openweather

    //  i've used:  dig $api.openweathermap.org
    //;; ANSWER SECTION:
    // api.openweathermap.org.	1910	IN	A	188.166.16.132
    // api.openweathermap.org.	1910	IN	A	37.139.1.159
    // api.openweathermap.org.	1910	IN	A	37.139.20.5
    // api.openweathermap.org.	1910	IN	A	82.196.7.246

    /* create a new socket */
    // sockfd = open_connection("37.139.20.5", 80, AF_INET, SOCK_STREAM, 0);

    // /* cookie from the previous ex */
    // strcpy(cookies[0], "connect.sid=s%3Ap2t6iH16XgvJsHncfM6dDSecwCeBiuW9.BhGhjQQpdQHWkhodkr5%2BBXr1Bnacko8l870Ksn8cd%2Fc");

    // message = compute_get_request("api.openweathermap.org",
    //                               "/data/2.5/weather", "lat=45&lon=12&appid=b912dd495585fbf756dc6d8f415a7649", cookies, 1);
    // puts(message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // puts(response);

    // free the allocated data at the end!

    return 0;
}
