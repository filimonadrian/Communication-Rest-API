#ifndef CLIENT_H
#define CLIENT_H

#include "helpers.h"
#include "requests.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>     /* read, write, close */
#include <sys/types.h>

#include "nlohmann/json.hpp"
#include "helpers.h"

#define PORT 8080
using json = nlohmann::json;

using namespace std;

const char* HOSTNAME = "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com";
const char* CONTENT_TYPE = "application/json";
const char* REGISTER = "/api/v1/tema/auth/register";
const char* LOGIN = "/api/v1/tema/auth/login";
const char* LOGOUT = "/api/v1/tema/auth/logout";
const char* ACCESS = "/api/v1/tema/library/access";
const char* BOOKS_INFO = "/api/v1/tema/library/books";
const char* BOOK_INFO = "/api/v1/tema/library/books/id";
const char* ADD_BOOK = "/api/v1/tema/library/books";
const char* DELETE_BOOK = "/api/v1/tema/library/books";
const char* DUMMY = "/api/v1/dummy";
 

// #define REGISTER "/api/v1/tema/auth/register"
// #define LOGIN "/api/v1/tema/auth/login"
// #define LOGOUT "/api/v1/tema/auth/logout"
// #define ACCESS "/api/v1/tema/library/access"
// #define BOOKS_INFO "/api/v1/tema/library/books"
// #define BOOK_INFO "/api/v1/tema/library/books/id"
// #define ADD_BOOK "/api/v1/tema/library/books"
// #define DELETE_BOOK "/api/v1/tema/library/books"
// #define DUMMY "/api/v1/dummy"


#endif