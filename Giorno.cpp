#ifndef GIORNO
#define GIORNO

#include "Elemento.cpp"
#include "Consumo.cpp"

class Giorno
{
public:
    vector<Elemento> giorno;

    Giorno(){}
    //Giorno(vector<Elemento> g) : giorno(g) {}

    // metodo che aggiunge un elemento al giorno
    void aggiungi(Elemento e)
    {
        giorno.push_back(e);
    }

    // metodo che calcola il consumo giornaliero
    Consumo consumoGiornaliero()
    {
        double medio = 0, minimo = 0, massimo = 0;
        Consumo c = Consumo();

        // se non ci sono elementi
        if (giorno.size() == 0) {
            return c;   // ritorno vuoto
        }

        double temp = giorno[0].consumo;

        for (int i=0;i<giorno.size();++i) {
            if (i==0) {
                massimo = minimo = giorno[0].consumo;
            } else {
                if (giorno[i].consumo > massimo)
                    massimo = giorno[i].consumo;

                if (giorno[i].consumo < minimo)
                    minimo = giorno[i].consumo;
            }

            medio += giorno[i].consumo;
        }

        c = Consumo(giorno[giorno.size() - 1].consumo - temp, medio/giorno.size() - temp, minimo - temp, massimo - temp);

        return c;
        //stampa();

        //return (giorno[giorno.size() - 1].consumo - giorno[0].consumo);     // altrimenti il consumo è l'ultimo meno il primo
    }

    tm getTempo()
    {
        return giorno[0].getTempo();
    }

    void svuota()
    {
        giorno.clear();
    }

    void stampa()
    {
        for (int i=0;i<giorno.size();++i)
        {
            giorno[i].stampa();
        }
    }
};

#endif
