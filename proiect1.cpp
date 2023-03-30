#include <bits/stdc++.h>
using namespace std;

class String{
    int lg;
    char* sir;
public:
    String(const char* str=""){ //constructor cu param pointer char
        lg=strlen(str);
        sir= new char[lg+1];
        strcpy(sir,str);
    }

    String(const String& cv){ //constr de copiere
        lg=cv.lg;
        sir= new char[lg+1];
        strcpy(sir,cv.sir);
    }

    ~String(){ //destructor
        delete[] sir;
    }

    String& operator=(const String& cv){ //suprascriere egal
        if (this!=&cv){
            delete[] sir;
            lg=cv.lg;
            sir = new char[lg+1];
            strcpy(sir, cv.sir);
        }
        return *this;
    }


    friend ostream& operator<<(ostream& outsys, const String& str); //supraincarcam operatorul <<
    
};

ostream& operator<<(ostream& outsys, const String& str){ //definirea functiei ca sa nu fie inline
        outsys<<str.sir; 
        return outsys;
}

class Artist{
    String nickname; //nume artist
    int age; //varsta artist

public:
    Artist(){ //constructor fara parametri
        nickname="Unknown";
        age=0;
    }

    void setArtistNickname(String n){ //setter pt nume
        nickname=n;
    }

    void setArtistAge(int v){ //setter varsta
        age=v;
    }

    String getArtistNickname() const { //getter nume
        return nickname;
    }

    int getArtistAge() const{ //getter varsta
        return age;
    }

};

class Song{ //clasa melodii
    String title;
    Artist artist;
    int year;
    int time;

public:
    //setters
    void setSongTitle(String t){ //setter titlu melodie
        title=t;
    }

    void setSongArtist(Artist a){ //setter artist melodie
        artist=a;
    }

    void setSongYear(int y){ //setter an melodie
        year=y;
    }

    void setSongTime(int t){ //setter durata melodie
        time=t;
    }

    //getters
    String getSongTitle() const{ //getter titlu melodie
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
};

class Album{
    String title; //titlu album
    vector<Song> songs; //vector cantece din album
    int numSongs; //numar cantece in album
    Artist artist; //artistul albumului
    int year; //anul lansarii albumului
    int price; //pretul albumului
    int discount=0; //folosim discount initializat cu 0, pentru ca in
    //momentul in care se aplica discountul respectiv, variabila asociata sa devina 1 si sa nu se mai poata 
    //aplica iarasi acest discount

public:

    Album(String t, Artist a, int nr, vector<Song> s, int y){ //Constructor initializare 
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
        return d;
    }

    String getAlbumTitle() const{ //getter titlu album
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

class Playlist{ //clasa playlist
    String title; //titlu playlist
    vector<Song> songs; //vector de melodii
    int numSongs; //nr cantece

public:
    Playlist(){ //constructor fara parametri, initializeaza playlist gol
        title="unknown";
        numSongs=0;
    }

    Playlist(String t, int nr, vector<Song> s){ //constructor cu parametri
        title=t;
        numSongs=nr;
        songs=s;
    }

    String getPlaylistTitle() const{ //getter nume playlist
        return title;
    }

    vector<Song> getPlaylistSongs() const{ //getter melodii playlist
        return songs;
    }
    int getPlaylistNrSongs() const{ //getter nr cantece din playlist
        return numSongs;
    }

    friend ostream & operator << (ostream &out, const Playlist &p);
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

int main(){

    Artist theweeknd; //creez artist theweeknd
    theweeknd.setArtistAge(33); //ii setez varsta in functie de anul nasterii ca sa se updateze mereu
    theweeknd.setArtistNickname("The Weeknd"); //ii setez numele

    Song tw1; //adaug primul cantec
    tw1.setSongArtist(theweeknd); //ii asociez artistul definit mai sus
    tw1.setSongTitle("Starboy"); //dau nume melodiei
    tw1.setSongYear(2016); //asociez an melodiei
    tw1.setSongTime(200);

    Song tw2;
    tw2.setSongArtist(theweeknd);
    tw2.setSongTitle("False Alarm");
    tw2.setSongYear(2016);
    tw2.setSongTime(140);

    Song tw3;
    tw3.setSongArtist(theweeknd);
    tw3.setSongTitle("Reminder");
    tw3.setSongYear(2017);
    tw3.setSongTime(134);

    Song tw4;
    tw4.setSongArtist(theweeknd);
    tw4.setSongTitle("Love To Lay");
    tw4.setSongYear(2016);
    tw4.setSongTime(123);

    Song tw5;
    tw5.setSongArtist(theweeknd);
    tw5.setSongTitle("A Lonely Night");
    tw5.setSongYear(2016);
    tw5.setSongTime(90);

    Song tw6;
    tw6.setSongArtist(theweeknd);
    tw6.setSongTitle("Die For You");
    tw6.setSongYear(2016);
    tw6.setSongTime(113);

    Song tw7;
    tw7.setSongArtist(theweeknd);
    tw7.setSongTitle("I Feel It Coming");
    tw7.setSongYear(2016);
    tw7.setSongTime(100);

    vector<Song> the_weeknd_songs={tw1,tw2,tw3,tw4,tw5,tw6,tw7}; //fac vector din cantecele definite mai sus

    Album album_the_weeknd("Starboy", theweeknd, the_weeknd_songs.size(), the_weeknd_songs, 2016); //creez album cu acest artist, vectorul si adaug celelalte date
    //album_the_weeknd.setDiscount1(), album_the_weeknd.setDiscount2(); //aplic discounts, automat daca nu sunt valabile ele nu se aplica
    cout<<album_the_weeknd<<'\n'; //afisez album
    cout<<"Durata albumului "<<album_the_weeknd.getAlbumTitle()<<" este: "<<album_the_weeknd.calculateDuration()<<" secunde."<<'\n';
    cout<<"Pretul albumului "<<album_the_weeknd.getAlbumTitle()<<" este de "<<album_the_weeknd.Discount()<<" RON.\n"<<"\n";
    Artist tzanca_uraganu;
    tzanca_uraganu.setArtistAge(32);
    tzanca_uraganu.setArtistNickname("Tzanca Uraganu");

    Song tz1;
    tz1.setSongArtist(tzanca_uraganu);
    tz1.setSongTitle("Trotinete");
    tz1.setSongYear(2023);

    Song tz2;
    tz2.setSongArtist(tzanca_uraganu);
    tz2.setSongTitle("Havana");
    tz2.setSongYear(2022);

    Song tz3;
    tz3.setSongArtist(tzanca_uraganu);
    tz3.setSongTitle("Banii");
    tz3.setSongYear(2021);

    Song tz4;
    tz4.setSongArtist(tzanca_uraganu);
    tz4.setSongTitle("Alo baza baza");
    tz4.setSongYear(2023);

    Song tz5;
    tz5.setSongArtist(tzanca_uraganu);
    tz5.setSongTitle("Te-am vazut fara inel");
    tz5.setSongYear(2022);

    Song tz6;
    tz6.setSongArtist(tzanca_uraganu);
    tz6.setSongTitle("Buzele Cu Rosu Inchis");
    tz6.setSongYear(2021);

    Song tz7;
    tz7.setSongArtist(tzanca_uraganu);
    tz7.setSongTitle("Hai ca m-ai sedus");
    tz7.setSongYear(2022);

    Song tz8;
    tz8.setSongArtist(tzanca_uraganu);
    tz8.setSongTitle("Cu Lumina Stinsa");
    tz8.setSongYear(2022);

    Song tz9;
    tz9.setSongArtist(tzanca_uraganu);
    tz9.setSongTitle("S-au Unit Legendele");
    tz9.setSongYear(2021);

    Song tz10;
    tz10.setSongArtist(tzanca_uraganu);
    tz10.setSongTitle("Noapte Golanii");
    tz10.setSongYear(2020);

    Song tz11;
    tz11.setSongArtist(tzanca_uraganu);
    tz11.setSongTitle("Fa spagatu");
    tz11.setSongYear(2020);

    vector<Song> tzanca_uraganu_songs={tz1,tz2,tz3,tz4,tz5,tz6,tz7,tz8,tz9,tz10,tz11};

    Album album_tzanca_uraganu("Manele Mentolate", tzanca_uraganu, tzanca_uraganu_songs.size(), tzanca_uraganu_songs, 2023);
    cout<<album_tzanca_uraganu<<'\n';


    Artist andra;
    andra.setArtistAge(36);
    andra.setArtistNickname("Andra");

    Song a1;
    a1.setSongArtist(andra);
    a1.setSongTitle("Eu as da");
    a1.setSongYear(2010);

    Song a2;
    a2.setSongArtist(andra);
    a2.setSongTitle("Nu regret - Cool Version");
    a2.setSongYear(2010);

    Song a3;
    a3.setSongArtist(andra);
    a3.setSongTitle("Vreau sărutarea ta");
    a3.setSongYear(2010);

    Song a4;
    a4.setSongArtist(andra);
    a4.setSongTitle("Doar o clipă");
    a4.setSongYear(2010);

    Song a5;
    a5.setSongArtist(andra);
    a5.setSongTitle("Ramai cu mine");
    a5.setSongYear(2010);

    Song a6;
    a6.setSongArtist(andra);
    a6.setSongTitle("Sarutul Noptilor De Rai");
    a6.setSongYear(2010);

    Song a7;
    a7.setSongArtist(andra);
    a7.setSongTitle("Dragostea Ramane");
    a7.setSongYear(2010);

    Song a8;
    a8.setSongArtist(andra);
    a8.setSongTitle("Colț de suflet");
    a8.setSongYear(2010);

    Song a9;
    a9.setSongArtist(andra);
    a9.setSongTitle("Femeia");
    a9.setSongYear(2010);
    /*a9.setSongArtist(andra);
    char titlumel[30]; 
    cin>>titlumel; //citire nume cantec de la tastatura
    a9.setSongTitle(titlumel); //set nume cantec
    int an; 
    cin>>an; //citire an melodie de la tastatura
    a9.setSongYear(an); //set an melodie*/

    vector<Song> andra_songs={a1,a2,a3,a4,a5,a6,a7,a8,a9};

    Album album_andra("Iubește-mă azi, iubește-mă mâine", andra, andra_songs.size(), andra_songs, 2010);
    cout<<album_andra<<'\n';


    vector<Song> others={a1,tz1,tw1,a2,tz2,tz3,tz4,tz5,tz6,tw7,tz8};
    Playlist muzica("Muzica", others.size(), others);

    cout<<muzica<<'\n';

}
