#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX 100
using namespace std;

//funcao para imprimir array de string
void imprimir (char v[MAX][MAX]) {
    for (int i=1; i<=8; i++){
        cout<<i<<' ';
        for (int j=1; j<=8; j++){
            cout<<v[i][j]<<' ';
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

//funcao para imprimir a localizacao das bombas ao final
void ImprimeBombas(char v[MAX][MAX], char w[MAX][MAX]){
		for(int i=1; i<=8; i++){
			for(int j=1; j<=8; j++){
				if(v[i][j]=='*' && w[i][j]=='M') {
					w[i][j];
				}
				else if(v[i][j]=='*'){
					w[i][j]='*';
				}
				else {
					w[i][j]=v[i][j];
				}
			}
		}
    imprimir(w);
    system("pause");
}

int main (){
    char mina[MAX][MAX], comando;
	char minabomba[MAX][MAX];
    int x, y, c, l,  aux=0, contNum=0, contBomba=1;

    int contM=10;

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
        if (minabomba[l][c] != '*') {
            minabomba[l][c]= '*';
            contBomba++;
        }
    }

    //verificar se ha bombas nas celulas vizinhas
    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
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

			//colocando numero de bombas dentro da celula
			if (minabomba[i][j] != '*') {
                minabomba[i][j]=inTChar(contNum);
            }
        }
    }

    imprimir(minabomba);

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

        switch (comando){
                case 'D':
                    if(minabomba[x][y] != '*') {
					mina[x][y] = minabomba[x][y];
					}
                    if(minabomba[x][y] == '*'){
                    	ImprimeBombas(minabomba, mina);
                    	exit(0);

					}
                    break;
                case 'M':
                    mina[x][y]='M';
					contM--;
                    break;
                case 'T':
                    mina[x][y]='?';
                    break;
                case 'L':
                    if(mina[x][y] == 'M'){
						mina[x][y]='.';
						contM++;
					}
					if(mina[x][y] == '?'){
						mina[x][y]='.';
					}
                    break;
                case 'S':
                    aux=1;
                }
            }

    return 0;
}
