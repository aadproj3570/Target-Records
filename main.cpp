#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

string lower(const string & str) {

  string lowstr;
  for(int i = 0; i < str.size(); i++) {
    lowstr.push_back(tolower(str[i]));
  }
  return lowstr;
}

void recordSearch(vector <string> arr, ostream& out, string s, int l, int r, int level) {

    int middle = (l + r) / 2;
    if(l == r) {
      if(lower(arr[l]).find(lower(s)) != string::npos) {
        out << "Level " << level << ": " << arr[r] << endl;
      }
    } else if(r - l > 0) {
      //cout << l << ' ' << r << endl;
      recordSearch(arr, out, s, l, middle, level + 1);
      recordSearch(arr, out, s, middle + 1, r, level + 1);
    }
}

int main(int argc, char* argv[])
{

    ArgumentManager am(argc, argv);
    string ifile = am.get("input"); //get the filename of argument name "input"
    string ofile = am.get("output"); //get the filename of argument name "output"
    string cfile = am.get("command");
    ifstream input(ifile);
    ifstream command(cfile);
    ofstream output(ofile);
    output << "";

    string s;
    command >> s;

    int idx;
    string data, str, temp;

    if(s != "") {
      while(getline(input, str)) {
        for(int i = 0; i < str.size(); i++) {
          if(str[i] != ' ' && str[i] != '\r' && str[i] != '\n') {
            data += str[i];
          }
        }
      }
    vector <string> arr;
    for(int i = 0; i < data.size(); i++) {
      int beg = data.find('{');
      int end = data.find('}') + 1;
      string record = data.substr(beg,end-beg);
      arr.push_back(record);
      data.erase(beg,end-beg);
      }
    recordSearch(arr, output, lower(s), 0, arr.size() - 1, 0);
    }
    output.flush();
    output.close();

    return 0;
}