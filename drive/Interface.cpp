#include "Interface.hpp"

Interface::Interface()
{
	AP_drive = new APdrive;
}

Interface::~Interface()
{
	delete AP_drive;
}
void Interface::add_user(std::vector<std::string> words)
{
	try{
		AP_drive->add_user(words);
	}
	catch (cant_add_user_now Ex) { 
		std::cout << "Can't add a user now. Log out to do that." << std::endl; 
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(repeated_username Ex){
		std::cout << "Username already taken." << std::endl;
	}
}
void Interface::login(std::vector<std::string> words)
{
	try{
		AP_drive->login(words);
	}
	catch (cant_login_now Ex){
		std::cout << "Can't login now. Log out to do so." << std::endl;
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(invalid_username_or_pass Ex){
		std::cout << "Invalid username or password." << std::endl;
	}
}
void Interface::logout()
{
	try{
		AP_drive->logout();
	}
	catch(no_user_logged_in Ex)
	{
		std::cout << "No user is logged in yet. To logout please login fisrt." << std::endl;
	}
}
void Interface::add_group(std::vector<std::string> words)
{
	try{
		AP_drive->add_group(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(invalid_group_name Ex){
		std::cout << "Group name already exists. Try another group name please." << std::endl;
	}
	catch(no_user_logged_in Ex){
		std::cout << "No user is logged in. To make a group you should be logged in." << std:: endl;
	}
}
void Interface::add_to_group(std::vector<std::string> words)
{
	try{
		AP_drive->add_to_group(words);
	}
	catch(group_doesnt_exist Ex){
		std::cout << "This group doesn't exist. Enter a valid group name please." << std::endl;
	}
	catch(user_doesnt_exist Ex){
		std::cout << "The user doesn't exist. Enter a valid username please." << std::endl;
	}
	catch(no_user_logged_in Ex){
		std::cout << "No user is logged in. To make a group you should be logged in." << std:: endl;
	}
}
void Interface::upload(std::vector<std::string> words)
{
	// try{
	// 	AP_drive->upload()
	// }
}
void Interface::make_directory(std::vector<std::string> words)
{
	try{
		AP_drive -> make_directory(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(no_user_logged_in Ex){
		std::cout << "No user is logged in. To make a directory you should be logged in." << std:: endl;
	}
	catch(something_went_wrong Ex){
		std::cout << "Oops. Something went wrong. Please try agian." << std::endl;
	}
	catch(invalid_folder_name Ex){
		std::cout << "Invalid folder name. Try a folder name that is not already taken." << std::endl;
	}
}
void Interface::copy(std::vector<std::string> words)
{
	try{
		AP_drive -> copy(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(source_doesnt_exist Ex){
		std::cout << "Source file doesn't exist." << std::endl;
	}
}
void Interface::change_directory(std::vector<std::string> words)
{
	try{
		AP_drive->change_directory(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(path_not_for_folder Ex){
		std::cout << "Path given is not valid, because it's not the path to a folder." << std::endl;
	}
	catch(invalid_path Ex){
		std::cout << "This path doesn't exist. Please enter a valid path." << std::endl;
	}
}
void Interface::userlist(std::vector<std::string> words)
{
	try{
		AP_drive->userlist(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
}
void Interface::print_directory(std::vector<std::string> words)
{
	try{
		AP_drive->print_directory(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(no_user_logged_in Ex){
		std::cout << "No user has logged in. To print directory please login first." << std::endl;
	}
}
void Interface::file_size(std::vector<std::string> words)
{
	try{
		AP_drive->file_size(words);
	}
	catch(element_not_file_type Ex){
		std::cout << "The path doesn't name a file type." << std::endl;
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(invalid_path Ex){
		std::cout << "This path doesn't exist. Please enter a valid path. " << std::endl;
	}
}
void Interface::promote(std::vector<std::string> words)
{
	try{
		AP_drive->promote(words);
	}
	catch(invalid_data_format Ex){
		std::cout << "Invalid data format." << std::endl;
	}
	catch(user_not_superuser Ex){
		std::cout << "Can't promote because User isn't superuser." << std::endl;
	}
	catch(cant_demote Ex){
		std::cout << "Can't demote in a promote command." << std::endl;
	}
}
void Interface::read_input()
{
	std::string input;
	while(getline(std::cin,input)){
		std::string word;
		std::vector<std::string> words;
		std::stringstream ss(input);
		while (getline(ss, word, SPACE)){
        	words.emplace_back(word);
        }
        if(words.size() == 0)
        	continue;
        else if(words[0] == "add_user")
        	add_user(words);
        else if(words[0] == "login")
        	login(words);
        else if(words[0] == "logout")
        	logout();
        else if(words[0] == "add_group")
        	add_group(words);
        else if(words[0] == "add_to_group")
        	add_to_group(words);
        else if(words[0] == "upload")
        	upload(words);
        else if(words[0] == "make_directory")
        	make_directory(words);
        // else if(words[0] == "copy")
        // 	copy(words);
        else if(words[0] == "change_directory")
        	change_directory(words);
        else if(words[0] == "userlist")
        	userlist(words);
        else if(words[0] == "print_directory")
        	print_directory(words);
        else if(words[0] == "file_size")
        	file_size(words);
        else if (words[0] == "promote")
        	promote(words);
        else
        	std::cout << "Invalid command." << std::endl;

    }
}