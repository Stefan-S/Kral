#pragma once
#include <list>
#include <algorithm>
#include "ai.h"
#include "close_form.h"


namespace kral {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace enkripcija;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			this->pole= new tabla;
			this->prv_beli=true;
			this->vi_faza=0;
			this->vreme_min=45;
			//
			//TUKA BONUS KONSTRUKTORSKI KOD================================
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
//===============================================================================================================================================================================
	private:
//statichki promelivi==================================================================================
		static tabla *pole;
		static bool prv_beli;
		static bool drag=false;
		static bool klik=false;
		static int vreme_min;
		static /*time_t*/unsigned vreme_vi_pochetok;
		static int vreme_ostanato_i1;
		static int vreme_ostanato_i2;
		static int vi_poteg_od_broj;
		static int vi_poteg_do_broj;
		static int vi_poteg_od_bukva;
		static int vi_poteg_do_bukva;
		static int xposledno;
		static int yposledno;
		static int igrach_na_red;
		static int vi_faza;
		static int dlabochina;
		System::Threading::Thread^ DThread;
		VIStart^ rezultat;

	private: System::Windows::Forms::Label^  unapreduvanje_slika;

	private: System::Windows::Forms::Button^  unap_d;

	private: System::Windows::Forms::Button^  unap_g;

	private: System::Windows::Forms::Label^  unapreduvanje_text;
	private: System::Windows::Forms::Timer^  timer_vi;
	private: System::Windows::Forms::ImageList^  min_btn;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  vreme;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  vreme_bd;
	private: System::Windows::Forms::Button^  vreme_bg;
	private: System::Windows::Forms::Label^  vreme_i1;
	private: System::Windows::Forms::Label^  vreme_i2;
	private: System::Windows::Forms::Timer^  vreme_clock_i1;
	private: System::Windows::Forms::Timer^  vreme_clock_i2;

	private: System::Windows::Forms::Label^  raboti_i1;
	private: System::Windows::Forms::Label^  raboti_i2;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  novaigra;
	private: System::Windows::Forms::ImageList^  btn;
	private: System::Windows::Forms::Button^  btn_nazad1;
	private: System::Windows::Forms::GroupBox^  aboutBox;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Button^  nazadOdAboutBTN;

	private: System::Windows::Forms::Label^  objasnuvanje;
	private: System::Windows::Forms::Label^  label10;







	private: System::Windows::Forms::Label^  label5;
//od tuka moi metodi=================================================================================
		void poteg(int od_br,int od_bu,int do_br,int do_bu)
		{
					 //zapis vo listata
					 if(prv_beli==true)
					 {
						 if(igrach_na_red==1)
						 {
							 this->listBox1->Items->Add(this->textBox1->Text+L" од "+Convert::ToChar(od_bu+65)+Convert::ToString(8-od_br)+L" до "+Convert::ToChar(do_bu+65)+Convert::ToString(8-do_br));
						 }
						 else
						 {
							 this->listBox1->Items->Add(this->textBox2->Text+L" од "+Convert::ToChar(od_bu+65)+Convert::ToString(8-od_br)+L" до "+Convert::ToChar(do_bu+65)+Convert::ToString(8-do_br));				
						 }
					 }
					 else
					 {
						 if(igrach_na_red==1)
						 {
							 this->listBox1->Items->Add(this->textBox1->Text+L" од "+Convert::ToChar(-od_bu+72)+Convert::ToString(od_br+1)+L" до "+Convert::ToChar(-do_bu+72)+Convert::ToString(do_br+1));
						 }
						 else
						 {
							 this->listBox1->Items->Add(this->textBox2->Text+L" од "+Convert::ToChar(-od_bu+72)+Convert::ToString(od_br+1)+L" до "+Convert::ToChar(-do_bu+72)+Convert::ToString(do_br+1));				
						 }
					 }

					 //potegot
					 pole->poteg(od_br,od_bu,do_br,do_bu);
		};
/*		int vi(int za_koj, int red,tabla tab,int depth){
			
			if(depth>0)
			{
				int sostojba=tab.procenka_so_gen(za_koj);
				int rez;
				int max=-1000000;
				for(int i=0;i<8;i++)
				{
					for(int j=0;j<8;j++)
					{
						int size=tab.tablata[i][j].mozni.size();
						if(size>0 && za_koj==tab.tablata[i][j].owner)
						{
							for(int k=size-1;k>=0;k--)
							{						
								tabla nova=tab;
								nova.poteg(i,j,tab.tablata[i][j].mozni[k].br,tab.tablata[i][j].mozni[k].bu);
								rez=vi(3-za_koj,red,nova,depth-1);
								if(rez>max)
									max=rez;
							}
						}
					}
				}
				return (za_koj==red)?sostojba+max:-sostojba+max;
			}else{
				int sostojba=tab.procenka_bez_gen(za_koj);
				return (za_koj==red)?sostojba:-sostojba;
			}

		};*/
		void presmetaj_i_prikzi_kraj(int za_koj)
		{
			this->pole->gen_pat_mat(za_koj);
			int count=0;
			if(this->pole->pat_i1==true && (za_koj==0 || za_koj==1) )
				count+=1;
			if(this->pole->pat_i2==true && (za_koj==0 || za_koj==2) )
				count+=2;
			if(this->pole->mat_i1==true && (za_koj==0 || za_koj==1) )
				count+=4;
			if(this->pole->mat_i2==true && (za_koj==0 || za_koj==2) )
				count+=16;

			if(count!=0)
			{
				this->vreme_clock_i1->Enabled=false;
				this->vreme_clock_i2->Enabled=false;
				this->timer_vi->Enabled=false;

				String^ path ="output.data";
				System::IO::StreamWriter^ dat;
				if(System::IO::File::Exists(path)==true)
					System::IO::File::Delete(path);
				dat=System::IO::File::AppendText(path);
				dat->WriteLine(enkriptiraj("1"));
				dat->WriteLine(enkriptiraj("0"));
				dat->WriteLine(enkriptiraj("1"));
				dat->WriteLine(enkriptiraj("0"));

				switch(count)
				{
				case 0:
					break;
				case 1:
					 dat->WriteLine(enkriptiraj(L"Мечот завршува нерешено,\n заради тоа што "+this->label1->Text+L"\n се наоѓа во Пат позиција."));
					 dat->Close();
					break;
				case 2:
					 dat->WriteLine(enkriptiraj(L"Мечот завршува нерешено,\n заради тоа што "+this->label2->Text+L"\n се наоѓа во Пат позиција."));
					 dat->Close();
					break;
				case 4:
					 dat->WriteLine(enkriptiraj(L"Победник е "+this->label2->Text+L", \n "+this->label1->Text+L" се наоѓа во Мат позиција."));
					 dat->Close();
					break;
				case 16:
					 dat->WriteLine(enkriptiraj(L"Победник е "+this->label1->Text+L", \n "+this->label2->Text+L" се наоѓа во Мат позиција."));
					 dat->Close();
					break;
				default:
					 dat->WriteLine(enkriptiraj(L"Дошол мице глувчето и \n изел дел од програмот,\n прати дебаг на stef.mkd@gmail.com."));
					 dat->Close();
					break;
				}
				 System::Windows::Forms::Form^ izlezna_forma = gcnew kral::close_form;
				 if(this->closeBTN->Enabled!=false)
					 this->closeBTN->Enabled=false;
				 if(this->close->Enabled!=false)
					this->close->Enabled=false;
	 			 this->AddOwnedForm(izlezna_forma);
				 izlezna_forma->ShowDialog(this);
			}
		};

		void startVI()
		{
			this->closeBTN->Enabled=false;
		//	vreme_vi_pochetok=(unsigned)time(NULL);
			this->timer_vi->Enabled=true;		
		};

		void spremi_za_nova_igra()
		{
			if(this->vreme_clock_i1->Enabled==true)
				this->vreme_clock_i1->Enabled=false;
			if(this->vreme_clock_i2->Enabled==true)
				this->vreme_clock_i2->Enabled=false;
			if(this->timer_vi->Enabled==true)
				this->timer_vi->Enabled=false;

			if(this->prv_beli==false)
			{
				 System::Drawing::Image ^tmp;
				 for(int i=1;i<=6;i++)
				 {
					 tmp=this->imageList1->Images[i];
					 this->imageList1->Images[i]=this->imageList1->Images[i+6];
					 this->imageList1->Images[i+6]=tmp;
					 tmp=this->imageList1->Images[i+13];
					 this->imageList1->Images[i+13]=this->imageList1->Images[i+19];
					 this->imageList1->Images[i+19]=tmp;
				 }
			}
			this->listBox1->Items->Clear();
			this->pole->pochetok(prv_beli);
			this->vi_faza=0;
		};
		void osvezi_labela(int br,int bu)
		{
			int btn;
			btn=br*8+bu+1;
			switch(btn)
			{
			case 1:
					this->button1->Refresh();
				break;
				
			case 2:
					this->button2->Refresh();
				break;
				
			case 3:
					this->button3->Refresh();
				break;
				
			case 4:
					this->button4->Refresh();
				break;
				
			case 5:
					this->button5->Refresh();
				break;
				
			case 6:
					this->button6->Refresh();
				break;
				
			case 7:
					this->button7->Refresh();
				break;
				
			case 8:
					this->button8->Refresh();
				break;
				
			case 9:
					this->button9->Refresh();
				break;
				
			case 10:
					this->button10->Refresh();
				break;
				
			case 11:
					this->button11->Refresh();
				break;
				
			case 12:
					this->button12->Refresh();
				break;
				
			case 13:
					this->button13->Refresh();
				break;
				
			case 14:
					this->button14->Refresh();
				break;
				
			case 15:
					this->button15->Refresh();
				break;
				
			case 16:
					this->button16->Refresh();
				break;
				
			case 17:
					this->button17->Refresh();
				break;
				
			case 18:
					this->button18->Refresh();
				break;
				
			case 19:
					this->button19->Refresh();
				break;
			
			case 20:
					this->button20->Refresh();
				break;
			case 21:
					this->button21->Refresh();
				break;
			case 22:
					this->button22->Refresh();
				break;
			case 23:
					this->button23->Refresh();
				break;
			case 24:
					this->button24->Refresh();
				break;

			case 25:
					this->button25->Refresh();
				break;
			case 26:
					this->button26->Refresh();
				break;

			case 27:
					this->button27->Refresh();
				break;

			case 28:
					this->button28->Refresh();
				break;

			case 29:
					this->button29->Refresh();
				break;

			case 30:
					this->button30->Refresh();
				break;
				
			case 31:
					this->button31->Refresh();
				break;
				
			case 32:
					this->button32->Refresh();
				break;
				
			case 33:
					this->button33->Refresh();
				break;
				
			case 34:
					this->button34->Refresh();
				break;
				
			case 35:
					this->button35->Refresh();
				break;
				
			case 36:
					this->button36->Refresh();
				break;
				
			case 37:
					this->button37->Refresh();
				break;
				
			case 38:
					this->button38->Refresh();
				break;
				
			case 39:
					this->button39->Refresh();
				break;
				
			case 40:
					this->button40->Refresh();
				break;
				
			case 41:
					this->button41->Refresh();
				break;
				
			case 42:
					this->button42->Refresh();
				break;
				
			case 43:
					this->button43->Refresh();
				break;
				
			case 44:
					this->button44->Refresh();
				break;
				
			case 45:
					this->button45->Refresh();
				break;
				
			case 46:
					this->button46->Refresh();
				break;
				
			case 47:
					this->button47->Refresh();
				break;
				
			case 48:
					this->button48->Refresh();
				break;
				
			case 49:
					this->button49->Refresh();
				break;
				
			case 50:
					this->button50->Refresh();
				break;
				
			case 51:
					this->button51->Refresh();
				break;
				
			case 52:
					this->button52->Refresh();
				break;
				
			case 53:
					this->button53->Refresh();
				break;
				
			case 54:
					this->button54->Refresh();
				break;
				
			case 55:
					this->button55->Refresh();
				break;
				
			case 56:
					this->button56->Refresh();
				break;
				
			case 57:
					this->button57->Refresh();
				break;
				
			case 58:
					this->button58->Refresh();
				break;
				
			case 59:
					this->button59->Refresh();
				break;
				
			case 60:
					this->button60->Refresh();
				break;
				
			case 61:
					this->button61->Refresh();
				break;
				
			case 62:
					this->button62->Refresh();
				break;
				
			case 63:
					this->button63->Refresh();
				break;
				
			case 64:
					this->button64->Refresh();
				break;

			default:
				break;
			};

		}
		void osvezi_site_labeli()
		{
			this->button1->Refresh();
			this->button2->Refresh();
			this->button3->Refresh();
			this->button4->Refresh();
			this->button5->Refresh();
			this->button6->Refresh();
			this->button7->Refresh();
			this->button8->Refresh();
			this->button9->Refresh();
			this->button10->Refresh();
			this->button11->Refresh();
			this->button12->Refresh();
			this->button13->Refresh();
			this->button14->Refresh();
			this->button15->Refresh();
			this->button16->Refresh();
			this->button17->Refresh();
			this->button18->Refresh();
			this->button19->Refresh();
			this->button20->Refresh();
			this->button21->Refresh();
			this->button22->Refresh();
			this->button23->Refresh();
			this->button24->Refresh();
			this->button25->Refresh();
			this->button26->Refresh();
			this->button27->Refresh();
			this->button28->Refresh();
			this->button29->Refresh();
			this->button30->Refresh();
			this->button31->Refresh();
			this->button32->Refresh();
			this->button33->Refresh();
			this->button34->Refresh();
			this->button35->Refresh();
			this->button36->Refresh();
			this->button37->Refresh();
			this->button38->Refresh();
			this->button39->Refresh();
			this->button40->Refresh();
			this->button41->Refresh();
			this->button42->Refresh();
			this->button43->Refresh();
			this->button44->Refresh();
			this->button45->Refresh();
			this->button46->Refresh();
			this->button47->Refresh();
			this->button48->Refresh();
			this->button49->Refresh();
			this->button50->Refresh();
			this->button51->Refresh();
			this->button52->Refresh();
			this->button53->Refresh();
			this->button54->Refresh();
			this->button55->Refresh();
			this->button56->Refresh();
			this->button57->Refresh();
			this->button58->Refresh();
			this->button59->Refresh();
			this->button60->Refresh();
			this->button61->Refresh();
			this->button62->Refresh();
			this->button63->Refresh();
			this->button64->Refresh();
		}
		void osvezi()
		{
			if(this->button1->ImageIndex!=slika(0,0))
				this->button1->ImageIndex=slika(0,0);
			if(this->button2->ImageIndex!=slika(0,1))
				this->button2->ImageIndex=slika(0,1);
			if(this->button3->ImageIndex!=slika(0,2))
				this->button3->ImageIndex=slika(0,2);
			if(this->button4->ImageIndex!=slika(0,3))
				this->button4->ImageIndex=slika(0,3);
			if(this->button5->ImageIndex!=slika(0,4))
				this->button5->ImageIndex=slika(0,4);
			if(this->button6->ImageIndex!=slika(0,5))
				this->button6->ImageIndex=slika(0,5);
			if(this->button7->ImageIndex!=slika(0,6))
				this->button7->ImageIndex=slika(0,6);
			if(this->button8->ImageIndex!=slika(0,7))
				this->button8->ImageIndex=slika(0,7);
			if(this->button9->ImageIndex!=slika(1,0))
				this->button9->ImageIndex=slika(1,0);
			if(this->button10->ImageIndex!=slika(1,1))
				this->button10->ImageIndex=slika(1,1);
			if(this->button11->ImageIndex!=slika(1,2))
				this->button11->ImageIndex=slika(1,2);
			if(this->button12->ImageIndex!=slika(1,3))
				this->button12->ImageIndex=slika(1,3);
			if(this->button13->ImageIndex!=slika(1,4))
				this->button13->ImageIndex=slika(1,4);
			if(this->button14->ImageIndex!=slika(1,5))
				this->button14->ImageIndex=slika(1,5);
			if(this->button15->ImageIndex!=slika(1,6))
				this->button15->ImageIndex=slika(1,6);
			if(this->button16->ImageIndex!=slika(1,7))
				this->button16->ImageIndex=slika(1,7);
			if(this->button17->ImageIndex!=slika(2,0))
				this->button17->ImageIndex=slika(2,0);
			if(this->button18->ImageIndex!=slika(2,1))
				this->button18->ImageIndex=slika(2,1);
			if(this->button19->ImageIndex!=slika(2,2))
				this->button19->ImageIndex=slika(2,2);
			if(this->button20->ImageIndex!=slika(2,3))
				this->button20->ImageIndex=slika(2,3);
			if(this->button21->ImageIndex!=slika(2,4))
				this->button21->ImageIndex=slika(2,4);
			if(this->button22->ImageIndex!=slika(2,5))
				this->button22->ImageIndex=slika(2,5);
			if(this->button23->ImageIndex!=slika(2,6))
				this->button23->ImageIndex=slika(2,6);
			if(this->button24->ImageIndex!=slika(2,7))
				this->button24->ImageIndex=slika(2,7);
			if(this->button25->ImageIndex!=slika(3,0))
				this->button25->ImageIndex=slika(3,0);
			if(this->button26->ImageIndex!=slika(3,1))
				this->button26->ImageIndex=slika(3,1);
			if(this->button27->ImageIndex!=slika(3,2))
				this->button27->ImageIndex=slika(3,2);
			if(this->button28->ImageIndex!=slika(3,3))
				this->button28->ImageIndex=slika(3,3);
			if(this->button29->ImageIndex!=slika(3,4))
				this->button29->ImageIndex=slika(3,4);
			if(this->button30->ImageIndex!=slika(3,5))
				this->button30->ImageIndex=slika(3,5);
			if(this->button31->ImageIndex!=slika(3,6))
				this->button31->ImageIndex=slika(3,6);
			if(this->button32->ImageIndex!=slika(3,7))
				this->button32->ImageIndex=slika(3,7);
			if(this->button33->ImageIndex!=slika(4,0))
				this->button33->ImageIndex=slika(4,0);
			if(this->button34->ImageIndex!=slika(4,1))
				this->button34->ImageIndex=slika(4,1);
			if(this->button35->ImageIndex!=slika(4,2))
				this->button35->ImageIndex=slika(4,2);
			if(this->button36->ImageIndex!=slika(4,3))
				this->button36->ImageIndex=slika(4,3);
			if(this->button37->ImageIndex!=slika(4,4))
				this->button37->ImageIndex=slika(4,4);
			if(this->button38->ImageIndex!=slika(4,5))
				this->button38->ImageIndex=slika(4,5);
			if(this->button39->ImageIndex!=slika(4,6))
				this->button39->ImageIndex=slika(4,6);
			if(this->button40->ImageIndex!=slika(4,7))
				this->button40->ImageIndex=slika(4,7);
			if(this->button41->ImageIndex!=slika(5,0))
				this->button41->ImageIndex=slika(5,0);
			if(this->button42->ImageIndex!=slika(5,1))
				this->button42->ImageIndex=slika(5,1);
			if(this->button43->ImageIndex!=slika(5,2))
				this->button43->ImageIndex=slika(5,2);
			if(this->button44->ImageIndex!=slika(5,3))
				this->button44->ImageIndex=slika(5,3);
			if(this->button45->ImageIndex!=slika(5,4))
				this->button45->ImageIndex=slika(5,4);
			if(this->button46->ImageIndex!=slika(5,5))
				this->button46->ImageIndex=slika(5,5);
			if(this->button47->ImageIndex!=slika(5,6))
				this->button47->ImageIndex=slika(5,6);
			if(this->button48->ImageIndex!=slika(5,7))
				this->button48->ImageIndex=slika(5,7);
			if(this->button49->ImageIndex!=slika(6,0))
				this->button49->ImageIndex=slika(6,0);
			if(this->button50->ImageIndex!=slika(6,1))
				this->button50->ImageIndex=slika(6,1);
			if(this->button51->ImageIndex!=slika(6,2))
				this->button51->ImageIndex=slika(6,2);
			if(this->button52->ImageIndex!=slika(6,3))
				this->button52->ImageIndex=slika(6,3);
			if(this->button53->ImageIndex!=slika(6,4))
				this->button53->ImageIndex=slika(6,4);
			if(this->button54->ImageIndex!=slika(6,5))
				this->button54->ImageIndex=slika(6,5);
			if(this->button55->ImageIndex!=slika(6,6))
				this->button55->ImageIndex=slika(6,6);
			if(this->button56->ImageIndex!=slika(6,7))
				this->button56->ImageIndex=slika(6,7);
			if(this->button57->ImageIndex!=slika(7,0))
				this->button57->ImageIndex=slika(7,0);
			if(this->button58->ImageIndex!=slika(7,1))
				this->button58->ImageIndex=slika(7,1);
			if(this->button59->ImageIndex!=slika(7,2))
				this->button59->ImageIndex=slika(7,2);
			if(this->button60->ImageIndex!=slika(7,3))
				this->button60->ImageIndex=slika(7,3);
			if(this->button61->ImageIndex!=slika(7,4))
				this->button61->ImageIndex=slika(7,4);
			if(this->button62->ImageIndex!=slika(7,5))
				this->button62->ImageIndex=slika(7,5);
			if(this->button63->ImageIndex!=slika(7,6))
				this->button63->ImageIndex=slika(7,6);
			if(this->button64->ImageIndex!=slika(7,7))
				this->button64->ImageIndex=slika(7,7);

			if(this->klik==true)
			{
				for(int i=0;i<pole->tablata[pole->br_select][pole->bu_select].mozni.size();i++)
				{
					stavi_slika(pole->tablata[pole->br_select][pole->bu_select].mozni[i].br,pole->tablata[pole->br_select][pole->bu_select].mozni[i].bu,13+slika(pole->tablata[pole->br_select][pole->bu_select].mozni[i].br,pole->tablata[pole->br_select][pole->bu_select].mozni[i].bu));
				}

			}
		};
		void stavi_slika(int br, int bu,int sl)
		{
			int btn;
			btn=br*8+bu+1;
			switch(btn)
			{
			case 1:
				if(this->button1->ImageIndex!=sl)
					this->button1->ImageIndex=sl;
				break;
				
			case 2:
				if(this->button2->ImageIndex!=sl)
					this->button2->ImageIndex=sl;
				break;
				
			case 3:
				if(this->button3->ImageIndex!=sl)
					this->button3->ImageIndex=sl;
				break;
				
			case 4:
				if(this->button4->ImageIndex!=sl)
					this->button4->ImageIndex=sl;
				break;
				
			case 5:
				if(this->button5->ImageIndex!=sl)
					this->button5->ImageIndex=sl;
				break;
				
			case 6:
				if(this->button6->ImageIndex!=sl)
					this->button6->ImageIndex=sl;
				break;
				
			case 7:
				if(this->button7->ImageIndex!=sl)
					this->button7->ImageIndex=sl;
				break;
				
			case 8:
				if(this->button8->ImageIndex!=sl)
					this->button8->ImageIndex=sl;
				break;
				
			case 9:
				if(this->button9->ImageIndex!=sl)
					this->button9->ImageIndex=sl;
				break;
				
			case 10:
				if(this->button10->ImageIndex!=sl)
					this->button10->ImageIndex=sl;
				break;
				
			case 11:
				if(this->button11->ImageIndex!=sl)
					this->button11->ImageIndex=sl;
				break;
				
			case 12:
				if(this->button12->ImageIndex!=sl)
					this->button12->ImageIndex=sl;
				break;
				
			case 13:
				if(this->button13->ImageIndex!=sl)
					this->button13->ImageIndex=sl;
				break;
				
			case 14:
				if(this->button14->ImageIndex!=sl)
					this->button14->ImageIndex=sl;
				break;
				
			case 15:
				if(this->button15->ImageIndex!=sl)
					this->button15->ImageIndex=sl;
				break;
				
			case 16:
				if(this->button16->ImageIndex!=sl)
					this->button16->ImageIndex=sl;
				break;
				
			case 17:
				if(this->button17->ImageIndex!=sl)
					this->button17->ImageIndex=sl;
				break;
				
			case 18:
				if(this->button18->ImageIndex!=sl)
					this->button18->ImageIndex=sl;
				break;
				
			case 19:
				if(this->button19->ImageIndex!=sl)
					this->button19->ImageIndex=sl;
				break;
			
			case 20:
				if(this->button20->ImageIndex!=sl)
					this->button20->ImageIndex=sl;
				break;
			case 21:
				if(this->button21->ImageIndex!=sl)
					this->button21->ImageIndex=sl;
				break;
			case 22:
				if(this->button22->ImageIndex!=sl)
					this->button22->ImageIndex=sl;
				break;
			case 23:
				if(this->button23->ImageIndex!=sl)
					this->button23->ImageIndex=sl;
				break;
			case 24:
				if(this->button24->ImageIndex!=sl)
					this->button24->ImageIndex=sl;
				break;

			case 25:
				if(this->button25->ImageIndex!=sl)
					this->button25->ImageIndex=sl;
				break;
			case 26:
				if(this->button26->ImageIndex!=sl)
					this->button26->ImageIndex=sl;
				break;

			case 27:
				if(this->button27->ImageIndex!=sl)
					this->button27->ImageIndex=sl;
				break;

			case 28:
				if(this->button28->ImageIndex!=sl)
					this->button28->ImageIndex=sl;
				break;

			case 29:
				if(this->button29->ImageIndex!=sl)
					this->button29->ImageIndex=sl;
				break;

			case 30:
				if(this->button30->ImageIndex!=sl)
					this->button30->ImageIndex=sl;
				break;
				
			case 31:
				if(this->button31->ImageIndex!=sl)
					this->button31->ImageIndex=sl;
				break;
				
			case 32:
				if(this->button32->ImageIndex!=sl)
					this->button32->ImageIndex=sl;
				break;
				
			case 33:
				if(this->button33->ImageIndex!=sl)
					this->button33->ImageIndex=sl;
				break;
				
			case 34:
				if(this->button34->ImageIndex!=sl)
					this->button34->ImageIndex=sl;
				break;
				
			case 35:
				if(this->button35->ImageIndex!=sl)
					this->button35->ImageIndex=sl;
				break;
				
			case 36:
				if(this->button36->ImageIndex!=sl)
					this->button36->ImageIndex=sl;
				break;
				
			case 37:
				if(this->button37->ImageIndex!=sl)
					this->button37->ImageIndex=sl;
				break;
				
			case 38:
				if(this->button38->ImageIndex!=sl)
					this->button38->ImageIndex=sl;
				break;
				
			case 39:
				if(this->button39->ImageIndex!=sl)
					this->button39->ImageIndex=sl;
				break;
				
			case 40:
				if(this->button40->ImageIndex!=sl)
					this->button40->ImageIndex=sl;
				break;
				
			case 41:
				if(this->button41->ImageIndex!=sl)
					this->button41->ImageIndex=sl;
				break;
				
			case 42:
				if(this->button42->ImageIndex!=sl)
					this->button42->ImageIndex=sl;
				break;
				
			case 43:
				if(this->button43->ImageIndex!=sl)
					this->button43->ImageIndex=sl;
				break;
				
			case 44:
				if(this->button44->ImageIndex!=sl)
					this->button44->ImageIndex=sl;
				break;
				
			case 45:
				if(this->button45->ImageIndex!=sl)
					this->button45->ImageIndex=sl;
				break;
				
			case 46:
				if(this->button46->ImageIndex!=sl)
					this->button46->ImageIndex=sl;
				break;
				
			case 47:
				if(this->button47->ImageIndex!=sl)
					this->button47->ImageIndex=sl;
				break;
				
			case 48:
				if(this->button48->ImageIndex!=sl)
					this->button48->ImageIndex=sl;
				break;
				
			case 49:
				if(this->button49->ImageIndex!=sl)
					this->button49->ImageIndex=sl;
				break;
				
			case 50:
				if(this->button50->ImageIndex!=sl)
					this->button50->ImageIndex=sl;
				break;
				
			case 51:
				if(this->button51->ImageIndex!=sl)
					this->button51->ImageIndex=sl;
				break;
				
			case 52:
				if(this->button52->ImageIndex!=sl)
					this->button52->ImageIndex=sl;
				break;
				
			case 53:
				if(this->button53->ImageIndex!=sl)
					this->button53->ImageIndex=sl;
				break;
				
			case 54:
				if(this->button54->ImageIndex!=sl)
					this->button54->ImageIndex=sl;
				break;
				
			case 55:
				if(this->button55->ImageIndex!=sl)
					this->button55->ImageIndex=sl;
				break;
				
			case 56:
				if(this->button56->ImageIndex!=sl)
					this->button56->ImageIndex=sl;
				break;
				
			case 57:
				if(this->button57->ImageIndex!=sl)
					this->button57->ImageIndex=sl;
				break;
				
			case 58:
				if(this->button58->ImageIndex!=sl)
					this->button58->ImageIndex=sl;
				break;
				
			case 59:
				if(this->button59->ImageIndex!=sl)
					this->button59->ImageIndex=sl;
				break;
				
			case 60:
				if(this->button60->ImageIndex!=sl)
					this->button60->ImageIndex=sl;
				break;
				
			case 61:
				if(this->button61->ImageIndex!=sl)
					this->button61->ImageIndex=sl;
				break;
				
			case 62:
				if(this->button62->ImageIndex!=sl)
					this->button62->ImageIndex=sl;
				break;
				
			case 63:
				if(this->button63->ImageIndex!=sl)
					this->button63->ImageIndex=sl;
				break;
				
			case 64:
				if(this->button64->ImageIndex!=sl)
					this->button64->ImageIndex=sl;
				break;

			default:
				break;
			};

		};

		int slika(int br,int bu)
		{
			int k=(pole->z_owner(br,bu)*6+pole->z_tip(br,bu)-6);
			if(k>0)
				return k;
			else
				return 0;
		};
//do tuka moi metodi=======================================================================================

	private: System::Windows::Forms::GroupBox^  igra;
	protected: 

	private: System::Windows::Forms::GroupBox^  meny;
	private: System::Windows::Forms::GroupBox^  newgame;
	private: System::Windows::Forms::Button^  close;

	private: System::Windows::Forms::Button^  about;

	private: System::Windows::Forms::Button^  replay;

	private: System::Windows::Forms::Button^  open_save;



	private: System::Windows::Forms::Button^  minimiseBTN;
	private: System::Windows::Forms::Button^  closeBTN;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button57;
	private: System::Windows::Forms::Button^  button58;
	private: System::Windows::Forms::Button^  button59;
	private: System::Windows::Forms::Button^  button60;
	private: System::Windows::Forms::Button^  button61;
	private: System::Windows::Forms::Button^  button62;
	private: System::Windows::Forms::Button^  button63;
	private: System::Windows::Forms::Button^  button64;
	private: System::Windows::Forms::Button^  button49;
	private: System::Windows::Forms::Button^  button50;
	private: System::Windows::Forms::Button^  button51;
	private: System::Windows::Forms::Button^  button52;
	private: System::Windows::Forms::Button^  button53;
	private: System::Windows::Forms::Button^  button54;
	private: System::Windows::Forms::Button^  button55;
	private: System::Windows::Forms::Button^  button56;
	private: System::Windows::Forms::Button^  button41;
	private: System::Windows::Forms::Button^  button42;
	private: System::Windows::Forms::Button^  button43;
	private: System::Windows::Forms::Button^  button44;
	private: System::Windows::Forms::Button^  button45;
	private: System::Windows::Forms::Button^  button46;
	private: System::Windows::Forms::Button^  button47;
	private: System::Windows::Forms::Button^  button48;
	private: System::Windows::Forms::Button^  button33;
	private: System::Windows::Forms::Button^  button34;
	private: System::Windows::Forms::Button^  button35;
	private: System::Windows::Forms::Button^  button36;
	private: System::Windows::Forms::Button^  button37;
	private: System::Windows::Forms::Button^  button38;
	private: System::Windows::Forms::Button^  button39;
	private: System::Windows::Forms::Button^  button40;
	private: System::Windows::Forms::Button^  button25;
	private: System::Windows::Forms::Button^  button26;
	private: System::Windows::Forms::Button^  button27;
	private: System::Windows::Forms::Button^  button28;
	private: System::Windows::Forms::Button^  button29;
	private: System::Windows::Forms::Button^  button30;
	private: System::Windows::Forms::Button^  button31;
	private: System::Windows::Forms::Button^  button32;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Button^  button19;
	private: System::Windows::Forms::Button^  button20;
	private: System::Windows::Forms::Button^  button21;
	private: System::Windows::Forms::Button^  button22;
	private: System::Windows::Forms::Button^  button23;
	private: System::Windows::Forms::Button^  button24;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button7;
private: System::Windows::Forms::Button^  button6;

private: System::Windows::Forms::Button^  button5;

private: System::Windows::Forms::Button^  button4;

private: System::Windows::Forms::Button^  button3;

private: System::Windows::Forms::Button^  button2;

private: System::Windows::Forms::Button^  button1;

private: System::Windows::Forms::Button^  start;

	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;


private: System::Windows::Forms::Label^  naslov;

private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Button^  i1bd;

private: System::Windows::Forms::Button^  i1bg;

private: System::Windows::Forms::Label^  i2t;

private: System::Windows::Forms::Label^  i2b;

private: System::Windows::Forms::Label^  i1b;
private: System::Windows::Forms::Button^  i2b2d;



private: System::Windows::Forms::Button^  i2b2g;

private: System::Windows::Forms::Button^  i2b1d;

private: System::Windows::Forms::Button^  i2b1g;
private: System::Windows::Forms::ImageList^  imageList1;
private: System::ComponentModel::IContainer^  components;
















	protected: 



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->igra = (gcnew System::Windows::Forms::GroupBox());
			this->button58 = (gcnew System::Windows::Forms::Button());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->raboti_i2 = (gcnew System::Windows::Forms::Label());
			this->raboti_i1 = (gcnew System::Windows::Forms::Label());
			this->vreme_i2 = (gcnew System::Windows::Forms::Label());
			this->vreme_i1 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button57 = (gcnew System::Windows::Forms::Button());
			this->button59 = (gcnew System::Windows::Forms::Button());
			this->button60 = (gcnew System::Windows::Forms::Button());
			this->button61 = (gcnew System::Windows::Forms::Button());
			this->button62 = (gcnew System::Windows::Forms::Button());
			this->button63 = (gcnew System::Windows::Forms::Button());
			this->button64 = (gcnew System::Windows::Forms::Button());
			this->button49 = (gcnew System::Windows::Forms::Button());
			this->button50 = (gcnew System::Windows::Forms::Button());
			this->button51 = (gcnew System::Windows::Forms::Button());
			this->button52 = (gcnew System::Windows::Forms::Button());
			this->button53 = (gcnew System::Windows::Forms::Button());
			this->button54 = (gcnew System::Windows::Forms::Button());
			this->button55 = (gcnew System::Windows::Forms::Button());
			this->button56 = (gcnew System::Windows::Forms::Button());
			this->button41 = (gcnew System::Windows::Forms::Button());
			this->button42 = (gcnew System::Windows::Forms::Button());
			this->button43 = (gcnew System::Windows::Forms::Button());
			this->button44 = (gcnew System::Windows::Forms::Button());
			this->button45 = (gcnew System::Windows::Forms::Button());
			this->button46 = (gcnew System::Windows::Forms::Button());
			this->button47 = (gcnew System::Windows::Forms::Button());
			this->button48 = (gcnew System::Windows::Forms::Button());
			this->button33 = (gcnew System::Windows::Forms::Button());
			this->button34 = (gcnew System::Windows::Forms::Button());
			this->button35 = (gcnew System::Windows::Forms::Button());
			this->button36 = (gcnew System::Windows::Forms::Button());
			this->button37 = (gcnew System::Windows::Forms::Button());
			this->button38 = (gcnew System::Windows::Forms::Button());
			this->button39 = (gcnew System::Windows::Forms::Button());
			this->button40 = (gcnew System::Windows::Forms::Button());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->button26 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->button29 = (gcnew System::Windows::Forms::Button());
			this->button30 = (gcnew System::Windows::Forms::Button());
			this->button31 = (gcnew System::Windows::Forms::Button());
			this->button32 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->meny = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->close = (gcnew System::Windows::Forms::Button());
			this->btn = (gcnew System::Windows::Forms::ImageList(this->components));
			this->about = (gcnew System::Windows::Forms::Button());
			this->replay = (gcnew System::Windows::Forms::Button());
			this->open_save = (gcnew System::Windows::Forms::Button());
			this->novaigra = (gcnew System::Windows::Forms::Button());
			this->newgame = (gcnew System::Windows::Forms::GroupBox());
			this->btn_nazad1 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->vreme_bd = (gcnew System::Windows::Forms::Button());
			this->vreme_bg = (gcnew System::Windows::Forms::Button());
			this->vreme = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->unap_d = (gcnew System::Windows::Forms::Button());
			this->unap_g = (gcnew System::Windows::Forms::Button());
			this->unapreduvanje_text = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->i2b2d = (gcnew System::Windows::Forms::Button());
			this->i2b2g = (gcnew System::Windows::Forms::Button());
			this->i2b1d = (gcnew System::Windows::Forms::Button());
			this->i2b1g = (gcnew System::Windows::Forms::Button());
			this->i1bd = (gcnew System::Windows::Forms::Button());
			this->i1bg = (gcnew System::Windows::Forms::Button());
			this->i2t = (gcnew System::Windows::Forms::Label());
			this->i2b = (gcnew System::Windows::Forms::Label());
			this->i1b = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->start = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->unapreduvanje_slika = (gcnew System::Windows::Forms::Label());
			this->minimiseBTN = (gcnew System::Windows::Forms::Button());
			this->closeBTN = (gcnew System::Windows::Forms::Button());
			this->naslov = (gcnew System::Windows::Forms::Label());
			this->timer_vi = (gcnew System::Windows::Forms::Timer(this->components));
			this->min_btn = (gcnew System::Windows::Forms::ImageList(this->components));
			this->vreme_clock_i1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->vreme_clock_i2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->aboutBox = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->nazadOdAboutBTN = (gcnew System::Windows::Forms::Button());
			this->objasnuvanje = (gcnew System::Windows::Forms::Label());
			this->igra->SuspendLayout();
			this->meny->SuspendLayout();
			this->newgame->SuspendLayout();
			this->aboutBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// igra
			// 
			this->igra->BackColor = System::Drawing::Color::Transparent;
			this->igra->Controls->Add(this->button58);
			this->igra->Controls->Add(this->raboti_i2);
			this->igra->Controls->Add(this->raboti_i1);
			this->igra->Controls->Add(this->vreme_i2);
			this->igra->Controls->Add(this->vreme_i1);
			this->igra->Controls->Add(this->listBox1);
			this->igra->Controls->Add(this->label2);
			this->igra->Controls->Add(this->label1);
			this->igra->Controls->Add(this->button57);
			this->igra->Controls->Add(this->button59);
			this->igra->Controls->Add(this->button60);
			this->igra->Controls->Add(this->button61);
			this->igra->Controls->Add(this->button62);
			this->igra->Controls->Add(this->button63);
			this->igra->Controls->Add(this->button64);
			this->igra->Controls->Add(this->button49);
			this->igra->Controls->Add(this->button50);
			this->igra->Controls->Add(this->button51);
			this->igra->Controls->Add(this->button52);
			this->igra->Controls->Add(this->button53);
			this->igra->Controls->Add(this->button54);
			this->igra->Controls->Add(this->button55);
			this->igra->Controls->Add(this->button56);
			this->igra->Controls->Add(this->button41);
			this->igra->Controls->Add(this->button42);
			this->igra->Controls->Add(this->button43);
			this->igra->Controls->Add(this->button44);
			this->igra->Controls->Add(this->button45);
			this->igra->Controls->Add(this->button46);
			this->igra->Controls->Add(this->button47);
			this->igra->Controls->Add(this->button48);
			this->igra->Controls->Add(this->button33);
			this->igra->Controls->Add(this->button34);
			this->igra->Controls->Add(this->button35);
			this->igra->Controls->Add(this->button36);
			this->igra->Controls->Add(this->button37);
			this->igra->Controls->Add(this->button38);
			this->igra->Controls->Add(this->button39);
			this->igra->Controls->Add(this->button40);
			this->igra->Controls->Add(this->button25);
			this->igra->Controls->Add(this->button26);
			this->igra->Controls->Add(this->button27);
			this->igra->Controls->Add(this->button28);
			this->igra->Controls->Add(this->button29);
			this->igra->Controls->Add(this->button30);
			this->igra->Controls->Add(this->button31);
			this->igra->Controls->Add(this->button32);
			this->igra->Controls->Add(this->button17);
			this->igra->Controls->Add(this->button18);
			this->igra->Controls->Add(this->button19);
			this->igra->Controls->Add(this->button20);
			this->igra->Controls->Add(this->button21);
			this->igra->Controls->Add(this->button22);
			this->igra->Controls->Add(this->button23);
			this->igra->Controls->Add(this->button24);
			this->igra->Controls->Add(this->button9);
			this->igra->Controls->Add(this->button10);
			this->igra->Controls->Add(this->button11);
			this->igra->Controls->Add(this->button12);
			this->igra->Controls->Add(this->button13);
			this->igra->Controls->Add(this->button14);
			this->igra->Controls->Add(this->button15);
			this->igra->Controls->Add(this->button16);
			this->igra->Controls->Add(this->button8);
			this->igra->Controls->Add(this->button7);
			this->igra->Controls->Add(this->button6);
			this->igra->Controls->Add(this->button5);
			this->igra->Controls->Add(this->button4);
			this->igra->Controls->Add(this->button3);
			this->igra->Controls->Add(this->button2);
			this->igra->Controls->Add(this->button1);
			this->igra->Controls->Add(this->label7);
			this->igra->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->igra->ForeColor = System::Drawing::Color::Black;
			this->igra->Location = System::Drawing::Point(12, 25);
			this->igra->Name = L"igra";
			this->igra->Size = System::Drawing::Size(776, 563);
			this->igra->TabIndex = 0;
			this->igra->TabStop = false;
			this->igra->Visible = false;
			// 
			// button58
			// 
			this->button58->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button58.BackgroundImage")));
			this->button58->FlatAppearance->BorderSize = 0;
			this->button58->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button58->ImageList = this->imageList1;
			this->button58->Location = System::Drawing::Point(93, 467);
			this->button58->Name = L"button58";
			this->button58->Size = System::Drawing::Size(60, 60);
			this->button58->TabIndex = 244;
			this->button58->UseVisualStyleBackColor = true;
			this->button58->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"empty.png");
			this->imageList1->Images->SetKeyName(1, L"white pawn.png");
			this->imageList1->Images->SetKeyName(2, L"white rook.png");
			this->imageList1->Images->SetKeyName(3, L"white knight.png");
			this->imageList1->Images->SetKeyName(4, L"white bishop.png");
			this->imageList1->Images->SetKeyName(5, L"white queen.png");
			this->imageList1->Images->SetKeyName(6, L"white king.png");
			this->imageList1->Images->SetKeyName(7, L"black pawn.png");
			this->imageList1->Images->SetKeyName(8, L"black rook.png");
			this->imageList1->Images->SetKeyName(9, L"black knight.png");
			this->imageList1->Images->SetKeyName(10, L"black bishop.png");
			this->imageList1->Images->SetKeyName(11, L"black queen.png");
			this->imageList1->Images->SetKeyName(12, L"black king.png");
			this->imageList1->Images->SetKeyName(13, L"select.png");
			this->imageList1->Images->SetKeyName(14, L"white pawn.png");
			this->imageList1->Images->SetKeyName(15, L"white rook.png");
			this->imageList1->Images->SetKeyName(16, L"white knight.png");
			this->imageList1->Images->SetKeyName(17, L"white bishop.png");
			this->imageList1->Images->SetKeyName(18, L"white queen.png");
			this->imageList1->Images->SetKeyName(19, L"white king.png");
			this->imageList1->Images->SetKeyName(20, L"black pawn.png");
			this->imageList1->Images->SetKeyName(21, L"black rook.png");
			this->imageList1->Images->SetKeyName(22, L"black knight.png");
			this->imageList1->Images->SetKeyName(23, L"black bishop.png");
			this->imageList1->Images->SetKeyName(24, L"black queen.png");
			this->imageList1->Images->SetKeyName(25, L"black king.png");
			// 
			// raboti_i2
			// 
			this->raboti_i2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"raboti_i2.Image")));
			this->raboti_i2->Location = System::Drawing::Point(572, 170);
			this->raboti_i2->Name = L"raboti_i2";
			this->raboti_i2->Size = System::Drawing::Size(48, 48);
			this->raboti_i2->TabIndex = 252;
			this->raboti_i2->Visible = false;
			// 
			// raboti_i1
			// 
			this->raboti_i1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"raboti_i1.Image")));
			this->raboti_i1->Location = System::Drawing::Point(572, 71);
			this->raboti_i1->Name = L"raboti_i1";
			this->raboti_i1->Size = System::Drawing::Size(48, 48);
			this->raboti_i1->TabIndex = 251;
			this->raboti_i1->Visible = false;
			// 
			// vreme_i2
			// 
			this->vreme_i2->AutoSize = true;
			this->vreme_i2->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->vreme_i2->Location = System::Drawing::Point(624, 195);
			this->vreme_i2->Name = L"vreme_i2";
			this->vreme_i2->Size = System::Drawing::Size(47, 22);
			this->vreme_i2->TabIndex = 250;
			this->vreme_i2->Text = L"10:00";
			// 
			// vreme_i1
			// 
			this->vreme_i1->AutoSize = true;
			this->vreme_i1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->vreme_i1->Location = System::Drawing::Point(624, 96);
			this->vreme_i1->Name = L"vreme_i1";
			this->vreme_i1->Size = System::Drawing::Size(47, 22);
			this->vreme_i1->TabIndex = 249;
			this->vreme_i1->Text = L"10:00";
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 18;
			this->listBox1->Location = System::Drawing::Point(570, 288);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(151, 184);
			this->listBox1->TabIndex = 248;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(619, 173);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(51, 22);
			this->label2->TabIndex = 247;
			this->label2->Text = L"label2";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(619, 74);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 22);
			this->label1->TabIndex = 246;
			this->label1->Text = L"label1";
			// 
			// button57
			// 
			this->button57->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button57.BackgroundImage")));
			this->button57->FlatAppearance->BorderSize = 0;
			this->button57->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button57->ImageList = this->imageList1;
			this->button57->Location = System::Drawing::Point(33, 467);
			this->button57->Name = L"button57";
			this->button57->Size = System::Drawing::Size(60, 60);
			this->button57->TabIndex = 245;
			this->button57->UseVisualStyleBackColor = true;
			this->button57->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button59
			// 
			this->button59->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button59.BackgroundImage")));
			this->button59->FlatAppearance->BorderSize = 0;
			this->button59->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button59->ImageList = this->imageList1;
			this->button59->Location = System::Drawing::Point(153, 467);
			this->button59->Name = L"button59";
			this->button59->Size = System::Drawing::Size(60, 60);
			this->button59->TabIndex = 243;
			this->button59->UseVisualStyleBackColor = true;
			this->button59->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button60
			// 
			this->button60->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button60.BackgroundImage")));
			this->button60->FlatAppearance->BorderSize = 0;
			this->button60->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button60->ImageList = this->imageList1;
			this->button60->Location = System::Drawing::Point(213, 467);
			this->button60->Name = L"button60";
			this->button60->Size = System::Drawing::Size(60, 60);
			this->button60->TabIndex = 242;
			this->button60->UseVisualStyleBackColor = true;
			this->button60->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button61
			// 
			this->button61->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button61.BackgroundImage")));
			this->button61->FlatAppearance->BorderSize = 0;
			this->button61->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button61->ImageList = this->imageList1;
			this->button61->Location = System::Drawing::Point(273, 467);
			this->button61->Name = L"button61";
			this->button61->Size = System::Drawing::Size(60, 60);
			this->button61->TabIndex = 241;
			this->button61->UseVisualStyleBackColor = true;
			this->button61->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button62
			// 
			this->button62->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button62.BackgroundImage")));
			this->button62->FlatAppearance->BorderSize = 0;
			this->button62->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button62->ImageList = this->imageList1;
			this->button62->Location = System::Drawing::Point(333, 467);
			this->button62->Name = L"button62";
			this->button62->Size = System::Drawing::Size(60, 60);
			this->button62->TabIndex = 240;
			this->button62->UseVisualStyleBackColor = true;
			this->button62->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button63
			// 
			this->button63->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button63.BackgroundImage")));
			this->button63->FlatAppearance->BorderSize = 0;
			this->button63->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button63->ImageList = this->imageList1;
			this->button63->Location = System::Drawing::Point(393, 467);
			this->button63->Name = L"button63";
			this->button63->Size = System::Drawing::Size(60, 60);
			this->button63->TabIndex = 239;
			this->button63->UseVisualStyleBackColor = true;
			this->button63->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button64
			// 
			this->button64->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button64.BackgroundImage")));
			this->button64->FlatAppearance->BorderSize = 0;
			this->button64->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button64->ImageList = this->imageList1;
			this->button64->Location = System::Drawing::Point(453, 467);
			this->button64->Name = L"button64";
			this->button64->Size = System::Drawing::Size(60, 60);
			this->button64->TabIndex = 238;
			this->button64->UseVisualStyleBackColor = true;
			this->button64->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button49
			// 
			this->button49->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button49.BackgroundImage")));
			this->button49->FlatAppearance->BorderSize = 0;
			this->button49->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button49->ImageList = this->imageList1;
			this->button49->Location = System::Drawing::Point(33, 408);
			this->button49->Name = L"button49";
			this->button49->Size = System::Drawing::Size(60, 60);
			this->button49->TabIndex = 237;
			this->button49->UseVisualStyleBackColor = true;
			this->button49->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button50
			// 
			this->button50->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button50.BackgroundImage")));
			this->button50->FlatAppearance->BorderSize = 0;
			this->button50->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button50->ImageList = this->imageList1;
			this->button50->Location = System::Drawing::Point(93, 408);
			this->button50->Name = L"button50";
			this->button50->Size = System::Drawing::Size(60, 60);
			this->button50->TabIndex = 236;
			this->button50->UseVisualStyleBackColor = true;
			this->button50->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button51
			// 
			this->button51->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button51.BackgroundImage")));
			this->button51->FlatAppearance->BorderSize = 0;
			this->button51->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button51->ImageList = this->imageList1;
			this->button51->Location = System::Drawing::Point(153, 408);
			this->button51->Name = L"button51";
			this->button51->Size = System::Drawing::Size(60, 60);
			this->button51->TabIndex = 235;
			this->button51->UseVisualStyleBackColor = true;
			this->button51->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button52
			// 
			this->button52->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button52.BackgroundImage")));
			this->button52->FlatAppearance->BorderSize = 0;
			this->button52->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button52->ImageList = this->imageList1;
			this->button52->Location = System::Drawing::Point(213, 408);
			this->button52->Name = L"button52";
			this->button52->Size = System::Drawing::Size(60, 60);
			this->button52->TabIndex = 234;
			this->button52->UseVisualStyleBackColor = true;
			this->button52->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button53
			// 
			this->button53->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button53.BackgroundImage")));
			this->button53->FlatAppearance->BorderSize = 0;
			this->button53->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button53->ImageList = this->imageList1;
			this->button53->Location = System::Drawing::Point(273, 408);
			this->button53->Name = L"button53";
			this->button53->Size = System::Drawing::Size(60, 60);
			this->button53->TabIndex = 233;
			this->button53->UseVisualStyleBackColor = true;
			this->button53->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button54
			// 
			this->button54->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button54.BackgroundImage")));
			this->button54->FlatAppearance->BorderSize = 0;
			this->button54->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button54->ImageList = this->imageList1;
			this->button54->Location = System::Drawing::Point(333, 408);
			this->button54->Name = L"button54";
			this->button54->Size = System::Drawing::Size(60, 60);
			this->button54->TabIndex = 232;
			this->button54->UseVisualStyleBackColor = true;
			this->button54->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button55
			// 
			this->button55->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button55.BackgroundImage")));
			this->button55->FlatAppearance->BorderSize = 0;
			this->button55->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button55->ImageList = this->imageList1;
			this->button55->Location = System::Drawing::Point(393, 408);
			this->button55->Name = L"button55";
			this->button55->Size = System::Drawing::Size(60, 60);
			this->button55->TabIndex = 231;
			this->button55->UseVisualStyleBackColor = true;
			this->button55->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button56
			// 
			this->button56->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button56.BackgroundImage")));
			this->button56->FlatAppearance->BorderSize = 0;
			this->button56->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button56->ImageList = this->imageList1;
			this->button56->Location = System::Drawing::Point(453, 408);
			this->button56->Name = L"button56";
			this->button56->Size = System::Drawing::Size(60, 60);
			this->button56->TabIndex = 230;
			this->button56->UseVisualStyleBackColor = true;
			this->button56->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button41
			// 
			this->button41->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button41.BackgroundImage")));
			this->button41->FlatAppearance->BorderSize = 0;
			this->button41->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button41->ImageList = this->imageList1;
			this->button41->Location = System::Drawing::Point(33, 348);
			this->button41->Name = L"button41";
			this->button41->Size = System::Drawing::Size(60, 60);
			this->button41->TabIndex = 229;
			this->button41->UseVisualStyleBackColor = true;
			this->button41->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button42
			// 
			this->button42->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button42.BackgroundImage")));
			this->button42->FlatAppearance->BorderSize = 0;
			this->button42->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button42->ImageList = this->imageList1;
			this->button42->Location = System::Drawing::Point(93, 348);
			this->button42->Name = L"button42";
			this->button42->Size = System::Drawing::Size(60, 60);
			this->button42->TabIndex = 228;
			this->button42->UseVisualStyleBackColor = true;
			this->button42->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button43
			// 
			this->button43->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button43.BackgroundImage")));
			this->button43->FlatAppearance->BorderSize = 0;
			this->button43->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button43->ImageList = this->imageList1;
			this->button43->Location = System::Drawing::Point(153, 348);
			this->button43->Name = L"button43";
			this->button43->Size = System::Drawing::Size(60, 60);
			this->button43->TabIndex = 227;
			this->button43->UseVisualStyleBackColor = true;
			this->button43->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button44
			// 
			this->button44->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button44.BackgroundImage")));
			this->button44->FlatAppearance->BorderSize = 0;
			this->button44->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button44->ImageList = this->imageList1;
			this->button44->Location = System::Drawing::Point(213, 348);
			this->button44->Name = L"button44";
			this->button44->Size = System::Drawing::Size(60, 60);
			this->button44->TabIndex = 226;
			this->button44->UseVisualStyleBackColor = true;
			this->button44->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button45
			// 
			this->button45->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button45.BackgroundImage")));
			this->button45->FlatAppearance->BorderSize = 0;
			this->button45->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button45->ImageList = this->imageList1;
			this->button45->Location = System::Drawing::Point(273, 348);
			this->button45->Name = L"button45";
			this->button45->Size = System::Drawing::Size(60, 60);
			this->button45->TabIndex = 225;
			this->button45->UseVisualStyleBackColor = true;
			this->button45->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button46
			// 
			this->button46->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button46.BackgroundImage")));
			this->button46->FlatAppearance->BorderSize = 0;
			this->button46->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button46->ImageList = this->imageList1;
			this->button46->Location = System::Drawing::Point(333, 348);
			this->button46->Name = L"button46";
			this->button46->Size = System::Drawing::Size(60, 60);
			this->button46->TabIndex = 224;
			this->button46->UseVisualStyleBackColor = true;
			this->button46->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button47
			// 
			this->button47->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button47.BackgroundImage")));
			this->button47->FlatAppearance->BorderSize = 0;
			this->button47->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button47->ImageList = this->imageList1;
			this->button47->Location = System::Drawing::Point(393, 348);
			this->button47->Name = L"button47";
			this->button47->Size = System::Drawing::Size(60, 60);
			this->button47->TabIndex = 223;
			this->button47->UseVisualStyleBackColor = true;
			this->button47->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button48
			// 
			this->button48->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button48.BackgroundImage")));
			this->button48->FlatAppearance->BorderSize = 0;
			this->button48->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button48->ImageList = this->imageList1;
			this->button48->Location = System::Drawing::Point(453, 348);
			this->button48->Name = L"button48";
			this->button48->Size = System::Drawing::Size(60, 60);
			this->button48->TabIndex = 222;
			this->button48->UseVisualStyleBackColor = true;
			this->button48->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button33
			// 
			this->button33->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button33.BackgroundImage")));
			this->button33->FlatAppearance->BorderSize = 0;
			this->button33->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button33->ImageList = this->imageList1;
			this->button33->Location = System::Drawing::Point(33, 288);
			this->button33->Name = L"button33";
			this->button33->Size = System::Drawing::Size(60, 60);
			this->button33->TabIndex = 221;
			this->button33->UseVisualStyleBackColor = true;
			this->button33->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button34
			// 
			this->button34->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button34.BackgroundImage")));
			this->button34->FlatAppearance->BorderSize = 0;
			this->button34->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button34->ImageList = this->imageList1;
			this->button34->Location = System::Drawing::Point(93, 288);
			this->button34->Name = L"button34";
			this->button34->Size = System::Drawing::Size(60, 60);
			this->button34->TabIndex = 220;
			this->button34->UseVisualStyleBackColor = true;
			this->button34->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button35
			// 
			this->button35->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button35.BackgroundImage")));
			this->button35->FlatAppearance->BorderSize = 0;
			this->button35->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button35->ImageList = this->imageList1;
			this->button35->Location = System::Drawing::Point(153, 288);
			this->button35->Name = L"button35";
			this->button35->Size = System::Drawing::Size(60, 60);
			this->button35->TabIndex = 219;
			this->button35->UseVisualStyleBackColor = true;
			this->button35->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button36
			// 
			this->button36->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button36.BackgroundImage")));
			this->button36->FlatAppearance->BorderSize = 0;
			this->button36->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button36->ImageList = this->imageList1;
			this->button36->Location = System::Drawing::Point(213, 288);
			this->button36->Name = L"button36";
			this->button36->Size = System::Drawing::Size(60, 60);
			this->button36->TabIndex = 218;
			this->button36->UseVisualStyleBackColor = true;
			this->button36->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button37
			// 
			this->button37->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button37.BackgroundImage")));
			this->button37->FlatAppearance->BorderSize = 0;
			this->button37->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button37->ImageList = this->imageList1;
			this->button37->Location = System::Drawing::Point(273, 288);
			this->button37->Name = L"button37";
			this->button37->Size = System::Drawing::Size(60, 60);
			this->button37->TabIndex = 217;
			this->button37->UseVisualStyleBackColor = true;
			this->button37->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button38
			// 
			this->button38->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button38.BackgroundImage")));
			this->button38->FlatAppearance->BorderSize = 0;
			this->button38->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button38->ImageList = this->imageList1;
			this->button38->Location = System::Drawing::Point(333, 288);
			this->button38->Name = L"button38";
			this->button38->Size = System::Drawing::Size(60, 60);
			this->button38->TabIndex = 216;
			this->button38->UseVisualStyleBackColor = true;
			this->button38->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button39
			// 
			this->button39->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button39.BackgroundImage")));
			this->button39->FlatAppearance->BorderSize = 0;
			this->button39->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button39->ImageList = this->imageList1;
			this->button39->Location = System::Drawing::Point(393, 288);
			this->button39->Name = L"button39";
			this->button39->Size = System::Drawing::Size(60, 60);
			this->button39->TabIndex = 215;
			this->button39->UseVisualStyleBackColor = true;
			this->button39->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button40
			// 
			this->button40->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button40.BackgroundImage")));
			this->button40->FlatAppearance->BorderSize = 0;
			this->button40->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button40->ImageList = this->imageList1;
			this->button40->Location = System::Drawing::Point(453, 288);
			this->button40->Name = L"button40";
			this->button40->Size = System::Drawing::Size(60, 60);
			this->button40->TabIndex = 214;
			this->button40->UseVisualStyleBackColor = true;
			this->button40->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button25
			// 
			this->button25->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button25.BackgroundImage")));
			this->button25->FlatAppearance->BorderSize = 0;
			this->button25->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button25->ImageList = this->imageList1;
			this->button25->Location = System::Drawing::Point(33, 228);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(60, 60);
			this->button25->TabIndex = 213;
			this->button25->UseVisualStyleBackColor = true;
			this->button25->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button26
			// 
			this->button26->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button26.BackgroundImage")));
			this->button26->FlatAppearance->BorderSize = 0;
			this->button26->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button26->ImageList = this->imageList1;
			this->button26->Location = System::Drawing::Point(93, 228);
			this->button26->Name = L"button26";
			this->button26->Size = System::Drawing::Size(60, 60);
			this->button26->TabIndex = 212;
			this->button26->UseVisualStyleBackColor = true;
			this->button26->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button27
			// 
			this->button27->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button27.BackgroundImage")));
			this->button27->FlatAppearance->BorderSize = 0;
			this->button27->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button27->ImageList = this->imageList1;
			this->button27->Location = System::Drawing::Point(153, 228);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(60, 60);
			this->button27->TabIndex = 211;
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button28
			// 
			this->button28->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button28.BackgroundImage")));
			this->button28->FlatAppearance->BorderSize = 0;
			this->button28->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button28->ImageList = this->imageList1;
			this->button28->Location = System::Drawing::Point(213, 228);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(60, 60);
			this->button28->TabIndex = 210;
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button29
			// 
			this->button29->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button29.BackgroundImage")));
			this->button29->FlatAppearance->BorderSize = 0;
			this->button29->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button29->ImageList = this->imageList1;
			this->button29->Location = System::Drawing::Point(273, 228);
			this->button29->Name = L"button29";
			this->button29->Size = System::Drawing::Size(60, 60);
			this->button29->TabIndex = 209;
			this->button29->UseVisualStyleBackColor = true;
			this->button29->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button30
			// 
			this->button30->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button30.BackgroundImage")));
			this->button30->FlatAppearance->BorderSize = 0;
			this->button30->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button30->ImageList = this->imageList1;
			this->button30->Location = System::Drawing::Point(333, 228);
			this->button30->Name = L"button30";
			this->button30->Size = System::Drawing::Size(60, 60);
			this->button30->TabIndex = 208;
			this->button30->UseVisualStyleBackColor = true;
			this->button30->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button31
			// 
			this->button31->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button31.BackgroundImage")));
			this->button31->FlatAppearance->BorderSize = 0;
			this->button31->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button31->ImageList = this->imageList1;
			this->button31->Location = System::Drawing::Point(393, 228);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(60, 60);
			this->button31->TabIndex = 207;
			this->button31->UseVisualStyleBackColor = true;
			this->button31->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button32
			// 
			this->button32->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button32.BackgroundImage")));
			this->button32->FlatAppearance->BorderSize = 0;
			this->button32->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button32->ImageList = this->imageList1;
			this->button32->Location = System::Drawing::Point(453, 228);
			this->button32->Name = L"button32";
			this->button32->Size = System::Drawing::Size(60, 60);
			this->button32->TabIndex = 206;
			this->button32->UseVisualStyleBackColor = true;
			this->button32->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button17
			// 
			this->button17->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button17.BackgroundImage")));
			this->button17->FlatAppearance->BorderSize = 0;
			this->button17->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button17->ImageList = this->imageList1;
			this->button17->Location = System::Drawing::Point(33, 168);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(60, 60);
			this->button17->TabIndex = 205;
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button18
			// 
			this->button18->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button18.BackgroundImage")));
			this->button18->FlatAppearance->BorderSize = 0;
			this->button18->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button18->ImageList = this->imageList1;
			this->button18->Location = System::Drawing::Point(93, 168);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(60, 60);
			this->button18->TabIndex = 204;
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button19
			// 
			this->button19->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button19.BackgroundImage")));
			this->button19->FlatAppearance->BorderSize = 0;
			this->button19->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button19->ImageList = this->imageList1;
			this->button19->Location = System::Drawing::Point(153, 168);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(60, 60);
			this->button19->TabIndex = 203;
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button20
			// 
			this->button20->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button20.BackgroundImage")));
			this->button20->FlatAppearance->BorderSize = 0;
			this->button20->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button20->ImageList = this->imageList1;
			this->button20->Location = System::Drawing::Point(213, 168);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(60, 60);
			this->button20->TabIndex = 202;
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button21
			// 
			this->button21->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button21.BackgroundImage")));
			this->button21->FlatAppearance->BorderSize = 0;
			this->button21->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button21->ImageList = this->imageList1;
			this->button21->Location = System::Drawing::Point(273, 168);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(60, 60);
			this->button21->TabIndex = 201;
			this->button21->UseVisualStyleBackColor = true;
			this->button21->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button22
			// 
			this->button22->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button22.BackgroundImage")));
			this->button22->FlatAppearance->BorderSize = 0;
			this->button22->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button22->ImageList = this->imageList1;
			this->button22->Location = System::Drawing::Point(333, 168);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(60, 60);
			this->button22->TabIndex = 200;
			this->button22->UseVisualStyleBackColor = true;
			this->button22->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button23
			// 
			this->button23->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button23.BackgroundImage")));
			this->button23->FlatAppearance->BorderSize = 0;
			this->button23->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button23->ImageList = this->imageList1;
			this->button23->Location = System::Drawing::Point(393, 168);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(60, 60);
			this->button23->TabIndex = 199;
			this->button23->UseVisualStyleBackColor = true;
			this->button23->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button24
			// 
			this->button24->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button24.BackgroundImage")));
			this->button24->FlatAppearance->BorderSize = 0;
			this->button24->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button24->ImageList = this->imageList1;
			this->button24->Location = System::Drawing::Point(453, 168);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(60, 60);
			this->button24->TabIndex = 198;
			this->button24->UseVisualStyleBackColor = true;
			this->button24->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button9
			// 
			this->button9->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button9.BackgroundImage")));
			this->button9->FlatAppearance->BorderSize = 0;
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->ImageList = this->imageList1;
			this->button9->Location = System::Drawing::Point(33, 108);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(60, 60);
			this->button9->TabIndex = 197;
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button10
			// 
			this->button10->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button10.BackgroundImage")));
			this->button10->FlatAppearance->BorderSize = 0;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->ImageList = this->imageList1;
			this->button10->Location = System::Drawing::Point(93, 108);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(60, 60);
			this->button10->TabIndex = 196;
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button11
			// 
			this->button11->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button11.BackgroundImage")));
			this->button11->FlatAppearance->BorderSize = 0;
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->ImageList = this->imageList1;
			this->button11->Location = System::Drawing::Point(153, 108);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(60, 60);
			this->button11->TabIndex = 195;
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button12
			// 
			this->button12->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button12.BackgroundImage")));
			this->button12->FlatAppearance->BorderSize = 0;
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->ImageList = this->imageList1;
			this->button12->Location = System::Drawing::Point(213, 108);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(60, 60);
			this->button12->TabIndex = 194;
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button13
			// 
			this->button13->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button13.BackgroundImage")));
			this->button13->FlatAppearance->BorderSize = 0;
			this->button13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button13->ImageList = this->imageList1;
			this->button13->Location = System::Drawing::Point(273, 108);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(60, 60);
			this->button13->TabIndex = 193;
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button14
			// 
			this->button14->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button14.BackgroundImage")));
			this->button14->FlatAppearance->BorderSize = 0;
			this->button14->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button14->ImageList = this->imageList1;
			this->button14->Location = System::Drawing::Point(333, 108);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(60, 60);
			this->button14->TabIndex = 192;
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button15
			// 
			this->button15->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button15.BackgroundImage")));
			this->button15->FlatAppearance->BorderSize = 0;
			this->button15->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button15->ImageList = this->imageList1;
			this->button15->Location = System::Drawing::Point(393, 108);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(60, 60);
			this->button15->TabIndex = 191;
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button16
			// 
			this->button16->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button16.BackgroundImage")));
			this->button16->FlatAppearance->BorderSize = 0;
			this->button16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button16->ImageList = this->imageList1;
			this->button16->Location = System::Drawing::Point(453, 108);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(60, 60);
			this->button16->TabIndex = 190;
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button8
			// 
			this->button8->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button8.BackgroundImage")));
			this->button8->FlatAppearance->BorderSize = 0;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->ImageList = this->imageList1;
			this->button8->Location = System::Drawing::Point(453, 48);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(60, 60);
			this->button8->TabIndex = 189;
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button7
			// 
			this->button7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button7.BackgroundImage")));
			this->button7->FlatAppearance->BorderSize = 0;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->ImageList = this->imageList1;
			this->button7->Location = System::Drawing::Point(393, 48);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(60, 60);
			this->button7->TabIndex = 188;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button6
			// 
			this->button6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button6.BackgroundImage")));
			this->button6->FlatAppearance->BorderSize = 0;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->ImageList = this->imageList1;
			this->button6->Location = System::Drawing::Point(333, 48);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(60, 60);
			this->button6->TabIndex = 187;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button5
			// 
			this->button5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button5.BackgroundImage")));
			this->button5->FlatAppearance->BorderSize = 0;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->ImageList = this->imageList1;
			this->button5->Location = System::Drawing::Point(273, 48);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(60, 60);
			this->button5->TabIndex = 186;
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button4
			// 
			this->button4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button4.BackgroundImage")));
			this->button4->FlatAppearance->BorderSize = 0;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->ImageList = this->imageList1;
			this->button4->Location = System::Drawing::Point(213, 48);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(60, 60);
			this->button4->TabIndex = 185;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button3
			// 
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->ImageList = this->imageList1;
			this->button3->Location = System::Drawing::Point(153, 48);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(60, 60);
			this->button3->TabIndex = 184;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->ImageList = this->imageList1;
			this->button2->Location = System::Drawing::Point(93, 48);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(60, 60);
			this->button2->TabIndex = 183;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// button1
			// 
			this->button1->AccessibleName = L"";
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->ImageList = this->imageList1;
			this->button1->Location = System::Drawing::Point(33, 48);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 60);
			this->button1->TabIndex = 182;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::dbutton_Click);
			// 
			// label7
			// 
			this->label7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label7.Image")));
			this->label7->Location = System::Drawing::Point(2, 17);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(542, 542);
			this->label7->TabIndex = 253;
			// 
			// meny
			// 
			this->meny->BackColor = System::Drawing::Color::Transparent;
			this->meny->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"meny.BackgroundImage")));
			this->meny->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->meny->Controls->Add(this->label9);
			this->meny->Controls->Add(this->close);
			this->meny->Controls->Add(this->about);
			this->meny->Controls->Add(this->replay);
			this->meny->Controls->Add(this->open_save);
			this->meny->Controls->Add(this->novaigra);
			this->meny->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->meny->Location = System::Drawing::Point(273, 79);
			this->meny->Name = L"meny";
			this->meny->Size = System::Drawing::Size(254, 443);
			this->meny->TabIndex = 1;
			this->meny->TabStop = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::Cornsilk;
			this->label9->Location = System::Drawing::Point(99, 16);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(57, 25);
			this->label9->TabIndex = 10;
			this->label9->Text = L"Мени";
			// 
			// close
			// 
			this->close->FlatAppearance->BorderSize = 0;
			this->close->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->close->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->close->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->close->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->close->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->close->ForeColor = System::Drawing::Color::Cornsilk;
			this->close->ImageIndex = 1;
			this->close->ImageList = this->btn;
			this->close->Location = System::Drawing::Point(49, 367);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(157, 40);
			this->close->TabIndex = 9;
			this->close->Text = L"Излез";
			this->close->UseVisualStyleBackColor = true;
			this->close->MouseLeave += gcnew System::EventHandler(this, &Form1::MouseLeave);
			this->close->Click += gcnew System::EventHandler(this, &Form1::close_Click);
			this->close->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseDown);
			this->close->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseUp);
			this->close->MouseEnter += gcnew System::EventHandler(this, &Form1::MouseEnter);
			// 
			// btn
			// 
			this->btn->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"btn.ImageStream")));
			this->btn->TransparentColor = System::Drawing::Color::Transparent;
			this->btn->Images->SetKeyName(0, L"overtop.png");
			this->btn->Images->SetKeyName(1, L"btn.png");
			this->btn->Images->SetKeyName(2, L"clicked.png");
			// 
			// about
			// 
			this->about->FlatAppearance->BorderSize = 0;
			this->about->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->about->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->about->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->about->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->about->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->about->ForeColor = System::Drawing::Color::Cornsilk;
			this->about->ImageIndex = 1;
			this->about->ImageList = this->btn;
			this->about->Location = System::Drawing::Point(49, 111);
			this->about->Name = L"about";
			this->about->Size = System::Drawing::Size(157, 40);
			this->about->TabIndex = 8;
			this->about->Text = L"За авторот";
			this->about->UseVisualStyleBackColor = true;
			this->about->MouseLeave += gcnew System::EventHandler(this, &Form1::MouseLeave);
			this->about->Click += gcnew System::EventHandler(this, &Form1::about_Click);
			this->about->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseDown);
			this->about->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseUp);
			this->about->MouseEnter += gcnew System::EventHandler(this, &Form1::MouseEnter);
			// 
			// replay
			// 
			this->replay->FlatAppearance->BorderSize = 0;
			this->replay->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->replay->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->replay->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->replay->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->replay->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->replay->ForeColor = System::Drawing::Color::Cornsilk;
			this->replay->ImageIndex = 1;
			this->replay->ImageList = this->btn;
			this->replay->Location = System::Drawing::Point(49, 321);
			this->replay->Name = L"replay";
			this->replay->Size = System::Drawing::Size(157, 40);
			this->replay->TabIndex = 7;
			this->replay->Text = L"Приказ на игра";
			this->replay->UseVisualStyleBackColor = true;
			this->replay->Visible = false;
			this->replay->MouseLeave += gcnew System::EventHandler(this, &Form1::MouseLeave);
			this->replay->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseDown);
			this->replay->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseUp);
			this->replay->MouseEnter += gcnew System::EventHandler(this, &Form1::MouseEnter);
			// 
			// open_save
			// 
			this->open_save->FlatAppearance->BorderSize = 0;
			this->open_save->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->open_save->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->open_save->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->open_save->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->open_save->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->open_save->ForeColor = System::Drawing::Color::Cornsilk;
			this->open_save->ImageIndex = 1;
			this->open_save->ImageList = this->btn;
			this->open_save->Location = System::Drawing::Point(49, 272);
			this->open_save->Name = L"open_save";
			this->open_save->Size = System::Drawing::Size(157, 40);
			this->open_save->TabIndex = 6;
			this->open_save->Text = L"Отвори зачувана игра";
			this->open_save->UseVisualStyleBackColor = true;
			this->open_save->Visible = false;
			this->open_save->MouseLeave += gcnew System::EventHandler(this, &Form1::MouseLeave);
			this->open_save->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseDown);
			this->open_save->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseUp);
			this->open_save->MouseEnter += gcnew System::EventHandler(this, &Form1::MouseEnter);
			// 
			// novaigra
			// 
			this->novaigra->FlatAppearance->BorderSize = 0;
			this->novaigra->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->novaigra->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->novaigra->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->novaigra->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->novaigra->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->novaigra->ForeColor = System::Drawing::Color::Cornsilk;
			this->novaigra->ImageIndex = 1;
			this->novaigra->ImageList = this->btn;
			this->novaigra->Location = System::Drawing::Point(49, 65);
			this->novaigra->Name = L"novaigra";
			this->novaigra->Size = System::Drawing::Size(157, 40);
			this->novaigra->TabIndex = 5;
			this->novaigra->Text = L"Нова игра";
			this->novaigra->UseVisualStyleBackColor = true;
			this->novaigra->MouseLeave += gcnew System::EventHandler(this, &Form1::MouseLeave);
			this->novaigra->Click += gcnew System::EventHandler(this, &Form1::newgame_Click);
			this->novaigra->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseDown);
			this->novaigra->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseUp);
			this->novaigra->MouseEnter += gcnew System::EventHandler(this, &Form1::MouseEnter);
			// 
			// newgame
			// 
			this->newgame->BackColor = System::Drawing::Color::Transparent;
			this->newgame->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newgame.BackgroundImage")));
			this->newgame->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->newgame->Controls->Add(this->btn_nazad1);
			this->newgame->Controls->Add(this->label8);
			this->newgame->Controls->Add(this->vreme_bd);
			this->newgame->Controls->Add(this->vreme_bg);
			this->newgame->Controls->Add(this->vreme);
			this->newgame->Controls->Add(this->checkBox1);
			this->newgame->Controls->Add(this->label6);
			this->newgame->Controls->Add(this->unap_d);
			this->newgame->Controls->Add(this->unap_g);
			this->newgame->Controls->Add(this->unapreduvanje_text);
			this->newgame->Controls->Add(this->label5);
			this->newgame->Controls->Add(this->i2b2d);
			this->newgame->Controls->Add(this->i2b2g);
			this->newgame->Controls->Add(this->i2b1d);
			this->newgame->Controls->Add(this->i2b1g);
			this->newgame->Controls->Add(this->i1bd);
			this->newgame->Controls->Add(this->i1bg);
			this->newgame->Controls->Add(this->i2t);
			this->newgame->Controls->Add(this->i2b);
			this->newgame->Controls->Add(this->i1b);
			this->newgame->Controls->Add(this->label4);
			this->newgame->Controls->Add(this->label3);
			this->newgame->Controls->Add(this->start);
			this->newgame->Controls->Add(this->textBox2);
			this->newgame->Controls->Add(this->textBox1);
			this->newgame->Controls->Add(this->unapreduvanje_slika);
			this->newgame->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->newgame->Location = System::Drawing::Point(179, 136);
			this->newgame->Name = L"newgame";
			this->newgame->Size = System::Drawing::Size(442, 371);
			this->newgame->TabIndex = 2;
			this->newgame->TabStop = false;
			this->newgame->Visible = false;
			// 
			// btn_nazad1
			// 
			this->btn_nazad1->AutoSize = true;
			this->btn_nazad1->FlatAppearance->BorderSize = 0;
			this->btn_nazad1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->btn_nazad1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btn_nazad1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_nazad1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btn_nazad1->ForeColor = System::Drawing::Color::Cornsilk;
			this->btn_nazad1->Location = System::Drawing::Point(252, 319);
			this->btn_nazad1->Name = L"btn_nazad1";
			this->btn_nazad1->Size = System::Drawing::Size(75, 32);
			this->btn_nazad1->TabIndex = 34;
			this->btn_nazad1->Text = L"Назад";
			this->btn_nazad1->UseVisualStyleBackColor = true;
			this->btn_nazad1->Click += gcnew System::EventHandler(this, &Form1::btn_nazad1_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::Cornsilk;
			this->label8->Location = System::Drawing::Point(102, 15);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(91, 25);
			this->label8->TabIndex = 33;
			this->label8->Text = L"Нова игра";
			// 
			// vreme_bd
			// 
			this->vreme_bd->FlatAppearance->BorderSize = 0;
			this->vreme_bd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->vreme_bd->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->vreme_bd->Location = System::Drawing::Point(164, 285);
			this->vreme_bd->Name = L"vreme_bd";
			this->vreme_bd->Size = System::Drawing::Size(23, 23);
			this->vreme_bd->TabIndex = 32;
			this->vreme_bd->Text = L"\\/";
			this->vreme_bd->UseVisualStyleBackColor = true;
			this->vreme_bd->Click += gcnew System::EventHandler(this, &Form1::vreme_bd_Click);
			// 
			// vreme_bg
			// 
			this->vreme_bg->FlatAppearance->BorderSize = 0;
			this->vreme_bg->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->vreme_bg->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->vreme_bg->Location = System::Drawing::Point(164, 261);
			this->vreme_bg->Name = L"vreme_bg";
			this->vreme_bg->Size = System::Drawing::Size(23, 23);
			this->vreme_bg->TabIndex = 31;
			this->vreme_bg->Text = L"/\\";
			this->vreme_bg->UseVisualStyleBackColor = true;
			this->vreme_bg->Click += gcnew System::EventHandler(this, &Form1::vreme_bg_Click);
			// 
			// vreme
			// 
			this->vreme->AutoSize = true;
			this->vreme->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->vreme->Location = System::Drawing::Point(41, 270);
			this->vreme->Name = L"vreme";
			this->vreme->Size = System::Drawing::Size(122, 25);
			this->vreme->TabIndex = 30;
			this->vreme->Text = L"10:00 минути";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(100, 247);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 29;
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(12, 244);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(75, 15);
			this->label6->TabIndex = 28;
			this->label6->Text = L"Игра на време";
			// 
			// unap_d
			// 
			this->unap_d->FlatAppearance->BorderSize = 0;
			this->unap_d->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->unap_d->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->unap_d->Location = System::Drawing::Point(177, 220);
			this->unap_d->Name = L"unap_d";
			this->unap_d->Size = System::Drawing::Size(23, 23);
			this->unap_d->TabIndex = 26;
			this->unap_d->Text = L"\\/";
			this->unap_d->UseVisualStyleBackColor = true;
			this->unap_d->Click += gcnew System::EventHandler(this, &Form1::unap_d_Click);
			// 
			// unap_g
			// 
			this->unap_g->Enabled = false;
			this->unap_g->FlatAppearance->BorderSize = 0;
			this->unap_g->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->unap_g->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->unap_g->Location = System::Drawing::Point(177, 196);
			this->unap_g->Name = L"unap_g";
			this->unap_g->Size = System::Drawing::Size(23, 23);
			this->unap_g->TabIndex = 25;
			this->unap_g->Text = L"/\\";
			this->unap_g->UseVisualStyleBackColor = true;
			this->unap_g->Click += gcnew System::EventHandler(this, &Form1::unap_g_Click);
			// 
			// unapreduvanje_text
			// 
			this->unapreduvanje_text->AutoSize = true;
			this->unapreduvanje_text->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->unapreduvanje_text->Location = System::Drawing::Point(14, 204);
			this->unapreduvanje_text->Name = L"unapreduvanje_text";
			this->unapreduvanje_text->Size = System::Drawing::Size(82, 25);
			this->unapreduvanje_text->TabIndex = 24;
			this->unapreduvanje_text->Text = L"Кралица";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(10, 175);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(112, 15);
			this->label5->TabIndex = 23;
			this->label5->Text = L"Тип на унапредување";
			// 
			// i2b2d
			// 
			this->i2b2d->Enabled = false;
			this->i2b2d->FlatAppearance->BorderSize = 0;
			this->i2b2d->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->i2b2d->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->i2b2d->Location = System::Drawing::Point(408, 153);
			this->i2b2d->Name = L"i2b2d";
			this->i2b2d->Size = System::Drawing::Size(23, 23);
			this->i2b2d->TabIndex = 22;
			this->i2b2d->Text = L"\\/";
			this->i2b2d->UseVisualStyleBackColor = true;
			this->i2b2d->Click += gcnew System::EventHandler(this, &Form1::i2b2d_Click);
			// 
			// i2b2g
			// 
			this->i2b2g->FlatAppearance->BorderSize = 0;
			this->i2b2g->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->i2b2g->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->i2b2g->Location = System::Drawing::Point(408, 129);
			this->i2b2g->Name = L"i2b2g";
			this->i2b2g->Size = System::Drawing::Size(23, 23);
			this->i2b2g->TabIndex = 21;
			this->i2b2g->Text = L"/\\";
			this->i2b2g->UseVisualStyleBackColor = true;
			this->i2b2g->Click += gcnew System::EventHandler(this, &Form1::i2b2g_Click);
			// 
			// i2b1d
			// 
			this->i2b1d->Enabled = false;
			this->i2b1d->FlatAppearance->BorderSize = 0;
			this->i2b1d->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->i2b1d->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->i2b1d->Location = System::Drawing::Point(178, 153);
			this->i2b1d->Name = L"i2b1d";
			this->i2b1d->Size = System::Drawing::Size(23, 23);
			this->i2b1d->TabIndex = 20;
			this->i2b1d->Text = L"\\/";
			this->i2b1d->UseVisualStyleBackColor = true;
			this->i2b1d->Click += gcnew System::EventHandler(this, &Form1::i2b1d_Click);
			// 
			// i2b1g
			// 
			this->i2b1g->FlatAppearance->BorderSize = 0;
			this->i2b1g->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->i2b1g->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->i2b1g->Location = System::Drawing::Point(178, 129);
			this->i2b1g->Name = L"i2b1g";
			this->i2b1g->Size = System::Drawing::Size(23, 23);
			this->i2b1g->TabIndex = 19;
			this->i2b1g->Text = L"/\\";
			this->i2b1g->UseVisualStyleBackColor = true;
			this->i2b1g->Click += gcnew System::EventHandler(this, &Form1::i2b1g_Click);
			// 
			// i1bd
			// 
			this->i1bd->FlatAppearance->BorderSize = 0;
			this->i1bd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->i1bd->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->i1bd->Location = System::Drawing::Point(178, 89);
			this->i1bd->Name = L"i1bd";
			this->i1bd->Size = System::Drawing::Size(23, 23);
			this->i1bd->TabIndex = 18;
			this->i1bd->Text = L"\\/";
			this->i1bd->UseVisualStyleBackColor = true;
			this->i1bd->Click += gcnew System::EventHandler(this, &Form1::i1bd_Click);
			// 
			// i1bg
			// 
			this->i1bg->Enabled = false;
			this->i1bg->FlatAppearance->BorderSize = 0;
			this->i1bg->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->i1bg->Font = (gcnew System::Drawing::Font(L"Mistral", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->i1bg->Location = System::Drawing::Point(178, 65);
			this->i1bg->Name = L"i1bg";
			this->i1bg->Size = System::Drawing::Size(23, 23);
			this->i1bg->TabIndex = 17;
			this->i1bg->Text = L"/\\";
			this->i1bg->UseVisualStyleBackColor = true;
			this->i1bg->Click += gcnew System::EventHandler(this, &Form1::i1bg_Click);
			// 
			// i2t
			// 
			this->i2t->AutoSize = true;
			this->i2t->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->i2t->Location = System::Drawing::Point(220, 139);
			this->i2t->Name = L"i2t";
			this->i2t->Size = System::Drawing::Size(190, 25);
			this->i2t->TabIndex = 16;
			this->i2t->Text = L"Компјутер (нормално)";
			// 
			// i2b
			// 
			this->i2b->AutoSize = true;
			this->i2b->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->i2b->Location = System::Drawing::Point(130, 139);
			this->i2b->Name = L"i2b";
			this->i2b->Size = System::Drawing::Size(54, 25);
			this->i2b->TabIndex = 15;
			this->i2b->Text = L"Црна";
			// 
			// i1b
			// 
			this->i1b->AutoSize = true;
			this->i1b->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->i1b->Location = System::Drawing::Point(132, 73);
			this->i1b->Name = L"i1b";
			this->i1b->Size = System::Drawing::Size(48, 25);
			this->i1b->TabIndex = 14;
			this->i1b->Text = L"Бела";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 114);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 15);
			this->label4->TabIndex = 13;
			this->label4->Text = L"втор играч";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(54, 15);
			this->label3->TabIndex = 12;
			this->label3->Text = L"прв играч";
			// 
			// start
			// 
			this->start->AutoEllipsis = true;
			this->start->FlatAppearance->BorderSize = 0;
			this->start->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->start->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->start->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->start->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->start->ForeColor = System::Drawing::Color::Cornsilk;
			this->start->ImageIndex = 1;
			this->start->ImageList = this->btn;
			this->start->Location = System::Drawing::Point(252, 256);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(157, 40);
			this->start->TabIndex = 5;
			this->start->Text = L"Старт";
			this->start->UseVisualStyleBackColor = true;
			this->start->MouseLeave += gcnew System::EventHandler(this, &Form1::MouseLeave);
			this->start->Click += gcnew System::EventHandler(this, &Form1::start_Click);
			this->start->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseDown);
			this->start->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MouseUp);
			this->start->MouseEnter += gcnew System::EventHandler(this, &Form1::MouseEnter);
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Mistral", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(11, 136);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 27);
			this->textBox2->TabIndex = 4;
			this->textBox2->Text = L"Аида";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Mistral", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::GrayText;
			this->textBox1->Location = System::Drawing::Point(11, 75);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 27);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"Внеси име";
			this->textBox1->Click += gcnew System::EventHandler(this, &Form1::textBox1_Click);
			// 
			// unapreduvanje_slika
			// 
			this->unapreduvanje_slika->ImageIndex = 5;
			this->unapreduvanje_slika->ImageList = this->imageList1;
			this->unapreduvanje_slika->Location = System::Drawing::Point(118, 190);
			this->unapreduvanje_slika->Name = L"unapreduvanje_slika";
			this->unapreduvanje_slika->Size = System::Drawing::Size(60, 60);
			this->unapreduvanje_slika->TabIndex = 27;
			// 
			// minimiseBTN
			// 
			this->minimiseBTN->BackColor = System::Drawing::Color::Transparent;
			this->minimiseBTN->FlatAppearance->BorderSize = 0;
			this->minimiseBTN->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->minimiseBTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->minimiseBTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->minimiseBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->minimiseBTN->ForeColor = System::Drawing::Color::Gold;
			this->minimiseBTN->Location = System::Drawing::Point(763, 0);
			this->minimiseBTN->Name = L"minimiseBTN";
			this->minimiseBTN->Size = System::Drawing::Size(18, 21);
			this->minimiseBTN->TabIndex = 8;
			this->minimiseBTN->Text = L"--";
			this->minimiseBTN->UseVisualStyleBackColor = false;
			this->minimiseBTN->MouseLeave += gcnew System::EventHandler(this, &Form1::navBTN_MouseLeave);
			this->minimiseBTN->Click += gcnew System::EventHandler(this, &Form1::minimiseBTN_Click);
			this->minimiseBTN->MouseEnter += gcnew System::EventHandler(this, &Form1::navBTN_MouseEnter);
			// 
			// closeBTN
			// 
			this->closeBTN->BackColor = System::Drawing::Color::Transparent;
			this->closeBTN->FlatAppearance->BorderSize = 0;
			this->closeBTN->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->closeBTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->closeBTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->closeBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeBTN->Font = (gcnew System::Drawing::Font(L"Mistral", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->closeBTN->ForeColor = System::Drawing::Color::Gold;
			this->closeBTN->Location = System::Drawing::Point(782, 0);
			this->closeBTN->Name = L"closeBTN";
			this->closeBTN->Size = System::Drawing::Size(18, 21);
			this->closeBTN->TabIndex = 7;
			this->closeBTN->Text = L"X";
			this->closeBTN->UseVisualStyleBackColor = false;
			this->closeBTN->MouseLeave += gcnew System::EventHandler(this, &Form1::navBTN_MouseLeave);
			this->closeBTN->Click += gcnew System::EventHandler(this, &Form1::closeBTN_Click);
			this->closeBTN->MouseEnter += gcnew System::EventHandler(this, &Form1::navBTN_MouseEnter);
			// 
			// naslov
			// 
			this->naslov->AutoSize = true;
			this->naslov->BackColor = System::Drawing::Color::Transparent;
			this->naslov->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->naslov->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 20.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->naslov->ForeColor = System::Drawing::SystemColors::ControlText;
			this->naslov->Location = System::Drawing::Point(370, 8);
			this->naslov->Name = L"naslov";
			this->naslov->Size = System::Drawing::Size(71, 33);
			this->naslov->TabIndex = 11;
			this->naslov->Text = L"Крал";
			this->naslov->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::naslov_MouseMove);
			this->naslov->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::naslov_MouseDown);
			this->naslov->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::naslov_MouseUp);
			// 
			// timer_vi
			// 
			this->timer_vi->Interval = 5;
			this->timer_vi->Tick += gcnew System::EventHandler(this, &Form1::timer_vi_Tick);
			// 
			// min_btn
			// 
			this->min_btn->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"min_btn.ImageStream")));
			this->min_btn->TransparentColor = System::Drawing::Color::Transparent;
			this->min_btn->Images->SetKeyName(0, L"min_n.png");
			this->min_btn->Images->SetKeyName(1, L"min_o.png");
			// 
			// vreme_clock_i1
			// 
			this->vreme_clock_i1->Interval = 1000;
			this->vreme_clock_i1->Tick += gcnew System::EventHandler(this, &Form1::vreme_clock_i1_Tick);
			// 
			// vreme_clock_i2
			// 
			this->vreme_clock_i2->Interval = 1000;
			this->vreme_clock_i2->Tick += gcnew System::EventHandler(this, &Form1::vreme_clock_i2_Tick);
			// 
			// aboutBox
			// 
			this->aboutBox->BackColor = System::Drawing::Color::Transparent;
			this->aboutBox->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"aboutBox.BackgroundImage")));
			this->aboutBox->Controls->Add(this->label10);
			this->aboutBox->Controls->Add(this->label11);
			this->aboutBox->Controls->Add(this->nazadOdAboutBTN);
			this->aboutBox->Controls->Add(this->objasnuvanje);
			this->aboutBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->aboutBox->Location = System::Drawing::Point(144, 120);
			this->aboutBox->Name = L"aboutBox";
			this->aboutBox->Size = System::Drawing::Size(512, 360);
			this->aboutBox->TabIndex = 254;
			this->aboutBox->TabStop = false;
			this->aboutBox->Visible = false;
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(357, 252);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(140, 60);
			this->label10->TabIndex = 3;
			this->label10->Text = L"Стефан Спасовски 2010 година.";
			this->label10->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::Cornsilk;
			this->label11->Location = System::Drawing::Point(103, 20);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(99, 22);
			this->label11->TabIndex = 2;
			this->label11->Text = L"За Авторот";
			// 
			// nazadOdAboutBTN
			// 
			this->nazadOdAboutBTN->AutoSize = true;
			this->nazadOdAboutBTN->FlatAppearance->BorderSize = 0;
			this->nazadOdAboutBTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->nazadOdAboutBTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->nazadOdAboutBTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->nazadOdAboutBTN->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nazadOdAboutBTN->ForeColor = System::Drawing::Color::Cornsilk;
			this->nazadOdAboutBTN->Location = System::Drawing::Point(322, 311);
			this->nazadOdAboutBTN->Name = L"nazadOdAboutBTN";
			this->nazadOdAboutBTN->Size = System::Drawing::Size(75, 32);
			this->nazadOdAboutBTN->TabIndex = 1;
			this->nazadOdAboutBTN->Text = L"Назад";
			this->nazadOdAboutBTN->UseVisualStyleBackColor = true;
			this->nazadOdAboutBTN->Click += gcnew System::EventHandler(this, &Form1::nazadOdAboutBTN_Click);
			// 
			// objasnuvanje
			// 
			this->objasnuvanje->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->objasnuvanje->Location = System::Drawing::Point(34, 59);
			this->objasnuvanje->Name = L"objasnuvanje";
			this->objasnuvanje->Size = System::Drawing::Size(362, 194);
			this->objasnuvanje->TabIndex = 0;
			this->objasnuvanje->Text = resources->GetString(L"objasnuvanje.Text");
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(800, 600);
			this->Controls->Add(this->meny);
			this->Controls->Add(this->aboutBox);
			this->Controls->Add(this->newgame);
			this->Controls->Add(this->naslov);
			this->Controls->Add(this->minimiseBTN);
			this->Controls->Add(this->closeBTN);
			this->Controls->Add(this->igra);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Крал - Шаховска игра";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Enter);
			this->Enter += gcnew System::EventHandler(this, &Form1::Form1_Enter);
			this->igra->ResumeLayout(false);
			this->igra->PerformLayout();
			this->meny->ResumeLayout(false);
			this->meny->PerformLayout();
			this->newgame->ResumeLayout(false);
			this->newgame->PerformLayout();
			this->aboutBox->ResumeLayout(false);
			this->aboutBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
//OD TUKA MOI KODOVI==================================================================================================
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void newgame_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->meny->Visible=false;
			 this->newgame->Visible=true;
			 this->Text=L"Нова игра";
			 this->vreme->Text=Convert::ToString(Convert::ToString(vreme_min)+L":00 минути");
		 }
private: System::Void start_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->newgame->Visible=false;
			 pole->unapreduvanje=this->unapreduvanje_slika->ImageIndex;
			 this->pole->pochetok(this->prv_beli);
			 this->igra->Visible=true;
			 this->label1->Text=this->textBox1->Text;
			 this->label2->Text=this->textBox2->Text;
			 this->Text=Convert::ToString(this->label1->Text+L" против "+this->label2->Text);
			 this->vi_faza=0;
			 
			 //saatchinjata
			 this->vreme_ostanato_i1=this->vreme_min*60;
			 this->vreme_ostanato_i2=this->vreme_min*60;
			 this->vreme_i1->Text=Convert::ToString(Convert::ToString(vreme_ostanato_i1/60)+L":"+Convert::ToString(vreme_ostanato_i1%60));
			 this->vreme_i2->Text=Convert::ToString(Convert::ToString(vreme_ostanato_i2/60)+L":"+Convert::ToString(vreme_ostanato_i2%60));

			 //ako igrach 1 e so crni
			 if(this->prv_beli==false)
			 {
				 this->igrach_na_red=2;
				 this->vreme_clock_i2->Enabled=true;
				 System::Drawing::Image ^tmp;
				 for(int i=1;i<=6;i++)
				 {
					 tmp=this->imageList1->Images[i];
					 this->imageList1->Images[i]=this->imageList1->Images[i+6];
					 this->imageList1->Images[i+6]=tmp;
					 tmp=this->imageList1->Images[i+13];
					 this->imageList1->Images[i+13]=this->imageList1->Images[i+19];
					 this->imageList1->Images[i+19]=tmp;

				 }
			 }
			 else
			 {
				 this->igrach_na_red=1;
				 this->vreme_clock_i1->Enabled=true;
			 }

			 if(this->label1->Text->Equals(L"Аида") && igrach_na_red==1)
			 {
				 this->vreme_clock_i1->Enabled=false;
				 this->vreme_clock_i2->Enabled=false;
				 this->startVI();
				 this->raboti_i1->Visible=true;
			 }
			 if(this->label2->Text->Equals(L"Аида") && igrach_na_red==2)
			 {
				 this->vreme_clock_i1->Enabled=false;
				 this->vreme_clock_i2->Enabled=false;
				 this->startVI();
				 this->raboti_i2->Visible=true;
			 }
			 if(this->i2t->Text->Equals(L"Компјутер (лесно)"))
				 this->dlabochina=2;
			 if(this->i2t->Text->Equals(L"Компјутер (нормално)"))
				 this->dlabochina=3;

			 this->osvezi();
		 }
//iksot vo desno gore koga ke se klikne....
private: System::Void closeBTN_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ path ="output.data";
			 System::IO::StreamWriter^ dat;
			 if(this->meny->Visible==true)
			 {
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj("0"));
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj(L"Изберете една опција од \n долу наведените:"));
				 dat->Close();
			 }
			 
			 if(this->newgame->Visible==true)
			 {
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("0"));
				 dat->WriteLine(enkriptiraj("0"));
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj(L"Дали навистина сакате \n да излезете од играта?"));
				 dat->Close();
			 }

			 if(this->igra->Visible==true)
			 {
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("1"));
				 if(this->timer_vi->Enabled==true)
					dat->WriteLine(enkriptiraj("0"));
				 else
					dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj("1"));
				 dat->WriteLine(enkriptiraj(L"Озберете опција од \n  долу наведените:"));
				 dat->Close();
			 }

			 System::Windows::Forms::Form^ izlezna_forma = gcnew kral::close_form;
			 this->closeBTN->Enabled=false;
			 this->close->Enabled=false;
	 		 this->AddOwnedForm(izlezna_forma);
			 izlezna_forma->ShowDialog(this);

		 }
private: System::Void minimiseBTN_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->WindowState=System::Windows::Forms::FormWindowState::Minimized;
		 }

//labelata da ja dvizi celata forma
private: System::Void moveBTN_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->FormBorderStyle==System::Windows::Forms::FormBorderStyle::FixedDialog)
				 this->FormBorderStyle=System::Windows::Forms::FormBorderStyle::None;
			 else
				 this->FormBorderStyle=System::Windows::Forms::FormBorderStyle::FixedDialog;
		 }
private: System::Void naslov_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 drag=false;
		 }
private: System::Void naslov_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			if (drag)
            {
                int newY = this->Top + (e->Y - yposledno);
                int newX = this->Left + (e->X - xposledno);
                this->Location = System::Drawing::Point(newX, newY);
            }

		 }
private: System::Void naslov_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
            drag = true;
            xposledno = e->X;
            yposledno = e->Y;

		 }
//do tuka

private: System::Void i1bd_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->i1b->Text=L"Црна";
			 this->i1bg->Enabled=true;
			 this->i1bd->Enabled=false;

			 this->i2b->Text=L"Бела";
			 this->i2b1d->Enabled=true;
			 this->i2b1g->Enabled=false;

			 this->prv_beli=false;
		 }
private: System::Void i2b1g_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->i1b->Text=L"Црна";
			 this->i1bg->Enabled=true;
			 this->i1bd->Enabled=false;

			 this->i2b->Text=L"Бела";
			 this->i2b1d->Enabled=true;
			 this->i2b1g->Enabled=false;

			 this->prv_beli=false;
		 }
private: System::Void i1bg_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->i1b->Text=L"Бела";
			 this->i1bg->Enabled=false;
			 this->i1bd->Enabled=true;

			 this->i2b->Text=L"Црна";
			 this->i2b1d->Enabled=false;
			 this->i2b1g->Enabled=true;

			 this->prv_beli=true;
		 }
private: System::Void i2b1d_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->i1b->Text=L"Бела";
			 this->i1bg->Enabled=false;
			 this->i1bd->Enabled=true;

			 this->i2b->Text=L"Црна";
			 this->i2b1d->Enabled=false;
			 this->i2b1g->Enabled=true;

			 this->prv_beli=false;
		 }
private: System::Void i2b2g_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(i2b2d->Enabled==false)
			 {
				 i2b2d->Enabled=true;
				 i2t->Text=L"Компјутер (лесно)";
				 i2b2g->Location= System::Drawing::Point(383, 129);
				 i2b2d->Location= System::Drawing::Point(383, 153);
			 }
			 else
			 {
				 i2b2g->Enabled=false;
				 i2t->Text=L"Човек";
				 this->textBox2->Enabled=true;
				 this->textBox2->Text=L"Внеси име";
				 i2b2g->Location= System::Drawing::Point(285, 129);
				 i2b2d->Location= System::Drawing::Point(285, 153);
			 }
		 }
private: System::Void i2b2d_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(i2b2g->Enabled==false)
			 {
				 i2b2g->Enabled=true;
				 i2t->Text=L"Компјутер (лесно)";
				 this->textBox2->Enabled=false;
				 this->textBox2->Text=L"Аида";
				 i2b2g->Location= System::Drawing::Point(383, 129);
				 i2b2d->Location= System::Drawing::Point(383, 153);
			 }
			 else
			 {
				 i2b2d->Enabled=false;
				 i2t->Text=L"Компјутер (нормално)";
				 i2b2g->Location= System::Drawing::Point(413, 129);
				 i2b2d->Location= System::Drawing::Point(413, 153);
			 }
		 }
private: System::Void textBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->textBox1->Text="";
			 this->textBox1->ForeColor=System::Drawing::SystemColors::WindowText;
		 }
private: System::Void dbutton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!(timer_vi->Enabled==true))
			 {
			 System::String ^ime;
			 ime=(((Button^)sender)->Name)->Substring(6);
			 int broj=Convert::ToInt16(ime);
			 int br,bu;
			 br=(broj-1)/8;
			 bu=(broj-1)%8;


//od tuka pochnuva obichno klikanje bez VI

			 //proverka dali e klik za igranje ili klik za selektiranje

			 //ako e klik za selektiranje
			 if(klik==false)
			 {
				 if(pole->tablata[br][bu].owner==igrach_na_red)
				 {
					pole->gen_mozni(br,bu);
					pole->br_select=br;
					pole->bu_select=bu;
					this->klik=true;
				 }
			 }
			 //ako e klik za igranje
			 else
			 {
				 //proverka dali e kliknato na pole shto moze da se igra
				 bool test=false;
				 for(int i=0;i<pole->tablata[pole->br_select][pole->bu_select].mozni.size();i++)
					 if(pole->tablata[pole->br_select][pole->bu_select].mozni[i].br==br && pole->tablata[pole->br_select][pole->bu_select].mozni[i].bu==bu)
						 test=true;

				 //dali se igra
				 if(test==true)
				 {

					//potegot
					 this->poteg(pole->br_select ,pole->bu_select ,br ,bu);
					 this->presmetaj_i_prikzi_kraj(3-igrach_na_red);
					 
					 //semna na igrachi
					 igrach_na_red=3-igrach_na_red;
					 //proverka dali igrachot shto sega stana igrach na red e AI
					 if(!this->i2t->Text->Equals(L"Човек"))
					 {
						 if(this->label1->Text->Equals(L"Аида") && igrach_na_red==1)
						 {
							 this->startVI();
							 this->raboti_i1->Visible=true;
						 }
						 if(this->label2->Text->Equals(L"Аида") && igrach_na_red==2)
						 {
							 this->startVI();
							 this->raboti_i2->Visible=true;
						 }
					 }
					 else
					 {
						 if(this->vreme_clock_i1->Enabled==true && this->vreme_clock_i2->Enabled==false)
						 {
							 this->vreme_clock_i1->Enabled=false;
							 this->vreme_clock_i2->Enabled=true;
						 }
						 else
						 {
							 if(this->vreme_clock_i1->Enabled==false && this->vreme_clock_i2->Enabled==true)
							 {
								 this->vreme_clock_i1->Enabled=true;
								 this->vreme_clock_i2->Enabled=false;
							 }
						 }
					 }




				 }
				 //otselektiranje
				 this->klik=false;
			 }
//tuka zavrshuva

			 this->osvezi();			 
			 }
		 }
private: System::Void unap_d_Click(System::Object^  sender, System::EventArgs^  e) {
			 switch(this->unapreduvanje_slika->ImageIndex)
			 {
			 case 5:
				 this->unapreduvanje_slika->ImageIndex--;
				 this->unapreduvanje_text->Text=L"Ланфер/Ловец";
				 this->unap_g->Enabled=true;
				 break;
			 case 4:
				 this->unapreduvanje_slika->ImageIndex--;
				 this->unapreduvanje_text->Text=L"Коњ";
				 break;
			 case 3:
				 this->unapreduvanje_slika->ImageIndex--;
				 this->unapreduvanje_text->Text=L"Топ";
				 this->unap_d->Enabled=false;
				 break;
			 }
		 }
private: System::Void unap_g_Click(System::Object^  sender, System::EventArgs^  e) {
			 switch(this->unapreduvanje_slika->ImageIndex)
			 {
			 case 2:
				 this->unapreduvanje_slika->ImageIndex++;
				 this->unapreduvanje_text->Text=L"Коњ";
				 this->unap_d->Enabled=true;
				 break;
			 case 3:
				 this->unapreduvanje_slika->ImageIndex++;
				 this->unapreduvanje_text->Text=L"Ланфер/Ловец";
				 break;
			 case 4:
				 this->unapreduvanje_slika->ImageIndex++;
				 this->unapreduvanje_text->Text=L"Кралица";
				 this->unap_g->Enabled=false;
				 break;
			 }
		 }
private: System::Void navBTN_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 ((Button^)sender)->ForeColor=System::Drawing::Color::Azure;//=System::Drawing::Font::Bold;
		 }
private: System::Void navBTN_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 ((Button^)sender)->ForeColor=System::Drawing::Color::Gold;//=System::Drawing::Font::Bold;
		 }
private: System::Void timer_vi_Tick(System::Object^  sender, System::EventArgs^  e) {
			 this->vi_faza++;
			 switch(this->vi_faza)
			 {
			 case 1:
				 if(this->vreme_clock_i1->Enabled==true && this->vreme_clock_i2->Enabled==false)
				 {
					 this->vreme_clock_i1->Enabled=false;
					 this->vreme_clock_i2->Enabled=true;
				 }
				 else
				 {
					 if(this->vreme_clock_i1->Enabled==false && this->vreme_clock_i2->Enabled==true)
					 {
						 this->vreme_clock_i1->Enabled=true;
						 this->vreme_clock_i2->Enabled=false;
					 }
					 else
					 {
						 if(this->vreme_clock_i1->Enabled==false && this->vreme_clock_i2->Enabled==false)
						 {
							 if(igrach_na_red==1)
								 this->vreme_clock_i1->Enabled=true;
							 else
								 this->vreme_clock_i2->Enabled=true;
						 }
					 }
				 }
				 break;
			 case 2:
				 rezultat=gcnew VIStart(pole,igrach_na_red,dlabochina);
				 DThread=gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(rezultat,&VIStart::exec));
			//	 DThread->Priority=System::Threading::ThreadPriority::AboveNormal;
				 DThread->Start();
				 break;
			 case 3:
				 if(DThread->IsAlive)
				 {
					 this->vi_faza--;
					 this->timer_vi->Interval=500;
				 }
				 else
				 {
					 this->timer_vi->Interval=5;
					 this->poteg(rezultat->odBR,rezultat->odBU,rezultat->doBR,rezultat->doBU);
				 }
				 break;
			 case 4:
//				 this->osvezi_labela(this->vi_poteg_do_broj,this->vi_poteg_do_bukva);
//				 this->osvezi_labela(this->vi_poteg_od_broj,this->vi_poteg_od_bukva);

				 this->osvezi();
				 this->timer_vi->Enabled=false;
		 		 
				 if(igrach_na_red==1)
					 this->raboti_i1->Visible=false;
				 else
					 this->raboti_i2->Visible=false;
				 
				 this->vi_faza=0;
			 	 if(this->vreme_clock_i1->Enabled==true && this->vreme_clock_i2->Enabled==false)
				 {
					 this->vreme_clock_i1->Enabled=false;
					 this->vreme_clock_i2->Enabled=true;
				 }
				 else
				 {
					 if(this->vreme_clock_i1->Enabled==false && this->vreme_clock_i2->Enabled==true)
					 {
						 this->vreme_clock_i1->Enabled=true;
						 this->vreme_clock_i2->Enabled=false;
					 }
				 }

				 igrach_na_red=3-igrach_na_red;
				 this->presmetaj_i_prikzi_kraj(igrach_na_red);
//////debag///// this->pole->analizaVoDatoteka(igrach_na_red);
				 this->closeBTN->Enabled=true;
			 default:
				 break;
			 }
		 }
private: System::Void vreme_bg_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(vreme_min>150)
				 this->checkBox1->Checked=false;
			 else
				 this->vreme_min++;
			 if(this->vreme_bd->Enabled==false)
				 vreme_bd->Enabled=true;
			 this->vreme->Text=Convert::ToString(Convert::ToString(vreme_min)+L":00 минути");
		 }
private: System::Void vreme_bd_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(vreme_min>6)
				 this->vreme_min--;
			 if(vreme_min==6)
			 {
				 this->vreme_bd->Enabled=false;
				 vreme_min--;
			 }
			 this->vreme->Text=Convert::ToString(Convert::ToString(vreme_min)+L":00 минути");
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(this->checkBox1->Checked==true)
			 {
				 this->vreme->Enabled=true;
				 this->vreme_bd->Enabled=true;
				 this->vreme_bg->Enabled=true;
			 }
			 else
			 {
				 this->vreme->Enabled=false;
				 this->vreme_bd->Enabled=false;
				 this->vreme_bg->Enabled=false;
			 }
		 }
private: System::Void vreme_clock_i1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 this->vreme_ostanato_i1--;
			 this->vreme_i1->Text=Convert::ToString(Convert::ToString(vreme_ostanato_i1/60)+L":"+Convert::ToString(vreme_ostanato_i1%60));
		 }
private: System::Void vreme_clock_i2_Tick(System::Object^  sender, System::EventArgs^  e) {
 			 this->vreme_ostanato_i2--;
			 this->vreme_i2->Text=Convert::ToString(Convert::ToString(vreme_ostanato_i2/60)+L":"+Convert::ToString(vreme_ostanato_i2%60));

		 }
private: System::Void Form1_Enter(System::Object^  sender, System::EventArgs^  e) {
			String^ path = "input.data";
			String^ in;
			 if(System::IO::File::Exists(path)==true)
			{
				System::IO::StreamReader^ dat= System::IO::File::OpenText(path);
				in=dekriptiraj(dat->ReadLine());
				dat->Close();
				System::IO::File::Delete(path);
				
				char a=Convert::ToChar(in);	
				switch(a)
				{
					//samo enable na kopchinjata za izleguvanje
				case '0':
					this->closeBTN->Enabled=true;
					this->close->Enabled=true;
					break;

					//nova igra
				case '1':
					this->spremi_za_nova_igra();
					this->prv_beli=true;

					if(this->igra->Visible==true)
						this->igra->Visible=false;
					if(this->meny->Visible==true)
						this->meny->Visible=false;

					this->newgame->Visible=true;
					this->closeBTN->Enabled=true;
					this->close->Enabled=true;
					break;


					//revanz
				case '2':
					 
					 //saatchinjata
					 this->vreme_ostanato_i1=this->vreme_min*60;
					 this->vreme_ostanato_i2=this->vreme_min*60;
					 this->vreme_i1->Text=Convert::ToString(Convert::ToString(vreme_ostanato_i1/60)+L":"+Convert::ToString(vreme_ostanato_i1%60));
					 this->vreme_i2->Text=Convert::ToString(Convert::ToString(vreme_ostanato_i2/60)+L":"+Convert::ToString(vreme_ostanato_i2%60));
					 
					 this->spremi_za_nova_igra();
					 prv_beli=(!prv_beli);
					 this->pole->pochetok(this->prv_beli);
					 
					 //ako igrach 1 e so crni
					 if(this->prv_beli==false)
					 {
						 this->igrach_na_red=2;
						 this->vreme_clock_i2->Enabled=true;
						 System::Drawing::Image ^tmp;
						 for(int i=1;i<=6;i++)
						 {
							 tmp=this->imageList1->Images[i];
							 this->imageList1->Images[i]=this->imageList1->Images[i+6];
							 this->imageList1->Images[i+6]=tmp;
							 tmp=this->imageList1->Images[i+13];
							 this->imageList1->Images[i+13]=this->imageList1->Images[i+19];
							 this->imageList1->Images[i+19]=tmp;

						 }
					 }
					 else
					 {
						 this->igrach_na_red=1;
						 this->vreme_clock_i1->Enabled=true;
					 }

					 if(this->label1->Text->Equals(L"Аида") && igrach_na_red==1)
					 {
						 this->startVI();
						 this->raboti_i1->Visible=true;
						 this->vreme_clock_i1->Enabled=false;
						 this->vreme_clock_i2->Enabled=false;
					 }
					 if(this->label2->Text->Equals(L"Аида") && igrach_na_red==2)
					 {
						 this->startVI();
						 this->raboti_i2->Visible=true;
						 this->vreme_clock_i1->Enabled=false;
						 this->vreme_clock_i2->Enabled=false;
					 }
					 this->igra->Visible=false;
					 this->igra->Visible=true;
					this->closeBTN->Enabled=true;
					this->close->Enabled=true;
					this->osvezi();
					break;
				default:
					break;
				}
			}

		 }

private: System::Void close_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 ((System::Windows::Forms::Button^)sender)->ImageIndex+=2;
		 }
private: System::Void MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 ((System::Windows::Forms::Button^)sender)->ImageIndex-=2;
		 }
private: System::Void MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 ((System::Windows::Forms::Button^)sender)->ImageIndex--;
		 }
private: System::Void MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 ((System::Windows::Forms::Button^)sender)->ImageIndex++;
		 }
private: System::Void btn_nazad1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->newgame->Visible=false;
			 this->meny->Visible=true;
			 this->Text=L"Крал-Шаховска игра";
		 }
private: System::Void about_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->meny->Visible=false;
			 this->aboutBox->Visible=true;
			 this->Text=L"За авторот";
		 }
private: System::Void nazadOdAboutBTN_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->aboutBox->Visible=false;
			 this->meny->Visible=true;
			 this->Text=L"Крал-Шаховска игра";
		 }
};
}