// Não deixa ter inclusão do mesmo arquivo duas vezes no local em que o mesmo for chamado.
#ifndef TIME_H 
#define TIME_H

class Time {
    public:
        Time(int h, int m, int s); // construtor
        ~Time(); // destrutor
        void setTime(int h, int m, int s);
        int getTimeHour();
        int getTimeMinute();
        int getTimeSecond();
        void printUniversal();
        void printStandard();
    private:
        int hour;
        int minute;
        int second;
};

#endif