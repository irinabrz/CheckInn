#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
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

    Client(const string& n = "", const string& p = "", const string& t = "")
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

    void schimbaTelefon(const string& t) { telefon = t; }
    string getNumeComplet() const { return nume + " " + prenume; }
    bool compara(const Client& c) const { return nume == c.nume && prenume == c.prenume; }
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

    Camera(int nr = 0, int e = 0, int p = 1)
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

    bool rezerva(const Client& c) {
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
    Rezervare(const Camera& cam = Camera(), const Client& c = Client(), const string& d = "")
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
};

//---------------------------------------------
// Clasa Hotel
//---------------------------------------------
class Hotel {
private:
    string nume;
    string adresa;
    vector<Camera> camere;

public:

    Hotel(const string& n = "", const string& a = "")
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

//---------------------------------------------
// Main: scenariu de utilizare
//---------------------------------------------
int main() {
    Client c1("Popescu", "Ion", "0712345678");
    Client c2("Ionescu", "Maria", "0723456789");
    Client c3("Georgescu", "Andrei", "0734567890");

    Camera cam1(101, 1, 2);
    Camera cam2(102, 1, 3);
    Camera cam3(201, 2, 2);
    Camera cam4(202, 2, 1);

    Hotel h("Hotel Central", "Str. Libertatii 10");
    h.adaugaCamera(cam1);
    h.adaugaCamera(cam2);
    h.adaugaCamera(cam3);
    h.adaugaCamera(cam4);

    cout << h << endl;

    h.rezervaCamera(2, c1);
    h.rezervaCamera(1, c2);
    h.rezervaCamera(3, c3); // va rezerva camera cu 3 paturi

    cout << "\nDupa rezervari:\n";
    cout << h << endl;

    h.raportCamere();
    cout << "Numar total paturi libere: " << h.numarPaturiLibere() << endl;

    h.elibereazaCamera(101);
    cout << "\nDupa eliberarea camerei 101:\n";
    cout << h << endl;///test

    return 0;
}
