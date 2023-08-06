#pragma once

#include <iostream>
#include <string>
#include <pqxx/pqxx>

//#include "ShellAPI.h"

#if _WINDOWS
#include <Windows.h>
#include <stringapiset.h>
#endif

#include "DatabaseClients.h"

enum class e_main_menu {
	exit,
	DB_list,
	createDB,
	connectToDB
};

#if _WINDOWS
std::string cp1251_to_utf8(const char* str);
#endif

void print_title();
void creat_db();
void connect_to_db();
