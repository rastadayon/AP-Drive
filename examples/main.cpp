#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  APdrive* AP_drive = new APdrive();
  
  srand(time(NULL)); // for rand
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    
    server.setNotFoundErrPage("static/404.html");
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(AP_drive));
    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler(AP_drive));
    server.get("/drive.png", new ShowImage("static/drive.png"));
    server.get("/accfolder.png", new ShowImage("images/accfolder.png"));
    server.get("/loggedin", new HomePageHandler(AP_drive));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/normalHomepage", new ShowPage("static/normalusercss.html"));
    server.get("/systemManagement", new ShowPage("static/systemManagementcss.html"));
    server.get("/userlist", new UserlistHandler(AP_drive));
    server.get("/adduser", new ShowPage("static/addusercss.html"));
    server.post("/adduser", new AddUserHandler(AP_drive));
    server.get("/logout", new LogoutHandler(AP_drive));
    server.post("/showFolder", new ShowFolderHandler(AP_drive));
    server.get("/user.png", new ShowImage("static/user.png"));
    server.post("/promote", new PromoteHandler(AP_drive));
    server.post("/demote", new DemoteHandler(AP_drive));
    server.get("/background.jpg", new ShowImage("static/background.jpg"));
    server.get("/elemslist", new ShowFolderHandler(AP_drive));
    server.post("/elemslist", new ShowFolderHandler(AP_drive));
    server.get("/Folder.png", new ShowImage("static/Folder.png"));
    server.post("/element", new ShowElementHandler(AP_drive));
    server.get("/file.png", new ShowImage("static/file.png"));
    server.post("/fatherfolder", new FatherFolderHandler(AP_drive));
    server.get("/newfolder.png", new ShowImage("static/newfolder.png"));
    server.post("/newfolder", new NewFolderHandler(AP_drive));
    server.post("/details", new DetailsHandler(AP_drive));
    server.post("/copy", new CopyHandler(AP_drive));
    server.post("/paste", new PasteHandler(AP_drive));
    server.post("/remove", new RemoveHandler(AP_drive));

    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
