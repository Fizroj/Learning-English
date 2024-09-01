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
char separate_the_words_in_the_file=432 ;//252;
char line_end_in_the_file=433; //209;
char brackets[11]={185, 186, 187, 188, 200, 201, 202, 203, 204, 205, 206};
string files[10]={"POL_1.txt", "ENG_1.txt", "POL_2.txt", "ENG_2.txt", "POL_3.txt", "ENG_3.txt", "POL_4.txt", "ENG_4.txt", "POL_5.txt", "ENG_5.txt"};
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
        cout << "\n";
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
void Read(vector<Word> &YE, string file1, string file2){
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
int Read_Opt(string options[]){
    fstream file_opt;
    fstream what;
    int previous=0; //previous words used by the user
    string previous_s;
    file_opt.open("Options.txt", ios::out | ios::app);
    if(!file_opt.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    file_opt.close();
    what.open("what.txt", ios::out | ios::app);
    if(!what.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    what.close();
    what.open("what.txt", ios::in);
    if(!what.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    string line;
    while(getline(what, line)){
            previous_s=line;
            if(previous_s=="1") previous=1;
            else if(previous_s=="2") previous=2;
            else if(previous_s=="3") previous=3;
            else if(previous_s=="4") previous=4;
            else if(previous_s=="5") previous=5;
            else previous=0;
    }
    what.close();
    file_opt.open("Options.txt", ios::in);
    if(!file_opt.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    string line_2;
    int cnt=0;
    while(getline(file_opt, line_2)){
        //cout << line_2 << endl;
        if(line_2[0]=='1'){
            options[0]="";
            for(int i=2; i<line_2.length(); i++){
                options[0]=options[0]+line_2[i];
            }
        }
        if(line_2[0]=='2'){
            options[1]="";
            for(int i=2; i<line_2.length(); i++){
                options[1]=options[1]+line_2[i];
            }
        }
        if(line_2[0]=='3'){
            options[2]="";
            for(int i=2; i<line_2.length(); i++){
                options[2]=options[2]+line_2[i];
            }
        }
        if(line_2[0]=='4'){
            options[3]="";
            for(int i=2; i<line_2.length(); i++){
                options[3]=options[3]+line_2[i];
            }
        }
        if(line_2[0]=='5'){
            options[4]="";
            for(int i=2; i<line_2.length(); i++){
                options[4]=options[4]+line_2[i];
            }
        }
        //else break;
        cnt++;
    }
    //cout << "    " << cnt << "    " << endl;
    file_opt.close();
    return previous; //returning what was previous alias the user have been using before closing the program
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
void Revise(vector<Word> YE){
    int pool=YE.size(); //all avaible Words
    int ans_id; //id of a word answered coorectly
    int que; //question id
    int limit=pool-1; //limit of questions blocked to prevent back-to-back repeating
    if(limit>5){limit=5;}
    queue<int> been_already; //stores id's of words that have been previously shown
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
        //if(pool<=limit){}//repair the issue when you have less than 5 words
        been_already.push(que);
        if(been_already.size()>limit) been_already.pop();
        //cout << been_already.size();
        ans=YE.at(que).Ask();
        if(ans=="X"){break;}
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
void Add(vector<Word> &YE, string filepol, string fileeng){
    fstream file_pol;
    fstream file_eng;
    fstream file_polB;
    fstream file_engB;
    //.....youuuu, you stole my damn words
    file_pol.open(filepol.c_str(), ios::out | ios::app);
    if(!file_pol.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    file_eng.open(fileeng.c_str(), ios::out | ios::app);
    if(!file_eng.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    file_polB.open("POL_backup.txt", ios::out | ios::app);
    if(!file_polB.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    file_engB.open("ENG_backup.txt", ios::out | ios::app);
    if(!file_engB.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    cout << "Podawaj polskie slowko/definicje, a potem angielskie slowka, ktore sa dobrym tlumaczeniem. Poniewaz moze byc wiecej niz jedno poprawne tlumaczenie, wprowadz pojedyncze X aby zakonczyc podawanie angielskich slowek";
    cout << ", a jezeli chcesz calkowicie skonczyc dodawanie slowek, wprowadz XX w dowolnym momencie. Pamietaj, ze program zapisze Twoje inputy tylko wtedy, gdy podasz polskie slowko i przynajmniej jedno angielskie!" << "\n" << "\n" << endl;
    int i=0;
    string POLAND="";
    vector<string> NOT_POLAND;
    string eng_ans="";
    string one_line="";
    //bool atLeastOne=false;
    adding:
    cout << "Polskie slowo/objasnienie: ";//Outputs like that I'm going to move to some other file, so that they don't get corrupted by the improper format
    getline(cin, POLAND);
    if(POLAND!="XX"){
        while(eng_ans!="X" && eng_ans!="XX"){
            cout << "Angielskie slowo (jezeli to koniec, wprowadz samo duze X)";
            getline(cin, eng_ans);
            if(eng_ans!="X" && eng_ans!="XX"){NOT_POLAND.push_back(eng_ans);}
        }

        while(i<NOT_POLAND.size()){
            one_line=one_line+NOT_POLAND[i];
            one_line=one_line+separate_the_words_in_the_file+' ';
            i++;
        }
        i=0;
        if(NOT_POLAND.empty()){
            cout << "Nie podales zadnego slowka po angielsku!" << endl;
            POLAND="";
            NOT_POLAND.clear();
            eng_ans="";
            one_line="";
            //temp.~Word();
            for(int i=0; i<62; i++){
                cout << brackets[9];
            }
            goto adding;
        }
        else{
            one_line=one_line+line_end_in_the_file;
            file_pol << POLAND << endl;
            file_eng << one_line << endl;
            file_polB << POLAND << endl;
            file_engB << one_line << endl;
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
    }
    //POLAND="";
    //one_line="";
    //NOT_POLAND.clear();
    //will implement goto here, XX will stop procedure, X will stop adding just English words, that's the idea
    file_pol.close();
    file_eng.close();
    file_polB.close();
    file_engB.close();
}
void Illustrate(vector<Word> YE){
    for(int i=0; i<YE.size(); i++){ //that will be cout's function job
        YE[i].Say();
    }
    getch();
    return;
}
void case1(int capa, int wide, int prev, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n";
    cout << "Current category: ";
    if(prev==0){cout << "<not created/chosen>" << "\n";}
    else if(options[prev-1]=="<empty>"){cout << "<not created/chosen>" << "\n";}
    else cout << options[prev-1] << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << " > ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case2(int capa, int wide, int prev, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n";
    cout << "Current category: ";
    if(prev==0){cout << "<not created/chosen>" << "\n";}
    else if(options[prev-1]=="<empty>"){cout << "<not created/chosen>" << "\n";}
    else cout << options[prev-1] << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case3(int capa, int wide, int prev, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n";
    cout << "Current category: ";
    if(prev==0){cout << "<not created/chosen>" << "\n";}
    else if(options[prev-1]=="<empty>"){cout << "<not created/chosen>" << "\n";}
    else cout << options[prev-1] << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case4(int capa, int wide, int prev, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n";
    cout << "Current category: ";
    if(prev==0){cout << "<not created/chosen>" << "\n";}
    else if(options[prev-1]=="<empty>"){cout << "<not created/chosen>" << "\n";}
    else cout << options[prev-1] << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case5(int capa, int wide, int prev, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n";
    cout << "Current category: ";
    if(prev==0){cout << "<not created/chosen>" << "\n";}
    else if(options[prev-1]=="<empty>"){cout << "<not created/chosen>" << "\n";}
    else cout << options[prev-1] << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << "Revise Words";
    for(int j=0; j<capa-15; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Add New Words";
    for(int j=0; j<capa-16; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Display All Words";
    for(int j=0; j<capa-20; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << "Choose category";
    for(int j=0; j<capa-18; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << "Exit";
    for(int j=0; j<capa-7; j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case4_1(int capa, int wide, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n" << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << " > ";
    cout << options[0];
    for(int j=0; j<capa-3-(options[0].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[1];
    for(int j=0; j<capa-3-(options[1].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[2];
    for(int j=0; j<capa-3-(options[2].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[3];
    for(int j=0; j<capa-3-(options[3].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[4];
    for(int j=0; j<capa-3-(options[4].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case4_2(int capa, int wide, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n" << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << options[0];
    for(int j=0; j<capa-3-(options[0].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << options[1];
    for(int j=0; j<capa-3-(options[1].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[2];
    for(int j=0; j<capa-3-(options[2].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[3];
    for(int j=0; j<capa-3-(options[3].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[4];
    for(int j=0; j<capa-3-(options[4].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case4_3(int capa, int wide, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n" << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << options[0];
    for(int j=0; j<capa-3-(options[0].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[1];
    for(int j=0; j<capa-3-(options[1].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << options[2];
    for(int j=0; j<capa-3-(options[2].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[3];
    for(int j=0; j<capa-3-(options[3].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[4];
    for(int j=0; j<capa-3-(options[4].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case4_4(int capa, int wide, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n" << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << options[0];
    for(int j=0; j<capa-3-(options[0].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[1];
    for(int j=0; j<capa-3-(options[1].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[2];
    for(int j=0; j<capa-3-(options[2].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << options[3];
    for(int j=0; j<capa-3-(options[3].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[4];
    for(int j=0; j<capa-3-(options[4].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void case4_5(int capa, int wide, string options[]){
    system("cls");
    cout << "Acceptable inputs: down arrow, up arrow or Enter." << "\n" << "\n";
    cout << brackets[5];  //formula for the top
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[2] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[1] << "   ";
    cout << options[0];
    for(int j=0; j<capa-3-(options[0].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[1];
    for(int j=0; j<capa-3-(options[1].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[2];
    for(int j=0; j<capa-3-(options[2].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << "   ";
    cout << options[3];
    for(int j=0; j<capa-3-(options[3].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    cout << brackets[1] << " > ";
    cout << options[4];
    for(int j=0; j<capa-3-(options[4].length()); j++){
        cout << " ";
    }
    cout << brackets[1] << "\n";
    //
    for(int i=0; i<wide; i++){ //formula for the empty line
        cout << brackets[1];
        for(int j=0; j<capa; j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    cout << brackets[4];
    for(int i=0; i<capa; i++){
        cout << brackets[9];
    }
    cout << brackets[3];
    cout << endl;
}
void New_Category(int CHOICE, string options[]){
    string name;
    string line_out;
    cout << "Wyglada na to, ze tworzysz nowy katalog. Jak chcialbys go nazwac? " << endl;
    ur_empty:
    cout << " > ";
    getline(cin, name);
    if(name=="<empty>"){cout << "Wez moze cos innego, ta nazwe juz zaklepalem..."; goto ur_empty;}
    if(name.length()>52){cout << "Ta nazwa jest troche za dluga..."; goto ur_empty;}
    fstream file_opt;
    file_opt.open("Options.txt", ios::out | ios::app);
    if(!file_opt.good()){
        cerr << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    switch(CHOICE){
        case 0: {line_out=line_out+"1 "; options[0]=name; break;}
        case 1: {line_out=line_out+"2 "; options[1]=name; break;}
        case 2: {line_out=line_out+"3 "; options[2]=name; break;}
        case 3: {line_out=line_out+"4 "; options[3]=name; break;}
        case 4: {line_out=line_out+"5 "; options[4]=name; break;}
        default: break;
    }
    line_out=line_out+name;
    file_opt << line_out << endl;
    file_opt.close();
}
int Interface_Choose(vector<Word> &YE, string options[]){
    int capa=60; //length of the window
    int wide=1; //margin for the top and the bottom
    int poss=4; // possibilities of reacting
    //the same drill with switch()
    case4_1(capa, wide, options);
    short choice_2=0;
    decide_moron_2:
    switch(getch()){
        case 72: {choice_2--; if(choice_2<0){choice_2=poss;}
            if(choice_2==0) case4_1(capa, wide, options);
            if(choice_2==1) case4_2(capa, wide, options);
            if(choice_2==2) case4_3(capa, wide, options);
            if(choice_2==3) case4_4(capa, wide, options);
            if(choice_2==4) case4_5(capa, wide, options);
        } break;
        case 80: {choice_2++; if(choice_2>poss){choice_2=0;}
            if(choice_2==0) case4_1(capa, wide, options);
            if(choice_2==1) case4_2(capa, wide, options);
            if(choice_2==2) case4_3(capa, wide, options);
            if(choice_2==3) case4_4(capa, wide, options);
            if(choice_2==4) case4_5(capa, wide, options);
        } break;
        case 13: {system("cls");
            cout << "Loading..." << endl;
            if(choice_2==0) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; YE.clear(); Read(YE, files[0], files[1]); return choice_2+1;} //Read(YE, files[0], files[1]);
            if(choice_2==1) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; YE.clear(); Read(YE, files[2], files[3]); return choice_2+1;} //Read(YE, files[2], files[3]);
            if(choice_2==2) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; YE.clear(); Read(YE, files[4], files[5]); return choice_2+1;} //Read(YE, files[4], files[5]);
            if(choice_2==3) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; YE.clear(); Read(YE, files[6], files[7]); return choice_2+1;} //Read(YE, files[6], files[7]);
            if(choice_2==4) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; YE.clear(); Read(YE, files[8], files[9]); return choice_2+1;} //Read(YE, files[8], files[9]);
        } break;
        default: {cout << endl; goto decide_moron_2;}
    }
    goto decide_moron_2;
}
int Interface(vector<Word> &YE, int prev, string options[]){
    //72 - up_arrow
    //75 - left_arrow
    //80 - down_arrow
    //77 - right_arrow
    //concept here - either revise some new words, add new ones or cout everything, decision managed here
    int capa=60; //length of the window
    int wide=1; //margin for the top and the bottom
    int poss=4; // possibilities of reacting
    int last=prev; //last category used before closing
    menu:
    case1(capa, wide, prev, options);
    short choice=0;
    //cout << options.size();
    decide_moron:
    switch(getch()){
        case 72: {choice--; if(choice<0){choice=poss;}
            if(choice==0) case1(capa, wide, prev, options);
            if(choice==1) case2(capa, wide, prev, options);
            if(choice==2) case3(capa, wide, prev, options);
            if(choice==3) case4(capa, wide, prev, options);
            if(choice==4) case5(capa, wide, prev, options);
        } break;
        case 80: {choice++; if(choice>poss){choice=0;}
            if(choice==0) case1(capa, wide, prev, options);
            if(choice==1) case2(capa, wide, prev, options);
            if(choice==2) case3(capa, wide, prev, options);
            if(choice==3) case4(capa, wide, prev, options);
            if(choice==4) case5(capa, wide, prev, options);
        } break;
        case 13: {system("cls");
            cout << "Loading..." << endl;
            if(choice==0) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;} else if(YE.empty()){cout << "Nie ma dodanych slowek! Dodaj jakies" << endl; system("pause"); goto menu;} Revise(YE); goto menu;}
            if(choice==1) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;}; Add(YE, files[(2*prev)-2], files[(2*prev)-1]); goto menu;}
            if(choice==2) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;} else if(YE.empty()){cout << "Nie ma dodanych slowek! Dodaj jakies" << endl; system("pause"); goto menu;} Illustrate(YE); goto menu;}
            if(choice==3) {system("cls"); last=Interface_Choose(YE, options); prev=last; goto menu;}
            if(choice==4) {system("cls"); return last;};
        } break;
        default: {goto decide_moron;}
    }
    goto decide_moron;
}
int main()
{
    vector<Word> YE;
    vector<string> outputs; //probably ill store here all the outputs for the program in a different file, so reading it wont get corrupted again
    srand(time(NULL));
    string options[5]={"<empty>", "<empty>", "<empty>", "<empty>", "<empty>"};
    int prev=0;
    char ue=432;
    //cout << "a" << endl;
    prev=Read_Opt(options);
    //prev++;
    //cout << "b" << endl;
    if(prev==1) Read(YE, files[0], files[1]);
    else if(prev==2) Read(YE, files[2], files[3]);
    else if(prev==3) Read(YE, files[4], files[5]);
    else if(prev==4) Read(YE, files[6], files[7]);
    else if(prev==5) Read(YE, files[8], files[9]);
    //cout << prev << " " << ue;
    //cout << options[prev-1];
    cout << "W razie potrzeby zwieksz rozmiar okna aby program lepiej wygladal XD" << "\n";
    system("pause");
    //else Read(YE, "POL.txt", "ENG.txt");
    //maybe implement here, that the program remembers what were the last revised words, prolly in that options file as well
    prev=Interface(YE, prev, options);
    fstream what;
    what.open("what.txt", ios::out);
    what << prev;
    what.close();
    cout << "Dzieki za skorzystanie z programu! Nacisnij cokolwiek, aby zakonczyc" << endl; system("pause");
    return 0;
}
//ideas
//create categories of revised words, each can be stored in different files, i can afford that with .c_str() func [YES]
//implement menu for naming a new category [OYE]
//fix that output weirdo in naming categories [DONE]
//new problem, prev-1 goes out of bound for cout when user launches for the first time, fix this [FIXED (probably)]
//display that user have not added any words when trying to revise or view them [ok i guess]
//deleting unwanted word, possibly inputed wrong (probably can be done in a matter of a single func)
//and work on that encoding shit [hopefully everything in place]
//less than 5 words in Revise() causes problems [NOT ANYMORE]
