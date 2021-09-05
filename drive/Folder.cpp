#include "Folder.hpp"
#include "File.hpp"
Folder::Folder(std::string elem_name, std:: string _path, User* owner_user, Group* owner_group)
		:Elements(elem_name, _path, owner_user, owner_group){ element_type = FOLDER; }

Folder::Folder(Folder* folder)
		:Folder(folder->get_elem_name(), "", folder->get_user_owner(), folder->get_group_owner()){}