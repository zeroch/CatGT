#include <tr1/unordered_map>
#include <string>

class CmdGenerator{

public:
    typedef  enum { right, left } Cmd;


    CmdGenerator(char firstcmd []);

    void updateCmd(char cmd_string []);

    Cmd const &getLatestCommand() const {
        return latestCommand;
    }

private:
    Cmd latestCommand;

    std::unordered_map<int,Cmd> converter;
};