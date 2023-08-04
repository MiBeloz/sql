#include <iostream>
#include <pqxx/pqxx>

#include "DatabaseClients.h"


int main(){
	

	//system("chcp UTF8");
	//SetConsoleCP(CP_UTF8);

	std::string ff;
	std::cin >> ff;

	setlocale(LC_ALL, "ru_RU.UTF-8");
	
	try {
		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=DBclients "
			"user=postgres "
			"password=oven57jpm");

		pqxx::work tx(c);
		for (const auto& [name, surname, email] : tx.query<std::string, std::string, std::string>("SELECT name, surname, email FROM client")) {
			std::cout << "Имя: " << name << std::endl;
			std::cout << "Фамилия: " << surname << std::endl;
			std::cout << "email: " << email << std::endl;
			std::cout << std::endl;
		}

		//tx.exec("INSERT INTO client VALUES(3, 'Валентина', 'Белозерова', 'valushka@mail.ru')");
		tx.commit();

		pqxx::work tx2(c);
		//tx2.exec("UPDATE client SET email='belozerova.vv@omsk.gazprom-neft.ru' where email='valushka@mail.ru'");
		tx2.exec("UPDATE client SET email='" + ff + "' where email='Валентина'");
		tx2.commit();
		
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	
	
	system("pause > nul");
	return 0;
}















//CREATE TABLE IF NOT EXISTS Client(
//	id SERIAL PRIMARY KEY,
//	name text NOT NULL,
//	surname text NOT NULL,
//	email text UNIQUE NOT null
//);
//
//CREATE TABLE IF NOT EXISTS Phone(
//	id SERIAL PRIMARY KEY,
//	number text UNIQUE NOT NULL
//);
//
//CREATE TABLE IF NOT EXISTS ClientPhone(
//	client_id INTEGER REFERENCES Client(id),
//	phone_id INTEGER REFERENCES Phone(id),
//	CONSTRAINT pk_ClientPhone PRIMARY KEY(client_id, phone_id)
//);
//
//
//INSERT INTO Client(name, surname, email)
//VALUES('Михаил', 'Белозеров', 'mihabeloz@gmail.com'), ('Татьяна', 'Белозерова', 't.kytuzova@gmail.com');
//
//INSERT INTO Phone(number)
//VALUES('89083179589'), ('89059404572'), ('89609908802');
//
//INSERT INTO ClientPhone(client_id, phone_id)
//VALUES(1, 1), (1, 2), (2, 3);
