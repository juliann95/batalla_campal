/*
tp 1 de algoritmos 2
-------------------REGLAS----------
-------------------------------------
	-tablero de 10*10
	-2 jugadores
	-3 soldados por cada jugador
	-un soldado ataca una celda y queda unitilizada o
	mata si un soldado esta en ella.
	-luego opta por moverce en cualquier direccion, no
	no puede moverce a una celda inactiva
	-celdas: '' vacio
			 X 	inactiva
			1,2 jugador(soldado)

*/

#include <iostream>
#include <fstream>
#include<string.h>

using namespace std;

const int SOLD_INIC = 3;
const int ANCHO = 10;
const int ALTO = 10;
const int MAX_MOVIMIENTO = 49;
const int MAX_ATAQUES = 98;
const int DIMENCION = 2;

	
struct Player {
	string nombre;
	string nombre_archivo;
	char caracter;
	int soldados;
	int posicion[SOLD_INIC][DIMENCION];//son 3 dos elementos para posicicionarlos
	//(combiene hacer una estructura aparte?)

};

//--------------------------------------------------------------- 
void escribirArchivo(Player *jugador,char dato){  
	const void* dic_dato = &dato;
	FILE *archivo_escritura= fopen((*jugador).nombre_archivo.c_str(),"a");
	fseek (archivo_escritura, ftell (archivo_escritura ), SEEK_END);
	fwrite(dic_dato, sizeof(dato),sizeof(dato),archivo_escritura);
	fclose(archivo_escritura);
} 

void mostraTablero(char tablero[ANCHO][ALTO], Player *jugador){
	for (int i = 0;i < 10;i++){
		cout<<endl;
		escribirArchivo(jugador,10);
		for (int e = 0; e < 10;e++){
			//comparo las posiciones de los soldados
			if (((*jugador).posicion[0][0]-1 == i && (*jugador).posicion[0][1]-1 == e) || ((*jugador).posicion[1][0]-1 == i && (*jugador).posicion[1][1]-1 == e )|| ((*jugador).posicion[2][0]-1 == i && (*jugador).posicion[2][1]-1 == e)){
				cout<<(*jugador).caracter<<" ";
				escribirArchivo(jugador,(*jugador).caracter);
			}
			else if (tablero[i][e] != 88){
				cout<<tablero[i][e]<<" ";
				escribirArchivo(jugador,34);

			}
			else if(tablero[i][e] == 88){
			cout<<"X ";
			escribirArchivo(jugador,88);
			}
		}
	}
	escribirArchivo(jugador,10);
}

//--------------------------------------------------------------- 

void comparo(Player *jugador1,Player *jugador2){
	for (int i = 0; i < SOLD_INIC; ++i){
		for (int e = 0; e < SOLD_INIC; ++e){
			if((*jugador1).posicion[i][0] == (*jugador2).posicion[e][0] && (*jugador1).posicion[i][1] == (*jugador2).posicion[e][1] && (*jugador1).posicion[i][0] != -1){
				(*jugador1).posicion[i][0] = (*jugador2).posicion[e][0] = (*jugador1).posicion[i][1] = (*jugador2).posicion[e][1] = -1;
				(*jugador1).soldados -= 1;
				(*jugador2).soldados -= 1;
			}}}}

//---------------------------------------------------------------
void atacarCelda(int pos_atacada[DIMENCION],char tablero[ANCHO][ALTO]){
	int x,y;
	cout <<"\n Atacar celda en x: "<<endl;
	cin>>x;
	cout <<"\n Atacar celda en y: "<<endl;
	cin>>y;
	while(tablero[y-1][x-1] == 88){
		cout<<"\n\ncelda inhabilitada. ingrese otra ubicacion\n"<<endl;
		cin>>x;
		cin>>y;
	}
	pos_atacada[0] = y;
	pos_atacada[1] = x;
	tablero[y-1][x-1] = 88;
}
//---------------------------------------------------------------

void borroSold(char tablero[ALTO][ANCHO],int pos_atacada[DIMENCION],Player *jugador1,Player *jugador2){
	for(int i =0; i < SOLD_INIC;i++){
		if((pos_atacada[0] == (*jugador1).posicion[i][0] && pos_atacada[1] == (*jugador1).posicion[i][1])){//|| (tablero[soldados[i][0]-1][soldados[i][1]-1]==88)
			(*jugador1).posicion[i][0] = -1;
			(*jugador1).posicion[i][1] = -1;
			(*jugador1).soldados -= 1;
		}
		if((pos_atacada[0] == (*jugador2).posicion[i][0] && pos_atacada[1] == (*jugador2).posicion[i][1])){//|| tablero[soldados1[i][0]-1][soldados1[i][1]-1]==88
			(*jugador2).posicion[i][0] = -1;
			(*jugador2).posicion[i][1] = -1;
			(*jugador2).soldados -= 1;
		}}}


//---------------------------------------------------------------

void moverSoldado(char tablero[ALTO][ANCHO],Player *jugador){
	int x, y, soldados;
	do{
		for(int i =0;i<SOLD_INIC;i++){
			if((*jugador).posicion[i][0]!= -1){
			cout<<"\n soldado "<<i+1<<"en x,y:"<<(*jugador).posicion[i][0]<<","<<(*jugador).posicion[i][1] <<endl;
			}
		}
		cout<<"\n\n numero de soldado a mover"<<endl;
		cin>>soldados;
		while((*jugador).posicion[soldados-1][0] == -1){
			cout<<"\n\n soldado muerto"<<endl;
			cout<<"\n numero de soldado a mover"<<endl;
			cin>>soldados;
		}
		cout<<"mover soldados en x"<<endl;
		cin>>x;
		cout<<"mover soldados en y"<<endl;
		cin>>y;
		if (tablero[y-1][x-1] == 88 ){
			cout<<"\ncelda inhabilitada"<<endl;
		}
	}while(tablero[y-1][x-1] == 88 );
	(*jugador).posicion[soldados-1][0] = y;
	(*jugador).posicion[soldados-1][1] = x;
}
//---------------------------------------------------------------

void nombreJugador( Player *jugador){
	 string escribir_nombre;
	 cout <<"ingrese el nombre del jugador"<<endl;
	 cin >> escribir_nombre;
	jugador-> nombre= escribir_nombre;
}
//---------------------------------------------------------------

void posicionInicial(Player *jugador){
	for (int i=0;i <SOLD_INIC;i++){
		int x,y;
		cout<<"ingresela posicion del soldados "<< i+1<<(*jugador).nombre <<endl;
		cout<<"posicion x: "<<endl;
		cin>>x;
		cout<<"posicion y: "<<endl;
		cin>>y;
		jugador-> posicion[i][0] = y;
		jugador-> posicion[i][1] = x;
	}
}
//---------------------------------------------------------------

void turno(Player *jugador,Player *contrincante,char tablero[ALTO][ANCHO]){
	mostraTablero(tablero,jugador);
	int atacarPosicion[DIMENCION]; 
	cout<<"\nsoldados de "<<(*jugador).nombre<<" "<<(*jugador).soldados<<endl;
	cout<<"\nturno de "<<(*jugador).nombre<<endl;
	atacarCelda(atacarPosicion,tablero);
	borroSold(tablero,atacarPosicion,jugador,contrincante);
	
	if ((*jugador).soldados > 0 && (*contrincante).soldados > 0){
		moverSoldado(tablero,jugador);
		comparo(jugador,contrincante);
		cout<<"\nsoldados de "<<(*jugador).nombre<<" "<<(*jugador).soldados<<endl;
		mostraTablero(tablero,jugador);
		cout<<"\n"<<endl;}
}
//--------------------------------------------------------------- 

void ciclo(char tablero[][ALTO],Player *jugador1,Player *jugador2){
	while((*jugador1).soldados > 0 && (*jugador2).soldados > 0){
		
		if ((*jugador1).soldados > 0 && (*jugador2).soldados > 0){
			turno(jugador1,jugador2,tablero);
		}
		if((*jugador1).soldados > 0 && (*jugador2).soldados > 0){
			turno(jugador2,jugador1,tablero);
		}
	}
}
//---------------------------------------------------------------
void iniciarTablero(char tablero[ANCHO][ALTO]){
	for (int i = 0;i < 10;i++){
		for (int e = 0; e < 10;e++){
			tablero[i][e] = 34;
		}
	}
}
//---------------------------------------------------------------
void iniciarArchivo(Player *jugador1){
	ofstream archivo;
	archivo.open((*jugador1).nombre_archivo.c_str());
	archivo.close();
}
//---------------------------------------------------------------
void inicializarStruc(Player *jugador1,Player *jugador2){

	jugador1->soldados = SOLD_INIC;
 	jugador2->soldados = SOLD_INIC;
 	jugador1->caracter = 49;
 	jugador2->caracter = 50;
	jugador1->nombre_archivo ="jugador_1.txt";
	jugador2->nombre_archivo ="jugador_2.txt";
	iniciarArchivo(jugador1);
	iniciarArchivo(jugador2);

	nombreJugador(jugador1);
	nombreJugador(jugador2);
	posicionInicial(jugador1);
	posicionInicial(jugador2);
	comparo(jugador1,jugador2);
}
int main(){
	char tablero[ANCHO][ALTO];
	iniciarTablero(tablero);

	Player *player1 =  new Player;
	Player *player2 =  new Player;
 	inicializarStruc(player1,player2);
	comparo(player1,player2);//sirve para cuando se mueve

	ciclo(tablero,player1,player2);

	cout<<"fin del juego";
	delete player1;
	delete player2;
	return 0;
}
