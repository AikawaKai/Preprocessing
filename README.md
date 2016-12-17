# Preprocessing

Tramite questo progetto in cpp è possibile realizzare pseudo-randomicamente dei modelli di programmazione lineare intera\continua\binaria\mista e applicarvi alcune tecniche di preprocessing (Per maggiori dettagli si invita a leggere il contenuto della relazione.pdf, nella folder Relazione della repo)

## Istruzione per la compilazione:

g++ -std=c++11 -o preprocess.exe utility.cpp write_utility.cpp print_utility.cpp preprocess.cpp main.cpp

## Istruzione per l'esecuzione:

./preprocess.exe parameters.txt

## Contenuto parameters.txt

- NumOfVar: 5  **[Il numero di variabili che si vuole generare nel problema]**
- NumOfVinc: 3 **[Il numero di vincoli che si vogliono generare per il problema]**
- MaxVal: 10 **[Il valore massimo che possono assumere i coefficienti e i bound delle variabili]**
- MinVal: -10 **[Il valore minimo che possono assumere i coefficienti e i boun delle variabili]**
- Seed1: 1241 **[Il seed da inizializzare per i diversi generatori presenti all'interno del codice]**
- NameFileDat1: before.dat **[Il nome del file dati da utilizzare per AMPL, in cui verranno scritti i dati del problema prima del preprocessamento]**
- NameFileDat2: after.dat **[Il nome del file dati da utilizzare per AMPL, in cui verranno scritti i dati a seguito del preprocessamento**]
- bin: 0 **[Variabile che ci dice se vogliamo il caso binario puro, o un caso mixed. Assume 1 se vogliamo il caso binario, 0 altrimenti]**
- MaxValTN: 20 **[Variabile che ci dice il massimo valore che possono assumere i termini noti dei vincoli]**
- MinValTN: 10 **[Variabile che ci dice il minimo valore che possono assumere i termini noti dei vincoli]**

**NOTA:** è di fondamentale importanza che ci sia uno spazio tra la variabile e il suo nome, altrimenti il file non viene letto correttamente dal programma.

