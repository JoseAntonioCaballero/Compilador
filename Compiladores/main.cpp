#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;

    class cToken{
    protected:
        string nomToken;
        string lexema;

    public:

        void setNomToken(string nT){
            this -> nomToken = nT;

        }

        void setLexema(string lex = "123.34"){
            this ->lexema= lex;

        }

        string getNomToken(){
            return this -> nomToken;

        }

        string getLexema(){
            return this -> lexema;

        }


    };

    template <class T>
    class cTokenNum: public cToken{
            T valorNum;

        public:

            void setValor(T vN){
                this -> valorNum = vN;
            }

            T getValor(){
                return this -> valorNum;

            }

            T ConvierteToNum(){
                stringstream aux (this -> lexema);
                aux>>valorNum;
                return valorNum;
            }


    };

    class cAnalisisLexico{
        ifstream in;  //creación del fichero de lectura
        ofstream out; //creación de fichero de escritura
        ifstream palabrasReservadas;
        list<string> listaPalabras;
        vector<cToken> bufferToken;

        void (cAnalisisLexico::*fs[3])();


        char* archivoSalida;

public:
    cAnalisisLexico()
    {}

    cAnalisisLexico(char* s)
    {}


     bool esReservada(char *id){

    bool reservada = false;
 for(list<string>::iterator it=listaPalabras.begin();it!=listaPalabras.end();it++){
            if(strcmp(id,(*it).c_str())==0){
                reservada=true;
                break;

            }

        }

        return reservada;
    }

    cAnalisisLexico(char*s, const char*salida){
        in.open(s);
    try{

        if(in.fail())
            throw 1;
        cout<<"Exito al abrir el archivo"<<endl;
        string cad;

          while(!palabrasReservadas.eof()){
            palabrasReservadas>>cad;
            listaPalabras.push_back(cad);

        }

        out.open(salida);

       }catch (int i){
        if(i==1)
            cout<<"error al abrir el archivo para analizar"<<endl;
        else if(i==2)
            cout<<"error al abrir el archivo de palabras reservadas"<<endl;
        else
            cout<<"error no definido"<<endl;
                  }
        cout<<"Constructor dos";
                                       }


    void recuperaTokens(){
        string id;


        char c;

            while(!in.eof()){

                c=in.get();
                    if(c=='(')
                        out<<"TokPI"<<endl;
                    else if(c==';')
                        out<<"TokPyK"<<endl;
                    else if(c=='>')
                        out<<"TokMayor"<<endl;
                    else if(c=='<')
                        out<<"TokMenor"<<endl;

                    else if(isalpha(c)|| c== '_'){
                    //guardar c
                     id=c;
                        c=in.get();
                        while(isalnum(c) || c== '_'){
                     //guardar
                     id+=c;
                    c=in.get();
                        }

                        if(!esReservada((char*)id.c_str()))
                            out<<"(TokID,"<<id<<")";
                        else
                             out<<"(TokPR,"<<id<<")";
                    out<<"(TokenID,"<<id<<")";

                        in.unget(); //Permite regresar algo que no es un digito o letra.

                  } else if(c=='/'){
                        c=in.get();
                            if(c=='/'){
                            c= in.get();
                            while(c!='\n')
                                c=in.get();
                                    in.unget();
                                    out<<"TokComentario Corto";


                                       } else if(isalpha(c)){
                                            out<<"TokDiv";
                                            in.unget();

                                       }else if(c=='*'){ //comentario largo
                                            char d;

                                        do{
                                            while(in.get()!='*')
                                                in.unget();
											
												while(in.get()=='*')
													in.unget();
												if((d=in.get())=='/'){
													out<<"TokComentario largo";
													in.unget();
                                                    break;
												}
											

                                        }while(d!='/');

                                       }

                                    }

                                    else if(c=='+' || c== '-' ||  isdigit(c)){
                                        string num;
                                        num=c;
                                        c=in.get();
                                        if(c=='+')
                                            out<<"(TokIncre, ++)";
                                        else if(c=='-')
                                            out<<"(TokDecre, --)";
                                        else if(c=='=')
                                            out<<"(TokIncre, +=)";
                                        else if (isalpha(c) && toupper(c)!='E')
                                            out<<"(TokOpAtm,"<<c;
                                        else{
                                            while(isdigit(c)){
                                                num+=c;
                                                c=in.get();
                                            }

                                            if(c=='.'){
                                                num+=c;
                                                c=in.get();
                                                 while(isdigit(c)){
                                                num+=c;
                                                c=in.get();
                                            }

                                            if(toupper(c)!='E')
                                            out<<"TokFloat"<<num;
                                            else{
                                                parteFinalAutomata:
                                                num+=c;
                                                c=in.get();
                                            if(c=='+' || c== '-' ||  isdigit(c)) {
                                                num+=c;
                                                c=in.get();
                                                while(isdigit(c)){
                                                    num+=c;
                                                    c=in.get();
                                               }

                                               out<<"TokNumExp"<<num;

                                            }
                                            else
                                                out<<"Error en el formaro exponencial";
                                            }


                                        }

                                         else if(toupper(c)=='E')
                                        goto parteFinalAutomata;

                                        else
                                        out<<"TokInt,"<<num<<endl;
                                    in.unget();

                                        }

                                    }


                    else
                    out<<c;



    }

    };


    class cAnalisisSintactico{


    };

    };
    int main(int nArgs, char ** args)
{

    const char * sal = "miSalida.txt";

    if(nArgs == 3)
        sal= args[2];

    cAnalisisLexico analisis1(args[1], sal);
    analisis1.recuperaTokens();

    return 0;
}
