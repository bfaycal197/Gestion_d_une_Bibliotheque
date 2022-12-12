#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// déclaration de l'enregistrement  des ouvrages
typedef struct{
      char cote[50] ,Titre[50];
	  int Ne , Nee ;  // Ne : le nombre d'exemplaire dans la bibliothéque ; Nee : le nombre d'exemplaire empruntés
      }ouvrage ;
// declaration de l'enegistrement des etudiants
typedef struct {
       int  MC, PT;// MC : matricule ; PC: pénalité
        char TA ; // TAP : type d'abonnement premiem ;TAC : type d'abonnement classique
      }etudiant;

typedef struct {int JJ,MM,AA;}date; // enregistrement de la date
// enregistrement des emprunts
typedef struct {
       char cote[50];
	   int  MC ;
         date  DE;  // DE : date d'emprunt
         date DR;}emprunt ;

 //declaration de la liste des ouvrages
  typedef struct Liste1 *PlisteOV;
   typedef struct Liste1 {
      ouvrage VAL1;
      PlisteOV Suivo;} Cellule;

 //declaration de la liste des etudiant

 typedef struct Liste2 *PlisteET;
   typedef struct Liste2 {
      etudiant VAL2;
      PlisteET Suive;} Cellule2;

 //déclaration liste des emprunts
 typedef struct Liste3* PlisteEP;
   typedef struct Liste3 {
      emprunt  VAL3;
   PlisteEP Suivp;} Cellule3;

//------------------------------------------------------------------------------

PlisteOV CreerFIFO() {
 PlisteOV  P=NULL,T ; PlisteOV P1; 
     ouvrage x; int i;int n,j,nbr=0;
     char*chaine=(char*)malloc(100+1);char tmp1[]=" "; char s[50];

     	FILE* fichier = NULL; char*nomFich=(char*)malloc(100+1);

	printf("	<<Donner le nom de votre fichier d'ouvrages>>: ");
	gets(nomFich);
	fichier = fopen(nomFich, "r");
	if(fichier==NULL){
		do{
			printf("	//Nous n'avons pas trouver votre fichier, \n	//Si votre fichier ne trouve pas au meme dossier que votre programme\n	//Donner le chemin absolu: ");
			gets(nomFich);
			fichier = fopen(nomFich, "r");
		}while(fichier==NULL);
	}
     rewind(fichier);
     	while (!feof(fichier)){
     		fgets(chaine, 100, fichier); i=0;
     		n=strlen(chaine);if(chaine[n-1]=='\n'){ chaine[n-1]='\0';}
     		char *token = strtok(chaine,tmp1);
     	
   				while(token != NULL){
   			
   					switch(i){
   						case 0:
      					strcpy((x.cote),token);
      					break;
      					case 1:
      						strcpy(s,token);
      					strcpy((x.Titre),s);
      					break;
      					case 2:
      					strcpy(s,token);j=0	;
      					while(s[j]!='\0'){  nbr = nbr*10+(int)s[j] - 48;j++;}
      					(x.Ne)=nbr;nbr=0;
      					break;
      					case 3:
      					strcpy(s,token);j=0	;
      					while(s[j]!='\0'){  nbr = nbr*10+(int)s[j] - 48;j++;}
      					(x.Nee)=nbr;nbr=0;
      					break;
					   }
        			
       				 token = strtok(NULL, tmp1);i++;
   					 }
   					 
					   if(P==NULL){
					   	P=(PlisteOV)malloc(sizeof(Cellule));
					   	P->VAL1=x;
        		  		P->Suivo=NULL;
        		  		P1=P;
					   } 
					   else{
					 
					   	P1->Suivo=(PlisteOV)malloc(sizeof(Cellule)); 
						P1=P1->Suivo; 
						P1->VAL1=x;
						P1->Suivo=NULL;
					
        		  		
					   }
   		
		 }
	
     return P;
}

//procedure affichage
void AfficheOV(PlisteOV T) { 
	PlisteOV P; ouvrage x ;
    P=T; printf("\nLes elements de la liste sont:\n");
    
  while(P!=NULL){
  	x=(P->VAL1);
  	printf("\nla cote est : %s",x.cote);

 	printf("\nle nombre d'exemplaire est : %d",x.Ne);

 	printf("\nle nombre d'exeplaire emprunte est : %d",x.Nee);

  	printf("\nle titre est : %s\n",x.Titre);
             
	 P=P->Suivo;  }
}


//insertion d'un ouvrage 
 void IsertOV (PlisteOV *T){
	int i, NOVA ; // NOVA : le nombre des ouvrages que l'utulisateur  veut ajouter
	PlisteOV p,Q; ouvrage x;
	
	  Q=*T;

 	while (Q->Suivo!=NULL){
  		Q=Q->Suivo ;
	 }
	
	printf ("\n 	//Donner le nombre des ouvrages que vous voullez ajouter a votre liste: ");
  	scanf("%d",&NOVA);

	
for (i=0;i<NOVA;i++){
	printf ("\nVeuillez saisir les caracteristique du l'ouvrage N°%d : \n",i+1);
    printf("Donner la cote: ");
    fflush(stdin);
    scanf("%s",&x.cote);
  	printf("Donner le nombre d'exemplaire dans la bibliotheque: ");
    scanf("%d",&x.Ne);
   	printf("Donner le nombre d'exemplaire emprunte: ");
    scanf("%d",&x.Nee);
  	printf("Donner le titre: ");
    fflush(stdin);
	scanf("%s",&x.Titre);
  p=malloc(sizeof(Cellule));
  p->VAL1=x;
  p->Suivo=NULL;
  Q->Suivo=p;
  Q=Q->Suivo ;
}


}


void ExemplairesDispo (PlisteOV *P1 ,char *titre ,int *n){
int nbr=0; *n=nbr;PlisteOV P=*P1;
//printf("------%s----",titre);
	while(P!=NULL && nbr==0){
		if(!strcmp(P->VAL1.Titre,titre) && P->VAL1.Ne>0 ){nbr++;*n=nbr;*P1=P ;break; }
		P=P->Suivo;
	}
	

}

int MaxOV (PlisteOV P){
	int nbr=0;
	while(P!=NULL){
		nbr= nbr + P->VAL1.Ne;
		P=P->Suivo;
	}
	return nbr;
}

PlisteOV SupprimerOV (PlisteOV *T){
	PlisteOV L=*T; PlisteOV P,Pred;
	char*titre=(char*)malloc(50+1);
	
	printf("	- Donner le titre de votre ouvrage que vous voulez supprimer : ");
	fflush(stdin);
	gets(titre);
	
	P=L;Pred=L;
	while(P!=NULL ){
		if(strcmp(P->VAL1.Titre ,titre )!=0){
			Pred=P;
		P=P->Suivo;
		}else{
			break;
		}

	}
		
	if(P==NULL){
		printf("	Votre ouvrage n'existe pas dans la liste \n");
	}else{
		if(P==L){
			L=L->Suivo;
			free(P);
			*T=L;
		}else{
			Pred->Suivo=P->Suivo;
			free(P);
			*T=L;
		}
	}
	
}


//----les fonctions Etudiant------------------------------------------------------------------------------------------------

PlisteET CreerFIFOET() {
 PlisteET  P=NULL,T ; PlisteET P1; 
     etudiant x; int i;int n,j,nbr=0;
     char*chaine=(char*)malloc(100+1);char tmp1[]=" "; char s[50];

     	FILE* fichier = NULL; char*nomFich=(char*)malloc(100+1);

	printf("	<<Donner le nom de votre fichier d'etudiant>>: ");
	gets(nomFich);
	fichier = fopen(nomFich, "r");
	if(fichier==NULL){
		do{
			printf("	//Nous n'avons pas trouver votre fichier, \n	//Si votre fichier ne trouve pas au meme dossier que votre programme\n	//Donner le chemin absolu: ");
			gets(nomFich);
			fichier = fopen(nomFich, "r");
		}while(fichier==NULL);
	}

     rewind(fichier);
     	while (!feof(fichier)){
     		fgets(chaine, 100, fichier); i=0;
     		n=strlen(chaine);if(chaine[n-1]=='\n'){ chaine[n-1]='\0';}
     		char *token = strtok(chaine,tmp1);
     	
   				while(token != NULL){
   			
   					switch(i){
   						case 0:
      					strcpy(s,token);j=0	;
      					while(s[j]!='\0'){  nbr = nbr*10+(int)s[j] - 48;j++;}
      					(x.MC)=nbr;nbr=0; x.PT=0;
      					break;
      					case 1:
      						strcpy(s,token);
      					if(!strcmp(s ,"Premium")){ x.TA='P';}else{	if(!strcmp(s ,"Classique")){ x.TA='C';  }else{ x.TA='N'; }  }
      					break;
      				
					   }
        			
       				 token = strtok(NULL, tmp1);i++;
   					 }
   					 
					   if(P==NULL){
					   	P=(PlisteET)malloc(sizeof(Cellule2));
					   	P->VAL2=x;
        		  		P->Suive=NULL;
        		  		P1=P;
					   } 
					   else{
        		  		P1->Suive=(PlisteET)malloc(sizeof(Cellule2)); 
						P1=P1->Suive; 
						P1->VAL2=x;
						P1->Suive=NULL;
					   }
   		
		   	  
		 }
     
     return P;
}

//procedure affichage
void AfficheET(PlisteET T) { 
	PlisteET P; etudiant x ; int i=1;
    P=T; printf("\nLes elements de la liste sont:\n");
    
  while(P!=NULL){
  	x=(P->VAL2);
  	printf("\nEtudiant %d matricule: %d",i,x.MC);

	if(x.TA == 'P'){printf("\nEtudiant %d abonnement: Premuim ",i); } else {if (x.TA == 'C') {printf("\nEtudiant %d abonnement: Classique ",i); }else{printf("\nEtudiant %d verifier son abonnement ",i); } }	

 	printf("\nEtudiant %d penalite = %d\n",i,x.PT);
             
	 P=P->Suive;i++;  }
}


//insertion d'un ouvrage 
 void IsertET (PlisteET *T){
	int i, NOVA ; // NOVA : le nombre d'etudiants que l'utulisateur  veut ajouter
	PlisteET p,Q; etudiant x;char s[50];
	
	  Q=*T;

 	while (Q->Suive!=NULL){
  		Q=Q->Suive ;
	 }
	
	printf ("\n 	//Donner le nombre d'etudiants que vous voullez ajouter a votre liste: ");
  	scanf("%d",&NOVA);

	
for (i=0;i<NOVA;i++){
	printf("\nDonner le matricule du l'etudiant N°%d : ",i+1);
	scanf("%d",&x.MC);
	printf("Donner son type d'abonnement ");

	do{		printf("Classique ou Premium? ");
			fflush(stdin);
 			gets(s);
	} while(strcmp(s,"Premium") && strcmp(s,"Classique"));

	if(!strcmp(s ,"Premium")){ x.TA='P';}else{	if(!strcmp(s ,"Classique")){ x.TA='C';  }  }
	x.PT=0;
  p=malloc(sizeof(Cellule2));
  p->VAL2=x;
  p->Suive=NULL;
  Q->Suive=p;
  Q=Q->Suive ;
}

}

void SupprimerET (PlisteET *T){
	PlisteET L=*T; PlisteET P,Pred;
	int matricule;
	
	printf("	- Donner le matricule de l'etudiant que vous voulez supprimer : ");
	scanf("%d",&matricule);
	
	P=L;Pred=L;
	while(P!=NULL ){
		if(P->VAL2.MC != matricule){
		Pred=P;
		P=P->Suive;
		}else{
			break;
		}
		
	}
		
	if(P==NULL){
		printf("	Votre etudiant n'existe pas dans la liste \n");
	}else{
		if(P==L){
			L=L->Suive;
			free(P);
			*T=L;
		}else{
			Pred->Suive=P->Suive;
			free(P);
			*T=L;
		}
	}
	
}


void ModifierET(PlisteET *T){
	int i , NOVA ;
	char s[50];int mat;
		PlisteET Q; etudiant x;
		 Q=*T;	
	
	printf ("\n 	//Donner le nombre d'etudiants que vous voullez Modifier a votre liste: ");
  	scanf("%d",&NOVA);	
	
	for (i=0;i<NOVA;i++){
		
			printf("\nDonner le matricule et le nv abonnement de l'etudiant N°%d\n",i+1);
			printf("Matricule : "); scanf("%d",&mat); printf("Abonnement ");
			do{
			printf("Classique ou Premium? ");
			fflush(stdin);
 			gets(s);
			} while(strcmp(s,"Premium") && strcmp(s,"Classique"));
			
				while (Q->VAL2.MC!=mat && Q->Suive!=NULL ){
  					Q=Q->Suive ;
	 			}
	 			
	 			if(Q!=NULL){	if(!strcmp(s ,"Premium")){ Q->VAL2.TA='P';Q->VAL2.PT=0;}else{ Q->VAL2.TA='C';Q->VAL2.PT=0; }  }else{
	 				printf("Votre Matricule est incorrect");exit(-1);	 }
	 				
	 		 Q=*T;
	}
	
}


//----les fonctions Emprunts----------------------------------------------------------------------

PlisteEP CreerFIFOEP() {
 PlisteEP  P=NULL,T ; PlisteEP P1; 
     emprunt x; int i;int n,j,nbr=0;
     char*chaine=(char*)malloc(100+1);char tmp1[]=" "; char s[50];

     	FILE* fichier = NULL; char*nomFich=(char*)malloc(100+1);

	printf("	<<Donner le nom de votre fichier des Emprunts>>: ");
	gets(nomFich);
	fichier = fopen(nomFich, "r");
	if(fichier==NULL){
		do{
			printf("	//Nous n'avons pas trouver votre fichier, \n	//Si votre fichier ne trouve pas au meme dossier que votre programme\n	//Donner le chemin absolu: ");
			gets(nomFich);
			fichier = fopen(nomFich, "r");
		}while(fichier==NULL);
	}

     rewind(fichier);
     	while (!feof(fichier)){
     		fgets(chaine, 100, fichier); i=0;
     		n=strlen(chaine);if(chaine[n-1]=='\n'){ chaine[n-1]='\0';}
     		char *token = strtok(chaine,tmp1);
     	
   				while(token != NULL){
   			
   					switch(i){
   						case 0:
      						strcpy(s,token);j=0	;
      						while(s[j]!='\0'){  nbr = nbr*10+(int)s[j] - 48;j++;}
      						(x.MC)=nbr;nbr=0; 
      					break;
      					case 1:
      						strcpy(s,token);
      						strcpy((x.cote),s);
      					break;
      					case 2:
      						strcpy(s,token);
      						j=0	;
      						while(s[j]!='\0'){ if(s[j]!='-'){nbr = nbr*10+(int)s[j] - 48;j++;}else{	switch(j){case 2:
      																											x.DE.JJ=nbr;nbr=0;j++; 
      																										  break;
      																										  case 5:
      																											x.DE.MM=nbr;nbr=0;j++;
      																										  break;} }
											 }
							  x.DE.AA=nbr;nbr=0;
      					break;
      					case 3:
      						strcpy(s,token);
      						j=0	;
      						while(s[j]!='\0'){ if(s[j]!='-'){nbr = nbr*10+(int)s[j] - 48;j++;}else{	switch(j){case 2:
      																											x.DR.JJ=nbr;nbr=0;j++;
      																										  break;
      																										  case 5:
      																											x.DR.MM=nbr;nbr=0;j++;
      																										  break;} }
											 }
							  x.DR.AA=nbr;nbr=0;
      					break;
      				
					   }
        			
       				 token = strtok(NULL, tmp1);i++;
   					 }
   					 
					   if(P==NULL){
					   	P=(PlisteEP)malloc(sizeof(Cellule3));
					   	P->VAL3=x;
        		  		P->Suivp=NULL;
        		  		P1=P;
					   } 
					   else{
        		  		P1->Suivp=(PlisteEP)malloc(sizeof(Cellule3)); 
						P1=P1->Suivp; 
						P1->VAL3=x;
						P1->Suivp=NULL;
					   }
   		
		   	  
		 }
     
     return P;
}
//----
void AfficheEP(PlisteEP T) { 
	PlisteEP P; emprunt x ;
    P=T; printf("\nLes elements de la liste des emprunts sont:\n");
    
  while(P!=NULL){
  	x=(P->VAL3);
  	printf("\nle Matricule est : %d",x.MC);

 	printf("\nla cote : %s",x.cote);

 	printf("\nla date d'emprunte est : %d-%d-%d",x.DE.JJ,x.DE.MM,x.DE.AA);

  	printf("\nla date de retour : %d-%d-%d\n",x.DR.JJ,x.DR.MM,x.DR.AA);
             
	 P=P->Suivp;  }
}
//----
void AjouterEP(PlisteEP *T2,PlisteET *T1,PlisteOV *T){
	PlisteEP Q,P,L2=*T2;PlisteET L1=*T1;PlisteOV L=*T; int matricule,nbrPN=8,nbrOV,nbr=0;char *titre=(char*)malloc(50+1);
	
	printf("	-Donner le matricule de l'etudiant qui va emprunter");
	scanf("%d",&matricule);
	
	Q=L2;
		while (Q!=NULL){
			if(Q->VAL3.MC==matricule) nbr++;
  		Q=Q->Suivp;
	 	}
	
	if(nbr<4){
		nbrPN=nombrePN(L1, matricule); // !=0 
	}else{
		printf("	-Vous n'avez pas le droit d'emprunter un live "); // prcq fat le nbr masmoh bih
	}	


if(nbrPN<7 ){
	printf("\n	//Donner l'ouvrage que vous chercher : ");fflush(stdin); gets(titre); 
	ExemplairesDispo (&L,titre,&nbrOV); }else{
	if(nbrPN==7)	printf("	-Vous n'avez pas le droit d'emprunter un live ");
	}	
	// if (nbrOV==0) hna tji la file bon courage

	if(nbrPN<7 && nbrOV!=0 ){
		L->VAL1.Ne--;L->VAL1.Nee++;
		P=malloc(sizeof(Cellule3));
		strcpy(P->VAL3.cote,L->VAL1.cote);
		P->VAL3.MC=matricule;
		printf("	- Donner la date d'aujourd'hui:\n	- Jour: ");scanf("%d",&P->VAL3.DE.JJ);
		printf("	- Mois: ");scanf("%d",&P->VAL3.DE.MM);
		printf("	- Annee: ");scanf("%d",&P->VAL3.DE.AA);
		
		printf("	- Donner la date de retour:\n	- Jour: ");scanf("%d",&P->VAL3.DR.JJ);
		printf("	- Mois: ");scanf("%d",&P->VAL3.DR.MM);
		printf("	- Annee: ");scanf("%d",&P->VAL3.DR.AA);
		L=*T;Q=L2;
		while (Q->Suivp!=NULL){
  		Q=Q->Suivp;
	 	}

  		P->Suivp=NULL;
  		Q->Suivp=P;
  		Q=Q->Suivp ;
			
	}
	
	*T2=L2;*T1=L1;*T=L;
}

//----
void SupprimerEP (PlisteEP *T, int *n ,date *x){
	PlisteEP L=*T; PlisteEP P,Pred; char cote[50];
	int matricule; date x1;
	
	printf("\n	- Donner le matricule de l'etudiant que vous voulez supprimer son emprunte : ");
	scanf("%d",&matricule);
	*n=matricule;
	
	printf("\n	- Donner la cote de l'ouvrage : ");
	fflush(stdin);
	gets(cote);
	
	
	P=L;Pred=L;
	while(P!=NULL ){
		if(P->VAL3.MC != matricule && P->VAL3.cote!=cote){
		Pred=P;
		P=P->Suivp;
		}else{
			break;
		}
		
	}
		
	if(P==NULL){
		printf("	Verifier le matricule ou la cote il y a une erreur dans la saisie \n"); 
	}else{
		x1.JJ=P->VAL3.DR.JJ;
		x1.MM=P->VAL3.DR.MM;
		x1.AA=P->VAL3.DR.AA;
		*x=x1;
		if(P==L){
			L=L->Suivp;
			free(P);
			*T=L;
		}else{
			Pred->Suivp=P->Suivp;
			free(P);
			*T=L;
		}
	}
	
}
// cas spe hadi tae penalite drtha hna prcq nkhdm biha tahtha
void AjouterPN(PlisteET P){
	
	P->VAL2.PT++; 
	printf("\n	- Votre penalite a etait augmenter car vous n'avez pas rendu le livre a temps\n");
	
}
//-----
void RetournerEP (PlisteEP *T, PlisteET *T1){
	PlisteEP L=*T; int mat=0; date x,x1;
	PlisteET P,L1=*T1; 
	
	printf("	- Donner la date d'aujourd'hui:\n	- Jour: ");scanf("%d",&x.JJ);
	printf("	- Mois: ");scanf("%d",&x.MM);
	printf("	- Annee: ");scanf("%d",&x.AA);
	
	SupprimerEP(&L,&mat,&x1);
	
	if(x1.AA<=x.AA && mat!=0){ 
		if(x1.MM<=x.MM){
			
			P=L1;
		while(P!=NULL ){
		if(P->VAL2.MC != mat){
		P=P->Suive;
		}else{
			break;
			}
		}
	
		AjouterPN(P); }else{
			if(x1.JJ<x.JJ){
			P=L1;
		while(P!=NULL ){
		if(P->VAL2.MC != mat){
		P=P->Suive;
		}else{
			break;
			}
		}
		
		AjouterPN(P);
			}
		}
		
	}
	
	*T=L;
	*T1=L1;
}
//--
void ModifierEP(PlisteEP *T){
	PlisteEP P,L=*T;
	int matricule; 
	
	printf("\n	- Donner le matricule de l'etudiant que vous voulez modifier sa date de retour d'emprunte : ");
	scanf("%d",&matricule);

	P=L;
	while(P!=NULL ){
		if(P->VAL3.MC != matricule){
		P=P->Suivp;
		}else{
			break;
		}
		
	}
	
		
	if(P==NULL){
		printf("	Votre etudiant n'existe pas dans la liste \n"); 
	}else{
	printf("	- Donner la nouvelle date de retour:\n	- Jour: ");scanf("%d",&P->VAL3.DR.JJ);
	printf("	- Mois: ");scanf("%d",&P->VAL3.DR.MM);
	printf("	- Annee: ");scanf("%d",&P->VAL3.DR.AA);
	}
	
	*T=L;
}
//---
void dureeEP (){
	printf("	- Chaque etudiant avec un abonnement Classique a une duree de 1 mois, \n	et pour ceux qui dispose d'un abonnement Premium auront une duree de 2 mois\n");
}

//----les pénalités ----------------------------------------------------------------------
void AffichePN(PlisteET T) { 
	PlisteET P; etudiant x ; int i=1;
    P=T; printf("\nLa liste des penalites:\n");
    
  while(P!=NULL){
  	x=(P->VAL2);
  	printf("\nEtudiant %d sa penalite: %d\n",x.MC,x.PT);
             
	 P=P->Suive;i++;  }
}

int nombrePN(PlisteET P , int matricule){
		
	while(P!=NULL ){
		if(P->VAL2.MC != matricule){
		P=P->Suive;
		}else{
			break;
		}	
	}
	
	if(P==NULL){
		printf("	Votre etudiant n'existe pas dans la liste \n"); return 8;
	}else{
		return P->VAL2.PT;
		}
	}



//--------------------------------------------------------------------------
void menuOv(PlisteOV *Q, char*cmpt) {
	char n[50];PlisteOV T=*Q;int nbr; char cmpt1[10];strcpy(cmpt,"oui"); char titre[50];

do{
printf("-------------------------<< Liste des Ouvrages >>-------------------------\n");
printf("1- Ajouter des ouvrages\n");
printf("2- Supprimer un ouvrage\n");
printf("3- Consulter la liste de tous les ouvrages\n");
printf("4- La disponibilite des exemplaires\n");
printf("5- Le maximum d’ouvrage a emprunter\n");
printf("6- Retourner au menu principal\n");

printf("--------------------------- <<o>> --------------------------\n\n");
do{
printf("- veuillez choisir le numero la fonction que vous voulez executer: "); fflush(stdin);gets(n);

} while(n[0]<'1' || n[0]>'6' || n[1]!= '\0') ;

switch (n[0])
  {
    case '1':
       IsertOV(&T);*Q=T;
       break;
    case '2':
       SupprimerOV (&T);*Q=T;
       break;
    case '3':
       AfficheOV(T);
       break;
    case '4':
    		printf("\n	//Donner l'ouvrage que vous chercher : ");fflush(stdin); gets(titre);
       ExemplairesDispo(&T,titre,&nbr);if(nbr==1){ printf("  -Exemplaires de votre ouvrage disponible \n");  }else{ printf("  -Exemplaires de votre ouvrage n'est pas disponible\n"); } 
       nbr=0;T=*Q;
	   break;
    case '5':
       nbr=MaxOV(T);
	   printf("    -Le maximum d'ouvrage disponible a emprunter est : %d ouvrages\n",nbr); printf("	-Et le maximum pour chaque etudiant est 3 ouvrages\n");
       break;
    case '6':
    	strcpy(cmpt,"no");
       break;
 }
 
 
if(strcmp(cmpt,"no")){
	printf("\n 	//Voulez vous reexecuter le menu des Ouvrages? ");
do{
printf("oui ou non? ");
fflush(stdin);
  gets(cmpt1);
} while(strcmp(cmpt1,"oui") && strcmp(cmpt1,"non"));
strcpy(cmpt,cmpt1);
}

   } while(!strcmp(cmpt,"oui"));


}

//--------------------------------------------------------------------------
void menuET(PlisteET *Q, char*cmpt) {
	char n[50];PlisteET T1=*Q;int nbr; char cmpt1[10];strcpy(cmpt,"oui");

do{
printf("-------------------------<< Liste des Etudiants >>-------------------------\n");
printf("1- Ajouter des etudiants\n");
printf("2- Supprimer un etudiant de la liste\n");
printf("3- Consulter la liste de tous les etudiants\n");
printf("4- Modifier un etudiant de la liste\n");
printf("5- Retourner au menu principal\n");

printf("--------------------------- <<o>> --------------------------\n\n");
do{
printf("- veuillez choisir le numero la fonction que vous voulez executer: "); gets(n);

} while(n[0]<'1' || n[0]>'5' || n[1]!= '\0') ;

switch (n[0])
  {
    case '1':
       IsertET(&T1);*Q=T1;
       break;
    case '2':
       SupprimerET(&T1);*Q=T1;
       break;
    case '3':
       AfficheET(T1);
       break;
    case '4':
    	ModifierET(&T1);*Q=T1;
       break;
    case '5':
       strcpy(cmpt,"no");
       break;
 }
 
 
if(strcmp(cmpt,"no")){
	printf("\n 	//Voulez vous reexecuter le menu de la liste des etudiants? ");
do{
printf("oui ou non? ");
fflush(stdin);
  gets(cmpt1);
} while(strcmp(cmpt1,"oui") && strcmp(cmpt1,"non"));
strcpy(cmpt,cmpt1);
}

   } while(!strcmp(cmpt,"oui"));


}
//------------------------------------------------------------------------------
void menuEP(PlisteEP *Q2,PlisteET *Q1,PlisteOV *Q , char*cmpt) {
	char n[50];int nbr; char cmpt1[10];strcpy(cmpt,"oui");
	PlisteET T1=*Q1; PlisteEP T2=*Q2;PlisteOV T=*Q;

do{
printf("-------------------------<< Liste des Emprunts >>-------------------------\n");
printf("1- Ajouter des emprunts\n");
printf("2- Retourner les emprunts\n");
printf("3- Consulter la liste des emprunts\n");
printf("4- Modifier un emprunt de la liste\n");
printf("5- La duree des emprunts\n");
printf("6- Retourner au menu principal\n");

printf("--------------------------- <<o>> --------------------------\n\n");
do{
printf("- veuillez choisir le numero la fonction que vous voulez executer: "); gets(n);

} while(n[0]<'1' || n[0]>'6' || n[1]!= '\0') ;

switch (n[0])
  {
    case '1':
       AjouterEP(&T2,&T1,&T);*Q1=T1; *Q2=T2;*Q=T;
       break;
    case '2':
       RetournerEP(&T2,&T1); *Q1=T1; *Q2=T2;
       break;
    case '3':
       AfficheEP(T2);
       break;
    case '4':
    	ModifierEP(&T2);*Q1=T1; *Q2=T2;
       break;
    case '5':
      dureeEP ();
       break;
    case '6':
       strcpy(cmpt,"no");
       break;
 }
 
 
if(strcmp(cmpt,"no")){
	printf("\n 	//Voulez vous reexecuter le menu de la liste des empruntes ? ");
do{
printf("oui ou non? ");
fflush(stdin);
  gets(cmpt1);
} while(strcmp(cmpt1,"oui") && strcmp(cmpt1,"non"));
strcpy(cmpt,cmpt1);
}

   } while(!strcmp(cmpt,"oui"));


}

//---------------------------------------------
int main(int argc, char *argv[]) {
  char n[50];char *cmpt=(char*)malloc(10+1);
  PlisteOV T=NULL; PlisteET T1; PlisteEP T2;
  
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<< Bienvenue dans notre programme >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
T=CreerFIFO(); T1=CreerFIFOET(); T2=CreerFIFOEP();
do{

printf("------------------------------- Menu Principal -------------------------------\n");
printf("1- Manipuler la liste des Ouvrages\n");
printf("2- Manipuler la liste des Etudiants\n");
printf("3- Manipuler la liste des Emprunt\n");
printf("4- Consulter la liste des Penalites\n");
printf("------------------------------- <<o>> ------------------------------\n\n");
do{
printf("- veuillez choisir le numero de la liste que vous voulez manipuler: "); gets(n);

} while(n[0]<'1' || n[0]>'4' || n[1]!= '\0') ;

 switch (n[0])
  {
    case '1':
       menuOv(&T,cmpt);
       break;
    case '2':
       menuET(&T1,cmpt);
       break;
    case '3':
       menuEP(&T2,&T1,&T,cmpt);
       break;
    case '4':
    	AffichePN(T1);strcpy(cmpt,"non");
       break;

  }
//*************************************reexecution******************************
if(!strcmp(cmpt,"non")){
	  printf("\n 	//Voulez vous quitter le programme? ");
do{
printf("oui ou non? ");
fflush(stdin);
  gets(cmpt);
} while(strcmp(cmpt,"oui") && strcmp(cmpt,"non"));
}else{
	strcpy(cmpt,"non");
}


 } while(!strcmp(cmpt,"non"));

  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<< Merci d'avoir utiliser notre programme >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  
    return 0;
}
