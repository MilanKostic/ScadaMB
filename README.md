# ScadaMB

SCADA sistem 2 (par II)
Projektovati i implementirati SCADA sistem koji prikuplja podatke od Modbus TCP simulatora na
svakih 2s. Nakon prikupljanja podataka treba da se podaci obrade i po potrebi da se korisniku saopšte
alarmna stanja. Sistem treba da omoguci i izdavanje komandi.
Opis kontrolisanog procesa:
Nadzire se i upravlja se mešalicom betona.
Monitorisane veličine:
  1. Ventil vode (otvoren-zatvoren)
  2. Ventil peska (otvoren-zatvoren)
  3. Ventil šljunka (otvoren-zatvoren)
  4. Mešanje (stanje uključeno-isključeno)
  5. Pražnjenje mešalice (stanje uključeno-isključeno )
Kontrolisane veličine:
  1. Količina vode
  2. Količina peska3. Količina šljunka
  4. Stanje mešalice (prazno-ne prazno)
  5. Detektor kamiona (ima-nema)
  6. Pražnjenje mešalice (u toku - nije u toku)
Radi se u closed loop režimu!
Ukoliko je otvoren ventil vode-peska-šljunka, treba da se uvećava količina sirovine i to 100 jedinica po
sekundi.
Pražnjenje mešalice je dozvoljeno samo ukoliko je kamion detektovan I ako su svi ventili zatvoreni.
Detekciju kamiona menjati svakih 2 minuta. Ukoliko je pražnjenje mešalice izvršeno postaviti stanje
mešalice na odgovarajuce i količine sirovina nulirati. Tokom pražnjena je brzina smanjivanja sirovine 50
jedinica po sekundi (sporije se prazni nego što se puni).
Alarmna stanja:
Pražnjenje mesalice komandovano, a nisu svi ventili zatvoreni.
HMI:
Korisnička sprega SCADA sistema je klijentska aplikacija za SCADA server, a treba da omogući
korisniku da bude u mogućnosti da komanduje kontrolisanim uređajima, kao i da ima uvid u trenutno
stanje sistema. Klijentska aplikacija komunicira sa SCADA serverom putem TCP/IP protokola na unapred
definisanom portu.
Napomena:
Konfiguracija upravljačkog bloka treba da sadrži podatke za sva polja iz SCADA modela koja je
prikazana na vežbama (prezentacija: „3. i 4 SCADA model podataka“).
SCADA server se konfiguriše iz datoteke.
