#ifndef ANNO
#define ANNO

#include "Mese.cpp"

class Anno
{
public:
    vector<Mese> anno;

    Anno(){}
    Anno(string path){creaStruttura(path);}

    // metodo che aggiunge un elemento al giorno
    void aggiungi(Mese m)
    {
        anno.push_back(m);
    }

    // metodo che calcola il consumo annuale
    Consumo consumoAnnuale()
    {
        Consumo c = Consumo();

        // se non ci sono elementi
        if (anno.size() == 0)
            return c;   // ritorno 0

        double consumo = 0, medio = 0, minimo = 0, massimo = 0;

        // passo in rassegna il mese e sommo i consumi dei giorni
        for (int i=0;i<anno.size();++i)
        {
            Consumo mensile = anno[i].consumoMensile();

            if (i==0) {
                massimo = minimo = mensile.consumo;
            } else {
                if (mensile.consumo > massimo)
                    massimo = mensile.consumo;

                if (mensile.consumo < minimo)
                    minimo = mensile.consumo;
            }

            medio += mensile.consumo;
        }

        c = Consumo(medio, medio/anno.size(), minimo, massimo);

        return c;
    }

    // metodo che calcola il consumo mensile
    Consumo consumoMensile(int m)
    {
        return (anno[m-1].consumoMensile());
    }

    // metodo che calcola il consumo settimanale
    Consumo consumoSettimanale(int m, int s)
    {
        return (anno[m-1].consumoSettimanale(s));
    }

    // metodo che calcola il consumo giornaliero
    Consumo consumoGiornaliero(int m, int g)
    {
        return (anno[m-1].mese[g-1].consumoGiornaliero());
    }

    void interrogazioneDate(tm data_inizio, tm data_fine)
    {

    }

    // metodo che carica un vector di elemento da un file posizionato in path, e lo ritorna
    vector<Elemento> caricaFile(string path)
    {
        vector<Elemento> elementi;
        ifstream input;
        Elemento elemento_appoggio;
        string s = "";

        input.open(path.c_str());

        //verifica della corretta apertura del file
        if (!input.is_open())
        {
            cout << "Errore, il file non e' stato aperto correttamente... \n";
        }
        else
        {
            cout << "Caricamento file in memoria..." << endl;

            //estrazione dei dati dal file e inserimento dei valori in una struct
            while(getline(input, s))
            {
                elemento_appoggio.leggi_elemento(s);
                elementi.push_back(elemento_appoggio);
            }

            cout << "Riordinamento dati..." << endl;

            //riordinamento del vettore contenente i dati ricevuti dal file
            quickSort(elementi, 0, elementi.size()-1);
        }

        return elementi;
    }

    // metodo che effettua il quickSort sugli elementi
    void quickSort(vector<Elemento> &elementi, int left, int right)
    {
        int i=left, j=right;
        string tmp;
        string pivot = elementi[(left + right) / 2].data;

        //partizione del vettore ricevuto
        while (i <= j)
        {
            while (elementi[i].data < pivot)
                i++;

            while (elementi[j].data > pivot)
                j--;

            if (i <= j)
            {
                // scambio gli elementi
                Elemento temp;

                temp = elementi[i];
                elementi[i] = elementi[j];
                elementi[j] = temp;
                /*
                tmp = elementi[i].data;
                elementi[i].data = elementi[j].data;
                elementi[j].data = tmp;
                */
                i++;
                j--;
            }

        };

        //ricorsione
        if (left < j)
            quickSort(elementi, left, j);

        if (i < right)
            quickSort(elementi, i, right);
    }

    // metodo che trasferisce vettore di elementi in questa struttura ad accesso diretto, si suppone che dati sia ordinato
    void creaStruttura(string path)
    {
        // carico i dati da file
        vector<Elemento> dati = caricaFile(path);

        cout << "Creazione struttura dati..." << endl;

        int mese_corrente = 1, giorno_corrente = 1;

        Giorno g;
        Mese m;

        // passo in rassegna dati
        for (int i=0;i<dati.size();++i)
        {
            if (dati[i].getMese() == mese_corrente)
            {
                if (dati[i].getGiorno() == giorno_corrente)
                {
                    // aggiungo elemento
                    g.aggiungi(dati[i]);
                }
                else
                {
                    // aumento il giorno
                    ++giorno_corrente;

                    // aggiungo quello che ho
                    m.aggiungi(g);

                    // svuoto giorno
                    g.svuota();

                    // ricomincio
                    g.aggiungi(dati[i]);
                }
            }
            else
            {
                // resetto il giorno
                giorno_corrente = 1;

                // aggiungo quello che ho
                m.aggiungi(g);

                // svuoto giorno
                g.svuota();

                // aumento il mese
                ++mese_corrente;

                // aggiungo quello che ho
                aggiungi(m);

                // svuoto mese
                m.svuota();
            }
        }

        m.aggiungi(g);

        aggiungi(m);
    }

    Anno estraiUtente(string codice_utente)
    {
        Anno utente;

        Mese m, m_tmp;
        Giorno g, g_tmp;

        // for dell'anno
        for (int i=0;i<anno.size();++i)
        {
            m = anno[i];

            // for del mese
            for (int j=0;j<m.mese.size();++j)
            {
                g = m.mese[j];

                for (int k=0;k<g.giorno.size();++k)
                {
                    // se è la persona da estrarre
                    if (g.giorno[k].codice_persona == codice_utente)
                    {
                        g_tmp.aggiungi(g.giorno[k]);
                    }
                }

                // aggiungo giorno che ho modificato
                m_tmp.aggiungi(g_tmp);

                g_tmp.svuota();
            }

            // aggiungo mese che ho modificato
            utente.aggiungi(m_tmp);

            m_tmp.svuota();
        }

        return utente;
    }

    vector<string> estraiUtenti()
    {
        vector<string> utenti;

        Mese m;
        Giorno g;

        // for dell'anno
        for (int i=0;i<anno.size();++i)
        {
            m = anno[i];

            // for del mese
            for (int j=0;j<m.mese.size();++j)
            {
                g = m.mese[j];

                // for del giorno
                for (int k=0;k<g.giorno.size();++k)
                {
                    string cod = g.giorno[0].codice_persona;

                    // se non c'è nel vettore degli utenti
                    if (!trova(utenti, cod))
                    {
                        utenti.push_back(cod);
                    }
                }
            }
        }

        return utenti;
    }

    bool trova(vector<string> vec, string s)
    {
        for (int i=0;i<vec.size();++i)
        {
            if (vec[i] == s)
                return true;
        }

        return false;
    }

    void stampa()
    {
        for (int i=0;i<anno.size();++i)
        {
            anno[i].stampa();

            system("pause");
        }
    }

    bool vuoto(){
        if (anno.empty())
            return true;
        else
            return false;
    }

};


#endif
