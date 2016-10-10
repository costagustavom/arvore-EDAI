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
void removeArv (arv *x, int numero);



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
    if(q==NULL){
        *root=p;
    }
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


//função nao terminada (com bug: remoçao primeiro elemento; remoçao do elemento do meio seguido de inserções).
void removeArv(arv *x, int numero){
    arv p,  /* p aponta para o no a ser removido */ 
        q,  /* q aponta para o pai do no */ 
        rp, /* rp aponta que ira substituir o no p */ 
        f, 
        s;  /* sucessor do no p */

     p = *x; q=NULL;

     /* procura o no com a chave num, p aponta para o no 
     e q aponta para o pai do no */ 
     while ( p && p->chave != numero) { 
           q = p; 
           if ( numero < p->chave) 
              p = p->esq; 
           else 
               p = p->dir; 
     } /* fim do while */ 
     if (!p) return; /* a chave nao existe na arvore */

     /* agora iremos ver os dois primeiros casos, o no tem um filho 
        no maximo */ 
    if ((!((*x)->dir) && !((*x)->esq)) && (*x == p)){
      free(*x);
      *x = NULL;
      return;
    }
     if (p->esq == NULL) 
        rp = p->dir; 
     else 
         if (p->dir == NULL) 
            rp = p->esq; 
         else { 
              f=p; 
              rp = p->dir; 
              s = rp->esq;   /* s e sempre o filho esq de rp */ 
              while (s != NULL) { 
                    f = rp; 
                    rp = s; 
                    s = rp->esq; 
              } 
              /* neste ponto, rp e o sucessor em ordem de p */ 
              if (f != p) { 
                 /*  p nao e o pai de rp e rp == f->left */ 
                 f->esq = rp->dir; 
                 /* remove o no rp de sua atual posicao e o 
                    substitui pelo filho direito de rp 
                    rp ocupa o lugar de p 
                 */ 
                 rp->dir = p->dir; 
              } 
              /* define o filho esquerdo de rp de modo que rp 
                 ocupe o lugar de p 
              */ 
              rp->esq = p->esq; 
         } 
     /* insere rp na posicao ocupada anteriormente por p */ 
     if (q == NULL) 
        *x = rp; 
     else 
         if (p == q->esq) 
            q->esq = rp; 
         else 
             q->dir = rp; 
     free(p); 
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
                printf("passou\n");
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