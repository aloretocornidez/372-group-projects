/*
 *
 * Author: Alan Manuel Loreto Cornídez
 * Initial Creation Date: December 1, 2022
 * Last Modified Date: December 1, 2022
 * Description: Header file for an fft library made from scratch.
 * 
 */

#ifndef FFT_H
#define FFT_H

/*
    Библиотека преобразования Фурье на С (для esp8266)
    GitHub: https://github.com/GyverLibs/FFT_C
    
    Основано на https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%BE%D0%B5_%D0%BF%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%A4%D1%83%D1%80%D1%8C%D0%B5
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    Версии:
    v1.0 - релиз
*/

// AVal - массив анализируемых данных
// FTvl - массив полученных значений
// FFT_SIZE - длина массива должна быть кратна степени 2
// void FFT(int* AVal, int* FTvl);
void FFT(float* AVal, float* FTvl);

void initFFTparams();







#endif