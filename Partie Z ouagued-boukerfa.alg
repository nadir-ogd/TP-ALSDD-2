SOIENT
  V UN VECTEUR(10) DE ARB DE (CHAINE , CHAINE , ENTIER , CAR);
  A UN ARB DE ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
  B UN ARB DE ( ENTIER , ENTIER , CAR );
  F UN VECTEUR (210) DE (CHAINE , CHAINE , ENTIER , CAR);
  Aleares UNE FONCTION ( CAR );
  Rech  UNE FONCTION (BOOLEEN);
  OccArb , Calcul_Prctg , NBtot , Prctg_Arb DES FONCTIONS (ENTIER);
  CreerArb ,  AffichArb  , InserArb , CreerTab ,  Inser_glob  , Creer_glob , Affich_glob ,
   Aff_tableau , Aff_tab_g  , Affich_Tableau DES  ACTIONS ;
  PERSO : ( ENTIER , ENTIER ,  CAR );
  PERSONNE  : ( CHAINE, CHAINE , ENTIER ,  CAR );
   k ,  tai  , minii , maxii DES ENTIERS;
   cr UN CAR;




/*        Programme Principal         */

DEBUT
   ECRIRE('PRMIERE STRUCTURE  :');
   APPEl CreerTab(V , 10);
   APPEL Affich_Tableau(V , 10);
   ECRIRE('DEUXIEME STRUCTURE  :');
   APPEL Aff_tab_g ( V , F , tai );
   APPEL Creer_glob(B ,  F , tai);
   APPEL Affich_glob( B );
   LIRE(cr);
   LIRE(minii);    /* Entrer la borne minimale de l'age  */
   LIRE(maxii);    /* Entrer la borne maximale de l'age */
   k := Prctg_Arb (F , cr , minii , maxii , tai);
   ECRIRE('LE pourcentage est :');
   ECRIRE(k);

FIN



FONCTION Aleares (H) : CAR    /* fonction qui genere un Resultat (D / R) aleatoirement */
  SOIENT
H , T DES ENTIERS;
c UN CAR;
DEBUT
T := Aleanombre(2);
SI T = 0
    c := 'D';
SINON
    c := 'R';
FSI ;
Aleares := c;
FIN



ACTION InserArb ( T , W ,NOM , PRE , AGE , RES )    /* insertion dans l'arbre de la premiere structure */
   SOIENT

       T , W UN ARB DE ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
       AGE , P DES ENTIERS ;
       PRE , NOM DES CHAINES;
       RES UN CAR;
       PERSONNE : ( CHAINE, CHAINE , ENTIER ,  CAR );
   DEBUT

           SI T = NIL
           CREERNOEUD ( T ) ;
           AFF_STRUCT(PERSONNE , 1 , NOM);
           AFF_STRUCT(PERSONNE , 2 , PRE);
           AFF_STRUCT(PERSONNE , 3 , AGE);
           AFF_STRUCT(PERSONNE , 4 , RES);
           AFF_INFO(T , PERSONNE);

           AFF_FG ( T , NIL ) ;
           AFF_FD ( T , NIL ) ;
           W := T ;

           SINON

           W := NIL ;
           PERSONNE := INFO(T);
               SI AGE <= STRUCT(PERSONNE,3)
                   APPEL InserArb ( FG( T ) , W , NOM , PRE , AGE , RES ) ;
                   SI FG ( T ) = NIL
                           AFF_FG ( T , W );
                   FSI ;
               FSI;
               SI AGE > STRUCT(PERSONNE,3)
                   APPEL InserArb ( FD(T) , W , NOM, PRE , AGE , RES ) ;
                   SI FD ( T ) = NIL
                           AFF_FD ( T , W );
                   FSI ;
               FSI;
           FSI;
   FIN


ACTION CreerArb ( T , Z)    /* Création d'un seul arbre (pays) avec nombre de noeuds aleatoire */
   SOIENT
       V UN VECTEUR (21) DE ( CHAINE, CHAINE , ENTIER , CAR );
       T ,R DES ARB DE ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
       Z ,  choix , age  ,X  DES ENTIER ;
       name , fname DES CHAINES;
       result UN CAR ;
       PERSONNE : (CHAINE , CHAINE , ENTIER , CAR);
   DEBUT


   SI Z >= 1
       POUR X := 1 , Z
           AFF_STRUCT(PERSONNE , 1 , Aleachaine(Aleanombre(5) + 5));
           AFF_STRUCT(PERSONNE , 2 , Aleachaine(Aleanombre(5) + 5));
           AFF_STRUCT(PERSONNE , 3 , Aleanombre(100) + 1);
           AFF_STRUCT(PERSONNE , 4 , AleaRes(choix));
           AFF_ELEMENT ( V [ X ] ,  PERSONNE) ;
           name     :=    STRUCT(ELEMENT ( V [ X ] ),1);
           fname    :=    STRUCT(ELEMENT ( V [ X ] ),2);
           age      :=    STRUCT(ELEMENT ( V [ X ] ),3);
           result   :=    STRUCT(ELEMENT ( V [ X ] ),4);
           APPEL InserArb ( T , R , name , fname , age , result ) ;
       FPOUR;

   FSI;

   FIN


   ACTION AffichArb ( T )  /* Affiche un seul arbre (pays) en inordre (trié) */
   SOIENT
       T UN ARB DE ( CHAINE, CHAINE , ENTIER ,  CAR )  ;
   DEBUT
       SI T <> NIL

           APPEL AffichArb ( FG ( T ) ) ;
           ECRIRE('Nom :');
           ECRIRE ( STRUCT(INFO ( T ) , 1) ) ;
           ECRIRE('Prénom :');
           ECRIRE ( STRUCT(INFO ( T ) , 2) ) ;
           ECRIRE('Age :');
           ECRIRE (STRUCT(INFO ( T ) , 3) ) ;
           ECRIRE('Résultat :');
           ECRIRE ( STRUCT(INFO ( T ) , 4) ) ;
           ECRIRE ('****************');
           APPEL AffichArb ( FD ( T ) ) ;

       FSI;

  FIN



  ACTION Affich_glob ( T )     /* affiche un seul arbre de la deuxieme structure */
   SOIENT
       T UN ARB DE ( ENTIER , ENTIER ,  CAR )  ;
   DEBUT
       SI T <> NIL

           APPEL Affich_glob ( FG ( T ) ) ;

           ECRIRE('Age :');
           ECRIRE ( STRUCT(INFO ( T ) , 1) ) ;
           ECRIRE('Occurence :');
           ECRIRE ( STRUCT(INFO ( T ) , 2) ) ;
           ECRIRE('Résultat :');
           ECRIRE (STRUCT(INFO ( T ) , 3) ) ;
           ECRIRE ('****************');
           APPEL Affich_glob ( FD ( T ) ) ;

       FSI;

  FIN



    ACTION CreerTab ( V , tai )  /* Cree le tableau de 10 pays dans chaque case un arbre (un pays) */
   SOIENT
   V UN VECTEUR(10) DE ARB DE  ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
   A  UN ARB DE ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
   I ,  tai  DES ENTIERS  ;
   DEBUT
   I := 1;
   POUR I := 1 , tai

   /* ECRIRE(' LE PAYS : ');
   ECRIRE(I); */
   APPEl CreerArb(A,Aleanombre(20)+ 1);
   AFF_ELEMENT(V [ I ],A);
   /* APPEL AffichArb(A);
    ECRIRE(' ***************************************************************** ');    */
   A := NIL;

   FPOUR;
   FIN


   ACTION Affich_Tableau(V , tai)  /* Affiche le tableau de 10 pays */
   SOIENT
    V UN VECTEUR(10) DE ARB DE  ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
   J ,  tai  DES ENTIERS  ;
   DEBUT
   J := 1;
   POUR J := 1 , tai
   ECRIRE(' LE PAYS : ');
   ECRIRE(J);
   APPEL AffichArb(ELEMENT(V [ J ]));
   ECRIRE(' ***************************************************************** ');
   FPOUR;
   FIN











      ACTION Inser_glob ( T , W ,AGE , OCC , RES )  /* insertion dans l'arbre de la deuxieme structure */
   SOIENT

       T , W UN ARB DE ( ENTIER , ENTIER , CAR ) ;
       AGE , OCC  DES ENTIERS ;
       RES UN CAR;
       PERSO : ( ENTIER , ENTIER ,  CAR );
   DEBUT

           SI T = NIL
           CREERNOEUD ( T ) ;
           AFF_STRUCT(PERSO , 1 , AGE);
           AFF_STRUCT(PERSO , 2 , OCC);
           AFF_STRUCT(PERSO , 3 , RES);
           AFF_INFO(T , PERSO);
           AFF_FG ( T , NIL ) ;
           AFF_FD ( T , NIL ) ;
           W := T ;

           SINON

           W := NIL ;



               SI ( AGE < STRUCT(INFO(T),1) ) ET ( STRUCT(INFO(T),3) = 'R'  )
                   APPEL Inser_glob ( FG( T ) , W , AGE , OCC ,RES ) ;
                   SI FG ( T ) = NIL
                           AFF_FG ( T , W );
                   FSI ;

               FSI;
               SI  ( AGE > STRUCT(INFO(T),1) ) ET ( STRUCT(INFO(T),3) = 'D'  )
                   APPEL Inser_glob ( FD( T ) , W , AGE , OCC ,RES ) ;
                   SI FD ( T ) = NIL
                           AFF_FD ( T , W );
                   FSI ;
               FSI;
               SI   ( AGE > STRUCT(INFO(T),1) ) ET ( STRUCT(INFO(T),3) = 'R'  )
                   APPEL Inser_glob ( FD( T ) , W , AGE , OCC ,RES ) ;
                   SI FD ( T ) = NIL
                           AFF_FD ( T , W );
                   FSI ;
               FSI;

               SI   ( AGE < STRUCT(INFO(T),1) ) ET ( STRUCT(INFO(T),3) = 'D'  )
                   APPEL Inser_glob ( FG( T ) , W , AGE , OCC ,RES ) ;
                   SI FG ( T ) = NIL
                           AFF_FG ( T , W );
                   FSI ;
               FSI;


           FSI;

FIN





ACTION Creer_glob ( T , F , tai )       /* Creation de l'arbre de la deuxieme structure */
   SOIENT
       F UN VECTEUR (210) DE (CHAINE , CHAINE , ENTIER , CAR);
       T ,R DES ARB DE ( ENTIER , ENTIER ,  CAR ) ;
      X , AG , OC , tai DES ENTIER ;
       RE  UN CAR ;
   DEBUT

       POUR X := 1 , tai  - 1
           AG := STRUCT(ELEMENT( F[ X ] ) , 3);
           RE := STRUCT(ELEMENT( F[ X ] ) , 4);
           OC :=  OccArb ( V , AG , RE );
           APPEL Inser_glob ( T , R , AG , OC , RE );

       FPOUR;

   FIN





FONCTION Rech ( R , AG , RE , trouv ) : BOOLEEN
/* Retourne vrai si trouve la personne avec l'age Ag et le resultat Re */
SOIENT
R UN ARB DE (CHAINE , CHAINE , ENTIER , CAR);
AG  UN ENTIER;
RE UN CAR;
trouv UN BOOLEEN;

DEBUT

SI ( R = NIL )
  trouv := FAUX ;
SINON
     SI ( AG = STRUCT(INFO(R),3) ) ET ( RE = STRUCT(INFO(R),4) )
      trouv := VRAI ;

     SINON
        SI  ( RE = 'D' )   ET   ( AG < STRUCT(INFO(R),3) )
          Rech := Rech( FG(R) , AG , RE , trouv);
        FSI;
        SI  ( RE = 'R' )   ET   ( AG > STRUCT(INFO(R),3) )
          Rech := Rech( FD(R) , AG , RE ,trouv  );
        FSI ;
        SI  ( RE = 'R' )   ET   ( AG < STRUCT(INFO(R),3) )
          Rech := Rech( FG(R) , AG , RE , trouv);
        FSI;
        SI  ( RE = 'D' )   ET   ( AG > STRUCT(INFO(R),3) )
          Rech := Rech( FD(R) , AG , RE , trouv);
        FSI;
     FSI;
FSI;
Rech := trouv;
FIN





FONCTION  OccArb ( V , AGE , RES  ) : ENTIER
 /* Retourne nombre d'occurence De la personne avec l'age Age et le resultat Res dnas tous les pays */
SOIENT
V UN VECTEUR(10) DE ARB DE  ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
A  UN ARB DE ( CHAINE, CHAINE , ENTIER ,  CAR ) ;
AGE , occu , Q  DES ENTIERS ;
RES UN CAR;
trouv UN BOOLEEN;

DEBUT
occu := 0;
POUR Q:= 1 , 10
     trouv := FAUX;
     SI Rech( ELEMENT ( V[ Q ] ) , AGE , RES , trouv ) = VRAI;
     occu := occu + 1;
     FSI;

FPOUR;
OccArb := occu;
FIN




ACTION Aff_tableau ( T , V , I) /* remplir un vecteur depuis un arbre */
   SOIENT
       T UN ARB DE ( CHAINE , CHAINE , ENTIER ,  CAR )  ;
       V UN VECTEUR(210) DE ( CHAINE , CHAINE , ENTIER ,  CAR ) ;
       I UN ENTIER;
   DEBUT
       SI T <> NIL

           APPEL Aff_tableau ( FG ( T ) , V , I) ;
           AFF_ELEMENT( V [ I ] , INFO( T ));
           I := I + 1;
           APPEL Aff_tableau ( FD ( T ) , V , I) ;

       FSI;

  FIN


ACTION Aff_tab_g ( V , W , Z )   /* remplir touts les pays  */
  SOIENT
     V UN VECTEUR (10)  DE ARB DE (CHAINE , CHAINE , ENTIER, CAR);
     W UN VECTEUR (210) DE (CHAINE , CHAINE , ENTIER , CAR);


       I ,J , Z DES ENTIERS;
   DEBUT
   J := 1 ;
   POUR I := 1 , 10

           APPEL Aff_tableau ( ELEMENT( V[ I ] )  , W , J);

   FINPOUR;
   Z := J;
   FIN

   FONCTION  Prctg_Arb  ( F ,  RES ,  mini , maxi , tai)  : ENTIER
    /* Retourne le pourcentage de Resultat "Res" entre l'age Mini et Maxi dans tous les pays */
   SOIENT
   F UN VECTEUR (210) DE (CHAINE , CHAINE , ENTIER , CAR);
   RES UN CAR;
   mini , maxi , tai , som , H , total DES ENTIERS;
   DEBUT

   som := 0;
   POUR H := 1 , tai - 1
   SI (STRUCT(ELEMENT(F[ H ]),3) <= maxi) ET (STRUCT(ELEMENT(F[ H ]),3) >= mini)
        SI STRUCT(ELEMENT(F [ H ]),4) = RES
           som := som +  1 ;
        FSI;
   FSI;
   FPOUR;
   total := NBtot ( F , RES , tai );
   Prctg_Arb :=  Calcul_Prctg (som , total );

   FIN




FONCTION Calcul_Prctg (nb , nbtotal ) : ENTIER  /* calcul pourcnetage de Nb tel que le nombre total est Nbtotal */
SOIENT
Calc , nb , nbtotal DES ENTIERS;

DEBUT
calc := 0;
SI nbtotal <> 0
calc := nb * 100 ;
calc := ( calc / nbtotal );
Calcul_Prctg := Calc;
FSI;
FIN


FONCTION NBtot ( F , RE , tai ) : ENTIER        /* Retourne le nombre total de resultat "Re" dans tous le */
SOIENT
F UN VECTEUR(210) DE (CHAINE , CHAINE , ENTIER, CAR);
RE UN CAR;
J , nb , tai DES ENTIERS;

DEBUT

nb := 0;
POUR J := 1 , tai - 1
SI STRUCT(ELEMENT(F [ J ]) , 4) = RE
   nb := nb + 1;
FSI;
FINPOUR;
NBtot := nb;

FIN
