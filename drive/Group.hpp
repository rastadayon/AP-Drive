#ifndef __GROUP_H__
#define __GROUP_H__

#include <string>
#include <iostream>
#include <vector>
//#include "User.hpp"
#include "exception.hpp"
class User;

class Group
{
public:
	Group(std::string gp_name);
	//void add_to_group(std::string gp_name, User* usr);
	~Group();
	std::vector<User*> get_group();
	void add_to_group(User* _user);
	std::string get_group_name();
private:
	std::vector<User*> gp;
	std::string group_name;
	
};

#endif