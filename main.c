#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */
typedef struct
{
    char ll[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool enc;   // La paraula s'ha encertat
    int pos;    // La posicio inicial de la paraula
} paraula_t;

typedef struct
{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
    FILE *paraules;  //Fitxer que conte paraules de la sopa de lletres
} sopa_t;

/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas només l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pròpia. */
int cmp_paraula_t(const void *a, const void *b)
{
    paraula_t *pa = (paraula_t *) a;
    paraula_t *pb = (paraula_t *) b;
    return strcmp(pa->ll, pb->ll);
}

void llegir_paraules(sopa_t *s)
{
    int i;

    i=0;
    s->paraules=fopen("paraules4.txt","r");

    while(fgets(s->par[i].ll,MAX_LLETRES+1,s->paraules) != NULL){
        s->par[i].ll[strcspn(s->par[i].ll, "\n")] = '\0';  // Elimina los '\n' sobrantes
        i++;
        s->n_par=i;
    }
    fclose(s->paraules);

    qsort(s->par, s->n_par, sizeof(paraula_t), cmp_paraula_t);
}
void genera_sopa(sopa_t *s)
{
    /*s->dim = 30;*/    // Mida màxima: 40 x 40
    printf("Alo.\n");
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        s->encertades[i] = false;
        // Generem una lletra aleatoriament
        s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
    }
    s->n_encerts = 0;

    /*s->n_par = 5;
    strcpy(s->par[0].ll, "ALZINA");
    strcpy(s->par[1].ll, "ARBUST");
    strcpy(s->par[2].ll, "BOLET");
    strcpy(s->par[3].ll, "CAMI");
    strcpy(s->par[4].ll, "PEDRA");

    s->n_encerts = 2;
    s->par[0].enc = false;
    s->par[1].enc = true;
    s->par[2].enc = true;
    s->par[3].enc = false;
    s->par[4].enc = false;*/

    // Ara posem un parell de paraules a la sopa com si s'haguessin encertat
    /*s->lletres[5] = 'B'; s->encertades[5] = true;
    s->lletres[6] = 'O'; s->encertades[6] = true;
    s->lletres[7] = 'L'; s->encertades[7] = true;
    s->lletres[8] = 'E'; s->encertades[8] = true;
    s->lletres[9] = 'T'; s->encertades[9] = true;

    s->lletres[65 + s->dim] = 'A'; s->encertades[65 + s->dim] = true;
    s->lletres[65 + 2 * s->dim] = 'R'; s->encertades[65 + 2 * s->dim] = true;
    s->lletres[65 + 3 * s->dim] = 'B'; s->encertades[65 + 3 * s->dim] = true;
    s->lletres[65 + 4 * s->dim] = 'U'; s->encertades[65 + 4 * s->dim] = true;
    s->lletres[65 + 5 * s->dim] = 'S'; s->encertades[65 + 5 * s->dim] = true;
    s->lletres[65 + 6 * s->dim] = 'T'; s->encertades[65 + 6 * s->dim] = true;*/

}


/* Mostra la sopa de lletres pel terminal */

void ficar_paraules(sopa_t *s)
{
    int inici; /*Inici paraula*/
    int lle;   /*Posicio lletres*/
    int paraula;
    int num_lletres;
    int j;
    int a;
    int poscicio;
    int comprovar;

    srand(time(NULL));
    paraula = 0;
    a = 0;
    lle = 0;
    j = 1;
    do
    {
        inici = rand() % (s->dim*s->dim) + 1;
        j = rand() % 4+1;
        switch (j)
        {
        case 1: /* Dreta*/
            {
                comprovar = 0;
                poscicio = inici;
                num_lletres = strlen(s->par[paraula].ll);
                while(comprovar <  num_lletres)
                {
                    while((inici + num_lletres  > s->dim*s->dim) && (inici + num_lletres > s->dim+1))
                          {
                             inici = rand() % (s->dim*s->dim) + 1;
                          }
                    if(s->encertades[poscicio] == true)
                        {
                            inici = rand() % (s->dim*s->dim) + 1;
                            poscicio = inici;
                            comprovar = 0;
                        }
                    else
                    {
                        comprovar ++;
                        poscicio ++;
                    }
                }
                s->par[paraula].pos = inici;
                do
                {
                    s->lletres[inici + a] = s->par[paraula].ll[lle]; /*s->encertades[inici + a] = true;*/
                    lle++;
                    a ++;
                }
                while(num_lletres > a);
                break;
            }
        case 2: /*Esquerra*/
            {
                comprovar = 0;
                poscicio = inici;
                num_lletres = strlen(s->par[paraula].ll);
                while(comprovar < num_lletres)
                {
                    while((inici - num_lletres < num_lletres) && (inici - num_lletres < s->dim+1))
                          {
                             inici = rand() % (s->dim*s->dim) + 1;
                          }
                    if(s->encertades[poscicio] == true)
                        {
                            inici = rand() % (s->dim*s->dim) + 1;
                            poscicio = inici;
                            comprovar = 0;
                        }
                    else
                    {
                        comprovar ++;
                        poscicio --;
                    }
                }
                s->par[paraula].pos = inici;
                do
                {
                    s->lletres[inici - a] = s->par[paraula].ll[lle]; /*s->encertades[inici - a] = true;*/
                    lle++;
                    a ++;
                }
                while(num_lletres > a);
                break;
                }
        case 3: /*Dalt*/
            {
                    comprovar = 0;
                    poscicio = 1;
                    num_lletres = strlen(s->par[paraula].ll);
                    while(comprovar < num_lletres)
                    {
                        while((inici + (num_lletres * s->dim)) > s->dim * s->dim)
                              {
                                 inici = rand() % (s->dim*s->dim) + 1;
                              }
                        if(s->encertades[inici + s->dim * poscicio] == true)
                            {
                                inici = rand() % (s->dim*s->dim) + 1;
                                poscicio = 1;
                                comprovar = 0;
                            }
                        else
                        {
                            comprovar ++;
                            poscicio ++;
                        }
                    }
                    s->par[paraula].pos = inici;
                    a = 1;
                    do
                    {
                        s->lletres[inici + (s->dim * a)] = s->par[paraula].ll[lle]; /*s->encertades[inici + s->dim * a] = true;*/
                        a ++;
                        lle ++;
                    }
                    while(num_lletres >= a);
                    break;
                }
        case 4: /*Baix*/
            {
                comprovar = 0;
                poscicio = 1;
                num_lletres = strlen(s->par[paraula].ll);
                while(comprovar < num_lletres)
                {
                    while(inici - (num_lletres * s->dim) <= 0)
                          {
                             inici = rand() % (s->dim*s->dim) + 1;
                          }
                    if(s->encertades[inici - s->dim * poscicio ] == true)
                        {
                            inici = rand() % (s->dim*s->dim) + 1;
                            poscicio = 1;
                            comprovar = 0;
                        }
                    else
                    {
                        comprovar ++;
                        poscicio ++;

                    }
                }
                s->par[paraula].pos = inici;
                a = 1;
                do
                {
                        s->lletres[inici - s->dim * a] = s->par[paraula].ll[lle]; /*s->encertades[inici - s->dim * a] = true;*/
                        a ++;
                        lle ++;
                }
                while(num_lletres >= a);
                break;
            }
        }
        lle = 0;
        paraula ++;
        a = 0;
    }
    while(paraula < s->n_par);
}
void mostra_sopa (sopa_t *s)
{
    // Mostrem els numeros de columna
    printf("\033[0;31m");   // Color
    printf("  ");
    for (int i = 10; i < s->dim + 1; i+=10)
    {
        for (int j=0; j < 18; j++)
            printf(" ");
        printf(" %d", i/10);

    }

    printf("\n  ");
    for (int i = 0; i < s->dim; i++)
    {
        int p = (i % 10) + 1;
        p != 10 ? printf(" %d", p) : printf(" 0");
    }

    printf("\n");
    printf("\033[0m");  // Tornem al color per defecte


    // Mostrem les lletres. Cada lletra ocupa dos espais:
    // Si correspon a un encert, es marca
    for (int i = 0; i < s->dim ; i++)
    {
        printf("\033[0;31m");   // Color
        printf("%-2d", i + 1);  // Mostrar numero de linia
        printf("\033[0m");  // Tornem al color per defecte

        for (int j = 0; j < s->dim; j++)
        {
            if (s->encertades[i * s->dim + j])
            {
                printf("\033[0;42m");   // Color verd de fons
                printf(" %c", s->lletres[i * s->dim + j]);
                printf("\033[0m");  // Tornem al color per defecte
            }
            else
            {
                printf(" %c", s->lletres[i * s->dim + j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Portes %d encerts.\n", s->n_encerts);
    printf("Paraules a trobar: %d\n", s->n_par - s->n_encerts);
    for (int i = 0; i < s->n_par; i++)
    {
        if (!s->par[i].enc)
            printf("%s (%d)\n", s->par[i].ll, i);
    }

}
void benvinguda()
{
    printf("Us donem la benvinguda al joc de la sopa de lletres!.\n");
    printf("Autors: Pau Fores Prats, Sergi Izquierdo Segarra, Genis Aragones Torralbo.\n");
}
void demanar_dimensio(sopa_t *s)
{
    printf("\n");
    printf("De quan vols la sopa?(minim 10, maxim 40)\n");
    scanf("%d", &s->dim);
}


void trobar_paraula (sopa_t *s)
{
    int nparaula,fila, columna, direccio;
    char resposta[10];

    printf("\nEs el teu torn. Has trobat alguna paraula? (S/N)\n");
    scanf("%s", resposta);

    if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0)
    {
        printf("Entra quina paraula vols encertar (Indicant el nombre a la dreta de la llista de paraules):\n");
        scanf("%d", &nparaula);
        printf("Entra la fila de la inicial de la paraula:\n");
        scanf("%d", &fila);
        printf("Entra la columna de la inicial de la paraula:\n");
        scanf("%d", &columna);
        printf("Entra la direccio de la paraula (1: dreta, -1: esquerra, 2: baix, -2: dalt):\n");
        scanf("%d", &direccio);

        // Comprovar si la paraula és correcta
        int posicio = (fila - 1) * s->dim + (columna - 1); // Calcula la posicio en la taula
        int num_lletres = strlen(s->par[nparaula].ll); // Calcula el num de lletres de la paraula en la posició indicada

        if (direccio == 1) // Dreta
        {
            int pos_final = posicio + num_lletres - 1; // Calcula la posicio final
            if (s->lletres[posicio] == s->par[nparaula].ll[0])
            {
                int i;
                if (posicio == (pos_final - num_lletres + 1))
                {
                    s->par[nparaula].enc = true;
                    printf("%d, %d\n", posicio, pos_final);
                    for (i = posicio; i <= pos_final; i++)
                    {
                        s->encertades[i] = true;
                    }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;
                }
                else
                {
                    printf("La paraula introduida es incorrecta.\n");
                }
            }
            else
            {
                printf("La paraula introduida es incorrecta. (1)\n");
            }
        }
        else if (direccio == -1) // Esquerra
        {
            int pos_final = posicio - (num_lletres - 1); // Calcula la posicio final
            if (s->lletres[posicio] == s->par[nparaula].ll[0])
            {
                int i;
                if (posicio == (pos_final + num_lletres - 1))
                {
                    s->par[nparaula].enc = true;
                    printf("%d, %d\n", posicio, pos_final);
                    for (i = posicio; i >= pos_final; i--)
                    {
                        s->encertades[i] = true;
                    }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;
                }
                else
                {
                    printf("La paraula introduida es incorrecta.\n");
                }
            }
            else
            {
                printf("La paraula introduida es incorrecta. (-1)\n");
            }
        }
        else if (direccio == 2) // Baix.
        {
            int pos_final = posicio + (num_lletres - 1) * s->dim; // Calcula la posicio final
              if (s->lletres[posicio] == s->par[nparaula].ll[0])
            {
                int i;
                if (posicio == (pos_final - (num_lletres-1) * s->dim))
                {
                    s->par[nparaula].enc = true;
                    for (i = 0 ; i < num_lletres; i++)
                    {
                        s->encertades[posicio + (i * s->dim)] = true;
                    }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;
                }
                else
                {
                    printf("La paraula introduida es incorrecta.\n");
                }
            }
            else
            {
                printf("La paraula introduida es incorrecta. (2)\n");
            }
        }
        else if (direccio == -2) // Dalt
        {
            int pos_final = posicio - (num_lletres - 1) * s->dim; // Calcula la posicio final
            if (s->lletres[posicio] == s->par[nparaula].ll[0])
            {
                int i;
                if (posicio == (pos_final + (num_lletres-1) * s->dim))
                {
                    s->par[nparaula].enc = true;
                    printf("%d, %d\n", posicio, pos_final);
                    for (i = 0 ; i < num_lletres; i++)
                    {
                        s->encertades[posicio - (i * s->dim)] = true;
                    }
                    printf("Has trobat la paraula '%s'!\n", s->par[nparaula].ll);
                    s->n_encerts += 1;
                }
                else
                {
                    printf("La paraula introduida es incorrecta.\n");
                }
            }
            else
            {
                printf("La paraula introduida es incorrecta. (-2)\n");
            }
        }
        else
        {
            printf("Direccio invalida.\n");
        }
    }
    else if (strcmp(resposta, "N") == 0 || strcmp(resposta, "n") == 0)
    {
        printf("No has trobat cap paraula en aquest torn. Et rendeixes o continues? (Introduir RENDICIO/CONTINUAR).\n");
        scanf("%s", resposta);
        if (strcmp(resposta, "CONTINUAR") == 0 || strcmp(resposta, "continuar") == 0)
        {
            printf("\n");
        }

        else if (strcmp(resposta, "RENDICIO") == 0 || strcmp(resposta, "rendicio") == 0)
        {
            for (int i = 0; i < s->n_par; i++)
            {
                s->par[i].enc = true;
                int num_lletres = strlen(s->par[i].ll);
                int pos_inicial = s->par[i].pos;
                printf("%d\n", pos_inicial);

                for (int j = 0; j < num_lletres; j++)
                {
                    int posicio = pos_inicial + j;
                    s->encertades[posicio] =  true; // Direccio 1 (dreta)
                    s->encertades[posicio - j] =  true; // Direccio -1 (esquerra)
                    s->encertades[posicio + j * s->dim] =  true; // Direccio 2 (baix)
                    s->encertades[posicio - j * s->dim] =  true; // Direccio -2 (dalt)
                }
            }
            s->n_encerts = s->n_par;
        }

    }
    else
    {
        printf("Resposta invalida.\n");
    }
}


int main() {

    sopa_t sopa;    // La sopa de lletres
    benvinguda();
    demanar_dimensio(&sopa);
    llegir_paraules(&sopa);
    if(sopa.paraules!=NULL){

        genera_sopa(&sopa);     // La generem (exemple)
        ficar_paraules(&sopa);
        do {
            mostra_sopa(&sopa);      // La mostrem per pantalla
            printf("\nEl nombre de paraules es de %d", sopa.n_par);
            trobar_paraula(&sopa);
        } while (!(sopa.n_encerts == sopa.n_par));
        mostra_sopa(&sopa);
        printf("\nHas trobat totes les paraules! Felicitats!\n");
    }
    else
        {
        printf("L'arxiu de les paraules no existeix.");
        }
    return 0;
}
