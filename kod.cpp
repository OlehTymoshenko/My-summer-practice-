/**
* @file   Summer practice.cpp
* @author Тимошенко О.О., гр. 515Б
* @date   18 июня 2018
* @brief  Летняя практика
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX_LEN 50 // макс. длина строк

/**
* Функция вызова нужный функций для перевода числа в строку(часы)
*
* @param hour - к-во часов в введен. польз. времени
* @return str_hour, если преобр. успешно, или NULL, если нет
*/
char * check_h(int hour); // прототип ф-кции check_h

/**
* Функция вызова нужный функций для перевода числа в строку(минуты)
*
* @param min - к-во минут в введен. польз. времени
* @return str_min, если преобр. успешно, или NULL, если нет
*/
char * check_min(int min); // прототип ф-кции check_min

/**
* Разделение числа на 2 цифры
*
* @param *part-1 - первая цифра
* @param *part-2 - вторая цифра
* @param num - число
* @return ничего (тип данных ф-кции void)
*/
void dev_num(int * part_1, int * part_2, int num);

/**
* перевод из цифры в буквы для цифр 0-9
*
* @param part_2 - вторая цифра числа
* @param *str_h - строка для сохрания цифры буквами
* @return ничего (тип данных ф-кции void)
*/
void units_f(int part_2, char * str_h);

/**
* перевод из цифры в буквы для цифр 11-19
*
* @param part_2 - вторая цифра числа
* @param *str_hour - строка для сохрания цифры буквами
* @return ничего (тип данных ф-кции void)
*/
void teens(int num_2, char *  str_hour);

/**
* перевод из цифры в буквы для цифр 10, 20, 30, 40, 50
*
* @param part_1 - первая цифра числа
* @param *str_dec - строка для сохрания цифры буквами
* @return ничего (тип данных ф-кции void)
*/
void decades(int part_1, char * str_dec);

/**
* добавления правильной формы слова "година"
*
* @param part_2 - вторая цифра числа
* @param *str_form - строка для сохрания цифры буквами и прав. формы слова година
* @return ничего (тип данных ф-кции void)
*/
void form_hour(char * str_form, int part_2);

/**
* добавления правильной формы слова "хвилина"
*
* @param part_2 - вторая цифра числа
* @param *str_form - строка для сохрания цифры буквами и прав. формы слова хвилина
* @return ничего (тип данных ф-кции void)
*/
void form_min(char * str_form, int part_2);

const char * units[] = { "нуль", "один", "два", "три", "чотири", "п'ять", "шiсть", "сiм", "вiсiм", "дев'ять" }; // const масс. для цифр
const char * dec[] = { "десять", "двадцять", "тридцять", "сорок", "п'ятдесят" }; // const масс. для десятков
char * str_hour, *str_min; // строки для храниния числа буквами и прав. формы нужного слова(година, хвилина)

int main()
{
	char * str_hour_m, *str_min_m; // указ. для хран. возв. знач. ф-ций check_h, check_min
	setlocale(LC_ALL, "ukr"); // подкл. укр. языка
	int part_hour, part_min, choice; // part_hour-часовая состав. времени, part_min-минутная сост. времени, choice-перем. для хран. выбор. польз.
	while (1) // безк. цикл
	{
		printf("Введiть час числами(у форматi гг хх):");
		scanf_s("%d%d", &part_hour, &part_min); // ввод времени
		str_hour = (char*)calloc(MAX_LEN, sizeof(char)); // выдел. памяти для str_hour
		str_min = (char*)calloc(MAX_LEN, sizeof(char)); // выдел. памяти для str_min
		str_hour_m = check_h(part_hour); // вызов. ф-кции check_h, присв. str_hour_m возр. знач. этой ф-кции
		str_min_m = check_min(part_min); // вызов. ф-кции check_min, присв. str_min_m возр. знач. этой ф-кции
		if (str_hour_m == NULL || str_min_m == NULL) goto clear; // если не успеш. преобр.
		strcat(str_hour, " "); // добавление пробела
		strcat(str_hour, str_min_m); // добавление минутной состав. времени к часовой
		printf("Введений час лiтерами: %s\n", str_hour);  // вывод. преоб. времени
	clear: free(str_hour); // освоб. памяти
		free(str_min); // освоб. памяти
		printf("Введiть число 1, якщо хочете продовжити, або 0, якщо бажаєте вийти з программи:");
		scanf_s("%d", &choice); // ввод выбора польз.
		if (!choice) break; // выход из цикла, если польз. ввел 0
	}
	return 0; // заверш. программы
}

char * check_h(int hour)  // описание ф-кции check_h
{
	int num_1, num_2; // первая и вторая часть числа
	if (hour < 0 || hour>23) { // если часы меньше 0 или больше 23, то заверш. ф-кцию
		printf("Введений час невiрний\n");
		return NULL; // возв. NULL
	}
	dev_num(&num_1, &num_2, hour); // вызов ф-кции разд. числа на 2 цифры
	if (num_1 == 0) units_f(num_2, str_hour); // если первая цифра = 0, то вызов ф-кцию units_f
	if (num_1 == 1 && num_2 != 0) teens(num_2, str_hour); // при выпол. условий вызов ф-кции teens
	if (num_1 != 0 && num_2 == 0) decades(num_1, str_hour); // при выпол. условий вызов ф-кции decades
	if (num_1 > 1 && num_2 != 0) // при выпол. условий вызов ф-кций decades и units_f
	{
		decades(num_1, str_hour);
		strcat(str_hour, " "); // добав. пробела в строку
		units_f(num_2, str_hour);
	}
	if (hour > 10 && hour < 20) { // если час больше 10 и меньше 20, то добав. к строку "годин"
		strcat(str_hour, " годин"); // добавление "годин"
	}
	else { // если hour не больше 10 или больше 20, то
		form_hour(str_hour, num_2); // вызов ф-кции form_hour
	}
	return str_hour; // возв. знач. str_hour
}

char * check_min(int min) // описание ф-кции check_min
{
	int num_1, num_2; // первая и вторая часть числа
	if (min < 0 || min>59) { // если минуты меньше 0 или больше 59, то заверш. ф-кцию
		printf("Введений час невiрний\n");
		return NULL; // возв. NULL
	}
	dev_num(&num_1, &num_2, min); // вызов ф-кции разд. числа на 2 цифры
	if (num_1 == 0) units_f(num_2, str_min); // если первая цифра = 0, то вызов ф-кцию units_f
	if (num_1 == 1 && num_2 != 0) teens(num_2, str_min); // при выпол. условий вызов ф-кции teens
	if (num_1 != 0 && num_2 == 0) decades(num_1, str_min); // при выпол. условий вызов ф-кции decades
	if (num_1 > 1 && num_2 != 0) // при выпол. условий вызов ф-кций decades и units_f
	{
		decades(num_1, str_min);
		strcat(str_min, " "); // добав. пробела в строку
		units_f(num_2, str_min);
	}
	if (min > 10 && min < 20) { // если минуты больше 10 и меньше 20, то добав. к строку "хвилин"
		strcat(str_min, " хвилин"); // добавление "хвилин"
	}
	else {  // если min не больше 10 или больше 20, то
		form_min(str_min, num_2); // вызов ф-кции form_min
	}
	return str_min; // возв. знач. str_min
}