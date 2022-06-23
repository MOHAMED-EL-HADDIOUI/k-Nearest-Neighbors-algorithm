#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "K-NN.h"
//Calculer la distance entre Etudant et Etudant
double CalculsDistance(Etudant e1,Etudant e2)
{
    double x,y,z,t;
    x=pow((e1.math-e2.math),2);
    y=pow((e1.informatique-e2.informatique),2);
    z=pow((e1.francais-e2.francais),2);
    t=pow((e1.physique-e2.physique),2);
    double distance=sqrt(x+y+z+t);
    return distance;
}
//Creation les niveaux
void CreationNiveaux(Niveau tab[])
{
    int i;
    for(i=0;i<3;i++)
    {
        tab[i].niveau=i+1;
        tab[i].nombre=0;
        tab[i].list=NULL;
    }
}
//Creation la classe
Classe Creation(int taille)
{
    Classe c;
    c.n=taille;
	c.tab=(Etudant *)malloc(taille*sizeof(Etudant));
    return c;
}
int NombreEtudantFichier(char *Fichier)
{
    
    FILE *fp = fopen(Fichier,"r");
	if (!fp)
	{
		printf("Unable to open file.");
	}
	char buff[1024];
	int row_count=0;
	int field_count=0;
	int i=0;
	while(fgets(buff,1024,fp))
	{
		field_count=0;
		row_count++;
		if(row_count==1)
		   continue;
		char *field;
		field=strtok(buff,",");
		i++;
	}
	fclose(fp);
    return i;
}
Classe SauvegarderClasseFichier(char *Fichier,int taille)
{
    Classe c;
    c=Creation(taille);
    FILE *fp = fopen(Fichier,"r");
	if (!fp)
	{
		printf("Unable to open file.");
	}
	char buff[1024];
	int row_count=0;
	int field_count=0;
	int i=0;
	while(fgets(buff,1024,fp))
	{
		field_count=0;
		row_count++;
		if(row_count==1)
		   continue;
		char *field;
		field=strtok(buff,",");
		while(field)
		{
			if(field_count==0)
			{
				c.tab[i].math=atoi(field);
			}
			if(field_count==1)
			{
				c.tab[i].informatique=atoi(field);
				
			}
			if(field_count==2)
			{
				c.tab[i].physique=atoi(field);
				
			}
			if(field_count==3)
			{
				c.tab[i].francais=atoi(field);
			}
			c.tab[i].niveau=0;
			field=strtok(NULL,",");
			field_count++;
		}
		i++;
	}
	
	fclose(fp);
    return c;
}
void Afficher( Classe c)
{
    int i;
    printf("-------------les informations de la classe---------\n");
    for(i=0;i<c.n;i++)
    {
            printf("Etudant %d { Niveau: %d,Informatique: %lf,Math: %lf,Physique: %lf,Francais: %lf }",i+1,c.tab[i].niveau,c.tab[i].informatique,c.tab[i].math,c.tab[i].physique,c.tab[i].francais);
            printf("\n");
    }

}

void AfficherNiveau(Niveau NI)
{
    printf("-------------les informations de le Niveau---------\n");
    printf("le niveau %d :\n",NI.niveau);
    printf("le nombre %d :\n",NI.nombre);
    int i;
    for(i=0;i<NI.nombre;i++)
    {
            printf("Etudant %d { Niveau: %d,Informatique: %lf,Math: %lf,Physique: %lf,Francais: %lf }",i+1,NI.list[i].niveau,NI.list[i].informatique,NI.list[i].math,NI.list[i].physique,NI.list[i].francais);
            printf("\n");
    }
}


//Calculer le bary centre d'un niveau
void Barycentre(Niveau *NV)
{
    int i;
    double U1=0,U2=0,U3=0,U4=0;
    for(i=0;i<NV->nombre;i++)
    {
        U1+=NV->list[i].math;
        U2+=NV->list[i].informatique;
        U3+=NV->list[i].physique;
        U4+=NV->list[i].francais;
    }
    NV->centre.math=U1/NV->nombre;
    NV->centre.informatique=U2/NV->nombre;
    NV->centre.physique=U3/NV->nombre;
    NV->centre.francais=U4/NV->nombre;
}

//Determier le niveau d'un etudant
void DetermierNiveau( Etudant *e,Niveau TabNiveau[])
{
    double distance[3];
    int i;
    for (i=0;i<3;i++)
    {
        distance[i]=CalculsDistance(*e,TabNiveau[i].centre);
    }
    int position;
    double min=distance[e->niveau-1];
    for(i=0;i<3;i++)
    {
        if(distance[i]<min)
        {
            min=distance[i];
        }
    }
    for(i=0;i<3;i++)
    {
        if(distance[i]==min)
        {
            position=i+1;
        }
    }
    e->niveau=position;
}


//Ajouter un etudant a un niveau
void AjouteEtudantVersNiveau(Etudant *e,Niveau *NI)
{   
    e->niveau=NI->niveau;
    NI->list=(Etudant *)realloc(NI->list,(NI->nombre+1)*sizeof(Etudant));
    NI->list[NI->nombre++]=*e;
}
//Suprimer un etudant from niveau
void FreeEtudantNiveau(int Indice,Niveau *NV)
{
    int i;
    Etudant *E;
    E=(Etudant *)realloc(NV->list,(NV->nombre)*sizeof(Etudant));
    for (i=Indice+1;i<NV->nombre;i++)
    {
        NV->list[i-1]=E[i];
    }
    NV->list=(Etudant *)realloc(NV->list,(NV->nombre-1)*sizeof(Etudant));
    NV->nombre=NV->nombre-1;
}
//restruction les niveaux
void StructionNiveaux(Niveau NV[])
{
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<NV[i].nombre;j++)
        {
            DetermierNiveau(&NV[i].list[j],NV);
        }
    }
    Niveau N[3];
    CreationNiveaux(N);
    for(i=0;i<3;i++)
    {
        for(j=0;j<NV[i].nombre;j++)
        {
            if(NV[i].list[j].niveau==1)
            {
                AjouteEtudantVersNiveau(&NV[i].list[j],&N[0]);
            }
            if(NV[i].list[j].niveau==2)
            {
                AjouteEtudantVersNiveau(&NV[i].list[j],&N[1]);
            }
            if(NV[i].list[j].niveau==3)
            {
                AjouteEtudantVersNiveau(&NV[i].list[j],&N[2]);
            }
        }
    }

    int h;
    for(h=0;h<3;h++)
    {
        NV[h]=N[h];
    }

}
//=================================================================================================== 
void ClasseVersNiveau(Classe *C,Niveau TabNiveau[])
{
    //iteraation 0
    int i;
    int i1=0,i2=0,i3=0;
    for(i=0;i<C->n;i++)
    {
        
        if(C->tab[i].math>15)
        {
        	i1=i1+1;
            AjouteEtudantVersNiveau(&C->tab[i],&TabNiveau[0]);
            
        }
        if(C->tab[i].math<=15 && C->tab[i].math>=10)
        {
            i2=i2+1;
            AjouteEtudantVersNiveau(&C->tab[i],&TabNiveau[1]);

        }
        if(C->tab[i].math<10)
        {
        	i3=i3+1;
            AjouteEtudantVersNiveau(&C->tab[i],&TabNiveau[2]);
        }
    }
    for(i=0;i<3;i++)
    {
        Barycentre(&TabNiveau[i]);
    }


}

void classification(Niveau TabNiveau[])
{   
    int i,j;
    for(j=0;j<3;j++)
    {
        for(i=0;i<3;i++)
         {
        Barycentre(&TabNiveau[i]);
         }
        StructionNiveaux(TabNiveau);
    }
}


Etudant saisir()
{
    Etudant E;
    printf("-------------Entrez les informations de l'etudant---------\n");
    printf("- Informatique:\n");
    scanf("%lf",&E.informatique);
    printf("- Math:\n");
    scanf("%lf",&E.math);
    printf("- Physique:\n");
    scanf("%lf",&E.physique);
    printf("- Francais:\n");
    scanf("%lf",&E.francais); 
    return E;     
}
void AjouteEtudantVersClasse( Classe *C,Etudant E)
{
    C->n=C->n+1;
    Etudant *t,*R;
    t=(Etudant *)realloc(C->tab,C->n*sizeof(Etudant));
    t[C->n-1]=E;
    R=C->tab;
    C->tab=t;
    free(R);
}

int main() 
{
    
    int i;
    Classe c;
    Niveau Niveaux[3];
    CreationNiveaux(Niveaux);
    int y;
    Etudant E;
  do
  {
    printf("|_______________________________________________________________________|\n");
    printf("|_______________APPLICATION : (k-Nearest Neighbors algorithm)___________|\n");
    printf("|_______________________________________________________________________|\n");
    printf("|____________________Realise par : EL HADDIOUI MOHAMED__________________|\n");
    printf("|____________________________Filiere II-BDCC____________________________|\n");
    printf("|_______________________________________________________________________|\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("|_________________________________MENU__________________________________|\n");
    printf("|        { 1}|=> Afficher les listes d'etudants dans la classe          |\n");
    printf("|        { 2}|=> Afficher les listes d'etudants des diffrent Niveaux    |\n");
    printf("|        { 3}|=> Ajoute une etudant                                     |\n");
    printf("|        { 4}|=> Appliquer l'algorithm                                  |\n");
    printf("|                            {0}|=> Quttier                             |\n");
    printf("|_______________________________________________________________________|\n");
    printf("\n");
    
    printf("|_____________________Veullez choisir une action _______________________|\n");
    scanf("%d",&i);
    system("cls");
    printf("|_______________________________________________________________________|\n");
    switch (i)
    {
    case 1:
              printf("--------------------------------------------------------------------\n");
              c=SauvegarderClasseFichier("Data.csv",NombreEtudantFichier("Data.csv"));
              Afficher(c);
              printf("--------------------------------------------------------------------\n");
        break;
    case 2:
            ClasseVersNiveau(&c,Niveaux);
            for(y=0;y<3;y++)
            {
                printf("--------------------------------------------------------------------\n");
                AfficherNiveau(Niveaux[y]);
                printf("--------------------------------------------------------------------\n");
            }
        break;
    case 3:
            
            E=saisir();
            FILE *Data=fopen("Data.csv","a");
            fprintf(Data,"\n%lf,%lf,%lf,%lf",E.math,E.informatique,E.physique,E.francais);
            fclose(Data);
            c=SauvegarderClasseFichier("Data.csv",NombreEtudantFichier("Data.csv"));
        break;
    case 4:
            classification(Niveaux);
            
        break;
    default:
        break;
    }
  } while (i!=0);
system("pause");
    
}
