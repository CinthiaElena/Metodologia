//                                        Proyecto Final
//Hecho por: Alexis Garcia Talamantes, Cinthia Elena Hernandez, Brandon Gustavo Hernandez 

#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
using namespace std;

class Solucion{
	//Datos de la solución
	int solucion[10], N;
	int pesoSolucion, valorSolucion;
	
	//Datos del problema
	int valores[10];
	int pesos[10];
	int pesoMaximo;
	
	
	public:
		void generaSolucion();
		void asignaN(int n);
		void imprimeSolucion();
		void asignaValores(int v[]);
		void asignaPesos(int p[]);
		void asignaPesoMaximo(int pm);
		void evaluarSolucion(); 
		int recuperaValorSolucion();
		
		void asignaArticulo(int indice, int valor);
		int recuperaArticulo(int indice); 
		int esFactible(); 
		int sonIguales(Solucion s); 
		int getvalorSolucion();
	
};

int Solucion::recuperaValorSolucion(){
	return valorSolucion;
}

void Solucion::asignaN(int n){
	N = n;
}

void Solucion::asignaArticulo(int indice, int valor){
	solucion[indice] = valor;
}

int Solucion::recuperaArticulo(int indice){
	return solucion[indice];
}

int Solucion::sonIguales(Solucion s){
	for (int i= 0; i<N; i++){
		if (s.recuperaArticulo(i) != solucion[i])
			return 0; //falso, son diferentes
	}
	return 1; //verdadero, son iguales
}

void Solucion::evaluarSolucion(){
	valorSolucion = 0, pesoSolucion = 0;
	
	for (int i=0; i < N; i++){
		valorSolucion += solucion[i] * valores[i];
		pesoSolucion += solucion[i] * pesos[i];	
	}
}

int Solucion::esFactible(){
	if (pesoSolucion <= pesoMaximo){
		cout<<"Es factible" << endl;
		return 1; //verdadero, es factible, la solucion no rebasa el peso maximo permitido
	}
	else{
		cout<<"NO es factible" << endl;		
		return 0; //falso, NO es factible, rebasa el peso maximo
	}
}

void Solucion::imprimeSolucion(){
	cout << "Solucion " <<endl;
	for (int i=0; i < N; i++){
		cout << solucion[i] << " ";
	}
	cout << endl;
	cout << "Valor de la solucion: " << valorSolucion << endl;
	cout << "Peso de la solucion: " << pesoSolucion << endl;
}

void Solucion::asignaValores(int v[]){
	for (int i=0; i < N; i++){
		valores[i] = v[i];
	}
}

void Solucion::asignaPesos(int p[]){
	for (int i=0; i < N; i++){
		pesos[i] = p[i];
	}
}

void Solucion::asignaPesoMaximo(int pm){
	pesoMaximo = pm;
}


void Solucion::generaSolucion(){
	int num;

	for (int i=0; i < N; i++){
		num=rand()%2;
		solucion[i] = num;
	}
}

int Solucion::getvalorSolucion(){
	return valorSolucion;
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//Clase Operadores Geneticos
class operadoresGeneticos{
	public:
		void cruza(Solucion p1, Solucion p2, Solucion &h1, Solucion &h2);
		void muta(Solucion &h);
};




//Funcion Cruza
void operadoresGeneticos::cruza(Solucion p1, Solucion p2, Solucion &h1, Solucion &h2){
//Generar un número aleatorio entre 1 y 9.
	int random,art;
	random=(rand()%8)+1;


//Primera parte
	for(int i=0;i<=random-1;i++){
		
		//se recupera el digito del vector
		cout<<p1.recuperaArticulo(i);
		//se le asigna el digio a art
		art=p1.recuperaArticulo(i);
		//se isnerta el digito en el hijo (solo la parte izqueirda)
		h1.asignaArticulo(i,art);
		
		art=p2.recuperaArticulo(i);
		h2.asignaArticulo(i,art);
		
	}
	
	
//segunda parte
	for(int i=random;i<=9;i++){
		
		cout<<p2.recuperaArticulo(i);
		art=p2.recuperaArticulo(i);
		h1.asignaArticulo(i,art);
		
		art=p1.recuperaArticulo(i);
		h2.asignaArticulo(i,art);
		
	}
	
} //Termina la funcion cruza


//Funcion muta - Paso 9. 
void operadoresGeneticos::muta(Solucion &h){
//Generar un número aleatorio entre 0 y 9.
	int random,art;
	random=(rand()%8)+1;
	
//Usar las funciones recuperaArticulo y asignaArticulo	
	art=h.recuperaArticulo(random);
	h.asignaArticulo(random,art); 
	
	if(art==1){
		h.asignaArticulo(random, 0);
	}
	else{
		h.asignaArticulo(random, 1);
	}
	
}//Termina la funcion muta


int main(){
	srand(time(0));	
	int factible, iguales,f1,f2;
	
	int valores[] = {19, 45, 32, 18, 6, 25, 80, 7, 52, 22};
	int pesos[] = {1, 3, 10, 9, 10, 32, 23, 5, 15, 7};
	
	int valor,valormayor=0;

	//PADRE 1	
	Solucion p1;
	p1.asignaN(10);
	p1.asignaPesoMaximo(60);
	p1.asignaPesos(pesos);
	p1.asignaValores(valores);

	do{
		p1.generaSolucion();
		p1.evaluarSolucion();

		factible = p1.esFactible();
	}
	while(factible!=1);

	//PADRE 2
	Solucion p2;
	p2.asignaN(10);
	p2.asignaPesoMaximo(60);
	p2.asignaPesos(pesos);
	p2.asignaValores(valores);

	
	do{
		p2.generaSolucion();
		p2.evaluarSolucion();
		factible = p2.esFactible();
		iguales = p2.sonIguales(p1);
	}
	while(factible==0 || iguales==1);
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//SEGUNDA PARTE DEL ALGORITMO - PROYECTO FINAL
	
	system("cls");
	
	operadoresGeneticos o;  //Se crea un objeto de la clase operadoresGeneticos
	Solucion h1, h2;
	
	//Iniciar variables de h1 y h2
	h1.asignaN(10);
	h1.asignaPesoMaximo(60);
	h1.asignaPesos(pesos);
	h1.asignaValores(valores);
	
	
	h2.asignaN(10);
	h2.asignaPesoMaximo(60);
	h2.asignaPesos(pesos);
	h2.asignaValores(valores);
		
	o.cruza(p1, p2, h1, h2); //Paso 8.- Esta función invoca la cruza para crear h1 y h2.

//HIJO 1 .- Antes de la muta
	cout<<"Hijo 1: "<<endl;
	h2.evaluarSolucion();
	h2.imprimeSolucion();

//HIJO 2 .- Antes de la muta 
	cout<<"Hijo 2: "<<endl;
	h2.evaluarSolucion();
	h2.imprimeSolucion();


	system("cls");
	
//Imprimir valores de padres e hijos factibles. 
	cout<<"---------------------------------------------------------------"<<endl;
		cout<<"Padre 1"<<endl<<endl;
	p1.imprimeSolucion();
	p1.esFactible();
		
		
	cout<<"---------------------------------------------------------------"<<endl;
	cout<<"Padre 2"<<endl<<endl;
	p2.imprimeSolucion();
	p2.esFactible();
	
	
	cout<<"---------------------------------------------------------------"<<endl;
	
//Paso 10 y 11
//Evaluar hijos y verificar si son factibles   
	cout<<endl;                                  
	cout<<"Hijo 1 despues de muta" << endl;
	cout<<endl; 
	o.muta(h1);	
	h1.evaluarSolucion();
	f1=h1.esFactible();
	
	if(f1==1){
		  
	h1.imprimeSolucion();

			
	}

	cout<<"---------------------------------------------------------------"<<endl;
	
	cout<<endl;                                  
	cout<<"Hijo 2 despues de muta" << endl;
	cout<<endl; 
	o.muta(h2);
	h2.evaluarSolucion();
	f2=h2.esFactible();
	
	if(f2==1){
		
		h2.imprimeSolucion();
	
	}
	cout<<"---------------------------------------------------------------"<<endl;
	

//Paso 13. 
//Comparar a los hijos que resultaron factibles con los padres para determinar cuál es la mejor solución

	if(p1.getvalorSolucion()>valormayor){
		valormayor=p1.getvalorSolucion();
	}
	if(p2.getvalorSolucion()>valormayor){
		valormayor=p2.getvalorSolucion();
	}
	if(h1.getvalorSolucion()>valormayor and f1==1){
		valormayor=h1.getvalorSolucion();
	}
	if(h2.getvalorSolucion()>valormayor and f2==1){
		valormayor=h2.getvalorSolucion();
	}
	
	
	if(valormayor==p1.getvalorSolucion()){
		cout<<"El padre 1 es la mejor solucion";
	}
	if(valormayor==p2.getvalorSolucion()){
		cout<<"El padre 2 es la mejor solucion";
	}
	if(valormayor==h1.getvalorSolucion()){
		cout<<"El hijo 1 es la mejor solucion";
	}
	if(valormayor==h2.getvalorSolucion()){
		cout<<"El hijo 2 es la mejor solucion";
	}
	
	
}
