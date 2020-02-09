/**
 *  author:   Yuriy Lobarev
 *  telegram: @forman
 *  phone:    +7(910)983-95-90
 *  email:    forman@anyks.com
 *  site:     https://anyks.com
 */

#include <env.hpp>
#include <ablm.hpp>
#include <toolkit.hpp>
#include <progress.hpp>

using namespace std;
using namespace anyks;

/**
 * version Функция вывода версии приложения
 * @param address адрес приложения
 */
void version(const char * address){
	// Позиция в каталоге
	size_t pos = 0;
#ifdef __linux__
	// Название операционной системы
	const char * osname = "Linux";
#elif __FreeBSD__
	// Название операционной системы
	const char * osname = "FreeBSD";
#elif __APPLE__ || __MACH__
	// Название операционной системы
	const char * osname = "MacOS X";
#endif
	// Определяем адрес приложения
	string appname = realpath(address, nullptr);
	// Ищем каталог
	if((pos = appname.rfind("/")) != string::npos) appname = move(appname.substr(0, pos));
	// Выводим версию приложения
	printf(
		"\r\n%s %s (built: %s %s)\r\n"
		"target: %s\r\n"
		"installed dir: %s\r\n\r\n*\r\n"
		"* author:   %s\r\n"
		"* telegram: %s\r\n"
		"* email:    %s\r\n"
		"* site:     %s\r\n*\r\n\r\n",
		ANYKS_LM_NAME,
		ANYKS_VERSION,
		__DATE__,
		__TIME__,
		osname,
		appname.c_str(),
		ANYKS_AUTHOR,
		ANYKS_CONTACT,
		ANYKS_EMAIL,
		ANYKS_SITE
	);
}
/**
 * help Функция вывода справки
 */
void help(){
	// Формируем строку справки
	const string msg = "\r\n\x1B[32m\x1B[1musage:\x1B[0m alm [-V | --version] [-h | --help] "
	"[-alphabet <value> | --alphabet=<value>] [<args>]\r\n\r\n\r\n"
	"\x1B[34m\x1B[1mmethods:\x1B[0m\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m prune:  language model pruning method\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m sweep:  high backoff n-gram removal method\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m info:   binary dictionary information method\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m repair: broken language model recovery method\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m modify: method for modifying a language model\r\n"
	"  \x1B[1m-\x1B[0m (emplace | remove | change | replace)\r\n\r\n\r\n"
	"\x1B[34m\x1B[1mflags:\x1B[0m\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m case-insensitive flag:                                                        [-lower-case | --lower-case]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m unknown word permission flag:                                                 [-allow-unk | --allow-unk]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag allowing to consider words from the white list only:                     [-only-good | --only-good]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag allowing to use interpolation in estimating:                             [-interpolate | --interpolate]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag allowing accounting of all collected n-grams:                            [-all-grams | --all-grams]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an date sign:                                   [-no-date | --no-date]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an time sign:                                   [-no-time | --no-time]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an score sign:                                  [-no-score | --no-score]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an fraction sign:                               [-no-fract | --no-fract]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an dimension sign:                              [-no-dimen | --no-dimen]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of custom attributes:                              [-no-usign | --no-usign]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting the detection of Roman numerals:                             [-no-roman | --no-roman]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an punctuation sign:                            [-no-punct | --no-punct]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an approximate sign:                            [-no-aprox | --no-aprox]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of an abbreviation sign:                           [-no-abbr | --no-abbr]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting the detection of a sign of numbers:                          [-no-number | --no-number]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting the detection of a pseudo-number sign:                       [-no-a-number | --no-a-number]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag prohibiting detection of a sign of a range of numbers:                   [-no-range | --no-range]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag export in binary dictionary of users signs:                              [-w-bin-usigns | --w-bin-usigns]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag export in binary dictionary of toolkit options:                          [-w-bin-options | --w-bin-options]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag export in binary dictionary of blacklisted words:                        [-w-bin-badwords | --w-bin-badwords]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag export in binary dictionary of whitelisted words:                        [-w-bin-goodwords | --w-bin-goodwords]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag export in binary dictionary of script python - word preprocessing:       [-w-bin-preword | --w-bin-preword]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m flag export in binary dictionary of only arpa data without n-gram statistics: [-w-bin-arpa | --w-bin-arpa]\r\n\r\n\r\n"
	"\x1B[34m\x1B[1margs:\x1B[0m\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m alphabet (file or value):                           [-alphabet <value> | --alphabet=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m size n-grams:                                       [-size <value> | --size=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m log file address:                                   [-log <value> | --log=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m blacklisted file address:                           [-badwords <value> | --badwords=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m whitelisted file address:                           [-goodwords <value> | --goodwords=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m unknown word name:                                  [-unknown-word <value> | --unknown-word=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m script python3 - word preprocessing:                [-word-script <value> | --word-script=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m script python3 - custom attribute detector:         [-usign-script <value> | --usign-script=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m text file training corpus:                          [-corpus <value> | --corpus=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m extension files corpus:                             [-ext <value> | --ext=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m directory path with text corpus:                    [-path <value> | --path=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.alm binary file for export:               [-w-bin <value> | --w-bin=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.json meta file for export:                [-w-bin-meta <value> | --w-bin-meta=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.map file for export:                      [-w-map <value> | --w-map=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.arpa file for export:                     [-w-arpa <value> | --w-arpa=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.vocab file for export:                    [-w-vocab <value> | --w-vocab=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.ngrams file for export:                   [-w-ngram <value> | --w-ngram=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.alm binary file for import:               [-r-bin <value> | --r-bin=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.json meta file for import:                [-r-bin-meta <value> | --r-bin-meta=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.map file for import:                      [-r-map <value> | --r-map=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m directory path with *.map files:                    [-r-maps <value> | --r-maps=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.vocab file for import:                    [-r-vocab <value> | --r-vocab=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m directory path with *.vocab files:                  [-r-vocabs <value> | --r-vocabs=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.ngrams file for import:                   [-r-ngram <value> | --r-ngram=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m directory path with *.ngrams files:                 [-r-ngrams <value> | --r-ngrams=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m address *.arpa file for import:                     [-r-arpa <value> | --r-arpa=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m directory path with *.arpa files:                   [-r-arpas <value> | --r-arpas=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m pruning frequency threshold:                        [-prune-threshold <value> | --prune-threshold=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m the maximum size of n-grams of pruning:             [-prune-max-gram <value> | --prune-max-gram=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m list of custom attributes:                          [-usigns <value> | --usigns=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m modification flag for modify method:                [-modify <value> | --modify=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m delta size for smoothing by addsmooth algorithm:    [-delta <value> | --delta=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m discount size for smoothing by cdiscount algorithm: [-discount <value> | --discount=<value>]\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m debug mode:                                         [-debug <value> | --debug=<value>]\r\n"
	"  \x1B[1m-\x1B[0m (0 - off | 1 - progress | 2 - console)\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m method application:                                 [-method <value> | --method=<value>]\r\n"
	"  \x1B[1m-\x1B[0m (train | repair | modify | sweep | prune)\r\n\r\n"
	"\x1B[33m\x1B[1m×\x1B[0m smoothing algorithm:                                [-smoothing <value> | --smoothing=<value>]\r\n"
	"  \x1B[1m-\x1B[0m (goodturing | cdiscount | ndiscount | addsmooth | wittenbell | kneserney | mkneserney)\r\n\r\n";
	// Выводим сообщение справки
	printf("%s", msg.c_str());
}
/**
 * print Функция вывода сообщения в консоль
 * @param text     текст для вывода
 * @param filename адрес log файла
 * @param flag     флаг типа сообщения (info, error, warning)
 * @param end      флаг выхода из приложения
 */
void print(const string & text, const char * filename = nullptr, const alphabet_t::log_t flag = alphabet_t::log_t::error, const bool end = true){
	// Результат работы функции
	if(!text.empty()){
		// Выполняем логирование
		alphabet_t().log("%s", flag, filename, text.c_str());
		// Выходим из приложения
		if(end) exit(EXIT_FAILURE);
	}
}
/**
 * main Главная функция приложения
 * @param  argc длина массива параметров
 * @param  argv массив параметров
 * @return      код выхода из приложения
 */
int main(int argc, char * argv[]){
	// Создаём алфавит
	alphabet_t alphabet;
	// Бинарный файл словаря
	string binDictFile = "";
	// Значение параметра
	const char * value = nullptr;
	// Устанавливаем локаль
	alphabet.setlocale("en_US.UTF-8");
	// Объект отлова переменных
	env_t env(ANYKS_LM_NAME, &alphabet);
	// Выполняем чтение переданных параметров
	env.read((const char **) argv, argc);
	// Если это вывод справки
	if(!env.count() || env.is("help") || env.is("h")) {
		// Выводим справочную информацию
		help();
		// Выходим из приложения
		exit(0);
	// Если версия получена
	} else if(env.is("version") || env.is("V")){
		// Выводим версию приложения
		version(argv[0]);
		// Выходим из приложения
		exit(0);
	}
	// Проверяем существует ли бинарный файл
	if(((value = env.get("r-bin")) != nullptr) && fsys_t::isfile(value)) binDictFile = value;
	// Если алфавит снова не найден
	if(binDictFile.empty() && ((value = env.get("alphabet")) == nullptr)){
		// Выводим сообщение в консоль
		print("alphabet in not set", env.get("log"));
	// Продолжаем дальше
	} else {
		// Объявляем прогресс бра
		progress_t pss;
		// Расширение файла
		string ext = "txt";
		// Переводим указатель в строку
		string letters = (value != nullptr ? value : "");
		// Если расширение файлов передано
		if((value = env.get("ext")) != nullptr) ext = value;
		// Добавляем точку к расширению
		ext.insert(ext.begin(), 1, '.');
		// Проверяем является ли алфавит файлом
		if(letters.rfind(ext) != string::npos){
			// Получаем адрес файла
			const string filename = letters;
			// Очищаем список букв алфавита
			letters.clear();
			// Выполняем считывание всех строк текста
			fsys_t::rfile(filename, [&letters](const string & line, const uintmax_t size){
				// Если текст получен
				if(!line.empty()) letters.append(line);
			});
		}
		// Если алфавит получен
		if(!binDictFile.empty() || !letters.empty()){
			// Дополнительный коэффициент алгоритма сглаживания
			float mod = 0.0f;
			// Режим отладки и общий размер n-граммы
			u_short debug = 0, order = 1;
			// Устанавливаем символы алфавита
			if(!letters.empty()) alphabet.set(alphabet.toLower(letters));
			// Если режим отладки получен
			if((value = env.get("debug")) != nullptr){
				// Устанавливаем тип режима
				debug = stoi(value);
				// Если режим отладки больше указанного, компенсируем
				if(debug > 2) debug = 2;
			}
			// Если общий размер n-граммы получен
			if((value = env.get("size")) != nullptr) order = stoi(value);
			// Если бинарный файл не указан
			if(binDictFile.empty()){
				// Если алгоритм получен
				if(env.is("smoothing") && (string(env.get("smoothing")).compare("-yes-") != 0)){
					// Проверяем правильность введённого алгоритма сглаживания
					if(!env.is("smoothing", "goodturing") &&
					!env.is("smoothing", "cdiscount") &&
					!env.is("smoothing", "ndiscount") &&
					!env.is("smoothing", "addsmooth") &&
					!env.is("smoothing", "wittenbell") &&
					!env.is("smoothing", "kneserney") &&
					!env.is("smoothing", "mkneserney"))
						// Выводим сообщение в консоль
						print(alphabet.format("the algorithm name \"%s\" is bad", env.get("smoothing")), env.get("log"));
				// Сообщаем что алгоритм сглаживания не указан
				} else print("algorithm smoothing is not set", env.get("log"));
			}
			// Если основной метод работы получен
			if(env.is("method") && (string(env.get("method")).compare("-yes-") != 0)){
				// Проверяем правильность введённого основного метода работы
				if(!env.is("method", "train") &&
				!env.is("method", "repair") &&
				!env.is("method", "modify") &&
				!env.is("method", "sweep") &&
				!env.is("method", "prune") &&
				!env.is("method", "info"))
					// Выводим сообщение в консоль
					print(alphabet.format("the method name \"%s\" is bad", env.get("method")), env.get("log"));
			// Сообщаем что метод не указан
			} else print("toolkit method is not set", env.get("log"));
			// Если ни один файл для сохранения не передан, выходим
			if(!env.is("w-map") && !env.is("w-arpa") && !env.is("w-vocab") &&
			!env.is("w-ngram") && !env.is("w-bin") && !env.is("method", "info")) print("file address to save is not specified", env.get("log"));
			// Если алгоритм сглаживания ConstDiscount или AddSmooth, запрашиваем дополнительные параметры
			if(env.is("smoothing", "cdiscount") || env.is("smoothing", "addsmooth")){
				// Считываем флаг дополнительной модификации
				value = (env.is("smoothing", "cdiscount") ? env.get("discount") : env.get("delta"));
				// Если значение получено
				if(value != nullptr) mod = stof(value);
			}
			/** Начало работы основных методов **/
			// Создаём объект тулкита языковой модели
			toolkit_t toolkit(&alphabet, order);
			// Устанавливаем адрес файла для логирования
			toolkit.setLogfile(env.get("log"));
			// Устанавливаем режим отладки
			if(debug == 2) toolkit.setOption(toolkit_t::options_t::debug);
			// Разрешаем использовать признак неизвестного слова
			if(env.is("allow-unk")) toolkit.setOption(toolkit_t::options_t::allowUnk);
			// Разрешаем использовать абсолютно все полученные n-граммы
			if(env.is("all-grams")) toolkit.setOption(toolkit_t::options_t::allGrams);
			// Разрешаем переводить слова в нижний регистр
			if(env.is("lower-case")) toolkit.setOption(toolkit_t::options_t::lowerCase);
			// Разрешаем выполнять интерполяцию при расчёте arpa
			if(env.is("interpolate")) toolkit.setOption(toolkit_t::options_t::interpolate);
			// Устанавливаем запрет на все слова кроме тех, что находятся в белом списке
			if(env.is("only-good")) toolkit.setOption(toolkit_t::options_t::onlyGood);
			// Отключаем системный признак детектирования аббревиатур
			if(env.is("no-abbr")) toolkit.setOption(toolkit_t::options_t::notAbbr);
			// Отключаем системный признак детектирования диапазонов чисел
			if(env.is("no-range")) toolkit.setOption(toolkit_t::options_t::notRange);
			// Отключаем системный признак детектирования римских чисел
			if(env.is("no-roman")) toolkit.setOption(toolkit_t::options_t::notRoman);
			// Отключаем системный признак детектирования чисел
			if(env.is("no-number")) toolkit.setOption(toolkit_t::options_t::notNumber);
			// Отключаем применение пользовательского признака детектирования
			if(env.is("no-usign")) toolkit.setOption(toolkit_t::options_t::notUserSign);
			// Отключаем системный признак детектирования псевдо-чисел
			if(env.is("no-a-number")) toolkit.setOption(toolkit_t::options_t::notANumber);
			// Отключаем системный признак детектирования даты
			if(env.is("no-date")) toolkit.setOption(toolkit_t::options_t::notDate);
			// Отключаем системный признак детектирования времени
			if(env.is("no-time")) toolkit.setOption(toolkit_t::options_t::notTime);
			// Отключаем системный признак детектирования знаков пунктуации
			if(env.is("no-punct")) toolkit.setOption(toolkit_t::options_t::notPunct);
			// Отключаем системный признак детектирования числового счёта
			if(env.is("no-score")) toolkit.setOption(toolkit_t::options_t::notScore);
			// Отключаем системный признак детектирования габаритных размеров
			if(env.is("no-dimen")) toolkit.setOption(toolkit_t::options_t::notDimen);
			// Отключаем системный признак детектирования числовой дроби
			if(env.is("no-fract")) toolkit.setOption(toolkit_t::options_t::notFract);
			// Отключаем системный признак детектирования приблизительного числа
			if(env.is("no-aprox")) toolkit.setOption(toolkit_t::options_t::notAprox);
			// Если адрес файла чёрного списка получен
			if((value = env.get("badwords")) != nullptr){
				// Чёрный список слов
				vector <string> badwords;
				// Выполняем считывание всех слов для чёрного списка
				fsys_t::rfile(value, [&badwords, &toolkit](const string & line, const uintmax_t fileSize){
					// Если текст получен
					if(!line.empty()) badwords.push_back(line);
				});
				// Если чёрный список получен, устанавливаем его
				if(!badwords.empty()) toolkit.addBadwords(badwords);
			}
			// Если адрес файла белого списка получен
			if((value = env.get("goodwords")) != nullptr){
				// Белый список слов
				vector <string> goodwords;
				// Выполняем считывание всех слов для белого списка
				fsys_t::rfile(value, [&goodwords, &toolkit](const string & line, const uintmax_t fileSize){
					// Если текст получен
					if(!line.empty()) goodwords.push_back(line);
				});
				// Если белый список получен, устанавливаем его
				if(!goodwords.empty()) toolkit.addGoodwords(goodwords);
			}
			// Если неизвестное слово получено
			if((value = env.get("unknown-word")) != nullptr) toolkit.setUnknown(value);
			// Если пользовательские признаки получены
			if(((value = env.get("usigns")) != nullptr) && (string(value).compare("-yes-") != 0)){
				// Список пользовательских признаков
				vector <wstring> signs;
				// Выполняем извлечение пользовательских признаков
				alphabet.split(value, "|", signs);
				// Если список признаков получен
				if(!signs.empty()){
					// Если адрес скрипта получен
					if((value = env.get("usign-script")) != nullptr){
						// Устанавливаем адрес скрипта
						toolkit.setUsignScript(value);
						// Переходим по всему списку признаков
						for(auto & item : signs) toolkit.setUsign(alphabet.convert(item));
					}
				}
			}
			// Если адрес скрипта получен
			if((value = env.get("word-script")) != nullptr) toolkit.setWordScript(value);
			// Если нужно использовать бинарный контейнер
			if(!binDictFile.empty()){
				// Создаём бинарный контейнер
				ablm_t ablm(binDictFile, &toolkit, &alphabet, env.get("log"));
				// Если метаданные переданы
				if(((value = env.get("r-bin-meta")) != nullptr) && fsys_t::isfile(value)){
					// Данные в формате json
					string data = "";
					// Выполняем считывание всех строк текста
					fsys_t::rfile(realpath(value, nullptr), [&data](const string & line, const uintmax_t fileSize){
						// Добавляем полученные строки
						data.append(line);
					});
					// Если скрипт получен
					if(!data.empty()) ablm.setMeta(json::parse(data));
				}
				// Устанавливаем флаг отладки
				if(debug == 1) ablm.setFlag(ablm_t::flag_t::debug);
				// Выполняем инициализацию словаря
				ablm.init();
				// Если отладка включена, выводим индикатор загрузки
				if(debug > 0){
					// Устанавливаем заголовки прогресс-бара
					pss.title("Read dictionary", "Read dictionary is done");
					// Выводим индикатор прогресс-бара
					switch(debug){
						case 1: pss.update(); break;
						case 2: pss.status(); break;
					}
				}
				// Выполняем чтение бинарных данных
				ablm.read([debug, &pss](const u_short status){
					// Отображаем ход процесса
					switch(debug){
						case 1: pss.update(status); break;
						case 2: pss.status(status); break;
					}
				}, env.is("method", "info"));
				// Если это запрос информации о словаре
				if(env.is("method", "info")){
					// Выводим информацию о словаре
					ablm.info();
					// Выходим из приложения∂
					exit(0);
				}
			// Иначе выполняем инициализацию алгоритма сглаживания
			} else if(env.is("smoothing")) {
				// Если это WittenBell
				if(env.is("smoothing", "wittenbell")) toolkit.init(toolkit_t::algorithm_t::wittenBell, false, false, 0.0);
				// Если это AddSmooth
				else if(env.is("smoothing", "addsmooth")) toolkit.init(toolkit_t::algorithm_t::addSmooth, false, false, mod);
				// Если это GoodTuring
				else if(env.is("smoothing", "goodturing")) toolkit.init(toolkit_t::algorithm_t::goodTuring, false, false, 0.0);
				// Если это ConstDiscount
				else if(env.is("smoothing", "cdiscount")) toolkit.init(toolkit_t::algorithm_t::constDiscount, false, false, mod);
				// Если это NaturalDiscount
				else if(env.is("smoothing", "ndiscount")) toolkit.init(toolkit_t::algorithm_t::naturalDiscount, false, false, 0.0);
				// Если это KneserNey
				else if(env.is("smoothing", "kneserney")) toolkit.init(toolkit_t::algorithm_t::kneserNey, env.is("kneserney-modified"), env.is("kneserney-prepares"), 0.0);
				// Если это ModKneserNey
				else if(env.is("smoothing", "mkneserney")) toolkit.init(toolkit_t::algorithm_t::modKneserNey, env.is("kneserney-modified"), env.is("kneserney-prepares"), 0.0);
				// Сообщаем что сглаживание выбрано не верно
				else print("smoothing is bad", env.get("log"));
			// Сообщаем что сглаживание выбрано не верно
			} else print("smoothing is bad", env.get("log"));
			// Замеряем время начала работы
			auto timeShifting = chrono::system_clock::now();
			// Если передан метод обучения
			if(env.is("method", "train")){
				// Если нужно использовать бинарный контейнер
				if(!binDictFile.empty()){
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Train arpa", "Train arpa is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем обучение
					toolkit.train([debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				// Иначе продолжаем стандартное обучение
				} else {
					// Если путь получен
					if(((value = env.get("path")) != nullptr) && fsys_t::isdir(value)){
						// Идентификатор документа
						size_t idd = 0, size = 0;
						// Статус и процентное соотношение
						u_short status = 0, rate = 100;
						// Запоминаем путь к файлам
						const string path = realpath(value, nullptr);
						// Расширение файлов текстового корпуса
						const string ext = ((value = env.get("ext")) != nullptr ? value : "txt");
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Устанавливаем заголовки прогресс-бара
							pss.title("Load text corpus", "Load text corpus is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Переходим по всему списку файлов в каталоге
						fsys_t::rdir(path, ext, [&idd, &rate, &status, &size, debug, &pss, &toolkit](const string & filename, const uintmax_t dirSize){
							// Выполняем считывание всех строк текста
							fsys_t::rfile(filename, [idd, &rate, &status, &size, dirSize, debug, &pss, &toolkit](const string & text, const uintmax_t fileSize){
								// Если текст получен
								if(!text.empty()) toolkit.addText(text, idd);
								// Если отладка включена
								if(debug > 0){
									// Общий полученный размер данных
									size += text.size();
									// Подсчитываем статус выполнения
									status = u_short(size / float(dirSize) * 100.0f);
									// Если процентное соотношение изменилось
									if(rate != status){
										// Запоминаем текущее процентное соотношение
										rate = status;
										// Отображаем ход процесса
										switch(debug){
											case 1: pss.update(status); break;
											case 2: pss.status(status); break;
										}
									}
								}
							});
							// Увеличиваем идентификатор документа
							idd++;
						});
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Очищаем предыдущий прогресс-бар
							pss.clear();
							// Устанавливаем заголовки прогресс-бара
							pss.title("Train arpa", "Train arpa is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Выполняем обучение
						toolkit.train([debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					// Если файл корпуса получен
					} else if(((value = env.get("corpus")) != nullptr) && fsys_t::isfile(value)){
						// Идентификатор документа
						size_t size = 0;
						// Статус и процентное соотношение
						u_short status = 0, rate = 100;
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Устанавливаем заголовки прогресс-бара
							pss.title("Load text corpus", "Load text corpus is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Выполняем считывание всех строк текста
						fsys_t::rfile(value, [&rate, &status, &size, debug, &pss, &toolkit](const string & text, const uintmax_t fileSize){
							// Если текст получен
							if(!text.empty()) toolkit.addText(text, 0);
							// Если отладка включена
							if(debug > 0){
								// Общий полученный размер данных
								size += text.size();
								// Подсчитываем статус выполнения
								status = u_short(size / float(fileSize) * 100.0f);
								// Если процентное соотношение изменилось
								if(rate != status){
									// Запоминаем текущее процентное соотношение
									rate = status;
									// Отображаем ход процесса
									switch(debug){
										case 1: pss.update(status); break;
										case 2: pss.status(status); break;
									}
								}
							}
						});
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Очищаем предыдущий прогресс-бар
							pss.clear();
							// Устанавливаем заголовки прогресс-бара
							pss.title("Train arpa", "Train arpa is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Выполняем обучение
						toolkit.train([debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					// Если путь не указан
					} else print("path or file with corpus texts is not specified", env.get("log"));
				}
			// Проверяем правильно ли указаны адреса файлов
			} else if(((env.is("r-map") || env.is("r-maps")) &&
			(env.is("r-vocab") || env.is("r-vocabs"))) || (env.is("r-ngram") ||
			env.is("r-ngrams")) || (env.is("r-arpa") || env.is("r-arpas")) || !binDictFile.empty()) {
				// Если требуется загрузить файл n-грамм
				if(((value = env.get("r-ngram")) != nullptr) && fsys_t::isfile(value)){
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Read n-gram file", "Read n-gram file is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем загрузку файла n-грамм
					toolkit.readNgram(realpath(value, nullptr), [debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				// Если требуется загрузить список файлов n-грамм
				} else if(((value = env.get("r-ngrams")) != nullptr) && fsys_t::isdir(value)) {
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Read n-grams files", "Read n-grams files is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем загрузку файлов n-грамм
					toolkit.readNgrams(realpath(value, nullptr), [debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				}
				// Если требуется загрузить arpa
				if(((value = env.get("r-arpa")) != nullptr) && fsys_t::isfile(value)){
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Read arpa file", "Read arpa file is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем загрузку файла arpa
					toolkit.readArpa(realpath(value, nullptr), [debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				// Если нужно загрузить список файлов arpa
				} else if(((value = env.get("r-arpas")) != nullptr) && fsys_t::isdir(value)) {
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Read arpa files", "Read arpa files is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем загрузку файла arpa
					toolkit.readArpas(realpath(value, nullptr), [debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				}
				// Если требуется загрузить файл словаря vocab
				if(((value = env.get("r-vocab")) != nullptr) && fsys_t::isfile(value)){
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Read vocab file", "Read vocab file is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем загрузку файла словаря vocab
					toolkit.readVocab(realpath(value, nullptr), [debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				// Если требуется загрузить список словарей
				} else if(((value = env.get("r-vocabs")) != nullptr) && fsys_t::isdir(value)) {
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Read vocabs files", "Read vocabs files is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Переходим по всему списку словарей в каталоге
					fsys_t::rdir(realpath(value, nullptr), "vocab", [debug, &pss, &toolkit](const string & filename, const uintmax_t dirSize){
						// Выполняем загрузку файла словаря vocab
						toolkit.readVocab(filename, [debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					});
				}
				// Если требуется загрузить карту последовательности или список карт последовательностей
				if((env.is("r-map") || env.is("r-maps")) && (env.is("r-vocab") || env.is("r-vocabs"))){
					// Если нужно загрузить карту последовательности
					if(((value = env.get("r-map")) != nullptr) && fsys_t::isfile(value)){
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Очищаем предыдущий прогресс-бар
							pss.clear();
							// Устанавливаем заголовки прогресс-бара
							pss.title("Read map file", "Read map file is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Считываем карту последовательности
						toolkit.readMap(realpath(value, nullptr), [debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					// Если нужно загрузить список карт последовательностей
					} else if(((value = env.get("r-maps")) != nullptr) && fsys_t::isdir(value)){
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Очищаем предыдущий прогресс-бар
							pss.clear();
							// Устанавливаем заголовки прогресс-бара
							pss.title("Read maps files", "Read maps files is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Считываем список карт последовательностей
						toolkit.readMaps(realpath(value, nullptr), [debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					}
				}
				// Если конфигурация файлов верная и требуется обучение
				if(env.is("r-map") || env.is("r-maps") || env.is("r-ngram") || env.is("r-ngrams")){
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Train arpa", "Train arpa is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем обучение
					toolkit.train([debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				}
				// Если передан метод исправления arpa
				if(env.is("method", "repair")){
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Repair arpa", "Repair arpa is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем исправление arpa файла
					toolkit.repair([debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				// Если это метод удаление редких n-грамм
				} else if(env.is("method", "sweep")) {
					// Если отладка включена, выводим индикатор загрузки
					if(debug > 0){
						// Очищаем предыдущий прогресс-бар
						pss.clear();
						// Устанавливаем заголовки прогресс-бара
						pss.title("Sweep arpa", "Sweep arpa is done");
						// Выводим индикатор прогресс-бара
						switch(debug){
							case 1: pss.update(); break;
							case 2: pss.status(); break;
						}
					}
					// Выполняем удаление редких n-грамм
					toolkit.sweep([debug, &pss](const u_short status){
						// Отображаем ход процесса
						switch(debug){
							case 1: pss.update(status); break;
							case 2: pss.status(status); break;
						}
					});
				// Если нужно выполнить прунинг arpa
				} else if(env.is("method", "prune")) {
					// Максимальный размер n-граммы
					u_short size = 0;
					// Коэффициент прунинга
					float prune = 0.0f;
					// Если параметр прунинга получен
					if((value = env.get("prune-threshold")) != nullptr) prune = stof(value);
					// Если параметр максимального размера n-граммы для прунинга получен
					if((value = env.get("prune-max-gram")) != nullptr) size = stoi(value);
					// Если параметры получены
					if((size > 0) && (prune != 0.0f)){
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Очищаем предыдущий прогресс-бар
							pss.clear();
							// Устанавливаем заголовки прогресс-бара
							pss.title("Prune arpa", "Prune arpa is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Выполняем прунинг
						toolkit.prune(prune, size, [debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					}
				// Если нужно модифицировать arpa
				} else if(env.is("method", "modify")) {
					// Флаг модификации
					toolkit_t::modify_t modify;
					// Если флаг передан
					if(env.is("modify")){
						// Если это флаг добавления n-грамм
						if(env.is("modify", "emplace")) modify = toolkit_t::modify_t::emplace;
						// Если это флаг удаления n-грамм
						else if(env.is("modify", "remove")) modify = toolkit_t::modify_t::remove;
						// Если это флаг изменения n-грамм
						else if(env.is("modify", "change")) modify = toolkit_t::modify_t::change;
						// Если это флаг замены n-грамм
						else if(env.is("modify", "replace")) modify = toolkit_t::modify_t::replace;
						// Иначе выходим
						else print("modify flag is broken", env.get("log"));
					// Сообщаем что флаг не установлен
					} else print("modify flag is not set", env.get("log"));
					// Если файл передан
					if((value = env.get("modify-file")) != nullptr){
						// Если отладка включена, выводим индикатор загрузки
						if(debug > 0){
							// Очищаем предыдущий прогресс-бар
							pss.clear();
							// Устанавливаем заголовки прогресс-бара
							pss.title("Modify arpa", "Modify arpa is done");
							// Выводим индикатор прогресс-бара
							switch(debug){
								case 1: pss.update(); break;
								case 2: pss.status(); break;
							}
						}
						// Выполняем модификацию файла
						toolkit.modifyArpa(value, modify, [debug, &pss](const u_short status){
							// Отображаем ход процесса
							switch(debug){
								case 1: pss.update(status); break;
								case 2: pss.status(status); break;
							}
						});
					// Сообщаем что файл модификации не передан
					} else print("file modify not found", env.get("log"));
				}
			// Выводим сообщение что файлы не переданы
			} else print("arpa file is not loaded", env.get("log"));
			// Если файл для извлечения карты последовательности передан
			if((env.is("method", "train") || env.is("r-map") || env.is("r-maps") || env.is("r-ngram") ||
			env.is("r-ngrams") || !binDictFile.empty()) && ((value = env.get("w-map")) != nullptr)){
				// Если отладка включена, выводим индикатор загрузки
				if(debug > 0){
					// Очищаем предыдущий прогресс-бар
					pss.clear();
					// Устанавливаем заголовки прогресс-бара
					pss.title("Write map", "Write map is done");
					// Выводим индикатор прогресс-бара
					switch(debug){
						case 1: pss.update(); break;
						case 2: pss.status(); break;
					}
				}
				// Выполняем сохранение каты последовательности
				toolkit.writeMap(value, [debug, &pss](const u_short status){
					// Отображаем ход процесса
					switch(debug){
						case 1: pss.update(status); break;
						case 2: pss.status(status); break;
					}
				});
			}
			// Если файл для сохранения arpa передан
			if((value = env.get("w-arpa")) != nullptr){
				// Если отладка включена, выводим индикатор загрузки
				if(debug > 0){
					// Очищаем предыдущий прогресс-бар
					pss.clear();
					// Устанавливаем заголовки прогресс-бара
					pss.title("Write arpa", "Write arpa is done");
					// Выводим индикатор прогресс-бара
					switch(debug){
						case 1: pss.update(); break;
						case 2: pss.status(); break;
					}
				}
				// Выполняем сохранение arpa файла
				toolkit.writeArpa(value, [debug, &pss](const u_short status){
					// Отображаем ход процесса
					switch(debug){
						case 1: pss.update(status); break;
						case 2: pss.status(status); break;
					}
				});
			}
			// Если файл для сохранения vocab передан
			if((value = env.get("w-vocab")) != nullptr){
				// Если отладка включена, выводим индикатор загрузки
				if(debug > 0){
					// Очищаем предыдущий прогресс-бар
					pss.clear();
					// Устанавливаем заголовки прогресс-бара
					pss.title("Write vocab", "Write vocab is done");
					// Выводим индикатор прогресс-бара
					switch(debug){
						case 1: pss.update(); break;
						case 2: pss.status(); break;
					}
				}
				// Выполняем извлечение словаря в файл
				toolkit.writeVocab(value, [debug, &pss](const u_short status){
					// Отображаем ход процесса
					switch(debug){
						case 1: pss.update(status); break;
						case 2: pss.status(status); break;
					}
				});
			}
			// Если файл для сохранения n-грамм передан
			if((env.is("method", "train") || env.is("r-map") || env.is("r-maps") || env.is("r-ngram") ||
			env.is("r-ngrams") || !binDictFile.empty()) && ((value = env.get("w-ngram")) != nullptr)){
				// Если отладка включена, выводим индикатор загрузки
				if(debug > 0){
					// Очищаем предыдущий прогресс-бар
					pss.clear();
					// Устанавливаем заголовки прогресс-бара
					pss.title("Write ngrams", "Write ngrams is done");
					// Выводим индикатор прогресс-бара
					switch(debug){
						case 1: pss.update(); break;
						case 2: pss.status(); break;
					}
				}
				// Выполняем сохранение файлов n-грамм
				toolkit.writeNgrams(value, [debug, &pss](const u_short status){
					// Отображаем ход процесса
					switch(debug){
						case 1: pss.update(status); break;
						case 2: pss.status(status); break;
					}
				});
			}
			// Если нужно использовать бинарный контейнер
			if((value = env.get("w-bin")) != nullptr){
				// Создаём бинарный контейнер
				ablm_t ablm(value, &toolkit, &alphabet, env.get("log"));
				// Если метаданные переданы
				if(((value = env.get("w-bin-meta")) != nullptr) && fsys_t::isfile(value)){
					// Данные в формате json
					string data = "";
					// Выполняем считывание всех строк текста
					fsys_t::rfile(realpath(value, nullptr), [&data](const string & line, const uintmax_t fileSize){
						// Добавляем полученные строки
						data.append(line);
					});
					// Если скрипт получен
					if(!data.empty()) ablm.setMeta(json::parse(data));
				}
				// Устанавливаем флаг отладки
				if(debug == 1) ablm.setFlag(ablm_t::flag_t::debug);
				// Устанавливаем флаг сохранения только arpa данных
				if(env.is("w-bin-arpa")) ablm.setFlag(ablm_t::flag_t::onlyArpa);
				// Устанавливаем флаг экспорта пользовательских признаков
				if(env.is("w-bin-usigns")) ablm.setFlag(ablm_t::flag_t::expUsigns);
				// Устанавливаем флаг экспорта опций тулкита
				if(env.is("w-bin-options")) ablm.setFlag(ablm_t::flag_t::expOptions);
				// Устанавливаем флаг экспорта скрипта предобработки текста
				if(env.is("w-bin-preword")) ablm.setFlag(ablm_t::flag_t::expPreword);
				// Устанавливаем флаг экспорта чёрного списка слов
				if(env.is("w-bin-badwords")) ablm.setFlag(ablm_t::flag_t::expBadwords);
				// Устанавливаем флаг экспорта белого списка слов
				if(env.is("w-bin-goodwords")) ablm.setFlag(ablm_t::flag_t::expGoodwords);
				// Выполняем инициализацию словаря
				ablm.init();
				// Если отладка включена, выводим индикатор загрузки
				if(debug > 0){
					// Устанавливаем заголовки прогресс-бара
					pss.title("Write dictionary", "Write dictionary is done");
					// Выводим индикатор прогресс-бара
					switch(debug){
						case 1: pss.update(); break;
						case 2: pss.status(); break;
					}
				}
				// Выполняем запись бинарных данных
				ablm.write([debug, &pss](const u_short status){
					// Отображаем ход процесса
					switch(debug){
						case 1: pss.update(status); break;
						case 2: pss.status(status); break;
					}
				});
			}
			// Если режим отладки включён
			if(debug > 0){
				// Формируем строку результата времени работы
				const string & result = alphabet.format("work time shifting: %u seconds", chrono::duration_cast <chrono::seconds> (chrono::system_clock::now() - timeShifting).count());
				// Выводим результат
				print(result, env.get("log"), alphabet_t::log_t::info, false);
			}
		// Сообщаем что файл алфавита не найден
		} else print("file alphabet not found", env.get("log"));
	}
	// Успешно выходим
	return 0;
}
