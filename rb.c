#include <stdio.h>
#include <stdlib.h>

int **alocaGrafo(int tam){
  int **grafo, i;
  grafo = (int **) calloc(tam, sizeof(int *));
  for(i = 0; i < tam; i++)
    grafo[i] = (int *) calloc(tam, sizeof(int));
  return grafo;
}

void limpaGrafo(int **grafo, int tam){
  int i, j;
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      grafo[i][j] = 0;
    }
  }
}

void liberaGrafo(int **grafo, int tam){
  int i;
  for(i = 0; i < tam; i++)
    free(grafo[i]);
  free(grafo);
}

void somaGrafos(int **grafo1, int **grafo2, int **grafo3, int tam){
  int i, j;
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      if(grafo1[i][j] + grafo2[i][j] == 2)
        grafo3[i][j] = 1;
      else
        grafo3[i][j] = grafo1[i][j] + grafo2[i][j];
    }
  }
}

void diferencaGrafos(int **grafo1, int **grafo2, int **grafo3, int tam){
  int i, j;
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      //diferença armazenada no grafo2 devido à ordem de passagem de parâmetros
      grafo2[i][j] = grafo3[i][j] - grafo1[i][j];
    }
  }
}

int converteIndice(int indice, int *elementos, int tam){
  int i;
  for(i = 0; i < tam; i++){
    if(indice == elementos[i])
      return i;
  }
  return -1;
}

void leGrafo(int **grafo, int tam, int *elementos){
  int i, n1, n2;
  while (scanf("%d %d", &n1, &n2) != EOF){
    n1 = converteIndice(n1, elementos, tam);
    n2 = converteIndice(n2, elementos, tam);
    if(n1 >= 0 && n2 >= 0)
      grafo[n1][n2] = 1;
  }
}

//funçao que checa se o grafo é reflexivo ou irreflexivo
int reflexividade(int **grafo, int tam, int valor, int **grafo2){
  int i, validador = 1;
  limpaGrafo(grafo2, tam);
  for(i = 0; i < tam; i++){
    //se existir alguma linha com o valor diferente, então retorna falso
    if(grafo[i][i] == valor){
      validador = 0;
      grafo2[i][i] = 1;
    }
  }
  return validador;
}

//funcao que checa se o grafo é simétrico ou assimétrico
int simetria(int **grafo, int tam, int valor, int **grafo2){
  int i, j, validador = 1;
  limpaGrafo(grafo2, tam);
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      if(grafo[i][j] == 1 && grafo[j][i] == valor){
        validador = 0;
        grafo2[j][i] = 1;
      }
    }
  }
  return validador;
}

//funcao que checa se o grafo é antisimétrico
int antiSimetria(int **grafo, int tam, int **grafo2){
  int i, j, validador = 1;
  limpaGrafo(grafo2, tam);
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      if(grafo[i][j] == 1 && grafo[j][i] == 1)
        if(i != j && i < j){
          validador = 0;
          grafo2[i][j] = 1;
        }
    }
  }
  return validador;
}

//funcao que checa se o grafo é transitivo
int transitividade(int **grafo, int tam, int **grafo2){
  int i, j, k, validador = 1;
  limpaGrafo(grafo2, tam);
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      if(grafo[i][j]){
        for(k = 0; k < tam; k++){
          if(grafo[j][k] == 1 && grafo[i][k] == 0){
            validador = 0;
            //só marca auxiliar se não houver marcação já
            if(grafo2[i][k] == 0){
              grafo2[i][k] = 1;
            }
          }
        }
      }
    }
  }
  return validador;
}

int checaReflex(int **grafo, int tam, int **grafoResultante, int *elementos){
  int i, j, **grafo2, retorno = 0;
  grafo2 = alocaGrafo(tam);
  printf("1.\tReflexiva: ");
  if(reflexividade(grafo, tam, 0, grafo2)){
    printf("V\n");
    retorno = 1;
  }
  else{
    printf("F\n\t");
    for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
        if(grafo2[i][j])
          printf("(%d,%d); ", elementos[i], elementos[j]);
      }
    }
    printf("\n");
    somaGrafos(grafo, grafo2, grafoResultante, tam);
  }

  printf("2.\tIrreflexiva: ");
  if(reflexividade(grafo, tam, 1, grafo2)){
    printf("V\n");
  }
  else{
    printf("F\n\t");
    for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
        if(grafo2[i][j])
          printf("(%d,%d); ", elementos[i], elementos[j]);
      }
    }
    printf("\n");
  }
  liberaGrafo(grafo2, tam);
  return retorno;
}

int checaSimetria(int **grafo, int tam, int **grafoResultante, int *elementos){
  int i, j, **grafo2, retorno = 0;
  grafo2 = alocaGrafo(tam);
  printf("3.\tSimetrica: ");
  if(simetria(grafo, tam, 0, grafo2)){
    printf("V\n");
    retorno += 1;
  }
  else{
    printf("F\n\t");
    for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
        if(grafo2[i][j])
          printf("(%d,%d); ", elementos[i], elementos[j]);
      }
    }
    printf("\n");
    somaGrafos(grafo, grafo2, grafoResultante, tam);
  }

  printf("4.\tAnti-simetrica: ");
  if(antiSimetria(grafo, tam, grafo2)){
    printf("V\n");
    retorno += 2;
  }
  else{
    printf("F\n\t");
    for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
        if(grafo2[i][j])
          printf("(%d,%d) e (%d,%d); ", elementos[i], elementos[j], elementos[j], elementos[i]);
      }
    }
    printf("\n");
  }

  printf("5.\tAssimetrica: ");
  if(simetria(grafo, tam, 1, grafo2)){
    printf("V\n");
  }
  else{
    printf("F\n");
  }
  liberaGrafo(grafo2, tam);
  return retorno;
}

int checaTransitividade(int **grafo, int tam, int **grafoResultante, int *elementos){
  int i, j, **grafo2, retorno = 0;
  grafo2 = alocaGrafo(tam);
  printf("6.\tTransitiva: ");
  if(transitividade(grafo, tam, grafo2)){
    printf("V\n");
    retorno = 1;
  }
  else{
    printf("F\n\t");
    //é necessário passar os valores do grafo para o grafoResultante. Reaproveitamento de função
    somaGrafos(grafo, grafo, grafoResultante, tam);
    //enquanto não for transitivo, aplica a função de transitividade e adiciona os novos vértices ao grafo
    do{
      somaGrafos(grafoResultante, grafo2, grafoResultante, tam);
   }while(!transitividade(grafoResultante, tam, grafo2));
   //faz a diferença entre grafos para descobrir quais vértices foram adicionados
   diferencaGrafos(grafo, grafo2, grafoResultante, tam);
    for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
        if(grafo2[i][j])
          printf("(%d,%d); ", elementos[i], elementos[j]);
      }
    }
    printf("\n");
  }
  liberaGrafo(grafo2, tam);
  return retorno;
}

void checaEquivalencia(int r, int s, int t){
  printf("Relacao de equivalencia: ");
  if(r == 1 && (s == 1 || s == 3) && t == 1)
    printf("V\n");
  else
    printf("F\n");
}

void checaOrdemParcial(int r, int s, int t){
  printf("Relacao de ordem parcial: ");
  if(r == 1 && (s == 2 || s == 3) && t == 1)
    printf("V\n");
  else
    printf("F\n");
}

void fecho(int **grafo, int tam, char *nome, int *elementos){
  int i, j, validador = 1;
  printf("Fecho %s da relacao = {", nome);
  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      if(grafo[i][j]){
        if(!validador)
          printf(",");
        printf("(%d,%d)", elementos[i], elementos[j]);
        validador = 0;
      }
    }
  }
  printf("}\n");
}

int main(){
  int qteElem, qteRel, i, reflex, simet, trans;
  int *elementos, **grafo, **grReflex, **grSimet, **grTrans;

  scanf("%d", &qteElem);
  grafo = alocaGrafo(qteElem);
  elementos = (int *) malloc(qteElem * sizeof(int));
  for(i = 0; i < qteElem; i++){
    scanf("%d", &elementos[i]);
  }

  grReflex = alocaGrafo(qteElem);
  grSimet = alocaGrafo(qteElem);
  grTrans = alocaGrafo(qteElem);

  leGrafo(grafo, qteElem, elementos);
  printf("Propriedades\n");
  reflex = checaReflex(grafo, qteElem, grReflex, elementos);
  simet = checaSimetria(grafo, qteElem, grSimet, elementos);
  trans = checaTransitividade(grafo, qteElem, grTrans, elementos);
  printf("\n");
  checaEquivalencia(reflex, simet, trans);
  checaOrdemParcial(reflex, simet, trans);
  printf("\n");
  if(!reflex){
    fecho(grReflex, qteElem, "reflexivo", elementos);
  }
  if(simet == 0 || simet == 2){
    fecho(grSimet, qteElem, "simetrico", elementos);
  }
  if(!trans){
    fecho(grTrans, qteElem, "transitivo", elementos);
  }
  free(elementos);
  liberaGrafo(grafo, qteElem);
  liberaGrafo(grReflex, qteElem);
  liberaGrafo(grSimet, qteElem);
  liberaGrafo(grTrans, qteElem);
  return 0;
}
