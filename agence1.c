#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

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


char* int_array_to_string(int* arr, int size) {
    char* str = (char*) malloc((size * 12) * sizeof(char)); // Allocate memory for string
    if (str == NULL) { // Check if memory allocation failed
        printf("Error: Unable to allocate memory.\n");
        return NULL;
    }
    sprintf(str, "%d", arr[0]); // Copy first element to string
    for (int i = 1; i < size; i++) {
        sprintf(str + strlen(str), "/%d", arr[i]); // Append subsequent elements to string
    }
    return str;
}


int main (int argc,char* argv[]){
    int n;
 int socketserver;
 int portnumber;
 struct sockaddr_in serv_addr;
 struct hostent *server; 
 int choix; 
struct demande* demande;
struct choix* choice;
struct agence agences;
char buffer[256];
if (argc<3){
    fprintf(stderr,"erreur fatal");
    exit(1);
}
portnumber=atoi(argv[2]);

socketserver=socket(AF_INET,SOCK_STREAM,0);
//connecti=connect(socketfd,sockadd.sin_addr,200);
if (socketserver<0){
    perror("erreur open socket");
    exit(1);
}
server=gethostbyname(argv[1]);//avoir informations sur machine distante
if (server==NULL){
    fprintf(stderr,"erreur fatal");
    exit(1);

}
bzero((char*)&serv_addr,sizeof(serv_addr));


serv_addr.sin_family=AF_INET;
bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
serv_addr.sin_port=htons(portnumber);
if (connect(socketserver,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
perror("error connecting");
exit(1);
}
  
while (1){

int choix;
printf("/avoir facture (cliquer sur3) \n");
printf("effectuer transaction (cliquer sur2)\n");
scanf("%d",&choix);
switch (choix){
    
    case 2:agences.choix=2;
    printf("donner le num de votre agence\n");
    scanf("%s",agences.numagence);
    agences.placespourvol=(int *) malloc(sizeof(agences.nbvols*sizeof(int)));
    agences.listevolinitial=(char**) malloc(sizeof(agences.nbvols)*sizeof(char*));
    printf("donner le nombre de vols\n");
    scanf("%d",&agences.nbvols);
    

printf("donner les reference de vol \n");
//fflush(stdin);
for (int i=0;i<=agences.nbvols;i++){
  int length=0;
    fgets(agences.referencevol,100,stdin);
   length=strlen(agences.referencevol);
agences.referencevol[length-1]='\0';
agences.listevolinitial[i]=(char*)malloc(length*sizeof(char));

    strcpy(agences.listevolinitial[i],agences.referencevol);
    if (i<agences.nbvols&&i>0){
        strcat(agences.listevolinitial[i],",");
    }
 

}

for (int i=0;i<agences.nbvols;i++){
    printf("donner le nombre de place pour chaque vol \n");
    scanf("%d",&agences.placespourvol[i]);
 } 
printf("testfunction%s",int_array_to_string(agences.placespourvol,agences.nbvols));


printf("votre transaction est pretes voulez vous annulez(ecrire 0/1) ?\n");
scanf("%d",&agences.testannuler);
if (agences.testannuler==0){
   int  indexfinal=0;
   int indexnbplaces=0;
  
   // printf("votre transaction a eté enregistré");
   
  agences.compressedlistvolinitial=(char*)malloc(agences.nbvols*sizeof(char));
    for (int i=0;i<=agences.nbvols;i++){
      
   // printf("%s",agences.listevolinitial[i]);
 
   strcpy(agences.compressedlistvolinitial+indexfinal,agences.listevolinitial[i]);
  
    indexfinal+=strlen(agences.listevolinitial[i]);
}



for (int i=0;i<agences.nbvols;i++){
sprintf(agences.test,"%s",agences.compressedlistvolinitial);
}


 sprintf(agences.buffer,"%s",int_array_to_string(agences.placespourvol,agences.nbvols));

printf("%stest",int_array_to_string(agences.placespourvol,agences.nbvols));

printf("%s",agences.compressedlistvolinitial);

for (int i=0;i<agences.nbvols;i++){
    printf("%d",agences.placespourvol[i]);
    
}

    send(socketserver,&agences,sizeof(agences),0);
    break;
    
}
else{
//fflush(stdin);
int  indexfinal=0;
   int indexnbplaces=0;
  
   // printf("votre transaction a eté enregistré");
   
  agences.compressedlistvolinitial=(char*)malloc(agences.nbvols*sizeof(char));
    for (int i=0;i<=agences.nbvols;i++){
      
   // printf("%s",agences.listevolinitial[i]);
 
   strcpy(agences.compressedlistvolinitial+indexfinal,agences.listevolinitial[i]);
  
    indexfinal+=strlen(agences.listevolinitial[i]);
}



for (int i=0;i<agences.nbvols;i++){
sprintf(agences.test,"%s",agences.compressedlistvolinitial);
}
agences.placesannuleepourvol=(int*)malloc(agences.nbvols*sizeof(int));
for (int i=0;i<agences.nbvols;i++){
printf("donner le nombre de places annulées pour chaque vol\n");
scanf("%d",&agences.placesannuleepourvol[i]);
}
sprintf(agences.buffer,"%s",int_array_to_string(agences.placespourvol,agences.nbvols));
sprintf(agences.buffercancel,"%s",int_array_to_string(agences.placesannuleepourvol,agences.nbvols));



send(socketserver,&agences,sizeof(agences),0);
break;
}



   case 3:
   printf("donner le numero dagence\n");
     scanf("%s",agences.numagence);
     agences.choix=3;
     send (socketserver,&agences,sizeof(agences),0);

   
  char message[1024];
   if (recv(socketserver,message,2000,0)<0){
    puts("non recu");
    break;
   }
    
printf("tu as recu %s",message);
FILE* recu;
recu=fopen("recufacture.txt","w+");
if (recu==NULL){
    printf("error d ouverture de fichier");
}
fprintf(recu,"refageence%smontant%s",agences.numagence,message);
fclose(recu);
break;
} 
}
close(socketserver);
return 0;

}




