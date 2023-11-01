#include <stdio.h>
#include "btree.c"

int main() {

    int valor, ch;

    insercao(8);
    insercao(9);
    insercao(10);
    insercao(11);
    insercao(15);
    insercao(16);
    insercao(17);
    insercao(18);
    insercao(20);
    insercao(23);

    
    percorrer(raiz);
    excluir(20, raiz);
    
    printf("\n");
    percorrer(raiz);

    printf("\n");
    pesquisar(11, &ch, raiz);
}