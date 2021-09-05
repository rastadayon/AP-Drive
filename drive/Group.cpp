#include "Group.hpp"

Group::Group(std::string gp_name)
{
	group_name = gp_name;
}

std::vector<User*> Group::get_group()
{
	return gp;
}

void Group::add_to_group(User* _user)
{
	gp.push_back(_user);
}
std::string Group::get_group_name()
{
	return group_name;
}