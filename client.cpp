#include "client.h"

string extract_cookie_line(string sentence) {
    std::stringstream ss(sentence);
    std::string line;

    if (!sentence.empty()) {
        while (getline(ss, line, '\n')) {
            if (line.find("Cookie")) {
                return line;
            }
        }
    }
    return line;
}
/* returns 0 if all is ok -> returned code is 2xx */
int response_code(string response) {
    std::stringstream ss(response);
    std::string line;

    if (!response.empty()) {
        getline(ss, line, '\n');
        cout << line << endl;
        if (line[9] != '2') {
            return 1;
        }
    }
    return 0;
}

string extraction(string response, const char *start_find, const char *end_find) {
    stringstream ss(response);
    string toFind;
    int start, end;
    if (!strcmp(start_find, JSON_START)) {
        start = response.find(start_find);
    } else {
        start = response.find(start_find) + strlen(start_find);
    }

    end = response.find(end_find, start);
    return response.substr(start, end - start);
}

void print_book(json book) {
    for (json book : book) {
        cout << book << endl;
    }
}

int register_client(json credentials, int sockfd) {
    string message, response;
    message = compute_post_request(HOSTNAME, REGISTER, CONTENT_TYPE, credentials, "", "");

    cout << message << endl;

    send_to_server(sockfd, message.c_str());

    response = receive_from_server(sockfd);
     cout << response;

    if (response_code(response) == 0) {
        return 0;
    }

    extraction(response, ERR_START, ERR_END);
    return 1;
}

/* returns 0 if is OK */
int login(json credentials, int sockfd, string &cookie) {
    string message, response;
    message = compute_post_request(HOSTNAME, LOGIN, CONTENT_TYPE, credentials, "", "");

    cout << message << endl;

    send_to_server(sockfd, message.c_str());

    response = receive_from_server(sockfd);
    cout << response << endl;

    if (response_code(response) == 0) {
        // cookie = extract_cookie(response);
        cout << "extrag cookie:\n";
        cookie = extraction(response, COOKIE_START, COOKIE_END);
        cout << endl << cookie << endl;
        return 0;
    }

    extraction(response, ERR_START, ERR_END);
    return 1;
}

int logout(int sockfd, string cookie) {
    string message, response;
    message = compute_get_request(HOSTNAME, LOGOUT, GET, cookie, "");

    // cout << message << endl;

    send_to_server(sockfd, message.c_str());

    response = receive_from_server(sockfd);
    // cout << response << endl;

    if (response_code(response) == 0) {
        // cout << cookie << endl;
        return 0;
    }

    extraction(response, ERR_START, ERR_END);
    return 1;
}

int access_library(int sockfd, string cookie, string &jwt_token) {
    string message, response;

    message = compute_get_request(HOSTNAME, ACCESS, GET, cookie, "");

    cout << message << endl;

    send_to_server(sockfd, message.c_str());
    response = receive_from_server(sockfd);
    cout << response;

    if (response_code(response) == 0) {
        jwt_token = extraction(response, JWT_START, JWT_END);
        return 0;
    }

    cout << extraction(response, ERR_START, ERR_END);
    return 1;
}

int add_book(int sockfd, string cookie, string jwt_token, json add_book_fields) {
    string message, response;

    // message = compute_post_request(HOSTNAME, BOOKS_INFO, NULL, cookie, jwt_token);
    message = compute_post_request(HOSTNAME, LIBRARY, CONTENT_TYPE, add_book_fields,
                                   cookie, jwt_token);

    // cout << message << endl;

    send_to_server(sockfd, message.c_str());
    response = receive_from_server(sockfd);
    // cout << response << endl;

    if (response_code(response) == 0) {
        // jwt_token = extraction(response, JWT_START, JWT_END);
        //cout << extraction(response, JSON_START, JSON_END) << endl;
        return 0;
    }
    cout << extraction(response, ERR_START, ERR_END);
    return 1;
}

int library_information(int sockfd, string cookie, string jwt_token) {
    string message, response;

    message = compute_get_request(HOSTNAME, LIBRARY, GET, cookie, jwt_token);

    // cout << message << endl;

    send_to_server(sockfd, message.c_str());
    response = receive_from_server(sockfd);
    // cout << response << endl;

    if (response_code(response) == 0) {
        // jwt_token = extraction(response, JWT_START, JWT_END);
        json j;
        cout << "\n\n\n\n print de json \n";
        cout << extraction(response, JSON_START, JSON_END);
        // print_book(j);

        cout << "\n\n\n\n";
        return 0;
    }
    cout << extraction(response, ERR_START, ERR_END);
    return 1;
}

int book_information(int sockfd, string cookie, string jwt_token, int book_id) {
    string message, response;
    string lib_book = BOOK_INFO;
    lib_book = lib_book + to_string(book_id);

    message = compute_get_request(HOSTNAME, (lib_book.c_str()), GET, cookie, jwt_token);

    // cout << message << endl;

    send_to_server(sockfd, message.c_str());
    response = receive_from_server(sockfd);
    // cout << response << endl;

    if (response_code(response) == 0) {
        // jwt_token = extraction(response, JWT_START, JWT_END);
        cout << extraction(response, JSON_START, JSON_END) << endl;
        return 0;
    }
    cout << extraction(response, ERR_START, ERR_END);
    return 1;
}

int delete_book(int sockfd, string cookie, string jwt_token, int book_id) {
    string message, response;
    string lib_book = BOOK_INFO;
    lib_book = lib_book + to_string(book_id);

    message = compute_get_request(HOSTNAME, (lib_book.c_str()), DELETE, cookie, jwt_token);

    // cout << message << endl;

    send_to_server(sockfd, message.c_str());
    response = receive_from_server(sockfd);
    // cout << response << endl;

    if (response_code(response) == 0) {
        // jwt_token = extraction(response, JWT_START, JWT_END);
        //cout << extraction(response, JSON_START, JSON_END) << endl;
        return 0;
    }
    cout << extraction(response, ERR_START, ERR_END);
    return 1;
}

int check_number(char to_read[30]) {
    return (isdigit(atoi(to_read)));
}

int read_book_fields(json &add_book_fields) {
    char to_read[30];

    cout << "title=";
    cin >> to_read;
    add_book_fields["title"] = to_read;
    cout << "author=";
    cin >> to_read;
    add_book_fields["author"] = to_read;
    cout << "genre=";
    cin >> to_read;
    add_book_fields["genre"] = to_read;
    cout << "publisher=";
    cin >> to_read;
    add_book_fields["publisher"] = to_read;

    cout << "page_count=";
    cin >> to_read;

    if (!check_number(to_read)) {
        cout << "Page number si not a number\n";
        return 1;
    }

    add_book_fields["page_count"] = to_read;
    return 0;
}

int main(int argc, char *argv[]) {
    int sockfd, ret;
    string cookie, jwt_token;
    char *host_ip;
    host_ip = (char *)malloc(20 * sizeof(char));
    char to_read[20];
    int book_id;

    json credentials;
    json add_book_fields;

    hostname_to_ip(HOSTNAME, host_ip);
    sockfd = open_connection(host_ip, PORT, AF_INET, SOCK_STREAM, 0);

    // credentials["username"] = "studentiada1";
    // credentials["password"] = "studentiada1";

    // add_book_fields["title"] = "Marea mahmureala";
    // add_book_fields["author"] = "Studentii din regie";
    // add_book_fields["genre"] = "comedie";
    // add_book_fields["page_count"] = 999999;
    // add_book_fields["publisher"] = "Poliart";

    while (true) {
        fgets(to_read, 20, stdin);
        if (!strcmp(to_read, "register\n")) {
            cout << "username=";
            cin >> to_read; 
            credentials["username"] = to_read;
            cout << "password=";
            cin >> to_read; 
            credentials["password"] = to_read;
            
            register_client(credentials, sockfd);

        } else if (!strcmp(to_read, "login\n")) {
            cout << "username=";
            cin >> to_read;
            credentials["username"] = to_read;

            cout << "password=";
            cin >> to_read;
            credentials["password"] = to_read;

            ret = login(credentials, sockfd, cookie);
            if (ret) {
                continue;
            }

        } else if (!strcmp(to_read, "enter_library\n")) {

            ret = access_library(sockfd, cookie, jwt_token);
            if (ret) {
                continue;
            }
        } else if (!strcmp(to_read, "get_books\n")) {

            ret = library_information(sockfd, cookie, jwt_token);
            if (ret) {
                continue;
            }

        } else if (!strcmp(to_read, "get_book\n")) {

            cout << "id=";
            cin >> book_id;

            ret = book_information(sockfd, cookie, jwt_token, book_id);
            if (ret) {
                continue;
            }

        } else if (!strcmp(to_read, "add_book\n")) {
            read_book_fields(add_book_fields);

            ret = add_book(sockfd, cookie, jwt_token, add_book_fields);
            if (ret) {
                continue;
            }

        } else if (!strcmp(to_read, "delete_book\n")) {

            cout << "id=";
            cin >> book_id;
            ret = delete_book(sockfd, cookie, jwt_token, 1847);
            if (ret) {
                continue;
            }

        } else if (!strcmp(to_read, "logout\n")) {

            ret = logout(sockfd, cookie);
            if (ret) {
                continue;
            }

        } else if (!strcmp(to_read, "exit\n")) {
            break;
        }
    }

    close(sockfd);
    free(host_ip);
    return 0;
}
