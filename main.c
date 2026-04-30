#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Type def bax ngado maillon prod o tete
// 
// 
typedef struct produit produit;
typedef struct maillon maillon;
typedef struct stock stock;

struct produit {
    char code[10];
    char nom[50];
    int qte;
    float prix;
};

struct maillon{
    produit p;
    maillon* suivant;
};

struct stock{
    maillon* tete;
};

// ProtoType dl Functions
// 
// 
produit lireProduit();
void afficheProduit(produit p);
float valeurProduit(produit p);
maillon* creerMaillon(produit p);
void intStock(stock *s);
bool codeExiste(stock s,char code[]);
produit* rechercheProduit(stock s, char code[]);
void ajouterProduitDebut(stock* s,produit p);
void ajouterProduitFin(stock* s,produit p);
void supprimerDebut(stock* s);
void supprimerFin(stock* s);
void modifierProduit(stock* s,char code[]);

// L functions
// 
//

// PT 1
produit lireProduit(){
    produit p;

    printf("Entere le code d'un produit");
    scanf("%s",p.code);getchar();

    printf("Entere le nom du produit");
    fgets(p.nom,sizeof(p.nom),stdin);p.nom[strlen(p.nom) - 1]='\0';
    
    printf("Entere la quantite du produit");
    scanf("%d",&p.qte);getchar();

    printf("Entere le prix du produit");
    scanf("%f",&p.prix);getchar();   

    return p;
}
void afficheProduit(produit p){
    printf("|%s\t|%s\t|%d\t|%.2f\t|",p.code,p.nom,p.qte,p.prix);
}
float valeurProduit(produit p){
    return p.prix*p.qte;
}

// PT 2

maillon* creerMaillon(produit p){
    maillon* m = (maillon*)malloc(sizeof(maillon));
    m->p = p;
    m->suivant = NULL; 
    return m;

}

void initStock(stock *s){
    s->tete = NULL;

}

bool codeExiste(stock s,char code[]){
    maillon* ptr;
    ptr = s.tete;
    while (ptr != NULL){
        if (!strcmp(ptr->p.code ,code))
        return true;
        ptr = ptr->suivant;
    }
    return false;

}

produit* rechercheProduit(stock s, char code[]){
    if(!codeExiste(s,code))
        return NULL;
    maillon* ptr;
    ptr = s.tete;
    while (ptr != NULL){
        if (!strcmp(ptr->p.code ,code))
        return &(ptr->p);
        ptr = ptr->suivant;
    }
    return NULL;

}

void ajouterProduitDebut(stock* s,produit p){
    if(codeExiste(*s, p.code)) { printf("erreur..."); return; }
    if(s->tete == NULL)
        s->tete = creerMaillon(p);
    else{
        maillon* newMaillon = creerMaillon(p);
        maillon* TMP = s->tete;
        s->tete = newMaillon;
        newMaillon->suivant = TMP;
    }

}

void ajouterProduitFin(stock* s,produit p){
    if(codeExiste(*s, p.code)) { printf("erreur..."); return; }
    if(s->tete == NULL)
        s->tete = creerMaillon(p);
    else{
        maillon* ptr = s->tete;
        while (ptr->suivant !=NULL)
            ptr = ptr->suivant;
        
        maillon* newMaillon = creerMaillon(p);
        ptr->suivant = newMaillon;
        newMaillon->suivant = NULL;
    }

}

void supprimerDebut(stock* s){
    if(s->tete == NULL) { printf("Votre panier est deja vide!"); return; }

    maillon* TMP = s->tete->suivant;
    free(s->tete);
    s->tete = TMP;

}

void supprimerFin(stock* s){
    if(s->tete == NULL) { printf("Votre panier est deja vide!"); return; }
    
    maillon* ptr = s->tete;
    while (ptr->suivant !=NULL)
        ptr = ptr->suivant;

    free(ptr->suivant);
    ptr->suivant = NULL;

}

void modifierProduit(stock* s,char code[]){
    produit* p = rechercheProduit(*s,code);
    if(p == NULL) {printf("Code Introuvable"); return; }

    char nom[50];
    int qte;
    float prix;


    printf("Donner Nouveau Nom\n:");
    fgets(nom,sizeof(nom),stdin);
    nom[strlen(nom)-1]= '\0';

    printf("Donner Nouvelle Quantite\n:");
    scanf("%d",&qte);getchar();

    printf("Donner Nouveau Prix\n:");
    scanf("%f",&prix);getchar();

    strcpy(p->nom,nom);
    p->prix = prix;
    p->qte = qte;

}