#include<iostream>
#include<string>
#include<sstream>
#include<queue>
#include<functional>
#include<unordered_map>

typedef std::queue<std::string> Command;
typedef void (*CommandExecutor)(Command); 
//ProductionLine active;


//Also a nice way to visualize requirements for REPL interface
const std::string helpmessage = 
"Available commands: \n"
"help                              : Prints this message. \n"
"loadr <path>                      : Loads production lines from path.\n"
"new <name>                        : Creates new, empty production line.\n"
"add [-s] <b_name> <i_name> <pval> : Adds a new production block b_name,\n"
"then rescales it so that the total production of i_name in the entire line will be equal p_val.\n"
"if production block b_name already exists, does not add a 2nd time, only rescales.\n"
"remove [-s] <b_name>              : Removes a production block. \n"
"rescale [-s] <i_name> <pval>      : Rescales the entire line so that the production of i_name reaches pval.\n"
"In add,remove and rescale commands, unless the -s option is specified, dump will be called immedietaly afterwards.\n"
"save <path>                       : Saves the current line to path.\n"
"dump [-a]                         : Prints production values of current line to screen.\n"
"if -a option is specified, all details of current production line will be printed.\n"
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
const std::unordered_map<std::string,CommandExecutor> initExecutors()
{
    std::unordered_map<std::string,CommandExecutor> retval;
    retval["help"] = help;
    retval["load"] = load;
    retval["new"] = new_line;
    retval["add"] = add;
    retval["remove"] = remove;
    retval["rescale"] = rescale;
    retval["save"] = save;
    retval["dump"] = dump;
    return retval;
} const std::unordered_map<std::string,CommandExecutor> executors = initExecutors();

int main(int argc, char** argv)
{
    std::cout << "Welcome to Helmod 2. \n";
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
        executors.at(commandType)(command);
        
    }
    
    return 0;
}

Command parseCommand()
{
    std::string str;
    std::cin >> str;
    std::string buf;                 // Have a buffer string
    std::stringstream ss(str);       // Insert the string into a stream
    Command tokens; // Create vector to hold our words
    while (ss >> buf)
        tokens.push(buf);
    return tokens;
}
void help(Command)
{
    std::cout << helpmessage;
}
void load(Command)
{
    
}
void new_line(Command){}
void add(Command){}
void remove(Command){}
void rescale(Command){}
void save(Command){}
void dump(Command){}
