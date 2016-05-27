#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

struct AD {
	AD *si, *no;
	string dat;

	AD();
	AD(string);
	void Insertar(string);
	void Carga(ifstream &);
	void Guarda(fstream &);
};

AD::AD(string ani) : si(NULL), no(NULL), dat(ani) {}

void AD::Insertar(string ani) {
	if (!no) no = new AD(ani);
	else no->Insertar(ani);
}

void AD::Carga(ifstream &f) {
	string tmp;
	if (getline(f, tmp) and tmp != "---") {
		si = new AD(tmp); si->Carga(f);
	}
	if (getline(f, tmp) and tmp != "---") {
		no = new AD(tmp); no->Carga(f);
	}
}

void AD::Guarda(fstream &f) {
	f << dat << '\n';
	if (si) si->Guarda(f);
	else f << "---\n";
	if (no) no->Guarda(f);
	else f << "---\n";
}

int main(int argc, char **argv) {
	AD *arbol;
	string tmp;
	string nombre = "animales.dat";
	if (argc > 1) {
		nombre = string(argv[1]);
		ifstream arch(nombre);
		getline(arch, tmp);
		if (tmp == "") {
			cout << "Escribe una pregunta\n"; getline(cin, tmp);
			arbol = new AD(tmp);
			cout << "Escribe el animal\n"; getline(cin, tmp);
			arbol->si = new AD(tmp);
		}
		else {
			arbol = new AD(tmp);
			arbol->Carga(arch);
		}
		arch.close();
	}
	else {
		cout << "Escribe una pregunta\n"; getline(cin, tmp);
		arbol = new AD(tmp);
		cout << "Escribe el animal\n"; getline(cin, tmp);
		arbol->si = new AD(tmp);
	}
	AD *inicio = arbol;

	char r;
	string preg;
	while (arbol != NULL) {
		if (arbol->si) cout << arbol->dat << " (S/N)\n";
		else cout << "Es un " << arbol->dat << "? (S/N)\n";
		cin >> r; cin.ignore();
		if (r == 'S' or r == 's') {
			if (arbol->si) arbol = arbol->si;
			else {
				cout << "Gané\n";
				cout << "Quieres volver a jugar?\n";
				cin >> r;
				if (r == 'S' or r == 's') arbol = inicio;
				else {
					fstream arch(nombre, fstream::out);
					inicio->Guarda(arch);
					arch.close();
					return 0;
				}
			}
		}
		else {
			if (arbol->no) arbol = arbol->no;
			else {
				cout << "Escribe una pregunta\n"; getline(cin, preg);
				arbol->Insertar(preg); arbol = arbol->no;
				cout << "Escribe el animal\n"; getline(cin, preg);
				arbol->si = new AD(preg);
				cout << "Quieres volver a jugar?\n";
				cin >> r;
				if (r == 'S' or r == 's') arbol = inicio;
				else {
					fstream arch(nombre, fstream::out);
					inicio->Guarda(arch);
					arch.close();
					return 0;
				}
			}
		}
	}

	return 0;
}
