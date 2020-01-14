#ifndef WS2300_H
#define WS2300_H
#include "G2PortSerie.h"
class WS2300{
	private:
	bool estOuvert;
	
	public:
	WS2300();
	~WS2300();
	bool LireUnOctet (char octetALire [1] );
	bool EcrireUnOctet (char octetAEcrire [1] );
	bool OuvrirPortSerie(char nomPortSerie [20]);
	bool FermerPortSerie();
	bool Initialiser();
	bool EstOuvert();
	bool LireDesOctets(unsigned short adresse, char octetsLus[20], int nbOctectsALire);
	G2PortSerie ps;
};
#endif
