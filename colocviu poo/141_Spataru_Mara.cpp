/*
Nume: Spataru Mara-Andreea  Grupa: 141
Compilator: MINGW gcc.exe (GCC) 11.2.0 (VS Code)
Tutore laborator: Gabriel Majeri
*/   

#include <bits/stdc++.h>
using namespace std;

class Drum{
protected:
    string denumire;
    double lungime;
    int nr_tronsoane;
public:
    Drum()=default; //constructor fara param
    Drum(string d, double l, int nr);
    Drum(const Drum& d);
    Drum& operator=(const Drum& d);
    friend istream& operator>>(istream& is, Drum& d);
    friend ostream& operator<<(ostream& os, Drum& d);
    virtual ~Drum();
};
Drum::~Drum(){
    denumire="";
    lungime=nr_tronsoane=0;
}
ostream& operator<<(ostream& os, Drum& d){
    os<<"Denumirea drumului este: "<<d.denumire<<'\n';
    os<<"Lungimea drumului este: "<<d.lungime<<'\n';
    os<<"Numarul de tronsoane ale drumului: "<<d.nr_tronsoane<<'\n';
    return os;
}
istream& operator>>(istream& is, Drum& d){
    cout<<"Denumirea drumului este:\n";
    string s;
    is.get();
    getline(is, s);
    d.denumire=s;
    cout<<"Lungimea drumului este:\n";
    is>>d.lungime;
    cout<<"Numarul de tronsoane ale drumului este:\n";
    is>>d.nr_tronsoane;
    return is;
}
Drum& Drum::operator=(const Drum& d){
    denumire=d.denumire;
    lungime=d.lungime;
    nr_tronsoane=d.nr_tronsoane;
    return *this;
}
Drum::Drum(const Drum& d){
    denumire=d.denumire;
    lungime=d.lungime;
    nr_tronsoane=d.nr_tronsoane;
}
Drum::Drum(string d, double l, int nr):denumire(d), lungime(l), nr_tronsoane(nr){
}

class DrumNational: public Drum{
    int nr_judete;
public:
    DrumNational()=default; //constructor fara param
    DrumNational(string d, double l, int nr, int nrj);
    DrumNational(const DrumNational& dn);
    DrumNational& operator=(const DrumNational& dn);
    friend istream& operator>>(istream& is, DrumNational& dn);
    friend ostream& operator<<(ostream& os, DrumNational& dn);
    ~DrumNational() override;
};
DrumNational::~DrumNational(){
    denumire="";
    lungime=nr_tronsoane=0;
    nr_judete=0;
}
istream& operator>>(istream& is, DrumNational& dn){
    cout<<"Denumirea drumului national este:\n";
    string s;
    is.get();
    getline(is, s);
    dn.denumire=s;
    cout<<"Lungimea drumului national este:\n";
    is>>dn.lungime;
    cout<<"Numarul de tronsoane ale drumului national este:\n";
    is>>dn.nr_tronsoane;
    cout<<"Numarul de judete prin care drumul national trece:\n";
    is>>dn.nr_judete;
    return is;
}
ostream& operator<<(ostream& os, DrumNational& dn){
    os<<"Denumirea drumului national este: "<<dn.denumire<<'\n';
    os<<"Lungimea drumului national este: "<<dn.lungime<<'\n';
    os<<"Numarul de tronsoane ale drumului national: "<<dn.nr_tronsoane<<'\n';
    os<<"Numarul de judete prin care drumul national trece: "<<dn.nr_judete<<'\n';
    return os;
}
DrumNational& DrumNational::operator=(const DrumNational& dn){
    denumire=dn.denumire;
    lungime=dn.lungime;
    nr_tronsoane=dn.nr_tronsoane;
    nr_judete=dn.nr_judete;
    return *this;
}
DrumNational::DrumNational(const DrumNational& dn){
    denumire=dn.denumire;
    lungime=dn.lungime;
    nr_tronsoane=dn.nr_tronsoane;
    nr_judete=dn.nr_judete;
}
DrumNational::DrumNational(string d, double l, int nr, int nrj):Drum(d,l,nr), nr_judete(nrj){};


class DrumEuropean: public Drum{
    int nr_tari;
public:
    DrumEuropean()=default; //construct fara param
    DrumEuropean(string d, double l, int nr, int nrt); //constr cu param
    DrumEuropean(const DrumEuropean& de);
    DrumEuropean& operator=(const DrumEuropean& de);
    friend istream& operator>>(istream& is, DrumEuropean& de);
    friend ostream& operator<<(ostream& is, DrumEuropean& de);
    ~DrumEuropean() override; //suprascriere destructor virtual din clasa de baza

};
DrumEuropean::~DrumEuropean(){
    denumire="";
    lungime=nr_tronsoane=0;
    nr_tari=0;
}
ostream& operator<<(ostream& os, DrumEuropean& de){
    os<<"Denumirea drumului european este: "<<de.denumire<<'\n';
    os<<"Lungimea drumului european este: "<<de.lungime<<'\n';
    os<<"Numarul de tronsoane ale drumului european: "<<de.nr_tronsoane<<'\n';
    os<<"Numarul de tari prin care drumul european trece: "<<de.nr_tari<<'\n';
    return os;
}
istream& operator>>(istream& is, DrumEuropean& de){
    cout<<"Denumirea drumului european este:\n";
    string s;
    is.get();
    getline(is, s);
    de.denumire=s;
    cout<<"Lungimea drumului european este:\n";
    is>>de.lungime;
    cout<<"Numarul de tronsoane ale drumului european este:\n";
    is>>de.nr_tronsoane;
    cout<<"Numarul de tari prin care trece drumul european:\n";
    is>>de.nr_tari;
    return is;
}
DrumEuropean& DrumEuropean::operator=(const DrumEuropean& de){
    denumire=de.denumire;
    lungime=de.lungime;
    nr_tronsoane=de.nr_tronsoane;
    nr_tari=de.nr_tari;
    return *this;
}
DrumEuropean::DrumEuropean(const DrumEuropean& de){
    denumire=de.denumire;
    lungime=de.lungime;
    nr_tronsoane=de.nr_tronsoane;
    nr_tari=de.nr_tari;
}
DrumEuropean::DrumEuropean(string d, double l, int nr, int nrt):Drum(d,l,nr), nr_tari(nrt){};


class Autostrada: public Drum{
    int nr_benzi;
public:
    Autostrada()=default; //constructor default fara param
    Autostrada(string d, double l, int nr, int nrb); //constr cu param
    Autostrada(const Autostrada& a);//copy cstr
    Autostrada& operator=(const Autostrada& a); //operator = suprascriere
    friend istream& operator>>(istream& is, Autostrada& a);
    friend ostream& operator<<(ostream& os, Autostrada& a);
    ~Autostrada() override; //suprascriere destructor virtual din cls de Baza
};
Autostrada::~Autostrada(){
    denumire="";
    lungime=nr_tronsoane=0;
    nr_benzi=0;
}
ostream& operator<<(ostream& os, Autostrada& a){
    os<<"Denumirea autostrazii este: "<<a.denumire<<'\n';
    os<<"Lungimea autostrazii este: "<<a.lungime<<'\n';
    os<<"Numarul de tronsoane ale autostrazii: "<<a.nr_tronsoane<<'\n';
    os<<"Numarul de benzi ale autostrazii: "<<a.nr_benzi<<'\n';
    return os;
}
istream& operator>>(istream& is, Autostrada& a){
    cout<<"Denumirea autostrazii este:\n";
    string s;
    is.get();
    getline(is, s);
    a.denumire=s;
    cout<<"Lungimea autostrazii este:\n";
    is>>a.lungime;
    cout<<"Numarul de tronsoane ale autostrazii este:\n";
    is>>a.nr_tronsoane;
    cout<<"Numarul de benzi ale autostrazii:\n";
    is>>a.nr_benzi;
    return is;
}
Autostrada& Autostrada::operator=(const Autostrada& a){
    denumire=a.denumire;
    lungime=a.lungime;
    nr_tronsoane=a.nr_tronsoane;
    nr_benzi=a.nr_benzi;
    return *this;
}
Autostrada::Autostrada(const Autostrada& a){
    denumire=a.denumire;
    lungime=a.lungime;
    nr_tronsoane=a.nr_tronsoane;
    nr_benzi=a.nr_benzi;
}
Autostrada::Autostrada(string d, double l, int nr, int nrb):Drum(d,l,nr), nr_benzi(nrb){};



class AutostradaEuropeana:public Drum{
    int nr_tari, nr_benzi;
public: //doar modificam metodele, constructori etc
    AutostradaEuropeana()=default; //constr default fara param
    AutostradaEuropeana(string d, double l, int nr, int nrt, int nrb); //constr cu param
    AutostradaEuropeana(const AutostradaEuropeana& ae); //copy cstr
    AutostradaEuropeana& operator=(const AutostradaEuropeana& ae);//operator =
    friend istream& operator>>(istream& is, AutostradaEuropeana& ae); //citire pt clasa autostrada europeana
    friend ostream& operator<<(ostream& os, AutostradaEuropeana& ae); //afisare pt clasa autostrada europeana
};
ostream& operator<<(ostream& os, AutostradaEuropeana& ae){
    os<<"Denumirea autostrazii este: "<<ae.denumire<<'\n';
    os<<"Lungimea autostrazii este: "<<ae.lungime<<'\n';
    os<<"Numarul de tronsoane ale autostrazii: "<<ae.nr_tronsoane<<'\n';
    os<<"Numarul de benzi ale autostrazii: "<<ae.nr_benzi<<'\n';
    os<<"Numarul de tari prin care trece autostrada "<<ae.nr_tari<<'\n';
    return os;
}
istream& operator>>(istream& is, AutostradaEuropeana& ae){
    cout<<"Denumirea autostrazii este:\n";
    string s;
    is.get();
    getline(is, s);
    ae.denumire=s;
    cout<<"Lungimea autostrazii este:\n";
    is>>ae.lungime;
    cout<<"Numarul de tronsoane ale autostrazii este:\n";
    is>>ae.nr_tronsoane;
    cout<<"Numarul de benzi ale autostrazii:\n";
    is>>ae.nr_benzi;
    cout<<"Numarul de tari prin care autostrada trece:\n";
    is>>ae.nr_tari;
    return is;
}
AutostradaEuropeana& AutostradaEuropeana::operator=(const AutostradaEuropeana& ae){
    denumire=ae.denumire;
    lungime=ae.lungime;
    nr_tronsoane=ae.nr_tronsoane;
    nr_tari=ae.nr_tari;
    nr_benzi=ae.nr_benzi;
    return *this;
}
AutostradaEuropeana::AutostradaEuropeana(const AutostradaEuropeana& ae){
    denumire=ae.denumire;
    lungime=ae.lungime;
    nr_tronsoane=ae.nr_tronsoane;
    nr_tari=ae.nr_tari;
    nr_benzi=ae.nr_benzi;
}
AutostradaEuropeana::AutostradaEuropeana(string d, double l, int nr, int nrt, int nrb): Drum(d,l,nr),nr_benzi(nrb), nr_tari(nrt){};


class Contract{
    static int id;
    string nume, CIF;
    Drum* drum;
    int tronson;
public:
    Contract()=default; //constructor fara parametrii
    Contract(string n, string c, int t); //constr cu parametrii
    Contract(const Contract& c); //copy cstr
    Contract& operator=(const Contract& c); //opeartor =
    friend istream& operator>>(istream& is, Contract& c); //citire
    friend ostream& operator<<(ostream& os, Contract& c); //afisare
    virtual ~Contract();
    Drum getDrum()const;
    void setDrum(Drum d);
};
void Contract::setDrum(Drum d){
    this->drum=&d;
}
Drum Contract::getDrum()const{
    return *drum;
}
Contract::~Contract(){
    nume="";
    CIF="";
    drum=nullptr;
    tronson=0;
}
ostream& operator<<(ostream& os, Contract & c){
    os<<"Id-ul contractului este: "<<c.id<<'\n';
    os<<"Numele firmei care are contractul este: "<<c.nume<<'\n';
    os<<"CIF-ul firmei este: "<<c.CIF<<'\n';
    os<<"Tronsonul atribuit este: "<<c.tronson<<'\n';
    os<<"Drumul ilustrat in contract este\n"<<*(c.drum)<<'\n'; 
    return os;
}
istream& operator>>(istream& is, Contract& c){
    cout<<"Numele firmei este:\n";
    string s;
    is.get();
    getline(is, s);
    c.nume=s;
    cout<<"CIF-ul firmei este:\n";
    is>>c.CIF;
    cout<<"Tronsonul atribuit este:\n";
    is>>c.tronson;
    return is;
}
Contract& Contract::operator=(const Contract& c){
    id=c.id;
    nume=c.nume;
    CIF=c.CIF;
    drum=c.drum;
    tronson=c.tronson;
    return *this;
}
Contract::Contract(const Contract& c){
    id=c.id;
    nume=c.nume;
    CIF=c.CIF;
    drum=c.drum;
    tronson=c.tronson;
}
Contract::Contract(string n, string c, int t):nume(n), CIF(c), tronson(t){
    ++id;
}
int Contract::id=0; //initializare variabila statica

int main(){
    int optiune; //optiune pentru meniu
    vector<Drum> drumuri;
    vector<DrumNational> drumuri_nationale;
    vector<DrumEuropean> drumuri_europene;
    vector<Autostrada> autostrazi;
    vector<AutostradaEuropeana> autostrazi_europene;
    vector<Contract> contracte;
    while(1){
        cout<<"1.Adaugare Drum\n";
        cout<<"2.Adaugare Drum National\n";
        cout<<"3.Adaugare Drum European\n";
        cout<<"4.Adaugare Autostrada\n";
        cout<<"5.Adaugare Autostrada-Europeana\n";
        cout<<"6.Adaugare Contract\n";
        cout<<"7.Afisare Drumuri\n";
        cout<<"8.Afisare Drumuri National\n";
        cout<<"9.Afisare Drumuri Europene\n";
        cout<<"10.Afisare Autostrazi\n";
        cout<<"11.Afisare Autostrazi-Europene\n";
        cout<<"12.Afisare Contracte\n";
        cout<<"13.Inchide meniu\n\n";
        cin>>optiune;

        // try{
            if(optiune<1 || optiune>13){
                throw string("Optiune invalida!");
            }
            else if(optiune==1){
                Drum d;
                cin>>d;
                drumuri.push_back(d);
            }
            else if(optiune==2){
                DrumNational dn;
                cin>>dn;
                drumuri_nationale.push_back(dn);
            }
            else if(optiune==3){
                DrumEuropean de;
                cin>>de;
                drumuri_europene.push_back(de);
            }
            else if(optiune==4){
                Autostrada a;
                cin>>a;
                autostrazi.push_back(a);
            }
            else if(optiune==5){
                AutostradaEuropeana ae;
                cin>>ae;
                autostrazi_europene.push_back(ae);
            }
            else if(optiune==6){
                Contract c;
                Drum d;
                cin>>d;
                cin>>c;
                contracte.push_back(c);
                c.setDrum(d);
            }
            else if(optiune==7){
                for(auto i: drumuri)
                    cout<<i<<'\n';
                cout<<'\n';
            }
            else if(optiune==8){
                for(auto i: drumuri_nationale)
                    cout<<i<<'\n';
                cout<<'\n';
            }
            else if(optiune==9){
                for(auto i:drumuri_europene)
                    cout<<i<<'\n';
                cout<<'\n';
            }
            else if(optiune==10){
                for(auto i: autostrazi)
                    cout<<i<<'\n';
                cout<<'\n';
            }
            else if(optiune==11){
                for(auto i: autostrazi_europene)
                    cout<<i<<'\n';
                cout<<'\n';
            }
            else if(optiune==12){
                for(auto i: contracte)
                    cout<<i<<'\n';
                cout<<'\n';
            }
            else if(optiune==13) break;
    //    }catch(){};

    }
    return 0;
}