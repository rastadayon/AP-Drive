CC=g++
STD=-std=c++11 -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp examples/my_server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/Elements.o: drive/Elements.cpp drive/Elements.hpp drive/exception.hpp drive/Permission.hpp drive/Group.hpp drive/User.hpp
	$(CC) $(CF) -c drive/Elements.cpp -o $(BUILD_DIR)/Elements.o

$(BUILD_DIR)/File.o: drive/File.cpp drive/File.hpp drive/Elements.hpp drive/exception.hpp drive/Folder.hpp
	$(CC) $(CF) -c drive/File.cpp -o $(BUILD_DIR)/File.o

$(BUILD_DIR)/Folder.o: drive/Folder.cpp drive/Folder.hpp drive/exception.hpp drive/Elements.hpp
	$(CC) $(CF) -c drive/Folder.cpp -o $(BUILD_DIR)/Folder.o

$(BUILD_DIR)/Permission.o: drive/Permission.cpp drive/Permission.hpp drive/exception.hpp drive/Group.hpp drive/User.hpp
	$(CC) $(CF) -c drive/Permission.cpp -o $(BUILD_DIR)/Permission.o

$(BUILD_DIR)/Group.o: drive/Group.cpp drive/Group.hpp drive/exception.hpp drive/User.hpp
	$(CC) $(CF) -c drive/Group.cpp -o $(BUILD_DIR)/Group.o

$(BUILD_DIR)/User.o: drive/User.cpp drive/User.hpp drive/exception.hpp drive/Elements.hpp
	$(CC) $(CF) -c drive/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/APdrive.o: drive/APdrive.cpp drive/APdrive.hpp drive/exception.hpp drive/User.hpp drive/Folder.hpp drive/Group.hpp
	$(CC) $(CF) -c drive/APdrive.cpp -o $(BUILD_DIR)/APdrive.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp drive/APdrive.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/APdrive.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/Permission.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/Elements.o $(BUILD_DIR)/File.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/APdrive.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/Permission.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/Elements.o $(BUILD_DIR)/File.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
