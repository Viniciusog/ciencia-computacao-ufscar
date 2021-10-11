#include <stdio.h>

// Função - Horas, minutos, segundos para segundos
long int hmsParaSegundos(int h, int m, int s) {
    
    int horasEmSeg, minEmSeg;
    
    horasEmSeg = h * 3600;
    minEmSeg = m * 60;
    
    return (horasEmSeg + minEmSeg + s);
}

// Procedimento
void hmsParaSegundosProc(int *ponteiroHoras, int *ponteiroMin, int *ponteiroSeg) {
    // Adiciona no endereço contido pelo ponteiroSeg o valor que já está no 
    // endereço contido pelo ponteiroSeg + o valor que está no endereço contido pelo ponteiroHoras * 3600 
    // + o vlaor que está no endereço contido pelo ponteiroMin * 60.
    *ponteiroSeg = *ponteiroSeg + (*ponteiroHoras * 3600) + (*ponteiroMin * 60);
}

int main()
{
    int horas=3, min=40, seg=30;
    // Ponteiros
    int *endHoras = &horas;
    int *endMin = &min;
    int *endSeg = &seg;
    
    // Função
    // printf("3h:40m:30s = %ld segundos", hmsParaSegundos(horas, min, seg));
    
    // Procedimento
    hmsParaSegundosProc(endHoras, endMin, endSeg);
    printf("3h:40m:30s = %d segundos", seg);
    return 0;
}