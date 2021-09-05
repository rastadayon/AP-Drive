#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include <string>
#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
#include <sstream>	
#include "APdrive.hpp"
#include "User.hpp"
#include "Folder.hpp"

#define SPACE ' '

class Interface
{
public:
	Interface();
	~Interface();
	void read_input();

private:
	APdrive* AP_drive;
	void add_user(std::vector<std::string> words);
	void login(std::vector<std::string> words);
	void logout();
	void add_group(std::vector<std::string> words);
	void add_to_group(std::vector<std::string> words);
	void upload(std::vector<std::string> words);
	void make_directory(std::vector<std::string> words);
	void copy(std::vector<std::string> words);
	void change_directory(std::vector<std::string> words);
	void userlist(std::vector<std::string> words);
	void print_directory(std::vector<std::string> words);
	void file_size(std::vector<std::string> words);
	void promote(std::vector<std::string> words);
};

#endif