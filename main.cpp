#include "Anno.cpp"
using namespace std;

#define VISUALIZZA 1
#define INTERROGA 2
#define ANALISI 3
#define FINE 4

#define VISUALIZZA_ANNO 1
#define VISUALIZZA_MESE 2
#define VISUALIZZA_SETTIMANA 3
#define VISUALIZZA_GIORNO 4
#define VISUALIZZA_FINE 5

int menuPrincipale();
int menuVisualizza();
tm* creaData();

int main()
{
    Anno a = Anno("C:\\Users\\David\\Desktop\\consumption_some.csv");
    Anno utente;

    vector<string> utenti = a.estraiUtenti();

    int scelta = 0;
    string codice_utente = "";

    while((scelta=menuPrincipale()) != FINE) {
        switch(scelta) {
        case VISUALIZZA:
            do {
                for (int i=0;i<utenti.size();++i){
                    cout << utenti[i] << endl;
                }
                cout << "Inserisci codice utente : ";
                cin >> codice_utente;

                utente = a.estraiUtente(codice_utente);
            }while(utente.vuoto());

            while((scelta=menuVisualizza()) != VISUALIZZA_FINE) {
                switch(scelta) {
                case VISUALIZZA_ANNO:
                {
                    Consumo c = utente.consumoAnnuale();

                    c.stampa();

                    system("pause");
                    break;
                }
                case VISUALIZZA_MESE:
                {
                    int mese = 0;

                    do{
                        cout << "Inserisci il mese da analizzare :";
                        cin >> mese;
                    }while(mese < 1 || mese > 12);

                    Consumo c = utente.consumoMensile(mese);

                    c.stampa();

                    system("pause");
                    break;
                }
                case VISUALIZZA_SETTIMANA:
                {
                    int mese = 0, settimana = 0;

                    do{
                        cout << "Inserisci il mese da analizzare :";
                        cin >> mese;
                    }while(mese < 1 || mese > 12);

                    do{
                        cout << "Inserisci la settimana da analizzare :";
                        cin >> settimana;
                    }while(settimana < 1 || settimana > 6);

                    Consumo c = utente.consumoSettimanale(mese, settimana);

                    if (c.consumo == 0)
                        cout << "Consumo nullo nel periodo richiesto" << endl;
                    else
                        c.stampa();

                    system("pause");

                    break;
                }
                case VISUALIZZA_GIORNO:
                {
                    int mese = 0, giorno = 0;

                    do{
                        cout << "Inserisci il mese da analizzare :";
                        cin >> mese;
                    }while(mese < 1 || mese > 12);

                    do{
                        cout << "Inserisci il giorno da analizzare :";
                        cin >> giorno;
                    }while(giorno < 1 || giorno > 31);

                    Consumo c = utente.consumoGiornaliero(mese, giorno);

                    c.stampa();

                    system("pause");

                    break;
                }
                case VISUALIZZA_FINE:
                    break;
                }
            }

            break;
        case INTERROGA:
        {
            do {
                for (int i=0;i<utenti.size();++i){
                    cout << utenti[i] << endl;
                }
                cout << "Inserisci codice utente : ";
                cin >> codice_utente;

                utente = a.estraiUtente(codice_utente);
            }while(utente.vuoto());

            cout << "Inserisci le date sulle quali effettuare l'interrogazione: " << endl;
            tm data_inizio, data_fine;


            cout << "Data Inizio interrogazione : " << endl;
            data_inizio = *creaData();

            do {
                cout << "Data Fine interrogazione : " << endl;
                data_fine = *creaData();
            } while(data_inizio > data_fine);

            utente.interrogazioneDate(data_inizio, data_fine);

            system("pause");
            break;
        }
        case FINE:
            break;
        }
    }



    return 0;
}

int menuPrincipale(){
    system("cls");

    int scelta = 0;

    do {
        cout << VISUALIZZA << ") Visualizzazione dei consumi" << endl;
        cout << INTERROGA << ") Interrogazione dati periodo" << endl;
        cout << ANALISI << ") Analisi dei consumi" << endl;
        cout << FINE << ") Fine" << endl;

        cin >> scelta;

    }while(scelta < VISUALIZZA || scelta >> FINE);

    return scelta;
}

int menuVisualizza(){
    int scelta = 0;
    system("cls");

    do {
        cout << VISUALIZZA_ANNO << ") Visualizza consumo annuale utente" << endl;
        cout << VISUALIZZA_MESE << ") Visualizza consumo mensile utente" << endl;
        cout << VISUALIZZA_SETTIMANA << ") Visualizza consumo settimanale utente" << endl;
        cout << VISUALIZZA_GIORNO << ") Visualizza consumo giornaliero utente" << endl;
        cout << VISUALIZZA_FINE << ") Fine" << endl;

        cin >> scelta;

    }while(scelta < VISUALIZZA_ANNO || scelta >> VISUALIZZA_FINE);

    return scelta;
}

tm* creaData() {
    int giorno=0, mese=0, anno=0;

    Calendar c = Calendar(1,2015);

    do {
        cout << "Anno : "; cin >> anno;
    } while(anno < 0 || anno > 2020);

    do {
        cout << "Mese : "; cin >> mese;
    } while(mese < 1 || mese > 12);

    do {
        cout << "giorno : "; cin >> giorno;
    } while(giorno < 1 || giorno > c.getGiorniMese(mese));

    tm* data = new tm();
    data->tm_year = anno - 1900;
    data->tm_mon = mese - 1;
    data->tm_mday = giorno;
    data->tm_hour = 0;
    data->tm_min = 0;
    data->tm_sec = 0;

    mktime(data);

    return data;
}
