#ifndef __MY_FUNC_H
#define __MY_FUNC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <math.h>

/**
 * @brief Функция 1
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float f1(float x);
/**
 * @brief Функция 2
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float f2(float x);
/**
 * @brief Функция 3
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float f3(float x);
/**
 * @brief Производная функции 1
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float df1(float x);
/**
 * @brief Производная функции 2
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float df2(float x);
/**
 * @brief Производная функции 3
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float df3(float x);
/**
 * @brief Функция поиска точек пересечения функций 1 и 2
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float f1_2(float x);
/**
 * @brief Функция поиска точек пересечения функций 1 и 3
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float f1_3(float x);
/**
 * @brief Функция поиска точек пересечения функций 2 и 3
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float f2_3(float x);
/**
 * @brief Производная функции поиска точек пересечения функций 1 и 2
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float df1_2(float x);
/**
 * @brief Производная функции поиска точек пересечения функций 1 и 3
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float df1_3(float x);
/**
 * @brief Производная функции поиска точек пересечения функций 2 и 3
 * 
 * @param x Значение по оси X
 * @return float Значение по оси Y
 */
float df2_3(float x);
/**
 * @brief Функция проверки интервала для функции на наличие корня
 * 
 * @param f Указатель на функцию
 * @param xl левая граница интервала
 * @param xr правая граница интервала
 * @return float Возвращает 1, если корни есть, иначе NAN
 */
float rootPresent(float (*f)(float), float xl, float xr);
// Функция нахождения корня по методу "Линейный поиск"
/**
 * @brief Функция нахождения корня по методу "Линейный поиск"
 * 
 * @param f Указатель на функцию
 * @param xl левая граница интервала
 * @param xr правая граница интервала
 * @param eps точность
 * @return float Возвращает значение корня, либо NAN если его нет
 */
float rootFindLineSearch(float (*f)(float), float xl, float xr, float eps);
/**
 * @brief Функция нахождения корня по методу "Деление отрезка пополам"
 * 
 * @param f Указатель на функцию
 * @param xl левая граница интервала
 * @param xr правая граница интервала
 * @param eps точность
 * @return float Возвращает значение корня, либо NAN если его нет
 */
float rootFindDiv2(float (*f)(float), float xl, float xr, float eps);
/**
 * @brief Функция нахождения корня по методу "Хорды"
 * 
 * @param f Указатель на функцию
 * @param xl левая граница интервала
 * @param xr правая граница интервала
 * @param eps точность
 * @return float Возвращает значение корня, либо NAN если его нет
 */
float rootFindChord(float (*f)(float), float xl, float xr, float eps);
/**
 * @brief Поиск и вывод на экран всех корней на заданном интервале
 * 
 * @param f Указатель на функцию
 * @param fM Указатель на функцию метода поиска
 * @param xl левая граница интервала
 * @param xr правая граница интервала
 * @param eps точность
 * @param minx указатель на минимальный найденный корень
 * @param maxx указатель на максимальный найденный корень
 */
void findAllRoot(float (*f)(float), float (*fM)(float (*f)(float), float, float, float), float xl, float xr, float eps, float *minx, float *maxx);
/**
 * @brief Поиск ближайшей большей точки к y 
 * @param y Заданная точка y
 * @param y1 
 * @param y2 
 * @param y3 
 * @return float Результат поиска
 */
float nearestAbove(float y, float y1, float y2, float y3);
/**
 * @brief Поиск ближайшей меньшей точки к y 
 * @param y Заданная точка y
 * @param y1 
 * @param y2 
 * @param y3 
 * @return float Результат поиска
 */
float nearestBelow(float y, float y1, float y2, float y3);
/**
 * @brief Поиск площади фигуры ограниченной тремя функциями
 * @param f_1 указатель на 1 функцию
 * @param f_2 указатель на 2 функцию
 * @param f_3 указатель на 3 функцию
 * @param xl левая граница поиска
 * @param xr правая граница поиска
 * @param eps шаг интегрирования
 * @param sX точка по оси Х внутри площади искомой фигуры
 * @param sY точка по оси Y внутри площади искомой фигуры
 * @return float Результат рассчета площади
 */
float calcIntegralSquare(float (*f_1)(float), float (*f_2)(float), float (*f_3)(float), float xl, float xr, float eps, float sX, float sY);


#ifdef __cplusplus
}
#endif

#endif