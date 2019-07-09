#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "analizadorSintactico.h"
#include "cToken.h"

using namespace std;


class cAnalisisLexico
{
    ifstream in;//conducto que me permite comunicarme con el archivo
    ofstream out;
    //void (cAnalisisLexico::*fs[5])();
    vector<cToken*> bufferToken;
    char c;
    string id;
    typedef void(cAnalisisLexico::*punteroFuncionToken)();
    map<char,punteroFuncionToken> tipoToken;
    public:
    cAnalisisLexico()
    {

    }

    cAnalisisLexico(char* s, const char* salida)
    {
        in.open(s);
        try
        {
            if(in.fail())
                throw 1;
            cout<<"Exito al abrir el archivo"<<endl;
            string cad;


            out.open(salida);
        }
        catch(int i)
        {
            if(i==1)
                cout<<"Error al abrir el archivo para analizar"<<endl;
            else
                cout<<"Error no definido"<<endl;
        }
    }
    vector<cToken*> getTokens()
    {
        return this->bufferToken;
    }
    void TokenAssignTiny()
    {
        c=in.get();
        if(c=='='){
            out<<"TokenAssignTiny";
            bufferToken.push_back(new cToken("TokenAssignTiny",":="));
        }
    }
    void TokenPI()
    {
        out<<"TokenPI";
        bufferToken.push_back(new cToken("TokenPI","("));
    }
    void TokenPD()
    {
        out<<"TokenPD";
        bufferToken.push_back(new cToken("TokenPD",")"));
    }
    void TokenPyC()
    {
        out<<"TokenPyC";
        bufferToken.push_back(new cToken("TokenPyC",";"));
    }
    void TokenMenor()
    {
        out<<"TokenMenor";
        bufferToken.push_back(new cToken("TokenMenor","<"));
    }
    void TokenMayor()
    {
        out<<"TokenMayor";
        bufferToken.push_back(new cToken("TokenMayor",">"));
    }
    void TokenCorIzq()
    {
        out<<"Token[[";
        bufferToken.push_back(new cToken("TokenCorIzq","["));
    }
    void TokenCorDer()
    {
        out<<"Token]]";
        bufferToken.push_back(new cToken("TokenCorDer","]"));
    }
    void TokenLlaveI()
    {
        out<<"(Token,{)";
        bufferToken.push_back(new cToken("TokenLlaveI","{"));
    }
    void TokenLlaveD()
    {
        out<<"(Token,})";
        bufferToken.push_back(new cToken("TokenLlaveD","}"));
    }
    void TokenIgual()
    {
        out<<"(Token,=)";
        bufferToken.push_back(new cToken("TokenIgual","="));
    }
    void TokenComa()
    {
        out<<"(Token,,)";
        bufferToken.push_back(new cToken("TokenComa",","));
    }
    void TokenAsterisco()
    {
        out<<"Token*";
        bufferToken.push_back(new cToken("TokenAsterisco","*"));
    }
    void TokenComilla()
    {
        id="";
        //id=c;
        c=in.get();
        while(c!='"')
        {
            id+=c;
            c=in.get();
        }
        out<<"(TokenCadena,"<<id<<")";
        bufferToken.push_back(new cToken("TokenCadena",id));
        //in.unget();
    }
    void TokenID()
    {
        string id;
        id=c;
        c=in.get();
        while(isalnum(c)||c=='_')
        {
            id+=c;
            c=in.get();
        }
        if(esReservada(id)){
            out<<"(TokenReser,"<<id<<")";
            bufferToken.push_back(new cToken("TokenReser",id));
        }
        else{
            out<<"(TokenID,"<<id<<")";
            bufferToken.push_back(new cToken("TokenID",id));
		}
        in.unget();
    }
    void TokenComentario()
    {
        c=in.get();
        if(c=='/')
        {
            while(c!='\n')
                c=in.get();
            in.unget();
            out<<"TokenComentarioCorto";
        }
        else if(isalpha(c))
        {
            out<<"TokDiv";
            bufferToken.push_back(new cToken("TokenDiv","/"));
            in.unget();
        }
        else if(c=='*')
        {
            c=in.get();
            while(c!='/')
            {
                while(c!='*')
                {
                    c=in.get();
                    if(in.eof())
                    {
                        out<<"Error en ";
                        break;
                    }
                }
            if(in.eof())
            break;
            c=in.get();

            }
            if(!in.eof())
                in.unget();

            out<<"TokenComentarioLargo";
        }
    }
    void TokenNumero()
    {
        string num;
                    num=c;
                    c=in.get();
                    if(c=='+'){
                        out<<"(TokInc,++)";
                        bufferToken.push_back(new cToken("TokenInc","++"));
                    }
                    else if(c=='-'){
                        out<<"(TokDec,--)";
                        bufferToken.push_back(new cToken("TokenDec","--"));
                    }
                    else if(c=='='){
                        out<<"(TokInc,+=)";
                        bufferToken.push_back(new cToken("TokenInc","+="));
                    }
                    else if(isalpha(c)&&toupper(c)!='E'){
                        out<<"(TokOpAt,"<<c<<")";
                        //bufferToken.push_back(new cToken("TokenOpAt",string(c)));
                    }
                    else
                    {
                        while(isdigit(c))
                        {

                            num+=c;
                            c=in.get();
                        }
                        if(c=='.')
                        {
                            num+=c;
                            c=in.get();
                            while(isdigit(c))
                            {
                                num+=c;
                                c=in.get();
                            }
                            if(toupper(c)!='E'){
                                out<<"(TokFloat,"<<num<<")";
                                bufferToken.push_back(new cTokenNum<float>("TokenFloat",num));
                            }

                            else //if(toupper(c)=='E')
                            {
                                parteFinalAutomata:
                                num+=c;
                                c=in.get();
                                if(c=='+'||c=='-'||isdigit(c))
                                {
                                    num+=c;
                                    c=in.get();
                                    while(isdigit(c))
                                    {
                                        num+=c;
                                        c=in.get();
                                    }
                                    out<<"(TokNumExp,"<<num<<")";
                                    bufferToken.push_back(new cTokenNum<double>("TokenNumExp",num));
                                }
                                else
                                {
                                    out<<"Error en formato exponencial";
                                }
                            }
                        }
                        else if(toupper(c)=='E')
                            goto parteFinalAutomata;
                        else{
                            out<<"(TokInt,"<<num<<")";
                            bufferToken.push_back(new cTokenNum<int>("TokenInt",num));
                        }
                        in.unget();
                    }
    }
    void TokenGato()
    {
        out<<"Tok#";
        c=in.get();
        id="";
        while(c!='<')
        {
            id+=c;
            c=in.get();
        }
        out<<"(TokReser,"<<id<<")"<<c;
        bufferToken.push_back(new cToken("TokenReser",id));
        id="";
        c=in.get();
        if(c!=32)
        {
        while(c!='>')
        {
            id+=c;
            c=in.get();
        }
            out<<"(TokLibreria,"<<id<<")"<<c;
            bufferToken.push_back(new cToken("TokenLibreria",id));
        }
        else
            out<<"(Error declaracion de libreria)";
    }
    void recuperaTokens()
    {
        tipoToken['(']=&cAnalisisLexico::TokenPI;
        tipoToken[')']=&cAnalisisLexico::TokenPD;
        tipoToken[';']=&cAnalisisLexico::TokenPyC;
        tipoToken['<']=&cAnalisisLexico::TokenMenor;
        tipoToken['>']=&cAnalisisLexico::TokenMayor;
        tipoToken['[']=&cAnalisisLexico::TokenCorIzq;
        tipoToken[']']=&cAnalisisLexico::TokenCorDer;
        tipoToken['{']=&cAnalisisLexico::TokenLlaveI;
        tipoToken['}']=&cAnalisisLexico::TokenLlaveD;
        tipoToken['=']=&cAnalisisLexico::TokenIgual;
        tipoToken['_']=&cAnalisisLexico::TokenID;
        tipoToken[',']=&cAnalisisLexico::TokenComa;
        tipoToken['"']=&cAnalisisLexico::TokenComilla;
        tipoToken['*']=&cAnalisisLexico::TokenAsterisco;
        for(int i=97;i<=122;i++)
            tipoToken[(char)i]=&cAnalisisLexico::TokenID;
        for(int i=65;i<=90;i++)
            tipoToken[(char)i]=&cAnalisisLexico::TokenID;
        tipoToken['/']=&cAnalisisLexico::TokenComentario;
        tipoToken['+']=&cAnalisisLexico::TokenNumero;
        tipoToken['-']=tipoToken['+'];
         for(int i=48;i<=57;i++)
            tipoToken[(char)i]=tipoToken['+'];
        tipoToken['#']=&cAnalisisLexico::TokenGato;
        tipoToken[':']=&cAnalisisLexico::TokenAssignTiny;
         map<char,punteroFuncionToken>::iterator it;
        while(!in.eof())
            {
                if(in.eof()||in.fail())
                    break;
                in.get(c);
                //if(c=='('||c==';'||c=='<'||c=='>'||c=='['||isalpha(c)||c=='_'||c=='/'||c=='+'||c=='-'||isdigit(c))
               it=tipoToken.find(c);
               if(it!=tipoToken.end())
                    (this->*tipoToken[c])();

                else
                    out<<c;
            }

    }

    bool esReservada(string id)
    {
        vector<string> reservadas;
        ifstream fileRes;
        string res;
        int j=0;
        int i=0;
        bool x=false;
        fileRes.open("pReservada.txt");
        try
        {
            if(in.fail())
                throw 1;
            while(!fileRes.eof())
            {
                fileRes>>res;
                reservadas.push_back(res);
                j++;
            }
            //cout<<j<<endl;
            //system("pause");
            while(i<j)
            {
              if(id.compare(reservadas[i])==0)
                x=true;
              i++;
            }
        }
        catch(int i)
        {
            if(i==1)
                cout<<"Error al abrir el archivo de palabras Reservadas"<<endl;
            else
                cout<<"Error no definido"<<endl;
        }
        fileRes.close();
        return x;
    }

};

int main(int nArgs,char** args)
{
    /*stringstream z("123.2");
    float o;
    z>>o;
    cout<<o*2;*/
    /*cTokenNum <float> p;
    p.setLexema();
    cout<<p.ConvierteToNum();*/
    const char* sal="miSalida.txt";
    if(nArgs==3)
        sal=args[2];



    cAnalisisLexico analisis1(args[1],sal);
    analisis1.recuperaTokens();
    vector<cToken*> s;
    cAnalisisSintactico p(analisis1.getTokens());
    //analisis1.getTokens();
    return 0;
}


