#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  res->cabeca = (PONT) malloc(sizeof(REGISTRO));
  res->cabeca->id=-1;
  res->cabeca->tipo=-1;
  res->cabeca->quantidade=0;
  res->cabeca->valorUnitario=0;
  res->cabeca->proxProd=NULL;
  return res;
}


int tamanho(PLISTA l){
  PONT atual = l->cabeca->proxProd;
  int tam = 0;
  while (atual) {
    atual = atual->proxProd;
    tam++;
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  PONT atual = l->cabeca->proxProd;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n    ", numElementos);
  PONT atual = f->cabeca->proxProd;
  while (atual){
    printf(" [%i;%i;%i;%i;$%i]", atual->id, atual->tipo, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
    atual = atual->proxProd;
  }
  printf("\n\n");
}

int consultarValorUnitario(PLISTA l, int id){
  PONT atual = l->cabeca->proxProd;
   while (atual) {
    if (atual->id == id) return atual->valorUnitario;
    atual = atual->proxProd;
  }
  return 0;
}

PONT valorEntre(PLISTA l, int qttTotal){
	PONT atual = l->cabeca->proxProd;
	PONT esse;
	
	while(atual->proxProd){
		esse=atual;
		atual=atual->proxProd;
		
		if(atual->quantidade*atual->valorUnitario >= qttTotal && qttTotal > esse->quantidade*esse->valorUnitario) return esse;
		
	}
	
	if(qttTotal >= atual->quantidade*atual->valorUnitario) return atual;
	
}
PONT pegaAnterior(PLISTA l, int id){
	PONT atual = l->cabeca->proxProd;
	PONT esse = l->cabeca;
	while (atual) {
		if (atual->id == id) return esse;
		esse=atual;
		atual = atual->proxProd;
	}
	return NULL;

}

void organizarLista(PLISTA l){

	int tam = tamanho(l);

	int totalAtual, totalProxProd,i;

	for(i=0;i<tam;i++){
		PONT atual = l->cabeca->proxProd;
		while (atual->proxProd) {
			totalAtual=atual->quantidade*atual->valorUnitario;
			totalProxProd=atual->proxProd->quantidade*atual->proxProd->valorUnitario;

			if(totalAtual>=totalProxProd){

			PONT ant = pegaAnterior(l,atual->id);

			PONT aux=atual->proxProd->proxProd;

			ant->proxProd=atual->proxProd;
			atual->proxProd->proxProd=atual;
			atual->proxProd=aux;

			}
			if(atual->proxProd)
			atual=atual->proxProd;
		}
	}

}

bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
	if(id<0||tipo<0||quantidade<0||valor<0||buscarID(l,id)!=NULL) return false;
	PONT atual = l->cabeca;
	PONT nLista = (PONT) malloc(sizeof(REGISTRO));
	if(atual->proxProd==NULL){
		atual->proxProd = nLista;
	  	nLista->id=id;
	  	nLista->quantidade=quantidade;
	  	nLista->tipo=tipo;
	  	nLista->valorUnitario=valor;
	  	nLista->proxProd=NULL;
	  	return true;
	}
	while(atual->proxProd){

		if(quantidade*valor < atual->proxProd->quantidade*atual->proxProd->valorUnitario){
			if(atual->proxProd->proxProd==NULL){

			nLista->id=id;
			nLista->quantidade=quantidade;
			nLista->tipo=tipo;
			nLista->valorUnitario=valor;

			PONT aux1 = atual->proxProd;

		    atual->proxProd=nLista;
		    nLista->proxProd=aux1;

		    return true;
		}else{

			nLista->id=id;
			nLista->quantidade=quantidade;
			nLista->tipo=tipo;
			nLista->valorUnitario=valor;

			PONT aux=atual->proxProd;

			atual->proxProd=nLista;
			nLista->proxProd=aux;


			return true;
			}
		}else if(quantidade*valor > atual->proxProd->quantidade*atual->proxProd->valorUnitario){

		  	PONT aux = valorEntre(l,quantidade*valor);

			nLista->id=id;
			nLista->quantidade=quantidade;
			nLista->tipo=tipo;
			nLista->valorUnitario=valor;

			PONT ajuda = aux->proxProd;

			aux->proxProd=nLista;
			nLista->proxProd=ajuda;

			return true;
		}
		atual=atual->proxProd;
	}

}

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){

  PONT aux = buscarID(l,id);
  if(aux==NULL) return false;
  int auxQtt = aux->quantidade;
  
  if(quantidade>auxQtt || quantidade<=0) return false;
  
  
  if(auxQtt-quantidade==0){
  	PONT esse = pegaAnterior(l,id);
  	esse->proxProd=aux->proxProd;
  	
  	free(aux);
  	
  	return true;
  }else{

  	aux->quantidade-=quantidade;
  	organizarLista(l);

	return true;

  }

}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){
	PONT aux = buscarID(l,id);
	if(aux==NULL || valor<=0) return false;

	aux->valorUnitario=valor;
	organizarLista(l);

  return true;
}
