#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int nbrmax[5] = {40, 25, 30, 10, 5};
const int nbrtotal = 110;
int nbrchamb[5] = {0, 0, 0, 0, 0};
int *chambdispo;
const char type[5][20] = {"Simple", "Double", "Triple", "Suite", "Royal"};
const float price[5] = {300, 500, 1000, 4000, 7000};
int disp = 0;
typedef struct Chambre
{
    int num_chambre;
    char type[20];
    float prix;
} Chambre;
typedef struct noeudch noeudch;
struct noeudch
{
    Chambre *c;
    noeudch *next;
    noeudch *prev;
};
typedef struct listech
{
    noeudch *first;
    noeudch *last;
    int taille;
} listech;
listech *lch;
void initlistech()
{
    lch=(listech*)malloc(sizeof(listech));
    lch->first = NULL;
    lch->last = NULL;
    lch->taille = 0;
}
int numunique()
{
    int num;
    noeudch *ptr = lch->first;
    bool b;
    do
    {
        b = false;
        printf("Numéro De Chambre:");
        scanf("%d", &num);
        while (ptr)
        {
            if (num == ptr->c->num_chambre)
            {
                b = true;
                printf("Chambre Occupée\n");
                break;
            }
            else
                ptr = ptr->next;
        }
        printf("\n");
    }
    while (b);
    return num;
}

char *suggesetion(char *typech)
{
    int i, j = 0;
    static char t[4][10], s[10];
    for (i = 0; i < 5; i++)
    {
        if (strcmp(typech, type[i]) != 0 && nbrchamb[i] < nbrmax[i])
        {
            strcpy(t[j], type[i]);
            j++;
        }
    }
    if (j < 4)
    {
        printf("\nOn vous propose:\n");
        for (i = 0; i < j; i++)
        {
            printf("\n%s", t[i]);
        }
        do
        {
            scanf("%s", s);
            for (i = 0; i < j; i++)
            {
                if (strcmp(s, t[i]) == 0)
                    return s;
            }
        }
        while (1);
    }
    else
        return typech;
}

char *typechamb()
{
    int i;
    static char s[20];
    do
    {
        printf("\nType De Chambre  :");
        scanf("%s", s);
        strcpy(s, suggesetion(s));
        for (i = 0; i < 5; i++)
        {
            if (strcmp(s, type[i]) == 0)
            {
                nbrchamb[i]++;
                return type[i];
            }
        }
        printf("\nType inexistant\n");
    }
    while (1);
}

float prix(char *s)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (strcmp(s, type[i]) == 0)
        {
            printf("Le prix          :%.2f\n", price[i]);
            return price[i];
        }
    }
}

Chambre *creerchambre()
{
    Chambre *ptr = (Chambre *)malloc(sizeof(Chambre));
    ptr->num_chambre = numunique();
    strcpy(ptr->type, typechamb());
    ptr->prix = prix(ptr->type);
    return ptr;
}

void ajouterchambre()
{
    noeudch *nv = (noeudch *)malloc(sizeof(noeudch));
    nv->c = creerchambre();
    disp++;
    chambdispo = (int *)realloc(chambdispo, disp * sizeof(int));
    chambdispo[disp - 1] = nv->c->num_chambre;
    lch->taille++;
    nv->next = NULL;
    nv->prev = lch->last;
    if (lch->last)
        lch->last->next = nv;
    else
        lch->first = nv;
    lch->last = nv;
}

void supprimerchambre(int id)
{
    if (lch->taille > 0)
    {
        printf("Entrez le numéro de la chambre à supprimer\n");
        scanf("%d", &id);
        noeudch *ptr = lch->first, *tmp;
        if (lch->taille >= 1)
        {
            if (lch->taille == 1)
            {
                lch->last = lch->first = NULL;
                lch->taille = 0;
                tmp = ptr;
            }
            else
            {
                while (ptr)
                {
                    if (ptr->c->num_chambre == id)
                    {
                        tmp = ptr;
                        break;
                    }
                    ptr = ptr->next;
                }
            }
            if (!tmp->next)
            {
                tmp->prev->next = NULL;
            }
            else if (!tmp->prev)
            {
                tmp->next->prev = NULL;
            }
            else
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }
            lch->taille--;
            disp--;
            chambdispo = (int *)realloc(chambdispo, disp * sizeof(int));
            printf("Chambre supprimée\n");
            free(tmp);
        }
    }
    else
    {
        printf("\n Aucune chambre est réservée\n");
    }
}

void afficherchambre(Chambre *c)
{
    printf("Numéro De Chambre:%d\n", c->num_chambre);
    printf("Type De Chambre  :%s\n", c->type);
    printf("Prix             :%.2f\n", c->prix);
}

void consulterchambre()
{
    if(lch->first!=NULL)
    {
        if (lch->taille > 0)
        {
            noeudch *ptr = lch->first;
            while (ptr)
            {
                afficherchambre(ptr->c);
                ptr = ptr->next;
            }
        }
        else
        {
            printf("\nAucune chambre est réservée\n");
        }
    }
    else
    {
        printf("\n\tAucune chambre n'est créer en ce moment !");
    }
}

void modifierchambre(int id)
{
    if (lch->taille > 0)
    {
        printf("Entrez le numéro de la chambre\n");
        scanf("%d", &id);
        bool b = false;
        noeudch *ptr = lch->first;
        while (ptr)
        {
            if (id == ptr->c->num_chambre)
            {
                strcpy(ptr->c->type, typechamb());
                ptr->c->prix = prix(ptr->c->type);
                b = true;
                break;
            }
            ptr = ptr->next;
        }
        if (!b)
        {
            printf("\nNuméro non valide\n");
        }
    }
    else
    {
        printf("\n Aucune chambre est réservée\n");
    }
}

void afficherchambrevide()
{
    int t[110], i, j, k = 0;
    for (i = 0; i < nbrtotal; i++)
    {
        bool found = false;
        for (j = 0; j < disp; j++)
        {
            if (chambdispo[j] == i)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            t[k] = i;
            k++;
        }
    }
    printf("Les chambres disponibles sont:\n");
    for (i = 0; i < k; i++)
    {
        printf("\n%d et son type est:", t[i]);
        if (t[i] < 40)
            printf("%s", type[0]);
        else if (t[i] < 65)
            printf("%s", type[1]);
        else if (t[i] < 95)
            printf("%s", type[2]);
        else if (t[i] < 105)
            printf("%s", type[3]);
        else if (t[i] < 110)
            printf("%s", type[4]);
    }
}



typedef struct Client
{
    char id_client[10];
    char nom[20];
    char prenom[20];
    char CIN[10];
    char tel[10];
} Client;
typedef struct noeudcl noeudcl;
typedef struct noeudcl
{
    noeudcl *next;
    noeudcl *prev;
    Client data;
} noeudcl;
typedef struct listecl
{
    noeudcl *head;
    noeudcl *tail;
} listecl;
listecl *lcl;
void initlistecl()
{
    lcl = (listecl *)malloc(sizeof(listecl));
    lcl->head = NULL;
    lcl->tail = NULL;
}
void afficherclient()
{
    if (lcl->head != NULL)
    {
        noeudcl* aide = lcl->head;
        char id[20];
        printf("Saisissez votre id: ");
        scanf("%s", id);
        int i=0;
        while (aide!= NULL)
        {
            if (strcmp(aide->data.id_client, id) == 0)
            {
                printf("Nom Du Client: %s\n", aide->data.nom);
                printf("Prénom Du Client: %s\n", aide->data.prenom);
                printf("CIN Du Client: %s\n", aide->data.CIN);
                printf("Tél Du Client: %s\n", aide->data.tel);
                i++;
            }
            aide = aide->next;
        }
        if(i== 0)
        {

            printf(" ce client existe pas !!\n");
        }
    }
    else
    {
        printf("La liste des clients est vide !!\n");
    }

}
void consulterclient()
{
    if(lcl->head!=NULL)
    {
        noeudcl* aide = lcl->head;
        while (aide!= NULL)
        {
            printf("Id: %s\n", aide->data.id_client);
            printf("Nom : %s\n", aide->data.nom);
            printf("Prénom : %s\n", aide->data.prenom);
            printf("CIN : %s\n", aide->data.CIN);
            printf("Tél : %s\n", aide->data.tel);
            aide = aide->next;
        }
    }
    else
    {
        printf("La liste des clients est vide !!\n");
    }
}

void  modifierclient()
{
    if(lcl->head!=NULL)
    {
        noeudcl* aide = lcl->head;
        char id[20];
        printf("Saisissez votre id: ");
        scanf("%s", id);
        while (aide != NULL)
        {
            if (strcmp(aide->data.id_client, id) == 0)
            {
                printf("\nNouveau Nom: ");
                scanf("%s", aide->data.nom);
                printf("\nNouveau Prénom: ");
                scanf("%s", aide->data.prenom);
                printf("\nNouveau CIN: ");
                scanf("%s", aide->data.CIN);
                printf("\nNouveau Tel: ");
                scanf("%s", aide->data.tel);
            }
            aide = aide->next;
        }
    }
    else
    {
        printf("Client introuvable ou liste vide\n");
    }
}
void supprimerclient()
{
    if(lcl->head!=NULL)
    {
        noeudcl* aide = lcl->head;
        int i = 0;
        char id[20];
        printf("Saisissez votre id: ");
        scanf("%s", id);

        while (aide != NULL)
        {
            noeudcl* s = NULL;
            if (strcmp(aide->data.id_client, id) == 0)
            {
                s = aide;
                if(aide->prev && aide->next)
                {
                    aide->prev->next = aide->next;
                    aide->next->prev = aide->prev;
                }
                else if(!aide->prev && !aide->next)
                {
                    aide->next=aide->prev=NULL;
                }
                else
                {
                    if(!aide->prev)
                    {
                        lcl->head=aide->next;
                        aide->next->prev=NULL;
                    }
                    if(!aide->next)
                    {
                        lcl->tail=aide->prev;
                        aide->prev->next=NULL;
                    }
                }
                free(s);
                printf("Client supprimé\n");
                i=1;
                break;
            }
            aide = aide->next;
        }
        if (i == 0)
        {
            printf("Client introuvable\n");
        }
    }
    else
    {
        printf("Liste est encore vide!\n");
    }
}
void creerclient()
{
    char id[20];
    noeudcl* aide;
    noeudcl* p = (noeudcl*)malloc(sizeof(noeudcl));
    p->prev = NULL;
    int i;
    do
    {
        printf("Saisir un id client: ");
        scanf("%s", id);
        i = 0;
        aide = lcl->head;
        while (aide != NULL)
        {
            if (strcmp(aide->data.id_client, id) == 0)
            {
                i = 1;
                break;
            }
            aide = aide->next;
        }
        if (i != 0)
        {
            printf("Ce client existe déjà\n");
        }
    }
    while (i != 0);
    strcpy(p->data.id_client, id);
    printf("Nom Du Client:\n");
    scanf("%s", p->data.nom);
    printf("Prenom Du Client:\n");
    scanf("%s", p->data.prenom);
    printf("CIN Du Client:\n");
    scanf("%s", p->data.CIN);
    printf("Tel Du Client:\n");
    scanf("%s", p->data.tel);

    if (lcl->head)
    {
        p->next = lcl->head;
        lcl->head->prev = p;
        lcl->head = p;
    }
    else
    {
        p->next=NULL;
        lcl->head = p;
        lcl->tail = p;
    }
}
typedef struct date
{
    int j;
    int m;
    int a;
} date;
typedef struct reservation
{
    char id[6];
    date d;
    int nb_nuit;
    date debut_sejour;
    date fin_sejour;
    float montant_avance;
    char idclient[6];
    int num_chambre;
} reservation;
typedef struct ctrl_res
{
    reservation r;
    struct ctrl_res *next;
    struct ctrl_res *prev;
} ctrl_res;
typedef struct listeres
{
    ctrl_res *head;
    ctrl_res *tail;
} listeres;
listeres *lr;
void initres()
{
    lr=(listeres*)malloc(sizeof(listeres));
    lr->head=NULL;
    lr->tail=NULL;
}
//vérifier si la chambre est dispo
/*int verchambre()
{
    ctrl_res *tmp;
    int chambre,c;
    do
    {
        printf("Saisir numero de chambre:\n");
        scanf("%d",&chambre);
        c=0;
        tmp=lr->head;
        while(tmp!=NULL)
        {
            if(tmp->r.num_chambre==chambre)
            {
                printf("Pas disponibilite !!\n");
                c++;
            }
            tmp=tmp->next;
        }
    }
    while(c!=0);
    return chambre;
}*/
reservation remp()
{
    reservation r;
    ctrl_res *tmp=lr->head;
    int t=0;
    printf("+++++++++++++++++++++++++++++++++++\n");
    do
    {
        printf("Saisir Date :");
        scanf("%d %d %d",&r.d.j,&r.d.m,&r.d.a);
    }
    while((r.d.j<1 || r.d.j>31)||(r.d.m<1 || r.d.m>12)|| r.d.a!=2023 );
    do
    {
        printf("Saisir id_reservation:");
        scanf("%s",r.id);
        tmp = lr->head;
        t = 0;
        while(tmp!=NULL)
        {
            if(strcmp(tmp->r.id,r.id)==0)
            {
                t++;
            }
            tmp=tmp->next;
        }
        if(t!=0)
        {
            printf("\tCet id reservation deja existe !!\n");
        }
    }
    while(t!=0);
        printf("Saisir id_client:");
        scanf("%s",&r.idclient);
    do
    {
        printf("Saisir date de debut:");
        scanf("%d %d %d",&r.debut_sejour.j,&r.debut_sejour.m,&r.debut_sejour.a);
    }
    while((r.debut_sejour.j<1 || r.debut_sejour.j>31)||(r.debut_sejour.m<1 || r.debut_sejour.m>12)|| (r.d.j+(r.d.m*30)+(r.d.a*365))<(r.debut_sejour.j+(r.debut_sejour.m*30)+(r.debut_sejour.a*365) ));  //vérification de date date de début doit pas etre < date actuel(année)
    do
    {
        printf("Saisir date de fin:");
        scanf("%d %d %d",&r.fin_sejour.j,&r.fin_sejour.m,&r.fin_sejour.a);
    }
    while((r.debut_sejour.j<1 || r.debut_sejour.j>31)||(r.debut_sejour.m<1 || r.debut_sejour.m>12)||r.d.a>r.fin_sejour.a || (r.fin_sejour.j+(r.fin_sejour.m*30)+(r.fin_sejour.a*365))<(r.debut_sejour.j+(r.debut_sejour.m*30)+(r.debut_sejour.a*365) ));
    //nb de nuit formule
    r.nb_nuit=(r.fin_sejour.j+(r.fin_sejour.m*30)+(r.fin_sejour.a*365))-(r.debut_sejour.j+(r.debut_sejour.m*30)+(r.debut_sejour.a*365));
    //verification de disponibilité des chambres
    r.num_chambre=numunique();
    printf("\n");
    printf("Saisir montant avancee:");
    scanf("%f",&r.montant_avance);
    return r;
}
void ajouter_res()
{
    reservation v;
    v=remp();
    ctrl_res *p=(ctrl_res*)malloc(sizeof(ctrl_res));
    p->next=NULL;
    p->prev=NULL;
    if(p!=NULL)
        p->r=v; //à tester pcq v n'est pas un pointeur
    if(lr->head==NULL)
    {
        lr->head=lr->tail=p;
        p->next=p->prev=NULL;
    }
    else
    {
        p->prev=lr->tail;
        lr->tail->next=p;
        lr->tail=p;
    }
}
void affcher_res()
{
    if (lr->head == NULL)
    {
        printf("\n\t++++Pas de reservation jusqu'au moment.++++\n");
    }
    else
    {
        ctrl_res *p=lr->head;
        printf("\n\t++++AFFICHAGE DES RESERVATION++++\n");
        do
        {
            printf("_________________________\n");
            printf("Date :%d/%d/%d\n",p->r.d.j,p->r.d.m,p->r.d.a);
            printf("Debut de sejour :%d/%d/%d\n",p->r.debut_sejour.j,p->r.debut_sejour.m,p->r.debut_sejour.a);
            printf("Fin de sejour :%d/%d/%d\n",p->r.fin_sejour.j,p->r.fin_sejour.m,p->r.fin_sejour.a);
            printf("Id_res :%s\n",p->r.id);
            printf("Id_client :%s\n",p->r.idclient);
            printf("Avance :%.2f DH\n",p->r.montant_avance);
            printf("Nb_nuit :%d Jours\n",p->r.nb_nuit);
            printf("Num_chambre :%d\n",p->r.num_chambre);
            p=p->next;
        }
        while(p!=NULL);
    }
}
void supprimerres()
{
    if(lr->head!=NULL)
    {
        ctrl_res *drop=lr->head;
        char tmp[6];
        printf("\t++++Suppression de reservation++++\n");
        printf("Saisir l'ID de reservation:");
        scanf("%s",&tmp);
        while(drop!=NULL)
        {
            if(strcmp(lr->head->r.id,tmp)==0)
            {
                lr->head=lr->head->next;
                lr->head->prev=NULL;
                free(drop);
            }
            else if(strcmp(lr->tail->r.id,tmp)==0)
            {
                drop=lr->tail;
                lr->tail=lr->tail->prev;
                lr->tail->next=NULL;
                free(drop);
            }
            else
            {
                if(strcmp(drop->r.id,tmp)==0)
                {
                    drop->next->prev=drop->prev;
                    drop->prev->next=drop->next;
                    free(drop);
                }
            }
            drop=drop->next;
        }
    }
    else
    {
        printf("La liste est vide\n");
    }
}
void chercher()
{
    char idr[6];
    int c=0;
    ctrl_res *p=lr->head;
    if(lr->head==NULL)
    {
        printf("\t Error: La liste des reservation est encore vide \n");
    }
    else
    {
        printf("Saisir Id reservation:");
        scanf("%s",&idr);
        while(strcmp(p->r.id,idr)!=0 && p!=NULL)
        {
            p=p->next;
        }
        if(strcmp(p->r.id,idr)==0)
        {
            c++;
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            printf("Date :%d/%d/%d\n",p->r.d.j,p->r.d.m,p->r.d.a);
            printf("Debut de sejour :%d/%d/%d\n",p->r.debut_sejour.j,p->r.debut_sejour.m,p->r.debut_sejour.a);
            printf("Fin de sejour :%d/%d/%d\n",p->r.fin_sejour.j,p->r.fin_sejour.m,p->r.fin_sejour.a);
            printf("Id_res :%s\n",p->r.id);
            printf("Id_client :%s\n",p->r.idclient);
            printf("Avance :%.2f DH\n",p->r.montant_avance);
            printf("Nb_nuit :%d Jours\n",p->r.nb_nuit);
            printf("Num_chambre :%d\n",p->r.num_chambre);
        }
        if(c==0)
        {
            printf("Pas de reservation avec cet ID !");
        }
    }
}
void modify()
{
    ctrl_res *tmp=lr->head;
    if(lr->head !=NULL)
    {
        char idm[5];
        int t=0;
        reservation v;
        printf("Saisir l'Id de reservation à modifier:");
        scanf("%s",&idm);
        while(tmp!=NULL)
        {
            if(strcmp(tmp->r.id,idm)==0)
            {
                printf("\t++++Modification++++\n");
                v=remp(lr);
                tmp->r=v;
                break;
            }
            else
                tmp=tmp->next;
        }
    }
    else
    {
        printf("la liste est encore vide!!\n");
    }
}

int menugenerale()
{
    int choix;
    do
    {
        printf("\nGestion de réservation hôtelière\n");
        printf("1. Gestion des clients\n");
        printf("2. Gestion des chambres\n");
        printf("3. Gestion des réservations\n");
        printf("4. Gestion d'états\n");
        printf("5. Enregistrer\n");
        printf("6. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);
    }
    while (choix < 1 || choix > 6);
    return choix;
}

int menuchamb()
{
    int choix;
    do
    {
        printf("\nGestion des chambres\n");
        printf("1. Nouveau\n");
        printf("2. Consulter\n");
        printf("3. Modifier\n");
        printf("4. Supprimer\n");
        printf("5. Menu\n");
        printf("Choix: ");
        scanf("%d", &choix);
    }
    while (choix < 1 || choix > 5);
    return choix;
}

void gestionclient()
{
    int choix;
    do
    {
        printf("\nMenu Gestion des clients selected.\n");
        printf("1. Création d'un client\n");
        printf("2. Modification\n");
        printf("3. Suppression\n");
        printf("4. Consulter la liste\n");
        printf("5. Afficher vos données\n");
        printf("6. MENU PRINCIPAL\n");
        printf("\nEntrer votre choix: ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            system("cls");
            creerclient();
            break;
        case 2:
            system("cls");
            modifierclient();
            break;
        case 3:
            system("cls");
            supprimerclient();
            break;
        case 4:
            system("cls");
            consulterclient();
            break;
        case 5:
            system("cls");
            afficherclient();
            break;
        default:
            printf("Choix n'est pas valide!!");
        }
    }
    while (choix != 6);
}

void mainfunctionres()
{
    int choix;
    do
    {
        printf("\n\t\t\t________________________________\n");
        printf("\t\t\t****Gestion des réservations****\n");
        printf("\t1. Afficher les réservations\n");
        printf("\t2. Ajouter une réservation\n");
        printf("\t3. Supprimer une réservation\n");
        printf("\t4. Chercher une réservation\n");
        printf("\t5. Modifier une réservation\n");
        printf("\t0. Quitter\n");
        printf("\tSaisir votre choix: ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 0:
            printf("Quitter gestion de réservation !!");
            system("cls");
            break;
        case 1:
            system("cls");
            affcher_res();
            break;
        case 2:
            system("cls");
            ajouter_res();
            break;
        case 3:
            system("cls");
            supprimerres();
            break;
        case 4:
            system("cls");
            chercher();
            break;
        case 5:
            system("cls");
            modify();
            break;
        default:
            printf("\t\tChoix invalide !!");
        }
    }
    while (choix != 0);
}

void mainfunctionchambre()
{
    int id, c, x = 2,y;
    do
    {
        y = menuchamb();
        system("cls");
        switch (y)
        {
        case 1:
            system("cls");
            do
            {
                ajouterchambre();
                printf("Continuer ou non? Si non, appuyez sur 0\n");
                scanf("%d", &c);
            }
            while (c != 0);
            break;
        case 2:
            system("cls");
            consulterchambre();
            break;
        case 3:
            system("cls");
            modifierchambre(id);
            break;
        case 4:
            system("cls");
            supprimerchambre(id);
            break;
        case 5:
            printf("\t\tQuitter");
            break;
        default:
            printf("\n\tchoix invalide !!\n");
        }
    }
    while(y!=5);

}

int gestionhotel()
{
    int y = menugenerale();
    system("cls");
    switch (y)
    {
    case 1:
        gestionclient();
        break;
    case 2:
        mainfunctionchambre();
        break;
    case 3:
        mainfunctionres();
        break;
    default:
        break;
    }
    system("cls");
    return y;
}

#endif // HOTEL_H_INCLUDED
