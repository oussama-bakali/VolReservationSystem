#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
int client_sockets[7] = {-1};
struct agence{
int choix;
int nbvols;
int* placespourvol;
int* placesannuleepourvol;
 char buffer[300];
 char buffercancel[300];
char referencevol[100];
char numagence[20];
char test[300];
char testannulee[200];
int testannuler;
int placesannulees;
char** listevolinitial;
char * compressedlistvolinitial;
char* compressedlistvolapresannulation;
char** listevolapresannulation;
char* compressednbplacesinitial;
char* compressednbplacesfinal;
};

char** string_to_table(char* str, char delimiter, int count, int length) {
    char** table = (char**) malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) {
        table[i] = (char*) malloc((length) * sizeof(char));
    }
    
    char* token = strtok(str, &delimiter);
    int i = 0;
    while (token != NULL && i < count) {
        strncpy(table[i], token, length);
        table[i][length] = '\0';
        token = strtok(NULL, &delimiter);
        i++;
    }
    
    return table;
}
int *stringToIntArray(char *str, char *delim, int *size) {
    char *token = strtok(str, delim);
    int *int_arr = malloc(sizeof(int));
    int i = 0;

    while (token != NULL) {
        int_arr[i++] = atoi(token);
        int_arr = realloc(int_arr, sizeof(int) * (i+1));
        token = strtok(NULL, delim);
    }

    *size = i; // Set the size of the integer array
    return int_arr;
}
char* facture(char numagence[20]){

FILE* f;
f=fopen("facture.txt","r");
if (f==NULL){printf("erreur");}
char *reference="2000",*Destion;
char *nbplaces;
char *destination;
char line[1000];

int test=0;


while(fgets(line,sizeof(line),f)){
//printf("%s",line);
nbplaces=strtok(line," \t");

if (strcmp(numagence,nbplaces)==0){
    
    printf("la reference d agence%s\n",nbplaces);
nbplaces=strtok(NULL," \t");
printf("le montant a payer est %s",nbplaces);
//return atoi(nbplaces); 
return nbplaces;
}


   


}

fclose(f);


}
void miseajour(FILE *fp,char buffer[20],int newnumberofplaces){
        
    char line[100];
    char reference[20];
    int numberofplaces;
  
    


    strcpy(reference, buffer);

    fp = fopen("vols.txt", "r+");

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, reference)) {
            sscanf(line, "%*s %*s %d %*d", &numberofplaces);
            numberofplaces = newnumberofplaces;
            fseek(fp, -strlen(line), SEEK_CUR);
            fseek(fp,sizeof(reference),SEEK_CUR);
            fseek(fp,sizeof(numberofplaces),SEEK_CUR);
            fprintf(fp, "%s %s %d %s", "", "", numberofplaces, "");
            break;
        }
    }

    fclose(fp);
}
void annulez(FILE*fp,char buffer[20],char newstate[10],char refagences[20]){
    
    char line[100];
    char reference[20];
    char rest[20];
    char res[30];
    int newnumberofplaces ;
    
    char agence[10];
    char transaction[10];
    

char result[30];
long int pos;

int valeur;
    fp = fopen("histo.txt", "r+");
char *nbplaces;
    while (fgets(line, sizeof(line), fp)) {
        nbplaces=strtok(line," \t");
        
        if (strcmp(buffer,nbplaces)==0){
            printf("ok");
            nbplaces=strtok(NULL," \t");
            //nbplaces=strtok(NULL," \t");
           //nbplaces=strtok(NULL," \t");
            printf("l etat est %s",nbplaces);
            if (strcmp(refagences,nbplaces)==0){
sscanf(line, "%*s%*s%s%*s%*s", reference);
       
        
        
            
            pos=ftell(fp)-strlen(line);
           fseek(fp, pos-sizeof(reference)+1, SEEK_SET);
//fseek(fp,pos,SEEK_SET);
//fseek(fp,sizeof(reference),SEEK_CUR);
//fseek(fp,sizeof(int),SEEK_CUR);

//search(fp,buffer,"2");
            //fseek(fp,sizeof(rest),SEEK_CUR);
            //fseek(fp,sizeof(rest),SEEK_CUR);
            
            fprintf(fp, "%s%s%s%s%s", "", "\t", newstate, "","");
            break;
         }}
    }

    fclose(fp);
}
void factures(FILE* f,int referenceagence,int montant){
    f=fopen("facture.txt","r+");
    if (f==NULL){
        printf("erreur d ouverture de fichier");
    }
    fprintf(f,"%s\t \t %s\n","nomagence","prixapayer");
    fprintf(f,"%d \t \t%d \t",referenceagence,montant);
    fclose(f);
}
void socketserver(int argc,char* argv[],int socketfd,int newsocketfd,struct sockaddr_in serv_addr,struct sockaddr_in cli_addr,int portno,int clilen){

if (argc<2){fprintf(stderr,"specifier le port");exit(-1);}
portno=atoi(argv[1]);
socketfd=socket(AF_INET,SOCK_STREAM,0);
if(socketfd<0){
printf("erreur de creation ");exit(-1);}
bzero((char*)&serv_addr,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
serv_addr.sin_port=htons(portno);
if (bind(socketfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
printf("erreur de bind \n");exit(-1);}
listen(socketfd,5);
clilen=sizeof(cli_addr);


}
void listtransaction(FILE* f){
    char line[1000];
f=fopen("histo.txt","r");
if (f==NULL){
    printf("probleme d ouverture de fichier");
}

while (fgets(line,sizeof(line),f)){
   printf("%s",line); 
}
}
void communicationavecclient(struct agence agence){
    FILE* historique;
    FILE* vols;
    FILE* facture ;
FILE* f ;
int s=0;
int* tabj;
int *tabs;
tabs=(int*)malloc(agence.nbvols*sizeof(int));
tabj=(int*)malloc(agence.nbvols*sizeof(int));
f=fopen("vols.txt","r");
if (f==NULL){printf("erreur");exit(-1);}
int numberelements;
char *nbplaces;
char *destination;
char line[1000];
while(fgets(line,sizeof(line),f)){
   nbplaces=strtok(line," \t");
   for (int i=0;i<agence.nbvols;i++) {
    if (strcmp(agence.listevolinitial[i],nbplaces)==0){
        nbplaces=strtok(NULL," \t");
printf("la destination est%s",nbplaces);
nbplaces=strtok(NULL," \t");
if (nbplaces !=NULL){
printf("le nombre de place est %s",nbplaces);
 int y=atoi(nbplaces);
 
 nbplaces=strtok(NULL," \t");
 int x=atoi(nbplaces);
tabj[i]=x;
 printf("le prix de place est %d",tabj[i]);
historique=fopen("histo.txt","a+");
 if (historique==NULL){
    printf("erreur fatal");
    exit(-1);

 }
 tabs[i]=y;

    
 
 if (agence.placespourvol[i]>tabs[i]){
    fprintf(historique,"%s\t%d\t%s\t\t%d\t%s\n",agence.listevolinitial[i],atoi(agence.numagence),"demande",agence.placespourvol[i],"impossible");
 }
 else{
    fprintf(historique,"%s\t%d\t%s\t\t%d\t%s\n",agence.listevolinitial[i],atoi(agence.numagence),"demande",agence.placespourvol[i],"success");
 
int test;
if (agence.testannuler==0){
s+=agence.placespourvol[i]*x;
    FILE* fp;
    fprintf(historique,"%s\t%d\t%s\t\t%d\t%s\n",agence.listevolinitial[i],atoi(agence.numagence),"demande",agence.placespourvol[i],"success");
 miseajour(fp,agence.listevolinitial[i],y-agence.placespourvol[i]);
 }
else{
  
agence.placespourvol[i]-=agence.placesannuleepourvol[i];
    s+=0.1*(agence.placesannuleepourvol[i]*tabj[i]);
    s+=agence.placespourvol[i]*x;
   fprintf(historique,"%s\t%d\t%s\t\t%d\t%s\n",agence.listevolinitial[i],atoi(agence.numagence),"demande",agence.placespourvol[i],"success");
     FILE* fp;
 miseajour(fp,agence.listevolinitial[i],y-agence.placespourvol[i]);  
if (agence.placesannuleepourvol[i]>0){
    
    
   fprintf(historique,"%s\t%d\t%s\t\t%d\t%s\n",agence.listevolinitial[i],atoi(agence.numagence),"annulez",agence.placesannuleepourvol[i],"success");
   
    
 

 
    
 
    
 
 

   
   FILE* fp;
 miseajour(fp,agence.listevolinitial[i],y-agence.placespourvol[i]);  

 
 } 
 }
 


 printf("le prix des places est %s",nbplaces);

 
}
}
    }
    }
   }


printf("le montant a payer est %d",s);
factures(facture,atoi(agence.numagence),s);
fclose(historique);

fclose(f);

}
void listvolparreference(FILE* f){
 char buffer[200];

f=fopen("vols.txt","r");
if (f==NULL){printf("erreur");}
char *reference="2000",*Destion;
char *nbplaces;
char *destination;
char line[1000];
printf("donner la reference");
scanf("%s",buffer);
while(fgets(line,sizeof(line),f)){
//printf("%s",line);
nbplaces=strtok(line," \t");
//Destion =strtok(NULL,"");
//nbplaces=strtok(NULL,"");
if (strcmp(buffer,nbplaces)==0){
nbplaces=strtok(NULL," \t");
printf("la destination est%s",nbplaces);
nbplaces=strtok(NULL," \t");
if (nbplaces !=NULL){
 printf("le nombre de place est %s",nbplaces);
 nbplaces=strtok(NULL," \t");
 printf("le prix des places est %s",nbplaces);
}
else{
    printf("could not extract");
}
}
}
fclose(f);
}

void* handleclient(void *arg){
     int client_socket = *(int *)arg;
     FILE* f;
struct sockaddr_in serveradress,clientaddress;
struct agence agence;
int portnumber;
int serversocket;
int clientsocket;
int clientadrsize;
int choix,clientchoice;
char reference[20];
FILE* transaction;
FILE* vols;


int socketfd,newsocketfd,portno,clilen,n;
struct sockaddr_in serv_addr,cli_addr;
char buffer[256],msg[256];
while(1){

struct agence ag;
 

int valread=recv(client_socket,&ag,sizeof(ag),0);


switch (ag.choix){
    case 2:
    printf("nbvols%hd\n",ag.nbvols);
    ag.placespourvol=(int *) malloc(ag.nbvols*sizeof(int));
    if (ag.testannuler==0){
       
 
printf("nbplacesinitial%s\n",ag.buffer);
            
ag.placespourvol=stringToIntArray(ag.buffer,"/",&ag.nbvols);
 for (int i=0;i<ag.nbvols;i++){
    printf("contenuinitial%d\n",ag.placespourvol[i]);
 }       
        


 ag.compressedlistvolinitial=(char*)malloc(ag.nbvols*sizeof(char));



printf("les references%s\n",ag.test);

ag.listevolinitial=string_to_table(ag.test,',',ag.nbvols,*ag.referencevol);
for (int i=0;i<ag.nbvols;i++){
    printf("references%s",ag.listevolinitial[i]);
}

communicationavecclient(ag);

//break;

    }
    else{
        ag.placesannuleepourvol=(int*) malloc(ag.nbvols*sizeof(int));
printf("nbplacesinitial%s\n",ag.buffer);
            
 printf("nbplacescanceled%s\n",ag.buffercancel);       
        

ag.placesannuleepourvol=stringToIntArray(ag.buffercancel,"/",&ag.nbvols);
ag.placespourvol=stringToIntArray(ag.buffer,"/",&ag.nbvols);

ag.listevolinitial=string_to_table(ag.test,',',ag.nbvols,*ag.referencevol);

printf("les references%s\n",ag.test);
printf("nbvols%hd\n",ag.nbvols);
for (int i=0;i<ag.nbvols;i++){
    printf("places intiiaux%d\n",ag.placespourvol[i]);
}
    
 for (int i=0;i<ag.nbvols;i++){
    printf("places cancelled%d\n",ag.placesannuleepourvol[i]);
} 
  communicationavecclient(ag);
    
  
  }
    break;
    
    case 3:
    
    printf("montant %s\n",facture(ag.numagence));
    char* message;
    message=facture(ag.numagence);
    
    send(client_socket,message,strlen(message),0);
    break;
    
    }
    while(1){
    printf("faites un choix \n");
printf("voir l historique des transactions (cliquersur1)\n");
printf("voir la liste des vols (cliquer sur2) \n");
printf("consulter la facture de l agence (cliquer sur 3)\n");
//printf("quitter \n (cliquer sur 4)");
scanf("%d",&choix);
switch(choix){
case 1:listtransaction(transaction);break;
case 2:listvolparreference(vols); break;
case 3:printf("donner l agence dont tu veux chercher la facture\n");

char refagence[20];
scanf("%s",refagence);
if (facture(refagence)!=NULL){
    printf("la facture est \n refagence%s \t montant%s\t",refagence,facture(refagence));
}
else{
    printf("agence non existante");
}
break;



}
break;

 for (int i = 0; i < 7; i++) {
if (client_sockets[i] == client_socket) {
client_sockets[i] = -1;


}



}
}








}
return 0;


}
int main (int argc,char* argv[]){
FILE* f;
int client_count=0;
struct sockaddr_in serveradress,clientaddress;
struct agence agence;
int portnumber;
int serversocket;
int clientsocket;
int clientadrsize;
int choix,clientchoice;
char reference[20];
FILE* transaction;
FILE* vols;
pthread_t t1,t2;

int socketfd,newsocketfd,portno,clilen,n;
struct sockaddr_in serv_addr,cli_addr;
char buffer[256],msg[256];
if (argc<2){fprintf(stderr,"specifier le port");exit(-1);}
portno=atoi(argv[1]);
socketfd=socket(AF_INET,SOCK_STREAM,0);
if(socketfd<0){
printf("erreur de creation ");exit(-1);}
bzero((char*)&serv_addr,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
serv_addr.sin_port=htons(portno);
if (bind(socketfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
printf("erreur de bind \n");exit(-1);}
listen(socketfd,7);
clilen=sizeof(cli_addr);

while(1){
newsocketfd=accept(socketfd,(struct sockaddr*)&cli_addr,&clilen);
if(newsocketfd<0){printf("erreur d acceptation\n");exit(-1);}
printf("%sconnected to server",inet_ntoa(cli_addr.sin_addr));
struct agence ag;
 

 if (pthread_create(&t1, NULL, handleclient, (void *)&newsocketfd) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }

        // Add client socket to array
        client_sockets[client_count++] = newsocketfd;

        // Limit number of clients
        if (client_count >= 7) {
            printf("Maximum number of clients reached. Closing server...\n");
            
        }





}


return 0;





}





