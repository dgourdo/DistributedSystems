#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <stdint.h>

#include "exercise1.h"


void error(char *msg)
{
    perror(msg);
    exit(1);
}


void
ds_ex1_1(char *host,int n,int *X,int *Y,int sockfd)
{
	CLIENT *clnt;
	int  *result_1;
	Exercise1  inner_product_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DS_Ex1, Ex1_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

//-------------------------------------------------------
//Προσθέτω κώδικα πριν την κλήση της συνάρτησης
//Τα νούμερα που έδωσε ο χρήστης
inner_product_1_arg.n=n;

inner_product_1_arg.X.X_len = n;
inner_product_1_arg.X.X_val = (int *) malloc(n * sizeof(int));
for (int i = 0; i < n; i++) {
    inner_product_1_arg.X.X_val[i] = X[i];
}

inner_product_1_arg.Y.Y_len = n;
inner_product_1_arg.Y.Y_val = (int *) malloc(n * sizeof(int));
for (int i = 0; i < n; i++) {
    inner_product_1_arg.Y.Y_val[i] = Y[i];
}

//-------------------------------------------------------
	result_1 = inner_product_1(&inner_product_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}else {
        printf("\nRPC reply->");
		printf("result is %d\n", *result_1); 
        
        printf("Transfering the final result to the socket-client...");
        //The same should be done for the other 2 functions.
        char buffer[256];
        sprintf(buffer,"%d",*result_1);
        write(sockfd,buffer,strlen(buffer));   
        
	}
	
	free(inner_product_1_arg.X.X_val);
    free(inner_product_1_arg.Y.Y_val);
	
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
    
}




void
ds_ex1_2(char *host,int n,int *X,int *Y)
{
	CLIENT *clnt;
	double  *result_1;
	Exercise1  mean_value_2_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DS_Ex1, Ex1_2, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

//-------------------------------------------------------
//Προσθέτω κώδικα πριν την κλήση της συνάρτησης
//Τα νούμερα που έδωσε ο χρήστης
mean_value_2_arg.n=n;

mean_value_2_arg.X.X_len = n;
mean_value_2_arg.X.X_val = (int *) malloc(n * sizeof(int));

mean_value_2_arg.Y.Y_len = n;
mean_value_2_arg.Y.Y_val = (int *) malloc(n * sizeof(int));


int i;
for(i=0;i<n;i++)
    mean_value_2_arg.X.X_val[i]=X[i];
for(i=0;i<n;i++)
    mean_value_2_arg.Y.Y_val[i]=Y[i];

//-------------------------------------------------------
	result_1 = mean_value_2(&mean_value_2_arg, clnt);
	if (result_1 == (double *) NULL) {
		clnt_perror (clnt, "call failed");
	}else {
		printf("result is %f\n", *result_1);
	}
	

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}



void
ds_ex1_3(char *host,int n,int *X,int *Y,double r)
{
	CLIENT *clnt;
	double  *result_1;
	Exercise1  product_3_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DS_Ex1, Ex1_3, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

//-------------------------------------------------------
//Προσθέτω κώδικα πριν την κλήση της συνάρτησης
//Τα νούμερα που έδωσε ο χρήστης
product_3_arg.n=n;

product_3_arg.X.X_len = n;
product_3_arg.X.X_val = (int *) malloc(n * sizeof(int));

product_3_arg.Y.Y_len = n;
product_3_arg.Y.Y_val = (int *) malloc(n * sizeof(int));

int i;
for(i=0;i<n;i++)
    product_3_arg.X.X_val[i]=X[i];
for(i=0;i<n;i++)
    product_3_arg.Y.Y_val[i]=Y[i];
product_3_arg.r=r;
//-------------------------------------------------------

	result_1 = product_3(&product_3_arg, clnt);
	if (result_1 == (double *) NULL) {
		clnt_perror (clnt, "call failed");
	}else {
		printf("result is %f\n", *result_1);
	}
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


// ταυτόχρονα πολλοί clients
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, done;
     pid_t procId;
     struct sockaddr_in serv_addr, cli_addr;
     unsigned int children = 0;
     
     
    	char *host;
		int n;
		double r;
    
        //s:server
        int choice;
        int ns;
        double rs;
        int i;
        
        char choice_str[100]; 
        char n_str[100];
        int num_array1[100];
        int num_array2[100];
        char rbuffer[100];
        
     if (argc < 3) { 
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0); //!!!
     if (sockfd < 0) 
         error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[2]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(portno);
     serv_addr.sin_addr.s_addr = INADDR_ANY;

     if (bind(sockfd, (struct sockaddr *) &serv_addr, //!!!
              sizeof(serv_addr)) < 0)
                  error("ERROR on binding");

     listen(sockfd,5); 
     

     
     int choice_value;
     int n_value;

     double r_value;
        
     for (;;)  {
     	printf("Waiting for a connection...\n");
     	clilen = sizeof(cli_addr);
     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); 
     	if (newsockfd < 0) 
          	error("ERROR on accept");
          	
	
     	if (fork() == 0)  { //child process   
     		close (sockfd); 
        	printf("Connected.\n");
        	done = 0;
        	
        	
            choice=recv(newsockfd, choice_str, sizeof(choice_str), 0);
            choice_value=atoi(choice_str);
            printf("Choice:%d\n",choice_value);
        	
            n=recv(newsockfd, n_str, sizeof(n_str), 0);
            n_value=atoi(n_str);
            printf("n:%d\n",n_value);
                
            
            int valreadX,valreadY;
            
            char *bufferX=malloc(n_value*sizeof(int));
            char *bufferY=malloc(n_value*sizeof(int));
          
            int* buffX=malloc(n_value*sizeof(int));
            int* buffY=malloc(n_value*sizeof(int));
            
         
                if (valreadX=recv(newsockfd, bufferX, n_value*sizeof(int), 0) == -1) {
                    perror("recv() error");
                    exit(1);
                }  
                
          
                if (valreadY=recv(newsockfd, bufferY, n_value*sizeof(int),0) == -1) {
                    perror("recv() error");
                    exit(1);
                }  
                
                
                
                for (int i = 0; i < n_value; i++) {
                    buffX[i] = ntohl(((int*)bufferX)[i]);
                    buffY[i] = ntohl(((int*)bufferY)[i]);
                }
                
                /*
                //2os Tropos
                //buffX->bufferX (char* -> int*)
                for (int i = 0; i < n_value; i++) {
                    buffX[i]=atoi((const char*)&bufferX[i]); //casting
                }
                */
                
                             
                printf("Vector X:");        
                for (int i = 0; i < n_value; i++) {
                    printf("%d ", buffX[i]);
                }
                printf("\n");
                    
                
                printf("Vector Y:");        
                for (int i = 0; i < n_value; i++) {
                    printf("%d ", buffY[i]);
                }
                printf("\n");
                    

      
		rs = recv(newsockfd, rbuffer, sizeof(rbuffer), 0);
        r_value=atof(rbuffer);
        if(choice_value==3)
        printf("r:%f\n",r_value);
        
            
	host = argv[1];
    
    //Κλήση της εκάστοτε απομακρυσμένης συνάρτησης
    if(choice_value==1){
        printf("func1");
        ds_ex1_1 (host,n_value,buffX,buffY,newsockfd);
        printf("end of func1");  
	}else if(choice_value==2){
        printf("func2");
	ds_ex1_2 (host,n_value,buffX,buffY);
	}else if(choice_value==3){
        printf("func3");
	ds_ex1_3 (host,n_value,buffX,buffY,r_value);}
	
    free(bufferX);
	free(bufferY);
	
    free(buffX);
	free(buffY);
				    
        	exit (0) ; 
	}
     	close(newsockfd); //!!!
	children++;
	while (children){ // μπορεί να παραλειφθεί
             procId=waitpid((pid_t) -1, NULL, WNOHANG); //!!!
	     if (procId<0) error("waitpid error.\n");
	     else if (procId==0) break;
	     else printf("I collected them.");
	}
   }  
   
     return 0; 
}
