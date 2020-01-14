#include "WS2300.h"

#include <iostream>
#include <unistd.h>

using namespace std;


int main()
{
	WS2300 station;
	char nom[20]="/dev/ttyUSB0";
	if(station.OuvrirPortSerie(nom))
	{
		cout<<"ok"<<endl;
	}
	else
	{
		cout<<"échec"<<endl;
		
	}

	/*char octetAEnvoyer[1]={0x06};
	if(station.EcrireUnOctet(octetAEnvoyer))
	{
		cout<<"bien passé"<<endl;
	}
	else
	{
		cout<<"pas bien passé"<<endl;
	}
	char octetALire[1];
	if(station.LireUnOctet(octetALire))
	{
		cout<<"Octet lu : "<<(int)octetALire[0]<<endl;
	}
	else
	{
		cout<<"Octet pas lu"<<endl;
	}*/
	char reponse[5];
	int vent;
	if(station.LireDesOctets(0x527,reponse,3)==true)
	{
		vent=(reponse[2]>>4)*22;
		cout<<"la direction du vent est : "<<dec<<(int) vent<<"°"<<endl;
	}
	else
	{
		cout<<"Echec direction du vent"<<endl;
	}
	
	if(station.LireDesOctets(0x0346,reponse,5)==true)
	{
		float temp=((reponse[1]>>4)-3)*10+(reponse[1]&0x000F)+((reponse[0]>>4)/10.0)+((reponse[0]&0x000F)/100.0);
		cout<<"la temperature est : "<<dec<<(float) temp<<"°"<<endl;
	}
	else
	{
		cout<<"Echec temperature"<<endl;
	}
	
	station.Initialiser();
	station.FermerPortSerie();
    return 0;
	
}	
