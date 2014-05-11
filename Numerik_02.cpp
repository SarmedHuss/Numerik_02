// Numerik_02.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
 
using namespace std;

double pi = 3.14159265;
double sigma = 5810000.0;
double my = 1-0.0000064;
double c = 300000000;
double rho0 = 5;			//Wert fehlt
double k = 0.0;

double reihe(bool abl, double con, double x, int add)
{
	double reihe = con;			//Der Start der Reihe ändert sich aber das Verhalen bleibt gleich
	double zaehler = con;
	double nenner = 1.0;
	int n =0;
	int faktor = 2-add;			// Nötig um die Methode auch für die Ableitungen zu benutzen
	for(unsigned int k = 1 + add; k<10; k++){
		n=k;
		if(abl){								// Falls es sich um eine Ableitung handelt, kommt ein Faktor hinzu
			n+=1-add;
			zaehler /= faktor;
			faktor += 2;
			zaehler *= -faktor * x*x*x*x/16;		//Es werden die Reihenglieder iterativ bestimmt
		}
		else 
			zaehler *= -x*x*x*x/16;
		nenner *= (2*n-add)*(2*n-add-1)*(2*n+add)*(2*n+add-1);			//Die Fakultät wird immer um das Quadrat der nächsten beiden Faktoren erweitert
		reihe += zaehler/nenner;
	}
	return reihe;
}


double ber(double x)
{
	return reihe(false, 1, x, 0);
}

double bei(double x)
{
	double con = x*x/4;
	return reihe(false, con, x, 1);
}

double berAbl(double x)
{
	double con = -x*x*x/16;
	return reihe(true, con, x, 0);
}

double beiAbl(double x)
{
	double con = -x/2;
	return reihe(true, con, x, 1);
}

double kappa(double w)
{
	k = 2*sqrt(pi*my*sigma*w)/c;
	return k;
}


double realLadung(double I0, double rho)		//Berechnet den Realteil der Ladungsfunktion
{
	double x = k*rho;
	double j = (ber(x)*beiAbl(k*rho0)-berAbl(k*rho0)*bei(x))/(berAbl(k*rho0)*berAbl(k*rho0)+beiAbl(k*rho0)*beiAbl(k*rho0));
	return j;
}

double imgLadung(double I0, double rho)			//Berechnet den Imaginärteil der Ladungsfunktion
{
	double x = k*rho;
	double j = (ber(x)*berAbl(k*rho0)-beiAbl(k*rho0)*bei(x))/(berAbl(k*rho0)*berAbl(k*rho0)+beiAbl(k*rho0)*beiAbl(k*rho0));
	return j;
}

int main()
{
	double I0 = 30;
	double betrag=0;
	double rho = 10;
	double w = 0;
	double c = 0;
	std::cout << "Geben sie nun einen Wert fuer w an:" << std::endl;
	std::cin >> w ;
	kappa(w);
	c = I0*k/(2*pi*rho0);
	betrag = c * sqrt( imgLadung (I0, rho)*imgLadung (I0, rho) + realLadung (I0, rho)*realLadung (I0, rho));
    std::cout << "Die Ladung betraegt: " << betrag << std::endl;
}