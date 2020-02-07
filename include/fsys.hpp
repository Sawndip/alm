/**
 *  author:   Yuriy Lobarev
 *  telegram: @forman
 *  phone:    +7(910)983-95-90
 *  email:    forman@anyks.com
 *  site:     https://anyks.com
 */

#ifndef _ANYKS_FSYS_
#define _ANYKS_FSYS_

/**
 * Стандартная библиотека
 */
#include <string>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <unistd.h>
#include <functional>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
// Если это clang v10 или выше
#if defined(__clang__) && (__clang_major__ > 9)
#include <filesystem>
#endif

/**
 * Наши модули
 */
#include <alphabet.hpp>

// Устанавливаем область видимости
using namespace std;

/**
 * anyks пространство имён
 */
namespace anyks {
	/**
	 * FSys Класс модуля работы с каталогами
	 */
	typedef struct FSys {
		/**
		 * mkdir Функция рекурсивного создания каталогов
		 * @param path адрес каталогов
		 */
		static void mkdir(const string & path){
			// Если путь передан
			if(!path.empty()){
				// Буфер с названием каталога
				char tmp[256];
				// Указатель на сепаратор
				char * p = nullptr;
				// Копируем переданный адрес в буфер
				snprintf(tmp, sizeof(tmp), "%s", path.c_str());
				// Определяем размер адреса
				size_t len = strlen(tmp);
				// Если последний символ является сепаратором тогда удаляем его
				if(tmp[len - 1] == '/') tmp[len - 1] = 0;
				// Переходим по всем символам
				for(p = tmp + 1; * p; p++){
					// Если найден сепаратор
					if(* p == '/'){
						// Сбрасываем указатель
						* p = 0;
						// Создаем каталог
						::mkdir(tmp, S_IRWXU);
						// Запоминаем сепаратор
						* p = '/';
					}
				}
				// Создаем последний каталог
				::mkdir(tmp, S_IRWXU);
			}
		}
		/**
		 * rmdir Функция удаления каталога и всего содержимого
		 * @param  path путь до каталога
		 * @return      количество дочерних элементов
		 */
		static const int rmdir(const string & path){
			// Результат работы функции
			int result = -1;
			// Если путь передан
			if(!path.empty()){
				try {
					// Открываем указанный каталог
					DIR * dir = opendir(path.c_str());
					// Если каталог открыт
					if(dir != nullptr){
						// Устанавливаем количество дочерних элементов
						result = 0;
						// Создаем указатель на содержимое каталога
						struct dirent * ptr = nullptr;
						// Выполняем чтение содержимого каталога
						while(!result && (ptr = readdir(dir))){
							// Количество найденных элементов
							int res = -1;
							// Пропускаем названия текущие "." и внешние "..", так как идет рекурсия
							if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;
							// Получаем размер дочернего каталога
							const size_t length = (path.length() + strlen(ptr->d_name) + 2);
							// Создаем буфер данных
							char * buffer = new char [length];
							// Если память выделена
							if(buffer != nullptr){
								// Создаем структуру буфера статистики
								struct stat statbuf;
								// Заполняем нулями буфер
								memset(buffer, 0 , length);
								// Копируем в буфер название дочернего элемента
								snprintf(buffer, length, "%s/%s", path.c_str(), ptr->d_name);
								// Если статистика извлечена
								if(!stat(buffer, &statbuf)){
									// Если дочерний элемент является дирректорией
									if(S_ISDIR(statbuf.st_mode)) res = rmdir(string(buffer, length));
									// Если дочерний элемент является файлом то удаляем его
									else res = ::unlink(buffer);
								}
							}
							// Освобождаем выделенную ранее память
							delete [] buffer;
							// Запоминаем количество дочерних элементов
							result = res;
						}
						// Закрываем открытый каталог
						closedir(dir);
					}
					// Удаляем последний каталог
					if(!result) result = ::rmdir(path.c_str());
				// Если происходит ошибка то игнорируем её
				} catch(const bad_alloc &) {
					// Выводим сообщение об ошибке
					cerr << "error: bad alloc for recursive rm dir" << endl;
					// Выходим из приложения
					exit(EXIT_FAILURE);
				}
			}
			// Выводим результат
			return result;
		}
		/**
		 * getuid Функция вывода идентификатора пользователя
		 * @param  name имя пользователя
		 * @return      полученный идентификатор пользователя
		 */
		static const uid_t getuid(const string & name){
			// Получаем идентификатор имени пользователя
			struct passwd * pwd = getpwnam(name.c_str());
			// Если идентификатор пользователя не найден
			if(pwd == nullptr){
				// Выводим сообщение об ошибке
				printf("failed to get userId from username [%s]\n", name.c_str());
				// Сообщаем что ничего не найдено
				return 0;
			}
			// Выводим идентификатор пользователя
			return pwd->pw_uid;
		}
		/**
		 * getgid Функция вывода идентификатора группы пользователя
		 * @param  name название группы пользователя
		 * @return      полученный идентификатор группы пользователя
		 */
		static const gid_t getgid(const string & name){
			// Получаем идентификатор группы пользователя
			struct group * grp = getgrnam(name.c_str());
			// Если идентификатор группы не найден
			if(grp == nullptr){
				// Выводим сообщение об ошибке
				printf("failed to get groupId from groupname [%s]\n", name.c_str());
				// Сообщаем что ничего не найдено
				return 0;
			}
			// Выводим идентификатор группы пользователя
			return grp->gr_gid;
		}
		/**
		 * isdir Функция проверяющий существование дирректории
		 * @param  name адрес дирректории
		 * @return      результат проверки
		 */
		static const bool isdir(const string & name){
			// Результат проверки
			bool result = false;
			// Если адрес дирректории передан
			if(!name.empty()){
				// Структура проверка статистики
				struct stat info;
				// Проверяем переданный нам адрес
				result = ((stat(name.c_str(), &info) == 0) ? ((info.st_mode & S_IFDIR) != 0) : result);
			}
			// Выводим результат
			return result;
		}
		/**
		 * isfile Функция проверяющий существование файла
		 * @param  name адрес файла
		 * @return      результат проверки
		 */
		static const bool isfile(const string & name){
			// Результат проверки
			bool result = false;
			// Если адрес файла передан
			if(!name.empty()){
				// Структура проверка статистики
				struct stat info;
				// Проверяем переданный нам адрес
				result = ((stat(name.c_str(), &info) == 0) ? ((info.st_mode & S_IFMT) != 0) : result);
			}
			// Выводим результат
			return result;
		}
		/**
		 * issock Функция проверки существования сокета
		 * @param  name адрес сокета
		 * @return      результат проверки
		 */
		static const bool issock(const string & name){
			// Результат проверки
			bool result = false;
			// Если адрес файла передан
			if(!name.empty()){
				// Структура проверка статистики
				struct stat info;
				// Проверяем переданный нам адрес
				result = ((stat(name.c_str(), &info) == 0) ? ((info.st_mode & S_IFSOCK) != 0) : result);
			}
			// Выводим результат
			return result;
		}
// Если это clang v10 или выше
#if defined(__clang__) && (__clang_major__ > 9)
		/**
		 * dsize Функция подсчёта размера каталога
		 * @param path путь для подсчёта
		 * @param ext  расширение файла по которому идет фильтрация
		 * @return     размер каталога в байтах
		 */
		static const uintmax_t dsize(const string & path, const string & ext){
			// Результат работы функции
			uintmax_t result = 0;
			// Если адрес каталога и расширение файлов переданы
			if(!path.empty() && !ext.empty() && isdir(path)){
				// Устанавливаем область видимости
				namespace fs = std::__fs::filesystem;
				// Устанавливаем путь поиска
				fs::path dirpath = path;
				// Выполняем рекурсивный переход по всем подкаталогам
				for(auto && entry : fs::recursive_directory_iterator(dirpath, fs::directory_options::skip_permission_denied)){
					// Возможная ошибка
					error_code ignore_error;
					// Запрашиваем файл из каталога и считаем его размер
					if(fs::is_regular_file(fs::symlink_status(entry, ignore_error))){
						// Получаем путь файла
						fs::path fsp = entry.path();
						// Если расширение файла соответствует
						if(string(fsp.extension().c_str()).rfind(ext) != string::npos) result += fs::file_size(entry);
					}
				}
			}
			// Выводим результат
			return result;
		}
// Если это gcc
#else
		/**
		 * dsize Функция подсчёта размера каталога
		 * @param path путь для подсчёта
		 * @param ext  расширение файла по которому идет фильтрация
		 * @return     размер каталога в байтах
		 */
		static const uintmax_t dsize(const string & path, const string & ext){
			// Результат работы функции
			uintmax_t result = 0;
			// Если адрес каталога и расширение файлов переданы
			if(!path.empty() && !ext.empty() && isdir(path)){
				// Открываем указанный каталог
				DIR * dir = opendir(path.c_str());
				// Если каталог открыт
				if(dir != nullptr){
					// Структура проверка статистики
					struct stat info;
					// Создаём объект алфавита
					alphabet_t alphabet;
					// Получаем длину адреса
					const size_t length = path.size();
					// Создаем указатель на содержимое каталога
					struct dirent * ptr = nullptr;
					// Выполняем чтение содержимого каталога
					while((ptr = readdir(dir))){
						// Пропускаем названия текущие "." и внешние "..", так как идет рекурсия
						if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;
						// Получаем адрес в виде строки
						const string & address = alphabet.format("%s/%s", path.c_str(), ptr->d_name);
						// Если статистика извлечена
						if(!stat(address.c_str(), &info)){
							// Если дочерний элемент является дирректорией
							if(S_ISDIR(info.st_mode)) result += dsize(address, ext);
							// Если дочерний элемент является файлом то удаляем его
							else {
								// Получаем расширение файла
								const string & extension = alphabet.format(".%s", ext.c_str());
								// Получаем длину адреса
								const size_t length = extension.length();
								// Если расширение файла найдено
								if(address.substr(address.length() - length, length).compare(extension) == 0){
									// Открываем файл на чтение
									ifstream file(address, ios::in);
									// Если файл открыт
									if(file.is_open()){
										// Перемещаем указатель в конец файла
										file.seekg(0, file.end);
										// Определяем размер файла
										result += file.tellg();
										// Возвращаем указатель обратно
										file.seekg(0, file.beg);
										// Закрываем файл
										file.close();
									}
								}
							}
						}
					}
					// Закрываем открытый каталог
					closedir(dir);
				}
			}
			// Выводим результат
			return result;
		}
#endif
		/**
		 * chown Функция установки владельца на каталог
		 * @param path  путь к файлу или каталогу для установки владельца
		 * @param user  данные пользователя
		 * @param group идентификатор группы
		 */
		static void chown(const string & path, const string & user, const string & group){
			// Если путь передан
			if(!path.empty() && !user.empty() && !group.empty()
			&& (realpath(path.c_str(), nullptr) != nullptr)){
				// Идентификатор пользователя
				uid_t uid = getuid(user);
				// Идентификатор группы
				gid_t gid = getgid(group);
				// Устанавливаем права на каталог
				if(uid && gid) ::chown(path.c_str(), uid, gid);
			}
		}
		/**
		 * makedir Функция создания каталога для хранения логов
		 * @param  path  адрес для каталога
		 * @param  user  данные пользователя
		 * @param  group идентификатор группы
		 * @return       результат создания каталога
		 */
		static const bool makedir(const string & path, const string & user, const string & group){
			// Проверяем существует ли нужный нам каталог
			if(!isdir(path)){
				// Создаем каталог
				mkdir(path);
				// Устанавливаем права на каталог
				chown(path, user, group);
				// Сообщаем что все удачно
				return true;
			}
			// Сообщаем что каталог и так существует
			return false;
		}
		/**
		 * rfile Функция рекурсивного получения всех строк файла
		 * @param filename адрес файла для чтения
		 * @param callback функция обратного вызова
		 */
		static void rfile(const string & filename, function <void (const string &, const uintmax_t)> callback){
			// Если адрес файла передан
			if(!filename.empty()){
				// Если файл существует
				if(isfile(filename)){
					// Создаем объект словаря
					alphabet_t alphabet;
					// Открываем файл на чтение
					ifstream file(filename, ios::binary);
					// Если файл открыт
					if(file.is_open()){
						// Строка чтения из файла
						string text;
						// Перемещаем указатель в конец файла
						file.seekg(0, file.end);
						// Определяем размер файла
						const uintmax_t size = file.tellg();
						// Возвращаем указатель обратно
						file.seekg(0, file.beg);
						// Считываем до тех пор пока все удачно
						while(file.good()){
							// Считываем строку из файла
							alphabet.readline(file, text);
							// Если текст получен
							if(!text.empty()) callback(text, size);
						}
						// Закрываем файл
						file.close();
					}
				// Выводим сообщение об ошибке
				} else cerr << "error: the file name: \"" << filename << "\" is not found" << endl;
			}
		}
// Если это clang v10 или выше
#if defined(__clang__) && (__clang_major__ > 9)
		/**
		 * rdir Функция рекурсивного получения файлов во всех подкаталогах
		 * @param path     путь до каталога
		 * @param ext      расширение файла по которому идет фильтрация
		 * @param callback функция обратного вызова
		 */
		static void rdir(const string & path, const string & ext, function <void (const string &, const uintmax_t)> callback){
			// Если адрес каталога и расширение файлов переданы
			if(!path.empty() && !ext.empty() && isdir(path)){
				// Устанавливаем область видимости
				namespace fs = std::__fs::filesystem;
				// Устанавливаем путь поиска
				fs::path dirpath = path;
				// Получаем полный размер каталога
				const uintmax_t size = dsize(path, ext);
				// Если размер каталога получен
				if(size > 0){
					// Выполняем рекурсивный переход по всем подкаталогам
					for(auto && entry : fs::recursive_directory_iterator(dirpath, fs::directory_options::skip_permission_denied)){
						// Возможная ошибка
						error_code ignore_error;
						// Запрашиваем файл из каталога и считаем его размер
						if(fs::is_regular_file(fs::symlink_status(entry, ignore_error))){
							// Получаем путь файла
							fs::path fsp = entry.path();
							// Если расширение файла соответствует
							if(string(fsp.extension().c_str()).rfind(ext) != string::npos){
								// Выводим полный путь файла
								callback(realpath(fsp.c_str(), nullptr), size);
							}
						}
					}
				// Сообщаем что каталог пустой
				} else callback("", 0);
			// Выводим сообщение об ошибке
			} else cerr << "error: the path name: \"" << path << "\" is not found" << endl;
		}
// Если это gcc
#else
		/**
		 * rdir Функция рекурсивного получения файлов во всех подкаталогах
		 * @param path     путь до каталога
		 * @param ext      расширение файла по которому идет фильтрация
		 * @param callback функция обратного вызова
		 */
		static void rdir(const string & path, const string & ext, function <void (const string &, const uintmax_t)> callback){
			// Если адрес каталога и расширение файлов переданы
			if(!path.empty() && !ext.empty() && isdir(path)){
				// Получаем полный размер каталога
				const uintmax_t sizeDir = dsize(path, ext);
				// Если размер каталога получен
				if(sizeDir > 0){
					// Открываем указанный каталог
					DIR * dir = opendir(path.c_str());
					// Если каталог открыт
					if(dir != nullptr){
						// Структура проверка статистики
						struct stat info;
						// Создаём объект алфавита
						alphabet_t alphabet;
						// Получаем длину адреса
						const size_t length = path.size();
						// Создаем указатель на содержимое каталога
						struct dirent * ptr = nullptr;
						// Выполняем чтение содержимого каталога
						while((ptr = readdir(dir))){
							// Пропускаем названия текущие "." и внешние "..", так как идет рекурсия
							if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;
							// Получаем адрес в виде строки
							const string & address = alphabet.format("%s/%s", path.c_str(), ptr->d_name);
							// Если статистика извлечена
							if(!stat(address.c_str(), &info)){
								// Если дочерний элемент является дирректорией
								if(S_ISDIR(info.st_mode)) rdir(address, ext, callback);
								// Если дочерний элемент является файлом то удаляем его
								else {
									// Получаем расширение файла
									const string & extension = alphabet.format(".%s", ext.c_str());
									// Получаем длину адреса
									const size_t length = extension.length();
									// Если расширение файла найдено
									if(address.substr(address.length() - length, length).compare(extension) == 0){
										// Выводим полный путь файла
										callback(address, sizeDir);
									}
								}
							}
						}
						// Закрываем открытый каталог
						closedir(dir);
					}
				// Сообщаем что каталог пустой
				} else callback("", 0);
			// Выводим сообщение об ошибке
			} else cerr << "error: the path name: \"" << path << "\" is not found" << endl;
		}
#endif
	} fsys_t;
};

#endif // _ANYKS_FSYS_
