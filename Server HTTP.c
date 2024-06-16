#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

const char *STATIC_RESPONSE =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: 155\r\n"
        "Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\r\n"
        "Accept-Ranges: bytes\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html>\r\n"
        "  <head>\r\n"
        "    <title>An Example Page</title>\r\n"
        "  </head>\r\n"
        "  <body>\r\n"
        "    <p>Hello World, this is a very simple HTML document.</p>\r\n"
        "  </body>\r\n"
        "</html>";

const char *STATIC_RESPONSE_KARTAX =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: 155\r\n"
        "Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\r\n"
        "Accept-Ranges: bytes\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html>\r\n"
        "  <head>\r\n"
        "    <title>KARTAX</title>\r\n"
        "  </head>\r\n"
        "  <body>\r\n"
        "    <p>Jesteś na innej stronie</p>\r\n"
        "  </body>\r\n"
        "</html>";


#define INPUT_BUFFER_SIZE   4096
#define MAX_CLIENTS         1024

void findPath(const char *request, char *target) {
    while (*(request)++ != ' ') {}
    while (*request != ' ') {
        *(target)++ = *(request)++;
    }
    *target = 0x00;
}

void handler_sig13(int signum)
{
    printf("Broken pipe error\n");
}

const char *Router(const char *requestedPath) {
    if (strcmp("/kartax", requestedPath) == 0) {
        return STATIC_RESPONSE_KARTAX;
    } else if (strcmp("/vanish", requestedPath) == 0) {
        return NULL;
    } else {
        return STATIC_RESPONSE;
    }
}

int findFreeSocketSlot(int* araara, int araaraSize)
{
    for(int i = 0; i < araaraSize;i++)
    {
        if(araara[i] == 0)
            return i;
    }

    return -1;
}

int main(void) {
    signal(13, handler_sig13);
    //miejsce na dane od klienta
    char inputBuffer[INPUT_BUFFER_SIZE + 1];

    char pathBuffer[1024];
    char ipBuffer[16];
    struct sockaddr_in clientData;
    socklen_t size = sizeof(clientData);

    // Tu tworzymy socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("Error creating socket");
        exit(0);
    }

    int status = fcntl(serverSocket, F_SETFL, O_NONBLOCK);

    if (status == -1) {
        perror("calling fcntl");
        // handle the error.  By the way, I've never seen fcntl fail in this way
    }

    int clients[MAX_CLIENTS];

    for(int i = 0; i < MAX_CLIENTS;i++)
    {
        clients[i] = 0;
    }

    // Tu przypisujemy adres IP i port do servera.
    struct sockaddr_in ipadr;
    ipadr.sin_addr.s_addr = inet_addr("0.0.0.0"); //IP na którym tworzymy server.
    ipadr.sin_family = AF_INET; // IPv4
    ipadr.sin_port = htons(2137);   // Port htons(port)
    memset(ipadr.sin_zero, 0, 8);   //Padding zawsze ustaw na 0.


    int ret = bind(serverSocket, (struct sockaddr *) &ipadr, sizeof(ipadr));

    if (ret != 0) {
        printf("Error when binding socket\n");
        exit(-1);
    }
    //ustawienie socketa na nasłuch
    ret = listen(serverSocket, 1024);
    if (ret != 0) {
        printf("nie udalo sie");
        exit(-1);
    }

    while (1) {
        // Akceptujemy połączenie przychodzące.
        while (1) {
            int clientSocket = accept(serverSocket, (struct sockaddr *) &ipadr, &size);

            if(clientSocket != -1)
            {
                int freeClientSocket = findFreeSocketSlot(clients, MAX_CLIENTS);

                if(freeClientSocket == -1)
                {
                    printf("Max clients reached (%d)\n", MAX_CLIENTS);
                    shutdown(clientSocket, SHUT_RDWR);
                    close(clientSocket);
                }

                printf("Accepted connection from %s:%d\n", inet_ntop(AF_INET, &clientData.sin_addr.s_addr, ipBuffer, 16),
                       ntohs(clientData.sin_port));

                fcntl(clientSocket, F_SETFL, O_NONBLOCK);

                clients[freeClientSocket] = clientSocket;
            }
            else
            {
                break;
            }
        }


        for(int i = 0; i < MAX_CLIENTS;i++)
        {
            if(clients[i] == 0)
                continue;

            size_t received = recv(clients[i], inputBuffer, INPUT_BUFFER_SIZE, 0);
            inputBuffer[received] = 0x00;

            if(received == -1)
            {
                if(errno != EWOULDBLOCK && errno != EAGAIN)
                {
                    printf("Error occured on socket, closing connection %d.\n", i);
                    shutdown(clients[i], SHUT_RDWR);
                    close(clients[i]);
                    clients[i] = 0;

                }
                continue;
            }

            findPath(inputBuffer, pathBuffer);
            printf("Requested path:\n%s by socket %d\n", pathBuffer, i);

            const char *response = Router(pathBuffer);

            if (response == NULL) {
                // Zamykamy transmisje na sockecie clienta.
                shutdown(clients[i], SHUT_RDWR);
                // Zamykamy socket clienta.
                close(clients[i]);
                clients[i] = 0;
                break;
            }

            // Wysyłamy stringa do przeglądarki.
            send(clients[i], response, strlen(response), 0);
        }
    }

    shutdown(serverSocket, SHUT_RDWR);
    close(serverSocket);
    return 0;
}