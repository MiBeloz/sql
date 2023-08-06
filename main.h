#pragma once

#include <iostream>
#include <string>
#include <pqxx/pqxx>

#if _WINDOWS
#include <Windows.h>
#include <stringapiset.h>
#endif

#include "DatabaseClients.h"

enum class e_main_menu {
	exit,
	DB_list,
	createDB,
	deleteDB,
	connectToDB
};

#if _WINDOWS
std::string cp1251_to_utf8(const char* str);
#endif

void print_title();
void show_db();
void Hide();
void create_db();
void delete_db();
void connect_to_db();
