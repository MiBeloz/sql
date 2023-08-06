#include "main.h"


int main(){
#if _WINDOWS
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
	
	while (true) {
		print_title();

		std::cout << "Выбирите действие:" << std::endl;
		std::cout <<
			"1 - Вывести список баз данных\n"
			"2 - Создать базу данных\n"
			"3 - Удалить базу данных\n"
			"4 - Подключиться к существующей базе данных\n"
			"0 - Выход\n"
			<< std::endl;
		int mn_select = 0;
		std::cin >> mn_select;
		while (mn_select < static_cast<int>(e_main_menu::exit) || mn_select > static_cast<int>(e_main_menu::connectToDB)) {
			std::cout << "Неккоректный ввод! Введите еще раз:" << std::endl;
			std::cin >> mn_select;
		}
		e_main_menu mn = static_cast<e_main_menu>(mn_select);

		if (mn == e_main_menu::exit) {
			break;
		}
		else if (mn == e_main_menu::DB_list) {
			show_db();
		}
		else if (mn == e_main_menu::createDB) {
			create_db();
		}
		else if (mn == e_main_menu::deleteDB) {
			delete_db();
		}
		else if (mn == e_main_menu::connectToDB) {
			connect_to_db();
		}
	}
	
	return 0;
}


#if _WINDOWS
std::string cp1251_to_utf8(const char* str) {
	std::string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (!result_u) { return ""; }
	wchar_t* ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return "";
	}
	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return "";
	}
	char* cres = new char[result_c];
	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return "";
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}
#endif

void print_title() {
#if _WINDOWS
	system("cls");
#else
	system("clear");
#endif

	std::cout << "\tРабота с PostgreSQL из C++\n\n" << std::endl;
}

void show_db() {
	std::string username, cmd;

	print_title();
	std::cout << "\tСписок баз данных\n" << std::endl;
	std::cout << "Введите имя пользователя(без пробелов): ";
	std::cin >> username;

	Hide();
	cmd = "psql -U " + username + " -l";
	system(cmd.c_str());

	std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
#if _WINDOWS
	system("pause > nul");
#else
	std::cin.get();
#endif
}

void Hide() {
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, 1);
}

void create_db() {
	std::string username, db_name, cmd;

	print_title();
	std::cout << "\tСоздание базы данных\n" << std::endl;
	std::cout << "Введите имя пользователя(без пробелов): ";
	std::cin >> username;
	std::cout << "Введите название базы данных(без пробелов): ";
	std::cin >> db_name;
	while (db_name == "postgres" || db_name == "template0" || db_name == "template1") {
		std::cout << "Базу данных с этим названием нельзя создать! Введите другое название: ";
		std::cin >> db_name;
	}
	std::cout << std::endl;

	Hide();
	cmd = "createdb -U " + username + ' ' + db_name;

	system(cmd.c_str());

	std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
#if _WINDOWS
	system("pause > nul");
#else
	std::cin.get();
#endif
}

void delete_db() {
	std::string username, db_name, cmd;

	print_title();
	std::cout << "\tУдаление базы данных\n" << std::endl;
	std::cout << "Введите имя пользователя(без пробелов): ";
	std::cin >> username;
	std::cout << "Введите название базы данных(без пробелов): ";
	std::cin >> db_name;
	while (db_name == "postgres" || db_name == "template0" || db_name == "template1") {
		std::cout << "Базу данных с этим названием нельзя удалить! Введите другое название: ";
		std::cin >> db_name;
	}
	std::cout << std::endl;

	Hide();
	cmd = "dropdb -U " + username + ' ' + db_name;

	system(cmd.c_str());

	std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
#if _WINDOWS
	system("pause > nul");
#else
	std::cin.get();
#endif
}

void connect_to_db() {
	std::string username, db_name, password, cmd;

	print_title();
	std::cout << "Введите имя пользователя(без пробелов): ";
	std::cin >> username;
	std::cout << "Введите название базы данных(без пробелов): ";
	std::cin >> db_name;
	std::cout << "Введите пароль(без пробелов): ";
	std::cin >> password;
	std::cout << std::endl;

	try {
		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=" + db_name + " "
			"user=" + username + " "
			"password=" + password);
		password = "";

		std::cout << "Подключение успешно установлено!" << std::endl;


		//pqxx::work tx(c);
		//for (const auto& [name, surname, email] : tx.query<std::string, std::string, std::string>("select name, surname, email from client")) {
		//	std::cout << "Имя: " << name << std::endl;
		//	std::cout << "Фамилия: " << surname << std::endl;
		//	std::cout << "email: " << email << std::endl;
		//	std::cout << std::endl;
		//}

		////tx.exec("insert into client values(3, 'Валентина', 'Белозерова', 'valushka@mail.ru')");
		//tx.commit();

		////pqxx::work tx2(c);
		////tx2.exec("update client set email='belozerova.vv@omsk.gazprom-neft.ru' where email='valushka@mail.ru'");
		////tx2.exec("update client set email='" + ggg + "' where email='ggg'");
		////tx2.commit();

#if _WINDOWS
		system("pause > nul");
#else
		std::cin.get();
#endif
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
#if _WINDOWS
		system("pause > nul");
#else
		std::cin.get();
#endif
	}
}















//create table if not exists client(
//	id serial primary key,
//	name text not null,
//	surname text not null,
//	email text unique not null
//);
//
//create table if not exists phone(
//	id serial primary key,
//	number text unique not null
//);
//
//create table if not exists clientphone(
//	client_id integer references client(id),
//	phone_id integer references phone(id),
//	constraint pk_clientphone primary key(client_id, phone_id)
//);
//
//
//insert into client(name, surname, email)
//values('михаил', 'белозеров', 'mihabeloz@gmail.com'), ('татьяна', 'белозерова', 't.kytuzova@gmail.com');
//
//insert into phone(number)
//values('89083179589'), ('89059404572'), ('89609908802');
//
//insert into clientphone(client_id, phone_id)
//values(1, 1), (1, 2), (2, 3);
