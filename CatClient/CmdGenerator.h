
class CmdGenerator{
    Cmd latestCommand;
public:
    typedef  enum { right, left } Cmd;


    CmdGenerator(char firstcmd []);
    
    void updateCmd(char cmd_string []);

    Cmd const &getLatestCommand() const {
        return latestCommand;
    }
};