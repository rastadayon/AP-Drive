#include "Permission.hpp"

Permission::Permission(User* _owner_user, Group* _owener_group)
{
	user_permission.first = _owner_user;
	user_permission.second = rw;
	group_permission.first = _owener_group;
	if(!_owener_group)
		group_permission.second = rw;
	else
		group_permission.second = nothing;

}

User* Permission::get_user_owner()
{
	return user_permission.first;
}

Group* Permission::get_group_owner()
{
	return group_permission.first;
}

std::string Permission::get_user_permission()
{
	if(user_permission.second == read)
		return READ;
	else if(user_permission.second == write)
		return WRITE;
	else if(user_permission.second == rw)
		return RW;
	else if(user_permission.second == nothing)
		return NOTHING;
}

std::string Permission::get_group_permission()
{
	if(group_permission.second == read)
		return READ;
	else if(group_permission.second == write)
		return WRITE;
	else if(group_permission.second == rw)
		return RW;
	else if(group_permission.second == nothing)
		return NOTHING;
}