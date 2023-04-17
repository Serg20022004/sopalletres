
void trobar_paraula(paraula_t *p)
{
    int i, n_fila, n_columna, n_direccio;
    char frase[MAX_LLETRES];
    printf("Indica quina paraula has encertat: ");
    fgets(frase, MAX_LLETRES, stdin);

    while(!(frase[i] >= 'A' && frase[i] <= 'Z'))
    {
        printf("Introdueix un valor valid.\n");
        fgets(frase, MAX_LLETRES, stdin);
    }

    printf("Indica fila, columna i direcció.\n");
    printf("Fila: "); scanf("%d", &n_fila); printf("\n");
    printf("Columna: "); scanf("%d", &n_columna); printf("\n");
    printf("Direccio: "); scanf("%d", &n_direccio); printf("\n");

}
