#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include <dirent.h>

using namespace std;

int main(){
    set<string> a;
    a.insert("bmw");
    a.insert("mercedes");
    
    map<string,set<string> > car;
    car.insert(make_pair("felipe rafael", a));
    for(auto i : car)
    {
        cout << i.first << " :" <<endl;
        for (auto j : i.second){
            cout << j << " ";
        }
        cout << endl;
    }
    system("pause");

    return 0;
}