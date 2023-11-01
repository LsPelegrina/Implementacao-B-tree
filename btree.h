#ifndef BTREE_H
#define BTREE_H


/*Esta função cria um novo nó na árvore B. Ela recebe um valor e um ponteiro para um filho como parâmetros, 
aloca memória para o novo nó, insere o valor no novo nó, atualiza o contador de valores, define o filho esquerdo como a raiz atual 
e o filho direito como o filho passado como parâmetro. A função retorna o novo nó criado.*/
struct NoArvoreB *criarNo(int valor, struct NoArvoreB *filho);

/*Esta função adiciona um valor a um nó existente na árvore B. Ela recebe um valor, uma posição, um ponteiro para um nó e um ponteiro para um filho
como parâmetros. A função move todos os valores e filhos à direita da posição para a direita, insere o novo valor e filho na posição correta
e incrementa o contador de valores do nó.*/
void adicionarValorAoNo(int valor, int posicao, struct NoArvoreB *no, struct NoArvoreB *filho);

/*Esta função divide um nó quando está cheio. Ela recebe um valor, um ponteiro para um valor promovido, uma posição, um ponteiro para um nó,
um ponteiro para um filho e um ponteiro para um novo nó como parâmetros. A função determina a posição mediana do nó, cria um novo nó,
move os valores e filhos à direita da mediana para o novo nó, atualiza os contadores de valores dos nós, adiciona o novo valor ao nó correto,
promove o valor do meio para o nível superior e atualiza os filhos do nó.*/
void dividirNo(int valor, int *valorPromovido, int posicao, struct NoArvoreB *no, struct NoArvoreB *filho, struct NoArvoreB **novoNo);

/*Esta função define um valor em um nó na árvore B. Ela recebe um valor, um ponteiro para um valor promovido, um ponteiro para um nó e 
um ponteiro para um filho como parâmetros. A função verifica se o nó existe, encontra a posição correta para o valor no nó, 
verifica se o valor já existe no nó e chama a função recursivamente até encontrar a posição correta para inserir o valor. 
Se o nó não estiver cheio, adiciona o valor ao nó. Se o nó estiver cheio, divide o nó.*/
int defineValorNoNo(int valor, int *valorPromovido, struct NoArvoreB *no, struct NoArvoreB **filho);

/*Esta função realiza a operação de inserção na árvore B. Ela recebe os valores a serem inseridos como parâmetros. A função chama a função 
para definir o valor no nó e se a função retornar verdadeiro (1), cria um novo nó com o valor e filho especificados.*/
void insercao(int valores);

/*Esta função copia o sucessor de um valor que queremos remover. Ela recebe um ponteiro para um nó e uma posição como parâmetros. 
A função percorre os nós até encontrar o sucessor do valor que queremos remover.*/
void copiaSucessor(struct NoArvoreB *meuNo, int posicao);

/*Esta função remove um valor de um nó existente na árvore B. Ela recebe um ponteiro para um nó e uma posição como parâmetros. 
A função desloca todos os valores e links para a esquerda após a remoção do valor.*/
void removeValor(struct NoArvoreB *meuNo, int posicao);

/*Esta função realiza um deslocamento à direita nos nós da árvore B. Ela recebe um ponteiro para um nó e uma posição como parâmetros. 
A função desloca todos os valores e links para a direita.*/
void deslocarDireita(struct NoArvoreB *meuNo,int posicao);

/*Esta função realiza um deslocamento à esquerda nos nós da árvore B. Ela recebe um ponteiro para um nó e uma posição como parâmetros. 
A função desloca todos os valores e links para a esquerda após a remoção do valor.*/
void deslocarEsquerda(struct NoArvoreB *meuNo,int posicao);

/*Esta função junta dois nós na árvore B. Ela recebe um ponteiro para um nó e uma posição como parâmetros. 
A função move todos os valores e filhos do segundo nó para o primeiro e atualiza os valores e filhos do primeiro nó.*/
void fundirNos(struct NoArvoreB *meuNo,int posicao);

/*Esta função ajusta um nó na árvore B após a remoção de um valor. Ela recebe um ponteiro para um nó e uma posição como parâmetros. 
A função verifica a posição e o contador do nó e realiza um deslocamento à esquerda ou à direita ou funde os nós conforme necessário.*/
void ajustarNo(struct NoArvoreB *meuNo, int posicao);

/*Esta função deleta um valor de um nó na árvore B. Ela recebe um valor e um ponteiro para um nó como parâmetros. A função verifica 
se o nó existe, encontra a posição do valor no nó, verifica se o valor existe no nó, remove o valor e ajusta o nó se necessário.*/
int deletarValorDoNo(int valor, struct NoArvoreB *meuNo);

/*Esta função realiza a operação de exclusão na árvore B. Ela recebe um valor e um ponteiro para um nó como parâmetros. 
A função chama a função para deletar o valor do nó e se o contador do nó for zero após a remoção, libera a memória do nó.*/
void excluir(int valor, struct NoArvoreB *meuNo);

/*Esta função pesquisa um valor na árvore B. Ela recebe um valor, um ponteiro para uma posição e um ponteiro para um nó como parâmetros. 
A função verifica se o nó existe, encontra a posição do valor no nó e chama a função recursivamente até encontrar o valor.*/
void pesquisar(int valor, int *posicao, struct NoArvoreB *meuNo);

/*Esta função percorre a árvore B e imprime os valores. Ela recebe um ponteiro para um nó como parâmetro. 
A função verifica se o nó existe e imprime os valores do nó.*/
void percorrer(struct NoArvoreB *meuNo);

#endif 