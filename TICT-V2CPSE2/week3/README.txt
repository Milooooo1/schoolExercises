In de main.cpp staan comments bij de code die niet goed werkt
de onderstaande code krijg ik als ik de code te optimaliseren.
Wanneer ik deze error krijg staat in de comments. De problemen
zijn hieronder ook nog even uitgewerkt.

Er zijn eigenlijk 2 dingen waar ik tegen aan loop, het verplaatsen van
de objecten gaat niet 'smooth'... Je klikt 1x op een object en vervolgens
klik je op de locatie waar je hem wilt, het object verplaatst dan ook
maar wordt niet 'gedeselecteerd'. Verder had ik ook het idee dat je de code
compacter/efficienter kan maken door alleen het object te hertekenen wat
verplaatst is, als ik dat probeer krijg ik echter een scherm wat steeds blijft
knipperen. 

Het tweede probleem is dat ik de objecten at runtime naar het bestand schrijf,
dit is niet iets wat ik eigenlijk wil aangezien je ook veel onnodig schrijft.
Het lieftste wil ik dus dat hij aan het eind, wanneer de gebruiker het programma
sluit, alle objecten naar het bestand schrijft.


ls: cannot access '/dev/ttyUSB?': No such file or
grep: @: No such file or directory
Compiling C++ (.cpp) file: main.cpp
"g++" @_cpp_flags -c -o main.o main.cpp
main.cpp: In function ‘int main(int, char**)’:
main.cpp:75:53: error: cannot call member function ‘void screen_object::screen_object_write(drawable*, std::ostream&)’ without object
  75 |      screen_object::screen_object_write(object, file);
     |                                                     ^
make: *** [..//../bmptk/Makefile.inc:1338: main.o] Error 1
