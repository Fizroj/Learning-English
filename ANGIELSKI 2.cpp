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
#include <locale>
#include <queue>
using namespace std;
char separate_the_words_in_the_file=252;
char line_end_in_the_file=209;
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
    void Say(){ //useful for Illustrate func
        cout << pl_word << " - ";
        for(int i=0; i<eng_words.size()-1; i++){
            cout << eng_words.at(i) << ", ";
        }
        cout << eng_words.back() << ". ";
        cout << endl;
    }
    string Ask(){ //useful for Revise func
        string ANS;
        cout << getPL() << " - ";
        getline(cin, ANS);
        return ANS;
    }
    bool Check(string ANS){
        int NUM=eng_words.size(); //number of possible English words to choose from
        for(int i=0; i<NUM; i++){
            if(ANS==eng_words.at(i)){
                return true;
            }
        }
        return false;
    }
    void Other_Ones(string ANS){
        int NUM=eng_words.size(); //number of possible English words to choose from
        for(int i=0; i<NUM; i++){
            if(eng_words.at(i)!=ANS) cout << eng_words.at(i) << ", ";
        }
        cout << endl;
    }
    ~Word(){}
};
void Read_ini(vector<Word> &YE, string file1, string file2){
    fstream file_pol;
    fstream file_eng;
    //setlocale(LC_ALL, "");
    file_pol.open(file1.c_str(), ios::out | ios::app);
    file_eng.open(file2.c_str(), ios::out | ios::app);
    if (!file_pol.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
    if (!file_eng.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
    file_pol.close();
    file_eng.close();
    file_pol.open(file1.c_str(), ios::in); // I'll make the program only read the file upon launching, the program will reopen it only when the new words are added, so that .txt can be accessed anytime
    file_eng.open(file2.c_str(), ios::in);
    if (!file_pol.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
    if (!file_eng.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
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
        //cout << line;
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
    //setlocale(LC_CTYPE, "en_US.UTF-8");
}
bool Is_There(int A, queue<int> B){
    int S=B.size();
    for(int i=0; i<S; i++){
            //cout << B.front() << " ";
            if(A==B.front()) {return true;}
            B.pop();
    }
    return false;
}
void Revise(vector<Word> &YE){
    int pool=YE.size(); //all avaible Words
    int ans_id; //id of a word answered coorectly
    int que; //question id
    queue<int> been_already; //stores id's of flashcards that have been previously shown
    cout << "Poda zatem na powtarzanie slowek!";
    string ans; //what user inputs as an answer
    cout << "Jesli chcesz skonczyc, w dowolnym momencie wprowadz pojedyncze duze X" << endl;
    while(ans!="X"){
        for(int i=0; i<62; i++){
            cout << brackets[9];
        }
        cout << endl;
        do{
            que=rand()%pool;
        }while(Is_There(que, been_already));
        been_already.push(que);
        if(been_already.size()>5) been_already.pop();
        //cout << been_already.size();
        ans=YE.at(que).Ask();
        if(YE.at(que).Check(ans)){
            cout << "Dobra odpowiedz! Inne poprawne odpowiedzi: ";
            YE.at(que).Other_Ones(ans);
        }
        else{
            cout << "To nie to... Poprawne odpowiedzi to: ";
            YE.at(que).Other_Ones("X");
        }
    }
}
void Add(vector<Word> &YE){
    fstream file_pol;
    fstream file_eng;
    file_pol.open("POL.txt", ios::out | ios::app);
    file_eng.open("ENG.txt", ios::out | ios::app);
    cout << "zeby skonczyc podawanie slowek, nie ma znaczenia czy polskie czy angielskie, wprowadz XX" << endl;
    int i=0;
    string POLAND="";
    vector<string> NOT_POLAND;
    string eng_ans="";
    string one_line="";
    adding:
    cout << "Polskie slowo/objasnienie: ";//Outputs like that I'm going to move to some other file, so that they don't get corrupted by the improper format
    getline(cin, POLAND);
    if(POLAND!="XX"){
        while(eng_ans!="X" && eng_ans!="XX"){
            cout << "Angielskie slowo (jezeli to koniec, wprowadz samo duze X)";
            getline(cin, eng_ans);
            if(eng_ans!="X" && eng_ans!="XX") NOT_POLAND.push_back(eng_ans);
        }

        while(i<NOT_POLAND.size()){
            one_line=one_line+NOT_POLAND[i];
            one_line=one_line+separate_the_words_in_the_file+' ';
            i++;
        }
        i=0;
        one_line=one_line+line_end_in_the_file;
        file_pol << POLAND << endl;
        file_eng << one_line << endl;
        Word temp(POLAND, NOT_POLAND);
        YE.push_back(temp);
        if(eng_ans!="XX"){
            POLAND="";
            NOT_POLAND.clear();
            eng_ans="";
            one_line="";
            //temp.~Word();
            goto adding;
        }
    }
    //POLAND="";
    //one_line="";
    //NOT_POLAND.clear();
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
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
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
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
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
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
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
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
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
void case5(int capa, int wide){
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
    cout << brackets[1] << "   ";
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
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
void case4_1(int capa, int wide, vector<string> options){
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
    cout << options.at(0);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(1);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(2);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(3);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(4);
    for(int j=0; j<capa-10; j++){
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
void case4_2(int capa, int wide, vector<string> options){
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
    cout << options.at(0);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << options.at(1);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(2);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(3);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(4);
    for(int j=0; j<capa-10; j++){
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
void case4_3(int capa, int wide, vector<string> options){
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
    cout << options.at(0);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(1);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << options.at(2);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(3);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(4);
    for(int j=0; j<capa-10; j++){
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
void case4_4(int capa, int wide, vector<string> options){
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
    cout << options.at(0);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(1);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(2);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << options.at(3);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(4);
    for(int j=0; j<capa-10; j++){
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
void case4_5(int capa, int wide, vector<string> options){
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
    cout << options.at(0);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(1);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(2);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << "   ";
    cout << options.at(3);
    for(int j=0; j<capa-10; j++){
        cout << " ";
    }
    cout << brackets[1] << endl;
    //
    cout << brackets[1] << " > ";
    cout << options.at(4);
    for(int j=0; j<capa-10; j++){
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
int Interface_Choose(vector<Word> &YE){
    
    return 0;
}
void Interface(vector<Word> &YE){
    //72 - up_arrow
    //75 - left_arrow
    //80 - down_arrow
    //77 - right_arrow
    //concept here - either revise some new words, add new ones or cout everything, decision managed here
    int capa=60; //length of the window
    int wide=1; //margin for the top and the bottom
    int poss=4; // ossibilities of reacting
    fstream file_opt;
    vector<string> options;
    file_opt.open("Options.txt", ios::out | ios::app);
    if(!file_opt.good()){
        cerr << "Nie da sie wczytac opcji";
        exit(0);
    }
    file_opt.close();
    file_opt.open("Options.txt", ios::in);
    if(!file_opt.good()){
        cerr << "Nie da sie wczytac opcji";
        exit(0);
    }
    string line;
    while(getline(file_opt, line)){
        options.push_back(line);
    }
    for(int i=0; i<5; i++){
        options.push_back("<emtpy>");
    }
    file_opt.close();
    menu:
    case1(capa, wide);
    short choice=0;
    decide_moron:
    switch(getch()){
        case 72: {choice--; if(choice<0){choice=poss;}
            if(choice==0) case1(capa, wide);
            if(choice==1) case2(capa, wide);
            if(choice==2) case3(capa, wide);
            if(choice==3) case4(capa, wide);
            if(choice==4) case5(capa, wide);
        } break;
        case 80: {choice++; if(choice>poss){choice=0;}
            if(choice==0) case1(capa, wide);
            if(choice==1) case2(capa, wide);
            if(choice==2) case3(capa, wide);
            if(choice==3) case4(capa, wide);
            if(choice==4) case5(capa, wide);
        } break;
        case 13: {system("cls");
            cout << "Loading..." << endl;
            if(choice==0) {system("cls"); Revise(YE); goto menu;}
            if(choice==1) {system("cls"); Add(YE); goto menu;}
            if(choice==2) {system("cls"); Illustrate(YE); goto menu;}
            if(choice==3) {system("cls"); Interface_Choose(YE, options); goto menu;}
            if(choice==4) {system("cls"); cout << "Dzieki za skorzystanie z programu! Nacisnij cokolwiek, aby kontynuowac" << endl; system("pause"); exit(0);};
        } break;
        default: {cout << endl; goto decide_moron;}
    }
    goto decide_moron;
}
int main()
{
    vector<Word> YE;
    vector<string> outputs; //probably ill store here all the outputs for the program in a different file, so reading it wont get corrupted again
    srand(time(NULL));
    Read_ini(YE, "POL.txt", "ENG.txt");
    Interface(YE);
    return 0;
}
//ideas
//create categories of revised words, each can be stored in different files, i can afford that with .c_str() func
//deleting unwanted word, possibly inputed wrong (probably can be done in a matter of a single func)
//
