#ifndef CLOSE_FORM_H
#define CLOSE_FORM_H

#include "enkripcija.h"
#pragma once

namespace kral {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace enkripcija;

	/// <summary>
	/// Summary for close_form
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class close_form : public System::Windows::Forms::Form
	{
	public:
		close_form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~close_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  close;
	protected: 
	private: System::Windows::Forms::Label^  tekst;
	private: System::Windows::Forms::Label^  naslov;

	private: System::Windows::Forms::Button^  closeBTN;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		static bool drag=false;
		static bool klik=false;
		static int xposledno;
		static int yposledno;
	private: System::Windows::Forms::Button^  nova_partija;
	private: System::Windows::Forms::Button^  revansh;
	private: System::Windows::Forms::Button^  Otkazi;
	private: System::Windows::Forms::ImageList^  btn;
	private: System::ComponentModel::IContainer^  components;





#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(close_form::typeid));
			this->close = (gcnew System::Windows::Forms::Button());
			this->btn = (gcnew System::Windows::Forms::ImageList(this->components));
			this->tekst = (gcnew System::Windows::Forms::Label());
			this->naslov = (gcnew System::Windows::Forms::Label());
			this->closeBTN = (gcnew System::Windows::Forms::Button());
			this->nova_partija = (gcnew System::Windows::Forms::Button());
			this->revansh = (gcnew System::Windows::Forms::Button());
			this->Otkazi = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// close
			// 
			this->close->BackColor = System::Drawing::Color::Transparent;
			this->close->FlatAppearance->BorderSize = 0;
			this->close->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->close->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->close->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->close->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->close->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->close->ForeColor = System::Drawing::Color::Cornsilk;
			this->close->ImageIndex = 1;
			this->close->ImageList = this->btn;
			this->close->Location = System::Drawing::Point(62, 216);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(157, 40);
			this->close->TabIndex = 0;
			this->close->Text = L"Излез";
			this->close->UseVisualStyleBackColor = false;
			this->close->MouseLeave += gcnew System::EventHandler(this, &close_form::MouseLeave);
			this->close->Click += gcnew System::EventHandler(this, &close_form::close_Click);
			this->close->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseDown);
			this->close->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseUp);
			this->close->MouseEnter += gcnew System::EventHandler(this, &close_form::MouseEnter);
			// 
			// btn
			// 
			this->btn->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"btn.ImageStream")));
			this->btn->TransparentColor = System::Drawing::Color::Transparent;
			this->btn->Images->SetKeyName(0, L"overtop.png");
			this->btn->Images->SetKeyName(1, L"btn.png");
			this->btn->Images->SetKeyName(2, L"clicked.png");
			// 
			// tekst
			// 
			this->tekst->BackColor = System::Drawing::Color::Transparent;
			this->tekst->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->tekst->Location = System::Drawing::Point(18, 32);
			this->tekst->Name = L"tekst";
			this->tekst->Size = System::Drawing::Size(245, 78);
			this->tekst->TabIndex = 1;
			this->tekst->Text = L"Изберете опција";
			this->tekst->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// naslov
			// 
			this->naslov->AutoSize = true;
			this->naslov->BackColor = System::Drawing::Color::Transparent;
			this->naslov->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->naslov->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 20.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->naslov->ForeColor = System::Drawing::SystemColors::ControlText;
			this->naslov->Location = System::Drawing::Point(107, 7);
			this->naslov->Name = L"naslov";
			this->naslov->Size = System::Drawing::Size(71, 33);
			this->naslov->TabIndex = 14;
			this->naslov->Text = L"Крал";
			this->naslov->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::naslov_MouseMove);
			this->naslov->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::naslov_MouseDown);
			this->naslov->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::naslov_MouseUp);
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
			this->closeBTN->Location = System::Drawing::Point(263, -1);
			this->closeBTN->Name = L"closeBTN";
			this->closeBTN->Size = System::Drawing::Size(18, 21);
			this->closeBTN->TabIndex = 12;
			this->closeBTN->Text = L"X";
			this->closeBTN->UseVisualStyleBackColor = false;
			this->closeBTN->Click += gcnew System::EventHandler(this, &close_form::closeBTN_Click);
			// 
			// nova_partija
			// 
			this->nova_partija->BackColor = System::Drawing::Color::Transparent;
			this->nova_partija->FlatAppearance->BorderSize = 0;
			this->nova_partija->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->nova_partija->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->nova_partija->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->nova_partija->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->nova_partija->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->nova_partija->ForeColor = System::Drawing::Color::Cornsilk;
			this->nova_partija->ImageIndex = 1;
			this->nova_partija->ImageList = this->btn;
			this->nova_partija->Location = System::Drawing::Point(62, 124);
			this->nova_partija->Name = L"nova_partija";
			this->nova_partija->Size = System::Drawing::Size(157, 40);
			this->nova_partija->TabIndex = 15;
			this->nova_partija->Text = L"Нова партија шах";
			this->nova_partija->UseVisualStyleBackColor = false;
			this->nova_partija->MouseLeave += gcnew System::EventHandler(this, &close_form::MouseLeave);
			this->nova_partija->Click += gcnew System::EventHandler(this, &close_form::nova_partija_Click);
			this->nova_partija->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseDown);
			this->nova_partija->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseUp);
			this->nova_partija->MouseEnter += gcnew System::EventHandler(this, &close_form::MouseEnter);
			// 
			// revansh
			// 
			this->revansh->BackColor = System::Drawing::Color::Transparent;
			this->revansh->FlatAppearance->BorderSize = 0;
			this->revansh->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->revansh->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->revansh->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->revansh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->revansh->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->revansh->ForeColor = System::Drawing::Color::Cornsilk;
			this->revansh->ImageIndex = 1;
			this->revansh->ImageList = this->btn;
			this->revansh->Location = System::Drawing::Point(62, 170);
			this->revansh->Name = L"revansh";
			this->revansh->Size = System::Drawing::Size(157, 40);
			this->revansh->TabIndex = 16;
			this->revansh->Text = L"Реванш";
			this->revansh->UseVisualStyleBackColor = false;
			this->revansh->MouseLeave += gcnew System::EventHandler(this, &close_form::MouseLeave);
			this->revansh->Click += gcnew System::EventHandler(this, &close_form::revansh_Click);
			this->revansh->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseDown);
			this->revansh->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseUp);
			this->revansh->MouseEnter += gcnew System::EventHandler(this, &close_form::MouseEnter);
			// 
			// Otkazi
			// 
			this->Otkazi->BackColor = System::Drawing::Color::Transparent;
			this->Otkazi->FlatAppearance->BorderSize = 0;
			this->Otkazi->FlatAppearance->CheckedBackColor = System::Drawing::Color::Transparent;
			this->Otkazi->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->Otkazi->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->Otkazi->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Otkazi->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->Otkazi->ForeColor = System::Drawing::Color::Cornsilk;
			this->Otkazi->ImageIndex = 1;
			this->Otkazi->ImageList = this->btn;
			this->Otkazi->Location = System::Drawing::Point(62, 262);
			this->Otkazi->Name = L"Otkazi";
			this->Otkazi->Size = System::Drawing::Size(157, 40);
			this->Otkazi->TabIndex = 17;
			this->Otkazi->Text = L"Откажи";
			this->Otkazi->UseVisualStyleBackColor = false;
			this->Otkazi->MouseLeave += gcnew System::EventHandler(this, &close_form::MouseLeave);
			this->Otkazi->Click += gcnew System::EventHandler(this, &close_form::Otkazi_Click);
			this->Otkazi->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseDown);
			this->Otkazi->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &close_form::MouseUp);
			this->Otkazi->MouseEnter += gcnew System::EventHandler(this, &close_form::MouseEnter);
			// 
			// close_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Bisque;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(280, 320);
			this->Controls->Add(this->Otkazi);
			this->Controls->Add(this->revansh);
			this->Controls->Add(this->nova_partija);
			this->Controls->Add(this->naslov);
			this->Controls->Add(this->closeBTN);
			this->Controls->Add(this->tekst);
			this->Controls->Add(this->close);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"close_form";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"close_form";
			this->Load += gcnew System::EventHandler(this, &close_form::close_form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
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
	private: System::Void closeBTN_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ path ="input.data";
				 System::IO::StreamWriter^ dat;
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("0"));
				 dat->Close(); 
				 this->Owner->Show();
				 this->Close();
			 }
	private: System::Void Otkazi_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ path ="input.data";
				 System::IO::StreamWriter^ dat;
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("0"));
				 dat->Close(); 
				 this->Owner->Show();
				 this->Close();
			 }
	private: System::Void close_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Owner->Close();
			 }
private: System::Void nova_partija_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ path ="input.data";
				 System::IO::StreamWriter^ dat;
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("1"));
				 dat->Close(); 
				 this->Owner->Show();
				 this->Close();
		 }
private: System::Void revansh_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ path ="input.data";
				 System::IO::StreamWriter^ dat;
				 if(System::IO::File::Exists(path)==true)
					 System::IO::File::Delete(path);
				 dat=System::IO::File::AppendText(path);
				 dat->WriteLine(enkriptiraj("2"));
				 dat->Close(); 
				 this->Owner->Show();
				 this->Close();
		 }
private: System::Void close_form_Load(System::Object^  sender, System::EventArgs^  e) {
				 String^ path = "output.data";
				 String^ in;
				 if(System::IO::File::Exists(path)==true)
				 {
					System::IO::StreamReader^ dat= System::IO::File::OpenText(path);
					
					//nova partija kopcheto
					in=dekriptiraj(dat->ReadLine());
					char a=Convert::ToChar(in);	
					if(a=='0')
						this->nova_partija->Enabled=false;
					else
						this->nova_partija->Enabled=true;
					
					//revanz
					in=dekriptiraj(dat->ReadLine());
					a=Convert::ToChar(in);	
					if(a=='0')
						this->revansh->Enabled=false;
					else
						this->revansh->Enabled=true;

					//izlez
					in=dekriptiraj(dat->ReadLine());
					a=Convert::ToChar(in);	
					if(a=='0')
						this->close->Enabled=false;
					else
						this->close->Enabled=true;

					//otkazi
					in=dekriptiraj(dat->ReadLine());
					a=Convert::ToChar(in);	
					if(a=='0')
						this->Otkazi->Enabled=false;
					else
						this->Otkazi->Enabled=true;

					//tekstot
					in=dekriptiraj(dat->ReadToEnd());
					this->tekst->Text=in;

					dat->Close();
					System::IO::File::Delete(path);
				 }
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
};
}

#endif