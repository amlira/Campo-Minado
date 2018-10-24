#include<iostream>
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

    int x, y, contM=0;

    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
           mina[i][j]='.';
        }
    }
    imprimir(mina);
    cout<<endl;
    cout<<endl;

    while(comando!='S' || comando!='s'){
      cout<<endl;

      cout<<"D - - - > Descobrir o quadrado (colocar as coordenadas)"<<endl;
      cout<<"M - - - > Marcar mina"<<endl;
      cout<<"T - - - > Talvez mina;"<<endl;
      cout<<"L - - - > Limpar marcação"<<endl;
      cout<<"S - - - > Sair do jogo"<<endl;

      cout<<endl;

      cout<<"Insira o comando ";
      cin>>comando;
      letra(comando);

      if (comando!='S'){
      //coordenadas
      cin>>x>>y;
      cout<<endl;
      }
      /*else if (comando=='S' ||comando=='s') {
        break;
      }*/

    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
            switch (comando){
            case 'D':
                mina[x][y];
                break;
            case 'M':
                mina[x][y]='M';
                contM++;
                break;
            case 'T':
                mina[x][y]='?';
                break;
            case 'L':
                mina[x][y]='.';
                contM--;
                break;
            }
        }
    }

    cout<<endl;

    imprimir(mina);

}//while(comando!='S' || comando!='s');


   return 0;
}
