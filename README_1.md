# Proiect-POO
Nume proiect: Music Library

Tema: Am ales ca tema proiectului un music library

Clase: 
  1. String - clasa ce memoreaza elemente de tip string pentru a putea folosi siruri de caractere in alte clase;
  2. Artist - clasa ce memoreaza un string cu numele artistului si un numar ce reprezinta varsta lui;
  3. Song - clasa ce retine un string cu titlul melodiei, are in componenta o variabila de tip Artist descrisa mai sus si un numar ce reprezinta anul lansarii melodiei;
  4. Album - clasa ce memoreaza un string cu titlul albumului, un vector de melodii (variabile de tip Song), un numar care reprezinta numarul de cantece din albumul respectiv, o variabila de tip Artist, un numar care reprezinta anul lansarii albumului si o variabila de tip intreg pentru pretul albumului;
  5. Playlist - clasa ce memoreaza un string cu titlul playlistului, un vector de melodii (variabile de tip Song), un numar care semnifica numarul de cantece din playlist.
  
Functionalitati:
- capabil sa retina o lista de artisti (nume + varsta);
- capabil sa retina o lista de melodii (nume + variabila de tip artist + an);
- capabil sa retina un album de melodii (nume + vector melodii + nr cantece + variabila de tip artist + an + pret);
- capabil sa calculeze cu ajutorul unei metode, pretul unui Album in functie de 2 criterii: daca albumul contine mai mult de 10 melodii, pretul scade cu 3 unitati/melodie; daca albumul este mai vechi de anul 2016, pretul este redus cu 50%;
- capabil sa calculeze durata unui album in functie de durata melodiilor din acesta, si afisarea ei in secunde prin intermediul unei metode;
- capabil sa afiseze un album (afiseaza titlu, numele artistului, anul si lista de melodii);
- capabil sa retina un playlist (titlu playlist + vector melodii + nr melodii) si sa il afiseze in maniera asemanatoare cu album.
                 
                 
