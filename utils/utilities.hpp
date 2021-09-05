#ifndef __UTILILITES__
#define __UTILILITES__
#include <map>
#include <string>
#include <vector>
#define SEED "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
#define BUFFER_SIZE 4145152
#define SID_SIZE 16
#define NEG -1
#include <time.h>  


struct comp {
  bool operator()(const std::string &lhs, const std::string &rhs) const;
};

typedef std::map<std::string, std::string, comp>
    cimap; // Case-Insensitive <string, string> map

std::string readFile(const char *filename);
std::string readFile(std::string filename);
std::string getExtension(std::string filePath);
void printVector(std::vector<std::string>);
std::vector<std::string> split(std::string s, std::string d, bool trim = true);

std::string urlEncode(std::string const &);
std::string urlDecode(std::string const &);

std::string toLowerCase(std::string);

std::string randomStrGnr();
void insert(std::string &body, std::string text, std::string key);

std::vector<std::string> tokenize(std::string const &);
void replaceAll(std::string &str, const std::string &from,
                const std::string &to);



#endif
