#ifndef __APDRIVE_H__
#define __APDRIVE_H__

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
#include <sstream>
#include <fstream>
#include "User.hpp"
#include "exception.hpp"
#include "Folder.hpp"
#include "Group.hpp"
#include "File.hpp"
#define FOLDER "folder"
#define FILE "file"
#define SLASH '/'
#define ADMIN "admin"
#define SUPERUSER "superuser"
#define NORMAL "normal"


class SID
{
private:
	std::string sid;
	std::string username;
public:
	SID(std::string _sid, std::string _username){sid = _sid; username = _username;};
	std::string getSID(){return sid;};
	std::string getUsername(){return username;};
};


class APdrive
{
public:
	APdrive();
	~APdrive();
	bool add_user(std::string username, std::string password);
	bool login(std::string username, std::string password);
	User* get_user_by_sid(std::string sid);
	Folder* get_root_folder();
	bool logout(std::string sid);
	bool new_folder(Elements* father_elem, std::string folder_name);
	Elements* find_element_by_relative_path(std::string relative_path);
	Elements* find_element_by_absoloute_path(std::string absoloute_path);
	bool if_relative_path(std::string path);
	void setUserSID(std::string sid, std::string username);
	User* findUserBySessionId(std::string sid);
	User* search_user(std::string usr_name);
	Elements* get_user_base_elem(std::string username);
	void delete_sid(std::string sid);
	bool upload(std::string source_path, Elements* elem);
	std::vector<std::string> split_by_slash(std::string path);
	std::vector<User*> get_all_users();
	void copy(Elements* copied_elem, Folder* dest_folder);
	void remove(Folder* curr_folder, Elements* elem);
	void upload_phase2(Folder* curr_folder, File* upped_file);
	

private:
	std::vector<User*> users;
	std::vector<Group*> groups;
	Folder* root_folder_ptr;
	Folder* root_folder;
	User* root_user;
	Group* root_group;
	Group* search_group(std::string gp_);
	std::vector<SID*> sessionIds;
};

#endif