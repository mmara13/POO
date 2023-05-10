# Proiect-POO
Nume proiect: Music Library

Tema: Am ales ca tema proiectului un music library

Clase: 
  1. Artist - clasa ce memoreaza un string cu numele artistului si un numar ce reprezinta varsta lui;
  2. Media - clasa abstracta care contine un string ce retine titlu, un destructor virtual, si doua metode pur virtuale;
  3. Song - clasa ce retine un string cu titlul melodiei, are in componenta o variabila de tip Artist descrisa mai sus si un numar ce reprezinta anul lansarii melodiei **(mostenita din clasa Media)**;
  4. Searchable - interfata - are un destructor virtual si 3 metode virtuale cu ajutorul carora putem cauta cantece din Playlist/Albume/etc. in functie de titlu/artist/anul lansarii;
  5. Album - clasa ce memoreaza un string cu titlul albumului, un vector de melodii (variabile de tip Song), un numar care reprezinta numarul de cantece din albumul respectiv, o variabila de tip Artist, un numar care reprezinta anul lansarii albumului si o variabila de tip intreg pentru pretul albumului **(mostenita din clasa Searchable - pt metodele virtuale de cautare, si din clasa Media pentru metoda virtuala de afisare)**;
  6. GenreAlbum - clasa mostenita din clasa Album, care adauga celei din urma un string care retine genul muzical al albumului.
  7.  Playlist - clasa ce memoreaza un string cu titlul playlistului, un vector de melodii (variabile de tip Song), un numar care semnifica numarul de cantece din playlist **(mostenita din clasa Searchable - pt metodele virtuale de cautare, si din clasa Media pt metoda virtuala de afisare)**;
  8. UserAccount - clasa ce retine doua variabile de tip string: una pentru username si una pentru password. Are ca metoda relevanta changePassword() care permite utilizatorului schimbarea parolei contului;
  9. User - mostenita din clasa UserAccount - adauga la aceasta un string care reprezinta numele utilizatorului, un vector de pointeri la Media care reprezinta diferitele media pe care utilizatorul le are in cont ( playlist-uri/albume/etc.), un numar curent de useri pe care ii avem in program, si un numar maxim de useri pe care ii putem avea;
  10. Mixtape - clasa mostenita din clasele Album si Playlist - contine un string cu titlul;
  11. Track - clasa template - functia play care functioneaza pe orice tip de data;
  12. SongIterator - clasa iterator.

Exceptii: 
  1. DuplicateLibraryException - clasa de exceptii care extinde std::exception prin care se verifica, in momentul adaugarii unei noi colectii intr-o librarie, daca nu cumva aceasta a mai fost adaugata anterior. Se afiseaza "Acest element este deja in biblioteca!";
  2. InvalidSongDurationException - clasa de exceptii care arunca exceptie in cazul in care valoarea atribuita variabilei time setate unei melodii este <= 0. In acest caz, se afiseaza "Durata melodiei trebuie sa fie pozitiva!";
  3. InvalidPlaylistNameException - clasa care arunca exceptie in cazul in care numarul de caractere folosit in denumirea unui playlist depaseste 50. Se afiseaza "Numele playlist-ului este prea lung!";
  4. InvalidUserAccountException - clasa care arunca exceptie in momentul in care un user incearca sa se conecteze dar foloseste username/parola incorecte. In acest caz s-ar afisa "Username sau parola incorecte!";
  5. InvalidCredentialsException - clasa de exceptie care este aruncata in momentul in care este aruncata si exceptia anterioara. Aceasta verifica si daca nu cumva username-ul sau parola sunt siruri goale. In aceste cazuri, se afiseaza "Autentificare nereusita!" respectiv "Username sau parola nu pot fi goale!".
  
Functionalitati:
- capabil sa retina o lista de artisti (nume + varsta);
- capabil sa retina o lista de melodii (nume + variabila de tip artist + an);
- capabil sa retina un album de melodii (nume + vector melodii + nr cantece + variabila de tip artist + an + pret);
- capabil sa calculeze cu ajutorul unei metode, pretul unui Album in functie de 2 criterii: daca albumul contine mai mult de 10 melodii, pretul scade cu 3 unitati/melodie; daca albumul este mai vechi de anul 2016, pretul este redus cu 50%;
- capabil sa calculeze durata unui album in functie de durata melodiilor din acesta, si afisarea ei in secunde prin intermediul unei metode;
- capabil sa afiseze un album (afiseaza titlu, numele artistului, anul si lista de melodii);
- capabil sa retina un playlist (titlu playlist + vector melodii + nr melodii) si sa il afiseze in maniera asemanatoare cu album;
- verifica daca intr-o biblioteca incearca sa se adauge o variabila media deja existenta (arunca exceptie daca da);
- verifica sa fie pozitiva durata unui cantec (arunca exceptie daca nu e);
- verifica sa fie mai mica decat 50 lungimea numelui unui playlist (arunca exceptie daca nu e);
- verifica daca username-ul si parola sunt corecte in momentul autentificarii (arunca exceptie altfel);
- verifica daca username-ul si/sau parola sunt goale (daca da, arunca exceptie);
- capabil sa afiseze playlist-uri/albume/mixtape-uri cu ajutorul unei singure metode virtuale (displayDetails())
- capabil sa caute o melodie dupa titlu/numele artistului/anul lansarii cu ajutorul functiilor virtuale
- capabil cu ajutorul unei functii statice si a downcast-ului sa determine daca variabilele salvate intr-una de tip Media sunt albume (daca da, afiseaza detaliile, altfel afiseaza o informare ca sunt de alt tip);
- capabil sa retina si genul muzical al unui album
- capabil sa retina users (username+parola) si sa le schimbe parola (simuland realitatea - trebuie cunoscuta parola curenta pentru a se putea schimba parola);
- capabil sa adauge prin intermediul mostenirii un nume acestui user si sa ii atribuie o biblioteca in care se pot adauga diverite tipuri de media;
- simuleaza autentificare intr-un cont cu ajutorul functiei autheticateUser care verifica daca username-ul si parola sunt bine introduse si sunt cele corecte;
- capabil sa retina un Mixtape (variabila formata din Album si Playlist, mostenind toate atributele acestora);
- contine functia play() ce reda date precum Playlist-uri/Albume/Melodii, iar daca sunt altfel de date afiseaza un mesaj spunand ca tipul este necunoscut dar o reda indiferent;
- functie template printInfo() care afiseaza informatii despre tipul de date folosit;
- poate parcurge un vector de melodii folosind un iterator;
- capabil sa caute si sa returneze un vector de melodii dupa artist, folosind functia utilitara copy_if();
- sorteaza un vector de melodii dupa durata acestora folosind functia utilitara sort();
- foloseste unique_ptr pentru media in loc de vector de pointeri obisnuiti;
- foloseste shared_ptr pentru libraria unui user pentru a arata la diferite tipuri de date.
                 
