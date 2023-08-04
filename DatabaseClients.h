#pragma once

#include <string>
#include <vector>


class DatabaseClients final {
public:
	DatabaseClients();
	~DatabaseClients();

	DatabaseClients(const DatabaseClients& other) = delete;
	DatabaseClients(DatabaseClients&& other) noexcept = delete;
	DatabaseClients& operator=(const DatabaseClients& other) = delete;
	DatabaseClients& operator=(DatabaseClients&& other) noexcept = delete;

	void createDB();
	void addClient();
	void addClientPhone();
	void changeClient();
	void deleteClientPhone();
	void deleteClient();
	void findClient();

private:
	std::string name;
	std::string surname;
	std::string email;
	std::vector<int> phone;
};
