#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;
class AnalisisLexico{
	public:
	ifstream in;
	ofstream out;
	ifstream palabrasReservadas;
	list<string> listaPalabras;
	
	bool esReservada(char *id){//funcion es reservada busca en el arcchivo de palabras reservadas
		bool reservada = false;
		for(list<string>::iterator it=listaPalabras.begin();it!=listaPalabras.end();it++){
			if(strcmp(id,(*it).c_str())==0){
                reservada=true;
                break;
            }
        }
		return reservada;
    }
    
    AnalisisLexico(char * entrada,char * salida){//constructor para inicializar la clase
		getPalabrasReservadas();
		
	}
	
	private:
	void getPalabrasReservadas(){//toma las palabras reservadas del archivo si es que existe.
		palabrasReservadas.open("palabrasReservadas.txt");
		try{
			if (palabrasReservadas.fail()){
				throw 1;
			}else{
				cout<<"exito al abrir el archivo plabras reservadas"<<endl;
				string cadena;
				while(!palabrasReservadas.eof()){
					palabrasReservadas>>cadena;
					listaPalabras.push_back(cadena);
				}
			}
		}catch(int error){
			if (error==1){
				cout<<"Error al abrir el archivo palabras reservadas"<<endl;
			}else{
				cout<<"ocurrio un error inesperado al querer abrir palabras reservadas."<<endl;
			}
		}
	}
    
};
int main(int nArgs, char ** args){
	
	return 0;	
}
