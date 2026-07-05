#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

static const char response[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=utf-8\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html><head><meta charset=\"utf-8\"><title>Hola</title></head>"
    "<body><h1>\xc2\xa1Hola, Mundo!</h1></body></html>\r\n";

int main(void) {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = __builtin_bswap16(PORT),
    };
    bind(server, (struct sockaddr *)&addr, sizeof(addr));
    listen(server, 10);

    printf("Listening on http://localhost:%d\n", PORT);
    fflush(stdout);

    for (;;) {
        int client = accept(server, NULL, NULL);
        if (client < 0) continue;
        char buf[1024];
        read(client, buf, sizeof(buf));
        write(client, response, sizeof(response) - 1);
        close(client);
    }
}
