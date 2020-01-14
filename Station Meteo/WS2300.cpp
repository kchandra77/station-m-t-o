#include "WS2300.h"
#include <iostream>
#include <unistd.h>
WS2300::WS2300()
{
	estOuvert=false;
}

bool WS2300::OuvrirPortSerie(char nomPortSerie [20])
{ 
	if(ps.Ouvrir(nomPortSerie) <0 )
	{
		return false;
	}
	if(ps.ModifierVitesse(V2400_BAUD)==0)
	{
		return false;
	}
	if(ps.ModifierLongueurDonnees(D8_BITS)==0)
	{
		return false;
	}
	if(ps.ModifierNombreBitStop(S1_BIT)==0)
	{
		return false;
	}
	if(ps.ModifierParite(PAS_DE_PARITE)==0)
	{
		return false;
	}
	
	estOuvert=true;
	return true;
	
}

bool WS2300::FermerPortSerie()
{
	int res;
	if(estOuvert==true)
	{
		res=ps.Fermer();
		if(res==0)
		{
			return true;
		}
	} 
	return false;
}

WS2300::~WS2300()
{
	
}
bool WS2300::EcrireUnOctet (char octetAEcrire [1] )
{
	ps.ModifierRequestToSend(1);
	ps.ModifierDataTerminalReady(0);
	int n=ps.EnvoyerDesOctets(octetAEcrire,1);
	return n;
}
bool WS2300::LireUnOctet (char octetALire [1] )
{
	int nbBoucle=0;
	int nbOctectsLus=0;
	do
	{
		nbOctectsLus=ps.LireDesOctets(octetALire,1);
		usleep(4000);
		nbBoucle++;
	}while(nbOctectsLus<=0 && nbBoucle<=50);
	
	if(nbOctectsLus==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool WS2300::Initialiser()
{
	char octet[1];
	int val,nbFois=0;
	do
	{
		octet[0]=0x06;
		EcrireUnOctet(octet);
		LireUnOctet(octet);
		val=octet[0];
		cout<<val<<endl;
		nbFois++;
		if(nbFois>10)
		{
			return false;
		}
	}while(val!=0x02);
	return true;
}
bool WS2300::LireDesOctets(unsigned short adresse, char octetsLus[0], int nbOctetsALire)
{ 
	char tabE[5];
	tabE[0]=(adresse>>12)*4+0x82;
	tabE[1]=((adresse>>8)&0x000F)*4+0x82;
	tabE[2]=((adresse>>4)&0x000F)*4+0x82;
	tabE[3]=((adresse&0x000F)*4)+0x082;
	tabE[4]=nbOctetsALire*4+0xC2;	
	
	
	for(int i=0; i<5; i++)
		{
			cout<<hex<<(int)tabE[i]<<endl;
		}
	char octetLu[1];
	for(int j=0; j<5; j++)
		{
			EcrireUnOctet(&tabE[j]);
			if(LireUnOctet(octetLu)==false)
				{
					return false;
				}
			cout<<hex<<(int)octetLu[0]<<endl;
		}
	for(int k=0;k<nbOctetsALire;k++)
		{
			if(LireUnOctet(&octetsLus[k])==false)
				{
					return false;
				}
			cout<<hex<<(int)octetsLus[k]<<endl;
		}
		// Lecture du checksum
		if(LireUnOctet(octetLu)==false)
				{
					return false;
				}
				cout<< "CHECKSUM : " <<hex<<(int)octetLu[0]<<endl;
		
	
		return true;
}
