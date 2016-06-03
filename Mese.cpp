#ifndef MESE
#define MESE

#include "Giorno.cpp"

class Mese
{
public:
    vector<Giorno> mese;

    Mese(){}
    //Mese(vector<Elemento> g) : giorno(g) {}

    // metodo che aggiunge un giorno al mese
    void aggiungi(Giorno g)
    {
        mese.push_back(g);
    }

    // metodo che calcola il consumo mensile
    Consumo consumoMensile()
    {
        Consumo c = Consumo();

        // se non ci sono elementi
        if (mese.size() == 0)
            return c;   // ritorno vuoto

        double consumo = 0, massimo = -1, minimo = -1, media = 0;

        // passo in rassegna il mese e sommo i consumi dei giorni
        for (int i=0;i<mese.size();++i)
        {
            Consumo tmp = mese[i].consumoGiornaliero();

            if (massimo == -1)
            {
                massimo = tmp.consumo;
                minimo = tmp.consumo;
            }

            if (tmp.consumo > massimo)
                massimo = tmp.consumo;

            if (tmp.consumo < minimo)
                minimo = tmp.consumo;

            consumo += tmp.consumo;
        }

        c = Consumo(consumo, consumo/mese.size(), minimo, massimo);

        return c;
    }

    // metodo che calcola il consumo settimanale
    Consumo consumoSettimanale(int s)
    {
        Consumo c = Consumo();

        // se non ci sono elementi
        if (mese.size() == 0)
            return c;   // ritorno vuoto

        double consumo = 0, minimo = 0, massimo = 0;
        int cont_settimana = 1, cont_giorni = 0;

        tm tempo;

        // passo in rassegna il mese fino alla fine o fino a quando ho calcolato il consumo
        for (int i=0;i<mese.size() && cont_settimana <= s;++i)
        {
            if (mese[i].giorno.size() > 0)
               tempo  = mese[i].getTempo();
            else
               ++tempo.tm_wday;

            if (cont_settimana == s)
            {
                Consumo t = mese[i].consumoGiornaliero();

                // minimo massimo
                if (i==0) {
                    minimo = massimo = t.consumo;
                } else {
                    if (t.consumo > massimo)
                        massimo = t.consumo;

                    if (t.consumo < minimo)
                        minimo = t.consumo;
                }

                // aggiungo a consumo
                consumo += t.consumo;

                // aumento cont_giorno (per media)
                ++cont_giorni;
            }

            // se è domenica
            if (tempo.tm_wday == domenica)
            {
                ++cont_settimana;
            }
        }

        c = Consumo(consumo, consumo/cont_giorni, minimo, massimo);

        return c;
    }

    void svuota()
    {
        mese.clear();
    }

    void stampa()
    {
        for (int i=0;i<mese.size();++i)
        {
            mese[i].stampa();
        }
    }
};

#endif
