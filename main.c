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
    int direccio; // La direccio de la paraula
} paraula_t;

typedef struct
{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    bool *insertades;   // Si la paraula ja ha estat insertada.
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
    s->insertades = malloc(s->dim * s->dim * sizeof(char));
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        s->encertades[i] = false;
        s->insertades[i] = false;
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
    int inici;
    int num_lletres;
    int j;
    int posicio;
    int comprovar;
    int intent;
    int solapat;

    srand(time(NULL));
    comprovar = 0;
    intent = 0;

    for (int paraula = 0; paraula < s->n_par; paraula++)
    {
        num_lletres = strlen(s->par[paraula].ll);
        solapat = 1;

        while (solapat)
        {
            intent++;
            if (intent > 1000) {
                printf("Error: No es pot generar la sopa de lletres.\n"); // Si es superen els 1000 intents per a re-insertar una paraula sense que solapi, dona error.
                return;
            }

            solapat = 0;
            inici = rand() % (s->dim * s->dim) + 1;
            j = rand() % 4 + 1;
            bool sortir = false;
            switch (j)
            {
                case 1: /* Dreta */
                    posicio = inici;
                    for (int a = 0; a < num_lletres && !sortir; a++)
                    {
                        if ((posicio + a) % s->dim == 0 || s->insertades[posicio + a] == true)
                        {
                            solapat = 1;
                            sortir = true;
                        }
                    }
                    break;

                case 2: /* Esquerra */
                    posicio = inici;
                    for (int a = 0; a < num_lletres && !sortir; a++)
                    {
                        if ((posicio - a) % s->dim == (s->dim - 1) || s->insertades[posicio - a] == true)
                        {
                            solapat = 1;
                            sortir = true;
                        }
                    }
                    break;

                case 3: /* Dalt */
                    posicio = inici;
                    for (int a = 0; a < num_lletres && !sortir; a++)
                    {
                        if (posicio + (a * s->dim) >= (s->dim * s->dim) || s->insertades[posicio + (a * s->dim)] == true)
                        {
                            solapat = 1;
                            sortir = true;
                        }
                    }
                    break;

                case 4: /* Baix */
                    posicio = inici;
                    for (int a = 0; a < num_lletres && !sortir; a++)
                    {
                        if (posicio - (a * s->dim) < 1 || s->insertades[posicio - (a * s->dim)] == true)
                        {
                            solapat = 1;
                            sortir = true;
                        }
                    }
                    break;
            }

            if (!solapat)
            {
                for (int a = 0; a < num_lletres; a++)
                {
                    int index;
                    switch (j)
                    {
                        case 1: /* Dreta */
                            index = inici + a;
                            break;
                        case 2: /* Esquerra */
                            index = inici - a;
                            break;
                        case 3: /* Dalt */
                            index = inici + (a * s->dim);
                            break;
                        case 4: /* Baix */
                            index = inici - (a * s->dim);
                            break;
                    }

                    s->lletres[index] = s->par[paraula].ll[a];
                    s->insertades[index] = true;
                }

                s->par[paraula].pos = inici;
                s->par[paraula].direccio = j;
            }
        }
    }
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
    char input[50];
    printf("\n");
    printf("De quan vols la sopa?(minim 10, maxim 40)\n");
    do
    {
        fgets(input, 50, stdin);
        if(sscanf(input, "%d", &s->dim) != 1 || s->dim < 10 || s->dim > 40)
        {
            printf("El valor indicat es incorrecte. Introdueix un nombre de 10 a 40.\n");
        }
    }while(sscanf(input, "%d", &s->dim) != 1 || s->dim < 10 || s->dim > 40);
}

void limpiar_buffer()
{
    int c;
    while ((c = getchar() != '\n' && c != EOF)){}
}

int validar_entrada(const char* missatge, int minim, int maxim, const char* error) { // Funció per a validar els inputs del jugador (principalment per a no tenir tant de text repetit a la funció de trobar_paraula)
    int valor;
    char input[50];
    bool valid = false;

    while (!valid) {
        printf("%s\n", missatge);
        fgets(input, 50, stdin);
        if (sscanf(input, "%d", &valor) == 1 && valor >= minim && valor <= maxim) {
            valid = true;
        } else if (minim == 1){
            printf("%s %d\n", error, maxim);
        }
        else if (minim == -2)
        {
            printf("%s\n", error);
        }
    }

    return valor;
}




void trobar_paraula(sopa_t *s) {
    int fila, columna, direccio;
    char resposta[10];
    bool trobat = false;

    printf("\nEs el teu torn. Has trobat alguna paraula? (S/N)\n");
    scanf("%s", resposta);
    limpiar_buffer();
    while ((strcmp(resposta, "S") != 0 && strcmp(resposta, "s") != 0) && (strcmp(resposta, "N") != 0 && strcmp(resposta, "n") != 0)) {
        printf("Resposta invalida.\n");
        printf("Torna a introduir la teva resposta. Has trobat alguna paraula? (S/N)\n");
        scanf("%s", resposta);
        limpiar_buffer();
    }

    if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0) {
        char input[50] = "";

        fila = validar_entrada("Entra la fila de la inicial de la paraula:", 1, s->dim, "El valor indicat es incorrecte. Introdueix un nombre de 1 a");
        columna = validar_entrada("Entra la columna de la inicial de la paraula:", 1, s->dim, "El valor indicat es incorrecte. Introdueix un nombre de 1 a");
        direccio = validar_entrada("Entra la direccio (1: dreta, -1: esquerra, 2: baix, -2: dalt):", -2, 2, "El valor indicat es incorrecte. Introdueix una direccio valida (1: dreta, -1: esquerra, 2: baix, -2: dalt)");


        int posicio = (fila - 1) * s->dim + (columna - 1);
        int pos_actual, increment, j, fila_actual, fila_paraula;

            for (int i = 0; i < s->n_par && !trobat; i++) {
                if (!s->par[i].enc) {
                    switch (direccio) {
                        case 1: // Dreta
                            pos_actual = posicio;
                            increment = 1;
                            j = 0;
                            break;
                        case -1: // Esquerra
                            pos_actual = posicio - 1;
                            increment = -1;
                            j = 1;
                            break;
                        case 2: // Baix
                            pos_actual = posicio + s->dim;
                            increment = s->dim;
                            j = 1;
                            break;
                        case -2: // Dalt
                            pos_actual = posicio - s->dim;
                            increment = -s->dim;
                            j = 1;
                            break;
                    }

                    while (pos_actual >= 0 && pos_actual < s->dim * s->dim && j < strlen(s->par[i].ll) && !trobat) {
                        if (s->lletres[pos_actual] == s->par[i].ll[j]) {
                            if (j == strlen(s->par[i].ll) - 1) {
                                s->par[i].enc = true;
                                printf("Has trobat la paraula '%s'!\n", s->par[i].ll);
                                s->n_encerts += 1;
                                trobat = true;
                            }
                            j++;
                            pos_actual += increment;
                        } else {
                            pos_actual = -1; // Per sortir del bucle while
                        }
                    }


                    if (trobat) {
                        for (int k = 0; k < j; k++) { // Bucle per a donar el color de les acertades.
                            pos_actual -= increment;
                            s->encertades[pos_actual] = true;
                        }
                    }
                }
                else if (s->par[i].enc)
                {
                    printf("Ja has trobat aquesta! ");
                }
            }

        if (!trobat) {
            printf("La paraula introduida es invalida.\n");
        }
    }
    else if (strcmp(resposta, "N") == 0 || strcmp(resposta, "n") == 0)
    {

        printf("No has trobat cap paraula en aquest torn. Et rendeixes o continues? (Introduir RENDICIO/CONTINUAR).\n");
        scanf("%s", resposta);
        while((strcmp(resposta, "CONTINUAR") != 0 && strcmp(resposta, "continuar") != 0) && (strcmp(resposta, "RENDICIO") != 0 && strcmp(resposta, "rendicio") != 0))
        {
            printf("Resposta invalida.\n");
            printf("Torna a introduir la teva resposta. Et rendeixes o continues? (Introduir RENDICIO/CONTINUAR).\n");
            scanf("%s", resposta);
            limpiar_buffer();
        }
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

                for (int j = 0; j < num_lletres; j++) // Bucle for per anar colorint les lletres de totes les paraules
                {
                    int posicio;
                    switch(s->par[i].direccio)
                    {
                        case 1: // Direccio 1 (dreta)
                            posicio = pos_inicial + j;
                            break;
                        case 2: // Direccio -1 (esquerra)
                            posicio = pos_inicial - j;
                            break;
                        case 3: // Direccio 2 (baix)
                            posicio = pos_inicial + (j * s->dim);
                            break;
                        case 4: // Direccio -2 (dalt)
                            posicio = pos_inicial - (j * s->dim);
                            break;
                    }
                    if (posicio >= 0 && posicio < s->dim * s->dim) {
                        s->encertades[posicio] = true;
                    }
                }
            }
            s->n_encerts = s->n_par;
        }

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
