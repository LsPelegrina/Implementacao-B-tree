#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

#define MAX 3
#define MIN 2

// Estrutura para representar um nó da árvore B
struct NoArvoreB {
    int valores[MAX + 1], contador;
    struct NoArvoreB *filhos[MAX + 1];
};

struct NoArvoreB *raiz; // Raiz da árvore B

// Função para criar um novo nó na árvore B
struct NoArvoreB *criarNo(int valor, struct NoArvoreB *filho) {
  struct NoArvoreB *novoNo;
  novoNo = (struct NoArvoreB *)malloc(sizeof(struct NoArvoreB)); // Aloca memória para o novo nó
  novoNo->valores[1] = valor; // Insere o valor no novo nó
  novoNo->contador = 1; // Atualiza o contador de valores
  novoNo->filhos[0] = raiz; // Define o filho esquerdo como a raiz atual
  novoNo->filhos[1] = filho; // Define o filho direito como o filho passado como parâmetro
  return novoNo; // Retorna o novo nó criado
}

// Função para adicionar um valor ao nó
void adicionarValorAoNo(int valor, int posicao, struct NoArvoreB *no,
          struct NoArvoreB *filho) {
  int j = no->contador;
  
  // Move todos os valores e filhos à direita da posição para a direita
  while (j > posicao) {
    no->valores[j + 1] = no->valores[j];
    no->filhos[j + 1] = no->filhos[j];
    j--;
  }
  
  // Insere o novo valor e filho na posição correta
  no->valores[j + 1] = valor;
  no->filhos[j + 1] = filho;
  
  // Incrementa o contador de valores do nó
  no->contador++;
}

 // Função para dividir o nó quando está cheio
  void dividirNo(int valor, int *valorPromovido, int posicao, struct NoArvoreB *no,
           struct NoArvoreB *filho, struct NoArvoreB **novoNo) {
    int mediana, j;

    // Determina a posição mediana do nó
    if (posicao > MIN)
      mediana = MIN + 1;
    else
      mediana = MIN;

    // Cria um novo nó
    *novoNo = (struct NoArvoreB *)malloc(sizeof(struct NoArvoreB));
    
    // Move os valores e filhos à direita da mediana para o novo nó
    j = mediana + 1;
    while (j <= MAX) {
      (*novoNo)->valores[j - mediana] = no->valores[j];
      (*novoNo)->filhos[j - mediana] = no->filhos[j];
      j++;
    }
    
    // Atualiza os contadores de valores dos nós
    no->contador = mediana;
    (*novoNo)->contador = MAX - mediana;

    // Adiciona o novo valor ao nó correto
    if (posicao <= MIN) {
      adicionarValorAoNo(valor, posicao, no, filho);
    } else {
      adicionarValorAoNo(valor, posicao - mediana, *novoNo, filho);
    }
    
    // Promove o valor do meio para o nível superior
    *valorPromovido = no->valores[no->contador];
    
    // Atualiza os filhos do nó
    (*novoNo)->filhos[0] = no->filhos[no->contador];
    
    // Decrementa o contador de valores do nó original
    no->contador--;
  }
  // Define o valor no nó
int defineValorNoNo(int valor, int *valorPromovido, struct NoArvoreB *no, struct NoArvoreB **filho) {
  int posicao;
  // Se o nó não existir, atribua o valor e defina o filho como NULL
  if (!no) {
    *valorPromovido = valor;
    *filho = NULL;
    return 1;
  }

  // Se o valor for menor que o valores no nó, defina a posição como 0
  if (valor < no->valores[1]) {
    posicao = 0;
  } else {
    // Caso contrário, encontre a posição correta para o valor no nó
    for (posicao = no->contador; (valor < no->valores[posicao] && posicao > 1); posicao--)
      ;
    // Se o valor já existir no nó, retorne 0 pois duplicatas não são permitidas
    if (valor == no->valores[posicao]) {
      printf("Duplicatas não são permitidas\n");
      return 0;
    }
  }
  
  // Chama a função recursivamente até encontrar a posição correta para inserir o valor
  if (defineValorNoNo(valor, valorPromovido, no->filhos[posicao], filho)) {
    // Se o nó não estiver cheio, adicione o valor ao nó
    if (no->contador < MAX) {
      adicionarValorAoNo(*valorPromovido, posicao, no, *filho);
    } else {
      // Se o nó estiver cheio, divida o nó
      dividirNo(*valorPromovido, valorPromovido, posicao, no, *filho, filho);
      return 1;
    }
  }
  
  return 0;
}

// Operação de inserção
void insercao(int valor) {
    int flag, i;
    struct NoArvoreB *filho = NULL;

    // Chama a função para definir o valor no nó
    flag = defineValorNoNo(valor, &i, raiz, &filho);

    // Se a função retornar verdadeiro (1), crie um novo nó com o valor e filho especificados
    if (flag) {
        if (raiz == NULL) {
            // Se a árvore estiver vazia, crie um novo nó como raiz
            raiz = criarNo(i, filho);
        } else {
            // Se a árvore não estiver vazia, ajuste a raiz conforme necessário
            if (flag == 1) {
                raiz = criarNo(i, filho);
            }
        }
    }
}

// Copia o sucessor
void copiaSucessor(struct NoArvoreB *meuNo, int posicao) {
  
struct NoArvoreB *dummy;
dummy = meuNo -> filhos[posicao];

// Percorre os nós até encontrar o sucessor do valor que queremos remover
for (; dummy -> filhos[0] != NULL;)
dummy = dummy -> filhos[0];
meuNo -> valores[posicao] = dummy -> valores[1];
}

// Remove o valor do nó
void removeValor(struct NoArvoreB *meuNo, int posicao) {
int i=posicao+1;

// Desloca todos os valores e links para a esquerda após a remoção do valor
while(i <= meuNo -> contador){
meuNo -> valores[i-1]=meuNo -> valores[i];
meuNo -> filhos[i-1]=meuNo -> filhos[i];
i++;
}
meuNo -> contador--;
}

// Faz um deslocamento à direita nos nós
void deslocarDireita(struct NoArvoreB *meuNo,int posicao){
struct NoArvoreB *x=meuNo -> filhos[posicao];
int j=x -> contador;

// Desloca todos os valores e links para a direita
while(j > 0){
x -> valores[j+1]=x -> valores[j];
x -> filhos[j+1]=x -> filhos[j];
}
x -> valores[1]=meuNo -> valores[posicao];
x -> filhos[1]=x -> filhos[0];
x -> contador++;

x=meuNo -> filhos[posicao-1];
meuNo -> valores[posicao]=x -> valores[x -> contador];
meuNo -> filhos[posicao]=x -> filhos[x -> contador];
x -> contador--;
return;
}

// Faz um deslocamento à esquerda nos nós
void deslocarEsquerda(struct NoArvoreB *meuNo,int posicao){
int j=1;
struct NoArvoreB *x=meuNo -> filhos[posicao-1];

x->contador++;
x->valores[x->contador]=meuNo->valores[posicao];
x->filhos[x->contador]=meuNo->filhos[posicao]->filhos[0];

x=meuNo->filhos[posicao];
meuNo->valores[posicao]=x->valores[1];
x->filhos[0]=x->filhos[1];
x->contador--;

while(j <= x->contador){
x->valores[j]=x->valores[j+1];
x->filhos[j]=x->filhos[j+1];
j++;
}
return;
}

// Junta os nós
void fundirNos(struct NoArvoreB *meuNo,int posicao){
int j=1;
struct NoArvoreB *x1=meuNo->filhos[posicao],*x2=meuNo->filhos[posicao-1];

x2->contador++;
x2->valores[x2->contador]=meuNo->valores[posicao];
x2->filhos[x2->contador]=meuNo->filhos[0];

while(j <= x1->contador){
x2->contador++;
x2->valores[x2->contador]=x1->valores[j];
x2->filhos[x2->contador]=x1->filhos[j];
j++;
}

j=posicao;

while(j < meuNo->contador){
meuNo->valores[j]=meuNo->valores[j+1];
meuNo->filhos[j]=meuNo->filhos[j+1];
j++;
}
meuNo->contador--;
free(x1);
}

// Função para ajustar o nó após a exclusão de um valor
 void ajustarNo(struct NoArvoreB *meuNo, int posicao) {
    if (posicao == 0) {
        // Se a posição é 0, significa que o valor foi removido do filho à esquerda
        if (meuNo->filhos[1]->contador < MIN) {
            // Se o filho à direita não tem elementos suficientes, fundimos com ele
            fundirNos(meuNo, 1);
        } else {
            // Caso contrário, deslocamos um valor do filho à direita
            deslocarEsquerda(meuNo, 1);
        }
    } else if (posicao == meuNo->contador) {
        // Se a posição é a última, significa que o valor foi removido do filho à direita
        if (meuNo->filhos[posicao - 1]->contador < MIN) {
            // Se o filho à esquerda não tem elementos suficientes, fundimos com ele
            fundirNos(meuNo, posicao);
        } else {
            // Caso contrário, deslocamos um valor do filho à esquerda
            deslocarDireita(meuNo, posicao);
        }
    } else {
        // Se a posição está no meio, precisamos verificar ambos os filhos
        if (meuNo->filhos[posicao]->contador > MIN) {
            // Se o filho à direita tem elementos suficientes, deslocamos um valor dele
            deslocarEsquerda(meuNo, posicao);
        } else if (meuNo->filhos[posicao - 1]->contador > MIN) {
            // Se o filho à esquerda tem elementos suficientes, deslocamos um valor dele
            deslocarDireita(meuNo, posicao);
        } else {
            // Se ambos os filhos têm a quantidade mínima de elementos, fundimos com o filho à esquerda
            fundirNos(meuNo, posicao);
        }
    }
}

// Função para deletar um valor da árvore B
// Função para deletar um valor da árvore B
int deletarValorDoNo(int valor, struct NoArvoreB *meuNo) {
  int posicao, flag = 0;
  if (meuNo) {
    // Encontra a posição do valor no nó
    for (posicao = 1; posicao <= meuNo->contador && valor > meuNo->valores[posicao]; posicao++);

    // Verifica se o valor foi encontrado no nó atual
    if (posicao <= meuNo->contador && valor == meuNo->valores[posicao]) {
      flag = 1;
    } else {
      flag = 0;
    }

    // Se encontrou o valor no nó atual
    if (flag) {
      // Se o nó é folha, remove o valor
      if (meuNo->filhos[0] == NULL) {
        removeValor(meuNo, posicao);
      } else {
        // Se o nó não é folha, substitui o valor pelo seu sucessor e então remove o sucessor
        copiaSucessor(meuNo, posicao);
        flag = deletarValorDoNo(meuNo->valores[posicao], meuNo->filhos[posicao]);
        // Se a remoção do valor não afetou o nó filho, ajusta o nó
        if (!flag) {
          printf("Dado não encontrado na árvore B\n");
        }
      }
    } else {
      // Se o valor não está no nó atual, continua a busca nos filhos apropriados
      flag = deletarValorDoNo(valor, meuNo->filhos[posicao - 1]);
    }

    // Após a remoção, ajusta o nó atual se necessário
    if (meuNo->filhos[posicao - 1]) {
      if (meuNo->filhos[posicao - 1]->contador < MIN) {
        ajustarNo(meuNo, posicao - 1);
      }
    }
  }
  return flag;
}




// Função principal para exclusão na árvore B
void excluir(int valor, struct NoArvoreB *meuNo) {
  struct NoArvoreB *tmp;
  // Se o valor não for encontrado
  if (!deletarValorDoNo(valor, meuNo)) {
    printf("Não encontrado\n");
    return;
  } else {
    // Se o contador do nó for zero
    if (meuNo->contador == 0) {
      tmp = meuNo;
      meuNo = meuNo->filhos[0];
      free(tmp);
    }
  }
  raiz = meuNo;
  return;
}

// Função para encontrar valor na arvore B
void pesquisar(int valor, int *posicao, struct NoArvoreB *meuNo) {
  if (!meuNo) {
    return;
  }

  if (meuNo->contador >= 1 && valor < meuNo->valores[1]) {
    *posicao = 0;
  } else {
    for (*posicao = meuNo->contador;
       (valor < meuNo->valores[*posicao] && *posicao > 1); (*posicao)--)
      ;
    if (valor == meuNo->valores[*posicao]) {
      printf("%d esta na Arvore B", valor);
      return;
    }
  }
  pesquisar(valor, posicao, meuNo->filhos[*posicao]);
  return;
}

// Função para percorrer a árvore B e imprimir os valores
void percorrer(struct NoArvoreB *meuNo) {
  int i;
  // Se o nó existir
  if (meuNo) {
    for (i = 0; i < meuNo->contador; i++) {
      percorrer(meuNo->filhos[i]);
      printf("%d ", meuNo->valores[i + 1]);
    }
    percorrer(meuNo->filhos[i]);
  }
}