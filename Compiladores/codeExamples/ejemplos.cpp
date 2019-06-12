#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;

bool someFunction(int parameter, float otherParameter);//declaración de función para poder utilizarla en otro lado del codigo
class someClass{//declaracion simple de una clase
};
class otherClass{//declaración de clase con sus elememtos
	public://sección de metodos publicos de la clase como los constructores
	int elemento1=0;//primer elemento de la clase
	bool elemento2=false;
	
	otherClass(){//constructor de la clase o init
		
	}
	
	otherClass(int elemento1, bool elemento2){//Constructor de la misma clase pero con los valores para asignar
		this->elemento1=elemento1;
		this->elemento2=elemento2;
	}
	
	void print(){
		printElements();
	}
	
	private://sección privada
	void printElements(){//función privada de impresion de atributos
		cout<<elemento1<<endl;
		cout<<elemento2<<elemento2<<endl;
	}
};

class childClass:otherClass{//declaracion de clase hija con herencia de other class
	const char * chain = "some string";
	
	public:
	childClass(const char * chain,int elemento1,bool elemento2){//constructor de la clase hija que utilizara el constructor padre
		this -> chain=chain;
		//otherClass(elemento1,elemento2);//no funciona pues crea otra clase other
		this -> elemento1=elemento1;//asignando a los atributos que fueron heredados esto funciona por la herencia
		this -> elemento2=elemento2;
	}
	
	void getAll(){
		printAll();
	}
	
	private:
	void printAll(){
		cout<<elemento1<<endl;
		cout<<elemento2<<elemento2<<endl;
		cout<<chain<<endl;
	}
	
};

int main(int nArgs, char ** args){
	someFunction(1,1.4);//llamada a una función
	someClass x();//creación de un objeto someclass llamado x
	otherClass chafa();//creacion de objeto llamado chafa de la clase otherClass utilizando un cnstructor que no asigna nada a sus atributos
	otherClass y(5,true);//Creacion de objeto de la clase otherclass llamado y utilizando ademas su constructor para asignar los atributos en la clase
	//y.printElements();//esta linea da error porque al ser privada solo la misma clase tiene acceso a esta
	y.print();//utilizamos esta que hicimos publica solo para ejemplo
	cout<<"<<<<<<<<<<<<<<"<<endl;//linea para mostrar diferencia
	childClass q("hola mundo",15,false);//creación de la clase hija llamada q con uso del constructor
	q.getAll();//impresion de elementos notese que este metodo es solo de la clase hija ;)
return 0;	
}

bool someFunction(int parameter, float otherParameter){//función declarada previamente con sus instrucciones dentro
	
return true;
} 




