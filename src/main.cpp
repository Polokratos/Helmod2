#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<queue>
#include<functional>
#include<unordered_map>
#include "ProductionLine.hpp"

typedef std::queue<std::string> Command;
typedef void (*CommandExecutor)(Command); 
ProductionLine* active = nullptr;


//Also a nice way to visualize requirements for REPL interface
const std::string helpmessage = 
"Available commands: \n"
"help                              : Prints this message. \n"
"load  <path>                       : Loads production lines from path.\n"
"new <name>                        : Creates new, empty production line.\n"
"add [-s] <b_name> <i_name> <pval> : Adds a new production block b_name,\n"
"then rescales it so that the total production of i_name in the entire line will be equal p_val.\n"
"If production block b_name already exists, does not add a 2nd time, only rescales.\n"
"remove [-s] <b_name>              : Removes a production block. \n"
"rescale [-s] <i_name> <pval>      : Rescales the entire line so that the production of i_name reaches pval.\n"
"In add, remove and rescale commands, unless the -s option is specified, dump will be called immedietaly afterwards.\n"
"save <path>                       : Saves the current line to path.\n"
"dump [-a]                         : Prints production values of current line to screen.\n"
"If -a option is specified, all details of current production line will be printed.\n"
"quit                              : Exits the program.\n"; //not given an executor, handled directly in main()

Command parseCommand();
void help(Command);
void load(Command);
void new_line(Command);
void add(Command);
void remove(Command);
void rescale(Command);
void save(Command);
void dump(Command);
//Poor man's switch on strings
const std::unordered_map<std::string,CommandExecutor> initExecutors()
{
    std::unordered_map<std::string,CommandExecutor> retval; retval["help"] = help; retval["load"] = load;
    retval["new"] = new_line; retval["add"] = add; retval["remove"] = remove; retval["rescale"] = rescale;
    retval["save"] = save; retval["dump"] = dump; return retval;
} const std::unordered_map<std::string,CommandExecutor> executors = initExecutors();

int main(int argc, char** argv)
{
    std::cout << "Welcome to Helmod 2.\n";
    while (true)
    {
        std::queue<std::string> command = parseCommand();
        std::string commandType = command.front();
        if(commandType == "quit") break; 
        if(executors.find(commandType) == executors.end())
        {
            std::cout << "invalid command: " << commandType << std::endl;
            continue;
        }
        command.pop(); // a command executor does not need to hear its name, so we pop it.
        try
        {
            executors.at(commandType)(command);
        }
        catch(std::exception* e)
        {
            std::cout << e->what() << '\n';
            delete e; e = nullptr;
        }
        
    }
    
    return 0;
}

Command parseCommand()
{
    std::string str;
    getline(std::cin,str);
    std::string buf;                 // Have a buffer string
    std::stringstream ss(str);       // Insert the string into a stream
    Command tokens; // Create vector to hold our words
    while (ss >> buf)
        tokens.push(buf);
    return tokens;
}
void help(Command c)
{
    std::cout << helpmessage;
}
void load(Command c)
{
    std::ifstream f;
    f.open(c.front());
    if(!f) std::cout << "file not found\n";
    json data = json::parse(f);
    ProductionLine* block = new ProductionLine(data);
    ProductionLine::blocks[block->name] = *block;
    std::cout << "Loaded: " << block->name << '\n';
}
void new_line(Command c)
{
    delete active;
    active = new ProductionLine(c.front());
}
void add(Command c)
{
    bool dmp = true;
    if(c.front() == "-s") {dmp = false; c.pop();}

    std::string bname = c.front(); c.pop();
    Ingredient iname = c.front(); c.pop();
    double pval = stod(c.front());

    ProductionLine block = ProductionLine::blocks.at(bname);

    active->add(block,iname,pval);
    if(dmp) {active->dumpDelta();}
}
void remove(Command c)
{
    bool dmp = true;
    if(c.front() == "-s") {dmp = false; c.pop();}
    std::string bname = c.front(); c.pop();
    active->remove(bname);
    if(dmp) {active->dumpDelta();}
}
void rescale(Command c)
{
    bool dmp = true;
    if(c.front() == "-s") {dmp = false; c.pop();}
    Ingredient iname = c.front(); c.pop();
    double pval = stod(c.front());
    active->rescale(iname,pval);
    if(dmp) {active->dumpDelta();}
}
void save(Command c)
{
    std::string path = c.front();
    std::ofstream f;
    f.open(path);
    json data;
    data["name"] = active->name;
    data["delta"] = json::object();
    data["internal"] = json::object();
    for (auto &&[k,v] : active->delta)
        data["delta"][k] = v;
    for (auto &&[k,v] : active->internal)
        data["internal"][k] = v;
    f << std::setw(4) << data << std::endl;
}
void dump(Command c)
{
    bool all = false;
    if(!c.empty()) if(c.front() == "-a") {all = true; c.pop();}
    active->dumpDelta();
    if(all) active->dumpInternal();
}
