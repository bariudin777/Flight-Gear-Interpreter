//
// Created by ariel on 13/12/18.
//

#include "User.h"
#include "ShuntingYard.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "EntercCommand.h"
#include "RunCommand.h"
#include <algorithm>
#include <regex>

#define OPEN_DATA_SERVER "openDataServer"
#define CONNECT "connect"
#define VAR "var"
#define IF "if"
#define WHILE "while"
#define PRINT "print"
#define SLEEP "sleep"
#define EXIT "exit"
#define ENTERC "enterc"
#define RUN "run"


//User::User(SymbolTable *table, vector<pthread_t> *threads) {
//    m_symbolTable = table;
//    m_commands.insert(make_pair(OPEN_DATA_SERVER, new OpenServerCommand(&threads)));
//    m_commands.insert(make_pair(CONNECT, new ConnectCommand()));
//    m_commands.insert(make_pair(VAR, new DefineVarCommand(m_symbolTable)));
//    m_commands.insert(make_pair(IF, new IfCommand(m_symbolTable)));
//    m_commands.insert(make_pair(WHILE, new LoopCommand(m_symbolTable,this)));
//    m_commands.insert(make_pair(PRINT, new PrintCommand(m_symbolTable)));
//    m_commands.insert(make_pair(SLEEP, new SleepCommand()));
//}

User::~User() {
    delete m_symbolTable;
    for (auto &x : m_commands) {
        delete x.second;
    }
}

vector<string> User::lexer(string &str) {
    vector<string> data;
    ifstream stream(str);
    // If the given string is a name of a file
    if (stream.is_open()) {
        string line;
        while (getline(stream, line)) {
            // Adding the current line to the data vector
            if (!line.empty()) {
                vector<string> res = this->analyzeLine(line);
                data.insert(data.end(), res.begin(), res.end());
            }
        }
        stream.close();
        return data;
    }
    // Otherwise - it's a single string command
    data = this->analyzeLine(str);
    return data;
}

vector<string> User::analyzeLine(string &line) const {
    vector<string> v;
    this->adjustLine(line);
    while (!line.empty()) {
        unsigned long index = line.find(' ');
        string temp = line.substr(0, index);
        v.emplace_back(temp);
        if (index > line.length()) {
            line = "";
        } else {
            line = line.substr(index + 1);
        }
    }
    // Adding '\n' to distinguish between the lines in the original text
    v.emplace_back("\n");
    if (v.at(0) == OPEN_DATA_SERVER) {
        this->contractVector(v);
    }
    return v;
}

//void

void User::adjustLine(string &line) const {
    if (line.find('\r') < line.length()) {
        line.erase(line.length() - 1);
    }
    // Separating the '=' and ',' symbols from any text that is right next to it (if so happens)
    unsigned long index = line.find('=');
    if (index < line.length()) {
        if (line.at(index + 1) != ' ') {
            line.insert(index + 1, " ");
        }
        if (line.at(index - 1) != ' ') {
            line.insert(index, " ");
        }
    }
    index = line.find(',');
    if (index < line.length()) {
        if (line.at(index + 1) != ' ') {
            line.insert(index + 1, " ");
        }
        if (line.at(index - 1) != ' ') {
            line.insert(index, " ");
        }
        // If there isn't a comma string - add him for later use
    } else {
        if (line.find(OPEN_DATA_SERVER) < line.length()) {
            regex e("\\d+\\s+\\d+|\\)\\s+\\d+");
            smatch m;
            regex_search(line, m, e);
            // Add a comma where the white space is and separate it
            int index = line.find(' ', m.position(0));
            line.insert(index, ",").insert(index, " ");
        }
    }
    // Removing apostrophe symbols from binding paths
    if (line.find('\"') != string::npos && line.find("bind") < line.length()) {
        line.erase(line.find('\"'), 1);
        line.erase(line.rfind('\"'), 1);
    }
    // Removing any leading spaces before the actual text
    index = 0;
    while (line[index] == ' ') {
        index++;
    }
    line = line.substr(index);
}

/**
 * Contracting a vector by calculating different string expressions (if exist) and instead inserting their value
 * @param vec - a line of text entered by the user, broken down to a vector of strings
 */
void User::contractVector(vector<string> &vec) const {
    if (vec.size() == 3) {
        return;
    }
    // Due to a previous function, there is a comma string that separates the different expressions
    auto posComma = find(vec.begin(), vec.end(), ",");

    // Creating a temporary vector that is used to calculate the different expressions
    vector<string> temp;
    temp.insert(temp.end(), vec.begin() + 1, posComma);
    int first = (int) ShuntingYard().calculateExpression(temp);
    temp.clear();

    temp.insert(temp.end(), posComma + 1, vec.end() - 1);
    int second = (int) ShuntingYard().calculateExpression(temp);
    string name = vec.at(0);
    // Updating the input vector to contain only 3 final arguments
    vec.clear();
    vec = {name, to_string(first), to_string(second), "\n"};
}

void User::parser(vector<string> &details) {
    /*
     * If the input is from the terminal, a loop command won't be executed until all the lines are entered.
     * As a result, we first check if it is a terminal-input and if all the lines and commands have been entered.
     */
    if (details.at(0) == WHILE || details.at(0) == IF || m_isInsideCondition) {
        m_isInsideCondition = true;
        m_conditionDetails.insert(m_conditionDetails.end(), details.begin(), details.end());

        if (this->isBracketsMatching(m_conditionDetails)) {
            m_isInsideCondition = false;

            // Executing the commands
            string name = m_conditionDetails.at(0);
            auto itor = m_conditionDetails.begin() + 1;
            m_conditionDetails = this->bracketsParser(itor);
            m_commands.at(name)->doCommand(m_conditionDetails);
            // Resetting
            m_conditionDetails.clear();

        }
        return;
    }

    for (auto itor = details.begin(); itor != details.end(); itor++) {
        // Vector of information for the command
        vector<string> commandInfo;
        // Getting the arguments related to the command
        string name = *itor;
        if (name.length() == 1) {
            continue;
        }

        itor++;
        if (name == WHILE || name == IF) {
            commandInfo = this->bracketsParser(itor);
        } else {
            while (*itor != "\n") {
                commandInfo.emplace_back(*itor);
                itor++;
            }
        }
        // Executing the command with its arguments
        if (m_commands.count(name) == 0) {
            commandInfo.insert(commandInfo.begin(), name);
            m_commands.at(VAR)->doCommand(commandInfo);
        } else {
            m_commands.at(name)->doCommand(commandInfo);
        }
    }
    m_conditionDetails.clear();
    m_isInsideCondition = false;
}

bool User::isBracketsMatching(const vector<string> &lines) const {
    int countOpen = 0;
    int countClose = 0;
    auto itor = lines.begin();

    while (*itor != "{") {
        itor++;
        if (itor == lines.end()) {
            return false;
        }
    }
    itor++;
    countOpen++;
    while (itor != lines.end()) {
        if (*itor == "{") {
            countOpen++;
        } else if (*itor == "}") {
            countClose++;
        }
        itor++;
    }
    return countOpen == countClose;
}

vector<string> User::bracketsParser(vector<string>::iterator &itor) const {
    vector<string> v;
    // Getting the condition of the loop as the first item in the vector
    string condition;
    while (*itor != "\n") {
        condition += *itor;
        itor++;
        if (*itor == "{") {
            break;
        }
    }
    v.emplace_back(condition);
    v.emplace_back(*itor);
    itor++;
    if (*itor == "\n") {
        v.emplace_back("\n");
        itor++;
    }

    string currLine;
    // Iterating over all the commands in the bracket
    while (*itor != "}") {
        if (*itor == WHILE || *itor == IF) {
            string name = *itor;
            itor++;
            vector<string> temp = this->bracketsParser(itor);
            temp.at(0).insert(0, name + " ");
            v.insert(v.end(), temp.begin(), temp.end());
            itor++;
            continue;
        }
        currLine += *itor;
        itor++;
        // If we reached the end of the current command
        if (*itor == "\n") {
            v.emplace_back(currLine);
            v.emplace_back("\n");
            currLine = "";
            itor++;
        } else {
            currLine += " ";
        }
    }
    // Adding the closing bracket
    v.emplace_back(*itor);
    itor++;
    return v;
}


unordered_map<string, Command *> User::getMapCommands() const {
    return m_commands;
}

User::User(pthread_mutex_t * mutex,vector<pthread_t> *threads, ExitCommand *exitCommand) {
    InitializeParameterMap();
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
        printf("mutex init failed");
        return;
    }
    m_symbolTable = new SymbolTable(m_namesPaths, m_pathsValues, mutex);
    m_commands.insert(make_pair(OPEN_DATA_SERVER, new OpenServerCommand(m_symbolTable, threads)));
    m_commands.insert(make_pair(CONNECT, new ConnectCommand(m_symbolTable)));
    m_commands.insert(make_pair(VAR, new DefineVarCommand(m_symbolTable)));
    m_commands.insert(make_pair(IF, new IfCommand(m_symbolTable)));
    m_commands.insert(make_pair(WHILE, new LoopCommand(m_symbolTable, this)));
    m_commands.insert(make_pair(PRINT, new PrintCommand(m_symbolTable)));
    m_commands.insert(make_pair(SLEEP, new SleepCommand()));
    m_commands.insert(make_pair(EXIT, exitCommand));
    m_commands.insert(make_pair(ENTERC, new EntercCommand()));
    m_commands.insert(make_pair(RUN, new RunCommand(this)));
}

void User::InitializeParameterMap() {
    m_namesPaths["airspeed"] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    m_namesPaths["altimeter_altitude"] = "/instrumentation/altimeter/indicated-altitude-ft";
    m_namesPaths["altimeter_pressure"] = "/instrumentation/altimeter/pressure-alt-ft";
    m_namesPaths["attiude_indicated-pitch"] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    m_namesPaths["attiude_indicated-roll"] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    m_namesPaths["attiude_internal-pitch"] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    m_namesPaths["attiude_internal-roll"] = "/instrumentation/attitude-indicator/internal-roll-deg";
    m_namesPaths["encoder_indicated-altitude"] = "/instrumentation/encoder/indicated-altitude-ft";
    m_namesPaths["encoder_pressure"] = "/instrumentation/encoder/pressure-alt-ft";
    m_namesPaths["gps_indicated-altitude"] = "/instrumentation/gps/indicated-altitude-ft";
    m_namesPaths["gps_indicated-ground-speed"] = "/instrumentation/gps/indicated-ground-speed-kt";
    m_namesPaths["gps_indicated-vertical-speed"] = "/instrumentation/gps/indicated-vertical-speed";
    m_namesPaths["heading"] = "/instrumentation/heading-indicator/indicated-heading-deg";
    m_namesPaths["compass"] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    m_namesPaths["slip-skid-ball"] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    m_namesPaths["turn_rate"] = "/instrumentation/turn-indicator/indicated-turn-rate";
    m_namesPaths["vertical_speed_indicator"] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    m_namesPaths["aileron"] = "/controls/flight/aileron";
    m_namesPaths["elevator"] = "/controls/flight/elevator";
    m_namesPaths["rudder"] = "/controls/flight/rudder";
    m_namesPaths["flaps"] = "/controls/flight/flaps";
    m_namesPaths["throttle"] = "/controls/engines/current-engine/throttle";
    m_namesPaths["rpm"] = "/engines/engine/rpm";
    m_pathsValues.insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    m_pathsValues.insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    m_pathsValues.insert(pair<string, double>("/controls/flight/aileron", 0));
    m_pathsValues.insert(pair<string, double>("/controls/flight/elevator", 0));
    m_pathsValues.insert(pair<string, double>("/controls/flight/rudder", 0));
    m_pathsValues.insert(pair<string, double>("/controls/flight/flaps", 0));
    m_pathsValues.insert(pair<string, double>("/controls/engines/current-engine/throttle", 0));
    m_pathsValues.insert(pair<string, double>("/engines/engine/rpm", 0));
}