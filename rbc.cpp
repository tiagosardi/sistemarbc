//stayFit, gympass
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define DISTANCIA_MINIMA 0.6
#define DISTANCIA_MAXIMA 1.6
int k=3; //numero de amostras dentro de um arquivo ou dentro da funcao criaAmostras; 
int novaClasse=2; //ultima classe da lista original de instancias


//AMOSTRAS PARA TESTAR O RBC PELO EDITOR
//float ATT0=4.4, ATT1=3.2, ATT2=1.0, ATT3=0.2; //classe 0
//float ATT0=6.0, ATT1=3.4, ATT2=4.5, ATT3=1.6; //classe 1
float ATT0=6.6, ATT1=3.3, ATT2=6.0, ATT3=2.5; //classe 2
//float ATT0=8.4, ATT1=3.9, ATT2=1.2, ATT3=1.2; //classe NOVA

typedef struct instancias{
	float atributo[4];
	float classe;
}instancias;

typedef instancias amostras;

void imprimeInstancias(instancias* instancia, int n);
float distanciaEuclidiana(float a1, float b1,float a2,float b2,float a3,float b3,float a4,float b4);
void criaNovaClasse(instancias* instancia, int n, instancias* teste, int k);
void descobreClasse(instancias* instancia, int n);
void criaListaSemRuido(instancias* instancia, int n);
void compara(instancias* instancia, int n);
void criaAmostras(char* arquivo , instancias* instancia);
void capturaInstancias(char* arquivo, int n, instancias *vetInstancia);

void imprimeInstancias(instancias* instancia, int n){
	int i;
	for(i= 0 ; i<n ; i++){
		if(instancia[i].classe!=-1){
			printf("%.1f,%.1f,%.1f,%.1f,%.0f",instancia[i].atributo[0], instancia[i].atributo[1], instancia[i].atributo[2],instancia[i].atributo[3],instancia[i].classe)!=EOF;
			printf("\n");
		}
		
	}
	printf("\n\n");	
}

float distanciaEuclidiana(float a1, float b1,float a2,float b2,float a3,float b3,float a4,float b4){
	return (sqrt(
		pow((a1-b1),2)+
		pow((a2-b2),2)+
		pow((a3-b3),2)+
		pow((a4-b4),2)
		));
}
void criaNovaClasse(instancias* instancia, int n, instancias* teste, int k){
	int i, novo;
	for(i=n ; i<n+k ; i++){
		instancia[i].atributo[0]=teste[k-1].atributo[0];
		instancia[i].atributo[1]=teste[k-1].atributo[1];
		instancia[i].atributo[2]=teste[k-1].atributo[2];
		instancia[i].atributo[3]=teste[k-1].atributo[3];
		instancia[i].classe=teste[k-1].classe;
		novo=k;
		novo++;
	}
	//imprimeInstancias(instancia,n+k);

}

//A PARTIR DE UMA AMOSTRA OU VARIAS PARA TESTE, ESTA FUNCAO VAI IDENTIFICAR QUAL CLASSE A AMOSTRA SE ENCAIXA
void descobreClasse(instancias* instancia, int n){
	int i,j, printei;
	instancias teste[k];
	float menor;
	float distanciaInstancias;
	
	teste[i].atributo[0]=ATT0;
	teste[i].atributo[1]=ATT1;
	teste[i].atributo[2]=ATT2;
	teste[i].atributo[3]=ATT3;
	srand(unsigned(time(NULL)));
	for(i=1;i<k;i++){

		teste[i].atributo[0]=(50+rand()%70)/10;
		teste[i].atributo[1]=(20+rand()%44)/10;
		teste[i].atributo[2]=(10+rand()%45)/10;
		teste[i].atributo[3]=(2+rand()%25)/10;
		
	}


	menor= distanciaEuclidiana(
			instancia[0].atributo[0], teste[0].atributo[0],
			instancia[0].atributo[1], teste[0].atributo[1],
			instancia[0].atributo[2], teste[0].atributo[2],
			instancia[0].atributo[3], teste[0].atributo[3]);

	for(j=0 ; j<k ; j++){
		for(i = 1; i<n; i++){
			distanciaInstancias=distanciaEuclidiana(
			instancia[i].atributo[0], teste[j].atributo[0],
			instancia[i].atributo[1], teste[j].atributo[1],
			instancia[i].atributo[2], teste[j].atributo[2],
			instancia[i].atributo[3], teste[j].atributo[3]);

			if(distanciaInstancias<menor){
				teste[j].classe=instancia[i].classe;
				menor=distanciaInstancias;
				printei=distanciaInstancias;
			}
		}
		if(menor>DISTANCIA_MAXIMA){
			novaClasse=4;
			teste[j].classe=novaClasse;
			criaNovaClasse(instancia, n, teste, k);
			printf("\nInstancia muito distante");
		}	
		printf("\nA instancia %.1f,%.1f,%.1f,%.1f, pertence a classe: %.0f\nsua distancia eh: %.1f\n", 
		teste[j].atributo[0], 
		teste[j].atributo[1], 
		teste[j].atributo[2],
		teste[j].atributo[3],
		teste[j].classe, menor);
		menor=9999;	
	}

	
	printf("\n\nA primeira instancia teste foi criada numa variavel global para facilitar a manipulacao.\nAs demais sao criadas aleatoriamente\n");

	//nova lista gerada com mais classes	
	printf("\n==========================================\n");
	printf("LISTA DE INSTANCIAS COM NOVAS CLASSES");
	printf("\n==========================================\n");
	imprimeInstancias(instancia, n+k);




}

//DESCARTA A LISTA DE INSTANCIAS COM RUIDOS E PASSA A USAR UMA LISTA MENOR SEM RUIDO
void criaListaSemRuido(instancias* instancia, int n){
	instancias* listaSemRuido=(instancias*)malloc(sizeof(instancias)*50);
	int realoca=0;
	int i,k=0;
	for(i= 0 ; i<n ; i++){
		if(instancia[i].classe!=-1){
			listaSemRuido[k].atributo[0]=instancia[i].atributo[0];
			listaSemRuido[k].atributo[1]=instancia[i].atributo[1];
			listaSemRuido[k].atributo[2]=instancia[i].atributo[2];
			listaSemRuido[k].atributo[3]=instancia[i].atributo[3];
			listaSemRuido[k].classe=instancia[i].classe;
			k++;

		}
		
	}
	printf("\n===============================\n");
	printf("\t2.LISTA SEM RUIDO");
	printf("\n===============================\n");
	imprimeInstancias(listaSemRuido,k);
	descobreClasse(listaSemRuido, k);
}
	

//FAZ A COMPARACAO DE UMA INSTANCIA DA LISTA COM AS DEMAIS PARA RETIRAR OS RUIDOS DEPOIS
void compara(instancias* instancia, int n){
	int i,j,k, cont=0;
	float distanciaInstancias;

	for(i = 0; i<n; i++){
		if(instancia[i].classe!=-1){
			for(j=i+1 ; j<n ; j++){
				if(instancia[j].classe!=-1){
					distanciaInstancias=distanciaEuclidiana(
					instancia[i].atributo[0], instancia[j].atributo[0],
					instancia[i].atributo[1], instancia[j].atributo[1],
					instancia[i].atributo[2], instancia[j].atributo[2],
					instancia[i].atributo[3], instancia[j].atributo[3]);

					if(distanciaInstancias<DISTANCIA_MINIMA)
						instancia[j].classe=-1;
					else
						cont++;
				}
			}
		}
		
	}
	criaListaSemRuido(instancia,n);
	//imprimeInstancias(instancia,n);

}

//PEGA ALEATORIAMENTE 5 INSTANCIAS DA LISTA COM RUIDOS PARA USAR EM TESTES
void criaAmostras(char* arquivo , instancias* instancia, int n){
	amostras amostra[5];
	int i, raffle;
	FILE *fp = fopen(arquivo, "r");
	if(fp==NULL){
		printf("\nNao Abriu\n");
		return;
	}

	srand(unsigned(time(NULL)));
	for(i= 0 ; i<5 ; i++){
		raffle=rand()%n;
		fscanf(fp,"%f,%f,%f,%f,%f",&instancia[raffle].atributo[0], &instancia[raffle].atributo[1], &instancia[raffle].atributo[2],&instancia[raffle].atributo[3],&instancia[raffle].classe)!=EOF;
	}
	
	//imprimeInstancias(instancia, 5);
	
	printf("\n\n");
	fclose(fp);
}

void capturaInstancias(char* arquivo, int n, instancias *vetInstancia){
	instancias instancia[n];
	int i,a;
	FILE *fp = fopen(arquivo, "r");
	if(fp==NULL){
		printf("\nNao Abriu\n");
		exit(1);
	}

	for(i= 0 ; i<n ; i++){
		fscanf(fp,"%f,%f,%f,%f,%f",&instancia[i].atributo[0], &instancia[i].atributo[1], &instancia[i].atributo[2],&instancia[i].atributo[3],&instancia[i].classe)!=EOF;
	}
	printf("\n=============================================\n");
	printf("\t1.INSTANCIAS DO ARQUIVO IRIS.DATA");
	printf("\n=============================================\n");
	imprimeInstancias(instancia, n);
	criaAmostras(arquivo, instancia, n);
	
	printf("\n\n");
	compara(instancia,n);
	fclose(fp);
}
int main(int argc, char *argv[]){	
	int n=1;
	FILE *fp = fopen(argv[1], "r");
	instancias* vetInstancia;
	
	char caiu;
	if(fp==NULL){
		printf("\nNao Abriu\n");
		return 0;
	}
	while(fscanf(fp,"%c",&caiu)!=EOF){
		if(caiu=='\n')
			n++;
	}
	vetInstancia = (instancias*)malloc(6*n*sizeof(instancias));

	capturaInstancias(argv[1], n , vetInstancia);

	
}