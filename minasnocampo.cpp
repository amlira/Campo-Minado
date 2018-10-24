#include<iostream>
#define MAX 100
using namespace std;

int main (){
    char mina[MAX][MAX];
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
    /*Criar contador de minas que foram marcadas;

      D - - - > Descobrir o quadrado (colocar as coordenadas);
      M - - - > Marcar mina;
      T - - - > Talvez mina;
      L - - - > Limpar marcação;
      S - - - > Sair do jogo;

    */





   return 0;
}
