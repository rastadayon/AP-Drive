#include "../examples/my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include "../drive/APdrive.hpp"
#define ROOT "root"



class LoginHandler : public RequestHandler {
public:
	LoginHandler(APdrive* _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive * AP_drive;
};

class UploadHandler : public RequestHandler {
public:
	UploadHandler(APdrive* _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive * AP_drive;
};

class HomePageHandler : public RequestHandler{
public:
	HomePageHandler(APdrive* _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive * AP_drive;
};

class AddUserHandler : public RequestHandler{
public:
	AddUserHandler(APdrive* _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive * AP_drive;
};

class LogoutHandler : public RequestHandler{
public:
	LogoutHandler(APdrive* _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive * AP_drive;
};

class ShowFolderHandler : public RequestHandler{
public:
	ShowFolderHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive * AP_drive;
};

class UserlistHandler : public RequestHandler{
public:
	UserlistHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class PromoteHandler : public RequestHandler{
public:
	PromoteHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class DemoteHandler : public RequestHandler{
public:
	DemoteHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class ShowElementHandler : public RequestHandler{
public:
	ShowElementHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class FatherFolderHandler : public RequestHandler{
public:
	FatherFolderHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class NewFolderHandler : public RequestHandler{
public:
	NewFolderHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class DetailsHandler : public RequestHandler{
public:
	DetailsHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class CopyHandler : public RequestHandler{
public:
	CopyHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class PasteHandler : public RequestHandler{
public:
	PasteHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};

class RemoveHandler : public RequestHandler{
public:
	RemoveHandler(APdrive * _AP_drive){AP_drive = _AP_drive;};
	Response *callback(Request *);
private:
	APdrive* AP_drive;
};