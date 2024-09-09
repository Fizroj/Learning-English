//vector.push_back()
//vector.at(int)
//vector.pop_back()
//vector. size clear front - first element, back - last element, empty - checks if empty, capacity - size of a vector memorywise
//vector.begin() or .end() - 1 ; after that just like any regular pointer
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <queue>
using namespace std;
const char separate_the_words_in_the_file=432 ;//252; //why doesn't unsigned work???
const char line_end_in_the_file=433; //209;
const char brackets[11]={185, 186, 187, 188, 200, 201, 202, 203, 204, 205, 206};
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
        if(eng_words.size()==1){
            cout << eng_words.front() << ".";
        }
        else if(eng_words.back()!=ANS){
            for(int i=0; i<NUM-1; i++){
                if(eng_words.at(i)!=ANS) cout << eng_words.at(i) << ", ";
            }
            cout << eng_words.back() << ".";
        }
        else{
            for(int i=0; i<NUM-2; i++){
                if(eng_words.at(i)!=ANS) cout << eng_words.at(i) << ", ";
            }
            cout << eng_words.at(NUM-2) << ".";
        }
        cout << endl;
    }
    ~Word(){}
};
void Read(vector<Word> &PEW, string file1, string file2){
    fstream file_pol;
    fstream file_eng;
    //setlocale(LC_ALL, "");
    file_pol.open(file1.c_str(), ios::out | ios::app);
    file_eng.open(file2.c_str(), ios::out | ios::app);
    if (!file_pol.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        exit(0);
    }
    if (!file_eng.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        exit(0);
    }
    file_pol.close();
    file_eng.close();
    file_pol.open(file1.c_str(), ios::in); // I'll make the program only read the file upon launching, the program will reopen it only when the new words are added, so that .txt can be accessed anytime
    file_eng.open(file2.c_str(), ios::in);
    if (!file_pol.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        exit(0);
    }
    if (!file_eng.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        exit(0);
    }
    int i=0;
    string line;
    vector<string> temp2;
    temp2.push_back(" ");
    Word temp("temp", temp2); // fix later that crap
    while(getline(file_pol, line)){
        PEW.push_back(temp);
        //YE[i].pl_word=line;
        PEW[i].setPL(line);
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
                    PEW[i].eng_words.pop_back();
                    PEW[i].eng_words.push_back(egl);
                    egl="";
                    j=j+2;
                    check=false;
                }else{
                    PEW[i].eng_words.push_back(egl);
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
    char previous_char;
    char previous_char_2;
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
            previous_char=line[0];
            switch(previous_char){
                case '1': {previous=1; break;}
                case '2': {previous=2; break;}
                case '3': {previous=3; break;}
                case '4': {previous=4; break;}
                case '5': {previous=5; break;}
                default:  {previous=0; break;}
            }
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
void Remove_the_Word(vector<Word> PEW, string file_name_p, string file_name_n, int line_n){ //work on this, bc it doesn't erase the last word supposedly already erased...
    fstream file_p;
    fstream file_e;
    string one_line="";
    file_p.open(file_name_p.c_str(), ios::out);
    if (!file_p.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
    file_e.open(file_name_n.c_str(), ios::out);
    if (!file_e.good()) {
        cerr << "Nie mozna otworzyc pliku" << endl;
        return;
    }
    int j=0;
    for(int i=0; i<PEW.size(); i++){
        if(i==line_n-1){continue;}
        while(j<PEW.at(i).eng_words.size()){
            one_line=one_line+PEW.at(i).eng_words.at(j)+separate_the_words_in_the_file+' ';
            j++;
        }
        j=0;
        one_line=one_line+line_end_in_the_file;
        file_p << PEW.at(i).getPL() << endl;
        file_e << one_line << endl;
        one_line="";
    }
    file_p.close();
    file_e.close();
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
void Revise(vector<Word> PEW){
    int pool=PEW.size(); //all avaible Words
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
        ans=PEW.at(que).Ask();
        if(ans=="X"){break;}
        if(PEW.at(que).Check(ans) && PEW.at(que).eng_words.size()==1){
            cout << "Dobra odpowiedz!";
        }
        else if(PEW.at(que).Check(ans) && PEW.at(que).eng_words.size()>1){
            cout << "Dobra odpowiedz! Inne poprawne odpowiedzi: ";
            PEW.at(que).Other_Ones(ans);
        }
        else if(!PEW.at(que).Check(ans) && PEW.at(que).eng_words.size()==1){
            cout << "To nie to... Poprawna odpowiedz to: ";
            PEW.at(que).Other_Ones("X");
        }
        else{
            cout << "To nie to... Poprawne odpowiedzi to: ";
            PEW.at(que).Other_Ones("X");
        }
        cout << endl;
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
void Illustrate(vector<Word> PEW){
    for(int i=0; i<PEW.size(); i++){ //that will be cout's function job
        cout << i+1 << ". ";
        PEW[i].Say();
    }
    return;
}
void Cases_of_menu(int capa, int wide, int prev, string options[], int which){
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
    if(which==1){
        cout << brackets[1] << " > ";
        cout << "Revise Words";
        for(int j=0; j<capa-15; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
        cout << brackets[1] << "   ";
        cout << "Revise Words";
        for(int j=0; j<capa-15; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which==2){
        cout << brackets[1] << " > ";
        cout << "Add New Words";
        for(int j=0; j<capa-16; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
        cout << brackets[1] << "   ";
        cout << "Add New Words";
        for(int j=0; j<capa-16; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which==3){
        cout << brackets[1] << " > ";
        cout << "Remove Words";
        for(int j=0; j<capa-15; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
        cout << brackets[1] << "   ";
        cout << "Remove Words";
        for(int j=0; j<capa-15; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which==4){
        cout << brackets[1] << " > ";
        cout << "Display All Words";
        for(int j=0; j<capa-20; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
        cout << brackets[1] << "   ";
        cout << "Display All Words";
        for(int j=0; j<capa-20; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which==5){
        cout << brackets[1] << " > ";
        cout << "Choose Category";
        for(int j=0; j<capa-18; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
        cout << brackets[1] << "   ";
        cout << "Choose Category";
        for(int j=0; j<capa-18; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which==6){
        cout << brackets[1] << " > ";
        cout << "Exit";
        for(int j=0; j<capa-7; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
        cout << brackets[1] << "   ";
        cout << "Exit";
        for(int j=0; j<capa-7; j++){
        cout << " ";
        }
        cout << brackets[1] << "\n";
    }
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
void Cases_of_categories(int capa, int wide, string options[], int which_2){
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
    if(which_2==1){
        cout << brackets[1] << " > ";
        cout << options[0];
        for(int j=0; j<capa-3-(options[0].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
         cout << brackets[1] << "   ";
        cout << options[0];
        for(int j=0; j<capa-3-(options[0].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which_2==2){
        cout << brackets[1] << " > ";
        cout << options[1];
        for(int j=0; j<capa-3-(options[1].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
         cout << brackets[1] << "   ";
        cout << options[1];
        for(int j=0; j<capa-3-(options[1].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which_2==3){
        cout << brackets[1] << " > ";
        cout << options[2];
        for(int j=0; j<capa-3-(options[2].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
         cout << brackets[1] << "   ";
        cout << options[2];
        for(int j=0; j<capa-3-(options[2].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which_2==4){
        cout << brackets[1] << " > ";
        cout << options[3];
        for(int j=0; j<capa-3-(options[3].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
         cout << brackets[1] << "   ";
        cout << options[3];
        for(int j=0; j<capa-3-(options[3].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    //
    if(which_2==5){
        cout << brackets[1] << " > ";
        cout << options[4];
        for(int j=0; j<capa-3-(options[4].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
    else{
         cout << brackets[1] << "   ";
        cout << options[4];
        for(int j=0; j<capa-3-(options[4].length()); j++){
            cout << " ";
        }
        cout << brackets[1] << "\n";
    }
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
void Removing_Quest(vector<Word> &PEW, int prev){
    Illustrate(PEW);
    int THAT;
    while(THAT<0 || THAT>PEW.size()){
    cout << "Ktora linijke usunac? (Podaj jej numer). Jezeli to pomylka, podaj 0: " << endl;
    cout << " > ";
    cin >> THAT;
    if(THAT==0){return;}
    }
    Remove_the_Word(PEW, files[(2*prev)-2], files[(2*prev)-1], THAT);
    PEW.erase(PEW.begin()+THAT-1); //im scared if this crashes
    THAT=0;
}
int Interface_Choose(vector<Word> &PEW, string options[]){
    int capa=60; //length of the window
    int wide=1; //margin for the top and the bottom
    int poss=4; // possibilities of reacting
    //the same drill with switch()
    short choice_2=0;
    Cases_of_categories(capa, wide, options, choice_2+1);
    decide_moron_2:
    switch(getch()){
        case 72: {choice_2--; if(choice_2<0){choice_2=poss;}
            Cases_of_categories(capa, wide, options, choice_2+1);
        } break;
        case 80: {choice_2++; if(choice_2>poss){choice_2=0;}
            Cases_of_categories(capa, wide, options, choice_2+1);
        } break;
        case 13: {system("cls");
            cout << "Loading..." << endl;
            if(choice_2==0) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; PEW.clear(); Read(PEW, files[0], files[1]); return choice_2+1;} //Read(YE, files[0], files[1]);
            if(choice_2==1) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; PEW.clear(); Read(PEW, files[2], files[3]); return choice_2+1;} //Read(YE, files[2], files[3]);
            if(choice_2==2) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; PEW.clear(); Read(PEW, files[4], files[5]); return choice_2+1;} //Read(YE, files[4], files[5]);
            if(choice_2==3) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; PEW.clear(); Read(PEW, files[6], files[7]); return choice_2+1;} //Read(YE, files[6], files[7]);
            if(choice_2==4) {system("cls"); if(options[choice_2]=="<empty>"){New_Category(choice_2, options);}; PEW.clear(); Read(PEW, files[8], files[9]); return choice_2+1;} //Read(YE, files[8], files[9]);
        } break;
        default: {cout << endl; goto decide_moron_2;}
    }
    goto decide_moron_2;
}
int Interface(vector<Word> &PEW, int prev, string options[]){
    //72 - up_arrow
    //75 - left_arrow
    //80 - down_arrow
    //77 - right_arrow
    //concept here - either revise some new words, add new ones or cout everything, decision managed here
    int capa=60; //length of the window
    int wide=1; //margin for the top and the bottom
    int poss=5; // possibilities of reacting
    int last=prev; //last category used before closing
    menu:
    short choice=0;
    Cases_of_menu(capa, wide, prev, options, choice+1);
    //cout << options.size();
    decide_moron:
    switch(getch()){
        case 72: {choice--; if(choice<0){choice=poss;}
            Cases_of_menu(capa, wide, prev, options, choice+1);
        } break;
        case 80: {choice++; if(choice>poss){choice=0;}
            Cases_of_menu(capa, wide, prev, options, choice+1);
        } break;
        case 13: {system("cls");
            cout << "Loading...";
            if(choice==0) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;} else if(PEW.empty()){cout << "Nie ma dodanych slowek! Dodaj jakies..." << endl; system("pause"); goto menu;} Revise(PEW); goto menu;}
            if(choice==1) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;}; Add(PEW, files[(2*prev)-2], files[(2*prev)-1]); goto menu;}
            if(choice==2) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;} else if(PEW.empty()){cout << "Nie ma dodanych slowek! Nie masz czego usuwac!" << endl; system("pause"); goto menu;} Removing_Quest(PEW, prev); goto menu;}
            if(choice==3) {system("cls"); if(prev==0){cout << "Wybierz najpierw kategorie!" << endl; system("pause"); goto menu;} else if(PEW.empty()){cout << "Nie ma dodanych slowek! Dodaj jakies..." << endl; system("pause"); goto menu;} Illustrate(PEW); getch(); goto menu;}
            if(choice==4) {system("cls"); last=Interface_Choose(PEW, options); prev=last; goto menu;}
            if(choice==5) {system("cls"); return last;};
        } break;
        default: {goto decide_moron;}
    }
    goto decide_moron;
}
int main()
{
    vector<Word> PEW; //abbreviation for Polish and English Words
    vector<string> outputs; //probably ill store here all the outputs for the program in a different file, so reading it wont get corrupted again
    srand(time(NULL));
    string options[5]={"<empty>", "<empty>", "<empty>", "<empty>", "<empty>"};
    int prev=0;
    char ue=432;
    //cout << "a" << endl;
    prev=Read_Opt(options);
    //prev++;
    //cout << "b" << endl;
    if(prev==1) Read(PEW, files[0], files[1]);
    else if(prev==2) Read(PEW, files[2], files[3]);
    else if(prev==3) Read(PEW, files[4], files[5]);
    else if(prev==4) Read(PEW, files[6], files[7]);
    else if(prev==5) Read(PEW, files[8], files[9]);
    //cout << prev << " " << ue;
    //cout << options[prev-1];
    cout << "W razie potrzeby zwieksz rozmiar okna aby program lepiej wygladal XD" << "\n";
    system("pause");
    //else Read(YE, "POL.txt", "ENG.txt");
    //maybe implement here, that the program remembers what were the last revised words, prolly in that options file as well
    prev=Interface(PEW, prev, options);
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
//and work on that encoding shit [hopefully everything in place]
//less than 5 words in Revise() causes problems [NOT ANYMORE]
//work on the Other_Ones and cout of them during Revise() [GOT IT]
//deleting unwanted word, possibly inputed wrong (probably can be done in a matter of a single func) [DONE]
//optimized the code so that there are only single funcs to display each cases of the menus
