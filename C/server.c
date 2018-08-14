#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  printf("Server start at: http://0.0.0.0:%d\n", PORT);

  // bind and listen
  bind(server_fd, (struct sockaddr*) &server, sizeof(server));
  listen(server_fd, 128);

  // use for-loop to accept requests
  for (;;) {
    int client_fd = accept(server_fd, NULL, NULL);
    char res[] = "HTTP/1.1 200 OK\r\nContent-Length: 11\r\nConnection: close\r\n\r\nHello, web!";
    for (int sent = 0; sent < sizeof(res); sent += send(client_fd, res+sent, sizeof(res)-sent, 0));
    close(client_fd);
  }
  return 0;
}