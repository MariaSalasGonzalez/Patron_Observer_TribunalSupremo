#include <iostream>
#include <sstream>
#include <Windows.h>
using namespace std;


//esta es la interfaz
//esto es un observer
//padre de los observadores

class Partido {
   protected:
	   int valorPLN; //total
	   int valorPUSC; //va a ir sumando
	   int valorPAC; 
   public:
	   Partido();
	   virtual ~Partido();
	   virtual void update(int, int, int) = 0;//importante
	   virtual string toString() = 0;
	   virtual void graficando();
	   virtual int getVal1();
	   virtual int getVal2();
	   virtual int getVal3();
};

Partido::Partido() {
	cout << "-----Creando un partido politico----" << endl;
	    valorPLN = 0;
		valorPUSC = 0;
		valorPAC = 0;
}

Partido:: ~Partido() {
	cout << "Eliminando partido" << endl;
}

int Partido::getVal1() {
	return valorPLN;
}

int Partido::getVal2() {
	return valorPUSC;
}

int Partido::getVal3() {
	return valorPAC;
}

void Partido::graficando() {
	//desarrollo
}


//----------------------------------------------------

class PartidoLiberacion : public Partido {
	private:
		string nombre;
	public:
		PartidoLiberacion() {
			nombre = "PartidoLiberacion Nacional";
		}

		virtual~PartidoLiberacion() {
		}

		virtual void update(int a, int b, int c) {
			valorPLN += a; //valorPLN= valorPLN + a;
			valorPUSC += b;
			valorPAC += c;
		}

		virtual string toString() {
			stringstream s;
			s << "-------Partido Liberacion Naciona-----" << endl
				<< "Votos.... PLN = " << valorPLN << endl
				<< "Votos.... PAC = " << valorPAC << endl
				<< "Votos.... PUSC = " << valorPUSC << endl;
			return s.str();
		}

		virtual void graficando() {
			//desarrollo
		}

	};

//---------------------------------------------------
class PartidoUnidad : public Partido {
	private:
		string nombre;
	public:
		PartidoUnidad() {
			nombre = "Partido Unidad";
		}

		virtual~PartidoUnidad() {
		}

		virtual void update(int a, int b, int c) {
			valorPLN += a; //valorPLN= valorPLN + a;
			valorPUSC += b;
			valorPAC += c;
		}

		virtual string toString() {
			stringstream s;
			s << "-------Partido Unidad-----" << endl
				<< "Votos.... PLN = " << valorPLN << endl
				<< "Votos.... PAC = " << valorPAC << endl
				<< "Votos.... PUSC = " << valorPUSC << endl;
			return s.str();
		}

		virtual void graficando() { //a este le interesa ver graficos
			cout << "Partido Unidad" << endl;
			cout << "1.PLN: ";
			for (int i = 0; i < valorPLN / 100; i++) //PLN
				cout << "*"; cout << endl;
			cout << "2.PAC: ";
			for (int i = 0; i < valorPAC / 100; i++) //PAC
				cout << "*"; cout << endl;
			cout << "3.PUSC: ";
			for (int i = 0; i < valorPUSC / 100; i++) //PUSC
				cout << "*"; cout << endl;
		}

};

//------------------------------------------------------------------

class TSE { //subject
	//cosas del tribunal
	//el tribunal va actualizando estos valores
private:
	int numMesa; //Numero de la mesa de votacion
	int valor1; //PLN
	int valor2; //PAC
	int valor3; //PUSC
	Partido** vec; //Contenedor
	int can;
	int tam;
	
public:
	TSE();
	virtual ~TSE();
	void attach(Partido*);
	void setValores(int a, int b, int c);
	void notify();
    //pura fantasia --- puro maquillaje
	void conteoVotosXMesa();
	void infoDeMesa();
	void solicitaNuevaMesa();
};

TSE::TSE() {
	int numMesa=0;
	int valor1=0; 
	int valor2=0; 
	int valor3=0;
	vec = new Partido*[5];
	tam = 5;
	can = 0;
}

TSE::~TSE() {
	for (int i = 0; i < can; i++)
		delete vec[i];
	delete []vec;
}

void TSE::attach(Partido* obs) {
	vec[can++] = obs;
}

void TSE::setValores(int a, int b, int c) {
	int valor1 = a; //PLN
	int valor2 = b; //PAC
	int valor3 = c; //PUSC
	this->notify();
}

void TSE::notify() {
	for (int i = 0; i < can; i++)
		vec[i]->update(valor1, valor2, valor3); //actualizandotodos los observer
}

//ayuda a los metodos vitales
void TSE::conteoVotosXMesa() {
	int v1, v2, v3;
	v1 = 1 + rand() % (101 - 1); //obtiene valores de 1 - 100
	v2 = 1 + rand() % (101 - 1);
	v3 = 1 + rand() % (101 - 1);
	numMesa = 1 + rand() % (1000 - 1); //valor aleatorio de 1 - 10000;
	this->setValores(v1, v2, v3);
}

void TSE::infoDeMesa() {
	cout << "------Mesa No." << numMesa << endl;
	cout << "Votos del PLN = " << valor1 << endl;
	cout << "Votos del PAC = " << valor2 << endl;
	cout << "Votos del PUSC = " << valor3 << endl;
}

void TSE::solicitaNuevaMesa() {
	this->conteoVotosXMesa();
}

int main() {
	cout << "-------------PARTICIPACION POPULAR---------" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Crear partido politico" << endl;
	Partido* obv1 = new PartidoLiberacion();
	Partido* obv2 = new PartidoUnidad();

	cout << "Creacion del TSE" << endl;
	TSE objTSE;

	cout << "Ingresar partidos al TSE...." << endl;
	objTSE.attach(obv1);
	objTSE.attach(obv2);

	int x = 0;
	system("pause");
	
	while (x < 100) {
		system("cls");
		cout << "------------------SIMULACION-----------------" << endl;
		cout << "---------------------------------------------" << endl;
		objTSE.solicitaNuevaMesa();
		cout << endl << endl;
		cout << "----------------Informacion TSE--------------" << endl;
		cout << "---------------------------------------------" << endl;
		objTSE.infoDeMesa();
		cout << endl << endl;
		cout << "--------------------PARTIDOS------------------" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << endl;
		cout << "PARTIDO LIBERACION NACIONAL" << endl;
		cout << obv1->toString() << endl << endl;
		cout << "PARTIDO UNIDAD SOCIAL CRISTIANA" << endl;
		obv2->graficando();
		Sleep(5000);
		x++;
	}


	system("pause");
	return 0;
};
