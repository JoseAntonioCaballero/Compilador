#ifndef ANALIZADORSINTACTICO_H_INCLUDED
#define ANALIZADORSINTACTICO_H_INCLUDED
#include<vector>
#include"cToken.h"
#include <stdlib.h>
#include <list>
#include <sstream>
#include <vector>
#include <String>
#include <iostream>
#include <fstream>
using namespace std;

int i;

class cAnalisisSintactico
{
    string tokenActual;
    int i,numTokens;
    string tokens[100];
    ifstream inPrograma;
    public:
    cAnalisisSintactico(vector<cToken*> bufferTokens)
    {
        for(unsigned int i=0;i<bufferTokens.size();i++)
        {
            bufferTokens[i]->imprimeToken();
        }
        system("pause");
    }
    cAnalisisSintactico()
    {
        i=-1;
        tokenActual="";
        //recuperaTokens();
        inPrograma.open("programaTiny.txt");
        try
        {
            if(inPrograma.fail()){
                throw 0;
			}else{
                cout<<"Exito al abrir archivo"<<endl;
			}
        }
        catch(int i)
        {
            if (i==0)
                cerr<<"Error al abrir programa a analizar";
        }

        recuperaTokens();
    }
    void imprimeTokens()
    {
        for(int i=0;i<numTokens;i++)
            cout<<tokens[i]<<endl;
    }
    void recuperaTokens()
    {
        //llenar arreglo tokens
        int x=0;
        //cout<<"entre while"<<endl;
        while(!inPrograma.eof())
        {
            inPrograma>>tokens[x++];
            //cout<<x;
        }
        cout<<"sali while"<<endl;
        numTokens=x;
    }
    void match(string tokenEsperado)
    {
        if(tokenActual==tokenEsperado)
            tokenActual=obtnSigToken();
        else
            cerr<<"Error match";
    }
    string obtnSigToken()
    {
        return tokens[++i];
    }
    void programa()
    {
        tokenActual=obtnSigToken();//tokenActual vacio
        cout<<"Programa "<<tokenActual<<endl;
        secuencia_sent();
        if (tokenActual!="")
            cout<<"ERROR"<<endl;
    }
    void secuencia_sent()
    {
        sentencia();
        if (tokenActual==";")
          Cprima()  ;
        //sentencia();

    }
    void Cprima()
    {
        if (tokenActual==";")
        {
            match(tokenActual);
            sentencia();
        }
        if (tokenActual==";")
            Cprima();
    }
    void sentencia()
    {
        if(tokenActual=="if")
            sentencia_if();
        else if(tokenActual=="repeat")
            sentencia_repeat();
        else if(tokenActual=="read")
            sentencia_read();
        else if(tokenActual=="write")
            sentencia_write();
        else if(isalpha(tokenActual[0]))
            sentencia_assign();
    }
    void sentencia_if()
    {
        match("if");
        exp();
        match("then");
        secuencia_sent();
        if(tokenActual=="end")
            match("end");
        else if(tokenActual=="else")
        {
            //cout<<tokenActual;
            match("else");
            secuencia_sent();
            match("end");
        }
        else
            cerr<<"Error en la secuencia"<<endl;

    }
    void sentencia_repeat()
    {

        match("repeat");
        secuencia_sent();
        match("until");
        exp();

    }
    void sentencia_assign()
    {
        if (isalpha(tokenActual[0]))
        {
            tokenActual=obtnSigToken();
            match(":=");
            exp();
        }
        else
            cerr<<"Error secuencia_assign";
    }
    void sentencia_read()
    {
        match("read");
        if(isalpha(tokenActual[0])||tokenActual[0]=='_')
            tokenActual=obtnSigToken();
        else
            cerr<<"Error secuencia read"<<endl;

    }
    void sentencia_write()
    {
        match("write");
        exp();
    }
    void exp()
    {
        exp_simple();
        if(tokenActual=="="||tokenActual=="<")
        {
            //cout<<tokenActual;
            match(tokenActual);
            exp_simple();
        }


    }
    void exp_simple()
    {
        term();
        //tokenActual=obtnSigToken();
        if(tokenActual=="+"||tokenActual=="-")
            Aprima();
    }
    void Aprima()
    {
        if(tokenActual=="+"||tokenActual=="-")
        {
            match(tokenActual);
            term();
        }
        if(tokenActual=="+"||tokenActual=="-")
            Aprima();
    }
    void term()
    {
        factor();
        if(tokenActual=="*"||tokenActual=="/")
            Bprima();

    }
    void Bprima()
    {
        if(tokenActual=="*"||tokenActual=="/")
        {
            match(tokenActual);
            factor();
        }
        if(tokenActual=="*"||tokenActual=="/")
            Bprima();
    }
    void factor()
    {
        if(tokenActual=="(")
        {
            match("(");
            exp();
            match(")");

        }
        else if(isdigit(tokenActual[0]))
        {
            match(tokenActual);
        }
        else if(isalpha(tokenActual[0])||tokenActual[0]=='_')
        {
            match(tokenActual);
        }
        else
            cerr<<"Error en el factor"<<endl;
    }

};


#endif // ANALIZADORSINTACTICO_H_INCLUDED
