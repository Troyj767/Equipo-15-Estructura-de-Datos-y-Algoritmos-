#include <iostream>
#include <string>
#include <iomanip>
 
using namespace std;
 
const int MAX_ESTUDIANTES = 30;
const int NUM_EVALUACIONES = 5;
const double NOTA_APROBACION = 70.0;
 
class Estudiante {
private:
	string nombre;
	string matricula;
	double calificaciones[NUM_EVALUACIONES];
	double promedio;
	bool aprobado;
 
public:
	Estudiante() : promedio(0), aprobado(false) {
    	nombre = ""; matricula = "";
    	for (int i = 0; i < NUM_EVALUACIONES; i++) calificaciones[i] = 0;
	}
 
	// a) Registrar notas y calcular promedio automaticamente
	void registrar(string nom, string mat, double notas[]) {
    	nombre = nom; matricula = mat;
    	double suma = 0;
    	for (int i = 0; i < NUM_EVALUACIONES; i++) {
        	calificaciones[i] = notas[i];
        	suma += notas[i];
    	}
    	promedio = suma / NUM_EVALUACIONES;      	// b) Promedio automatico
    	aprobado = (promedio >= NOTA_APROBACION);	// Estado aprobado/reprobado
	}
 
	// Getters
	string getNombre()	const { return nombre; }
	string getMatricula() const { return matricula; }
	double getPromedio()  const { return promedio; }
	bool   isAprobado()   const { return aprobado; }
	double getNota(int i) const { return calificaciones[i]; }
 
	void mostrar() const {
    	cout << left << setw(25) << nombre << setw(14) << matricula;
    	for (int i = 0; i < NUM_EVALUACIONES; i++)
        	cout << setw(8) << fixed << setprecision(1) << calificaciones[i];
    	cout << setw(10) << promedio
         	<< (aprobado ? "APROBADO" : "REPROBADO") << endl;
	}
};
 
// Arreglo unidimensional de objetos Estudiante
Estudiante estudiantes[MAX_ESTUDIANTES];
int total = 0;
 
// a) Registrar estudiantes y notas
int registrarEstudiantes() {
	int n = 0;
	char continuar = 's';
	cout << "\n==== REGISTRO DE ESTUDIANTES ====" << endl;
	while (n < MAX_ESTUDIANTES && (continuar=='s'||continuar=='S')) {
    	string nom, mat;
    	double notas[NUM_EVALUACIONES];
    	cout << "\nEstudiante #" << (n+1) << endl;
    	cout << "Nombre   : "; cin.ignore(); getline(cin, nom);
    	cout << "Matricula: "; getline(cin, mat);
    	for (int i = 0; i < NUM_EVALUACIONES; i++) {
        	do { cout << "Evaluacion " << (i+1) << " (0-100): ";
             	cin >> notas[i]; } while (notas[i]<0||notas[i]>100);
    	}
    	estudiantes[n].registrar(nom, mat, notas);
    	n++;
    	if (n < MAX_ESTUDIANTES) {
        	cout << "Registrar otro? (s/n): "; cin >> continuar;
    	}
	}
	return n;
}
 
void imprimirCabecera() {
	cout << left << setw(25)<<"Nombre" << setw(14)<<"Matricula";
	for(int i=1;i<=NUM_EVALUACIONES;i++) cout<<setw(8)<<("Eval"+to_string(i));
	cout << setw(10)<<"Promedio" << "Estado" << endl;
	cout << string(95,'-') << endl;
}
 
// c) Mostrar aprobados con promedio >= 70
void mostrarAprobados() {
	cout << "\n=== ESTUDIANTES APROBADOS (Promedio >= 70) ===" << endl;
	imprimirCabecera();
	bool hay = false;
	for (int i = 0; i < total; i++)
    	if (estudiantes[i].isAprobado()) { estudiantes[i].mostrar(); hay=true; }
	if (!hay) cout << "No hay estudiantes aprobados." << endl;
}
 
// d) Ordenar por promedio (burbuja, mayor a menor)
void ordenarPorPromedio() {
	for (int i = 0; i < total-1; i++)
    	for (int j = 0; j < total-1-i; j++)
        	if (estudiantes[j].getPromedio() < estudiantes[j+1].getPromedio()) {
            	Estudiante temp = estudiantes[j];
            	estudiantes[j]   = estudiantes[j+1];
            	estudiantes[j+1] = temp;
        	}
}
 
void mostrarTodos() {
	cout << "\n=== LISTADO GENERAL (Por Promedio) ===" << endl;
	imprimirCabecera();
	for (int i = 0; i < total; i++) estudiantes[i].mostrar();
}
 
int main() {
	int opcion;
	cout << "===================================" << endl;
	cout << "  SISTEMA DE CALIFICACIONES BOOTCAMP" << endl;
	cout << "===================================" << endl;
	do {
    	cout << "\n1. Registrar estudiantes y notas" << endl;
    	cout << "2. Mostrar aprobados" << endl;
    	cout << "3. Ordenar y mostrar todos por promedio" << endl;
    	cout << "4. Salir" << endl;
    	cout << "Opcion: "; cin >> opcion;
    	switch(opcion) {
        	case 1: total = registrarEstudiantes(); break;
        	case 2: if(total==0) cout<<"Registre estudiantes primero."<<endl;
                	else mostrarAprobados(); break;
        	case 3: if(total==0) cout<<"Registre estudiantes primero."<<endl;
                	else { ordenarPorPromedio(); mostrarTodos(); } break;
        	case 4: cout<<"Saliendo..."<<endl; break;
        	default: cout<<"Opcion invalida."<<endl;
    	}
	} while(opcion != 4);
	return 0;
}

