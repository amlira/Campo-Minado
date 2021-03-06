#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <ctime>
#define MAX 100
int segundosIniciais;
using namespace std;
void analisarAbaixo (char v[MAX][MAX], char w[MAX][MAX], int i, int j);
void analisarAcima (char v[MAX][MAX], char w[MAX][MAX], int i, int j);
void analisarDireita (char v[MAX][MAX], char w[MAX][MAX], int i, int j);
void analisarEsquerda (char v[MAX][MAX], char w[MAX][MAX], int i, int j);
void descobrirNulos(char v[MAX][MAX], char w[MAX][MAX], int i, int j);
//funcao para imprimir array de string
void imprimir (char v[MAX][MAX]) {
    for (int i=0; i<8; i++){
        cout<<i+1<<' ';
        for (int j=0; j<8; j++){
            cout<<v[i][j]<<' ';
        }
        cout<<endl;
    }
}
//funcao para usar letras maiusculas ou minusculas
void letras (char &c) {
    if (96<c && c<123) {
            c-=32;
    }
}

//funcao para transformar int em char
char inTChar(int i) {
    switch (i) {
           case 0: return '_';
           case 1: return '1';
           case 2: return '2';
           case 3: return '3';
           case 4: return '4';
           case 5: return '5';
           case 6: return '6';
           case 7: return '7';
           case 8: return '8';
    }
}

//colocando bombas aleatoriamente pela matriz
void GeraBombas (char minabomba[MAX][MAX]){
	int c, l;
	int contBomba=1;
	while (contBomba <= 10) {
        l=1+rand()%8;
        c=1+rand()%8;
        if (minabomba[l][c] != '*') {

            minabomba[l][c]= '*';
            contBomba++;
        }
    }
}

    //verificar se ha bombas nas celulas vizinhas e contar quantas há por perto
void BombasVizinhas (char minabomba[MAX][MAX]){
		int contNum=0;
		for (int i=0; i<8; i++){
			for (int j=0; j<8; j++){
					contNum=0;
					if (minabomba[i-1][j-1] == '*') {
						contNum++;
					}
					if (minabomba[i-1][j] == '*') {
						contNum++;
					}
					if (minabomba[i-1][j+1] == '*') {
						contNum++;
					}
					if (minabomba[i][j-1] == '*') {
						contNum++;
					}
					if (minabomba[i][j+1] == '*') {
						contNum++;
					}
					if (minabomba[i+1][j-1] == '*') {
						contNum++;
					}
					if (minabomba[i+1][j] == '*') {
						contNum++;
					}
					if (minabomba[i+1][j+1] == '*') {
						contNum++;
					}

				//contagem de bombas por perto
				if (minabomba[i][j] != '*') {
				if(contNum == 1) {
					minabomba[i][j]='1';
				} else if(contNum==2) {
					minabomba[i][j]='2';
				} else if(contNum==3) {
					minabomba[i][j]='3';
				}  else if(contNum==4) {
					minabomba[i][j]='4';
				}  else if(contNum==5) {
					minabomba[i][j]='5';
				}  else if(contNum==6) {
					minabomba[i][j]='6';
				}  else if(contNum==7) {
					minabomba[i][j]='7';
				} else if(contNum==0) {
					minabomba[i][j]='_';
				}
			}
        }
    }
}


//funcao para imprimir a localizacao das bombas ao final
void ImprimeBombas(char v[MAX][MAX], char w[MAX][MAX]){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				if(v[i][j] == '*' && w[i][j] == 'M') {
					w[i][j]='M';
				}
				else if(v[i][j] == '*'){
					w[i][j] = '*';
				}
				else if(v[i][j] != '*' && w[i][j] == 'M') {
					w[i][j] = 'X';
				}
				else {
					w[i][j] = v[i][j];
				}
			}
		}
    imprimir(w);
    system("pause");
}

int converterSegundos(int hora, int minuto, int segundo) {
	return (segundo + 60*minuto+3600*hora);
}


//Análise
void analisarDireita (char v[MAX][MAX], char w[MAX][MAX], int i, int j){
		if(j+1 < 8) {
			if (v[i][j+1] == '_' && w[i][j+1] != v[i][j+1]) {
				w[i][j+1] = v[i][j+1];

				descobrirNulos(v, w, i, (j+1));
			}
			else if (v[i][j+1] != '*' && v[i][j+1] != '_' && w[i][j+1] != v[i][j+1] ){
				w[i][j+1] = v[i][j+1];
				/*analisarAbaixo(v, w, i, (j+1));
				analisarAcima(v, w, i, (j+1));*/
			}
		}
}

void analisarEsquerda (char v[MAX][MAX], char w[MAX][MAX], int i, int j) {
		if(j-1 >= 0) {
			if (v[i][j-1] == '_' && w[i][j-1] != v[i][j-1]) {
				w[i][j-1] = v[i][j-1];

				descobrirNulos(v, w, i, (j-1));

			} else if (v[i][j-1] != '*' && v[i][j-1] != '_' && w[i][j-1] != v[i][j-1]){
				w[i][j-1] = v[i][j-1];


			}
		}
}

void analisarAcima (char v[MAX][MAX], char w[MAX][MAX], int i, int j) {
		if(i-1 >= 0) {
			if (v[i-1][j] == '_' && w[i-1][j] != v[i-1][j]) {
				w[i-1][j] = v[i-1][j];

                descobrirNulos(v, w, (i-1), j);

			}
			if (v[i-1][j-1] == '_' && w[i-1][j-1] != v[i-1][j-1]) {
				w[i-1][j-1] = v[i-1][j-1];

                descobrirNulos(v, w, (i-1), (j-1));

			}
			if (v[i-1][j+1] == '_' && w[i-1][j+1] != v[i-1][j+1]) {

				w[i-1][j+1] = v[i-1][j+1];

                descobrirNulos(v, w, (i-1), (j+1));

			} else if(v[i-1][j] != '_' && w[i-1][j] != v[i-1][j]){
				w[i-1][j] = v[i-1][j];
			}
		}
}

void analisarAbaixo (char v[MAX][MAX], char w[MAX][MAX], int i, int j) {
		if(i+1 < 8) {

           if (v[i+1][j-1] == '_' && w[i+1][j-1] != v[i+1][j-1] && j>=1) {
				w[i+1][j-1] = v[i+1][j-1];
                cout<<"oi"<<endl;
                descobrirNulos(v, w, (i+1), (j-1));

			}
			if (v[i+1][j] == '_' && w[i+1][j] != v[i+1][j]) {
				w[i+1][j] = v[i+1][j];
                descobrirNulos(v, w, (i+1), j);

			}
			/*if (v[i+1][j-1] == '_' && w[i+1][j-1] != v[i+1][j-1] && j>=1) {
				w[i+1][j-1] = v[i+1][j-1];
                cout<<"oi"<<endl;
                descobrirNulos(v, w, (i+1), (j-1));
			}*/
			if (v[i+1][j+1] == '_' && w[i+1][j+1] != v[i+1][j+1] && j<7) {
				w[i+1][j+1] = v[i+1][j+1];

                descobrirNulos(v, w, (i+1), (j+1));

			}
			else if(v[i+1][j] != '_' && w[i+1][j] != v[i+1][j]) {
				w[i+1][j] = v[i+1][j];
			}
		}
}

void descobrirNulos(char v[MAX][MAX], char w[MAX][MAX], int i, int j){
	
		/*if (v[i][j]=='*'){
			para o jogo
		}
		else if (v[i][j]=='*' && v[i][j]=='_'){
			w[i][j]=v[i][j];
		}
		else {
			w[i][j]=v[i][j];
		
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		descobrirNulos(v, w, i , j);
		}
		obs n precisa mais das analises
		se n funcionar volta para a chamada das funcoes de analise
		*/
		
}




void Duracao() {
	time_t rawtime;
	struct tm * timeinfo;
	int hora, minuto, segundo;
	int segundosTotal, total;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	hora = timeinfo->tm_hour;
	minuto = timeinfo->tm_min;
	segundo = timeinfo->tm_sec;
	segundosTotal = converterSegundos(hora, minuto, segundo);

	total = segundosTotal-segundosIniciais;

	if(total < 3600) {
		hora = 0;
		if(total < 60) {
			minuto = 0;
			segundo = total;
		} else if(total > 60) {
			minuto = total/60;
			segundo = total%60;
		} else {
			minuto = 60;
		}

	} else if(total > 3600) {
		hora = total/3600;
		minuto = (total - (3600*hora))/60;
		segundo = total%60;
	}

	cout<<hora<<":"<<minuto<<":"<<segundo<<endl;

}

void converterSegundosinit(int hora, int minuto, int segundo) {
	segundosIniciais = (segundo + 60*minuto+3600*hora);
}



int main (){
    char mina[MAX][MAX], comando;
	char minabomba[MAX][MAX];
    int x, y, aux=0;

    time_t rawtime;
	struct tm * timeinfo;
	int hora, minuto, segundo;



    int contM=10;

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            mina[i][j] = '.';
        }
    }

    srand(time(NULL));

	GeraBombas(minabomba);

	BombasVizinhas(minabomba);

    imprimir(minabomba);

    cout<<"\n"<<"\n"<<endl;

    time (&rawtime);
	timeinfo = localtime (&rawtime);

	hora = timeinfo->tm_hour;
	minuto = timeinfo->tm_min;
	segundo = timeinfo->tm_sec;

	converterSegundosinit(hora, minuto, segundo);

    while(aux!=1){

		Duracao();
		cout<<endl;
        imprimir(mina);

        cout<<"\n"<<"\n"<<endl;


        cout<<"Minas a marcar: "<<contM<<endl;
        cout<<"D - - - > Descobrir o quadrado (colocar as coordenadas)"<<endl;
        cout<<"M - - - > Marcar mina"<<endl;
        cout<<"T - - - > Talvez mina"<<endl;
        cout<<"L - - - > Limpar marcacao"<<endl;
        cout<<"S - - - > Sair do jogo"<<endl;

        cout<<endl;

        cout<<"Insira o comando: ";
        cin>>comando;
        letras(comando);

        if (comando!='S'){
            cout<<"Insira as coordenadas: ";
            cin>>x>>y;
        }
        cout<<"\n"<<"\n"<<endl;
        x=x-1;
        y=y-1;
        switch (comando){
                case 'D':
                    /*if(minabomba[x][y] != '*') {
					mina[x][y] = minabomba[x][y];
					}
                    if(minabomba[x][y] == '*'){
                    	ImprimeBombas(minabomba, mina);
                    	exit(0);
					}
                    break;*/
                    if(minabomba[x][y] != '*' ) {
						mina[x][y] = minabomba[x][y];
					}
                    if(minabomba[x][y] == '*'){
                    	ImprimeBombas(minabomba, mina);
                    	exit(0);
                    }
					if(minabomba[x][y] == '_') {
						descobrirNulos(minabomba, mina, x, y);
					}
                    break;

                case 'M':
                    mina[x][y] = 'M';
					contM--;
                    break;
                case 'T':
                    mina[x][y] = '?';
                    break;
                case 'L':
                    if(mina[x][y] == 'M'){
						mina[x][y] = '.';
						contM++;
					}
					if(mina[x][y] == '?'){
						mina[x][y] = '.';
					}
                    break;
                case 'S':
                    aux=1;
                }
            }

    return 0;
}
