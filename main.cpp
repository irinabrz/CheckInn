#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

//---------------------------------------------
// Clasa Client
//---------------------------------------------
class Client {
private:
    string nume;
    string prenume;
    string telefon;

public:

    explicit Client(const string& n = "", const string& p = "", const string& t = "")
        : nume(n), prenume(p), telefon(t) {}
    Client(const Client& c)
        : nume(c.nume), prenume(c.prenume), telefon(c.telefon) {}

    Client& operator=(const Client& c) {
        if (this != &c) {
            nume = c.nume;
            prenume = c.prenume;
            telefon = c.telefon;
        }
        return *this;
    }


    ~Client() {}

    friend ostream& operator<<(ostream& out, const Client& c) {
        out << c.nume << " " << c.prenume << " (" << c.telefon << ")";
        return out;
    }
    bool telefonValid() const {
        for (char ch : telefon) if (!isdigit((unsigned char)ch)) return false;
        return !telefon.empty();
    }

    void schimbaTelefon(const string& t) { telefon = t; }
    string getNumeComplet() const { return nume + " " + prenume; }
    bool compara(const Client& c) const { return nume == c.nume && prenume == c.prenume; }
    string key() const { return nume + "|" + prenume; }
};

//---------------------------------------------
// Clasa Camera
//---------------------------------------------
class Camera {
private:
    int numar;
    int etaj;
    int paturi;
    bool ocupata;
    Client client;

public:

    explicit Camera(int nr = 0, int e = 0, int p = 1)
        : numar(nr), etaj(e), paturi(p), ocupata(false) {}

    Camera(const Camera& c)
        : numar(c.numar), etaj(c.etaj), paturi(c.paturi), ocupata(c.ocupata), client(c.client) {}

    Camera& operator=(const Camera& c) {
        if (this != &c) {
            numar = c.numar;
            etaj = c.etaj;
            paturi = c.paturi;
            ocupata = c.ocupata;
            client = c.client;
        }
        return *this;
    }

    ~Camera() {}

    friend ostream& operator<<(ostream& out, const Camera& c) {
        out << "Camera " << c.numar << " (etaj " << c.etaj << ", paturi " << c.paturi << ") ";
        if (c.ocupata)
            out << "Ocupata de " << c.client;
        else
            out << "Disponibila";
        return out;
    }

    bool esteDisponibila() const { return !ocupata; }

    bool rezerva(const Client& c){
        if (!ocupata) {
            client = c;
            ocupata = true;
            return true;
        }
        return false;
    }

    bool elibereaza() {
        if (ocupata) {
            ocupata = false;
            client = Client();
            return true;
        }
        return false;
    }

    string detaliiCamera() const {
        return "Camera " + to_string(numar) + ", etaj " + to_string(etaj) +
               ", paturi: " + to_string(paturi) + (ocupata ? " (ocupata)" : " (libera)");
    }

    int getNumarPaturi() const { return paturi; }
    int getEtaj() const { return etaj; }
    int getNumar() const { return numar; }
};

//---------------------------------------------
// Clasa Rezervare
//---------------------------------------------
class Rezervare {
private:
    Camera camera;
    Client client;
    string data;

public:
    explicit Rezervare(const Camera& cam = Camera(), const Client& c = Client(), const string& d = "")
        : camera(cam), client(c), data(d) {}

    Rezervare(const Rezervare& r)
        : camera(r.camera), client(r.client), data(r.data) {}


    Rezervare& operator=(const Rezervare& r) {
        if (this != &r) {
            camera = r.camera;
            client = r.client;
            data = r.data;
        }
        return *this;
    }

    ~Rezervare() {}

    friend ostream& operator<<(ostream& out, const Rezervare& r) {
        out << "Rezervare: Camera " << r.camera.getNumar()
            << " pentru " << r.client
            << " la data " << r.data;
        return out;
    }

    void afisareDetalii() const { cout << *this << endl; }

    bool verificaData(const string& d) const { return data == d; }
    const Client& getClient() const { return client; }
    int getNumarCamera() const { return camera.getNumar(); }
    string getData() const { return data; }
};

//---------------------------------------------
// Clasa Hotel
//---------------------------------------------
class Hotel {
private:
    string nume;
    string adresa;
    vector<Camera> camere;
    int getCameraIndexByNumber(int numar) const {
        for (size_t i = 0; i < camere.size(); ++i) {
            if (camere[i].getNumar() == numar) return (int)i;
        }
        return -1;
    }
public:

    explicit Hotel(const string& n = "", const string& a = "")
        : nume(n), adresa(a) {}


    Hotel(const Hotel& h)
        : nume(h.nume), adresa(h.adresa), camere(h.camere) {}

    Hotel& operator=(const Hotel& h) {
        if (this != &h) {
            nume = h.nume;
            adresa = h.adresa;
            camere = h.camere;
        }
        return *this;
    }

    ~Hotel() {}

    friend ostream& operator<<(ostream& out, const Hotel& h) {
        out << "Hotel: " << h.nume << ", adresa: " << h.adresa << "\n";
        out << "Camere:\n";
        for (const auto& c : h.camere)
            out << "  " << c << "\n";
        return out;
    }
    std::vector<Camera>& getCamere() { return camere; }
    const std::vector<Camera>& getCamere() const { return camere; }



    void adaugaCamera(const Camera& c) { camere.push_back(c); }

    bool rezervaCamera(int paturi, const Client& c) {
        for (auto& cam : camere) {
            if (cam.esteDisponibila() && cam.getNumarPaturi() >= paturi) {
                cam.rezerva(c);
                return true;
            }
        }
        return false;
    }

    bool elibereazaCamera(int numar) {
        for (auto& cam : camere) {
            if (cam.getNumar() == numar && !cam.esteDisponibila()) {
                cam.elibereaza();
                return true;
            }
        }
        return false;
    }

    void raportCamere() const {
        int libere = 0;
        int ocupate = 0;
        for (const auto& cam : camere) {
            if (cam.esteDisponibila())
                libere++;
            else
                ocupate++;
        }
        cout << "Camere libere: " << libere << ", camere ocupate: " << ocupate << endl;
    }

    int numarPaturiLibere() const {
        int total = 0;
        for (const auto& cam : camere) {
            if (cam.esteDisponibila())
                total += cam.getNumarPaturi();
        }
        return total;
    }
};
class HotelManager {
private:
    Hotel hotel;
    vector<Rezervare> rezervari;

public:
    explicit HotelManager(const Hotel& h) : hotel(h) {}

    Hotel& getHotel() { return hotel; }
    bool adaugaRezervareAutomata(const Client& c, int paturiNecesare, const string& data) {
        for (auto& cam : hotel.getCamere()) {
            if (cam.esteDisponibila() && cam.getNumarPaturi() >= paturiNecesare) {
                cam.rezerva(c);
                rezervari.emplace_back(cam, c, data);
                cout << "Rezervare automata realizata pentru " << c << " in camera " << cam.getNumar() << endl;
                return true;
            }
        }
        cout << "Nu exista camera disponibila pentru " << c << endl;
        return false;
    }

    bool rezervaCameraDirect(int numar, const Client& c, const string& data) {
        for (auto& cam : hotel.getCamere()) {
            if (cam.getNumar() == numar && cam.esteDisponibila()) {
                cam.rezerva(c);
                rezervari.emplace_back(cam, c, data);
                cout << "Rezervare directa realizata pentru " << c << " in camera " << numar << endl;
                return true;
            }
        }
        cout << "Camera " << numar << " nu este disponibila!\n";
        return false;
    }
    bool elibereazaCamera(int numar) {
        bool ok = hotel.elibereazaCamera(numar);
        if (ok) cout << "Camera " << numar << " a fost eliberata prin manager.\n";
        else cout << "Camera " << numar << " nu era ocupata.\n";
        return ok;
    }
    void stergeRezervare(int numarCamera) {
        rezervari.erase(remove_if(rezervari.begin(), rezervari.end(), [numarCamera](const Rezervare& r) {
            return r.getNumarCamera() == numarCamera;
        }), rezervari.end());
        cout << "Rezervarea pentru camera " << numarCamera << " a fost stearsa.\n";
    }

    void afiseazaRezervari() const {
        cout << "\n--- Lista rezervari ---\n";
        if (rezervari.empty()) cout << "Nu exista rezervari.\n";
        for (const auto& r : rezervari) r.afisareDetalii();
    }
    bool areRezervare(const Client& c) const {
        for (const auto& r : rezervari) {
            if (r.getClient().compara(c)) return true;
        }
        return false;
    }
    void afiseazaCamereLibere() const {
        cout << "\nCamere libere in hotel:\n";
        for (const auto& cam : hotel.getCamere()) {
            if (cam.esteDisponibila()) cout << "  " << cam.detaliiCamera() << endl;
        }
    }

    void raportRezervari() const {
        cout << "\n--- Raport rezervari ---\n";
        cout << "Total rezervari: " << rezervari.size() << endl;
    }
};
//---------------------------------------------
// Main: scenariu de utilizare
//---------------------------------------------
int main() {
    Client c1("Popescu", "Ion", "0712345678");
    Client c2("Ionescu", "Maria", "0723456789");
    Client c3("Georgescu", "Andrei", "0734567890");
    Client c4("Vasilescu", "Elena", "0745678901");
    Client c5("Marin", "Alex", "0756789012");

    Camera cam1(101, 1, 2);
    Camera cam2(102, 1, 3);
    Camera cam3(201, 2, 2);
    Camera cam4(202, 2, 1);
    Camera cam5(203, 2, 4);

    Hotel h("Hotel Central", "Str. Libertatii 10");
    h.adaugaCamera(cam1);
    h.adaugaCamera(cam2);
    h.adaugaCamera(cam3);
    h.adaugaCamera(cam4);
    h.adaugaCamera(cam5);
    cout << "Status hotel initial:\n";
    cout << h << endl;

    h.rezervaCamera(2, c1);
    h.rezervaCamera(1, c2);
    h.rezervaCamera(3, c3);
    h.rezervaCamera(4, c4);
    h.rezervaCamera(1, c5);
    cout << "\nDupa rezervari:\n";
    cout << h << endl;
    h.raportCamere();
    cout << "Numar total paturi libere: " << h.numarPaturiLibere() << endl;

    cout << "\nVerificare comparare clienti:\n";
    if (c1.compara(c2)) cout << "c1 si c2 sunt aceeasi persoana\n";
    else cout << "c1 si c2 sunt diferiti\n";

    if (c4.compara(c4)) cout << "c4 si c4 sunt aceeasi persoana\n";

    cout << "\nSchimbare telefoane clienti:\n";
    c1.schimbaTelefon("0799999999");
    c2.schimbaTelefon("0788888888");
    cout << c1 << endl;
    cout << c2 << endl;

    cout << "\nEliberare camere 101 si 202:\n";
    if (h.elibereazaCamera(101)) cout << "Camera 101 eliberata\n";
    if (h.elibereazaCamera(202)) cout << "Camera 202 eliberata\n";
    cout << h << endl;

    Rezervare r1(cam3, c3, "2025-11-05");
    Rezervare r2(cam5, c4, "2025-12-01");
    r1.afisareDetalii();
    r2.afisareDetalii();

    cout << "\nVerificare date rezervari:\n";
    cout << "r1 data corecta? " << (r1.verificaData("2025-11-05") ? "Da" : "Nu") << endl;
    cout << "r2 data corecta? " << (r2.verificaData("2025-11-05") ? "Da" : "Nu") << endl;

    cout << "\nIterare si afisare detalii camere:\n";
    for (auto& cam : h.getCamere()) {
        cout << cam << endl;
        if (!cam.esteDisponibila()) {
            cout << "  Camera ocupata, paturi: " << cam.getNumarPaturi() << endl;
        } else {
            cout << "  Camera libera, paturi: " << cam.getNumarPaturi() << endl;
        }
    }
    cout << "\nIterare si afisare detalii camere:\n";
    for (auto& cam : h.getCamere()) {
        cout << cam << endl;
        if (!cam.esteDisponibila()) {
            cout << "  Camera ocupata, paturi: " << cam.getNumarPaturi() << endl;
        } else {
            cout << "  Camera libera, paturi: " << cam.getNumarPaturi() << endl;
        }
    }

    cout << "\nTest rezervare suplimentara pentru camere ocupate:\n";
    if (!h.rezervaCamera(3, c5)) cout << "Nu exista camera libera pentru 3 paturi, clientul c5 nu poate rezerva\n";

    cout << "\nRezervari si eliberari in bucla:\n";
    for (auto& cam : h.getCamere()) {
        if (cam.esteDisponibila()) {
            cam.rezerva(c5);
            cout << "Rezervare automata camera " << cam.getNumar() << " pentru c5\n";
        } else {
            cam.elibereaza();
            cout << "Eliberare automata camera " << cam.getNumar() << "\n";
        }
    }

    cout << "\nTest rezervare suplimentara pentru camere ocupate:\n";
    if (!h.rezervaCamera(3, c5)) cout << "Nu exista camera libera pentru 3 paturi, clientul c5 nu poate rezerva\n";

    cout << "\nStare finala hotel:\n";
    cout << h << endl;
    cout << "\nAfisare finala clienti si camere:\n";
    cout << c1 << "\n" << c2 << "\n" << c3 << "\n" << c4 << "\n" << c5 << endl;
    for (int i = 0; i < 2; i++) {
        for (auto& cam : h.getCamere()) {
            if (cam.esteDisponibila()) {
                cam.rezerva(c1);
                cout << "Rezervare " << i+1 << " camera " << cam.getNumar() << " pentru c1\n";
            } else {
                cam.elibereaza();
                cout << "Eliberare " << i+1 << " camera " << cam.getNumar() << "\n";
            }
        }
    }

    cout << "\n=== Afisare camere dupa teste suplimentare ===\n";
    for (const auto& cam : h.getCamere()) {
        cout << cam.detaliiCamera() << endl;
    }
    cout << "\n=== Testare HotelManager ===\n";
    HotelManager manager(h);

    manager.afiseazaCamereLibere();
    manager.rezervaCameraDirect(101, c1, "2025-11-10");
    manager.rezervaCameraDirect(202, c2, "2025-11-11");
    manager.adaugaRezervareAutomata(c3, 2, "2025-11-15");
    manager.afiseazaRezervari();

    manager.elibereazaCamera(101);
    manager.stergeRezervare(101);
    manager.raportRezervari();

    cout << "\nVerificare rezervari clienti:\n";
    cout << c1.getNumeComplet() << (manager.areRezervare(c1) ? " are rezervare.\n" : " nu are rezervare.\n");
    cout << c3.getNumeComplet() << (manager.areRezervare(c3) ? " are rezervare.\n" : " nu are rezervare.\n");

    manager.afiseazaCamereLibere();

    return 0;
}
