#include<iostream>
#include <cstdlib>
#include <ctime>
#define MAX 100
using namespace std;

//funcao para imprimir array de string
void imprimir (char v[MAX][MAX]) {
    for (int i=1; i<=8; i++){
        cout<<i<<"   ";
        for (int j=1; j<=8; j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
}

//funcao para imprimir array de inteiros
void imprimirInt (int w[MAX][MAX]) {
    for (int i=1; i<=8; i++){
        cout<<i<<"   ";
        for (int j=1; j<=8; j++){
            cout<<w[i][j]<<" ";
        }
        cout<<endl;
    }
}

//funcao para usar letras maiusculas ou minusculas
void letras (char &c) {
    if (96<c && c<123) {
        for(int i=0; i<256; i++) {
            c-=32;
        }
    }
}

//funcao para transformar int em char
char inTChar(int i) {
    switch (i) {
           case 0: return '0';
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

//funcao para imprimir a localizacao das bombas ao final
void ImprimeBombas(int v[MAX][MAX], char w[MAX][MAX]){
		for(int i=1; i<=10; i++){
			for(int j=1; j<=10; j++){
				if(v[i][j]==9){
					w[i][j]='*';
				}
				else {
					w[i][j]=inTChar(v[i][j]);
				}
			}
		}
    imprimir(w);
    system("pause");
}

int main (){
    char mina[MAX][MAX], comando;
	int minabomba[MAX][MAX];
    int x, y, c, l, contM=10, aux=0, contNum=0, contBomba=1;

    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
            mina[i][j]='.';
        }
    }

    srand(time(NULL));

    //colando bombas aleatoriamente pela matriz
	while (contBomba <= 10) {
        l=1+rand()%8;
        c=1+rand()%8;
        if (minabomba[l][c] != 9) {
            minabomba[l][c]= 9;
            contBomba++;
        }
    }
    
    //verificar se ha bombas nas celulas vizinhas
    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
        	contNum=0;
			if (minabomba[i-1][j-1] == 9) {
				contNum++;
			}
			if (minabomba[i-1][j] == 9) {
				contNum++;
			}
			if (minabomba[i-1][j+1] == 9) {
				contNum++;
			}
			if (minabomba[i][j-1] == 9) {
				contNum++;
			}
			if (minabomba[i][j+1] == 9) {
				contNum++;
			}
			if (minabomba[i+1][j-1] == 9) {
				contNum++;
			}
			if (minabomba[i+1][j] == 9) {
				contNum++;
			}
			if (minabomba[i+1][j+1] == 9) {
				contNum++;
			}
			
			//colocando numero de bombas dentro da celula
			if (minabomba[i][j] != 9) {
				minabomba[i][j]=contNum;
			}
        }
    }

    imprimirInt(minabomba);
    cout<<"\n"<<"\n"<<endl;

    while(aux!=1){

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

        for (int i=1; i<=8; i++){
            for (int j=1; j<=8; j++){
                switch (comando){
                case 'D':
                    if(minabomba[x][y] != 9) {
					mina[x][y] = inTChar(minabomba[x][y]);
					}
                    if(minabomba[x][y] == 9){
                    	ImprimeBombas(minabomba, mina);
					}
                    break;
                case 'M':
                    mina[x][y]='M';
                    /* Esse contador ta dando super errado
					contM--;*/
                    break;
                case 'T':
                    mina[x][y]='?';
                    break;
                case 'L':
                    mina[x][y]='.';
                    /* Ta dando errado em todo canto
					contM--;*/
                    break;
                case 'S':
                    aux=1;
                }
            }
        }

    }


    return 0;
}
