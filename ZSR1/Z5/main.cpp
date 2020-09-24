	std::toupper(string)						cctype
	std::getline(std::cin, s);					string
	std::cin >> broj >> std::ws;				ingorira whitespaces do iduceg non whitespace
	char znak = std::cin.get(); 				uzme 1 char, pa cak i \n, whitespace etc.
	std::cin.getline(a, sizeof a, '\n');		kupi znakove za arrays of char sve dok nepopuni niz ili do \n
	for(char c : s1) s3.push_back(c);
	za spajanje stringova bar jedan parametar mora biti stiring 
	niz znakova mozemo poslati u niz pri cemu se on automatski konvertira u string
	s.substr(0, 5)
	std::to_string(2 + 3)
	std::stod(s)	string to double
	std::stoi(s)	string to integer
	std::strcpy(znakovi, s.c_str()); 	kad mora primit string na mjestu char array
	std::remove_reference<decltype(neki_izraz)>::type		type_traits,  uklanja reference jer decltype ispred funkcije vraca referencu na taj element
	decltype(0 + c[0])					kao iznad samo jednostavnije

	for(std::vector<int>::iterator i = v.begin(); i != v.end(); i++)
	 std::cout << *i << " ";

	 v.insert(v.begin() + n, x)          v.erase(v.begin() + n)”


	 template <typename TipElemenata>
		void IspisiDek(typename std::deque<TipElemenata>::iterator pocetak,
	 		typename std::deque<TipElemenata>::iterator iza_kraja) { //mora bit typename ispred iteratora  te se pozvati sa IspisiDek<int>(d.begin(), d.end())
	 			while(pocetak != iza_kraja) std::cout << *pocetak++ << " ";
	 	}

	template <typename Kontejner>
	 auto MaxElement(Kontejner &c, int broj_elemenata) -> decltype(c[0]+c[0]) {
	 int indeks = 0;
	 for(int i = 1; i < broj_elemenata; i++)
	 if(c[i] > c[indeks]) indeks = i;
	 return c[indeks];
	}


	[](double x) { return x * x * x - x – 1; }
	[](int x, double y) -> double { if(x > y) return x; else return y; }

	int (*pok_na_fun)(int, int); // bez zagrada na mjestu imean funkcije bi se smatralo kao prototip funkcije a ne pokazivac
	pok_na_fun = &Min;
	pok_na_fun = Min; //& nije obavezan
	std::cout << "Minimum je: " << (*pok_na_fun)(3, 5); 
	std::cout << "Minimum je: " << pok_na_fun(3, 5); //nije potrebno dereferencirati pokazivac na funkciju

	int (*pok_na_fun)(int, int) = [](int x, int y) { return x + y; };	//inicijalziacija
	pok_na_fun = [](int x, int y) { return x + y; }; 			5b 5. strana



	std::cout << (void *)pok_na_fun; // Ovo ispisuje adresu...



	//fragmentirana alokacija
	int **a = new int*[n]; // a je pokazivač na pokazivač
	for(int i = 0; i < n; i++) a[i] = new int[m];
	for(int i = 0; i < n; i++) delete[] a[i]; // Uništava redove
	delete[] a; // Uništava niz pokazivača na redove


	//kontinualna alokacija
	int **a = new int*[n];
	a[0] = new int[n * m];
	for(int i = 1; i < n; i++) a[i] = a[i – 1] + m; // ili a[i] = a[0] + m * i;


	int *&ref_na_pok = pok; // ovdje je pok neka pokazivačka promjenljiva //ref_na_pok je referenca na pokazivač
	void RazmijeniPokazivace(double *&x, double *&y) {
	 double *pomocna = x;
	x = y; y = pomocna;
	}





	“memory” zaglavlje za pametne pokazivace
	std::shared_ptr<double> p(new double(3.5));     //ne moze = kad je u pitanju new operator ali moze kad dodjeljujem drugi smart pointer ovom 	

	std::shared_ptr<double> p = std::make_shared<double>(3.5); // "=" je dopušteno  // make shared vraca pametni pokazivac pa moze = jer (new ...) je konverzija obicnog u smart pointer 
	p = std::make_shared<double>(2.13);   //pametne nmg delete uradit nego se sami brisu, i ne mogu im dati mem lokaciju neke promjenljive koja nije dinamicki alocirana i ne moze pokazivat na nizove vec samo na individualne promjenljive

	std::shared_ptr<int> p(new int[100], [](int *p) { delete[] p; });   //sad mogu pokazivat i na nizove jer inace ih brisu sa delete umjesto delete[] osim ako explicitno ne zadamo funkciju koja ce se pozivati pri brisanju nizova i ovakvom nizu pristupamo sa p.get()[i]

	za pemetne pok nema ++, +, +=, <, > ... vec samo !=, == i !

	std::shared_ptr<const double> p(new double(3.5));
	auto p = std::make_shared<const double>(3.5);



	std::unique_ptr<double> p(new double(3.5));
	p = std::unique_ptr<double>(new double(2.13));
	std::unique_ptr<double> p2 = std::move(p1);     //preusmjerenje kontrole, takodje samo ovo radi za davanje kontrole shared ptr-u
	std::unique_ptr<int[]> p(new int[5]);    //pookazuje na niz


	ulazni iteratori (engl. input iterators) - ne moraju se moci koristiti kao l vrijednost kad se dereferenciraju
	izlazni iteratori (engl. output iterators) - moraju se moci koristiti kao l vrijednost kad se dereferenciraju, ali ne moraju kao int a = *it
	iteratori sa kretanjem unaprijed (engl. forward iterators) - spoj ulaznog i izlaznog (nema --)
	dvosmjerni iteratori (engl. bidirectional iterators) -  ovo iznad sa operacijom -- (nemora biti podrzana pok artimetika (it + 5) i indeksiranje)
	iteratori sa direktnim (slučajnim) pristupom (engl. random access iterators) - ovo iznad sa operacijom >= <= < > 


	*Liste* #include list ?
	Iteratori su im dvosmjerni, znaci samo ++ i -- operacije
	std::list<int> lista{5, 2, 4, 6}; //liste se ne mogu indeksirati pa su efikasnije od dekova, a ostalo je isto ko dek
	lista.push_back(3);
	lista.push_front(8);

	//erase i insert su veoma efikasni jer se samo zahtjeva promjena 3 pokazivaca umjesto pomjeranje svih elemenata kao u vektoru ili deku
	it = lista.erase(it); // Obriši element i preuzmi iterator na sljedeći

	lista.insert(it, x); //stavi x ina poiciju gdje pokazuje it
	lista.sort() //jer neradi obicni sort iz alghorithim, mzoe joj se poslati funkcija poredjenja

	*Forward list*  //ista biblioteka ko list
	podrzava samo iteratore unaprije i umjesto insert i erase imaju 
	lista.insert_after(p_it, x); i erase_after te  lista.before_begin() 

	*Sets(skupovi) i multisets(multiskupovi)*    #include set
	Multiskupovi dozvolajvaju pojavljivanje istog elementa vise puta dok sets ne. 
	Podaci u njima se interno drze sortirano. Nemaju operacije indeksiranja i push _front jer element ili nije ili jeste u skupu te elementi u skupu nemaju poziciju.
	std::set<int> skup{3, 5, 1, 4, 3, 7};
	std::multiset<int> multiskup{3, 5, 1, 4, 3, 7};
	Begin() ce da dadne najmanji element u skupu jer su sortirani uvijek
	Za fukciju insert nemora se navoditi iterator pozicije osim ako ne zelimo da umetanje traje krace tj da guidamo element na blizu svoju poziciju
	Za funkciju erase dovoljno je navesti vrijednost elementa i on ce se izbrisati (samo za skupove)
	Skupove treba koristiti onda kada nam tačna pozicija elemenata
	u kolekciji nije bitna, ali imamo potrebu da ih brzo umećemo, brišemo i pronalazimo (za razliku od
	skupova, lista ne dozvoljava brzo pronalaženje elemenata, jer se ne može koristiti binarna pretraga).

	skup.find(5)  //vraca iterator na 5. element
	skup.count(x)  //broj puta pojavljivanja vrijednost
	*it = 10 	//neradi ako it pokazuje na neki element skupa, jedino mozemo izbaciti ili umetnuti novi element
	Skupovi nerade za tipove koji se ne mogu porediti kao complex numbers



	*Biblioteka #iterator:*
	std::advance(it, n)  //ko standardna petlja sa it++
	std::distance(it1, it2)  //ko while petlja koja broji razliku izmedju 2 pokazivaca    while(it1 != it2) brojac++;

	std::vector<int>::const_iterator it; //deref. daje const object kojem ne mozemo mjenjati vrijednost, koriste se za const vektore
	Begin i end funkcije nad ocnst vektorima daju const iterator koji se ne moze stavit u obicni iterator
	cbegin i cend uvjek daju const iterator cak i nad ne const vektorima

	Funkcije “rbegin” i “rend” primijenjene na neki kontejner daju kao rezultat obrnute iteratore koji pokazuju respektivno na kraj i tačno ispred početka kontejnera. Ovo su reverse_iterators

	Funkcija “back_inserter” traži kao parametar neki kontejner, a vraća umetač koji pokazuje tačno
	iza kraja kontejnera. Svako pisanje pomoću tog umetača dodaje element na kraj kontejnera, povećavajući
	njegovu veličinu za 1. Tipovi iteratora koje vraća funkcija “back_inserter” imaju užasna imena (poput
	“std::back_insert_iterator<std::vector<int>>” 

	Slična je funkcija “front_inserter” koja vraća umetač koji pokazuje na početak kontejnera, tako da
	vrši umetanje na početak kontejnera. Međutim, ovaj umetač je definiran samo za kontejnere koji
	podržavaju funkciju “push_front” (recimo, lista ili dek).

	Postoji i univerzalni umetač koji se može
	koristiti za umetanje na proizvoljno mjesto. On se dobija pozivom funkcije “inserter”. Ta funkcija kao
	parametre zahtijeva kontejner i obični iterator koji pokazuje na mjesto gdje se vrši umetanje, a vraća
	kao rezultat odgovarajući umetač. Jedino što se za kontejner zahtijeva je da podržava funkciju “insert”.
	Slijedi primjer primjene, nakon kojeg će vektor “v” sadržavati redom elemente 2, 6, 3, 5, 2, 8, 4, 1 i 7:

	std::deque<int> d{3, 5, 2, 8, 4};
	std::vector<int> v{2, 6, 1, 7};
	std::copy(d.begin(), d.end(), std::inserter(v, v.begin() + 2));


	std::ostream_iterator<int> it(std::cout, " ");  //u biblioteci iterator
	*it++ = 3; *it++ = 2; *it++ = 7;

	std::remove_copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"), 0);  //ispise sve elemente osim onih koji su jednaki nuli



	*Stack*  #include stack
	 zasnovan na last in first out

	*Queue* #include queue
	zasnovan na FIFO

	*priority_Queue* #include queue
	Best First Out - element na vrhu uvijek onaj koji je najbolji među elementima koji su u njega stavljeni  Podrazumijevano “najbolji” znači “najveći”, iako se kriterij “dobrote” može zadavati, ali u to nećemo ulaziti.


	U sva tri kontejnera novi elementi se dodaju pomoću funkcije “push
	pop uklanja gornji enement
	top daje gornji element bez uklanjanja (front za queue, a top za stack i priority q)
	back daje zadnji element reda
	empty daje true/false 


	*Lambde*
	[broj](int x) { return x > broj; } //[] je capture list da zarobi variable kao constante iz funkcije odakle se pozivaju
	[=] //zarobi sve promjenjive iz okruzenja
	[&] //zarobi sve promjenjive po referenci iz okruzenja
	“[&, a, b]” //znači “zarobi sve po referenci, osim promjenljivih “a” i “b” koje se zarobljavaju po vrijednosti”, te
	“[=, &a, &b]” //znači “zarobi sve po vrijednosti, osim promjenljivih “a” i “b” koje se zarobljavaju po referenci”.

	#include <functional>
	tabeliraj(std::function<int(int)> f, int x_min, int x_max) {
	 for(int x = x_min; x <= x_max; x++)
	 std::cout << std::setw(10) << x << std::setw(10) << f(x) << std::endl;
	}



	std::function<int(int)> Kompozicija(std::function<int(int)> f,
	 std::function<int(int)> g) {
	 return [f, g](int x) { return g(f(x)); };
	}


	std::function<double(double)> AproksimacijaIzvoda(
	 double f(double), double eps = 1e-5) {
	 return [f, eps](double x) { return (f(x + eps) – f(x)) / eps; };
	}



	#include <utility>
	std::pair<double, double> tacka_u_ravni, par_brojeva;
	tacka_u_ravni.first = 5.17; tacka_u_ravni.second = 2.5;
	tacka_u_ravni = std::make_pair(5.17, 2.5);
	get<0> i get<1> daju referencu na first ili second


	#include <map>
	std::map<std::string, int> stanovnistvo;
	stanovnistvo.insert({"Sarajevo", 450000});
	stanovnistvo.insert({"Banja Luka", 200000});
	stanovnistvo.insert({"Mostar", 85000});
	for(auto it = stanovnistvo.begin(); it != stanovnistvo.end(); it++) {
		std::cout << "Grad: " << it->first << " Broj stanovnika: " << it->second << std::endl;  	 //(*it).first
	}

	std::map<std::string, int> stanovnistvo{{"Sarajevo", 450000},
	 {"Banja Luka", 200000}, {"Mostar", 85000}};

	//prvo polje je kljucna vrijednost po kojoj se pretrazuje sve
	//drugo polje je prateca pridruzena vrijednost 	
	 std::cout << "Broj stanovnika " << stanovnistvo["Mostar"];

	auto it = stanovnistvo.find("Mostar");
	if(it == stanovnistvo.end()) std::cout << "Nema podataka!";
	else std::cout << "Broj stanovnika: " << it->second;

	stanovnistvo["Tuzla"] = 130000; //umjesto isnert moze ovo
	//ali ako nema polja tuzla, onda se to polje kreira u novom paru pa cak i kad koristim std::cout << stanovnistvo["Kifino Selo"]; bez dodjele sa =

	stanovnistvo.at("Mostar") //baca izuzetak ako ne postoji mostar
	//ako postoji polje sa isitm kljucnim poljem koje ubacujemo, onda ce se desiti overwrite i staro nece postojati a novo hoce
	//to se moze izbjeci koristenje multimapa u istoj biblioteci ali onda nema ["nesto"] ili koristiti .at ili find


	//ovdje imaju samo 4 para a ne 23398 kolko bi ih trebalo biti u nizu
	std::map<int, double> a;
	a[5] = 12.5; a[32] = 1.24; a[1149] = 0.712; a[23398] = 91;
	std::cout << a[5] << " " << a[32] << " " << a[1149] << " " << a[23398]; 

	//mape zahtijevaju da tip ključa bude tip koji podržava poređenje pomoću operatora “<”

	#include <unordered map> - unordered map i unordered multimap



	#include <tuple>
	std::tuple<int, int, std::string, double> t{3, 5, "pqr", 2.13};
	std::cout << std::get<0>(t) << " " << std::get<2>(t);  //ispise 3 pqr
	std::get<1>(t)++; std::get<3>(t) = 5.316;
	t = {12, 10, "abcde", 0}; // Ovo radi tek od C++17!
	t = std::make_tuple(12, 10, "abcde", 0); // Ali ovo je OK od C++11 nadalje

	//tie -Ona je slična funkciji “make_tuple”, ali kreira n-torku čija su polja reference na parametre funkcije
	int a = 1, b = 2, c = 3;
	auto t = std::tie(a, b, c); // Tip od t je std::tuple<int &, int &, int &>
	b = 4;
	std::cout << std::get<0>(t) << " " << std::get<1>(t)
	 << " " << std::get<2>(t) << std::endl; // Ispisuje 1 4 3!
	 //tie daje rezultat l-vrijednost pa je legalno:
	 std::tuple<int, int, int, int > t{1, 2, 3, 4};
	int a, b, c, d;
	std::tie(a, b, c, d) = t; // a = 1, b = 2, c = 3, d = 4


	#include <array>
	std::array<int, 5> niz;
	 niz[0] = 5; niz[1] = 3; niz[2] = 2; niz[3] = 4; niz[4] = 1;
	for(auto it = niz.begin(); it != niz.end(); it++) std::cout << *it << " ";
	niz.data(); //daje pokazivac na prvi element array tipa



	struct Cvor {
	 int element;
	 Cvor *veza;
	};
	for(Cvor *p = pocetak; p != nullptr; p = p->veza)
	 std::cout << p->element << std::endl;



	friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2); 
	//prijatelj funkcije ima pravo pristupa svim njenim atributima i metodama


	//const znaci da se parametri objekta nad kojim je pozvana metoda ne mogu promjeniti 
	//ovo se zove inspektror
	void Ocitaj (double &x, double &y, double &z) const
	    {
	        x = this->x;
	        y = this->y;
	        z = this->z;
	    }

	//parametri oznaceni sa mutable se mogu promjeniti u instektoru i samo oni
	mutable int brojIspisa = 0; 



	NekaFunkcija({12, 5, 2007})  //pozvat ce se default konstruktor nad objektom u {}
	NekaFunkcija(Datum{12, 5, 2007}) // moze i ovo ali obje konstrukcije neamju status l-vrijednosti


	dat = Datum(30, 4, 2004); // ovo sa desne strane ce se unistiti cim se iskori u dat


	//kopirajuci konstruktor koji se auto generate-a ako ga nismo napisali
	class Kompleksni {
	 …
	 Kompleksni(const Kompleksni &z) { re = z.re; im = z.im; }
	 …
	};

	Ukoliko
	iz bilo kojeg razloga želimo da zabranimo implicitno korištenje konstruktora sa jednim parametrom za
	automatsku pretvorbu tipova, tada ispred deklaracije odgovarajućeg konstruktora treba da navedemo
	ključnu riječ “explicit”. 

	//ovdje samo ne eksplicitne kosntrutkore
	Kompleksni a(5);
	Kompleksni a = 5;

	Kompleksni a = Kompleksni(5); //ovo poziva i eksplicitne konstruktore
	Kompleksni a(Kompleksni(5)); //i ovo


	Kompleksni a(Kompleksni(1, 2)); //moze bit exolicit copy konstruktor
	Kompleksni a = Kompleksni(1, 2); // ne smije biti explicit copy constructor

	//vektor datuma, drugi parametar je neophodan
	std::vector<Datum> vektor_datuma(1000, Datum(1, 1, 2000));
	vektor_datuma.resize(1500, Datum(1, 1, 2000));

	“emplace_back”, “emplace_front” i “emplace”  //umjesto push_bak, push_front i insert (efiaksnije samo za klase)

	Kompleksni niz[10] = {Kompleksni(4, 2), Kompleksni(3), 5}; //ostali ce biti inicializovani sa konstruktorom bez parametara

	new Datum(dan, mjesec, godina)// ako ovo padne, onda nece doci do cerenja memorije

	niz_datuma[i] = std::make_shared<Datum>(dan, mjesec, godina); //ovo radi nekako???



	//konstruktorska inicijalizaciona lista:

	class Student {
	 char ime_i_prezime[50];
	 const int indeks; // Konstantni atribut!
	 Datum datum_rodjenja;
	public:
	 Student(const char i_i_p[], int indeks, int d, int m, int g) :
	 datum_rodjenja(d, m, g), indeks(indeks) {
	 std::strcpy(ime_i_prezime, i_i_p);
	 }
	 ... // Ovdje bi trebalo definirati ostatak interfejsa klase
	};
	kada koristimo konstruktorske inicijalizacione liste, svi atributi pomenuti u
	listi se inicijalizirajun onim redoslijedom kako su deklarirani unutar klase





	inicijalizacija putem konstruktorske inicijalizacione liste ujedno i jedini način
	da se postavi dimenzija atributa tipa “vector” odmah pri stvaranju objekta (tj. bez potrebe da mu u
	tijelu konstruktora postavljamo veličinu pomoću “resize” funkcije).

	class KlasaSa4Vektora {
	 std::vector<int> v1, v2, v3, v4;
	public:
	 KlasaSa4Vektora() : v1(10), v2{10}, v3(5, 3), v4{5, 3} {}
	 … // Ostatak klase
	};


	class KlasaSa4Vektora {
	 std::vector<int> v1(10), v2{10}, v3(5, 3), v4{5, 3}; // OVO NE RADI!
	public:
	 … // Ostatak klase
	};


	 ukoliko se konstruktor implementira izvan deklaracije klase (što svakako treba
	raditi kad god je konstruktor iole složeniji) tada se konstruktorska inicijalizaciona lista navodi tek
	prilikom implementacije konstruktora, a ne prilikom navođenja njegovog prototipa.



	class VektorNd {
		//destruktori imaju tilda ispred imena i zovu se kao konstruktori (po imenu klase)
	 ~VektorNd() { delete[] koordinate; } // umjesto OslobodiMemoriju
	};
	//Oni se automatski pozivaju kad objekat dodje do kraja } ili kad se udje u catch blok. 
	//Ako je kreiranje bacilo izuzaetak onda ce se izbrisati samo oni objekti koji su se uspjesno alocirali
	Bitno je napomenuti da bacanje izuzetaka iz destruktora treba izbjegavati po svaku cijenu (srećom,
	ovo je rijetko potrebno).

	kad god parametar konstruktora sa jednim
	parametrom ne služi za inicijalizaciju vrijednosti objekta nego za definiranje interne strukture objekta
	(kao u ovom primjeru), takav konstruktor bi trebao biti eksplicitni konstruktor.

	 VektorNd(	 lista);

	 class VektorNd {

	 	VektorNd(std::initializer_list<double> lista):
	 		dimenzija(lista.size()), koordinate(new double[lista.size()]) {
	 		std::copy(lista.begin(), lista.end(), koordinate); 
	 		} // inicijalizaciona lista koja omugucava inici. pomocu {}
	 	double *begin() const { return koordinate; }//begin i ned da bi se podrzala rasponska for petlja
	 	double *end() const { return koordinate + dimenzija; }
	};


	 kao pravilo može uzeti da svaka klasa koja
	posjeduje vlastiti destruktor (tj. onaj koji nije automatski generiran), gotovo uvijek mora posjedovati i
	vlastiti kopirajući konstruktor i vlastiti operator dodjele. 


	//move konstruktor koji samo prekopira ili dodjeli vrijednosti objektu a 
	//original unisti jer ce svakako original biti unisten npr. nailaskom na }
	class VektorNd {
	 …
	 VektorNd(VektorNd &&v) : dimenzija(v.dimenzija),
	 koordinate(v.koordinate) { v.koordinate = nullptr; }
	 …
	};

	VektorNd b = std::move(a); // ovo je legal ako ima move constructor
	Sve što funkcija “move” radi je da vrati svoj argument kao rezultat, ali sa izmijenjenim statusom tako da
	se tretira kao r-vrijednost (tačnije, ona vraća r-vrijednosnu referencu na svoj argument). 

	b = a;
	c = ZbirVektora(a, b); //ovdje se nece izvrsiti kopirajuci konstrukjtor koji ce napraviti duboke kopije
	//jer ove varijable postoje od ranije pa se nad njima ne moze primjeniti konstruktor tako da se desava plitka kopija
	//i curenje memorije jer vise niko ne pokazuje na ono na sta je pokazivo b

	 izraz oblika “b = a” zapravo se interpretira kao izraz “b.operator =(a)”,  odnosno kao poziv jedne 
	 specijalne funkcije članice čije je ime “operator =” nad
	objektom “b” (razmak između ključne riječi “operator” i znaka “=” nije obavezan). 




	class VektorNd {
	 …
	 VektorNd &operator =(const VektorNd &v); // Kopirajuća verzija
	 VektorNd &operator =(VektorNd &&v); // Pomjerajuća verzija
	 …
	};

	// Kopirajuća verzija
	VektorNd &VektorNd::operator =(const VektorNd &v) {
	 if(&v != this) { // Samododjela? // provjerava da li je funkciaj pozvana nad istim objektom npr a=a
	 								// (ili v[i] = v[j] kad god je i == k ili *p = *q ako pokazuju na istu varablu) 
	 								//jer da jeste onda bi bez ovog
	 								// to bilo destruktivna samododjela (engl. destructive self-assignment). 
	 	delete[] koordinate;
	 	dimenzija = v.dimenzija; koordinate = new double[dimenzija];
	 	std::copy(v.koordinate, v.koordinate + v.dimenzija, koordinate);
	 }
	 return *this; //vraca se referenca na pozvani objekat da bi se moglo a = b = c = d = e; (a.operator =(b.operator =(c)...);)
	}

	//2. verzija koja prvo zauzima prostor pa onda brise zbog moguceg bacanja izuzetka
	//ovdje nije ni potrebna provjera samododjele jer bi presipali iz supjeg u prazno
	VektorNd &VektorNd::operator =(const VektorNd &v) {
	 double *novi_prostor = new double[v.dimenzija];
	 std::copy(v.koordinate, v.koordinate + v.dimenzija, novi_prostor);
	 delete[] koordinate;
	 dimenzija = v.dimenzija; koordinate = novi_prostor;
	 return *this;
	}



	//a=b
	//3. verzija koja primma kopiju dodjelujuceg objekta b i vrsi swap a i v pri cemu se v unisti  
	//i time unisti vrijednosti koje je a imao (copy & swap tehnika) ali ovo nije bas najefikasnije
	VektorNd &VektorNd::operator =(VektorNd v) {
	 	std::swap(dimenzija. v.dimenzija); std::swap(koordinate, v.koordinate);
	 	return *this;
	}



	//4. verzija koja gleda mozel se kopirat bez unistavanja
	VektorNd &VektorNd::operator =(const VektorNd &v) {
	 if(dimenzija < v.dimenzija) {
	 	double *novi_prostor = new double[v.dimenzija]; // Realokacija...
	 	delete[] koordinate; koordinate = novi_prostor;
	 }
	 dimenzija = v.dimenzija;
	 std::copy(v.koordinate, v.koordinate + v.dimenzija, koordinate);
	 return *this;
	}


	//pomjerajuce verzija operatora =
	VektorNd &VektorNd::operator =(VektorNd &&v) {
	 if(&v != this) { // Samododjela? zbog a = std::move(a)”
	 delete[] koordinate; koordinate = v.koordinate;
	 dimenzija = v.dimenzija; v.koordinate = nullptr;
	 }
	 return *this;
	}
	c = ZbirVektora(a, b)//ovo je sad efikasnije
	b = std::move(a) //ovo je sad legalno

	//2. efikasnija verzija pomjerajuce verzije sa copy and swap
	//ali ako je copy operator izveden na ovaj nacin onda se move operator ne smije implementirati (ispod je razlog)
	VektorNd &VektorNd::operator =(VektorNd &&v) {
	 std::swap(dimenzija. v.dimenzija); std::swap(koordinate, v.koordinate);
	 return *this;
	}

	//ovdje bi nastao konflikt jer oba operatora mogu primit v pa se ne zna koji treba uzeti u slucaju a = b
	class VektorNd {
	 …
	 VektorNd &operator =(VektorNd v); // Kopiraj-i-dodijeli verzija
	 VektorNd &operator =(VektorNd &&v); // Pomjerajuća verzija pravi konflikt?
	 …
	};

	//NAPOMENA: da smo umjesto poakzivaca na dinamicki alocirani niz koordinata koristili vector, svi ovi konstruktori, 
	//destruktori i operatori = bi postali bespotrebni so there's that for ya



	Ako funkciji sort prosijedimo funkciju clanicu, ta funkcija mora biti static jer da nije static onda bi se morala promijeniti nad 
	konkretnim objektom za sta funkcija sort ne bi mogla znati



	double Fun(int x) = delete; //zabrana ove permutacije funkcije, radi i za konstruktore i funk clanice
	“Razred() = default; // automatski generirano konstruktor

	ako mi definiramo ma kakav vlastiti konstruktor (pa čak i kopirajući), kompajler ne generira
	automatski konstruktor bez parametara (sa praznim tijelom)






	template <typename TipEl>
	 class Matrica {
	 int br_redova, br_kolona;
	 TipEl **elementi;
	 char ime_matrice;
	 static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	 static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	 void KopirajElemente(TipEl **elementi);

	public:
	 Matrica(int br_redova, int br_kolona, char ime = 0); //nije potrebno navoditi tip jer se podrazumijeva ako je u klasi izveden
	 Matrica(const Matrica &m);
	 Matrica(Matrica &&m);
	 ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
	 Matrica &operator =(const Matrica &m);
	 Matrica &operator =(Matrica &&m);
	 void Unesi();
	 void Ispisi(int sirina_ispisa) const;

	 template <typename Tip2> //OVO SE MORA PISATI AKO KLASA SADRZI GENERICKU FUNKCIJU CLANICU
	 friend Matrica<Tip2> ZbirMatrica(const Matrica<Tip2> &m1,

	 const Matrica<Tip2> &m2);
	 };


	//ako je van klase implementacija onda se mora navestio typename hepek
	 template <typename TipEl>
	 Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
	 br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
	 elementi(AlocirajMemoriju(br_redova, br_kolona)) {}




	//Ovdje zbirMatrica nije genericka funkcija nego ce se stvoriti nova funkcija za svaku instantaciju klase Matrica
	 //Drugi problem je sto ovako nije ostvareno prijateljstvo ma bilo koje instantacije klase Matrica i ma bilo koje instantacije
	 	//	funkcije ZbirMatrica
	template <typename TipEl>
	 class Matrica {
	 …
	 friend Matrica ZbirMatrica(const Matrica &m1, const Matrica &m2) {
	… // Ovdje ide implementacija funkcije ZbirMatrica
	 }
	 …
	};


	//uvjek barem 1 tip mora bit user defined aka klasa, enum, struct
	//preklapanje operatora +
	Vektor3d operator +(const Vektor3d &v1, const Vektor3d &v2) {
	 return {v1.DajX() + v2.DajX(), v1.DajY() + v2.DajY(), v1.DajZ() + v2.DajZ()};
	}

	//poziv
	c = operator +(a, b);
	c = a + b;
	//Skoro uvek se operatori deklariraju kao friend functions

	//operatori nisu asocijativni tj d * v nije isto sto i v * d unless we make it same:
	inline Vektor3d operator *(const Vektor3d &v, double d) {
	 return d * v;
	}




	Vektor3d &operator +=(Vektor3d &v1, const Vektor3d &v2) {
	 v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
	 return v1;
	}
	//operator + treba realizirati preko += jer je efikasnije
	inline Vektor3d operator +(Vektor3d v1, const Vektor3d &v2) {
	 return v1 += v2;
	}



	 bool operator ==(const Vektor3d &v1, const Vektor3d &v2) {
	 return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	inline bool operator !=(const Vektor3d &v1, const Vektor3d &v2) {
	 return !(v1 == v2);
	}



	izraz “std::cout << v” interpretira kao
	“operator <<(std::cout, v)”. Ukoliko se sjetimo da objekat “cout” nije ništa drugo nego jedna instanca
	klase “ostream”
	//klasa ostream se ne moze kopirati u funk tj prenositi po vrijednosti

	//operator << mora vratit sam objekat cout zbog ulancanog pozivanja cout << a << b << c
	std::ostream &operator <<(std::ostream &tok, const Vektor3d &v) {
	 tok << "{" << v.x << "," << v.y << "," << v.z << "}";
	 return tok;
	}

	//v mora bit referenca jer mu se sadrzaj mora izmijeniti
	std::istream &operator >>(std::istream &tok, Vektor3d &v) {
	 return tok >> v.x >> v.y >> v.z;
	}

	std::istream &operator >>(std::istream &tok, Kompleksni &a) {
	 char znak;
	 tok >> std::ws; // "Progutaj" razmake...
	 if(tok.peek() != '(') {
	 	tok >> a.re;
	 	a.im = 0;
	 }
	 else {
	 	tok >> znak >> a.re >> znak;
	 	//postavljanje u neispravno stanje
	 	//“ios::failbit” je konstanta pobrojanog tipa definirana unutar klase “ios” u biblioteci “iostream”)
	 	if(znak != ',') tok.setstate(std::ios::failbit);
	 	tok >> a.im >> znak;
	 	if(znak != ')') tok.setstate(std::ios::failbit);
	 }
	 return tok;
	}


	U slučaju da je moguće
	izvršiti više različitih pretvorbi, prvo se probavaju prirodnije pretvorbe (npr. ugrađene pretvorbe
	smatraju se prirodnijim od korisnički definiranih pretvorbi, kao što se i pretvorbe između jednog u
	drugi cjelobrojni tip smatraju prirodnijim od pretvorbe nekog cjelobrojnog u neki realni tip). Npr. operator * 
	sa 2 verzije vektor i double, vektor i vektor. poziv vektor * 3 ce pozvati vektor i dobule jer se int(3) prirodnije
	moze convert u tip doube



	//prefix ++ mora vratit l-vrijednost
	Vektor3d &operator ++(Vektor3d &v) {
	 double faktor = 1 + 1 / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	 v.x *= faktor; v.y *= faktor; v.z *= faktor;
	 return v;
	}


	//postfix ++
	izrazi poput “a++” gdje je “a” neki korisnički
	definirani tip podataka interpretiraju kao “operator ++(a, 0)”. Drugim riječima, postfiksni operatori
	“++” i “––” tretiraju se tehnički kao binarni operatori, ali čiji je drugi operand uvijek cijeli broj “0”.
	Drugim riječima, postfiksni operatori
	“++” i “––” tretiraju se tehnički kao binarni operatori, ali čiji je drugi operand uvijek cijeli broj “0”. Stoga
	odgovarajuća operatorska funkcija uvijek dobija nulu kao drugi parametar (zapravo, ona teoretski
	može dobiti i neku drugu vrijednost kao parametar, ali jedino ukoliko operatorsku funkciju eksplicitno
	pozovemo kao funkciju, recimo konstrukcijom poput “operator ++(a, 5)”, što se gotovo nikada ne
	čini)


	//ne smijemo vratit referencu
	Vektor3d operator ++(Vektor3d &v, int) {
	 Vektor3d pomocni = v;
	 double faktor = 1 + 1 / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	 v.x *= faktor; v.y *= faktor; v.z *= faktor;
	 return pomocni;
	} 
	//moze i pomocu prefix ++ se realizirati	
	Vektor3d operator ++(Vektor3d &v, int) {
	 Vektor3d pomocni = v;
	 ++v; // Pozivanje prefiksne verzije...
	 return pomocni;
	}




	enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};
	Dani &operator ++(Dani &d) {
	 return d = Dani((int(d) + 1) % 7); //int(d) je neophodne jer d + n bi se shvatio kao rekurzivni poziv
	}
	Dani operator ++(Dani &d, int) {
	 Dani pomocni = d; ++d; return pomocni;
	}
	Dani operator +(Dani d, int n) { // d nije referenca jer je male velicine pa je brze iskopirat nego kreirat referencu
	 return Dani((int(d) + n) % 7);
	}



	//operatorske funkcije smo mogli i implementirati kao funkcije clanice koje bi se primjenjivale nad objektom npr. x.operator ++(0)
	//ali tada izraz 3 + k bi se iterprirao kao 3.operator+(k) sto je illegal jer 3 nije klasa




	+, -, *, /, %,<, <=, >, >=, ==, !=, &, ^, |, && i || //ove kao prijateljsku funkciju
	=, +=, –=, *=, /=, %=, &=, ^=, |=, <<=, >>= //ove kao clanicu jer mijenjaju svoj levi parametar
	<<, >> //ove se moraju kao friend 
	[], ()//obavezno kao clanicu

	Vektor3d &Vektor3d::operator +=(const Vektor3d &v) {
	 x += v.x; y += v.y; z += v.z;
	 return *this;
	}

	inline Vektor3d operator +(const Vektor3d &v1, const Vektor3d &v2) {
	 return Vektor3d(v1) += v2;
	}	


	//Klase koje definiraju operator “()” nazivaju se funkcijske klase (ponekad i funktorske klase).
	class KvadratnaFunkcija {
	 double a, b, c;
	public:
	 KvadratnaFunkcija(double a, double b, double c) : a(a), b(b), c(c) {}
	 double operator ()(double x) const { return a * x * x + b * x + c; }
	};

	KvadratnaFunkcija kvf1(3, 5, 4), kvf2(1, 0, -6);
	std::cout << kvf1(-2) << " " << kvf2(7) << std::endl; 

	//polinom class
	double operator [](int indeks) const {
	 TestIndeksa(indeks); return koeficijenti[indeks];
	 }

	/*Funkcijski objekti nisu funkcije, mada se po nekim aspektima ponašaju poput funkcija. Stoga nije
	moguće pokazivaču na funkcije dodijeliti funkcijski objekat, niti njegovu adresu. Za to sluze 
	polimorfnim funkcijskim omotačima (definiranim u biblioteci “functional”) */
	 za prethodno definirane funkcijske objekte “kvf1” i
	“kvf2” (koji su tipa “KvadratnaFunkcija”) te funkcijske objekte “poli1” i “poli2” (tipa “Polinom”),
	sasvim je legalno pisati nešto poput sljedećeg:

	std::function<double(double)> pfo1, pfo2, pfo3, pfo4;
	pfo1 = kvf1; pfo2 = kfv2; pfo3 = poli1; pfo4 = poli2;
	std::cout << pfo1(-2) << " " << pfo2(7) << " "
	 << pfo3(2) << " " << pfo4(–1) << std::endl;

	 //Operator [] prima iskljucivo 1 parametar dok operator () moze primati proizvodljan broj parametara


	 /*Funktori su naročito korisni za realizaciju objekata koji se ponašaju kao funkcije koje pamte stanje
	svog izvršavanja. Recimo, neka je potrebno definirati funkciju “KumulativnaSuma” sa jednim parametrom
	koja vraća kao rezultat ukupnu sumu svih dotada zadanih vrijednosti njenih stvarnih argumenata. */

	int KumulativnaSuma(int n) {
	 static int suma = 0; // Važno: statička promjenljiva!
	 return suma += n; //problem je kako resetovat vrijednost bez prljavih trikova 
	}

	//ovo je bolje rjesenje i objekti tipa ove klase mogu cuvati svoju sumu nezavisno od ostalih
	class Akumulator {
	 int suma;
	public:
	 Akumulator() : suma(0) {}
	 void Resetiraj() { suma = 0; }
	 int operator ()(int n) { return suma += n; }
	};




	/*Sve funkcije iz standardne biblioteke “algorithm”, koje kao parametre prihvataju funkcije, također
	prihvataju i funktore odgovarajućeg tipa, što omogućava znatno veću fleksibilnost. Također, biblioteka
	“functional” između ostalog sadrži i nekoliko jednostavnih funkcijskih klasa (definiranih u imeniku
	“std”, poput svih drugih stvari definiranih u standardnim bibliotekama), pomoću kojih se mogu lako
	kreirati funkcijski objekti koji obavljaju neke česte i uobičajene operacije. */
	//nesto kao ovo
	template <typename UporediviTip>
	 struct greater {
	 bool operator ()(UporediviTip x, UporediviTip y) { return x > y; }
	 };
	//pa mogu deklarisat ovo (iznad je samo kako bi izgledalo ovo jer greater je u std biblioteci)
	 // ovako se interpretira (beksorisno al et) std::greater<int>().operator()(x, y)”).
	 std::greater<int> veci;  
	 std::sort(niz, niz + 100, std::greater<double>()); 

	 Pored generičke funkcijske klase greater, definirane su i generičke funkcijske klase “less”,
	“equal_to”, “not_equal_to”, “greater_equal” i “less_equal”, koje respektivno odgovaraju relacionim
	operatorima “<”,“==”,“!=”,“>=” i “<=”, zatim generičke funkcijske klase “plus”, “minus”, “multiplies”,
	“divides”, “modulus”, “logical_and” i “logical_or”, koje odgovaraju binarnim operatorima “+”, “–”,
	“*”, “/”, “%”, “&&” i “||”, i konačno, generičke funkcijske klase “negate” i “logical_not” koje odgovaraju
	unarnim operatorima “–” i “!” Kao primjer primjene ovih funkcijskih klasa, navedimo da naredba
		std::transform(niz1, niz1 + 10, niz2, niz3, std::multiplies<int>());
	prepisuje u niz “niz3” produkte odgovarajućih elemenata iz nizova “niz1” i “niz2” (pretpostavljajući
	da su sva tri niza nizovi od 10 cijelih brojeva), bez ikakve potrebe da definiramo odgovarajuću funkciju 





	Lambda fukcije nisu ništa drugo nego vrsta
	funkcijskih objekata, koje kompajler automatski kreira, tako da za svaku lambda funkciju upotrijebljenu
	u programu, kompajler generira po jednu pomoćnu funkcijsku klasu (čije ime kompajler automatski
	generira), čiji su atributi vrijednosti zarobljenih promjeljivih, a čije tijelo predstavlja tijelo operatorske
	funkcije za operator “()” u toj klasi.

	std::cout << std::count_if(niz, niz + 100, [n](int x) { return x < n; });
	//compiler automatski kreira:
	class PomocnaFunkcijskaKlasa {
	 const int n; // Zarobljena vrijednost iz okruženja
	public:
	 PomocnaFunkcijskaKlasa(int n) : n(n) {}
	 bool operator ()(int x) { return x < n; }
	};
	//pa se ovo prevede u
	std::cout << std::count_if(niz, niz + 100, PomocnaFunkcijskaKlasa(n));

	Slična stvar se dešava i pri zarobljavanju po referenci, samo što su tada odgovarajući atributi reference
	na promjenljive zarobljene iz okruženja, a ne njihove kopije. Ovim ujedno postaje posve jasno zbog čega
	se lambda funkcije koje zarobljavaju promjenljive iz svog okruženja ne mogu dodjeljivati pokazivačima
	na funkcije, nego samo polimorfnim funkcijskim omotačima.






	/*Funkcija “bind1st” prima dva
	parametra, nazovimo ih f i x0, pri čemu je f funktor koji prima dva parametra (nazovimo ih x i y). Ova
	funkcija vraća kao rezultat novi funktor (nazovimo ga g) koji prima samo jedan parametar (nazovimo
	ga y) takav da vrijedi g(y) = f(x0, y). Na primjer, ako je “f” neki konkretan funktor, izraz poput
	“std::bind1st(f, 5)(y)” ima isto dejstvo kao izraz “f(5, y)”.*/

	/*Slično, funkcija “bind2nd” prima dva
	parametra f i yo, i vraća kao rezultat novi funktor (nazovimo ga g) takav da vrijedi g(x) =f (x, y0),
	odnosno izraz poput “std::bind2nd(f, 5)(x)” ima isto dejstvo kao izraz “f(x, 5)”. */

	//ove dvije funkcije su izbacne u c++17 jer su traljave

	std::cout << std::count_if(niz, niz + 100, std::bind2nd(std::less<int>(), n));

	/*Naime, poziv “std::less<int>()” kreira funktor (nazovimo ga f) takav da f(x, y) ima vrijednost “true”
	ako i samo ako je x < y. Stoga će izraz “std::bind2nd(std::less<int>(), n)” kreirati novi funktor
	(nazovimo ga g) takav da je g(x) =f(x,n) pri čemu je vrijednost promjenljive “n”, odnosno g(x) ima
	vrijednost “true” ako i samo ako je x<n. Tako kreirani funktor prosljeđuje se funkciji “count if” kao
	kriterij, a dalje se sve dešava u skladu sa poznatim dejstvom funkcije “count if”.*/


	//nova funk uvedena u c++11
	std::bind( f, x0, std::placeholders::_1) 		umjesto std::bind1st(f, x0)
	std::bind( f, std::placeholders::_1, ) 			umjesto std::bind2nd(f, y0)
	//funkcije poput “bind1st”, “bind2nd” i “bind” nazivaju se veznici (engl. binders)
	std::cout << std::count_if(niz, niz + 100,
	 std::bind(std::less<int>(), std::placeholders::_1, n));

	/*funkcija “bind” kao svoj prvi parametar prima neku
	funkciju (nazovimo je f ) ili funktor, a nakon toga može imati proizvoljan broj parametara. Neki od tih
	parametara mogu biti posebni objekti nazvani držači (engl. placeholders) koji imaju specijalna imena
	poput “placeholders::_1” (prvi držač), “placeholders::_2” (drugi držač), itd. Kao rezultat funkcija
	“bind” vraća novi funkcijski objekat (nazovimo ga g) koji kad se pozove sa nekim argumentima, daje
	isti rezultat kao kada se funkciji (ili funktoru) f proslijede preostali parametri (osim prvog) navedeni u
	pozivu funkcije “bind”, ali uz zamjenu prvog držača sa prvim argumentom funktora g, drugog držača sa
	drugim argumentom funktora g, itd. */

	/*Na primjer, ukoliko je “f” neka funkcija (ili funktor) koja prima
	argumenata, tada poziv*/

	std::bind(f, 3, std::placeholders::_1, std::placeholders::_2, 4, 6, std::placeholders::_1, 0)

	/*daje kao rezultat novi funktor (nazovimo ga “g”) koji prima dva argumenta, takav da poziv “g(x, y)”
	daje isti rezultat kao i poziv “f(3, x, y, 4, 6, x, 0)”.*/


	 //operator ->

	 S obzirom da drugi parametar operatora “->” ne može biti bilo šta nego isključivo ime
	nekog atributa ili metode, izraz oblika “x->y” u slučaju kada je “x” primjerak neke klase ne interpretira se
	kao “x.operator->(y)”, nego kao “(x.operator->())->y”. Dakle, operatorska funkcija “operator ->”
	ne smije imati parametre i kao rezultat mora vratiti nešto na šta se također može primijeniti operator
	“->”.


	//new delete
	 Doduše, puna je istina da se operatori “new” i “delete” mogu preklopiti samo
	“djelimično”. Konkretno, oba ova operatora obavljaju dvoetapne procese: “new” vrši alokaciju memorije za
	potrebe objekta te poziv konstruktora nad novostvorenim objektom, dok “delete” vrši poziv destruktora
	nad objektom koji se uništava, te dealokaciju memorije koju je zauzimao objekat. Preklapanjem je
	moguće utjecati jedino na sam postupak alokacije i dealokacije, dok je poziv konstruktora odnosno
	destruktora “nepromjenljivi” dio ovih operatora. 


	//konverzija iz tip2 u tip1 ako je tip2 npr “double”
	Da bi se mogao definirati i postupak konverzije u proste ugrađene tipove, uvode se operatorske funkcije za
	konverziju tipa. One se isto pišu kao funkcije članice neke klase, a omogućavaju pretvorbu objekata te
	klase u bilo koji drugi tip, koji ne mora biti (i obično nije) klasa. Kod njih se ime tipa u koji se vrši
	pretvorba piše iza ključne riječi “operator”, a povratni tip funkcije se ne navodi, nego se podrazumijeva
	da on mora biti tačno onog tipa kao tip u koji se vrši pretvorba. Pored toga, operatorske funkcije za
	konverziju tipa nemaju parametre

	Slijedi primjer kako bismo mogli deklarirati i implementirati
	operatorsku funkciju za pretvorbu tipa “VektorNd” u tip “double” i obrnuto

	class VektorNd {
	 …
	 operator double() const;
	};
	VektorNd::operator double() const {
	 double suma = 0;
	 for(int i = 0; i < dimenzija; i++) suma += koordinate[i] * koordinate[i];
	 return std::sqrt(suma);
	}

	//sada se vektorNd moze convertovat u double
	std::cout << (double)v;
	std::cout << double(v);
	std::cout << static_cast<double>(v);
	d = v; // Skriveno d = double(v)
	std::cout << std::sin(v); // Skriveno std::sin(double(v))

	//previse ovih funkcija moze zbuniti compiler kada da koristi jednu a kad drugu

	na primjer, da su “Tip1” i “Tip2” dva tipa, i da je definirana konverzija iz tipa “Tip1” u tip “Tip2”, kao i
	konverzija iz tipa “Tip2” u tip “Tip1” (nebitno je da li su ove konverzije ostvarene konstruktorom ili
	operatorskim funkcijama za konverziju tipa). Pretpostavimo dalje da su za objekte tipova “Tip1” i “Tip2”
	definirani operatori za sabiranje. Postavlja se pitanje kako treba interpretirati izraz oblika “x + y” gdje
	je “x” tipa “Tip1” a “y” tipa “Tip2” (ili obrnuto). Da li treba objekat “x” pretvoriti u objekat tipa “Tip2”
	pa obaviti sabiranje objekata tipa “Tip2”, ili treba objekat “y” pretvoriti u objekat tipa “Tip1” pa obaviti
	sabiranje objekata tipa “Tip1”? Kompajler nema načina da razriješi ovu dilemu, tako da će biti prijavljena
	greška. U ovom slučaju bismo morali eksplicitno naglasiti šta želimo izrazima poput “x + Tip1(y)” ili “Tip2(x) + y”


	ove pretvorbe mozemo stavit da su explicit pa da se ne pozivaju autoamtski, osim za tip bool gdje ce se iskoristit
	iako ja explicit samo i samo u if i while uvjetima i nigdje drugo.
	 To je iskorišteno recimo kod pametnih pokazivača da se omogući da se oni mogu koristiti kao uvjeti u
	  naredbama “if” i “while” (sa značenjem da li su nulpokazivači ili ne), ali da se ne mogu koristiti kao 
	  logičke promjenljive u drugim kontekstima.




class DiplomiraniStudent : public Student {
 int godina_diplomiranja;
public:
 DiplomiraniStudent(std::string ime, int ind, int god_dipl) :
 Student(ime, ind), godina_diplomiranja(god_dipl) {}
 int DajGodinuDiplomiranja() const { return godina_diplomiranja; }
}; //kobstruktori se niakd ne naslijedjuju a ni pretvorba tipova sa konstruktorima sa 1 parametrom
//a ni prijateljske funkcije te operator dodjele =
//Važno je naglasiti da atributi i metode koji su privatni u baznoj klasi nisu dostupni čak ni metodama
//klase koja je iz nje nasljeđena
class Student {
protected: //sve klase koje naslijede ovu klasu imaju pravo pristupa ovim atributima sto inace nije moguce ako su private	
 std::string ime;
 int indeks;
public:
};

//sve objekte istog tipa koje primamo u metodu ili privremene variable istog ili nekog drugog tipa,
//nemozemo im pristupiti atributima koji su im protected iako je mozda rijec o  objektu istog tipa

s2.Student::Ispisi(); //poziv bazne metode ispisi ako postoji nova metoda ispisi 
Student::Ispisi(); //ako pozivamo u metodi
Ako imamo istoimenu metodu u izvedenoj klasi, sve takve metode neovisne o borju parametara postaju nevidljive
osim ako ne kosistimo Bazna::metoda

Ako hocemo da preuzmemo sve metode i da ih po zelji preklopimo onda pishemo
using BaznaKlasa::Metoda

Ako imamo istoimene atribute ona koristimo BaznaKlasa::x za pristup baznom

class C : public A, public B { //ako vise klasa je baza
 …
};
moguce je izvedenu klasu kopirati, dodjeliti i vratiti na majestu gdje se ocekuje bazna stim da se tada kopiraju samo
atributi bazne klase

da bi pretvorili baznu klasu i izvedenu moramo definirati konstruktor u izvedenoj ili operator izvedene u baznoj klasi
ili u izv klasi kopirajuci operator dodjele = koji prima baznu klasu kao parametar

ako je bazna klasa naslijedjena kao private ili potected tada izvedena klasa nenma pristup nicemu ?

pokazivacu an baznu klasi mezemo dodeliti adresu izvedene klase (samo za public izvodjenje) tj
podržana je automatska pretvorba pokazivača na objekte izvedene klase u pokazivače na obične klase.(upcasting)
Staticki pok na obj je tipa kojeg je deklariran 
Dinamicki pok je tipa onog na sta pokazuje 

Early binding je kada compiler pri kreiranju masinskog koda zakljuci kojeg ce tipa biti pokazivaci i u skladu
s tim poziva metode iz te klase
Late binding je kada se tip pokazivaca oderedi u toku izvrsavanja programa i tak ose odredi kojoj klasi pripada
Da bismo ostvarili kasno povezivanje, ispred deklaracije metode na koju želimo da se primjenjuje
kasno povezivanje treba dodati ključnu riječ “virtual”.

Bitno je naglasiti da se ključna riječ “virtual” piše samo unutar deklaracije klase, tako da u slučaju da
virtualnu metodu implementiramo izvan deklaracije klase, ključnu riječ “virtual” ne trebamo (i ne
smijemo) ponavljati na mjestu implementacije.

class Student {
 … // Sve ostalo ostaje isto
 virtual void Ispisi() const {
 std::cout << "Student " << ime << " ima indeks " << indeks;
 }
};

kad god imamo potrebu da u izvedenoj klasi mijenjamo neku funkciju iz bazne klase, to je
skoro siguran znak da bi ta funkcija u baznoj klasi trebala biti virtualna



 //Kada god želimo neku funkciju u izvedenoj klasi izmijeniti (zadržavajući joj isto zaglavlje) koristimo override
class DiplomiraniStudent : public Student {
 … // Sve ostalo ostaje isto
 void Ispisi() const override {

 … // Definicija funkcije ostaje ista
 }
};
. Prvo, kompajler će nam prijaviti grešku ukoliko odgovarajuća funkcija u
baznoj klasi ne postoji ili ukoliko nije deklarirana kao virtualna. Drugo, grešku ćemo dobiti i ukoliko u
baznoj klasi postoji takva funkcija, ali nema isto zaglavlje u odnosu na funkciju koju definiramo u
izvedenoj klasi (npr. razlikuje se broj ili tip parametara). ili zaboravimo const

Sve sto vredi za pokazivace vredi i za reference

void NekaFunkcija(const Student &s) {
 s.Ispisi();
}

Ako posaljem diploranog studenta, pozvat ce se isipisi u klasi diplomirani ako je ta metoda virtualna else nece.
Ako je s ne reference tj obicni parametar, onda bi se pozvalo ispisi iz studenta bez obzira na to da li je virtual ili ne


Metodologija koja omogućava da se ista promjenljiva u različitim trenucima ponaša kao da ima različite
tipove, tako da poziv iste metode (tačnije, metode istog imena) nad istom promjenljivom u različitim
trenucima izaziva različite akcije naziva se polimorfizam. Samoreference i poakzivaci mogu bit polimofrni.


 polimorfna klasa je ona koja sadrži barem jednu virtualnu metodu

class Student {
 …

 virtual ~Student() {} // Virtualni destruktor...
 …// kada god želimo
//koristiti polimorfizam, bazna klasa mora imati virtualni destruktor, makar sa praznim tijelom
};

bez velike potrebe ne treba
kreirati klase naslijeđene iz standardnih bibliotečkih klasa, a i ako ih kreiramo, trebamo ih koristiti s
izuzetnim oprezom, izbjegavajući u potpunosti korištenje polimorfizma s njima
/*
Student *s = new DiplomiraniStudent("Miki Maus", 3412, 2004);
std::cout << s->DajGodinuDiplomiranja(); // NE RADI!!!
*/

Ukoliko nam je baš neophodno da nad pokazivačem koji je
deklariran da pokazuje na baznu klasu primijenimo neku metodu koja je definirana samo u naslijeđenoj
klasi, a sigurni smo da u posmatranom trenutku taj pokazivač zaista pokazuje na objekat izvedene klase
(odnosno, ukoliko smo sigurni da je u posmatranom trenutku njegov dinamički tip takav da poziv
željene metode ima smisla) možemo na pokazivač primijeniti eksplicitnu konverziju tipa u tip pokazivača
na izvedenu klasu pomoću operatora za pretvorbu tipa (type-casting operatora), a zatim na rezultat
pretvorbe primijeniti metodu koju želimo. Ovakva pretvorba (koja se za razliku od pretvorbe naviše ne
vrši automatski) naziva se pretvorba naniže (engl. downcasting).

std::cout << ((DiplomiraniStudent *)s)->DajGodinuDiplomiranja();


#include <typeinfo>
if(typeid(*s) == typeid(DiplomiraniStudent))
 std::cout << static_cast<DiplomiraniStudent *>(s)->DajGodinuDiplomiranja();
else
 std::cout << "Zalim, s ne pokazuje na diplomiranog studenta!";
ispravno određivanje dinamičkog tipa nekog izraza pomoću “typeid”
operatora zahtijeva da bazna klasa bude polimorfna (tj. da ima makar jednu virtualnu funkciju),
U suprotnom, ovaj operator će prosto dati informacije o odgovarajućem statičkom a ne dinamičkom
tipu. 




//vraca nullptr ako se ne moze pretvoriti dok za reference baca “bad_cast” jer nema null reference
if(DiplomiraniStudent *s1 = dynamic_cast<DiplomiraniStudent *>(s))
 s1->DajGodinuDiplomiranja();
else std::cout << "Zalim, s ne pokazuje na diplomiranog studenta!";
 Iz istih razloga, operator “dynamic_cast” uopće ne radi (daje sintaksnu grešku) ukoliko se pokuša
primijeniti na tipove koji nisu polimorfni, tj. čija bazna klasa ne sadrži virtualne funkcije.


umjesto konstrukcija poput “static_cast<Tip *>” i
“dynamic_cast<Tip *>”, pri radu sa pametnim pokazivačima koriste se konstrukcije vrlo sličnog izgleda
“std::static_pointer_cast<Tip>” odnosno “std::dynamic_pointer_cast<Tip>” jer ne radi obicni static i dynamic_cast
zbog tegnickih razloga

bazne klase koje služe samo
da bi druge klase bile izvedene iz njih u cilju omogućavanja polimorfizma nazivaju se apstraktne bazne klase.

U normalnim okolnostima, primjerci apstraktnih baznih klasa se nikada ne deklariraju (mada se
deklariraju pokazivači ili reference na takve bazne klase, ali se oni uvijek povezuju sa objektima koji
pripadaju nekoj od klasa koje su iz njih izvedeni)
//zabranjujemo koristenje ovih metoda kad napisemo = 0

 često se uvodi i formalna definicija apstraktne bazne klase kao klase koja
posjeduje barem jednu apstraktnu metodu, ili kako se to još često kaže, čisto virtualnu funkciju

class ApstraktniLik {
 ...
 virtual double DajObim() const = 0; // Apstraktna metoda
 virtual double DajPovrsinu() const = 0; // Apstraktna metoda
 …
};
Ovom oznakom govorimo da metoda vjerovatno neće biti implementirana niti unutar klase, niti
izvan klase, nego tek eventualno u nekoj od klasa koje nasljeđuju klasu “ApstraktniLik”. Samo virtualne
metode mogu biti apstraktne, s obzirom da se one pozivaju mehanizmom kasnog povezivanja (tako da
se zapravo nikada neće ni pozvati virtuelna metoda iz bazne klase, nego neka metoda iz neke od
naslijeđenih klasa, za koje pretpostavljamo da će biti implementirane)

final” na kraju zaglavlja oznacava da se cijela klasa ili neka virtualna metoda ne moze mejnjati u izvedenim klaasama
Moguće je i cijelu klasu proglasiti za konačnu (npr. “class Datum final”), čime se potpuno
zabranjuje nasljeđivanje iz takve klase. Mogućnost ovih zabrana uvedena je tek od C++11 nadalje.



class ApstrakntniLik { …
virtual ApstrakntniLik *DajKopiju() const = 0;
};
class Krug { …
ApstraktniLik *DajKopiju() const override { return new Krug(*this); };
};
class Pravougaonik { …
ApstraktniLik *DajKopiju() const override { return new Pravougaonik(*this); };
};

Na ovaj način smo realizirali polimorfno kopiranje

Virtualne funkcije se ne mogu umetati u kod (inline) jer se pokazivaci na te funkcije cuvaju u 
u jednom nizu (tabeli) pokazivača koji se zove tabela virtualnih metoda(TVM)) te je to sporije nego obicne funkcije



















