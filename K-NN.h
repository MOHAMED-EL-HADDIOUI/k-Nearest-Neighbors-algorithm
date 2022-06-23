#ifndef _KNN
    #define _KNN
   typedef struct Etudant Etudant;
  struct Etudant{
    double math;
    double informatique;
    double physique;
    double francais;
   	int niveau;
   };
   typedef struct Classe Classe;
  struct Classe{
   	int n;
   	Etudant *tab;  
   };
   typedef struct Niveau Niveau;
  struct Niveau{
    int niveau;
   	int nombre;
   	Etudant centre;
    Etudant *list;
   };
  
   //les fonctions
   void CreationNiveaux(Niveau []);
   double CalculsDistance(Etudant,Etudant);
   Classe Creation(int);
   Classe SauvegarderClasseFichier(char *,int);
   void Afficher( Classe);
   void Barycentre( Niveau *);
   void DetermierNiveau( Etudant *,Niveau []);
   void AjouteEtudantVersNiveau(Etudant *,Niveau *);
   void FreeEtudantFromNiveau(int ,Niveau *);
   void  StructionNiveaux(Niveau []);
   void classification(Niveau []);  
   Etudant saisir();
   void AjouteEtudantVersClasse( Classe *,Etudant );
   void AfficherNiveau(Niveau);
   void ClasseVersNiveau(Classe *,Niveau []);
   int NombreEtudantFichier(char *);
#endif

