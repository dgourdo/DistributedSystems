#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
} 

int main(int argc, char *argv[])
{
    int sockfd, portno, done;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]); 
       exit(0);
    }
    portno = atoi(argv[2]); //port
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP AF_INET
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]); //!!!
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);  

    printf("Trying to connect to %s:%d...\n", argv[1], portno);

   if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
       close(sockfd);
       error("ERROR connecting");
   }
   else{
       printf("Connected.\n"); 
    }

    // -------------------------------------------------------- client's printing-sending job starts here ----------------------------------------------------------
     //MENU
        
        int choice,n;
        int *X,*Y;
        double r;
        int i;
        
        printf("===================================== \n");
        printf("MENU-Distributed Systems Exercise1\n");
        printf("1. Inner product of vectors.\n");
        printf("2. Mean value of each vector.\n");
        printf("3. Product r*(X+Y).\n");
        printf("4. Exit.\n");
        printf("===================================== \n");
        printf("Enter your choice :  ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:     
             printf("Give n,the length of the vectors:  ");
             scanf("%d",&n);
             
		     X = (int *) malloc(n * sizeof(int));
		     Y = (int *) malloc(n * sizeof(int));
             
             printf("Give vector's X values:  ");
              for(i=0;i<n;i++)
               scanf("%d",&X[i]);
               
             printf("Give vector's Y values:  ");
              for(i=0;i<n;i++)
               scanf("%d",&Y[i]);
             break;
             
            case 2:     
             printf("Give n,the length of the vectors:  ");
             scanf("%d",&n);
             
             X = (int *) malloc(n * sizeof(int));
		     Y = (int *) malloc(n * sizeof(int));
             
             printf("Give vector's X values:  ");
              for(i=0;i<n;i++)
               scanf("%d",&X[i]);
             printf("Give vector's Y values:  ");
              for(i=0;i<n;i++)
               scanf("%d",&Y[i]);
             break;
             
            case 3:     
             printf("Give n,the length of the vectors:  ");
             scanf("%d",&n);
             
             X = (int *) malloc(n * sizeof(int));
		     Y = (int *) malloc(n * sizeof(int));
             
             printf("Give vector's X values:  ");
              for(i=0;i<n;i++)
               scanf("%d",&X[i]);
             printf("Give vector's Y values:  ");
              for(i=0;i<n;i++)
               scanf("%d",&Y[i]);
            printf("Give r(double value):  ");   //only in case 3
             scanf("%lf",&r);
             break;
                
            case 4:
                printf("\nExit!");
                printf("\nBye!\n");
                exit(0);    
                
            default:               
               printf("Wrong Input\n"); //Σε περίπτωση λάθους εισόδου εκ μέρους του χρήστη(αριθμός εκτός από 1,2,3,4, οποιοσδήποτε άλλος χαρακτήρας).
    }    
    
    
//!!! -> Ο socket-Client διοχετεύει τα α) και β) στον socket-Server(RPC-client)

	char choice_str[sizeof(choice)]; 
	sprintf(choice_str, "%d", choice);  // converts choice to a char*
	send(sockfd, choice_str, strlen(choice_str), 0);  


	char n_str[sizeof(n)]; 
	sprintf(n_str, "%d", n);  // converts n to a char*
	send(sockfd, n_str, strlen(n_str), 0); 

     char *bufferX=malloc(n*sizeof(int));
     memcpy(bufferX,X,(n*sizeof(int));        // converts vector X to a char*

    if (send(sockfd, bufferX, n*sizeof(int), 0) == -1) {
        perror("send() error");
        exit(1);
    }
    
     char *bufferY=malloc(n*sizeof(int));
     memcpy(bufferY,Y,(n*sizeof(int));     // converts vector Y to a char*

    if (send(sockfd, bufferY, n*sizeof(int), 0) == -1) {
        perror("send() error");
        exit(1);
    }

	char rbuffer[32];
	snprintf(rbuffer,sizeof(rbuffer)+1,"%f", r); //converts r to a char*
    send(sockfd, rbuffer, strlen(rbuffer), 0);
	
	

    
  
  /*: Prints the results in the screen(received by socket-server). */
  
  printf("\n");  
  
        if(choice==1){
                printf("FINAL RESULTS.\n");
                printf("1. Inner product of vectors.\n");           
                char buffer[256];
                
                int u = read(sockfd, buffer, 256);
                if (u < 0) {
                    perror("read() failed");
                    exit(EXIT_FAILURE);
                }

                int FINAL_RESULT1 = atoi(buffer);

                printf("---Result--- %d\n", FINAL_RESULT1);
        }  
     
                
        /*     
            else if(choice==2){
  			 printf("2. Mean value of X.\n");
             double Result1[0]=recv
             printf("%lf",Result1[0]);
             
             printf("2. Mean value of Y.\n");
             double Result1[1]=recv
             printf("%lf",Result1[1]);
            }
             
             else if(choice==3){
  			 printf("3. Product r*(X+Y).\n");
             double Result1=recv
             
             for(int i=0;i<n;i++)             //wants convert!!!!!!!!
              printf("%lf",Result1[i]);
        }
             
   */         
  
  

    close(sockfd); 
        
        
    //frees the allocated memory
    free(X); 
	free(Y);

    return 0;


}
