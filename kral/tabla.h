#include <deque>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <iostream>
#include <fstream>
using namespace std;

#ifndef TABLA_H
#define TABLA_H

class poz
{
public:
	int br;
	int bu;
	int koef;

	poz()
	{};
	poz(int br,int bu,int nacin)
	{
		this->br=br;
		this->bu=bu;
		switch(nacin)
		{
		case 0:
			koef=0;
			break;
		case 1:
//tuka treba kod za evaluacija direktno od tabla
			koef=0;
			break;
		case 2:
			koef=0;
//tuka za AI
			break;
		default:
			koef=0;
			break;
		};

	};
	friend class figura;
};

class figura
{
public:
	int tip;//0-prazno,1-piun,2-top,3-konj,4-lanfer,5-kralica,6-kral
	int owner;//0-prazno,1-igrach,2-VI
	bool pomesteno;
	figura()
	{
		pomesteno=false;
		mozni.clear();
	};
	figura(const figura& B){
		this->tip=B.tip;
		this->owner=B.owner;
		this->pomesteno=B.pomesteno;
		this->mozni.clear();
//		if(B.mozni.size()>0)
//			for(int i=0;i<B.mozni.size()-1;i++)
//				this->mozni.push_back(B.mozni[i]);
	}
	poz idealna;
	std::deque <poz> mozni;
	friend class tabla;
	const figura operator=(const figura B)
	{
		this->tip=B.tip;
		this->owner=B.owner;
		this->pomesteno=B.pomesteno;
		this->mozni.clear();
//		if(B.mozni.size()>0)
//			for(int i=0;i<B.mozni.size()-1;i++)
//				this->mozni.push_back(B.mozni[i]);
		return *this;
	}
	const void vrati_idealna_od_mozni()
	{
		int i=1;
		srand((unsigned)time(0));
		std::deque <poz> idealni;
		if(mozni.size()>0)
			idealni.push_back(mozni[0]);
		while(mozni.size()>i)
		{
			if(idealni[idealni.size()-1].koef<mozni[i].koef)
			{
				idealni.clear();
				idealni.push_back(mozni[i]);
			}
			if(idealni[idealni.size()-1].koef==mozni[i].koef)
			{
				idealni.push_back(mozni[i]);
			}
			i++;
		}
		idealna=idealni[rand()%idealni.size()];
	}

};


class tabla
{
public:
	int br_select;
	int bu_select;
	bool mat_i1;
	bool pat_i1;
	bool mat_i2;
	bool pat_i2;
	figura prazno;
	figura tablata[8][8];
	int unapreduvanje;

	//VREDNOSTI
	int v_kral;
	int v_kralica;
	int v_top;
	int v_lanfer;
	int v_konj;
	int v_piun;
	//koeficienti
	float c_cuvanje;
	float c_napad;
	int c_otvorenost;
	int u_otvorenost;

	void set_select(int br,int bu)
	{
		br_select=br;
		bu_select=bu;
	};
	void pochetok(bool beli_dolu)
	{
		mat_i1=false;
		pat_i1=false;
		mat_i2=false;
		pat_i2=false;
		for(int i=0;i<8;i++)
		{
			prazno.mozni.clear();
			prazno.owner=0;
			prazno.tip=0;
			prazno.pomesteno=false;
			tablata[1][i].tip=1;
			tablata[6][i].tip=1;
			tablata[0][i].owner=2;
			tablata[1][i].owner=2;
			tablata[6][i].owner=1;
			tablata[7][i].owner=1;

			for(int j=2;j<=5;j++)
			{
				tablata[j][i].tip=0;
				tablata[j][i].owner=0;
			}

		}
			tablata[0][0].tip=2;
		tablata[0][1].tip=3;
		tablata[0][2].tip=4;
		
		if(beli_dolu==true)
		{
			tablata[0][3].tip=5;
			tablata[0][4].tip=6;
		}
		else
		{	
			tablata[0][3].tip=6;
			tablata[0][4].tip=5;
		}
		
		tablata[0][5].tip=4;
		tablata[0][6].tip=3;
		tablata[0][7].tip=2;
		tablata[7][0].tip=2;
		tablata[7][1].tip=3;
		tablata[7][2].tip=4;
		
		if(beli_dolu==true)
		{
			tablata[7][3].tip=5;
			tablata[7][4].tip=6;
		}
		else
		{	
			tablata[7][3].tip=6;
			tablata[7][4].tip=5;
		}
		
		tablata[7][5].tip=4;
		tablata[7][6].tip=3;
		tablata[7][7].tip=2;

		//TESTING=======
/*		mat_i1=false;
		pat_i1=false;
		mat_i2=false;
		pat_i2=false;
		for(int i=0;i<8;i++)
		{
			prazno.mozni.clear();
			prazno.owner=0;
			prazno.tip=0;
			prazno.pomesteno=false;
			for(int j=0;j<=7;j++)
			{
				tablata[j][i].tip=0;
				tablata[j][i].owner=0;
			}
		}
		tablata[2][2].tip=5;
		tablata[2][2].owner=2;

		tablata[3][5].tip=1;
		tablata[3][5].owner=2;

		tablata[4][4].tip=1;
		tablata[4][4].owner=1;

		tablata[5][5].tip=1;
		tablata[5][5].owner=1;

		tablata[5][3].tip=1;
		tablata[5][3].owner=1;

		//kralevite
		tablata[0][0].tip=6;
		tablata[0][0].owner=2;
		tablata[7][7].tip=6;
		tablata[7][7].owner=1;*/

	};
	const int z_tip(int br,int bu)
	{
		return tablata[br][bu].tip;
	};
	const int z_owner(int br,int bu)
	{
		return tablata[br][bu].owner;
	};
	tabla()
	{
		pochetok(true);

		//vrednosti 
		this->v_kral=5000;
		this->v_kralica=2500;
		this->v_top=1250;
		this->v_lanfer=900;
		this->v_konj=850;
		this->v_piun=450;
		//koeficienti
		this->c_cuvanje=1;
		this->c_napad=2;
		this->c_otvorenost=1;
		this->u_otvorenost=6;
	};
	tabla(const tabla& obj){
		//tablata
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				tablata[i][j]=obj.tablata[i][j];
			}
		}
		//statusi
		this->br_select=obj.br_select;
		this->bu_select=obj.bu_select;
		this->mat_i1=obj.mat_i1;
		this->pat_i1=obj.pat_i1;
		this->mat_i2=obj.mat_i2;
		this->pat_i2=obj.pat_i2;
		//def
		this->prazno=obj.prazno;
		this->unapreduvanje=obj.unapreduvanje;
		//vrednosti
		this->v_kral=obj.v_kral;
		this->v_kralica=obj.v_kralica;
		this->v_top=obj.v_top;
		this->v_lanfer=obj.v_lanfer;
		this->v_konj=obj.v_konj;
		this->v_piun=obj.v_piun;
		//koeficienti
		this->c_cuvanje=obj.c_cuvanje;
		this->c_napad=obj.c_napad;
		this->c_otvorenost;
		//uslovi
		this->u_otvorenost;
	};
	const tabla operator=(const tabla& obj){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				tablata[i][j]=obj.tablata[i][j];
			}
		}
		this->br_select=obj.br_select;
		this->bu_select=obj.bu_select;
		this->mat_i1=obj.mat_i1;
		this->pat_i1=obj.pat_i1;
		this->mat_i2=obj.mat_i2;
		this->pat_i2=obj.pat_i2;
		this->prazno=obj.prazno;
		this->unapreduvanje=obj.unapreduvanje;
		return *this;
	}
/*	int procenka_so_gen(int za_koj)
	{
		int ret=0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(tablata[i][j].owner!=0){
					if(tablata[i][j].owner==za_koj){
						ret+=tablata[i][j].tip;
						gen_mozni(i,j);
					}else{
						ret-=tablata[i][j].tip;
					}
				}
			}
		}
		return ret;
	};*/
	const int procenka_bez_gen(int za_koj)
	{
		int vrednost=0;
		bool giCuvam[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		bool giNapagjam[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		bool miSePodNapad[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		bool siGiCuva[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		int i,j;

		for(int br=0;br<8;br++)
		{
			for(int bu=0;bu<8;bu++)
			{
				if(tablata[br][bu].owner==za_koj)
				{//ako figurata na BR, BU e na e na red====================================
					//=====================================================================

					switch(tablata[br][bu].tip)
					{
					case 0:
						break;
					case 1://============================================piun==============
						vrednost+=this->v_piun;
						if(tablata[br][bu].owner==1)
						{
							if(br-1>=0)
							{
								if(bu-1>=0 && tablata[br-1][bu-1].owner!=0)
								{
									if(tablata[br-1][bu-1].owner==2)
										giNapagjam[br-1][bu-1]=true;
									else
										giCuvam[br-1][bu-1]=true;
								}
								if(bu+1<8 && tablata[br-1][bu+1].owner!=0)
								{
									if(tablata[br-1][bu+1].owner==2)
										giNapagjam[br-1][bu+1]=true;
									else
										giCuvam[br-1][bu+1]=true;;
								}
							}
						}
						else
						{
							if(br+1<8)
							{
								if(bu-1>=0 && tablata[br+1][bu-1].owner!=0)
								{
									if(tablata[br+1][bu-1].owner==1)
										giNapagjam[br+1][bu-1]=true;
									else
										giCuvam[br+1][bu-1]=false;
								}
								if(bu+1<8 && tablata[br+1][bu+1].owner!=0)
								{
									if(tablata[br+1][bu+1].owner==1)
										giNapagjam[br+1][bu+1]=true;
									else
										giCuvam[br+1][bu+1]=true;
								}
							}
						}
						break;

					case 5://====================================kralicata==================
						vrednost+=this->v_kralica;
					case 2://========================================top====================
						bool pomin;
						if(tablata[br][bu].tip==2)
							vrednost+=this->v_top;
						//za nadole
						i=br+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									giNapagjam[i][bu]=true;
								else
									giCuvam[i][bu]=true;
								pomin=false;
							}
							i++;
						};
						if(i-br>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						

						//za nagore
						i=br-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									giNapagjam[i][bu]=true;
								else
									giCuvam[i][bu]=true;
								pomin=false;
							}
							i--;
						}
						if(br-i>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za desno
						i=bu+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									giNapagjam[br][i]=true;
								else
									giCuvam[br][i]=true;
								pomin=false;
							}
							i++;
						};
						if(i-bu>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za levo
						i=bu-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									giNapagjam[br][i]=true;
								else
									giCuvam[br][i]=true;
								pomin=false;
							}
							i--;
						};
						if(bu-i>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						if(tablata[br][bu].tip==2)//====kralicata prodoluzva topot ne===
							break;
					case 4://============================================lanfer==========
						//za dole desno
						if(tablata[br][bu].tip==4)
							vrednost+=this->v_lanfer;
						i=br+1;
						j=bu+1;
						pomin=true;
						while(i<8 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i++;
							j++;
						};
						if(i-br>=this->u_otvorenost && j-bu>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za dole levo
						i=br+1;
						j=bu-1;
						pomin=true;
						while(i<8 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i++;
							j--;
						};
						if(i-br>=this->u_otvorenost && bu-j>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za gore desno
						i=br-1;
						j=bu+1;
						pomin=true;
						while(i>=0 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i--;
							j++;
						};
						if(br-i>=this->u_otvorenost && j-bu>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za gore levo
						i=br-1;
						j=bu-1;
						pomin=true;
						while(i>=0 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i--;
							j--;
						};
						if(br-i>=this->u_otvorenost && bu-j>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						break;
					case 3://==============================================konj=============
						vrednost+=this->v_konj;
						for(i=-2;i<=2;i++)
						{
							for(j=-2;j<=2;j++)
							{
								if(!(i==0 || j==0) && abs(i)!=abs(j))
								{
									if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
									{
										if(tablata[br+i][bu+j].owner!=0)
										{
											if(tablata[br+i][bu+j].owner==za_koj)
												giCuvam[br+i][bu+j]=true;
											else
												giNapagjam[br+i][bu+j]=true;
										}
									}
								}
							}
						}
						break;
					case 6://=======================================kral======================================
						//vrednost na kralevi ne se dodava bidejkji sekogas se dvata vo igra
						for(i=-1;i<=1;i++)
						{
							for(j=-1;j<=1;j++)
							{
								if(((br+i)<8 && (br+i)>=0 ) && ((bu+j)<8 && (bu+j)>=0) && (i!=0 && j!=0))
								{
									if(tablata[br+i][bu+j].owner!=0)
									{
										if(tablata[br+i][bu+j].owner==tablata[br][bu].owner)
											giCuvam[br+i][bu+j]=true;
										else
											giNapagjam[br+i][bu+j]=true;
									}
								}
							}
						}
						break;
					default:
						break;
					}
				}
				else
				{//ako figurata na BR, BU e na toj shto NE E NAred==========================
					//======================================================================

					switch(tablata[br][bu].tip)
					{
					case 0:
						break;
					case 1://============================================piun==============
						vrednost-=this->v_piun;
						if(tablata[br][bu].owner==1)
						{
							if(br-1>=0)
							{
								if(bu-1>=0 && tablata[br-1][bu-1].owner!=0)
								{
									if(tablata[br-1][bu-1].owner==2)
										miSePodNapad[br-1][bu-1]=true;
									else
										siGiCuva[br-1][bu-1]=true;
								}
								if(bu+1<8 && tablata[br-1][bu+1].owner!=0)
								{
									if(tablata[br-1][bu+1].owner==2)
										miSePodNapad[br-1][bu+1]=true;
									else
										siGiCuva[br-1][bu+1]=true;;
								}
							}
						}
						else
						{
							if(br+1<8)
							{
								if(bu-1>=0 && tablata[br+1][bu-1].owner!=0)
								{
									if(tablata[br+1][bu-1].owner==1)
										miSePodNapad[br+1][bu-1]=true;
									else
										siGiCuva[br+1][bu-1]=false;
								}
								if(bu+1<8 && tablata[br+1][bu+1].owner!=0)
								{
									if(tablata[br+1][bu+1].owner==1)
										miSePodNapad[br+1][bu+1]=true;
									else
										siGiCuva[br+1][bu+1]=true;
								}
							}
						}
						break;

					case 5://====================================kralicata==================
						vrednost-=this->v_kralica;
					case 2://========================================top====================
						bool pomin;
						if(tablata[br][bu].tip==2)
							vrednost-=this->v_top;
						//za nadole
						i=br+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									miSePodNapad[i][bu]=true;
								else
									siGiCuva[i][bu]=true;
								pomin=false;
							}
							i++;
						};

						//za nagore
						i=br-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									miSePodNapad[i][bu]=true;
								else
									siGiCuva[i][bu]=true;
								pomin=false;
							}
							i--;
						}
						//za desno
						i=bu+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									miSePodNapad[br][i]=true;
								else
									siGiCuva[br][i]=true;
								pomin=false;
							}
							i++;
						};
						//za levo
						i=bu-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									miSePodNapad[br][i]=true;
								else
									siGiCuva[br][i]=true;
								pomin=false;
							}
							i--;
						};
						if(tablata[br][bu].tip==2)//====kralicata prodoluzva topot ne===
							break;
					case 4://============================================lanfer==========
						//za dole desno
						if(tablata[br][bu].tip==4)
							vrednost-=this->v_lanfer;
						i=br+1;
						j=bu+1;
						pomin=true;
						while(i<8 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i++;
							j++;
						};
						//za dole levo
						i=br+1;
						j=bu-1;
						pomin=true;
						while(i<8 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i++;
							j--;
						};
						//za gore desno
						i=br-1;
						j=bu+1;
						pomin=true;
						while(i>=0 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i--;
							j++;
						};
						//za gore levo
						i=br-1;
						j=bu-1;
						pomin=true;
						while(i>=0 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i--;
							j--;
						};
						break;
					case 3://==============================================konj=============
						vrednost-=this->v_konj;
						for(i=-2;i<=2;i++)
						{
							for(j=-2;j<=2;j++)
							{
								if(!(i==0 || j==0) && abs(i)!=abs(j))
								{
									if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
									{
										if(tablata[br+i][bu+j].owner!=0)
										{
											if(tablata[br+i][bu+j].owner==za_koj)
												miSePodNapad[br+i][bu+j]=true;
											else
												siGiCuva[br+i][bu+j]=true;
										}
									}
								}
							}
						}
						break;
					case 6://=======================================kral======================================
						//vrednost na kralevi ne se dodava bidejkji sekogas se dvata vo igra
						for(i=-1;i<=1;i++)
						{
							for(j=-1;j<=1;j++)
							{
								if(((br+i)<8 && (br+i)>=0 ) && ((bu+j)<8 && (bu+j)>=0) && (i!=0 && j!=0))
								{
									if(tablata[br+i][bu+j].owner!=0)
									{
										if(tablata[br+i][bu+j].owner==tablata[br][bu].owner)
											siGiCuva[br+i][bu+j]=true;
										else
											miSePodNapad[br+i][bu+j]=true;
									}
								}
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}

		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if(miSePodNapad[i][j]==true)
				{
					if(giCuvam[i][j]==true)
						vrednost+=this->c_cuvanje;
					else//pod napad i ne go cuvam
						vrednost-=this->c_napad;
				}
				else//ne mi se pod napad
					if(giCuvam[i][j]==true)
						vrednost+=this->c_cuvanje;
				if(giNapagjam[i][j]==true)
				{
					if(siGiCuva[i][j]==true)
						vrednost+=this->c_cuvanje;
					else//go napagam i nishto ne go cuva
						vrednost+=this->c_napad;
				}
			}
		}

		return vrednost;
	};
	const void analizaVoDatoteka(int za_koj)
	{
		fstream dat;
		dat.open("alaniza.txt",ios::out);
		int vrednost=0;
		bool giCuvam[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		bool giNapagjam[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		bool miSePodNapad[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		bool siGiCuva[8][8]={{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false}};
		int i,j;

		for(int br=0;br<8;br++)
		{
			for(int bu=0;bu<8;bu++)
			{
				if(tablata[br][bu].owner==za_koj)
				{//ako figurata na BR, BU e na e na red====================================
					//=====================================================================

					switch(tablata[br][bu].tip)
					{
					case 0:
						break;
					case 1://============================================piun==============
						vrednost+=this->v_piun;
						if(tablata[br][bu].owner==1)
						{
							if(br-1>=0)
							{
								if(bu-1>=0 && tablata[br-1][bu-1].owner!=0)
								{
									if(tablata[br-1][bu-1].owner==2)
										giNapagjam[br-1][bu-1]=true;
									else
										giCuvam[br-1][bu-1]=true;
								}
								if(bu+1<8 && tablata[br-1][bu+1].owner!=0)
								{
									if(tablata[br-1][bu+1].owner==2)
										giNapagjam[br-1][bu+1]=true;
									else
										giCuvam[br-1][bu+1]=true;;
								}
							}
						}
						else
						{
							if(br+1<8)
							{
								if(bu-1>=0 && tablata[br+1][bu-1].owner!=0)
								{
									if(tablata[br+1][bu-1].owner==1)
										giNapagjam[br+1][bu-1]=true;
									else
										giCuvam[br+1][bu-1]=false;
								}
								if(bu+1<8 && tablata[br+1][bu+1].owner!=0)
								{
									if(tablata[br+1][bu+1].owner==1)
										giNapagjam[br+1][bu+1]=true;
									else
										giCuvam[br+1][bu+1]=true;
								}
							}
						}
						break;

					case 5://====================================kralicata==================
						vrednost+=this->v_kralica;
					case 2://========================================top====================
						bool pomin;
						if(tablata[br][bu].tip==2)
							vrednost+=this->v_top;
						//za nadole
						i=br+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									giNapagjam[i][bu]=true;
								else
									giCuvam[i][bu]=true;
								pomin=false;
							}
							i++;
						};
						if(i-br>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						

						//za nagore
						i=br-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									giNapagjam[i][bu]=true;
								else
									giCuvam[i][bu]=true;
								pomin=false;
							}
							i--;
						}
						if(br-i>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za desno
						i=bu+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									giNapagjam[br][i]=true;
								else
									giCuvam[br][i]=true;
								pomin=false;
							}
							i++;
						};
						if(i-bu>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za levo
						i=bu-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									giNapagjam[br][i]=true;
								else
									giCuvam[br][i]=true;
								pomin=false;
							}
							i--;
						};
						if(bu-i>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						if(tablata[br][bu].tip==2)//====kralicata prodoluzva topot ne===
							break;
					case 4://============================================lanfer==========
						//za dole desno
						if(tablata[br][bu].tip==4)
							vrednost+=this->v_lanfer;
						i=br+1;
						j=bu+1;
						pomin=true;
						while(i<8 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i++;
							j++;
						};
						if(i-br>=this->u_otvorenost && j-bu>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za dole levo
						i=br+1;
						j=bu-1;
						pomin=true;
						while(i<8 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i++;
							j--;
						};
						if(i-br>=this->u_otvorenost && bu-j>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za gore desno
						i=br-1;
						j=bu+1;
						pomin=true;
						while(i>=0 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i--;
							j++;
						};
						if(br-i>=this->u_otvorenost && j-bu>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						//za gore levo
						i=br-1;
						j=bu-1;
						pomin=true;
						while(i>=0 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									giNapagjam[i][j]=true;
								else
									giCuvam[i][j]=true;
								pomin=false;
							}
							i--;
							j--;
						};
						if(br-i>=this->u_otvorenost && bu-j>=this->u_otvorenost)
							vrednost+=c_otvorenost;
						break;
					case 3://==============================================konj=============
						vrednost+=this->v_konj;
						for(i=-2;i<=2;i++)
						{
							for(j=-2;j<=2;j++)
							{
								if(!(i==0 || j==0) && abs(i)!=abs(j))
								{
									if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
									{
										if(tablata[br+i][bu+j].owner!=0)
										{
											if(tablata[br+i][bu+j].owner==za_koj)
												giCuvam[br+i][bu+j]=true;
											else
												giNapagjam[br+i][bu+j]=true;
										}
									}
								}
							}
						}
						break;
					case 6://=======================================kral======================================
						//vrednost na kralevi ne se dodava bidejkji sekogas se dvata vo igra
						for(i=-1;i<=1;i++)
						{
							for(j=-1;j<=1;j++)
							{
								if(((br+i)<8 && (br+i)>=0 ) && ((bu+j)<8 && (bu+j)>=0) && (i!=0 && j!=0))
								{
									if(tablata[br+i][bu+j].owner!=0)
									{
										if(tablata[br+i][bu+j].owner==tablata[br][bu].owner)
											giCuvam[br+i][bu+j]=true;
										else
											giNapagjam[br+i][bu+j]=true;
									}
								}
							}
						}
						break;
					default:
						break;
					}
				}
				else
				{//ako figurata na BR, BU e na toj shto NE E NAred==========================
					//======================================================================

					switch(tablata[br][bu].tip)
					{
					case 0:
						break;
					case 1://============================================piun==============
						vrednost-=this->v_piun;
						if(tablata[br][bu].owner==1)
						{
							if(br-1>=0)
							{
								if(bu-1>=0 && tablata[br-1][bu-1].owner!=0)
								{
									if(tablata[br-1][bu-1].owner==2)
										miSePodNapad[br-1][bu-1]=true;
									else
										siGiCuva[br-1][bu-1]=true;
								}
								if(bu+1<8 && tablata[br-1][bu+1].owner!=0)
								{
									if(tablata[br-1][bu+1].owner==2)
										miSePodNapad[br-1][bu+1]=true;
									else
										siGiCuva[br-1][bu+1]=true;;
								}
							}
						}
						else
						{
							if(br+1<8)
							{
								if(bu-1>=0 && tablata[br+1][bu-1].owner!=0)
								{
									if(tablata[br+1][bu-1].owner==1)
										miSePodNapad[br+1][bu-1]=true;
									else
										siGiCuva[br+1][bu-1]=false;
								}
								if(bu+1<8 && tablata[br+1][bu+1].owner!=0)
								{
									if(tablata[br+1][bu+1].owner==1)
										miSePodNapad[br+1][bu+1]=true;
									else
										siGiCuva[br+1][bu+1]=true;
								}
							}
						}
						break;

					case 5://====================================kralicata==================
						vrednost-=this->v_kralica;
					case 2://========================================top====================
						bool pomin;
						if(tablata[br][bu].tip==2)
							vrednost-=this->v_top;
						//za nadole
						i=br+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									miSePodNapad[i][bu]=true;
								else
									siGiCuva[i][bu]=true;
								pomin=false;
							}
							i++;
						};

						//za nagore
						i=br-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[i][bu].owner!=0)
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									miSePodNapad[i][bu]=true;
								else
									siGiCuva[i][bu]=true;
								pomin=false;
							}
							i--;
						}
						//za desno
						i=bu+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									miSePodNapad[br][i]=true;
								else
									siGiCuva[br][i]=true;
								pomin=false;
							}
							i++;
						};
						//za levo
						i=bu-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[br][i].owner!=0)
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									miSePodNapad[br][i]=true;
								else
									siGiCuva[br][i]=true;
								pomin=false;
							}
							i--;
						};
						if(tablata[br][bu].tip==2)//====kralicata prodoluzva topot ne===
							break;
					case 4://============================================lanfer==========
						//za dole desno
						if(tablata[br][bu].tip==4)
							vrednost-=this->v_lanfer;
						i=br+1;
						j=bu+1;
						pomin=true;
						while(i<8 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i++;
							j++;
						};
						//za dole levo
						i=br+1;
						j=bu-1;
						pomin=true;
						while(i<8 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i++;
							j--;
						};
						//za gore desno
						i=br-1;
						j=bu+1;
						pomin=true;
						while(i>=0 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i--;
							j++;
						};
						//za gore levo
						i=br-1;
						j=bu-1;
						pomin=true;
						while(i>=0 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner!=0)
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									miSePodNapad[i][j]=true;
								else
									siGiCuva[i][j]=true;
								pomin=false;
							}
							i--;
							j--;
						};
						break;
					case 3://==============================================konj=============
						vrednost-=this->v_konj;
						for(i=-2;i<=2;i++)
						{
							for(j=-2;j<=2;j++)
							{
								if(!(i==0 || j==0) && abs(i)!=abs(j))
								{
									if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
									{
										if(tablata[br+i][bu+j].owner!=0)
										{
											if(tablata[br+i][bu+j].owner==za_koj)
												miSePodNapad[br+i][bu+j]=true;
											else
												siGiCuva[br+i][bu+j]=true;
										}
									}
								}
							}
						}
						break;
					case 6://=======================================kral======================================
						//vrednost na kralevi ne se dodava bidejkji sekogas se dvata vo igra
						for(i=-1;i<=1;i++)
						{
							for(j=-1;j<=1;j++)
							{
								if(((br+i)<8 && (br+i)>=0 ) && ((bu+j)<8 && (bu+j)>=0) && (i!=0 && j!=0))
								{
									if(tablata[br+i][bu+j].owner!=0)
									{
										if(tablata[br+i][bu+j].owner==tablata[br][bu].owner)
											siGiCuva[br+i][bu+j]=true;
										else
											miSePodNapad[br+i][bu+j]=true;
									}
								}
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}

		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if(miSePodNapad[i][j]==true)
				{
					if(giCuvam[i][j]==true)
						vrednost+=this->c_cuvanje;
					else//pod napad i ne go cuvam
						vrednost-=(int)tip_vo_vrednost(tablata[i][j].tip)*(1-this->c_napad);
				}
				else//ne mi se pod napad
					if(giCuvam[i][j]==true)
						vrednost+=this->c_cuvanje;
				if(giNapagjam[i][j]==true)
				{
					if(siGiCuva[i][j]==true)
						vrednost+=this->c_cuvanje;
					else//go napagam i nishto ne go cuva
						vrednost+=(int)tip_vo_vrednost(tablata[i][j].tip)*this->c_napad;
				}
			}
		}

		dat<<"vrednosta e: "<<vrednost<<endl;
		dat<<"tabela na pozicii shto gi napagja e:"<<endl;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
				(giNapagjam[i][j]==true)?dat<<"X ":dat<<"0 ";
			dat<<endl;
		}
		dat<<endl<<"tabela na pozicii shto gi cuva e:"<<endl;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
				(giCuvam[i][j]==true)?dat<<"X ":dat<<"0 ";
			dat<<endl;
		}
		dat<<endl<<"tabela na pozicii shto mu gi napagjaat e:"<<endl;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
				(miSePodNapad[i][j]==true)?dat<<"X ":dat<<"0 ";
			dat<<endl;
		}
		dat<<endl<<"tabela na pozicii shto protivnikot si gi cuva e:"<<endl;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
				(siGiCuva[i][j]==true)?dat<<"X ":dat<<"0 ";
			dat<<endl;
		}
	};
	const bool pod_napad(int br,int bu,int za_koj,int bez_br,int bez_bu)
	{
	/*	figura tmp;
		tmp=tablata[bez_br][bez_bu];
		tablata[bez_br][bez_bu]=prazno;
		bool vrakjanje;
		vrakjanje=pod_napad(br,bu,za_koj);
		tablata[bez_br][bez_bu]=tmp;
		return vrakjanje;*/
		tabla tmp;
		tmp=(*this);
		tmp.tablata[bez_br][bez_bu]=prazno;
		return tmp.pod_napad(br,bu,za_koj);
	};
	const bool pod_napad(int br,int bu,int za_koj)
	{
		bool napad;
		napad=false;
		bool pomin;
		int i,j;
		// za kral++++++++++++++++++++++++++++++++++++++++++++++++++
		for(i=-1;i<=1;i++)
		{
			for(j=-1;j<=1;j++)
			{
				if((br+i)<8 && (br+i)>=0 && (bu+j)<8 && (bu+j)>=0)
					if(za_koj!=tablata[br+i][bu+j].owner && tablata[br+i][bu+j].tip==6)
						return true;

			}
		}
		//za piun+++++++++++++++++++++++++++++++++++++++++++++++++++++
		if(za_koj==1)
		{
			if(br-1>=0)
			{
				if(bu-1>=0)
					if(tablata[br-1][bu-1].owner==2 && tablata[br-1][bu-1].tip==1)
						return true;
				if(bu+1>=0)
					if(tablata[br-1][bu+1].owner==2 && tablata[br-1][bu+1].tip==1)
						return true;

			}
		}
		else
		{
			if(br+1<8)
			{
				if(bu-1>=0)
					if(tablata[br+1][bu-1].owner==1 && tablata[br+1][bu-1].tip==1)
						return true;
				if(bu+1>=0)
					if(tablata[br+1][bu+1].owner==1 && tablata[br+1][bu+1].tip==1)
						return true;

			}
		}

		//za konj++++++++++++++++++++++++++++++++++++++++++++++++++
		for(i=-2;i<=2;i++)
		{
			for(j=-2;j<=2;j++)
			{
				if(!(i==0 || j==0) && abs(i)!=abs(j))
				{
					if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
						if(tablata[br+i][bu+j].owner!=za_koj && tablata[br+i][bu+j].tip==3)
							return true;
				}
			}
		}


		//za kralica top i lanfer+++++++++++++++++++++++++++++++++++
		//za dole
		i=br+1;
		pomin=true;
		while(i<8 && pomin==true)
		{
			if(tablata[i][bu].owner!=0)
			{
				if(tablata[i][bu].owner!=za_koj && (tablata[i][bu].tip==2 || tablata[i][bu].tip==5))
					return true;
				pomin=false;
			}
			i++;
		}
		//za gore
		i=br-1;
		pomin=true;
		while(i>=0 && pomin==true)
		{
			if(tablata[i][bu].owner!=0)
			{
				if(tablata[i][bu].owner!=za_koj && (tablata[i][bu].tip==2 || tablata[i][bu].tip==5))
					return true;
				pomin=false;
			}
			i--;
		}
		//za levo
		i=bu-1;
		pomin=true;
		while(i>=0 && pomin==true)
		{
			if(tablata[br][i].owner!=0)
			{
				if(tablata[br][i].owner!=za_koj && (tablata[br][i].tip==2 || tablata[br][i].tip==5))
					return true;
				pomin=false;
			}
			i--;
		}
		//za desno
		i=bu+1;
		pomin=true;
		while(i<8 && pomin==true)
		{
			if(tablata[br][i].owner!=0)
			{
				if(tablata[br][i].owner!=za_koj && (tablata[br][i].tip==2 || tablata[br][i].tip==5))
					return true;
				pomin=false;
			}
			i++;
		}
		//za dole desno
		i=br+1;
		j=bu+1;
		pomin=true;
		while(i<8 && j<8 && pomin==true)
		{
			if(tablata[i][j].owner!=0)
			{
				if(tablata[i][j].owner!=za_koj && (tablata[i][j].tip==4 || tablata[i][j].tip==5))
					return true;
				pomin=false;
			}
			i++;
			j++;
		}
		//za dole levo
		i=br+1;
		j=bu-1;
		pomin=true;
		while(i<8 && j>=0 && pomin==true)
		{
			if(tablata[i][j].owner!=0)
			{
				if(tablata[i][j].owner!=za_koj && (tablata[i][j].tip==4 || tablata[i][j].tip==5))
					return true;
				pomin=false;
			}
			i++;
			j--;
		}
		//za gore desno
		i=br-1;
		j=bu+1;
		pomin=true;
		while(i>=0 && j<8 && pomin==true)
		{
			if(tablata[i][j].owner!=0)
			{
				if(tablata[i][j].owner!=za_koj && (tablata[i][j].tip==4 || tablata[i][j].tip==5))
					return true;
				pomin=false;
			}
			i--;
			j++;
		}
		//za gore levo
		i=br-1;
		j=bu-1;
		pomin=true;
		while(i>=0 && j>=0 && pomin==true)
		{
			if(tablata[i][j].owner!=0)
			{
				if(tablata[i][j].owner!=za_koj && (tablata[i][j].tip==4 || tablata[i][j].tip==5))
					return true;
				pomin=false;
			}
			i--;
			j--;
		}
		return false;
	};
	void poteg(int odbr,int odbu,int dobr,int dobu)
	{
		//rokada
		if(tablata[odbr][odbu].pomesteno==false && tablata[dobr][dobu].pomesteno==false && tablata[odbr][odbu].tip==6 && tablata[dobr][dobu].tip==2 && tablata[dobr][dobu].owner==tablata[odbr][odbu].owner)
		{
			if(dobu==0)
			{
				std::swap(tablata[odbr][odbu],tablata[odbr][odbu-2]);
				std::swap(tablata[dobr][dobu],tablata[dobr][odbu-1]);
			}
			if(dobu==7)
			{

				std::swap(tablata[odbr][odbu],tablata[odbr][odbu+2]);
				std::swap(tablata[dobr][dobu],tablata[dobr][odbu+1]);
			}
		}
		else
		{

			//unapreduvanje
			if( tablata[odbr][odbu].tip==1 && ( (tablata[odbr][odbu].owner==1 && dobr==0) || (tablata[odbr][odbu].owner==2 && dobr==7) ) )
			{				
				tablata[dobr][dobu].owner=tablata[odbr][odbu].owner;
				tablata[dobr][dobu].tip=this->unapreduvanje;
				tablata[odbr][odbu].owner=0;
				tablata[odbr][odbu].tip=0;
				tablata[odbr][odbu].mozni.clear();
				tablata[dobr][dobu].mozni.clear();
			}
			//obichen poteg
			else
			{
				 std::swap(tablata[dobr][dobu],tablata[odbr][odbu]);
				 tablata[odbr][odbu]=prazno;
				 tablata[dobr][dobu].pomesteno=true;
			}
		}
	};
	void gen_mozni(int br,int bu)
	{
		int i,j;
		tablata[br][bu].mozni.clear();
		int kral_br;
		int kral_bu;

		switch(tablata[br][bu].tip)
		{
		case 0:
			break;
		case 1://============================================piun==============
			if(tablata[br][bu].owner==1)
			{
				if(br-1>=0)
				{
					if(tablata[br-1][bu].owner==0)
					{
						tablata[br][bu].mozni.push_back(poz(br-1,bu,0));
						if(br==6)
							if(tablata[br-2][bu].owner==0)
								tablata[br][bu].mozni.push_back(poz(br-2,bu,0));
					}
					if(bu-1>=0)
						if(tablata[br-1][bu-1].owner==2)
							tablata[br][bu].mozni.push_back(poz(br-1,bu-1,0));
					if(bu+1<8)
						if(tablata[br-1][bu+1].owner==2)
							tablata[br][bu].mozni.push_back(poz(br-1,bu+1,0));
				}
			}
			else
			{
				if(br+1<8)
				{
					if(tablata[br+1][bu].owner==0)
					{
						tablata[br][bu].mozni.push_back(poz(br+1,bu,0));
						if(br==1)
							if(tablata[br+2][bu].owner==0)
								tablata[br][bu].mozni.push_back(poz(br+2,bu,0));
					}
					if(bu-1>=0)
						if(tablata[br+1][bu-1].owner==1)
							tablata[br][bu].mozni.push_back(poz(br+1,bu-1,0));
					if(bu+1<8)
						if(tablata[br+1][bu+1].owner==1)
							tablata[br][bu].mozni.push_back(poz(br+1,bu+1,0));

				}
			}
			break;

		case 5://====================================kralicata==================
		case 2://========================================top====================
			bool pomin;
			
			//za nadole
			i=br+1;
			pomin=true;
			while(i<8 && pomin==true)
			{
				if(tablata[i][bu].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(i,bu,0));
				}
				else
				{
					if(tablata[i][bu].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(i,bu,0));
					pomin=false;
				}
				i++;
			};

			//za nagore
			i=br-1;
			pomin=true;
			while(i>=0 && pomin==true)
			{
				if(tablata[i][bu].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(i,bu,0));
				}
				else
				{
					if(tablata[i][bu].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(i,bu,0));
					pomin=false;
				}
				i--;
			}
			//za desno
			i=bu+1;
			pomin=true;
			while(i<8 && pomin==true)
			{
				if(tablata[br][i].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(br,i,0));
				}
				else
				{
					if(tablata[br][i].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(br,i,0));
					pomin=false;
				}
				i++;
			};
			//za levo
			i=bu-1;
			pomin=true;
			while(i>=0 && pomin==true)
			{
				if(tablata[br][i].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(br,i,0));
				}
				else
				{
					if(tablata[br][i].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(br,i,0));
					pomin=false;
				}
				i--;
			};
			if(tablata[br][bu].tip==2)//====kralicata prodoluzva topot ne===
				break;
		case 4://============================================lanfer==========
			//za dole desno
			i=br+1;
			j=bu+1;
			pomin=true;
			while(i<8 && j<8 && pomin==true)
			{
				if(tablata[i][j].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(i,j,0));
				}
				else
				{
					if(tablata[i][j].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(i,j,0));
					pomin=false;
				}
				i++;
				j++;
			};
			//za dole levo
			i=br+1;
			j=bu-1;
			pomin=true;
			while(i<8 && j>=0 && pomin==true)
			{
				if(tablata[i][j].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(i,j,0));
				}
				else
				{
					if(tablata[i][j].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(i,j,0));
					pomin=false;
				}
				i++;
				j--;
			};
			//za gore desno
			i=br-1;
			j=bu+1;
			pomin=true;
			while(i>=0 && j<8 && pomin==true)
			{
				if(tablata[i][j].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(i,j,0));
				}
				else
				{
					if(tablata[i][j].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(i,j,0));
					pomin=false;
				}
				i--;
				j++;
			};
			//za gore levo
			i=br-1;
			j=bu-1;
			pomin=true;
			while(i>=0 && j>=0 && pomin==true)
			{
				if(tablata[i][j].owner==0)
				{
					tablata[br][bu].mozni.push_back(poz(i,j,0));
				}
				else
				{
					if(tablata[i][j].owner!=tablata[br][bu].owner)
						tablata[br][bu].mozni.push_back(poz(i,j,0));
					pomin=false;
				}
				i--;
				j--;
			};
			break;
		case 3://==============================================konj=============
			for(i=-2;i<=2;i++)
			{
				for(j=-2;j<=2;j++)
				{
					if(!(i==0 || j==0) && abs(i)!=abs(j))
					{
						if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
							if(tablata[br+i][bu+j].owner!=tablata[br][bu].owner)
								tablata[br][bu].mozni.push_back(poz(br+i,bu+j,0));
					}
				}
			}
			break;
		case 6://=======================================kral======================================
			for(i=-1;i<=1;i++)
			{
				for(j=-1;j<=1;j++)
				{
					if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
						if(pod_napad(br+i,bu+j,tablata[br][bu].owner,br,bu)==false && tablata[br][bu].owner!=tablata[br+i][bu+j].owner)
							tablata[br][bu].mozni.push_back(poz(br+i,bu+j,0));

				}
			}
			if(tablata[br][bu].pomesteno==false)
			{
				if(bu==4)
				{
					if(tablata[br][0].tip==2 && tablata[br][0].pomesteno==false && tablata[br][1].tip==0 && tablata[br][2].tip==0 && tablata[br][3].tip==0)
						if(pod_napad(br,0,tablata[br][bu].owner)==false && pod_napad(br,1,tablata[br][bu].owner)==false && pod_napad(br,2,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner)==false)
							tablata[br][bu].mozni.push_back(poz(br,0,0));
					if(tablata[br][7].tip==2 && tablata[br][7].pomesteno==false && tablata[br][6].tip==0 && tablata[br][5].tip==0)
						if(pod_napad(br,7,tablata[br][bu].owner)==false && pod_napad(br,6,tablata[br][bu].owner)==false && pod_napad(br,5,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner)==false)
							tablata[br][bu].mozni.push_back(poz(br,7,0));
				}
				if(bu==3)
				{
					if(tablata[br][0].tip==2 && tablata[br][0].pomesteno==false && tablata[br][1].tip==0 && tablata[br][2].tip==0)
						if(pod_napad(br,0,tablata[br][bu].owner)==false && pod_napad(br,1,tablata[br][bu].owner)==false && pod_napad(br,2,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false)
							tablata[br][bu].mozni.push_back(poz(br,0,0));
					if(tablata[br][7].tip==2 && tablata[br][7].pomesteno==false && tablata[br][6].tip==0 && tablata[br][5].tip==0 && tablata[br][4].tip==0)
						if(pod_napad(br,7,tablata[br][bu].owner)==false && pod_napad(br,6,tablata[br][bu].owner)==false && pod_napad(br,5,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false)
							tablata[br][bu].mozni.push_back(poz(br,7,0));
				}
			}
			break;
		default:
			break;
		}

		//proverka za dali ke bide napadnat kralot
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				if(tablata[i][j].owner==tablata[br][bu].owner && tablata[i][j].tip==6)
				{
					kral_br=i;
					kral_bu=j;
				}
			}
		}
		if(tablata[br][bu].tip!=6)
		{
			for(i=tablata[br][bu].mozni.size()-1;i>=0;i--)
			{
				tabla tmp=*this;
				poz pozicija=tablata[br][bu].mozni.front();
				tablata[br][bu].mozni.pop_front();
				tmp.poteg(br,bu,pozicija.br,pozicija.bu);
				if(tmp.pod_napad(kral_br,kral_bu,tablata[br][bu].owner)==false)
					tablata[br][bu].mozni.push_back(pozicija);
			}
		}

	};

	int gen_site_mozni(int za_koj)//go vrakja brojot na site mozni, i gi stava moznite pozicii vo figurite
	{
		
		//
		int i,j;
		int num=0;
		//za kade se naogja kralot
		int kral_br;
		int kral_bu;
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				if(tablata[i][j].owner==za_koj && tablata[i][j].tip==6)
				{
					kral_br=i;
					kral_bu=j;
				}
			}
		}


		for(int br=0;br<8;br++)
		{
			for(int bu=0;bu<8;bu++)
			{
				if(tablata[br][bu].owner==za_koj)
				{
					tablata[br][bu].mozni.clear();
					switch(tablata[br][bu].tip)
					{
					case 0:
						break;
					case 1://============================================piun==============
						if(tablata[br][bu].owner==1)
						{
							if(br-1>=0)
							{
								if(tablata[br-1][bu].owner==0)
								{
									tablata[br][bu].mozni.push_back(poz(br-1,bu,0));
									if(br==6)
										if(tablata[br-2][bu].owner==0)
											tablata[br][bu].mozni.push_back(poz(br-2,bu,0));
								}
								if(bu-1>=0)
									if(tablata[br-1][bu-1].owner==2)
										tablata[br][bu].mozni.push_back(poz(br-1,bu-1,0));
								if(bu+1<8)
									if(tablata[br-1][bu+1].owner==2)
										tablata[br][bu].mozni.push_back(poz(br-1,bu+1,0));
							}
						}
						else
						{
							if(br+1<8)
							{
								if(tablata[br+1][bu].owner==0)
								{
									tablata[br][bu].mozni.push_back(poz(br+1,bu,0));
									if(br==1)
										if(tablata[br+2][bu].owner==0)
											tablata[br][bu].mozni.push_back(poz(br+2,bu,0));
								}
								if(bu-1>=0)
									if(tablata[br+1][bu-1].owner==1)
										tablata[br][bu].mozni.push_back(poz(br+1,bu-1,0));
								if(bu+1<8)
									if(tablata[br+1][bu+1].owner==1)
										tablata[br][bu].mozni.push_back(poz(br+1,bu+1,0));

							}
						}
						break;

					case 5://====================================kralicata==================
					case 2://========================================top====================
						bool pomin;
						
						//za nadole
						i=br+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[i][bu].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(i,bu,0));
							}
							else
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(i,bu,0));
								pomin=false;
							}
							i++;
						};

						//za nagore
						i=br-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[i][bu].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(i,bu,0));
							}
							else
							{
								if(tablata[i][bu].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(i,bu,0));
								pomin=false;
							}
							i--;
						}
						//za desno
						i=bu+1;
						pomin=true;
						while(i<8 && pomin==true)
						{
							if(tablata[br][i].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(br,i,0));
							}
							else
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(br,i,0));
								pomin=false;
							}
							i++;
						};
						//za levo
						i=bu-1;
						pomin=true;
						while(i>=0 && pomin==true)
						{
							if(tablata[br][i].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(br,i,0));
							}
							else
							{
								if(tablata[br][i].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(br,i,0));
								pomin=false;
							}
							i--;
						};
						if(tablata[br][bu].tip==2)//====kralicata prodoluzva topot ne===
							break;
					case 4://============================================lanfer==========
						//za dole desno
						i=br+1;
						j=bu+1;
						pomin=true;
						while(i<8 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(i,j,0));
							}
							else
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(i,j,0));
								pomin=false;
							}
							i++;
							j++;
						};
						//za dole levo
						i=br+1;
						j=bu-1;
						pomin=true;
						while(i<8 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(i,j,0));
							}
							else
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(i,j,0));
								pomin=false;
							}
							i++;
							j--;
						};
						//za gore desno
						i=br-1;
						j=bu+1;
						pomin=true;
						while(i>=0 && j<8 && pomin==true)
						{
							if(tablata[i][j].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(i,j,0));
							}
							else
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(i,j,0));
								pomin=false;
							}
							i--;
							j++;
						};
						//za gore levo
						i=br-1;
						j=bu-1;
						pomin=true;
						while(i>=0 && j>=0 && pomin==true)
						{
							if(tablata[i][j].owner==0)
							{
								tablata[br][bu].mozni.push_back(poz(i,j,0));
							}
							else
							{
								if(tablata[i][j].owner!=tablata[br][bu].owner)
									tablata[br][bu].mozni.push_back(poz(i,j,0));
								pomin=false;
							}
							i--;
							j--;
						};
						break;
					case 3://==============================================konj=============
						for(i=-2;i<=2;i++)
						{
							for(j=-2;j<=2;j++)
							{
								if(!(i==0 || j==0) && abs(i)!=abs(j))
								{
									if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
										if(tablata[br+i][bu+j].owner!=tablata[br][bu].owner)
											tablata[br][bu].mozni.push_back(poz(br+i,bu+j,0));
								}
							}
						}
						break;
					case 6://=======================================kral======================================
						for(i=-1;i<=1;i++)
						{
							for(j=-1;j<=1;j++)
							{
								if(((br+i)<8 && (br+i)>=0 )&& ((bu+j)<8 && (bu+j)>=0))
									if(pod_napad(br+i,bu+j,tablata[br][bu].owner,br,bu)==false && tablata[br][bu].owner!=tablata[br+i][bu+j].owner)
										tablata[br][bu].mozni.push_back(poz(br+i,bu+j,0));

							}
						}
						if(tablata[br][bu].pomesteno==false)
						{


							if(bu==4)
							{
								if(tablata[br][0].tip==2 && tablata[br][0].pomesteno==false && tablata[br][1].tip==0 && tablata[br][2].tip==0 && tablata[br][3].tip==0)
									if(pod_napad(br,0,tablata[br][bu].owner)==false && pod_napad(br,1,tablata[br][bu].owner)==false && pod_napad(br,2,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner)==false)
										tablata[br][bu].mozni.push_back(poz(br,0,0));
								if(tablata[br][7].tip==2 && tablata[br][7].pomesteno==false && tablata[br][6].tip==0 && tablata[br][5].tip==0)
									if(pod_napad(br,7,tablata[br][bu].owner)==false && pod_napad(br,6,tablata[br][bu].owner)==false && pod_napad(br,5,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner)==false)
										tablata[br][bu].mozni.push_back(poz(br,7,0));
							}
							if(bu==3)
							{
								if(tablata[br][0].tip==2 && tablata[br][0].pomesteno==false && tablata[br][1].tip==0 && tablata[br][2].tip==0)
									if(pod_napad(br,0,tablata[br][bu].owner)==false && pod_napad(br,1,tablata[br][bu].owner)==false && pod_napad(br,2,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false)
										tablata[br][bu].mozni.push_back(poz(br,0,0));
								if(tablata[br][7].tip==2 && tablata[br][7].pomesteno==false && tablata[br][6].tip==0 && tablata[br][5].tip==0 && tablata[br][4].tip==0)
									if(pod_napad(br,7,tablata[br][bu].owner)==false && pod_napad(br,6,tablata[br][bu].owner)==false && pod_napad(br,5,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false)
										tablata[br][bu].mozni.push_back(poz(br,7,0));
							}


							/*
							if(tablata[br][0].tip==2 && tablata[br][0].pomesteno==false && tablata[br][0].owner==tablata[br][bu].owner && pod_napad(br,2,tablata[br][bu].owner)==false && pod_napad(br,3,tablata[br][bu].owner)==false && pod_napad(br,4,tablata[br][bu].owner,br,bu)==false && tablata[br][1].owner==0 && tablata[br][2].owner==0 && tablata[br][3].owner==0)
								tablata[br][bu].mozni.push_back(poz(br,0,0));
							if(tablata[br][7].tip==2 && tablata[br][7].pomesteno==false && tablata[br][7].owner==tablata[br][bu].owner && pod_napad(br,4,tablata[br][bu].owner,br,bu)==false && pod_napad(br,5,tablata[br][bu].owner)==false && pod_napad(br,6,tablata[br][bu].owner)==false  && tablata[br][5].owner==0 && tablata[br][6].owner==0)
								tablata[br][bu].mozni.push_back(poz(br,7,0));*/
						}
						break;
					default:
						break;
					}

					//proverka za dali ke bide napadnat kralot
					if(tablata[br][bu].tip!=6)
					{
						for(i=tablata[br][bu].mozni.size()-1;i>=0;i--)
						{
							tabla tmp=*this;
							poz pozicija=tablata[br][bu].mozni.front();
							tablata[br][bu].mozni.pop_front();
							tmp.poteg(br,bu,pozicija.br,pozicija.bu);
							if(tmp.pod_napad(kral_br,kral_bu,tablata[br][bu].owner)==false)
								tablata[br][bu].mozni.push_back(pozicija);
						}
					}
					num+=tablata[br][bu].mozni.size();
				}
			}
		}
		return num;
	};
	const void gen_pat_mat(int za_koj)//0 za dvajcata
	{
		int i,j;
		bool test;
		int kral_br;
		int kral_bu;
		switch(za_koj)
		{
			//od tuka za igrach 1
		case 0:
		case 1:
			test=false;//ke bide false akko igrachot nemoze da napravi poteg
			for(i=0;i<8 && test!=true;i++)
			{
				for(j=0;j<8 && test!=true;j++)
				{
					if(tablata[i][j].owner==1)
					{
						this->gen_mozni(i,j);
						if(tablata[i][j].mozni.size()>0)
							test=true;
					}
				}
			}
			if(test==false)
			{
				for(i=0;i<8;i++)
				{
					for(j=0;j<8;j++)
					{
						if(tablata[i][j].owner==1 && tablata[i][j].tip==6)
						{
							kral_br=i;
							kral_bu=j;
						}
					}
				}
				if(pod_napad(kral_br,kral_bu,1)==true)
				{
					mat_i1=true;
					pat_i1=false;
				}
				else
				{
					pat_i1=true;
					mat_i1=false;
				}
			}
			else
			{
				pat_i1=false;
				mat_i1=false;
			}
			if(za_koj==1)
				break;
		case 2:
			test=false;//ke bide false akko igrachot nemoze da napravi poteg
			for(i=0;i<8 && test!=true;i++)
			{
				for(j=0;j<8 && test!=true;j++)
				{
					if(tablata[i][j].owner==2)
					{
						this->gen_mozni(i,j);
						if(tablata[i][j].mozni.size()>0)
							test=true;
					}
				}
			}
			if(test==false)
			{
				for(i=0;i<8;i++)
				{
					for(j=0;j<8;j++)
					{
						if(tablata[i][j].owner==2 && tablata[i][j].tip==6)
						{
							kral_br=i;
							kral_bu=j;
						}
					}
				}
				if(pod_napad(kral_br,kral_bu,2)==true)
				{
					mat_i2=true;
					pat_i2=false;
				}
				else
				{
					pat_i2=true;
					mat_i2=false;
				}
			}
			else
			{
				pat_i2=false;
				mat_i2=false;
			}
			break;
		}
	};
	const void gen_pat_mat()
	{
		gen_pat_mat(0);
	};
	const int tip_vo_vrednost(int tip){
		switch(tip){
			case 0:
				return 0;
			case 1:
				return this->v_piun;
			case 2:
				return this->v_top;
			case 3:
				return this->v_konj;
			case 4:
				return this->v_lanfer;
			case 5:
				return this->v_kralica;
			case 6:
				return this->v_kral;
		}
	};
};


#endif