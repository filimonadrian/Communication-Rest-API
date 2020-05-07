#ifndef CLIENT_H
#define CLIENT_H
#include "general_includes.h"

#define PORT 8080

const char *HOSTNAME = "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com";
const char *CONTENT_TYPE = "application/json";
const char *REGISTER = "/api/v1/tema/auth/register";
const char *LOGIN = "/api/v1/tema/auth/login";
const char *LOGOUT = "/api/v1/tema/auth/logout";
const char *ACCESS = "/api/v1/tema/library/access";
const char *LIBRARY = "/api/v1/tema/library/books";
// const char *ADD_BOOK = "/api/v1/tema/library/books";

const char *BOOK_INFO = "/api/v1/tema/library/books/";

const char *ERR_START = "error\":\"";
const char *ERR_END = "\"";
const char *COOKIE_START = "Cookie: ";
const char *COOKIE_END = ";";
const char *JWT_START = "token\":\"";
const char *JWT_END = "\"";
const char *JSON_START = "[{";
const char *JSON_END = "]}";


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