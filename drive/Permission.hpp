#ifndef __PERMISSION_H__
#define __PERMISSION_H__
#include <string>
#include <iostream>
#include <vector>
#include "User.hpp"
#include "Group.hpp"
#include "exception.hpp"
#define READ "read"
#define WRITE "write"
#define RW "read and write"
#define NOTHING "nothing"

class User;
class Group;
enum _permission{nothing, read, write, rw};
class Permission
{
public:
	Permission(User* _owner_user, Group* _owener_group);
	~Permission();
	User* get_user_owner();
	Group* get_group_owner();
	std::string get_user_permission();
	std::string get_group_permission();

private:
	std::pair <User*, _permission> user_permission;
	std::pair <Group*, _permission> group_permission;
	
};

#endif