#include<iostream>
#define MAX 100
using namespace std;

int main (){
    char mina[MAX][MAX], minabomba[MAX][MAX], comando;

    int x, y, contM=0;

    for (int i=1; i<=8; i++){
        for (int j=1; j<=8; j++){
           mina[i][j]='.';
        }
    }
    for (int i=1; i<=8; i++){
        cout<<i<<" ";
        for (int j=1; j<=8; j++){
            cout<<mina[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    //Criar contador de minas que foram marcadas;
    do{
      cout<<endl;

      cout<<"D - - - > Descobrir o quadrado (colocar as coordenadas)"<<endl;
      cout<<"M - - - > Marcar mina"<<endl;
      cout<<"T - - - > Talvez mina;"<<endl;
      cout<<"L - - - > Limpar marcação"<<endl;
      cout<<"S - - - > Sair do jogo"<<endl;

      cout<<endl;

      cout<<"Insira o comando ";
      cin>>comando;

      if (comando!='S'){
      //coordenadas
      cin>>x>>y;
      cout<<endl;
      }
      /*else{
      //acabar o jogo;
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

    for (int i=1; i<=8; i++){
        cout<<i<<" ";
        for (int j=1; j<=8; j++){
            cout<<mina[i][j];
        }
        cout<<endl;
    }

}while(comando!='S' || comando!='s');


   return 0;
}
