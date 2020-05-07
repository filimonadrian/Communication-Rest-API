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
#include <sys/types.h>
#include <unistd.h> /* read, write, close */

#include "helpers.h"
#include "nlohmann/json.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string>


#define DELETE 1
#define GET 0
using json = nlohmann::json;

using namespace std;