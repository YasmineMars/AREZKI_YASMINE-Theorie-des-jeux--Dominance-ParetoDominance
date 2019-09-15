#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct ESD{
	int nbrep;
	int nbDep;
}ESD;
/********************************************************************************************/
 ESD* RepDep (int** T,int* Ns,int nbCom, int nbJ){

  int  i,j,nbrepPrec=1;
  ESD *M ;
  for(i=1;i<nbJ;i++)
  {
    nbrepPrec=nbrepPrec * Ns[i];
  }

     M=malloc(nbJ*sizeof(ESD));
      M[0].nbrep= nbrepPrec;
      M[0].nbDep= nbCom - nbrepPrec;
     for(i=1;i<nbJ;i++)
     {
      M[i].nbrep= nbrepPrec/Ns[i];
      M[i].nbDep=nbrepPrec-M[i].nbrep;
      nbrepPrec=M[i].nbrep;

     }
     return(M);
 }
/*********************************************************************************************/
char**  ConstruireCombinaison( int* Ns , int Ttaille,int nbJ){

    char **combinaison , **alphabet;
    char lettre;
    int i ,j,ns ,l,ik;
    bool incrementer=false;
    int *K;


     alphabet=(char **) malloc(nbJ*sizeof(char*));
     for (i=0; i<nbJ; i++){
     ns=Ns[i];
     alphabet[i]= malloc(ns*sizeof(char));
     }
     lettre='A';
     i=0;//initialiser l'alphabet
      while(i<nbJ)
     {
       j=0;
       printf("\n|les strategies du joueur %d : ",i+1);
       while(j<Ns[i])
         {
          alphabet[i][j]=lettre;
          printf("%c ",alphabet[i][j]);
          j++;
          lettre++;

        }
      i++;

     }
     printf("\n \n");
      K =malloc(nbJ*sizeof(int));
       for(i=0;i<nbJ ; i++)
        {
        K[i]= 0;
        }
     combinaison=(char **)malloc(Ttaille*sizeof(char*));
     for (i=0; i<Ttaille; i++)
     combinaison[i]=(char *) malloc(nbJ*sizeof(char));


     i=0;

     while(i<Ttaille){

      j=0;
        while(j<nbJ){
            combinaison[i][j]=alphabet[j][K[j]];
            j++;
        }

        l=nbJ-1;
        while(l>=0 && incrementer==false){
            if(K[l]<Ns[l]-1){
                K[l]=K[l]+1;
                incrementer=true;
                for(ik=l+1;ik<nbJ;ik++){
                    K[ik]=0;
                }
            }
            else{
                l=l-1;
            }
        }
        i++;
        incrementer=false;
     }
    return (combinaison);
}
/********************************************************************************************/
void Equilibre_En_Strategies_Dominantes(int** T , int* Ns ,int nbCom , int nbJ){

  ESD *M ;
    M=RepDep(T,Ns,nbCom, nbJ);
    ESDominantes(T , Ns , M ,nbCom , nbJ );
}
/*********************************************************************************************/
void ESDominantes(int** T , int* Ns ,ESD* M ,int nbCom , int nbJ ){

   int i=0 ,j,ii,iii ,eliminer1=0 ,eliminer2=0,eliminer3=0, lignei, lignej ,deplignei=0,deplignej=0, k, nbrStraAdv=1;
   int fini=1 , nbrlecture,ct,compteur , nbrepPrec=1,kprime , joueur;
   int nbComPrime;
   int** Tprime ;
   int *Li,*Lj;
   int *Li2 ,*Lj2 , *Nsprime;
   bool supi , supj , ajouterligne;
   ESD *Mprime;

   if(nbCom==1)
        {
        printf("  |L'equilibre en strategie dominante est :\n");

           for(i=0;i<nbCom;i++)
     {
       printf(" [ ");
       for(j=0;j<nbJ;j++)
         {

          printf("%d ",T[i][j]);
        }
       printf("] \n");
     }

       }
    else{ fini=0;}
        if(fini== 0){
           joueur=0;

     while(joueur<nbJ && eliminer1==0){

         k=0;nbrStraAdv=1;
       /**/  /* calculer le nombre de strategies de l'adversaire pour le joueur j*/
         while(k<nbJ)
        {
         if(joueur!=k){
         nbrStraAdv=nbrStraAdv*Ns[k];
         }
          k++;
        }
      /**/ /* fin calcule*/

    //travailler avec la colonne j
    lignei=0;
    deplignei=0;
       while(lignei <= Ns[joueur]-2 && eliminer2==0){

            /*lire la ligne*//***********************************/
               Li=malloc(nbrStraAdv*sizeof(int));
               Li2=malloc(nbrStraAdv*sizeof(int));
               nbrlecture=0;
               ct=deplignei;
               while(nbrlecture < nbrStraAdv){
                  compteur=1;
                    while(compteur <= M[joueur].nbrep){
                        Li[nbrlecture]=T[ct][joueur];
                        Li2[nbrlecture]=ct;
                        nbrlecture=nbrlecture+1;
                        ct=ct+1;
                        compteur=compteur+1;
                      }

                  ct=ct+M[joueur].nbDep;

                    }

           /*fin lire la ligne*//******************************/
          /*  for(i=0;i<nbrlecture ; i++)
                 {
                 printf("[%d]", Li[i]);
                  }
               printf("\n");
        */
         lignej=lignei+1;
         deplignej=deplignei;

         while(lignej<= Ns[joueur]-1 && eliminer3==0){

          deplignej=deplignej + M[joueur].nbrep;

           /*lire la ligne*//***********************************/
               Lj=malloc(nbrStraAdv*sizeof(int));
               Lj2=malloc(nbrStraAdv*sizeof(int));
               nbrlecture=0;
               ct=deplignej;
               while(nbrlecture < nbrStraAdv){
                  compteur=1;
                    while(compteur <= M[joueur].nbrep){
                        Lj[nbrlecture]=T[ct][joueur];
                        Lj2[nbrlecture]=ct;
                        nbrlecture=nbrlecture+1;
                        ct=ct+1;
                        compteur=compteur+1;
                      }
                  ct=ct+M[joueur].nbDep;
                }
           /*fin lire la ligne*//******************************/
      /*  for(i=0;i<nbrlecture ; i++)
        {
        printf("[%d]", Lj[i]);
        }
        printf("\n");*/
    //LA COMPARAISON
    i=0; supi=true ;
    while(i<nbrlecture && supi==true)
    {

        if(Li[i]>Lj[i]){
            i++;
        }
        else { supi=false;}
    }
    if(supi==false){
        i=0;
        supj=true;
         while(i<nbrlecture && supj==true)
         {
            if(Li[i]<Lj[i])
            {
                i++;

            }
            else
            {
                supj=false;
            }

         }
            if(supj==true)
            {
                 nbComPrime= nbCom-nbrlecture;
                 Tprime=(int **) malloc(nbComPrime*sizeof(int*));
                 for (ii=0; ii<nbComPrime; ii++)
                    {
                      Tprime[ii]=(double *) malloc(nbJ*sizeof(int));
                    }
                 i=0;ii=0;
                 while(i<nbCom && ii<nbComPrime)
                    {
                         iii=0; ajouterligne=1;
                         while((iii<nbrlecture) && (ajouterligne==1))
                            {
                                if(i== Li2[iii])
                                    {
                                        ajouterligne=0;
                                    }
                                iii++;
                            }

                        if(ajouterligne==1)
                          {
                           //printf(" (");
                           for(j=0;j<nbJ;j++)
                              {
                                Tprime[ii][j]=T[i][j];
                             // printf("%d ",Tprime[ii][j]);
                               }
                           // printf(" )");
                            ii++;
                          }
                    i++;
                   }
             eliminer1=1;
             eliminer2=1;
             eliminer3=1;

    Nsprime=malloc(nbJ*sizeof(int));
      if (Nsprime == NULL)
        {
            exit(0);
        }
     for(i=0;i<nbJ ; i++)
        {
        Nsprime[i]= Ns[i];
        }
    Nsprime[joueur]=Nsprime[joueur]-1;
    ///creation de Mprime
              for(i=1;i<nbJ;i++)
              {
              nbrepPrec=nbrepPrec * Nsprime[i];
              }
              kprime=nbJ;
              Mprime=malloc(kprime*sizeof(ESD));
              Mprime[0].nbrep= nbrepPrec;
              Mprime[0].nbDep= nbComPrime - nbrepPrec;
              for(i=1;i<kprime;i++)
                  {
                     Mprime[i].nbrep= nbrepPrec/Nsprime[i];
                     Mprime[i].nbDep=nbrepPrec-Mprime[i].nbrep;
                     nbrepPrec=Mprime[i].nbrep;

                   }
     ///fin création

  printf("\n  |Elimination d'une strategie strictement dominee du joueur %d , le nombre de \n   combinaisons est decremente:   %d \n",joueur+1,nbComPrime);
             //printf("nb joueurs:   %d\n",nbJ);
        for(i=0;i<nbComPrime;i++)
     {
       printf(" (");
       for(j=0;j<nbJ;j++)
         {

          printf("%d ",Tprime[i][j]);
        }
       printf(") \n");
     }

             ESDominantes(Tprime , Nsprime , Mprime ,nbComPrime , nbJ );
            }
            else
            {
                  lignej++;
            }
    }
    else
    {
                 nbComPrime= nbCom-nbrlecture;
                 Tprime=(int **) malloc(nbComPrime*sizeof(int*));
                 for (ii=0; ii<nbComPrime; ii++)
                    {
                      Tprime[ii]=(double *) malloc(nbJ*sizeof(int));
                    }
                 i=0;ii=0;
                 while(i<nbCom && ii<nbComPrime)
                    {
                         iii=0;
                         ajouterligne=1;
                         while((iii<nbrlecture) && (ajouterligne==1))
                            {
                                if(i== Lj2[iii])
                                    {
                                        ajouterligne=0;
                                    }
                                iii++;
                            }
                        if(ajouterligne==1)
                          {
                          // printf(" (");
                           for(j=0;j<nbJ;j++)
                              {
                                Tprime[ii][j]=T[i][j];
                             // printf("%d ",Tprime[ii][j]);
                               }
                            ii++;
                            //printf(" )");
                          }
                    i++;
                   }
    eliminer1=1;
    eliminer2=1;
    eliminer3=1;

    Nsprime=malloc(nbJ*sizeof(int));
      if (Nsprime == NULL)
        {
            exit(0);
        }
     for(i=0;i<nbJ ; i++)
        {
        Nsprime[i]= Ns[i];
        }
    Nsprime[joueur]=Ns[joueur]-1;
    //printf("nbr de strategies du joueur %d est %d",j,Ns[j]);
    ///creation de Mprime
              for(i=1;i<nbJ;i++)
              {
              nbrepPrec=nbrepPrec * Nsprime[i];
              }
              kprime=nbJ;
              Mprime=malloc(kprime*sizeof(ESD));
              Mprime[0].nbrep= nbrepPrec;
              Mprime[0].nbDep= nbComPrime - nbrepPrec;
              for(i=1;i<kprime;i++)
                  {
                     Mprime[i].nbrep= nbrepPrec/Nsprime[i];
                     Mprime[i].nbDep=nbrepPrec-Mprime[i].nbrep;
                     nbrepPrec=Mprime[i].nbrep;

                   }
     ///fin création
    printf("\n  |Elimination d'une strategie strictement dominee du joueur %d , le nombre de \n  combinaisons est decremente:   %d \n",joueur+1,nbComPrime);
     for(i=0;i<nbComPrime;i++)
     {
       printf(" (");
       for(j=0;j<nbJ;j++)
         {
          printf("%d ",Tprime[i][j]);
         }
       printf(") \n");
     }
    ESDominantes(Tprime , Nsprime , Mprime ,nbComPrime , nbJ );
    }
         }
         lignei++;
         deplignei=deplignei+M[joueur].nbrep;
       }
     joueur=joueur+1;
     }
     if(eliminer1==0)
        {   printf(" \n ____________________________________________________ \n ");
            printf(" \n Il n'existe pas d'equilibre en strategies dominantes  ");
            printf(" \n ____________________________________________________ \n \n");
        }
   }
}
/*********************************************************************************************/
void Niveau_Securite (int** T , int* Ns ,int nbCom , int nbJ){
    int joueur,str,nbrStra , maximum, minimum ,nbrStraAdv=1 ,i,j,k,dep , compteur,nbrlecture,depstra;

    ESD* M;
    int *Min ,*Max;

    M=RepDep(T,Ns,nbCom, nbJ);
    Max=malloc(nbJ*sizeof(int));

        for(joueur=0;joueur<nbJ;joueur++){
         k=0;nbrStraAdv=1;
         while(k<nbJ)
          {
             if(joueur!=k){
                nbrStraAdv=nbrStraAdv*Ns[k];
              }
          k++;
          }

         nbrStra=Ns[joueur];
         Min=malloc(nbrStra*sizeof(int));
         dep=0;
         depstra=0;
          for(str=0;str<nbrStra;str++){

           dep=depstra;
            minimum=T[dep][joueur];
            compteur=1;
            nbrlecture=0;
            while( nbrlecture < nbrStraAdv){
               while( compteur <= M[joueur].nbrep){
                if(  minimum > T[dep][joueur]){
                   minimum=T[dep][joueur];
                    }
                 dep++;
                 compteur++;
                }
               compteur=1;
               nbrlecture=nbrlecture+M[joueur].nbrep;
               dep=dep+M[joueur].nbDep;
            }
           Min[str]=minimum;

           depstra=depstra+M[joueur].nbrep;

          }
          printf("  |Min( joueur%d )= { ",joueur+1);
          maximum=Min[0];
          printf("%d ",Min[0]);
          for(str=1;str<nbrStra;str++){
              printf("%d ",Min[str]);
            if(maximum<Min[str]){
                maximum = Min[str];
            }
          }
          printf("}\n");
          Max[joueur]=maximum;
    }

   printf("\n  Le niveau de securite de chaque joueur :\n");

    for(j=0;j<nbJ;j++){
        printf("  |Le joueur %d : %d \n",j+1,Max[j]);
    }


}
/*********************************************************************************************/
void Optimum_Pareto (int** T , int nbCom , int nbJ){

    int i,j ,ii,jj;
    bool pareto=true , passerausuivant=false;

  for(i=0;i<nbCom;i++){
        printf("voir :");
             printf("[");
             for(jj=0;jj<nbJ;jj++){
               printf("%d ",T[i][jj]);
             }
             printf("] : ");

    ii=0;
    pareto=true;
    while(ii<nbCom && pareto==true){
       if(i != ii){
       j=0;
       passerausuivant=false;
         while(j<nbJ && passerausuivant==false){
         if(T[ii][j]>= T[i][j]){
            j++;
          }
          else{
            passerausuivant=true;
             printf("[");
             for(jj=0;jj<nbJ;jj++){
            printf("%d ",T[ii][jj]);
             }
           printf("]");
            printf(" ne le domine pas");
          }
         }
         if(j==nbJ)
           {  pareto=false;
            printf("[");
             for(jj=0;jj<nbJ;jj++){
            printf("%d ",T[ii][jj]);
             }
           printf("]");
             printf(" le domine ");
             printf(" ,non pareto \n");
            }
       }
        ii++;
    }

   if(pareto==true){

   printf(" \n ____________________________________________________ \n ");
    printf(" profil pareto dominant :");
    printf("[");
    for(jj=0;jj<nbJ;jj++){
        printf("%d ",T[i][jj]);
    }
    printf("]");
    printf(" \n ____________________________________________________ \n ");
   }
  }
}

/***************************************************************************************/
int main()

{
    int nbJoueurs=0 , nbStr=0 , Ttaille=1 ,i,j,option,booleen=0 , maxNs,l,ik,ns ;
    bool incrementer;
    char* comb;
    int* Ns;
    int* K;
    int **T;
    //int **alphabet , **combinaison;
    char **combinaison;
    char lettre;
    printf(" ______________________________________________________________________________\n");
    printf("\n  | Veuillez Saisir le nombre de joueurs :");
    scanf("%d", &nbJoueurs);

    Ns=malloc(nbJoueurs*sizeof(int));
      if (Ns == NULL)
        {
            exit(0);
        }


     printf("  | Veuillez Saisir le nombre de strategies de chaque joueur :\n");
     for(i=0;i<nbJoueurs ; i++)
        {
        printf("  | Joueur %d: ", i+1);
        scanf("%d", &nbStr);
        Ns[i]= nbStr;

        }

      for(i=0;i<nbJoueurs ; i++)
        {
        Ttaille= Ttaille * Ns[i];
        }
        /******************************************/
      combinaison = ConstruireCombinaison(Ns ,Ttaille,nbJoueurs);
       /***************************************************/


     T=(int **) malloc(Ttaille*sizeof(int*));
     for (i=0; i<Ttaille; i++)
     T[i]=(double *) malloc(nbJoueurs*sizeof(int));

     printf("Sois le jeu sous forme strategique suivante :\n \n");
     for(i=0;i<Ttaille;i++)
     {
         printf(" | ");
          for(j=0;j<nbJoueurs;j++)
         {

          printf("%c ",combinaison[i][j]);
        }


       printf("| = ( ");
       for(j=0;j<nbJoueurs;j++)
         {
             scanf("%d",&T[i][j]);
           //T[i][j]=rand()%10;
           //printf("%d",T[i][j]);

        }
       printf(") \n");
     }
     for(i=0;i<Ttaille;i++)
     {
         printf(" | ");
          for(j=0;j<nbJoueurs;j++)
         {

          printf("%c ",combinaison[i][j]);
        }


       printf("| = ( ");
       for(j=0;j<nbJoueurs;j++)
         {
            // scanf("%d",&T[i][j]);
           //T[i][j]=rand()%10;
           printf("%d ",T[i][j]);

        }
       printf(") \n");
     }

    printf("\n1. Les equilibres en strategies dominantes.\n");
    //printf("2. Les equilibres de Nash.\n");
    printf("3. Le niveau de securite des N joueurs.\n");
    printf("4. L'optimum de pareto dominance.\n");
    printf("5. Quitter.\n");

    while(booleen==0){
    printf(" \n Veuillez choisir une option : ");
    scanf("%d", &option);
    printf("\n");
    switch (option){
        case 1 : Equilibre_En_Strategies_Dominantes(T,Ns,Ttaille,nbJoueurs); break;
       /* case 2 : Equilibre_Nash(T); break;*/
        case 3 : Niveau_Securite(T,Ns,Ttaille,nbJoueurs); break;
        case 4 : Optimum_Pareto(T,Ttaille,nbJoueurs); break;
        case 5:  exit(0) ;
    }
 }
     return 0;
}
