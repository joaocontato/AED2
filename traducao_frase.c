#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell {
    char *traducao;
    char *origem;
    struct cell *seg;
} cell;

unsigned int hashCode(const char *origem, int tam) {
    unsigned long hash = 5381;
    int c;
    while ((c = *origem++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % tam;
}

void dictInsert(cell **vetor, const char *origem, const char *traducao, int tam) {
    unsigned int index = hashCode(origem, tam);
    cell *current = vetor[index];
    while (current) {
        if (strcmp(current->origem, origem) == 0) {
            free(current->traducao);
            current->traducao = strdup(traducao);
            return;
        }
        current = current->seg;
    }
    cell *nova = malloc(sizeof(cell));
    nova->origem = strdup(origem);
    nova->traducao = strdup(traducao);
    nova->seg = vetor[index];
    vetor[index] = nova;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    getchar();

    int tam = 10007; 
    cell **vetor = malloc(tam * sizeof(cell *));
    for (int i = 0; i < tam; i++) vetor[i] = NULL;

    for (int i = 0; i < m; i++) {
        char palavra[101], traducao[101];
        fgets(palavra, 101, stdin);
        palavra[strcspn(palavra, "\n")] = '\0';
        fgets(traducao, 101, stdin);
        traducao[strcspn(traducao, "\n")] = '\0';
        dictInsert(vetor, palavra, traducao, tam);
    }

    for (int i = 0; i < n; i++) {
        char frase[101];
        fgets(frase, 101, stdin);
        frase[strcspn(frase, "\n")] = '\0';

        char *palavra = strtok(frase, " ");
        while (palavra != NULL) {
            unsigned int index = hashCode(palavra, tam);
            cell *current = vetor[index];
            int achou = 0;
            while (current) {
                if (strcmp(current->origem, palavra) == 0) {
                    printf("%s", current->traducao);
                    achou = 1;
                    break;
                }
                current = current->seg;
            }
            if (!achou) {
                printf("%s", palavra);
            }
            palavra = strtok(NULL, " ");
            if (palavra != NULL) printf(" ");
        }
        printf("\n");
    }


    free(vetor);
    return 0;
}
