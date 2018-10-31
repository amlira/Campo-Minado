#include<iostream>
#include <cstdlib>
#include <ctime>
#define MAX 100
using namespace std;

void imprimir(char v[MAX][MAX]) {
    for (int i=1; i<=8; i++){
        cout<<i<<" ";
        for (int j=1; j<=8; j++){
            cout<<v[i][j];
        }
        cout<<endl;
    }
}

void letras (char &c) {
    if (96<c && c<123) {
        for(int i=0; i<256; i++) {
            c-=32;
        }
    }
}

int main (){
    char mina[MAX][MAX], minabomba[MAX][MAX], comando;

    int x, y, c, l, contM=10, aux=0, contNum=0, contBomba=1;

    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
            minabomba[i][j]='.';
            mina[i][j]='.';
        }
    }

    srand(time(NULL));

    while (contBomba <= 10) {
        l=1+rand()%8;
        c=1+rand()%8;
        if (minabomba[l][c] != '*') {
            minabomba[l][c]= '*';
            contBomba++;
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
        cout<<"T - - - > Talvez mina;"<<endl;
        cout<<"L - - - > Limpar marcação"<<endl;
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
                    mina[x][y];
                    break;
                case 'M':
                    mina[x][y]='M';
                    contM--;
                    break;
                case 'T':
                    mina[x][y]='?';
                    break;
                case 'L':
                    mina[x][y]='.';
                    contM++;
                    break;
                case 'S':
                    aux=1;
                }
            }
        }

    }


    return 0;
}
