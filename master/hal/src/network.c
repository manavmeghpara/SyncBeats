#include "hal/network.h"
#include "hal/util.h"
#include "hal/musicPlayer.h"
#include <ctype.h>


static pthread_t tid;

static int sockfd;
static struct sockaddr_in client_addr;
static socklen_t client_addr_len = sizeof(client_addr);

struct Thread_args{
    int sockfd;
};


void Network_volume(int volume)
{
    musicPlayer_setVolume(volume);

    char messageTx[MAX_LEN];
    snprintf(messageTx, MAX_LEN, "Volume %d\n", volume);
    sendto(sockfd, messageTx, strlen(messageTx),0, (struct sockaddr *) &client_addr, client_addr_len);
}

void Network_pause()
{
    pauseSong();

    char messageTx[MAX_LEN];
    snprintf(messageTx, MAX_LEN, "Song paused\n");
    sendto(sockfd, messageTx, strlen(messageTx),0, (struct sockaddr *) &client_addr, client_addr_len);
}

void Network_play()
{
    playSong();

    char messageTx[MAX_LEN];
    snprintf(messageTx, MAX_LEN, "Song played\n");
    sendto(sockfd, messageTx, strlen(messageTx),0, (struct sockaddr *) &client_addr, client_addr_len);
}

void Network_next()
{
    stopCurrentSong();
    playNextSong();

    char messageTx[MAX_LEN];
    snprintf(messageTx, MAX_LEN, "Next song\n");
    sendto(sockfd, messageTx, strlen(messageTx),0, (struct sockaddr *) &client_addr, client_addr_len);
}

void Network_previous()
{
    stopCurrentSong();
    playPreviousSong();

    char messageTx[MAX_LEN];
    snprintf(messageTx, MAX_LEN, "Previous song\n");
    sendto(sockfd, messageTx, strlen(messageTx),0, (struct sockaddr *) &client_addr, client_addr_len);
}

	   

// void Network_update(){

//     char messageTx[MAX_LEN];
//     snprintf(messageTx, MAX_LEN, "update %d %d %d ", AudioMixer_getVolume(), getBpm(), getMode() );
//     sendto(sockfd, messageTx, strlen(messageTx),0, (struct sockaddr *) &client_addr, client_addr_len);
// } 
 
// Function to handle client requests
void *handle_client(void *arg) {
    struct Thread_args* args = (struct Thread_args *)arg;
    char buffer[MAX_LEN];
    while (!Util_is_shutDown()) {

        // Receive message from client
  
        int len = recvfrom(args->sockfd, buffer, MAX_LEN-1, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        buffer[len] = '\0';
        printf("\nReceived message from client: %s\n", buffer);
         
 
        if(strncmp(buffer, "stop", 4)==0 || strncmp(buffer, "Stop", 4)==0 || strncmp(buffer, "STOP", 4)==0  ){
            printf("Program Terminating!\n");

            close(args->sockfd);
            free(args);
            return NULL;
        }
        else if(strncmp(buffer, "volume", 6)==0){
            int v = (buffer[7] - '0')*10 + buffer[8];
            Network_volume(v);
        }
        else if(strncmp(buffer, "play", 4)==0)
            Network_play();
        else if(strncmp(buffer, "pause", 5)==0)
            Network_pause();
        else if(strncmp(buffer, "next", 4)==0)
            Network_next();
        else if(strncmp(buffer, "previous", 8)==0)
            Network_previous();


    }

    close(args->sockfd);
    free(args);

    return NULL;
}

void Network_init()
{  
    struct sockaddr_in sin;

    // Initialize server address structure
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    // Create UDP socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0); 

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address and port
    int bindfd = bind (sockfd, (struct sockaddr*) &sin, sizeof(sin));
    if (bindfd < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP server listening on port %d...\n", PORT);
    
    // Create a thread to handle client requests
    struct Thread_args *args = malloc(sizeof(*args));
    args->sockfd = sockfd;
    if (pthread_create(&tid, NULL, handle_client, args) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
}

void Network_cleanup(void)
{
    pthread_join(tid, NULL);

    close(sockfd);
}