//vector.push_back()
//vector.at(int)
//vector.pop_back()
//vector. size clear front - first element, back - last element, empty - checks if empty, capacity - size of a vector memorywise
//vector.begin() or .end() - 1 ; after that just like any regular pointer
#include <iostream>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;
char separate_the_words_in_the_file='Ø';
char line_end_in_the_file='Ð';
char brackets[11]={185, 186, 187, 188, 200, 201, 202, 203, 204, 205, 206};

class Word
{
    private:
    string pl_word;

    public:
    vector<string> eng_words;
    Word(string pol, vector<string> eng){
        pl_word=pol;
        eng_words=eng;
    }
    string getPL(){
        return pl_word;
    }
    void setPL(string input){
        pl_word=input;
    }
    void Say(){
        cout << pl_word << " - ";
        for(int i=0; i<eng_words.size()-1; i++){
            cout << eng_words.at(i) << ", ";
        }
        cout << eng_words.back() << ". ";
        cout << endl;
    }
    ~Word(){}
};
void Read_ini(vector<Word> &YE){
    fstream file_pol;
    fstream file_eng;
    file_pol.open("POL.txt", ios::in); // I'll make the program only read the file upon launching, the program will reopen it only when the new words are added, so that .txt can be accessed anytime
    file_eng.open("ENG.txt", ios::in);
    int i=0;
    string line;
    vector<string> temp2;
    temp2.push_back(" ");
    Word temp("temp", temp2); // fix later that crap
    while(getline(file_pol, line)){
        YE.push_back(temp);
        //YE[i].pl_word=line;
        YE[i].setPL(line);
        i++;
    }
    i=0;
    string egl;
    int j=0;
    while(getline(file_eng, line)){ // reading each letter, forming words to save in eng_words of each "Word" object
        bool check=true;
        while(j<line.length()){
            if(line[j]!=separate_the_words_in_the_file && line[j]!=line_end_in_the_file){
                egl=egl+line[j];
                j++;
            }
            else if(line[j]==separate_the_words_in_the_file){
                if(check){
                    YE[i].eng_words.pop_back();
                    YE[i].eng_words.push_back(egl);
                    egl="";
                    j=j+2;
                    check=false;
                }else{
                    YE[i].eng_words.push_back(egl);
                    egl="";
                    j=j+2;
                }
                //finish the doubling eng_words at the end of each Word object *Update. DONE, IT WAS STUPID OUTPUT FUNCTION
            }
            else if(line[j]==line_end_in_the_file){
                j=j+4;
            }
        }
        egl="";
        i++;
        j=0;
    }
    temp.~Word();
    file_pol.close();
    file_eng.close();
}
void Revise(vector<Word> &YE){
    int pool=YE.size();
    cout << "Poda zatem na powtarzanie slowek! Nacisnij, aby kontynuowac...";
    getch();
    string ans;
    while(ans!="X"){
        cout << "W dowolnym momencie jesli chcesz skonczyc, wprowadz pojedyncze duze X";
    }
}
void Add(vector<Word> &YE){
    fstream file_pol;
    fstream file_eng;
    file_pol.open("POL.txt", ios::out | ios::app);
    file_eng.open("ENG.txt", ios::out | ios::app);
    cout << "zeby skonczyc podawanie slowek, nie ma znaczenia czy polskie czy angielskie, wprowadz XX" << endl;
    adding:
    string POLAND="";
    vector<string> NOT_POLAND;
    string eng_ans="";
    string one_line="";
    Word temp(POLAND, NOT_POLAND);
    cout << "Polskie slowo/objasnienie: ";//Outputs like that I'm going to move to some other file, so that they don't get corrupted by the improper format
    getline(cin, POLAND);
    if(POLAND!="XX"){
        while(eng_ans!="X" && eng_ans!="XX"){
            cout << "Angielskie slowo (jezeli to koniec, wprowadz samo duze X)";
            getline(cin, eng_ans);
            if(eng_ans!="X") NOT_POLAND.push_back(eng_ans);
        }
        int i=0;
        while(i<NOT_POLAND.size()){
            one_line=one_line+NOT_POLAND[i];
            one_line=one_line+separate_the_words_in_the_file+' ';
            i++;
        }
        one_line=one_line+line_end_in_the_file;
        YE.push_back(temp);
        file_pol << POLAND << endl;
        file_eng << one_line << endl;
        temp.~Word();
        POLAND="";
        NOT_POLAND.clear();
        if(eng_ans!="XX"){
            goto adding;
        }
    }
    temp.~Word();
    POLAND="";
    one_line="";
    NOT_POLAND.clear();
    //will implement goto here, XX will stop procedure, X will stop adding just English words, that's the idea
    file_pol.close();
    file_eng.close();
}
void Illustrate(vector<Word> &YE){
    for(int i=0; i<YE.size(); i++){ //that will be cout's function job
        YE[i].Say();
    }
    getch();
    return;
}
void case1(int capa, int wide){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << endl << endl;
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[1] << " > ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
}
void case2(int capa, int wide){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << endl << endl;
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
}
void case3(int capa, int wide){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << endl << endl;
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
}
void case4(int capa, int wide){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << endl << endl;
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << endl;
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
}
void Interface(vector<Word> &YE){
    //72 - up_arrow
    //75 - left_arrow
    //80 - down_arrow
    //77 - right_arrow
    //concept here - either revise some new words, add new ones or cout everything, decision managed here
    int capa=60; //length of the window
    int wide=1; //margin for the top and the bottom
    int poss=3; // possibilities of reacting
    menu:
    case2(capa, wide);
    short choice=1;
    decide_moron:
    switch(getch()){
        case 72: {choice--; if(choice<0){choice=poss;}
            if(choice==0) case1(capa, wide);
            if(choice==1) case2(capa, wide);
            if(choice==2) case3(capa, wide);
            if(choice==3) case4(capa, wide);
        } break;
        case 80: {choice++; if(choice>poss){choice=0;}
            if(choice==0) case1(capa, wide);
            if(choice==1) case2(capa, wide);
            if(choice==2) case3(capa, wide);
            if(choice==3) case4(capa, wide);
        } break;
        case 13: {system("cls");
            cout << "Proceeding..." << endl;
            if(choice==0) {system("cls"); cout << "To be finished..."; goto menu;}
            if(choice==1) {system("cls"); Add(YE); goto menu;}
            if(choice==2) {system("cls"); Illustrate(YE); goto menu;}
            if(choice==3) {system("cls"); cout << "Dzieki za skorzystanie z programu! "; cout << "Nacisnij cokolwiek, aby kontynuowac" << endl; system("pause"); exit(0);};
        } break;
        default: {cout << endl; goto decide_moron;}
    }
    goto decide_moron;
    //system("cls");
}
int main()
{
    vector<Word> YE;
    vector<string> outputs;
    srand(time(NULL));
    //cout << separate_the_words_in_the_file;
    //cout << line_end_in_the_file;
    Read_ini(YE);
    Interface(YE);
    //Add(YE);
    return 0;
}
