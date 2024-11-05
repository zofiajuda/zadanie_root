# zadanie_root

Folder zawiera makra napisane w środowisku ROOT. Aby móc je uruchomić należy mieć zainstalowane środowisko root.

Makro WidmoCs.C jest wersją podstawową do czytania pliku tekstowego Cs-137.dat, na postawie którego rysuje widmo danych oraz dodatkowo wyznacza znalezione piki. 
Jako argument funckja bierze nazwę pliku z którego ma czytać dane, domyślnie jest to plik Cs-137.dat.
Makro można uruchomić w następujące sposoby:
  root WidmoCs.C -> makro uruchomi się z domyślnym argumentem
  w sesji root'a poprzez .x WidmoCs.C -> również uruchomi się z domyślnym argumentem
  w sesji root poprzez:
  .L WidmoCs.C => ładowanie makra
  WidmoCs("nazwa_pliku"); -> ta opcja umożliwa uruchomienie programu z innym argumentem

  Makro RewriteFile.C służy do konwersji pliku tekstowego Cs-137.dat do pliku binarnego. Jako argumenty bierze nazwę pliku konwertowanego domyślnie ustawioną na Cs-137.dat i nazwę pliku wyjściowego domyślnie ustawioną na Cs137.bin. W pliku binarnym zapisywane są Floaty.
  Makto można uruchomić analogicznie do pierwszego makra.

  Makro binary_read.C służy do czytania pliku binearnego i zapisywania jego wartości do tablicy. 
  Jako argumenty bierze tablicę doubli oraz nazwę pliku, z którego ma czystać domyślnie ustawioną na Cs137.bin. 
  To makro czyta plik  binarny zawierający Floaty!

  Do uruchomienia makra WidmoCsBin.C konieczne są makra RewriteFile.C i binary_read.C.
  To makro bierze plik tekstowy, który jest argumentem funkcji, domyślnie ustawionym na "Cs-137.dat", następnie konwertuje je na plik binarny, którego nazwa również jest argumentem funkcji domyślnie ustawionym na "Cs137.bin" => korzysta przy tym z funkcji RewriteFile.C.
  Nastepnie czyta plik przy pomocy makra binary_read.C, wpisuje wartości do histogramu. Znajduje piki, zaznacza je na histogramie. Histogramy oraz pozycje pików są wpisywane do drzewa rootowskiego.
  Uruchamiane analogicznie do makra WidmoCs.C

Makro generate.C generuje z liczb pseudolosowych 4 rozkłady, następnie rysuje je na kanwie, przy pomocy THStack. Makro nie posiada żadnych argumentów.

  
  
