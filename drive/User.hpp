#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <iostream>
#include <vector>
#include "exception.hpp"
#include "Elements.hpp"
#define ADMIN "admin"
#define SUPERUSER "superuser"
#define FOLDER "folder"

enum Authority {normal, superuser, admin};
class Elements;

class User
{
public:
	User(std::string uname, std::string pword, Authority _authority);
	~User();
	std::string get_username();
	std::string get_password();
	std::string get_authority();
	bool if_superuser_or_admin();
	bool if_superuser();
	bool promote();
	bool demote();
	void set_current_elem(Elements* elem);
	Elements* get_current_elem();
	void set_source_elem(Elements* elem);
	bool set_dest_elem(Elements* elem);
	Elements* get_dest_elem();
	Elements* get_source_elem();

private:
	std::string username;
	std::string password;
	Authority authority = normal;
	Elements* current_elem;
	Elements* source_elem;
	Elements* dest_elem;
	
};

#endif