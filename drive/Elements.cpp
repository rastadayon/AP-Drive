#include "Elements.hpp"
#include "Folder.hpp"
#include "Permission.hpp"
#include "User.hpp"
Elements::Elements(std::string elem_name, std:: string _path, User* owner_user, Group* owner_group)
{
	element_name = elem_name;
	path = _path + SLASH + elem_name;
	elem_permission = new Permission(owner_user, owner_group);
	user_owner = owner_user;
	group_owner = owner_group;
}

void Elements::add_to_elements(Elements* element)
{
	sub_elements.push_back(element);
}

std::string Elements::get_elem_type()
{
	return element_type;
}

void Elements::set_father_folder(Folder* _father_folder)
{
	father_folder = _father_folder;
}

std::string Elements::get_elem_name()
{
	return element_name;
}


std::string Elements::get_elem_path()
{
	return path;
}

std::vector<Elements*> Elements:: get_sub_elements()
{
	return sub_elements;
}

bool Elements::if_valid_folder_name(std::string folder_name)
{
	for (int i = 0; i < sub_elements.size(); ++i)
	{
		if(sub_elements[i]->get_elem_type() == FOLDER)
			if(sub_elements[i]->get_elem_name() == folder_name)
				return false;
	}
	return true;
}

void Elements::set_path(std::string _path)
{
	path = _path;
}

Permission* Elements::get_elem_permission()
{
	return elem_permission;
}

User* Elements::get_user_owner()
{
	return user_owner;
}
	
Group* Elements::get_group_owner()
{
	return group_owner;
}


bool Elements::if_folder()
{
	if(this->get_elem_type() == FOLDER)
		return true;
	return false;
}


bool Elements::if_file()
{
	if(this->get_elem_type() == FILE)
		return true;
	return false;
}

Folder* Elements::get_father_folder()
{
	return father_folder;
}

void Elements::remove_subelement(int index)
{
	sub_elements.erase(sub_elements.begin() + index);
}