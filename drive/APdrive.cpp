#include "APdrive.hpp"
APdrive::APdrive()
{
	root_user = new User("root", "root", superuser);
	users.push_back(root_user);
	Group* root_group = new Group("root");
	root_group->add_to_group(root_user);
	groups.push_back(root_group);
	root_folder = new Folder("", "", root_user, root_group);
	root_folder->set_path("");
	root_folder->set_father_folder(NULL);
	root_folder_ptr = root_folder;
	root_user->set_current_elem(root_folder);
	add_user("rasta","a");
	User* rasta = search_user("rasta");
	Elements* elem = rasta->get_current_elem();
	upload("/home/rasta/ut/AP/CA#4/phase 2/APHTTP-1.0.1/Files/hi.txt",elem);
	upload("/home/rasta/ut/AP/CA#4/phase 2/APHTTP-1.0.1/Files/hello.txt",elem);
	new_folder(elem, "folder1");
}

std::vector<User*> APdrive::get_all_users()
{
	return users;
}

Folder* APdrive::get_root_folder()
{
	return root_folder;
}

std::vector<std::string> APdrive::split_by_slash(std::string path)
{
	std::stringstream _path(path);
	std::string parts;
	std::vector<std::string> v;
	while(std::getline(_path, parts, SLASH)){
	   v.push_back(parts);	   
	}
	if(path[0] == SLASH)
		path.erase(path.begin() + 0);
	return v;
}

bool APdrive::upload(std::string source_path, Elements* elem)
{
	if(elem->get_elem_type() != FOLDER)
		return false;
	std::ifstream in(source_path, std::ios::binary);
	std::string content;
	std::vector<std::string> path = split_by_slash(source_path);
	std::string file_name = path[path.size() - 1];
	while(!in.eof())
		content += in.get();
	File* uped_file = new File(file_name, elem->get_elem_path(), elem->get_user_owner(), NULL);
	uped_file->set_file_content(content);
	elem->add_to_elements(uped_file);
	uped_file->set_father_folder(dynamic_cast<Folder*>(elem));
	in.close();
	return true;
}

bool APdrive::add_user(std::string username, std::string password)
{
	for (int i = 0; i < users.size(); ++i){
		if(users[i]->get_username() == username)
			return false;
	}
	User* new_user = new User(username, password, normal);
	users.push_back(new_user);
	Folder* new_folder = new Folder(username, root_folder->get_elem_path(), new_user, NULL);
	root_folder-> add_to_elements(new_folder);
	new_folder->set_father_folder(root_folder);
	new_user->set_current_elem(new_folder);
	return true;
}

void APdrive::setUserSID(std::string sid, std::string username)
{
	SID* newSID = new SID(sid, username);
	sessionIds.push_back(newSID);
}

User* APdrive::search_user(std::string usr_name)
{
	for (int i = 0; i < users.size(); ++i)
	{
		if (users[i]->get_username() == usr_name)
			return users[i];
	}
	return NULL;
}

User* APdrive::findUserBySessionId(std::string sid){
	User* user = NULL;
	for (int i = 0; i < sessionIds.size(); ++i){
		if(sessionIds[i]->getSID() == sid){
			user = search_user(sessionIds[i]->getUsername());
		}
	}
	return user;
}

void APdrive::copy(Elements* copied_elem, Folder* dest_folder)
{
	Elements* new_elem;
	if(copied_elem->get_elem_type() == FILE)
		new_elem = new File(dynamic_cast<File*>(copied_elem));
	else if(copied_elem->get_elem_type() == FOLDER)
		new_elem = new Folder(dynamic_cast<Folder*>(copied_elem));
	std::string new_path = dest_folder->get_elem_path();
	new_path = new_path + SLASH + copied_elem->get_elem_name();
	new_elem->set_path(new_path);
	new_elem->set_father_folder(dest_folder);
	dest_folder->add_to_elements(new_elem);
}

void APdrive::remove(Folder* curr_folder, Elements* elem)
{
	std::vector<Elements*> fathers_children = curr_folder->get_sub_elements();
	std::cerr<<fathers_children.size()<<std::endl;
	for (int i = 0; i < fathers_children.size(); ++i)
	{
		if(fathers_children[i] == elem){
			curr_folder->remove_subelement(i);
			return;
		}
	}
}

void APdrive::upload_phase2(Folder* curr_folder, File* upped_file)
{
	curr_folder->add_to_elements(upped_file);
}

bool APdrive::login(std::string username, std::string password)
{
	for (int i = 0; i < users.size(); ++i)
		if(users[i]->get_username() == username && users[i]->get_password() == password)
			return true;
	return false;	
}

User* APdrive::get_user_by_sid(std::string sid)
{
	std::string username = "";
	for (int i = 0; i < sessionIds.size(); ++i)
	{
		if(sessionIds[i]->getSID() == sid)
			username = sessionIds[i]->getUsername();
	}
	User* found_user = search_user(username);
	return found_user;
}

void APdrive::delete_sid(std::string sid)
{
	for (int i = 0; i < sessionIds.size(); ++i)
	{
		if(sessionIds[i]->getSID() == sid)
			sessionIds.erase(sessionIds.begin() + i);
	}
}

Elements* APdrive::get_user_base_elem(std::string username)
{
	std::string path = "/" + username;
	Elements* found_elem = find_element_by_absoloute_path(path);
	return found_elem;
}

bool APdrive::logout(std::string sid)
{

	User* found_user = get_user_by_sid(sid);
	if(found_user == NULL)
		return false;
	std::string username = found_user->get_username();
	delete_sid(sid);
	found_user->set_current_elem(get_user_base_elem(username));
	return true;
}

bool APdrive::new_folder(Elements* father_elem, std::string folder_name)
{

	if(father_elem){
		Folder* new_folder = new Folder(folder_name, father_elem->get_elem_path(), father_elem->get_user_owner(), father_elem->get_group_owner());
		new_folder->set_father_folder(dynamic_cast<Folder*>(father_elem));
		father_elem->add_to_elements(new_folder);
		return true;
	}
	else
		return false;
}

Elements* APdrive::find_element_by_absoloute_path(std::string absoloute_path)
{
	Elements* iterator = root_folder_ptr;
	std::stringstream _absoloute_path(absoloute_path);
	std::string parts;
	std::vector<std::string> path;
	while(std::getline(_absoloute_path, parts, SLASH)){
	   path.push_back(parts);	   
	}
	if(path.size() == 0)
		return root_folder;
	path.erase(path.begin() + 0);
	for (int i = 0; i < path.size(); ++i)
	{
		bool found = false;
		std::vector<Elements*> sub_elems = iterator->get_sub_elements();
		for (int j = 0; j < (sub_elems.size()); ++j)
		{
			if(path[i] == sub_elems[j]->get_elem_name()){
				iterator = sub_elems[j];
				found = true;
				break;
			}
		}
		if(found == false)
			return NULL;
	}
	return iterator;
}

