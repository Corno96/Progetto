#ifndef CALENDAR
#define CALENDAR

#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>

enum GIORNI{domenica = 0,lunedi,martedi,mercoledi,giovedi,venerdi,sabato};
enum MESI{gennaio = 1,febbraio,marzo,aprile,maggio,giugno,luglio,agosto,settembre,ottobre,novembre,dicembre};

using namespace std;

class Calendar
{
private:
    int month;
    int year;
    int firstday;
public:
    Calendar() : month(1), year(2011){}
    Calendar(int month, int year) : month(month), year(year){}

    static int getGiorniMese(int m)
    {
        int year = 2015;
        switch (m)
        {
          case 1:
            return(31);
          break;
          case 2:
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
              return(29);
            else
              return(28);
          break;
          case 3:
            return(31);
          break;
          case 4:
            return(30);
          break;
          case 5:
            return(31);
          break;
          case 6:
            return(30);
          break;
          case 7:
            return(31);
          break;
          case 8:
            return(31);
          break;
          case 9:
            return(30);
          break;
          case 10:
            return(31);
          break;
          case 11:
            return(30);
          break;
          case 12:
            return(31);
          break;
        }
    }

    static string convertiMese(int m)
    {
        switch (m)
        {
        case gennaio:
            return "Gennaio";
            break;
        case febbraio:
            return "Febbraio";
            break;
        case marzo:
            return "Marzo";
            break;
        case aprile:
            return "Aprile";
            break;
        case maggio:
            return "Maggio";
            break;
        case giugno:
            return "Giugno";
            break;
        case luglio:
            return "Luglio";
            break;
        case agosto:
            return "Agosto";
            break;
        case settembre:
            return "Settembre";
            break;
        case ottobre:
            return "Ottobre";
            break;
        case novembre:
            return "Novembre";
            break;
        case dicembre:
            return "Dicembre";
            break;
        default:
            return "ERRORE CONVERSIONE?";
            break;
        }
    }

    static string convertiGiorno(int w)
    {
        switch (w)
        {
        case domenica:
            return "Domenica";
            break;
        case lunedi:
            return "Lunedi";
            break;
        case martedi:
            return "Martedi";
            break;
        case mercoledi:
            return "Mercoledi";
            break;
        case giovedi:
            return "Giovedi";
            break;
        case venerdi:
            return "Venerdi";
            break;
        case sabato:
            return "Sabato";
            break;
        default:
            return "ERRORE CONVERSIONE?";
            break;
        }
    }

    void setFirstDay()
    {
        //This part determines which day will be the first day of that year (0 for Sunday, 1 for Monday, etc.)
        int day=1;
        int y = year - (14-month)/12;
        int m = month +12 * ((14-month) / 12) -2;
        firstday= (day + y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
    }
    void print()
    {

        int NumberOfDaysInMonth;
        int FirstDayOfMonth = 0;
        int DayOfWeekCounter = 0;
        int DateCounter = 1;

        switch (month)
        {
          case 1:
            NumberOfDaysInMonth = 31;
          break;
          case 2:
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
              NumberOfDaysInMonth = 29;
            else
              NumberOfDaysInMonth = 28;
          break;
          case 3:
            NumberOfDaysInMonth = 31;
          break;
          case 4:
            NumberOfDaysInMonth = 30;
          break;
          case 5:
            NumberOfDaysInMonth = 31;
          break;
          case 6:
            NumberOfDaysInMonth = 30;
          break;
          case 7:
            NumberOfDaysInMonth = 31;
          break;
          case 8:
            NumberOfDaysInMonth = 31;
          break;
          case 9:
            NumberOfDaysInMonth = 30;
          break;
          case 10:
            NumberOfDaysInMonth = 31;
          break;
          case 11:
            NumberOfDaysInMonth = 30;
          break;
          case 12:
            NumberOfDaysInMonth = 31;
          break;
        }
    }
};

#endif
