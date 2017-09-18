#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <ev.h>

#define BUFFER_SIZE 1024

int total_clients = 0;
int PORT_NO;

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);

int main(int argc, char **argv){
  struct ev_loop *loop = ev_default_loop(0);
  int sd;
  struct sockaddr_in addr;
  int addr_len = sizeof(addr);
  struct ev_io w_accept;

  if( argc < 3  || argc > 3 || !strcmp(argv[1], "-?") ) {
    (void)printf("usage: server [port] [server directory] &"
  "\tExample: server 80 ./ &\n\n"
  "\tOnly Supports HTML");

    (void)printf("\n\tNot Supported: directories / /etc /bin /lib /tmp /usr /dev /sbin \n"
        );
    exit(0);
  }

  if( !strncmp(argv[2],"/"   ,2 ) || !strncmp(argv[2],"/etc", 5 ) ||
      !strncmp(argv[2],"/bin",5 ) || !strncmp(argv[2],"/lib", 5 ) ||
      !strncmp(argv[2],"/tmp",5 ) || !strncmp(argv[2],"/usr", 5 ) ||
      !strncmp(argv[2],"/dev",5 ) || !strncmp(argv[2],"/sbin",6) ){
    (void)printf("ERROR: Bad top directory %s, see server -?\n",argv[2]);}

  if(chdir(argv[2]) == -1){ 
    (void)printf("ERROR: Can't Change to directory %s\n",argv[2]);
    exit(4);
  }

  PORT_NO = atoi(argv[1]);

  // Create server socket
  if( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){
    perror("socket error");
    return -1;
  }

  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT_NO);
  addr.sin_addr.s_addr = INADDR_ANY;

  // Bind socket to address
  if (bind(sd, (struct sockaddr*) &addr, sizeof(addr)) != 0){
    perror("bind error");
  }

  // Start listing on the socket
  if (listen(sd, 2) < 0){
    perror("listen error");
    return -1;
  }

  // Initialize and start a watcher to accepts client requests
  ev_io_init(&w_accept, accept_cb, sd, EV_READ);
  ev_io_start(loop, &w_accept);

  // Start infinite loop
  while (1){
    ev_loop(loop, 0);
  }
  // clean up
  close(sd);
  return 0;
}

/* Accept client requests */
void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents){
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  int client_sd;
  struct ev_io *w_client = (struct ev_io*) malloc (sizeof(struct ev_io));

  if(EV_ERROR & revents)
  {
    perror("got invalid event");
    return;
  }

  // Accept client request
  client_sd = accept(watcher->fd, (struct sockaddr *)&client_addr, &client_len);

  if (client_sd < 0)
  {
    perror("accept error");
    return;
  }

  total_clients ++; // Increment total_clients count
  printf("Successfully connected with client.\n");
  printf("%d client(s) connected.\n", total_clients);

  // Initialize and start watcher to read client requests
  ev_io_init(w_client, read_cb, client_sd, EV_READ);
  ev_io_start(loop, w_client);  
}

/* Read client message */
void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents){
  char buffer[BUFFER_SIZE];
  char buffer_html[BUFFER_SIZE];
  ssize_t evread;
  int j, file_fd, buflen, len;
  long i, ret;

  if(EV_ERROR & revents)
  {
    perror("got invalid event");
    return;
  }

  // Receive message from client socket
  printf("reading from client:\n");
  evread = recv(watcher->fd, buffer, BUFFER_SIZE, 0);

  if(evread < 0)
  {
    perror("read error");
    return;
  }

  if(evread == 0)
  {
    // Stop and free watchet if client socket is closing
    perror("peer might closing");
  }
  else
  {
    printf("message: %s\n", buffer);
    
    for(i=0;i<evread;i++)  
      if(buffer[i] == '\r' || buffer[i] == '\n')
        buffer[i]='*';
    
    if( !strncmp(buffer,"GET ",4) || !strncmp(buffer,"get ",4) ){
      for(i=4;i<BUFFER_SIZE;i++) { 
        if(buffer[i] == ' ') { 
          buffer[i] = 0;
          break;
        }
      }

      if( !strncmp(&buffer[0],"GET /\0",6) || !strncmp(&buffer[0],"get /\0",6) ) 
        (void)strcpy(buffer,"GET /index.html");

      buflen = strlen(buffer);
      if( strncmp(&buffer[buflen-4], "html", 4) != 0) {
        printf("Unsupported media type\n");
        (void)sprintf(buffer,"HTTP/1.0 415 Unsupported Media Type\n");
        (void)send(watcher->fd, buffer, strlen(buffer), 0);
      } else {
        printf("file: %s\n", &buffer[5]);

        if(( file_fd = open(&buffer[5], O_RDONLY)) == -1){
          printf("file not found\n");
          (void)sprintf(buffer,"HTTP/1.0 404 Not Found\n");
          (void)send(watcher->fd, buffer, strlen(buffer), 0);
        } else {
          printf("file found\n");
          (void)sprintf(buffer,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
          (void)send(watcher->fd, buffer, strlen(buffer), 0);

          printf("sending file\n");
          while ( (ret = read(file_fd, buffer_html, BUFFER_SIZE))>0 ){
            printf("ret: %d\n", ret);
            (void)send(watcher->fd, buffer_html, strlen(buffer_html), 0);
          }

          close(file_fd);
        }
      }
    }
  }

  ev_io_stop(loop,watcher);
  close(watcher->fd);
  free(watcher);
  total_clients --;
  printf("%d client(s) connected.\n", total_clients);
  return;
}