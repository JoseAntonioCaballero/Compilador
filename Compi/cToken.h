#ifndef CTOKEN_H_INCLUDED
#define CTOKEN_H_INCLUDED
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;

class cToken
{
    protected:
        string nomToken;
        string lexema;
    public:
        cToken(string nT, string l)
        {
            this->nomToken=nT;
            this->lexema=l;
        }
        cToken(string tyl)
        {
            this->nomToken=tyl;
            this->lexema=tyl;
        }
        //friend class cAnalisisLexico; en vez de sets y gets
        void setNomToken(string nt)
        {
            this->nomToken=nt;
        }
        void setLexema(string l)
        {
            this->lexema=l;
        }
        string getNomToken()
        {
            return this->nomToken;
        }
        string getLexema()
        {
            return this->lexema;
        }
        void imprimeToken()
        {
            cout<<nomToken<<","<<lexema<<endl;
        }
};
template <class T>
class cTokenNum : public cToken
{
    T valorNum;
    public:
    cTokenNum(string nT,string l) : cToken(nT,l)
    {

    }
    void setValor(T vN)
    {
        this->valorNum=vN;
    }
    T getValor()
    {
        return this->valorNum;
    }
    T ConvierteToNum()
    {
        stringstream aux(this->lexema);
        aux>>valorNum;
        return valorNum;
    }
};

#endif // CTOKEN_H_INCLUDED
