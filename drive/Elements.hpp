#ifndef __ELEMENTS_H__
#define __ELEMENTS_H__

#include <string>
#include <iostream>
#include <vector>
#include "exception.hpp"
#include "Group.hpp"
#define SLASH '/'
#define FOLDER "folder"
#define FILE "file"

class Folder;
class User;
class Permission;
class Elements
{
public:
	Elements(std::string elem_name, std:: string _path, User* owner_user, Group* owner_group);
	void add_to_elements(Elements* element);
	virtual std::string get_elem_type();
	void set_father_folder(Folder* _father_folder);
	Folder* get_father_folder();
	std::string get_elem_name();
	std::string get_elem_path();
	std::vector<Elements*> get_sub_elements();
	bool if_valid_folder_name(std::string folder_name);
	void set_path(std::string _path);
	Permission* get_elem_permission();
	User* get_user_owner();
	Group* get_group_owner();
	bool if_folder();
	bool if_file();
	void remove_subelement(int index);

protected:
	Folder* father_folder;
	std::string element_name;
	std::string path;
	std::string element_type;
	Permission *elem_permission;
	std::vector<Elements*> sub_elements;
	User* user_owner;
	Group* group_owner;
	
};

#endif