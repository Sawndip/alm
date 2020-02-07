/**
 *  author:   Yuriy Lobarev
 *  telegram: @forman
 *  phone:    +7(910)983-95-90
 *  email:    forman@anyks.com
 *  site:     https://anyks.com
 */

#ifndef _ANYKS_ENV_
#define _ANYKS_ENV_

/**
 * Стандартная библиотека
 */
#include <vector>
#include <string>
#include <limits>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unistd.h>
/**
 * Наши модули
 */
#include <alphabet.hpp>

using namespace std;

/**
 * anyks пространство имён
 */
namespace anyks {
	/**
	 * Env Класс модуля работы с переменными окружения
	 */
	typedef class Env {
		private:
			// Объект алфавита
			const alphabet_t * alphabet = nullptr;
		private:
			/**
			 * Название переменной содержащей текст
			 * и префикс переменной окружения
			 */
			string text, prefix;
			// Переменная окружения
			mutable string variable;
			// Список полученных переменных окружения
			unordered_map <string, string> data;
		private:
			/**
			 * env Метод извлечения переменной окружения
			 * @param  key переменная окружения
			 * @return     значение переменной
			 */
			const string env(const string & key) const;
		public:
			/**
			 * count Метод извлечения количества аргументов
			 * @return количество полученных аргументов
			 */
			const u_short count() const;
			/**
			 * get Метод извлечения содержимого переменной окружения
			 * @param  name название переменной окружения
			 * @return      значение переменной окружения
			 */
			const char * get(const string & name) const;
			/**
			 * is Метод проверки наличия и значения переменной
			 * @param key ключ - название переменной для проверки
			 * @param val значение переменной для проверки (если требуется)
			 */
			const bool is(const string & key, const string & val = "") const;
		public:
			/**
			 * textEnv Метод установки списка имён которые нужно извлечь
			 * @param text название переменной для извлечения текстовой информации из потока (если параметром не передана)
			 */
			void textEnv(const string & text);
			/**
			 * prefixEnv Метод установки префикса переменной окружения
			 * @param prefix префикс переменной окружения
			 */
			void prefixEnv(const string & prefix);
			/**
			 * setAlphabet Метод установки алфавита
			 * @param alphabet объект алфавита
			 */
			void setAlphabet(const alphabet_t * alphabet);
			/**
			 * read Метод чтения данных переменных окружения
			 * @param args  список переменных окружения
			 * @param count количество переменных окружения
			 */
			void read(const char * args[], const u_short count);
		public:
			/**
			 * Env Конструктор
			 * @param prefix префикс переменной окружения
			 */
			Env(const string & prefix);
			/**
			 * Env Конструктор
			 * @param alphabet объект алфавита
			 */
			Env(const alphabet_t * alphabet = nullptr);
			/**
			 * Env Конструктор
			 * @param prefix префикс переменной окружения
			 * @param text   название переменной для извлечения текстовой информации из потока (если параметром не передана)
			 */
			Env(const string & prefix, const string & text);
			/**
			 * Env Конструктор
			 * @param prefix   префикс переменной окружения
			 * @param alphabet объект алфавита
			 */
			Env(const string & prefix, const alphabet_t * alphabet);
			/**
			 * Env Конструктор
			 * @param prefix   префикс переменной окружения
			 * @param text     название переменной для извлечения текстовой информации из потока (если параметром не передана)
			 * @param alphabet объект алфавита
			 */
			Env(const string & prefix, const string & text, const alphabet_t * alphabet);
	} env_t;
};

#endif // _ANYKS_ENV_
