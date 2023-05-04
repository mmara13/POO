#include <bits/stdc++.h>
using namespace std;

//EXCEPTII
class DuplicateLibraryException : public exception{ //clasa care creaza exceptie in cazul in care intr-un Library(variabila de tip Media) adaugam de doua ori acelasi playlist/album
    string m_mesaj;
public:
    DuplicateLibraryException(const char* mesaj) : m_mesaj(mesaj) {} //constructor initializare
    //folosesc string din std pt ca nu am implementat toate chestiile si trb c_str() pt convertire string -> mesaj pt afisare la consola
    virtual const char* what() const noexcept override{ //catch exceptie nu throw
        return m_mesaj.c_str();
    }
};

class InvalidSongDurationException : public exception{
    string m_mesaj;
public:
    InvalidSongDurationException(const char* mesaj) : m_mesaj(mesaj) {}
    virtual const char* what() const noexcept override{
        return m_mesaj.c_str();
    }
};

class InvalidPlaylistNameException : public exception {
    string m_mesaj;
public:
    InvalidPlaylistNameException(const char* mesaj) : m_mesaj(mesaj){}
    virtual const char* what() const noexcept override{ 
        return m_mesaj.c_str();
    }
};

class InvalidUserAccountException : public exception{
    string m_mesaj;
public:
    InvalidUserAccountException(const char* mesaj) : m_mesaj(mesaj){}
    virtual const char* what() const noexcept override {
        return m_mesaj.c_str();
    }
};

class InvalidCredentialsException : public exception{
    string m_mesaj;
public:
    InvalidCredentialsException(const char* mesaj) : m_mesaj(mesaj){}
    virtual const char* what() const noexcept override {
        return m_mesaj.c_str();
    }
};

class Artist{
    string nickname; //nume artist
    int age; //varsta artist

public:
    Artist(){ //constructor fara parametri
        nickname="Unknown";
        age=0;
    }

    void setArtistNickname(string n){ //setter pt nume
        nickname=n;
    }

    void setArtistAge(int v){ //setter varsta
        age=v;
    }

    string getArtistNickname() const { //getter nume
        return nickname;
    }

    int getArtistAge() const{ //getter varsta
        return age;
    }

};

class Media{ //clasa abstracta Media
    string title;
public:
    virtual ~Media() {}
    virtual string getSongTitle() const {
        return title;
    }
    virtual void displayDetails() const = 0;
};

class Song : public Media{ //clasa melodii
    string title;
    Artist artist;
    int year;
    int time;

public:
    //setters
    void setSongTitle(string t){ //setter titlu melodie
        title=t;
    }

    void setSongArtist(Artist a){ //setter artist melodie
        artist=a;
    }

    void setSongYear(int y){ //setter an melodie
        year=y;
    }

    void setSongTime(int t){ //setter durata melodie
        if (t<=0) {
            throw InvalidSongDurationException("Durata melodiei trebuie sa fie pozitiva!");}
        time=t;
    }

    //getters
    virtual string getSongTitle() const override{ //getter titlu melodie suprascris din clasa abstracta Media
        return title;
    }

    Artist getSongArtist() const{ //getter artist melodie
        return artist;
    }

    int getSongYear() const{ //getter an melodie
        return year;
    }

    int getSongTime() const{
        return time;
    }

    void displayDetails() const override{ //afisare melodie cu toate datele ei
        cout<<"Song: "<<title<<" by "<<artist.getArtistNickname()<<" from "<<year<<" with duration "<<time<<" seconds"<<"\n";}
 
};

class Searchable{
//interfata ptc nu avem date membre
public:
    virtual ~Searchable() {}
    virtual vector<Song> searchByTitle(const string title) = 0;
    //virtual vector<Song> searchByArtist(const Artist artist) = 0; //pt album mut ideea in media si o sterg pe aia de acolo ca era facuta doar ca sa indeplineasca cerinta
    virtual vector<Song> searchByArtist(const string artist) = 0; //pt playlist (cauta doar stringul cu numele)
    virtual vector<Song> searchByYear(const int year) = 0;
};

class Album : public Searchable, public Media{
    string title; //titlu album
    vector<Song> songs; //vector cantece din album
    int numSongs; //numar cantece in album
    Artist artist; //artistul albumului
    int year; //anul lansarii albumului
    int price; //pretul albumului
    int discount=0; //folosim discount initializat cu 0, pentru ca in
    //momentul in care se aplica discountul respectiv, variabila asociata sa devina 1 si sa nu se mai poata 
    //aplica iarasi acest discount

public:

    Album(string t, Artist a, int nr, vector<Song> s, int y){ //Constructor initializare 
        title=t;
        artist=a;
        numSongs=nr;
        songs=s;
        year=y;
        
    }

    int Discount() {  // daca albumul are mai mult de 10 melodii se aplica o reducere de 3 unitati pe melodie
        int price=0;
        if (discount==0){
            if (numSongs<10){
                price=10*numSongs;
            }
            else price=7*numSongs;  
            if(year<=2015){
                price/=2;
            }
            discount=1; //previne aplicarea discountului de 2 ori
        }
        return price;
    }

    int calculateDuration() const{
        int d=0;
        for (const auto& song: songs)
            d+=song.getSongTime();
        return d/60;
    }

    int getnumSongs() const{ //getter si pt nr de cantece !!VEZI DACA CHIAR IL FOLOSESTI LA CEVA
        return numSongs;
    }

    string getAlbumTitle() const{ //getter titlu album
        return title;
    }

    Artist getAlbumArtist() const{ //getter nume artist album
        return artist;
    }

    vector<Song> getAlbumSongs() const{ //getter vector de cantece din album
        return songs;
    }

    int getAlbumYear() const{ //getter anul lansarii albumului
        return year;
    }

    //metoda afisare pe care am inlocuit-o cu supraincarcarea operatorului <<
    /*void print() const {
        cout << title <<" by "<<artist.getArtistNickname() << " (" << year << ")" << endl;
    }*/

    friend ostream & operator << (ostream &out, const Album &a); //antet functie supraincarcare

    vector<Song> searchByTitle(const string title) override{ //suprascriem functia virtuala din clasa Searchable
        vector<Song> result;
        for (const auto& song: songs){
            if (song.getSongTitle()==title){
                result.push_back(song);
            }
        }
        return result;
    }

    vector<Song> searchByArtist(const string artist) override{ //suprascriem functia virtuala din clasa Searchable
        vector<Song>* result = new vector<Song>; //situatia in care vectorul result va fi sters la iesirea din functie cu destructorul din cls de baza
        for (const auto& song: songs){
            if (song.getSongArtist().getArtistNickname()==artist){
                result->push_back(song);
            }
        }
        return *result;
    }

    vector<Song> searchByYear(const int year) override{ //suprascriem functia virtuala din clasa Searchable
        vector<Song> result;
        for (const auto& song: songs){
            if (song.getSongYear()==year){
                result.push_back(song);
            }
        }
        return result;
    }

    void displayDetails() const override{ //afisare album cu toate datele lui
        cout<<"Album: "<<title<<" by "<<artist.getArtistNickname()<<" from "<<year<<" with duration "<<calculateDuration()<<" minutes"<<endl;
        for (const auto& song: songs)
            song.displayDetails();
        cout<<"\n";
    }

};

ostream & operator << (ostream &out, const Album &a){ //functie pentru supraincarcarea operatorului << pt clasa album
    out<< "Album title: "<<a.title<<" by "<<a.artist.getArtistNickname()<<" ("<<a.year<<")"<<"\n"; //print titlu artist si an album
    out<< "Songs:"<<"\n";
    int i=1;
    for (const auto& song: a.songs){ //print vector de cantece
        out <<i<< ") \""<<song.getSongTitle()<<"\" by "<<song.getSongArtist().getArtistNickname()<<"."<<"\n"; //print titlu cantec si nume artist
        i++;
    }
    //out<<"Price: "<<a.getAlbumPrice()<<"\n";
    return out;
}

static void printAlbumDetails(Media* media){ 
    Album* album = dynamic_cast<Album*>(media); //downcast la clasa Album
    if(album) //verificam daca este album sa ii printam detaliile
        album->displayDetails();
    else cout<<"Nu este album. (alt tip de media)"<<"\n"; //altfel printam msj de atentionare fara continut
}

class GenreAlbum : public Album{ //clasa album de gen, mostenire publica
    string genre; //genul albumului 

public:
    GenreAlbum(string t, Artist a, int nr, vector<Song> s, int y, string g) : Album(t, a, nr, s, y), genre(g){} //constructor initializare pt clasa de baza si genre

    void setGenre(string g){ //setter gen
        genre=g;
    }

    string getGenre() const{//getter gen
        return genre;
    }

    friend ostream & operator << (ostream &out, const GenreAlbum &ga); //antet functie supraincarcare
};

ostream & operator << (ostream &out, const GenreAlbum &ga){ //suprascriere << pentru GenreAlbum
    out << static_cast<const Album&>(ga); //apelez suprascrierea << pentru Album
    out << "Genre: " << ga.getGenre() << endl; //adaug genre 
    return out;
}


class Playlist : public Searchable, public Media{ //clasa playlist
    string title; //titlu playlist
    vector<Song> songs; //vector de melodii
    int numSongs; //nr cantece

public:
    Playlist(){ //constructor fara parametri, initializeaza playlist gol
        title="unknown";
        numSongs=0;
    }

    Playlist(int nr, vector<Song> s){ //constructor cu parametri
        numSongs=nr;
        songs=s;
    }

    void setPlaylistName(string t){
        if (t.size() > 50){
            throw InvalidPlaylistNameException("Numele playlist-ului este prea lung!");
        }
        title=t;
    }

    string getPlaylistTitle() const{ //getter nume playlist
        return title;
    }

    vector<Song> getPlaylistSongs() const{ //getter melodii playlist
        return songs;
    }
    int getPlaylistNrSongs() const{ //getter nr cantece din playlist
        return numSongs;
    }

    friend ostream & operator << (ostream &out, const Playlist &p);

    //facem acelasi lucru cu functiile virtuale ca la clasa Album
    vector<Song> searchByTitle(const string title)  override{
        vector<Song>* result = new vector<Song>;
        for (const auto& song: songs){
            if (song.getSongTitle()==title){
                result->push_back(song);
            }
        }
        return *result;
    }

    vector<Song> searchByArtist(const string artist) override{
        vector<Song>* result = new vector<Song>;
        for (const auto& song: songs){
            if (song.getSongArtist().getArtistNickname()==artist){
                result->push_back(song);
            }
        }
        return *result;
    }

    vector<Song> searchByYear(const int year) override{
        vector<Song>* result = new vector<Song>;
        for (const auto& song: songs){
            if (song.getSongYear()==year){
                result->push_back(song);
            }
        }
        return *result;
    }

    void displayDetails() const override{
        cout<<"Playlist: "<<title<<"\n";
        for(const auto& song:songs)
            //cout<<song.getSongTitle()<<" by "<<song.getSongArtist().getArtistNickname()<<"\n";
            song.displayDetails();
        cout<<"\n";
    }
};

ostream & operator << (ostream &out, const Playlist &p){ //functie pentru supraincarcarea operatorului << pt clasa playlist
    out<< "Playlist title: "<<p.title<<"\n"; //print titlu playlist
    out<< "Songs in this playlist:"<<"\n";
    int i=1;
    for (const auto& song: p.songs){ //print vector de cantece
        out <<i<< ") \""<<song.getSongTitle()<<"\" by "<<song.getSongArtist().getArtistNickname()<<"."<<"\n"; //print titlu melodii si artist
        i++;
    }
    return out;
}

// class User : protected Playlist {
//     string username; //nume utilizator
//     string password; //parola

//     public: 
//         User(string u, string p, string t, int nr, vector<Song> s) : Playlist(t, nr, s), username(u), password(p){} //constructor initializare

//         string getUsername() const{ //getter nume utilizator
//             return username;
//         }

//         string getPassword() const{ //getter parola
//             return password;
//         }

//         friend ostream & operator << (ostream &out, const User &u);
// };

// ostream & operator<<(ostream& out, const User& u){
//     out<< "Username: "<<u.username<<"\n";
//     out<< "Password: "<<u.password<<"\n";
//     out<<"\n";
//     out<<"This user has this playlist in their account:\n";
//     out<<static_cast<const Playlist&>(u); //ca sa afisam playlistul cum am suprascris la clasa lui
//     out<<"\n";
//     return out;
// }

class UserAccount{ //am adaugat clasa UserAccount pentru a putea avea si clasa User mostenita din ea
protected:
    string username; //nume utilizator
    string password; //parola

    void changePassword(string thispassword, string newpassword){
        if (thispassword==password) //daca parola introdusa este egala cu parola curenta ca sa se apropie de realitate
            password=newpassword;
    }
public:
    UserAccount():username(), password(){} //constructor fara parametri
    UserAccount(string& u, string& p) : username(u), password(p){} //constructor initializare

    string getUsername() const{ //getter nume utilizator
        return username;
    }

    string getPassword() const{ //getter parola
        return password;
    }
    
};

class User : protected UserAccount{ //mostenire protected
    string name;
    //UserAccount account;
    vector<Media*> Library; //vector de pointeri la Media
    static int nrOfUsers; //numarul de utilizatori
    static const int maxNrOfUsers = 10; //numarul maxim de utilizatori

public:
    User(string n, string u, string p) : name(n), UserAccount(u,p){++nrOfUsers;} //constructor initializare

    static int getNumberOfUsers(){ //getter numar utilizatori
        return nrOfUsers;
    }

    static bool isMaxUserReached(){
        return nrOfUsers >= maxNrOfUsers;
    }

    static int getUsernameLength(User u){
        return u.username.length();
    }

    void changeUserPassword(string thispassword, string newpassword){
        changePassword(thispassword, newpassword); //apelez functia din clasa de baza
    }

    friend ostream & operator << (ostream &out, const User &u);

    void addToLibrary(Media* media){ //adaugam in biblioteca un pointer la media
        for (const auto& m: Library){
            if (m == media)
                throw DuplicateLibraryException("Acest element este deja in biblioteca!");
        }
        //altfel adaugam media in biblioteca
        Library.push_back(media); //adaugam in vectorul de pointeri la media un album/playlist deci din nou situatie de upcasting
        cout<<"Adaugat"<<media->getSongTitle() <<" cu succes in biblioteca!\n";
    }

    void displayLibrary() const{ //afisam biblioteca
        cout<<"\nBiblioteca utilizatorului "<<name<<":\n";
        int index=1;
        for (const auto& media: Library){
            cout<<index<<") ";
            media->displayDetails();
            index++;
        }
    }
    
    void authenticateUser(string u, string pss){
        if(u.empty() || pss.empty()){
            throw InvalidCredentialsException("Username sau parola nu pot fi goale!");
        }
        if(u!=username || pss!=password){
            throw InvalidUserAccountException("Username sau parola incorecte!");
        }
        //altfel afisam mesaj ca autentificarea s-a efectuat cu succes
        cout<<"Autentificat cu succes!"<<"\n";
    }

};

ostream & operator<<(ostream &out, const User &u){
    out << "Numele utilizatorului: " << u.name << "\n";
    out << "Username: " << u.username << "\n";
    //fara parola ca sa aiba sens programul
    return out;
}

class Mixtape : public Album, public Playlist{ //mostenire multipla
    string title; //titlu mixtape
    public:
        Mixtape(string t,Artist a, int nrAlbum, vector<Song> albumsongs, int y, int nrPlaylist, vector<Song> playlistsongs) : Album(t,a, nrAlbum, albumsongs,y ), Playlist(nrPlaylist, playlistsongs){} //constructor initializare

        string getMixtapeName() const{
            return title;
        }
        
        friend ostream & operator << (ostream &out, const Mixtape &m);

        void displayDetails() const override{
        cout<<"Mixtape: "<<title<<"\n";
        
        vector<Song> songs; //creez vector in care sa pun mel din album si din playlist
        vector<Song> songsAlbum=getAlbumSongs();
        vector<Song> songsPlaylist=getPlaylistSongs();
        songs.insert(songs.end(), songsAlbum.begin(), songsAlbum.end()); //adaug cantecele din album
        songs.insert(songs.end(), songsPlaylist.begin(), songsPlaylist.end()); //adaug cantecele din playlist
        for(const auto& song:songs)
            //cout<<song.getSongTitle()<<" by "<<song.getSongArtist().getArtistNickname()<<"\n";
            song.displayDetails();
        cout<<"\n";
    }
};

//suprascriere operator << pentru Mixtape
// ostream & operator << (ostream &out, const Mixtape &m){
//     out << "Mixtape: "<<m.getMixtapeName()<<"\n";
//     out << static_cast<const Album&>(m); //apelez suprascrierea << pentru Album
//     out << static_cast<const Playlist&>(m); //apelez suprascrierea << pentru Playlist
//     return out;
// } //nu merge ptc afiseaza titlul de doua ori, o data pt album o data pt playlist

ostream & operator << (ostream &out, const Mixtape &m){
    out << "Mixtape: "<<m.getMixtapeName()<<"\n";
    //afisam melodiile din Albumul din Mixtape
    int i=1;
    for(const auto& song: m.getAlbumSongs()){
        out << "Song " <<i<<": " << song.getSongTitle() << " by " << song.getSongArtist().getArtistNickname() << "\n";
        i++;
    }
    //afisam acum melodiile din Playlistul din Mixtape
    for(const auto& song: m.getPlaylistSongs()){
        out << "Song " <<i<<": " << song.getSongTitle() << " by " << song.getSongArtist().getArtistNickname() << "\n";
        i++;
    }
    return out;
}


int User::nrOfUsers = 0; //initializare variabila statica
int main(){

    Artist theweeknd; //creez artist theweeknd
    theweeknd.setArtistAge(33); //ii setez varsta in functie de anul nasterii ca sa se updateze mereu
    theweeknd.setArtistNickname("The Weeknd"); //ii setez numele

    Song tw1; //adaug primul cantec
    Song tw2, tw3, tw4, tw5, tw6, tw7; //adaug restul cantecelor

try{
    tw1.setSongArtist(theweeknd); //ii asociez artistul definit mai sus
    tw1.setSongTitle("Starboy"); //dau nume melodiei
    tw1.setSongYear(2016); //asociez an melodiei
    tw1.setSongTime(200);

    tw2.setSongArtist(theweeknd); tw2.setSongTitle("False Alarm"); tw2.setSongYear(2016); tw2.setSongTime(140);

    tw3.setSongArtist(theweeknd); tw3.setSongTitle("Reminder"); tw3.setSongYear(2017); tw3.setSongTime(134);

    tw4.setSongArtist(theweeknd); tw4.setSongTitle("Love To Lay"); tw4.setSongYear(2016); tw4.setSongTime(123);

    tw5.setSongArtist(theweeknd); tw5.setSongTitle("A Lonely Night"); tw5.setSongYear(2016); tw5.setSongTime(90);

    tw6.setSongArtist(theweeknd); tw6.setSongTitle("Die For You"); tw6.setSongYear(2016); tw6.setSongTime(113);

    tw7.setSongArtist(theweeknd); tw7.setSongTitle("I Feel It Coming"); tw7.setSongYear(2016); tw7.setSongTime(100);
} catch (const InvalidSongDurationException& e) {
    cout <<"Eroare: "<< e.what() << '\n';}
    vector<Song> the_weeknd_songs1={tw1,tw2,tw3,tw4,tw5,tw6,tw7}; //fac vector din cantecele definite mai sus

    Album album_the_weeknd("Starboy", theweeknd, the_weeknd_songs1.size(), the_weeknd_songs1, 2016); //creez album cu acest artist, vectorul si adaug celelalte date
    //album_the_weeknd.setDiscount1(), album_the_weeknd.setDiscount2(); //aplic discounts, automat daca nu sunt valabile ele nu se aplica
    cout<<album_the_weeknd<<'\n'; //afisez album
    cout<<"Durata albumului "<<album_the_weeknd.getAlbumTitle()<<" este de aproximativ: "<<album_the_weeknd.calculateDuration()<<" minute."<<'\n';
    cout<<"Pretul albumului "<<album_the_weeknd.getAlbumTitle()<<" este de "<<album_the_weeknd.Discount()<<" RON.\n"<<"\n";
    Artist tzanca_uraganu;
    tzanca_uraganu.setArtistAge(32);
    tzanca_uraganu.setArtistNickname("Tzanca Uraganu");

    Song tz1; Song tz2; Song tz3; Song tz4; Song tz5; Song tz6; Song tz7; Song tz8; Song tz9; Song tz10; Song tz11;

try{
    tz1.setSongArtist(tzanca_uraganu); tz1.setSongTitle("Trotinete"); tz1.setSongYear(2023); tz1.setSongTime(120);

    tz2.setSongArtist(tzanca_uraganu); tz2.setSongTitle("Havana"); tz2.setSongYear(2022); tz2.setSongTime(100);

    tz3.setSongArtist(tzanca_uraganu); tz3.setSongTitle("Banii"); tz3.setSongYear(2021); tz3.setSongTime(90);

    tz4.setSongArtist(tzanca_uraganu); tz4.setSongTitle("Alo baza baza"); tz4.setSongYear(2023); tz4.setSongTime(110);

    tz5.setSongArtist(tzanca_uraganu); tz5.setSongTitle("Te-am vazut fara inel"); tz5.setSongYear(2022); tz5.setSongTime(130);

    tz6.setSongArtist(tzanca_uraganu); tz6.setSongTitle("Buzele Cu Rosu Inchis"); tz6.setSongYear(2021); tz6.setSongTime(140);

    tz7.setSongArtist(tzanca_uraganu); tz7.setSongTitle("Hai ca m-ai sedus"); tz7.setSongYear(2022); tz7.setSongTime(150);

    tz8.setSongArtist(tzanca_uraganu); tz8.setSongTitle("Cu Lumina Stinsa"); tz8.setSongYear(2022); tz8.setSongTime(160);

    tz9.setSongArtist(tzanca_uraganu); tz9.setSongTitle("S-au Unit Legendele"); tz9.setSongYear(2021); tz9.setSongTime(170);

    tz10.setSongArtist(tzanca_uraganu); tz10.setSongTitle("Noapte Golanii"); tz10.setSongYear(2020); tz10.setSongTime(180);

    tz11.setSongArtist(tzanca_uraganu); tz11.setSongTitle("Fa spagatu"); tz11.setSongYear(2020); tz11.setSongTime(190);
} catch (const InvalidSongDurationException& e) {
    cout<<"Eroare: "<<e.what()<<'\n';
}
    vector<Song> tzanca_uraganu_songs={tz1,tz2,tz3,tz4,tz5,tz6,tz7,tz8,tz9,tz10,tz11};

    Album album_tzanca_uraganu("Manele Mentolate", tzanca_uraganu, tzanca_uraganu_songs.size(), tzanca_uraganu_songs, 2023);
    cout<<album_tzanca_uraganu<<'\n';

    Artist andra;
    andra.setArtistAge(36);
    andra.setArtistNickname("Andra"); 

    Song a1; Song a2; Song a3; Song a4; Song a5; Song a6; Song a7; Song a8; Song a9;
try{
    a1.setSongArtist(andra); a1.setSongTitle("Eu as da"); a1.setSongYear(2010); a1.setSongTime(120);

    a2.setSongArtist(andra); a2.setSongTitle("Nu regret - Cool Version"); a2.setSongYear(2010);  a2.setSongTime(100);

    a3.setSongArtist(andra); a3.setSongTitle("Vreau sărutarea ta"); a3.setSongYear(2010); a3.setSongTime(90);

    a4.setSongArtist(andra); a4.setSongTitle("Doar o clipă"); a4.setSongYear(2010);  a4.setSongTime(110);

    a5.setSongArtist(andra); a5.setSongTitle("Ramai cu mine"); a5.setSongYear(2010); a5.setSongTime(130);

    a6.setSongArtist(andra); a6.setSongTitle("Sarutul Noptilor De Rai"); a6.setSongYear(2010); a6.setSongTime(140);

    a7.setSongArtist(andra); a7.setSongTitle("Dragostea Ramane"); a7.setSongYear(2010); a7.setSongTime(150);

    a8.setSongArtist(andra); a8.setSongTitle("Colț de suflet"); a8.setSongYear(2010); a8.setSongTime(160);

    a9.setSongArtist(andra); a9.setSongTitle("Femeia"); a9.setSongYear(2010); a9.setSongTime(0);
} catch (const InvalidSongDurationException& e) {
    cout<< "Eroare: "<<e.what()<<'\n';
}

    vector<Song> andra_songs={a1,a2,a3,a4,a5,a6,a7,a8,a9};
    //Album album_andra("Iubește-mă azi, iubește-mă mâine", andra, andra_songs.size(), andra_songs, 2010);
    GenreAlbum album_andra("Iubește-mă azi, iubește-mă mâine", andra, andra_songs.size(), andra_songs, 2010, "Pop");
    cout<<album_andra<<'\n';
    //cout<<album_andra.getGenre()<<"Genul aici\n"; l am inclus in suprascriere

//     Song tw11; Song tw12; Song tw13; Song tw14; Song tw15; Song tw16; Song tw17; Song tw18;
// try{
//     tw11.setSongArtist(theweeknd); tw11.setSongTitle("Alone Again"); tw11.setSongYear(2020); tw11.setSongTime(250);

//     tw12.setSongArtist(theweeknd); tw12.setSongTitle("Too Late"); tw12.setSongYear(2020); tw12.setSongTime(239);

//     tw13.setSongArtist(theweeknd); tw13.setSongTitle("Hardest To Love"); tw13.setSongYear(2020); tw13.setSongTime(211);
    
//     tw14.setSongArtist(theweeknd); tw14.setSongTitle("Scared To Live"); tw14.setSongYear(2020); tw14.setSongTime(191);

//     tw15.setSongArtist(theweeknd); tw15.setSongTitle("Snowchild"); tw15.setSongYear(2020); tw15.setSongTime(247);

//     tw16.setSongArtist(theweeknd); tw16.setSongTitle("Escape From LA"); tw16.setSongYear(2020); tw16.setSongTime(355);

//     tw17.setSongArtist(theweeknd); tw17.setSongTitle("Heartless"); tw17.setSongYear(2020); tw17.setSongTime(198);

//     tw18.setSongArtist(theweeknd); tw18.setSongTitle("Faith"); tw18.setSongYear(2020); tw18.setSongTime(0);
// } catch (const InvalidSongDurationException& e){
//     cout<< "Eroare: "<<e.what()<<'\n';
// }
//     vector<Song> the_weeknd_songs2={tw11,tw12,tw13,tw14,tw15,tw16,tw17,tw18};
//     Album album_the_weeknd2("After Hours", theweeknd, the_weeknd_songs2.size(), the_weeknd_songs2, 2020);

    vector<Song> others={a1,tz1,tw1,a2,tz2,tz3,tz4,tz5,tz6,tw7,tz8};
    Playlist muzica(others.size(), others);
    muzica.setPlaylistName("Muzica");
    cout<<muzica<<'\n';

    //User myAccount("Mara","parola123","Muzica", others.size(), others );
    //cout<<myAccount<<'\n';

    User myUser("Mara","mara13", "parola123");
    cout<<myUser<<'\n';
    myUser.changeUserPassword("parola123","parola12345"); //schimb parola

    Mixtape mixtape1("The Weeknd Mixtape", theweeknd, the_weeknd_songs1.size(), the_weeknd_songs1, 2020, others.size(), others);
    cout<<mixtape1<<"\n";

    cout<<"Cautare in playlist-ul 'Muzica' dupa numele artistului"<<'\n';
    vector<Song> TheWeekndSongs = muzica.searchByArtist("The Weeknd");
    if(TheWeekndSongs.empty())
        cout<<"Nu exista melodii in playlist-ul 'Muzica' cu artistul 'The Weeknd'"<<'\n';
    else{
        cout<<"Melodiile cu artistul 'The Weeknd' din playlist-ul 'Muzica' sunt: "<<'\n';
        for(int i=0; i<TheWeekndSongs.size(); i++)
            cout<<TheWeekndSongs[i].getSongTitle()<<'\n';
        cout<<'\n';
    }

    vector<Song> songs2015 = muzica.searchByYear(2015);
    if(songs2015.empty())
        cout<<"Nu exista melodii in playlist-ul 'Muzica' din anul 2015"<<'\n';
    else{
        cout<<"Melodiile din anul 2015 din playlist-ul 'Muzica' sunt: "<<'\n';
        for(int i=0; i<songs2015.size(); i++)
            cout<<songs2015[i].getSongTitle()<<'\n';
        cout<<'\n';
    }

    //polimorfism la executie se realizeaza atunci cand am suprascris functia virtuale din clasa
    //Media in clasele Song, Album si Playlist (functia displayDetails())
    vector<Media*> media; //creez vector de pointeri la Media
    media.push_back(&tw1);
    media.push_back(&album_the_weeknd);
    media.push_back(&muzica); //exemplu de upcasting de la song, album, respectiv playlist la obiect de tip media

    for(int i=0; i<media.size(); i++)
        media[i]->displayDetails(); //apelez functia displayDetails() pentru fiecare element din vectorul de pointeri la Media

    try{
        myUser.addToLibrary(static_cast<Media*>(&album_the_weeknd)); //upcasting iar ca vectorul retine pointeri la media si in el punem album/playlist
        myUser.addToLibrary(static_cast<Media*>(&album_andra)); //la fel ca sus, pot elimina static_cast dar l-am pus pt upcasting
        myUser.addToLibrary(static_cast<Media*>(&album_the_weeknd)); //aici ar trb sa arunce exceptie
    }
    catch (const DuplicateLibraryException& e){
        cout<<"Eroare: "<<e.what()<<'\n';
    }
    myUser.displayLibrary();

    //downcasting - verificam daca elementele din media sunt albume
    for (const auto& m : media)
        printAlbumDetails(m);

    //creare playlist cu o singura melodie pentru a testa exceptia InvalidPlaylistNameEception
    vector<Song> mz={a1};
    Playlist plst(1,mz);
    try{ plst.setPlaylistName("My awesome playlist with a really long name that exceeds the maximum length allowed.");}
    catch(const InvalidPlaylistNameException& e){
        cout<<"Eroare: "<<e.what()<<"\n";
    }
    cout<<plst;

    try{
        myUser.authenticateUser("mara13", "mara");
    }
    catch (const InvalidUserAccountException& e){
        cout<<"Eroare: "<<e.what()<<'\n';
        try{throw InvalidCredentialsException("Autentificare nereusita!");}
        catch (const InvalidCredentialsException& ee){
        cout<<"Eroare: "<<ee.what()<<'\n';}
    }
 
}
