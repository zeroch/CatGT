#include "CmdGenerator.h"
#include "json/json.h"



/*
char  json_sample [] = "{\"left\":1,\"right\":2,\"value\":3}";
Json::Value root;
Json::Reader reader;

bool parsedSuccess = reader.parse(json_sample, root, false);
if(!parsedSuccess){
//Report failures and locations in the document
std::cout << "Failed to parse JSON" << std::endl
<< reader.getFormatedErrorMessages() << std::endl;
return 1;
}
const Json::Value left = root["left"];
const Json::Value right = root["right"];
const Json::Value value = root["value"];

std::cout << "Left Value: " << left << std::endl
<< "Right Value: " << right << std::endl
<< "Actual Value: " << value << std::endl;
std::cout << "Pretty Print: "
<< root.toStyledString() << std::endl;*/

CmdGenerator::CmdGenerator(char firstcmd[]) {

}

void CmdGenerator::updateCmd(char cmd_string[]) {

}
