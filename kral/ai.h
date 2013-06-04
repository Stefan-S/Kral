#include "tabla.h"
//#include <iostream>
//#include <fstream>
//using namespace std;

#ifndef AI_H
#define AI_H

public ref class VINode{
private:
	//input
	int za_koj;
	int red;
	tabla *tab;
	int depth;
	int ova;
	int pred;

	//output
	int rez;
public:
	int odBR;
	int odBU;
	int doBR;
	int doBU;
	const int zemiRez(){
		return rez;
	}
	VINode(int _za_koj,int _red,tabla* _tab,int _depth,int _ova,int _pred){
		this->za_koj=_za_koj;
		this->red=_red;
		this->tab=_tab;
		this->depth=_depth;
		this->ova=_ova;
		this->pred=_pred;
		this->rez=-10000000;
	}
	VINode(VINode% obj){
		this->za_koj=obj.za_koj;
		this->red=obj.red;
		this->tab=obj.tab;
		this->depth=obj.depth;
		this->rez=obj.rez;
		this->ova=obj.ova;
		this->pred=obj.pred;
	}
	void exec(/*System::Object ^state*/){
//		System::Threading::AutoResetEvent^ autoReset=(System::Threading::AutoResetEvent^)state;
		tabla baza=*tab;
		int prodolzuvanje=0;
		if(depth>0)
		{
			if(za_koj==red)
			{//BIRAME MAXIMALNA VREDNOST
				baza.gen_site_mozni(za_koj);
				int tmp;
				tabla nova;
				bool prune=false;
				for(int i=0;i<8 && prune==false;i++)
				{
					for(int j=0;j<8;j++)
					{
						if(za_koj==baza.tablata[i][j].owner)
						{
							int size=baza.tablata[i][j].mozni.size();
							if(size>0)
							{
								for(int k=size-1;k>=0;k--)
								{	
									nova=baza;
									if(nova.tablata[baza.tablata[i][j].mozni[k].br][baza.tablata[i][j].mozni[k].bu].owner==3-za_koj)
										prodolzuvanje=1;
									else
										prodolzuvanje=0;
									nova.poteg(i,j,baza.tablata[i][j].mozni[k].br,baza.tablata[i][j].mozni[k].bu);
									//if(TabeliNaTranspozicija(tab)!=-10000000)
									//	return TabeliNaTranspozicija(tab)
									//else
									tmp=vi(3-za_koj,red,&nova,prodolzuvanje+depth-1,10000000,ova);
									if(tmp>ova)
										ova=tmp;

									//za MAX
									if(pred>=ova)
										prune=true;
								}
							}
						}
					}
				}
				this->rez=ova;
			}
			else
			{//BIRAME MINIMALNA VREDNOST
				baza.gen_site_mozni(za_koj);
				int tmp;
				tabla nova;
				bool prune=false;
				for(int i=0;i<8 && prune==false;i++)
				{
					for(int j=0;j<8;j++)
					{
						if(za_koj==baza.tablata[i][j].owner)
						{
							int size=baza.tablata[i][j].mozni.size();
							if(size>0)
							{
								for(int k=size-1;k>=0;k--)
								{	
									nova=baza;
									if(nova.tablata[baza.tablata[i][j].mozni[k].br][baza.tablata[i][j].mozni[k].bu].owner==3-za_koj)
										prodolzuvanje=1;
									else
										prodolzuvanje=0;
									nova.poteg(i,j,baza.tablata[i][j].mozni[k].br,baza.tablata[i][j].mozni[k].bu);
									//if(TabeliNaTranspozicija(tab)!=-10000000)
									//	return TabeliNaTranspozicija(tab)
									//else
									tmp=vi(3-za_koj,red,&nova,prodolzuvanje+depth-1,-10000000,ova);
									if(tmp<ova)
										ova=tmp;
						
									//za MIN
									if(pred<=ova)
										prune=true;
								}
							}
						}
					}
				}
				this->rez=ova;
			}
		}else{
			this->rez=baza.procenka_bez_gen(red);
		}
		
	//	autoReset->Set();
	//	System::Threading::Thread::Sleep(0);
	}
	static const int vi(int za_koj,int red,tabla* tab,int depth,int ova,int pred){
		tabla baza=*tab;
		int prodolzuvanje=0;
		if(depth>0)
		{
			if(za_koj==red)
			{//BIRAME MAXIMALNA VREDNOST
				baza.gen_site_mozni(za_koj);
				int tmp;
				tabla nova;
				bool prune=false;
				for(int i=0;i<8 && prune==false;i++)
				{
					for(int j=0;j<8;j++)
					{
						if(za_koj==baza.tablata[i][j].owner)
						{
							int size=baza.tablata[i][j].mozni.size();
							if(size>0)
							{
								for(int k=size-1;k>=0;k--)
								{	
									nova=baza;
						//			if(nova.tablata[baza.tablata[i][j].mozni[k].br][baza.tablata[i][j].mozni[k].bu].owner==3-za_koj)
						//				prodolzuvanje=1;
						//			else
						//				prodolzuvanje=0;
									nova.poteg(i,j,baza.tablata[i][j].mozni[k].br,baza.tablata[i][j].mozni[k].bu);
									//if(TabeliNaTranspozicija(tab)!=-10000000)
									//	return TabeliNaTranspozicija(tab)
									//else
									tmp=vi(3-za_koj,red,&nova,depth-1,10000000,ova);
									if(tmp>ova)
										ova=tmp;

									//za MAX
									if(pred>=ova)
										prune=true;
								}
							}
						}
					}
				}
				return ova;
			}
			else
			{//BIRAME MINIMALNA VREDNOST
				baza.gen_site_mozni(za_koj);
				int tmp;
				tabla nova;
				bool prune=false;
				for(int i=0;i<8 && prune==false;i++)
				{
					for(int j=0;j<8;j++)
					{
						if(za_koj==baza.tablata[i][j].owner)
						{
							int size=baza.tablata[i][j].mozni.size();
							if(size>0)
							{
								for(int k=size-1;k>=0;k--)
								{	
									nova=baza;
						//			if(nova.tablata[baza.tablata[i][j].mozni[k].br][baza.tablata[i][j].mozni[k].bu].owner==3-za_koj)
						//				prodolzuvanje=1;
						//			else
						//				prodolzuvanje=0;
									nova.poteg(i,j,baza.tablata[i][j].mozni[k].br,baza.tablata[i][j].mozni[k].bu);
									//if(TabeliNaTranspozicija(tab)!=-10000000)
									//	return TabeliNaTranspozicija(tab)
									//else
									tmp=vi(3-za_koj,red,&nova,depth-1,-10000000,ova);
									if(tmp<ova)
										ova=tmp;
						
									//za MIN
									if(pred<=ova)
										prune=true;
								}
							}
						}
					}
				}
				return ova;
			}
		}else{
			return baza.procenka_bez_gen(red);
		}
	}
};


public ref class VIStart{
public:
	//output
	int odBR;
	int odBU;
	int doBR;
	int doBU;

private:
	//input
	tabla* pole;
	int igrach_na_red;
	int dlabochina;

public:
	VIStart(tabla* pole, int igrach_na_red, int dlabochina){
		this->pole=pole;
		this->igrach_na_red=igrach_na_red;
		this->dlabochina=dlabochina;
	}
	
	void exec()
	{
		srand((unsigned)time(0));
		tabla baza=*pole;
		tabla nova;
		int br_na_potezi=baza.gen_site_mozni(igrach_na_red);
		int num=0;
		int rez;
		int count=0;
		int max=-10000000;
		bool mat=false;
		if(br_na_potezi<7)
			this->dlabochina++;

	//	fstream dat;
	//	dat.open("spisok.txt",ios::out);
		for(int i=0;i<8 && mat!=true;i++)
		{
			for(int j=0;j<8;j++)
			{
				int size=baza.tablata[i][j].mozni.size();
				if(size>0 && baza.tablata[i][j].owner==igrach_na_red)
				{
					for(int k=0;k<size;k++)
					{
						nova=baza;
						nova.poteg(i,j,baza.tablata[i][j].mozni[k].br,baza.tablata[i][j].mozni[k].bu);
						VINode^ klasa=gcnew VINode(3-igrach_na_red,igrach_na_red,&nova,dlabochina-1,10000000,max);
						klasa->odBR=i;
						klasa->odBU=j;
						klasa->doBR=baza.tablata[i][j].mozni[k].br;
						klasa->doBU=baza.tablata[i][j].mozni[k].bu;
						klasa->exec();

						//dat<<endl<<"==================="<<endl;
						//dat<<"tmp->rez "<<klasa->zemiRez()<<endl;
						//dat<<"max"<<max<<endl;
						//dat<<"tmp->odBR"<<klasa->odBR<<endl;
						//dat<<"tmp->odBU"<<klasa->odBU<<endl;
						//dat<<"tmp->doBR"<<klasa->doBR<<endl;
						//dat<<"tmp->doBU"<<klasa->doBU<<endl;

						if(klasa->zemiRez()!=10000000)
						{//ako ne e cekor shto ja zavrsuva igrata
							if(klasa->zemiRez()>=max){
								if(max==klasa->zemiRez()){
									count++;
									if(abs(rand())%count==0){
										this->odBR=klasa->odBR;
										this->odBU=klasa->odBU;
										this->doBR=klasa->doBR;
										this->doBU=klasa->doBU;
									}
								}else{
									max=klasa->zemiRez();
									this->odBR=klasa->odBR;
									this->odBU=klasa->odBU;
									this->doBR=klasa->doBR;
									this->doBU=klasa->doBU;
									count=0;
								}
							}
						}
						else
						{//ako e proverka dali e pat ili mat
							int kral_br;
							int kral_bu;

							//naogjanje na kralot, ako toj e pod napad mat e
							for(i=0;i<8;i++)
							{
								for(j=0;j<8;j++)
								{
									if(baza.tablata[i][j].owner==3-igrach_na_red && baza.tablata[i][j].tip==6)
									{
										kral_br=i;
										kral_bu=j;
									}
								}
							}
							if(baza.pod_napad(kral_br,kral_bu,3-igrach_na_red)==true)
							{
								this->odBR=klasa->odBR;
								this->odBU=klasa->odBU;
								this->doBR=klasa->doBR;
								this->doBU=klasa->doBU;
								mat=true;
							}
							else
							{
								if(baza.procenka_bez_gen(igrach_na_red)<=baza.procenka_bez_gen(3-igrach_na_red))
								{
									this->odBR=klasa->odBR;
									this->odBU=klasa->odBU;
									this->doBR=klasa->doBR;
									this->doBU=klasa->doBU;
								}
								else
									continue;
							}
						}
						//dat<<"odBR"<<odBR<<endl;
						//dat<<"odBU"<<odBU<<endl;
						//dat<<"doBR"<<doBR<<endl;
						//dat<<"doBU"<<doBU<<endl;
					}
				}
			}
		}
	//	dat.close();
		if(br_na_potezi<7)
			this->dlabochina--;
	 }
};
#endif