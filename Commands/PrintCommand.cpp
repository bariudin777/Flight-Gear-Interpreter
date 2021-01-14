//
// Created by daniel on 12/22/18.
//

#include <iostream>
#include "PrintCommand.h"
#include "ShuntingYard.h"

PrintCommand::PrintCommand(SymbolTable *table) {
    this->_table = table;
}


int PrintCommand::doCommand(vector<string> &commandInfo) {


    string toPrint;
    //init what we have in the vector to one string
    for (auto iter:commandInfo) {
        toPrint += iter;
    }
    try {
        if (toPrint.empty()) {
            throw invalid_argument("the  word is empty");
        }
    } catch (invalid_argument e) {
        cout << e.what() << endl;
    }
    // if we dont have "--> just send to shunting yard
    if (toPrint.find('\"') > toPrint.length()) {
        double value = ShuntingYard(this->_table).calculateExpression(commandInfo);
        cout << value << endl;
        return 0;
    }//else we need to print string
    else {
        string tempToPrint = splitWord(toPrint);
        cout << tempToPrint << endl;
    }
}

PrintCommand::~PrintCommand() {

}

string PrintCommand::getWord(const string &wordToWorkOn) {

    string wordToReturn;
    size_t pos1 = wordToReturn.find('"', 0);// the first position of "
    size_t pos2 = wordToReturn.find('"', wordToReturn.length());//the second position of "
    return string(wordToReturn.c_str() + pos1, pos2);// return the string from pos1 to pos2

}

/*
 * split the string to be with-out " "
 */
string PrintCommand::splitWord(const string &str) {
    string result;
    result = str.substr(1, str.length() - 2);
    return result;
}























//        } else {
//            positionIndex = toPrint.find('\"');
//            // if there is an expresion and a string
//            //create an vector of expressions and strings
//            string temp = toPrint.substr(0, positionIndex - 1);
//            wordInLine.emplace_back(temp);
//            if (positionIndex > toPrint.length()) {
//                toPrint = "";
//            } else {
//                toPrint = toPrint.substr(positionIndex + 1);
//                string strWord;
//                /*
//                 * iter on the vector
//                 * if word have "== its a string
//                 * else- the word contains expresion and string
//                 */
//                for (auto word:wordInLine) {
//                    //handle string
//                    if (word.find('"', 0)) {
//                        strWord = getWord(word);
//                        cout << strWord;
//                        if (strWord == "done") {
//                            exit(0);//TODO - check it man....!!!
//                        }
//                    } else {
//                        //handle expresion
//                        //TODO check if works
//                        vector<string> temp;
//                        temp.at(0) = word;
//                        cout << ShuntingYard(this->_table).calculateExpression(temp);
//                    }
//                }
//            }