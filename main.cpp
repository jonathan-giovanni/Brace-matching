#include <iostream>
#include <string>
#include <list>
using namespace std;

enum Position{
    LEFT=0,
    RIGHT=1,
    NONE=-1
};
struct Symbol{
    char symbol='X';
    Position p=NONE;
    int value=-1;
    int index=-1;
};
class Matching{
private:
    char openSymbols[3]={'(','[','{'};
    char closeSymbols[3]={')',']','}'};
    string document;
    int current_position;
public:
    Matching(string doc){
        this->document=doc;
    }
    Symbol isSymbol(int curr_pos){
        Symbol s;
        //if(document.length()-curr_pos<0 || curr_pos>=document.length()) return s;
        this->current_position = curr_pos;
        for(int i=0;i<3;i++){
            if(document[current_position]==openSymbols[i]){
               s.symbol=openSymbols[i];
               s.index=current_position;
               s.p=RIGHT;
               s.value=i;
               return s;
            }
            if(document[current_position]==closeSymbols[i]){
               s.symbol=closeSymbols[i];
               s.index=current_position;
               s.p=LEFT;
               s.value=i;
               return s;
            }
        }
        return s;
    }
    Symbol getMatch(Symbol symbol){
        Symbol t;
        list<Symbol> temp;
        if(symbol.index==-1) return symbol;
        if(symbol.p==RIGHT){
            temp.push_front(symbol);
            for(int i=this->current_position+1;i<document.length();i++){
                t = isSymbol(i);
                if(t.symbol==symbol.symbol)
                    temp.push_front(t);
                if(t.value==symbol.value && t.p==LEFT)
                    temp.pop_front();
                if(matched(symbol,t) && temp.empty()){
                    return t;
                }
            }
        }
        if(symbol.p==LEFT){
            temp.push_front(symbol);
            for(int i=this->current_position-1;i>=0;--i){
                t = isSymbol(i);
                if(t.symbol==symbol.symbol)
                    temp.push_front(t);
                if(t.value==symbol.value && t.p==RIGHT)
                    temp.pop_front();
                if(matched(t,symbol) && temp.empty()){
                    return t;
                }
            }
        }
        return t;
    }
    bool matched(Symbol s1,Symbol s2){
        if(s1.value == s2.value && s1.p!=s2.p) return true;
        else return false;
    }
    void printSymbol(Symbol s){

        cout << "\nSymbol : "<< s.symbol<<"\nPosition : "<<s.p<<"\nIndex : "<<s.index;
    }
};

int main()
{
    cout << "Find symbols" << endl;
    string test = "tsimple text(e{)}";
    Matching matching(test);
    int p=16;
    Symbol s = matching.getMatch( matching.isSymbol(p) );
    cout << test[p];
    matching.printSymbol(s);


    return 0;
}
