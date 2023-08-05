#include <iostream>
#include <pqxx/pqxx>

#include <Windows.h>
#include <stringapiset.h>

#include "DatabaseClients.h"


std::string cp1251_to_utf8(const char* str);

int main(){
	setlocale(LC_ALL, "ru_RU.UTF-8");
	SetConsoleCP(1251);
	std::string ggg;
	std::cin >> ggg;

	ggg = cp1251_to_utf8(ggg.c_str());
	
	try {
		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=clients "
			"user=postgres "
			"password=oven57jpm");

		pqxx::work tx(c);
		for (const auto& [name, surname, email] : tx.query<std::string, std::string, std::string>("select name, surname, email from client")) {
			std::cout << "Имя: " << name << std::endl;
			std::cout << "Фамилия: " << surname << std::endl;
			std::cout << "email: " << email << std::endl;
			std::cout << std::endl;
		}

		//tx.exec("insert into client values(3, 'валентина', 'белозерова', 'valushka@mail.ru')");
		tx.commit();

		pqxx::work tx2(c);
		//tx2.exec("update client set email='belozerova.vv@omsk.gazprom-neft.ru' where email='valushka@mail.ru'");
		tx2.exec("update client set email='" + ggg + "' where email='ggg'");
		tx2.commit();
		
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	
	
	system("pause > nul");
	return 0;
}

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
