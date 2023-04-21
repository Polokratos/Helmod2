# Helmod2
Kalkulator linii montażowych, wykorzystujący interfejs REPL.


# About
Rozważamy następującą klasę problemu:
Mamy jakiś zestaw maszyn składających się na linię montażową i chcemy znaleźć ilości zezwalające nam na osiągnięcie żądanego poziomu produkcji.

Najlepiej zobrazować na przykładzie.
Będziemy tworzyć śrubki z metalowych płyt.
Mamy 2 typy maszyn. Masszyna A dzieli płyty na pręty, B wytwarza śruby z prętów.
Powiedzmy, że A wytwarza w jednostce czasu 4 pręty z jednej płyty.
B wytwarza 10 śrub z 1 pręta.

Jakie muszą być ilości maszyn A i B żeby osiągnąć produkcję 200 śrub w jednostce czasu?

Oczywiście rozwiązanie tego akurat problenu nie jest wielkim wyzwaniem.
Lecz gdy dołożymy setki typów maszyn, tysiące półproduktów zaczynamy mieć wyzwanie.
Dołączmy do tego produkty uboczne i ich utylizację - dostajemy głęboko rekursywne zależności, których ręczne policzenie jest co najmniej wyzwaniem.

# Dostępne komendy.
help                              : Prints this message.
load  <path>                      : Loads production lines from path
new <name>                        : Creates new, empty production line.
add [-s] <b_name> <i_name> <pval> : Adds a new production block b_name
                                    then rescales it so that
                                    the total production of i_name
                                    in the entire line will be equal p_val.
                                    If production block b_name already exists
                                    does not add a 2nd time, only rescales.
remove [-s] <b_name>              : Removes a production block.
rescale [-s] <i_name> <pval>      : Rescales the entire line,
                                    so that the production of i_name reaches pval
In add, remove and rescale commands, unless the -s option is specified
dump will be called immedietaly afterwards.
save <path>                       : Saves the current line to path
dump [-a] [name]                  : Prints production values of <name> line to screen
                                    If -a option is specified,
                                    all details of current production line will be printed
                                    If no name is specified
                                    the active production line is printed.
quit                              : Exits the program.