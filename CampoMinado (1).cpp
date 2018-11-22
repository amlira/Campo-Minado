#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

#define MAX 100
int segundosIniciais;
using namespace std;

struct Pessoa {
	string nome; 
	int TempoEmSegundos;
};

//FUNCAO DO MENU
void menu (char opcoes){

cout<<"                                                   BEM VINDO AO CAMPO MINADO       "<<endl;
cout<<"                                              ESCOLHA UM DOS NIVEIS E DIVIRTA-SE   "<<endl;
cout<<"                                                        1. Novo Jogo               "<<endl;
cout<<"                                                        2. Melhores Tempos         "<<endl;
cout<<"                                                        3. Sair                    "<<endl;
}
void menu2 (char opcoes2){
cout<<"                                                   BEM VINDO AO CAMPO MINADO       "<<endl;
cout<<"                                              ESCOLHA UM DOS NIVEIS E DIVIRTA-SE   "<<endl;
cout<<"                                                        1. Nivel facil             "<<endl;
cout<<"                                                        2. Nivel intermediario     "<<endl;
cout<<"                                                        3. Nivel personalizado     "<<endl;
cout<<"                                                        4. Voltar                  "<<endl;
}
//FUNÇÃO PARA IMPRIMIR ARRAY
void imprimir (char v[MAX][MAX], int n, int m) {
    for (int i=0; i<n; i++){
        if(i+1 < 10) {
            cout<<"0"<<i+1<<' ';
        } else {
            cout<<i+1<<' ';
        }
        for (int j=0; j<m; j++){
            cout<<v[i][j]<<' ';
        }
        cout<<endl;
    }
}

//FUNÇÃO PARA USAR LETRAS MAIUSCULAS OU MINUSCULAS
void letras (char &c) {
    if (96<c && c<123) {
        c-=32;
    }
}

//FUNÇÃO PARA TRANSFORMAR INT EM CHAR
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


//FUNÇÃO PARA COLOCAR BOMBAS ALEATORIAMENTE NA MATRIZ
void GeraBombas (char v[MAX][MAX], int lin, int col, int numB) {
	srand(time(NULL));
	int c, l;
	int contBomba=0;
	while (contBomba < numB){
        l=0+rand()%lin;
        c=0+rand()%col;
        if (v[l][c] != '*') {
            v[l][c] = '*';
            contBomba++;
        }
    }

    //tirar essa parte, só teste de codigo
    cout<<endl;
    imprimir(v, lin, col);
    cout<<"\n"<<endl;
}

//FUNÇÃO PARA VERIFICAR QUANTIDADE DE BOMBAS NAS CELULAS VIZINHAS
void BombasVizinhas (char minabomba[MAX][MAX], int n, int m) {
	int contNum=0;
	for (int i=0; i<n; i++){
		for (int j=0; j<m; j++){
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
				} else if(contNum==4) {
					minabomba[i][j]='4';
				} else if(contNum==5) {
					minabomba[i][j]='5';
				} else if(contNum==6) {
					minabomba[i][j]='6';
				} else if(contNum==7) {
					minabomba[i][j]='7';
				} else if(contNum==0) {
					minabomba[i][j]='_';
				}
			}
    	}
	}
}

//FUNÇÃO PARA IMPRIMIR BOMBAS QUANDO PERDE O JOGO
void ImprimeBombas(char v[MAX][MAX], char w[MAX][MAX], int n, int m){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
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
    imprimir(w, n, m);
    cout<<"\n";
	cout<<" _____________________________"<<endl;
	cout<<"|                             |"<<endl;
	cout<<"|        VOCE PERDEU!!!       |"<<endl;
	cout<<"|_____________________________|"<<endl;
	cout<<"\n";
    system("pause");
}


int converterSegundos(int hora, int minuto, int segundo) {
	return (segundo + 60*minuto+3600*hora);
}

//FUNÇÃO COM O COMANDO DE DESCOBRIR UMA CELULA
void descobrir(char v[MAX][MAX], char w[MAX][MAX], int i, int j, int n, int m, int& cont) {
	if (v[i][j] == '*' && w[i][j] != v[i][j]){
    	ImprimeBombas(v, w, n, m);
    	exit(0);
	}
	else if (v[i][j] != '*' && v[i][j] != '_' && w[i][j] != v[i][j]){
		w[i][j] = v[i][j];
		cont++;
	}
	else if (v[i][j] == '_' && w[i][j] != v[i][j]){
		w[i][j] = v[i][j];
		cont++;

		if ((i-1) >= 0) {
			if ((j-1) >=0){
				descobrir(v, w, i-1, j-1, n, m, cont);
			}

			descobrir(v, w, i-1, j, n, m, cont);

			if ((j+1) <=m-1) {
				descobrir(v, w, i-1, j+1, n, m, cont);
			}
		}
		if ((i+1) <=n-1 ) {
			if ((j-1) >= 0) {
				descobrir(v, w, i+1, j-1, n, m, cont);
			}
			descobrir(v, w, i+1, j, n, m, cont);
			if ((j+1) <=m-1) {
				descobrir(v, w, i+1, j+1, n, m, cont);
			}
		}
		if ((j-1) >= 0) {
			descobrir(v, w, i, j-1, n, m, cont);

		}
		if ((j+1) <= m-1) {
			descobrir(v, w, i, j+1, n, m, cont);
		}
	}
}

string converterHora (int total) {
	string TempoTotal;
	int hora, minuto, segundo;
	
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
	} else if(total >= 3600) {
		hora = total/3600;
		minuto = (total - (3600*hora))/60;
		segundo = total%60;
	}
	
	TempoTotal = to_string(hora)+":"+to_string(minuto)+":"+to_string(segundo);
		
	return TempoTotal;
}

 int Duracao() {
	time_t rawtime;
	struct tm * timeinfo;
	int hora, minuto, segundo;
	int segundosTotal, total;
	fstream arquivo;
	
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
	
	return total;
 }
 
 
void tratarArquivo(bool salvar, bool ler, Pessoa &jogador, char opcaoArquivo, int duracao) {
	  
	  int quantidade=0, quantidade_facil=0;
	  Pessoa jogadoresPersonalizado[4];
	  Pessoa jogadoresFacil[4];
	  Pessoa jogadoresIntermediario[4];
	  string linha;
	  int hora, minuto, segundo;
	  int contador=0, contadorFacil=0, contadorIntermediario = 0;
	  Pessoa auxiliar;
	  
	  // ofstream - arquivo apenas para saída de dados
	  ifstream arq_in;
	  ofstream arq_out;
	  // função open - abre o arquivo. Cria o arquivo caso ele não exista.
	  if(ler && opcaoArquivo == 't') {
		  arq_in.open("Personalizado.txt");
		  // Insere nomes no arquivo (operador "<<")		  
		  if (arq_in.is_open()) {
			  cout<<"Recordes do personalizado: "<<endl;
		  //eof() - retorna true ao atingir o fim do arquivo
			  while ((!arq_in.eof())) {
					getline (arq_in, linha, '.');
					stringstream num(linha);
					num >> quantidade;
					getline (arq_in, linha, ' ');
					getline(arq_in, linha, ';');
					
					jogadoresPersonalizado[contador].nome = linha;
					getline (arq_in, linha, ':');
					getline (arq_in, linha, ' ');
					getline (arq_in, linha, ':');
					
					stringstream geek(linha);
					geek >> hora;
					
					hora = hora*3600;
					getline(arq_in, linha, ':');
					stringstream geeks(linha);
					
					geeks >> minuto;
					minuto = minuto*60;
					getline(arq_in, linha, '\n');
					stringstream geekss(linha);
					geekss>>segundo;
					jogadoresPersonalizado[contador].TempoEmSegundos = hora+minuto+segundo;
					contador++;
			  }
			  arq_in.close();
			  for(int i = 0; i < quantidade; i++) {
				string tempo = converterHora(jogadoresPersonalizado[i].TempoEmSegundos);	
				cout<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
			  }
		  } else {
			cout << "ERRO: arquivo Personalizado.txt não foi aberto ou não existe" << endl;
		  }
		  
		  arq_in.open("Fácil.txt");
		  // Insere nomes no arquivo (operador "<<")		  
		  if (arq_in.is_open()) {	
			  cout<<"Recordes do fácil: "<<endl;
		  //eof() - retorna true ao atingir o fim do arquivo
			  while ((!arq_in.eof())) {
					getline (arq_in, linha, '.');
					stringstream num(linha);					
					num >> quantidade;
					getline (arq_in, linha, ' ');
					getline(arq_in, linha, ';');
					jogadoresFacil[contadorFacil].nome = linha;
					getline (arq_in, linha, ':');
					getline (arq_in, linha, ' ');
					getline (arq_in, linha, ':');
					stringstream geek(linha);
					
					geek >> hora;
					
					hora = hora*3600;
					getline(arq_in, linha, ':');
					stringstream geeks(linha);
					
					geeks >> minuto;
					minuto = minuto*60;
					getline(arq_in, linha, '\n');
					stringstream geekss(linha);
					geekss>>segundo;
					jogadoresFacil[contadorFacil].TempoEmSegundos = hora+minuto+segundo;
					contadorFacil++;
			  }
			  arq_in.close();
			  for(int i = 0; i < quantidade; i++) {
				string tempo = converterHora(jogadoresFacil[i].TempoEmSegundos);	
				cout<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
			  }
		  } else {
			cout << "ERRO: arquivo Fácil.txt não foi aberto ou não existe" << endl;
		  }  
		  
		  arq_in.open("Intermediário.txt");
		  // Insere nomes no arquivo (operador "<<")		  
		  if (arq_in.is_open()) {
			  cout<<"Recordes do intermediário: "<<endl;
		  //eof() - retorna true ao atingir o fim do arquivo
			  while ((!arq_in.eof())) {
					getline (arq_in, linha, '.');
					stringstream num(linha);
					num >> quantidade;
					getline (arq_in, linha, ' ');
					getline(arq_in, linha, ';');
					jogadoresIntermediario[contador].nome = linha;
					getline (arq_in, linha, ':');
					getline (arq_in, linha, ' ');
					getline (arq_in, linha, ':');
					stringstream geek(linha);
					geek >> hora;
					hora = hora*3600;
					getline(arq_in, linha, ':');
					stringstream geeks(linha);
					geeks >> minuto;
					minuto = minuto*60;
					getline(arq_in, linha, '\n');
					stringstream geekss(linha);
					geekss>>segundo;
					jogadoresIntermediario[contador].TempoEmSegundos = hora+minuto+segundo;
					contador++;
			  }
			  arq_in.close();
			  for(int i = 0; i < quantidade; i++) {
				string tempo = converterHora(jogadoresIntermediario[i].TempoEmSegundos);	
				cout<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
			  }
		  } else {
			cout << "ERRO: arquivo Intermediário.txt não foi aberto ou não existe" << endl;
		  }
	  } else if(salvar && opcaoArquivo == 'p') {
		  
			  /*arq_out.open("Personalizado.txt", ios::app);
			  string tempo = converterHora(duracao);		
			  arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;				
			  arq_out.close();*/
			  
			  
			  arq_in.open("Personalizado.txt");
			  if (arq_in.is_open()) {				  
				  while ((!arq_in.eof())) {  
					getline (arq_in, linha, '.');
					stringstream num(linha);
					num >> quantidade;
					getline(arq_in, linha, ' '); //add agora
					getline(arq_in, linha, ';');
					jogadoresPersonalizado[contador].nome = linha;
					getline (arq_in, linha, ':');
					getline (arq_in, linha, ' ');
					getline (arq_in, linha, ':');
					stringstream geek(linha);
					geek >> hora;
					hora = hora*3600;
					getline(arq_in, linha, ':');
					stringstream geeks(linha);
					geeks >> minuto;
					minuto = minuto*60;
					getline(arq_in, linha, '\n');
					stringstream geekss(linha);
					geekss>>segundo;
					jogadoresPersonalizado[contador].TempoEmSegundos = hora+minuto+segundo;
					contador++;	
					cout<<contador<<endl;		
					cout<<"Quantidade: "<<quantidade<<endl;
				
				}
			}
			arq_in.close();
				
			if(quantidade == 3) {
				for(int i = 0; i < quantidade; i++) {
					for(int j = i+1; j <= quantidade; j++) {	
						if(jogadoresPersonalizado[j].TempoEmSegundos < jogadoresPersonalizado[i].TempoEmSegundos ) {
							auxiliar = jogadoresPersonalizado[i];
							jogadoresPersonalizado[i] = jogadoresPersonalizado[j];
							jogadoresPersonalizado[j] = auxiliar;
						}
					}
				}
				
				if(jogador.TempoEmSegundos < jogadoresPersonalizado[2].TempoEmSegundos) {
					jogadoresPersonalizado[2] = jogador;
				}
				
				for(int i = 0; i < quantidade; i++) {
					for(int j = i+1; j < quantidade; j++) {	
						if(jogadoresPersonalizado[j].TempoEmSegundos < jogadoresPersonalizado[i].TempoEmSegundos ) {
							auxiliar = jogadoresPersonalizado[i];
							jogadoresPersonalizado[i] = jogadoresPersonalizado[j];
							jogadoresPersonalizado[j] = auxiliar;
						}
					}
				}
				
				
				for(int i = 0; i < 3; i++) {
					cout<<jogadoresPersonalizado[i].nome<<" "<<jogadoresPersonalizado[i].TempoEmSegundos<<endl;
				}
				
				arq_out.open("Personalizado.txt");
				for(int i = 0; i < contador-1; i++) {
					string tempo = converterHora(jogadoresPersonalizado[i].TempoEmSegundos);	
					arq_out<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
					cout<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
				}
				arq_out.close();
			} else if(quantidade == 0) {
				cout<<"Entrou 0"<<endl;
				arq_out.open("Personalizado.txt", ios::app);
				string tempo = converterHora(duracao);		
				arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;				
				arq_out.close();
			} else if(quantidade == 1) {
				if(jogador.TempoEmSegundos < jogadoresPersonalizado[0].TempoEmSegundos) {
					cout<<"Entrou 1"<<endl;
					Pessoa aux = jogadoresPersonalizado[0];
					jogadoresPersonalizado[0] = jogador;
					jogadoresPersonalizado[1] = aux;
					
					arq_out.open("Personalizado.txt");
					for(int i = 0; i < 2; i++) {
						string tempo = converterHora(jogadoresPersonalizado[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
					
				} else {
					jogadoresPersonalizado[1] = jogador;
					arq_out.open("Personalizado.txt");
					for(int i = 0; i < 2; i++) {
						string tempo = converterHora(jogadoresPersonalizado[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
				}
			} else if(quantidade == 2) {
				cout<<"Entrou 2"<<endl;
				jogadoresPersonalizado[2] = jogador;
				for(int i = 0; i < 3; i++) {
					for(int j = i+1; j < 3; j++) {	
						if(jogadoresPersonalizado[j].TempoEmSegundos < jogadoresPersonalizado[i].TempoEmSegundos ) {
							auxiliar = jogadoresPersonalizado[i];
							jogadoresPersonalizado[i] = jogadoresPersonalizado[j];
							jogadoresPersonalizado[j] = auxiliar;
						}
					}
					arq_out.open("Personalizado.txt");
					for(int i = 0; i < 3; i++) {
						string tempo = converterHora(jogadoresPersonalizado[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresPersonalizado[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
				}
			}
			
			/*if(jogador.TempoEmSegundos < jogadores[contador-1].TempoEmSegundos) {
				jogadores[contador] = jogador;
			}*/
			
			
			
			
			
			
			
			
			/*if (arq_out.is_open()) {
				string tempo = converterHora(duracao);		
				arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;
			}*/
	  } else if(salvar && opcaoArquivo == 'f') {
		  
			  /*arq_out.open("Personalizado.txt", ios::app);
			  string tempo = converterHora(duracao);		
			  arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;				
			  arq_out.close();*/
			  
			  
			  arq_in.open("Fácil.txt");
			  if (arq_in.is_open()) {			  
				  while ((!arq_in.eof())) {	
					getline (arq_in, linha, '.');
					stringstream num(linha);
					num >> quantidade;
					getline(arq_in, linha, ' '); //add agora
					getline(arq_in, linha, ';');
					jogadoresFacil[contador].nome = linha;
					getline (arq_in, linha, ':');
					getline (arq_in, linha, ' ');
					getline (arq_in, linha, ':');
					stringstream geek(linha);
					geek >> hora;
					hora = hora*3600;
					getline(arq_in, linha, ':');
					stringstream geeks(linha);
					geeks >> minuto;
					minuto = minuto*60;
					getline(arq_in, linha, '\n');
					stringstream geekss(linha);
					geekss>>segundo;
					jogadoresFacil[contador].TempoEmSegundos = hora+minuto+segundo;
					contador++;	
					cout<<contador<<endl;		
					cout<<"Quantidade: "<<quantidade<<endl;
				
				}
			}
			arq_in.close();
				
			if(quantidade == 3) {
				for(int i = 0; i < quantidade; i++) {
					for(int j = i+1; j <= quantidade; j++) {	
						if(jogadoresFacil[j].TempoEmSegundos < jogadoresFacil[i].TempoEmSegundos ) {
							auxiliar = jogadoresFacil[i];
							jogadoresFacil[i] = jogadoresFacil[j];
							jogadoresFacil[j] = auxiliar;
						}
					}
				}
				
				if(jogador.TempoEmSegundos < jogadoresFacil[2].TempoEmSegundos) {
					jogadoresFacil[2] = jogador;
				}
				
				for(int i = 0; i < quantidade; i++) {
					for(int j = i+1; j < quantidade; j++) {	
						if(jogadoresFacil[j].TempoEmSegundos < jogadoresFacil[i].TempoEmSegundos ) {
							auxiliar = jogadoresFacil[i];
							jogadoresFacil[i] = jogadoresFacil[j];
							jogadoresFacil[j] = auxiliar;
						}
					}
				}
				
				
				for(int i = 0; i < 3; i++) {
					cout<<jogadoresFacil[i].nome<<" "<<jogadoresFacil[i].TempoEmSegundos<<endl;
				}
				
				arq_out.open("Fácil.txt");
				for(int i = 0; i < contador-1; i++) {
					string tempo = converterHora(jogadoresFacil[i].TempoEmSegundos);	
					arq_out<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
					cout<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
				}
				arq_out.close();
			} else if(quantidade == 0) {
				cout<<"Entrou 0"<<endl;
				arq_out.open("Fácil.txt", ios::app);
				string tempo = converterHora(duracao);		
				arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;				
				arq_out.close();
			} else if(quantidade == 1) {
				if(jogador.TempoEmSegundos < jogadoresFacil[0].TempoEmSegundos) {
					cout<<"Entrou 1"<<endl;
					Pessoa aux = jogadoresFacil[0];
					jogadoresFacil[0] = jogador;
					jogadoresFacil[1] = aux;
					
					arq_out.open("Fácil.txt");
					for(int i = 0; i < 2; i++) {
						string tempo = converterHora(jogadoresFacil[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
					
				} else {
					jogadoresFacil[1] = jogador;
					arq_out.open("Fácil.txt");
					for(int i = 0; i < 2; i++) {
						string tempo = converterHora(jogadoresFacil[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
				}
			} else if(quantidade == 2) {
				cout<<"Entrou 2"<<endl;
				jogadoresFacil[2] = jogador;
				for(int i = 0; i < 3; i++) {
					for(int j = i+1; j < 3; j++) {	
						if(jogadoresFacil[j].TempoEmSegundos < jogadoresFacil[i].TempoEmSegundos ) {
							auxiliar = jogadoresFacil[i];
							jogadoresFacil[i] = jogadoresFacil[j];
							jogadoresFacil[j] = auxiliar;
						}
					}
					arq_out.open("Fácil.txt");
					for(int i = 0; i < 3; i++) {
						string tempo = converterHora(jogadoresFacil[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresFacil[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
				}
			}
			
			/*if(jogador.TempoEmSegundos < jogadores[contador-1].TempoEmSegundos) {
				jogadores[contador] = jogador;
			}*/
			
			
			
			
			
			
			
			
			/*if (arq_out.is_open()) {
				string tempo = converterHora(duracao);		
				arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;
			}*/
	  } else if(salvar && opcaoArquivo == 'i') {
		  
			  /*arq_out.open("Personalizado.txt", ios::app);
			  string tempo = converterHora(duracao);		
			  arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;				
			  arq_out.close();*/
			  
			  
			  arq_in.open("Intermediário.txt");
			  if (arq_in.is_open()) {				  
				  while ((!arq_in.eof())) {  
					getline (arq_in, linha, '.');
					stringstream num(linha);
					num >> quantidade;
					getline(arq_in, linha, ' '); //add agora
					getline(arq_in, linha, ';');
					jogadoresIntermediario[contador].nome = linha;
					getline (arq_in, linha, ':');
					getline (arq_in, linha, ' ');
					getline (arq_in, linha, ':');
					stringstream geek(linha);
					geek >> hora;
					hora = hora*3600;
					getline(arq_in, linha, ':');
					stringstream geeks(linha);
					geeks >> minuto;
					minuto = minuto*60;
					getline(arq_in, linha, '\n');
					stringstream geekss(linha);
					geekss>>segundo;
					jogadoresIntermediario[contador].TempoEmSegundos = hora+minuto+segundo;
					contador++;	
					cout<<contador<<endl;		
					cout<<"Quantidade: "<<quantidade<<endl;
				
				}
			}
			arq_in.close();
				
			if(quantidade == 3) {
				for(int i = 0; i < quantidade; i++) {
					for(int j = i+1; j <= quantidade; j++) {	
						if(jogadoresIntermediario[j].TempoEmSegundos < jogadoresIntermediario[i].TempoEmSegundos ) {
							auxiliar = jogadoresIntermediario[i];
							jogadoresIntermediario[i] = jogadoresIntermediario[j];
							jogadoresIntermediario[j] = auxiliar;
						}
					}
				}
				
				if(jogador.TempoEmSegundos < jogadoresIntermediario[2].TempoEmSegundos) {
					jogadoresIntermediario[2] = jogador;
				}
				
				for(int i = 0; i < quantidade; i++) {
					for(int j = i+1; j < quantidade; j++) {	
						if(jogadoresIntermediario[j].TempoEmSegundos < jogadoresIntermediario[i].TempoEmSegundos ) {
							auxiliar = jogadoresIntermediario[i];
							jogadoresIntermediario[i] = jogadoresIntermediario[j];
							jogadoresIntermediario[j] = auxiliar;
						}
					}
				}
				
				
				for(int i = 0; i < 3; i++) {
					cout<<jogadoresIntermediario[i].nome<<" "<<jogadoresIntermediario[i].TempoEmSegundos<<endl;
				}
				
				arq_out.open("Intermediário.txt");
				for(int i = 0; i < contador-1; i++) {
					string tempo = converterHora(jogadoresIntermediario[i].TempoEmSegundos);	
					arq_out<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
					cout<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
				}
				arq_out.close();
			} else if(quantidade == 0) {
				cout<<"Entrou 0"<<endl;
				arq_out.open("Intermediário.txt", ios::app);
				string tempo = converterHora(duracao);		
				arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;				
				arq_out.close();
			} else if(quantidade == 1) {
				if(jogador.TempoEmSegundos < jogadoresIntermediario[0].TempoEmSegundos) {
					cout<<"Entrou 1"<<endl;
					Pessoa aux = jogadoresIntermediario[0];
					jogadoresIntermediario[0] = jogador;
					jogadoresIntermediario[1] = aux;
					
					arq_out.open("Intermediário.txt");
					for(int i = 0; i < 2; i++) {
						string tempo = converterHora(jogadoresIntermediario[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
					
				} else {
					jogadoresIntermediario[1] = jogador;
					arq_out.open("Intermediário.txt");
					for(int i = 0; i < 2; i++) {
						string tempo = converterHora(jogadoresIntermediario[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
				}
			} else if(quantidade == 2) {
				cout<<"Entrou 2"<<endl;
				jogadoresIntermediario[2] = jogador;
				for(int i = 0; i < 3; i++) {
					for(int j = i+1; j < 3; j++) {	
						if(jogadoresIntermediario[j].TempoEmSegundos < jogadoresIntermediario[i].TempoEmSegundos ) {
							auxiliar = jogadoresIntermediario[i];
							jogadoresIntermediario[i] = jogadoresIntermediario[j];
							jogadoresIntermediario[j] = auxiliar;
						}
					}
					arq_out.open("Intermediário.txt");
					for(int i = 0; i < 3; i++) {
						string tempo = converterHora(jogadoresIntermediario[i].TempoEmSegundos);	
						arq_out<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
						cout<<i+1<<". "<<jogadoresIntermediario[i].nome<<"; Tempo: "<<tempo<<endl;
					}
					arq_out.close();
				}
			}
			
			/*if(jogador.TempoEmSegundos < jogadores[contador-1].TempoEmSegundos) {
				jogadores[contador] = jogador;
			}*/
			
			
			
			
			
			
			
			
			/*if (arq_out.is_open()) {
				string tempo = converterHora(duracao);		
				arq_out<<1<<". "<<jogador.nome<<"; Tempo: "<<tempo<<endl;
			}*/
	  }	  
 }

void converterSegundosinit(int hora, int minuto, int segundo) {
	segundosIniciais = (segundo + 60*minuto+3600*hora);
}

int main (){
	Pessoa jogador;
	
	fstream arquivo; 
	
	
    char op, op2, mina[MAX][MAX], minabomba[MAX][MAX], comando;
    int x, y, n, m, aux=0, aux2=0, aux3, numb;

    time_t rawtime;
	struct tm * timeinfo;

	int hora, minuto, segundo, contM=10;

    menu (op);
    cin>>op;
    cout<<"\n"<<endl;

    if (op =='1'){
		cout<<"Insira seu nome: "<<endl;
		cin.ignore();
		getline(cin, jogador.nome);
		
	    menu2(op2);
	    cin>>op2;
	    cout<<"\n"<<endl;
	    switch (op2){
	        case '1':
	            n=m=8;
	            numb = 10;

	            for (int i=0; i<n; i++){
		            for (int j=0; j<m; j++){
		                mina[i][j] = '.';
		            }
	            }

	            srand(time(NULL));
	            GeraBombas(minabomba, n, m, numb);
	            BombasVizinhas(minabomba, n, m);
	            imprimir(minabomba, n, m);
	            cout<<"\n"<<endl;

	            time (&rawtime);
	            timeinfo = localtime (&rawtime);
	            hora = timeinfo->tm_hour;
	            minuto = timeinfo->tm_min;
	            segundo = timeinfo->tm_sec;
	            converterSegundosinit(hora, minuto, segundo);

			    while(aux!=1) {
					
					Duracao();
					cout<<endl;
			        imprimir(mina, n, m);

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
			            	descobrir(minabomba, mina, x, y, n, m, aux2);
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

			        aux3 = (((n*m)-aux2)-numb); //equacao geral

					if (aux3 == 0) {
						jogador.TempoEmSegundos = Duracao();
						tratarArquivo(1, 0, jogador, 'f', jogador.TempoEmSegundos);
						cout<<" _____________________________"<<endl;
						cout<<"|                             |"<<endl;
						cout<<"|   PARABENS VOCE GANHOU!!!   |"<<endl;
						cout<<"|_____________________________|"<<endl;
						aux = 1;
					}
			    }
            break; // case1

	        case '2':
	            n=m=16;
	            numb = 40;

	            for (int i=0; i<n; i++){
		            for (int j=0; j<m; j++){
		                mina[i][j] = '.';
		            }
	            }

	            srand(time(NULL));
	            GeraBombas(minabomba, n, m, numb);
	            BombasVizinhas(minabomba, n, m);
	            imprimir(minabomba, n, m);
	            cout<<"\n"<<"\n"<<endl;

	            time (&rawtime);
	            timeinfo = localtime (&rawtime);
	            hora = timeinfo->tm_hour;
	            minuto = timeinfo->tm_min;
	            segundo = timeinfo->tm_sec;
	            converterSegundosinit(hora, minuto, segundo);

				while(aux!=1) {
					Duracao();

					cout<<endl;
			        imprimir(mina, n, m);

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
			            	descobrir(minabomba, mina, x, y, n, m, aux2);
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

			        aux3 = (((n*m)-aux2)-numb); //equacao geral

					if (aux3 == 0) {
						
						jogador.TempoEmSegundos = Duracao();
						tratarArquivo(1, 0, jogador, 'i', jogador.TempoEmSegundos);
						cout<<" _____________________________"<<endl;
						cout<<"|                             |"<<endl;
						cout<<"|   PARABENS VOCE GANHOU!!!   |"<<endl;
						cout<<"|_____________________________|"<<endl;
						cout<<"\n";
						aux = 1;
					}
		    	}
			break; //case2

	        case '3':
	            cout<<"Insira o tamanho da linha e da coluna (sendo o maximo 40 para ambos): ";
	            int a1, a2, a3;

	            do {
	            	cin>>a1;
				} while(a1 >= 40);
				n=a1;

	            do {
	            	cin>>a2;
				} while(a2 >= 40);
	            m=a2;

	            cout<<"Insira o numero de bombas: ";
	            do {
	            	cin>>a3;
				} while(a3 > ((n*m)-10));
	            numb = a3;

	            for (int i=0; i<n; i++){
		            for (int j=0; j<m; j++){
		                mina[i][j] = '.';
		            }
	            }

	            srand(time(NULL));
	            GeraBombas(minabomba, n, m, numb);
	            BombasVizinhas(minabomba, n, m);
	            imprimir(minabomba, n, m);
	            cout<<"\n"<<"\n"<<endl;
	            
	            
	            time (&rawtime);
	            timeinfo = localtime (&rawtime);
	            hora = timeinfo->tm_hour;
	            minuto = timeinfo->tm_min;
	            segundo = timeinfo->tm_sec;
	            converterSegundosinit(hora, minuto, segundo);

		        while(aux!=1) {
					Duracao();

					cout<<endl;
			        imprimir(mina, n, m);

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
			            	descobrir(minabomba, mina, x, y, n, m, aux2);
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

			        aux3 = (((n*m)-aux2)-numb); //equacao geral

					if (aux3 == 0) {
						jogador.TempoEmSegundos = Duracao();
						tratarArquivo(1, 0, jogador, 'p', jogador.TempoEmSegundos);
						cout<<" _____________________________"<<endl;
						cout<<"|                             |"<<endl;
						cout<<"|   PARABENS VOCE GANHOU!!!   |"<<endl;
						cout<<"|_____________________________|"<<endl;
						aux = 1;
					}
				}
	        break; //case3

			case '4':
				menu(op);
			break;
		} //fim do switch
    } //fim do if
    else if (op=='2'){
		tratarArquivo(0, 1, jogador, 't', Duracao());
    }
	else if (op=='3'){
	    exit(1);
	}
     return 0;
}
