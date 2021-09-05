#include "User.hpp"
#define NORMAL "normal"
#define SUPERUSER "superuser"
#define ADMIN "admin"


User::User(std::string uname, std::string pword, Authority _authority)
{
	username = uname;
	password = pword;
	authority = _authority;
}

std::string User::get_username()
{
	return username;
}

std::string User::get_password()
{
	return password;
}

std::string User::get_authority()
{
	if(authority == normal)
		return NORMAL;
	else if(authority == superuser)
		return SUPERUSER;
	else if(authority == admin)
		return ADMIN;
}

bool User::if_superuser_or_admin()
{
	if(authority == superuser || authority == admin)
		return true;
	return false;
}

bool User::if_superuser()
{
	if(authority == superuser)
		return true;
	return false;
}

bool User::promote()
{
	if(authority == normal){
		authority = admin;
		return true;
	}
	else if(authority == admin){
		authority = superuser;
		return true;
	}
	else if(authority == superuser){
		authority = superuser;
		return false;
	}
}

bool User::demote()
{
	if(authority == superuser){
		authority = admin;
		return true;
	}
	else if(authority == admin){
		authority = normal;
		return true;
	}
	else if(authority == normal){
		authority = normal;
		return false;
	}
}

void User::set_current_elem(Elements* elem)
{
	current_elem = elem;
}

Elements* User::get_current_elem()
{
	return current_elem;
}

void User::set_source_elem(Elements* elem)
{
	source_elem = elem;
}

bool User::set_dest_elem(Elements* elem)
{
	if(elem->get_elem_type() == FOLDER){
		dest_elem = elem;
		return true;
	}
	return false;
}

Elements* User::get_dest_elem()
{
	return dest_elem;
}

Elements* User::get_source_elem()
{
	return source_elem;
}