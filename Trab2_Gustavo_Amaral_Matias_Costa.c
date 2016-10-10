#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct arv{
    int chave;
    struct arv *esq, *dir;
}noarv, *arv;



void listaNoarv (arv p);
void nivelArv (arv p, int x);
void crescArv (arv p);
void decrescArv (arv p);
void consultaArv (arv p);
void removeArv (arv *p, int numero);



_Bool noExiste(arv *arv, int x){

  noarv *p,*q,*a;

  p=NULL;
  q=NULL;
  a=*arv;
  while((a!=NULL)&&(x!=a->chave)){
    q=a;
    if(x<(a->chave))
      a=a->esq;
    else
      a=a->dir;
  }
  if(a)
    return true;
  else
    return false;
}


_Bool insereArv(arv *root, int numero){

  noarv *p,*q,*a;

  if(!(p=(noarv *)malloc(sizeof(noarv)))||(noExiste(root,numero)))
    return false;
  p->chave = numero;
  p->esq = p->dir = NULL;
  a=*root;
  q=NULL;

  while(a!=NULL){
    q = a;
    if((p->chave) < (a->chave))
      a = a->esq;
    else
      a = a->dir;
  }
  if(q==NULL)
    *root=p;
  else{
    if((p->chave)<(q->chave))
      q->esq=p;
    else
      q->dir=p;
  }
  return true;

}

void listaNoarv(arv p){
  if(p){
      listaNoarv(p->esq);
      printf("chave: %d ", p->chave);
    if(p->esq)
      printf("fesq: %d ", p->esq->chave);
    else
      printf("fesq: nil ");
    if(p->dir)
      printf("fdir: %d\n", p->dir->chave);
    else
      printf("fdir: nil\n");
    listaNoarv(p->dir);
  }
}

void nivelArv(arv p, int x){
  if((p)&&(x)){
      x--;
      nivelArv(p->esq, x);
      if(!x)
          printf("%d\n", p->chave);
      nivelArv(p->dir, x);
  }
}

void crescArv(arv p){
  if(p){
      crescArv(p->esq);
      printf("%d\n", p->chave);
      crescArv(p->dir);
  }
  return;
}

void decrescArv(arv p){
  if(p){
      decrescArv(p->dir);
      printf("%d\n", p->chave);
      decrescArv(p->esq);
  }
  return;
}

void consultaArv(arv p){
  arv a;
  int h=0, x;
  a=p;
  scanf("%d", &x);
  while(a){
    if(a->chave==x){
      h=1;
      printf("existe no com chave: %d\n", x);}
    if(a->chave<x)
      a=a->dir;
    else
      a=a->esq;
  }
  if(!h)
    printf("nao existe no com chave:  %d\n", x);
}



void removeArv(arv *p, int numero){
  arv a,
      q,
      ra,
      f,
      s;

  a = *p; q=NULL;

  while ( a && a->chave != numero) {
    q = a;
    if ( numero < a->chave)
      a = a->esq;
      else
        a = a->dir;
  }
  if (!a) return;
    if ((!((*p)->dir) && !((*p)->esq)) && (*p == a)){
      free(*p);
      *p = NULL;
      return;
    }
    if (a->esq == NULL)
      ra = a->dir;
    else
        if (a->dir == NULL)
          ra = a->esq;
        else {
            f=a;
            ra = a->dir;
            s = ra->esq;
            while (s != NULL) {
              f = ra;
              ra = s;
              s = ra->esq;
            }
            if (f != a) {
              f->esq = ra->dir;
              ra->dir = a->dir;
            }
            ra->esq = a->esq;
        }
    if (q == NULL)
      *p = ra;
    else
      if (a == q->esq)
        q->esq = ra;
      else
        q->dir = ra;
  free(a);
  return;
}

int main(){
  int nivel, numero;
  char ordem, op;
  arv root = NULL;
  while(op!= 'e'){
      op = '\0';
      scanf("%c" , &op);
      switch(op){

      case 'i':
          scanf("%d" , &numero);
          insereArv(&root, numero);
          break;

      case 'c':
          consultaArv(root);
          break;

      case 'r':
          scanf("%d",&numero);
          removeArv(&root, numero);
          break;

      case 'p':
              getchar();
              scanf("%c",&ordem);
          if(ordem=='c')
              crescArv(root);
          else if (ordem=='d')
              decrescArv(root);
          break;

      case 'n':
          scanf("%d", &nivel);
          nivelArv(root, nivel);
          break;

      case 'd':
          listaNoarv(root);
      }
  }
  return 0;
}

