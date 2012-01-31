Pozdravljeni. 

Na zgoščenki so tri mape:
  - libtweaksort
  - sorts
  - exaples

V mapi libtweaksort se nahaja knjižnica v kateri je implementiran kompozitni algoritem
(sort.hpp) in knjižnica v kateri je implementiran algoritem za iskanje optimalne 
konfiguracije (learn.hpp). Notri sta še dve datoteki, ki ju ti dve knjižnici porebujeta.

V mapi sorts se nahajajo implementacije vseh ostalih sortirnih algoritmov. To so:
  - i.hpp (insertion sort)
  - s.hpp (selection sort)
  - h.hpp (heapsort)
  - q.hpp (quicksort)
  - m.hpp (merge sort)

V mapi examples pa se nahaja vsa programska koda, ki sem jo uporabljal pri raziskovanju.
Tam so tudi programi za risanje grafov in testiranje, ki pa imajo svoja lastna navodila za
uporabo. Vsi programi preverjeno delajo na sistemu Linux. Za Windows bi jih bilo potrebno
ponovno prevesti v okolju Windows. Za uporabo zgolj zgornjih dveh knjižnih pa na sistemih
Windows ni ovir, le funkcija za merjenje časa je precej slaba, saj je uporabljena kar
tista, ki je vgrajena v C++.

Vse datoteke v knjižnicah so komentirane po sistemu doxygen, tako da je dokumentacijo zelo
lahko zgenerirati. Zgenerirana dokumentacija je dostopna na
http://gimvic.org/slak/tweaksort/doxygen/html/.

Jure Slak
