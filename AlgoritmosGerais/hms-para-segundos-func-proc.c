#include <stdio.h>

// Função - Horas, minutos, segundos para segundos
long int hms_para_s(int h, int m, int s) {
    
    int horasEmSeg, minEmSeg;
    
    horasEmSeg = h * 3600;
    minEmSeg = m * 60;
    
    return (horasEmSeg + minEmSeg + s);
}

// Procedimento
void s_para_hms(int segundos, int *ponteiroHoras, int *ponteiroMin, int *ponteiroSeg) {
    // Adiciona no endereço contido pelo ponteiroHoras o valor dos segundos em horas;
    *ponteiroHoras = segundos / 3600;
    *ponteiroMin = (segundos % 3600) / 60;
    *ponteiroSeg = (segundos % 3600) % 60;
}

int main()
{
    // -- USANDO FUNÇÃO --
    // printf("3h:40m:30s = %ld segundos", hmsParaSegundos(3, 40, 30));
    
    // ----------------------------------------------------------------
    
    // -- USANDO PROCEDIMENTO --
    int horas, min, seg;
    // Ponteiros
    int *endHoras = &horas;
    int *endMin = &min;
    int *endSeg = &seg;
    
    // Procedimento
    s_para_hms(144000, endHoras, endMin, endSeg);
    printf("%02d:%02d:%02d\n", horas, min, seg);
    return 0;
}