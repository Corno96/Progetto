#ifndef ELEMENTO
#define ELEMENTO

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <math.h>

#include "Calendar.cpp"

using namespace std;

// inizio   --- fine
// 2015 5 5 --- 2014 6 5
// 2014 3 1 --- 2015 2 2
// 2015 1 1 --- 2015 2 2
bool operator>(tm inizio, tm fine) {
    if (inizio.tm_year > fine.tm_year)
        return true;
    else if (inizio.tm_year == fine.tm_year) {
        if (inizio.tm_mon > fine.tm_mon)
            return true;
        else if (inizio.tm_mon == fine.tm_mon) {
            if (inizio.tm_mday > fine.tm_mday)
                return true;
            else if (inizio.tm_mday == fine.tm_mday) {
                return true;
            }
        }
    }

    // se esecuzione sopravvive a questo if
    return false;
}

class Elemento
{
public:

    // ATTRIBUTI(Private)
    string data;
    double consumo;
    string codice_persona;

    // METODI

    // construttore di default
    Elemento() : data(""), consumo(0), codice_persona("") {}
    // construttore non di default
    Elemento(string data, double consumo, string codice_persona) : data(data), consumo(consumo), codice_persona(codice_persona) {}

    // ridefinizione dell'operatore di assegnamento
    Elemento& operator=(Elemento b)
    {
        data = b.data;
        consumo = b.consumo;
        codice_persona = b.codice_persona;

        return *this;
    }

    // metodo che ritorna l'anno della data dell'elemento
    int getAnno()
    {
        string sub = data.substr(0,4);
        const char* ptr = &sub[0];
        return atof(ptr);
    }
    // metodo che ritorna il mese della data dell'elemento
    int getMese()
    {
        string sub = data.substr(5,2);
        const char* ptr = &sub[0];
        return atof(ptr);
    }
    // metodo che ritorna il giorno della data dell'elemento
    int getGiorno()
    {
        string sub = data.substr(8,2);
        const char* ptr = &sub[0];
        return atof(ptr);
    }
    // metodo che ritorna l'ora della data dell'elemento
    int getOra()
    {
        string sub = data.substr(11,2);
        const char* ptr = &sub[0];
        return atof(ptr);
    }
    // metodo che ritorna i minuti della data dell'elemento
    int getMinuti()
    {
        string sub = data.substr(14,2);
        const char* ptr = &sub[0];
        return atof(ptr);
    }
    // metodo che ritorna i secondi della data dell'elemento
    int getSecondi()
    {
        string sub = data.substr(17,2);
        const char* ptr = &sub[0];
        return atof(ptr);
    }

    // metodo che costruisce una struct tm in base alla data dell'elemento e la ritorna
    tm getTempo()
    {
       time_t tempo;
       struct tm *temp;

       time(&tempo);
       temp = localtime(&tempo);

       temp->tm_year = getAnno() - 1900;
       temp->tm_mon = getMese() - 1;
       temp->tm_mday = getGiorno();
       temp->tm_hour = getOra();
       temp->tm_min = getMinuti();
       temp->tm_sec = getSecondi();

       mktime(temp);

       return *temp;
    }

    // metodo che ricava un elemento da una stringa
    void leggi_elemento(string s)
    {
        Elemento elem;
        vector<string> temp = DividiStringa(s, ',');

        const char* ptr = &temp[1][0];

        temp[0] = temp[0].substr(1, temp[0].size()-1);

        data = temp[0];
        consumo = atof(ptr);
        codice_persona = temp[2];
    }
    // metodo che scambia questo elemento con un altro
    void scambiaElementi (Elemento &b)
    {
        Elemento temp;

        temp = *this;
        *this = b;
        b = temp;
    }
    // metodo che divide una stringa a seconda del divisore in input
    vector<string> DividiStringa(string stringa, char divisore)
    {
        char c = ' ';

        string temp = "";

        c = stringa[0];

        vector<string> elementi;

        for (int i=0;i<stringa.length();i++)
        {
            c = stringa[i];

            if (c == divisore)
            {
                elementi.push_back(temp);
                temp = "";
            }
            else
            {
                temp += c;
            }
        }

        elementi.push_back(temp);

        return elementi;
    }

    // metodo che stampa l'elemento
    void stampa()
    {
        cout<<data<<" "<<consumo<< " "<< codice_persona<<endl;
    }
    // metodo che stampa la data
    void stampaData()
    {
        tm data = getTempo();

        cout << data.tm_year << " " << data.tm_mon << " " << data.tm_mday << " " << data.tm_hour << " "
             << data.tm_min << " " << data.tm_sec << endl;
    }
};

#endif  // ELEMENTO

/*
#include "Elemento.h"

void Elemento::stampa()
{
    cout<<data<<" "<<consumo<< " "<< codice_persona<<endl;
}

int Elemento::getAnno()
{
    string sub = data.substr(0,4);
    const char* ptr = &sub[0];
    return atof(ptr);
}

int Elemento::getMese()
{
    string sub = data.substr(5,2);
    const char* ptr = &sub[0];
    return atof(ptr);
}

int Elemento::getGiorno()
{
    string sub = data.substr(8,2);
    const char* ptr = &sub[0];
    return atof(ptr);
}

int Elemento::getOra()
{
    string sub = data.substr(11,2);
    const char* ptr = &sub[0];
    return atof(ptr);
}

int Elemento::getMinuti()
{
    string sub = data.substr(14,2);
    const char* ptr = &sub[0];
    return atof(ptr);
}

int Elemento::getSecondi()
{
    string sub = data.substr(17,2);
    const char* ptr = &sub[0];
    return atof(ptr);
}

 tm Elemento::getTempo()
 {
    time_t tempo;
    struct tm *temp;

    time(&tempo);
    temp = localtime(&tempo);

    temp->tm_year = getAnno() - 1900;
    temp->tm_mon = getMese() - 1;
    temp->tm_mday = getGiorno();
    //temp->tm_hour = getOra();
    //temp->tm_min = getMinuti();
    //temp->tm_sec = getSecondi();

    mktime(temp);

    return *temp;
 }

Elemento::Elemento()
{
    this->data = "";
    this->consumo = 0;
    this->codice_persona = "";
}

Elemento::Elemento(string data, double consumo, string codice_persona)
{
    this->data = data;
    this->consumo = consumo;
    this->codice_persona = codice_persona;
}

Elemento& Elemento::operator=(Elemento b)
{
    data = b.data;
    consumo = b.consumo;
    codice_persona = b.codice_persona;

    return *this;
}

void Elemento::leggi_elemento(string s)
{
    Elemento elem;
    vector<string> temp = DividiStringa(s, ',');

    const char* ptr = &temp[1][0];

    data = temp[0];
    consumo = atof(ptr);
    codice_persona = temp[2];
}

vector<string> Elemento::DividiStringa(string stringa, char divisore)
{
    char c = ' ';

    string temp = "";

    c = stringa[0];

    vector<string> elementi;

    for (int i=0;i<stringa.length();i++)
    {
        c = stringa[i];

        if (c == divisore)
        {
            elementi.push_back(temp);
            temp = "";
        }
        else
        {
            temp += c;
        }
    }

    elementi.push_back(temp);

    return elementi;
}

void Elemento::scambiaElementi (Elemento &b)
{
    Elemento temp;

    temp = *this;
    *this = b;
    b = temp;
}

void Elemento::stampaData()
{
    tm data = getTempo();

    cout << data.tm_year << " " << data.tm_mon << " " << data.tm_mday << " " << data.tm_hour << " "
         << data.tm_min << " " << data.tm_sec << endl;
}
*/
