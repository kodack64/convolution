#pragma once

#include "portaudio.h"
#include "MyHostApi.h"
#include <Windows.h>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

using namespace std;
using namespace msclr::interop;
#undef GetCurrentDirectory

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->CollectAudioLine();
			this->InitializeLineComboBox();
			nowConverting=false;
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		MyHostApiList* myHostApiList;
		int currentInputDeviceId;
		int currentOutputDeviceId;
		bool nowConverting;
	private: System::Windows::Forms::TextBox^  Textbox_InputFileName;
	private: System::Windows::Forms::TextBox^  Textbox_OutputFileName;
	private: System::Windows::Forms::CheckBox^  Check_OutputToFile;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;


		void CollectAudioLine(){
			myHostApiList = new MyHostApiList;
			myHostApiList->Initialize();
		}
		void InitializeLineComboBox(){
			for(unsigned int i=0;i<myHostApiList->hostApiList.size();i++){
				this->Combo_HostApiSelect->Items->Add(gcnew System::String(myHostApiList->hostApiList[i]->name.c_str()));
			}
			this->Combo_HostApiSelect->SelectedIndex=myHostApiList->defaultHostApi;
//			currentInputDeviceId=myHostApiList->hostApiList[myHostApiList->defaultHostApi]->defaultInputDevice;
//			currentOutputDeviceId=myHostApiList->hostApiList[myHostApiList->defaultHostApi]->defaultOutputDevice;
		}
		void ResetLineComboBox(){
			MyHostApi* hostApi;
			MyDevice* device;

			this->Combo_InputLineSelect->Items->Clear();
			this->Combo_OutputLineSelect->Items->Clear();

			hostApi = myHostApiList->hostApiList[this->Combo_HostApiSelect->SelectedIndex];

			for(unsigned int i=0;i<hostApi->inputDeviceList.size();i++){
				device = hostApi->inputDeviceList[i];
				this->Combo_InputLineSelect->Items->Add(gcnew System::String(device->name.c_str()));
			}
			for(unsigned int i=0;i<hostApi->outputDeviceList.size();i++){
				device = hostApi->outputDeviceList[i];
				this->Combo_OutputLineSelect->Items->Add(gcnew System::String(device->name.c_str()));
			}
			this->Combo_InputLineSelect->SelectedIndex=hostApi->defaultInputDevice;
			this->Combo_OutputLineSelect->SelectedIndex=hostApi->defaultOutputDevice;
		}
		void ChangeLineInComboBox(){
			int selectedHostApi=this->Combo_HostApiSelect->SelectedIndex;
			int selectedInputIndex=this->Combo_InputLineSelect->SelectedIndex;
			currentInputDeviceId=myHostApiList->hostApiList[selectedHostApi]->inputDeviceList[selectedInputIndex]->deviceId;
		}
		void ChangeLineOutComboBox(){
			int selectedHostApi=this->Combo_HostApiSelect->SelectedIndex;
			int selectedOutputIndex=this->Combo_OutputLineSelect->SelectedIndex;
			currentOutputDeviceId=myHostApiList->hostApiList[selectedHostApi]->outputDeviceList[selectedOutputIndex]->deviceId;
		}
	private: System::Windows::Forms::RadioButton^  Radio_SpeakerSwitchBoth;
	private: System::Windows::Forms::RadioButton^  Radio_SpeakerSwitchLeft;
	private: System::Windows::Forms::RadioButton^  Radio_SpeakerSwitchRight;
	private: System::Windows::Forms::RadioButton^  Radio_SpeakerConvolutionThrough;
	private: System::Windows::Forms::GroupBox^  Input;
	private: System::Windows::Forms::RadioButton^  Radio_InputFromLine;
	private: System::Windows::Forms::RadioButton^  Radio_InputFromFile;
	private: System::Windows::Forms::ComboBox^  Combo_InputLineSelect;
	private: System::Windows::Forms::GroupBox^  groupBox1;

	private: System::Windows::Forms::Button^  Button_InputFileSelect;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  Check_PlayAfterConvert;

	private: System::Windows::Forms::Button^  Button_OutputFileSelect;


	private: System::Windows::Forms::ComboBox^  Combo_OutputLineSelect;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::RadioButton^  Radio_SpeakerConvolutionUse;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::RadioButton^  Radio_HallTypeKomaba;
	private: System::Windows::Forms::RadioButton^  Radio_HallTypeHongo;
	private: System::Windows::Forms::RadioButton^  Radio_HallTypeNone;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::ComboBox^  Combo_HostApiSelect;
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->Radio_SpeakerSwitchBoth = (gcnew System::Windows::Forms::RadioButton());
			this->Radio_SpeakerSwitchLeft = (gcnew System::Windows::Forms::RadioButton());
			this->Radio_SpeakerSwitchRight = (gcnew System::Windows::Forms::RadioButton());
			this->Radio_SpeakerConvolutionThrough = (gcnew System::Windows::Forms::RadioButton());
			this->Input = (gcnew System::Windows::Forms::GroupBox());
			this->Textbox_InputFileName = (gcnew System::Windows::Forms::TextBox());
			this->Button_InputFileSelect = (gcnew System::Windows::Forms::Button());
			this->Radio_InputFromLine = (gcnew System::Windows::Forms::RadioButton());
			this->Radio_InputFromFile = (gcnew System::Windows::Forms::RadioButton());
			this->Combo_InputLineSelect = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Radio_SpeakerConvolutionUse = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->Check_OutputToFile = (gcnew System::Windows::Forms::CheckBox());
			this->Textbox_OutputFileName = (gcnew System::Windows::Forms::TextBox());
			this->Check_PlayAfterConvert = (gcnew System::Windows::Forms::CheckBox());
			this->Button_OutputFileSelect = (gcnew System::Windows::Forms::Button());
			this->Combo_OutputLineSelect = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->Radio_HallTypeNone = (gcnew System::Windows::Forms::RadioButton());
			this->Radio_HallTypeKomaba = (gcnew System::Windows::Forms::RadioButton());
			this->Radio_HallTypeHongo = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Combo_HostApiSelect = (gcnew System::Windows::Forms::ComboBox());
			this->Input->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// Radio_SpeakerSwitchBoth
			// 
			this->Radio_SpeakerSwitchBoth->AutoSize = true;
			this->Radio_SpeakerSwitchBoth->Checked = true;
			this->Radio_SpeakerSwitchBoth->Location = System::Drawing::Point(15, 18);
			this->Radio_SpeakerSwitchBoth->Name = L"Radio_SpeakerSwitchBoth";
			this->Radio_SpeakerSwitchBoth->Size = System::Drawing::Size(71, 16);
			this->Radio_SpeakerSwitchBoth->TabIndex = 1;
			this->Radio_SpeakerSwitchBoth->TabStop = true;
			this->Radio_SpeakerSwitchBoth->Text = L"左右両方";
			this->Radio_SpeakerSwitchBoth->UseVisualStyleBackColor = true;
			// 
			// Radio_SpeakerSwitchLeft
			// 
			this->Radio_SpeakerSwitchLeft->AutoSize = true;
			this->Radio_SpeakerSwitchLeft->Location = System::Drawing::Point(15, 60);
			this->Radio_SpeakerSwitchLeft->Name = L"Radio_SpeakerSwitchLeft";
			this->Radio_SpeakerSwitchLeft->Size = System::Drawing::Size(56, 16);
			this->Radio_SpeakerSwitchLeft->TabIndex = 2;
			this->Radio_SpeakerSwitchLeft->TabStop = true;
			this->Radio_SpeakerSwitchLeft->Text = L"左のみ";
			this->Radio_SpeakerSwitchLeft->UseVisualStyleBackColor = true;
			// 
			// Radio_SpeakerSwitchRight
			// 
			this->Radio_SpeakerSwitchRight->AutoSize = true;
			this->Radio_SpeakerSwitchRight->Location = System::Drawing::Point(15, 38);
			this->Radio_SpeakerSwitchRight->Name = L"Radio_SpeakerSwitchRight";
			this->Radio_SpeakerSwitchRight->Size = System::Drawing::Size(56, 16);
			this->Radio_SpeakerSwitchRight->TabIndex = 3;
			this->Radio_SpeakerSwitchRight->TabStop = true;
			this->Radio_SpeakerSwitchRight->Text = L"右のみ";
			this->Radio_SpeakerSwitchRight->UseVisualStyleBackColor = true;
			// 
			// Radio_SpeakerConvolutionThrough
			// 
			this->Radio_SpeakerConvolutionThrough->AutoSize = true;
			this->Radio_SpeakerConvolutionThrough->Location = System::Drawing::Point(20, 40);
			this->Radio_SpeakerConvolutionThrough->Name = L"Radio_SpeakerConvolutionThrough";
			this->Radio_SpeakerConvolutionThrough->Size = System::Drawing::Size(52, 16);
			this->Radio_SpeakerConvolutionThrough->TabIndex = 4;
			this->Radio_SpeakerConvolutionThrough->TabStop = true;
			this->Radio_SpeakerConvolutionThrough->Text = L"しない";
			this->Radio_SpeakerConvolutionThrough->UseVisualStyleBackColor = true;
			// 
			// Input
			// 
			this->Input->Controls->Add(this->Textbox_InputFileName);
			this->Input->Controls->Add(this->Button_InputFileSelect);
			this->Input->Controls->Add(this->Radio_InputFromLine);
			this->Input->Controls->Add(this->Radio_InputFromFile);
			this->Input->Location = System::Drawing::Point(10, 113);
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(578, 95);
			this->Input->TabIndex = 5;
			this->Input->TabStop = false;
			this->Input->Text = L"入力";
			// 
			// Textbox_InputFileName
			// 
			this->Textbox_InputFileName->Location = System::Drawing::Point(175, 29);
			this->Textbox_InputFileName->Name = L"Textbox_InputFileName";
			this->Textbox_InputFileName->ReadOnly = true;
			this->Textbox_InputFileName->Size = System::Drawing::Size(397, 19);
			this->Textbox_InputFileName->TabIndex = 6;
			this->Textbox_InputFileName->Text = L"input.wav";
			// 
			// Button_InputFileSelect
			// 
			this->Button_InputFileSelect->Location = System::Drawing::Point(127, 27);
			this->Button_InputFileSelect->Name = L"Button_InputFileSelect";
			this->Button_InputFileSelect->Size = System::Drawing::Size(42, 23);
			this->Button_InputFileSelect->TabIndex = 4;
			this->Button_InputFileSelect->Text = L"選択";
			this->Button_InputFileSelect->UseVisualStyleBackColor = true;
			this->Button_InputFileSelect->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// Radio_InputFromLine
			// 
			this->Radio_InputFromLine->AutoSize = true;
			this->Radio_InputFromLine->Enabled = false;
			this->Radio_InputFromLine->Location = System::Drawing::Point(20, 57);
			this->Radio_InputFromLine->Name = L"Radio_InputFromLine";
			this->Radio_InputFromLine->Size = System::Drawing::Size(73, 16);
			this->Radio_InputFromLine->TabIndex = 2;
			this->Radio_InputFromLine->TabStop = true;
			this->Radio_InputFromLine->Text = L"ライン入力";
			this->Radio_InputFromLine->UseVisualStyleBackColor = true;
			// 
			// Radio_InputFromFile
			// 
			this->Radio_InputFromFile->AutoSize = true;
			this->Radio_InputFromFile->Checked = true;
			this->Radio_InputFromFile->Location = System::Drawing::Point(20, 30);
			this->Radio_InputFromFile->Name = L"Radio_InputFromFile";
			this->Radio_InputFromFile->Size = System::Drawing::Size(81, 16);
			this->Radio_InputFromFile->TabIndex = 1;
			this->Radio_InputFromFile->TabStop = true;
			this->Radio_InputFromFile->Text = L"ファイル入力";
			this->Radio_InputFromFile->UseVisualStyleBackColor = true;
			// 
			// Combo_InputLineSelect
			// 
			this->Combo_InputLineSelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->Combo_InputLineSelect->FormattingEnabled = true;
			this->Combo_InputLineSelect->Location = System::Drawing::Point(81, 39);
			this->Combo_InputLineSelect->Name = L"Combo_InputLineSelect";
			this->Combo_InputLineSelect->Size = System::Drawing::Size(443, 20);
			this->Combo_InputLineSelect->TabIndex = 0;
			this->Combo_InputLineSelect->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::Combo_InputLineSelect_SelectedIndexChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->Radio_SpeakerConvolutionUse);
			this->groupBox1->Controls->Add(this->Radio_SpeakerConvolutionThrough);
			this->groupBox1->Location = System::Drawing::Point(10, 214);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(124, 101);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"キャビネットの畳込み";
			// 
			// Radio_SpeakerConvolutionUse
			// 
			this->Radio_SpeakerConvolutionUse->AutoSize = true;
			this->Radio_SpeakerConvolutionUse->Checked = true;
			this->Radio_SpeakerConvolutionUse->Location = System::Drawing::Point(20, 18);
			this->Radio_SpeakerConvolutionUse->Name = L"Radio_SpeakerConvolutionUse";
			this->Radio_SpeakerConvolutionUse->Size = System::Drawing::Size(42, 16);
			this->Radio_SpeakerConvolutionUse->TabIndex = 4;
			this->Radio_SpeakerConvolutionUse->TabStop = true;
			this->Radio_SpeakerConvolutionUse->Text = L"する";
			this->Radio_SpeakerConvolutionUse->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->Radio_SpeakerSwitchBoth);
			this->groupBox2->Controls->Add(this->Radio_SpeakerSwitchRight);
			this->groupBox2->Controls->Add(this->Radio_SpeakerSwitchLeft);
			this->groupBox2->Location = System::Drawing::Point(261, 214);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(162, 101);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"建物内のスピーカーの配置";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->Check_OutputToFile);
			this->groupBox3->Controls->Add(this->Textbox_OutputFileName);
			this->groupBox3->Controls->Add(this->Check_PlayAfterConvert);
			this->groupBox3->Controls->Add(this->Button_OutputFileSelect);
			this->groupBox3->Location = System::Drawing::Point(10, 321);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(578, 83);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"出力";
			// 
			// Check_OutputToFile
			// 
			this->Check_OutputToFile->AutoSize = true;
			this->Check_OutputToFile->Checked = true;
			this->Check_OutputToFile->CheckState = System::Windows::Forms::CheckState::Checked;
			this->Check_OutputToFile->Location = System::Drawing::Point(20, 30);
			this->Check_OutputToFile->Name = L"Check_OutputToFile";
			this->Check_OutputToFile->Size = System::Drawing::Size(92, 16);
			this->Check_OutputToFile->TabIndex = 8;
			this->Check_OutputToFile->Text = L"ファイルで出力";
			this->Check_OutputToFile->UseVisualStyleBackColor = true;
			this->Check_OutputToFile->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Check_OutputToFile_CheckedChanged);
			// 
			// Textbox_OutputFileName
			// 
			this->Textbox_OutputFileName->Location = System::Drawing::Point(175, 28);
			this->Textbox_OutputFileName->Name = L"Textbox_OutputFileName";
			this->Textbox_OutputFileName->ReadOnly = true;
			this->Textbox_OutputFileName->Size = System::Drawing::Size(397, 19);
			this->Textbox_OutputFileName->TabIndex = 7;
			this->Textbox_OutputFileName->Text = L"output.wav";
			// 
			// Check_PlayAfterConvert
			// 
			this->Check_PlayAfterConvert->AutoSize = true;
			this->Check_PlayAfterConvert->Checked = true;
			this->Check_PlayAfterConvert->CheckState = System::Windows::Forms::CheckState::Checked;
			this->Check_PlayAfterConvert->Location = System::Drawing::Point(20, 55);
			this->Check_PlayAfterConvert->Name = L"Check_PlayAfterConvert";
			this->Check_PlayAfterConvert->Size = System::Drawing::Size(184, 16);
			this->Check_PlayAfterConvert->TabIndex = 6;
			this->Check_PlayAfterConvert->Text = L"変換後に出力デバイスで再生する";
			this->Check_PlayAfterConvert->UseVisualStyleBackColor = true;
			this->Check_PlayAfterConvert->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Check_PlayAfterConvert_CheckedChanged);
			// 
			// Button_OutputFileSelect
			// 
			this->Button_OutputFileSelect->Location = System::Drawing::Point(127, 26);
			this->Button_OutputFileSelect->Name = L"Button_OutputFileSelect";
			this->Button_OutputFileSelect->Size = System::Drawing::Size(42, 23);
			this->Button_OutputFileSelect->TabIndex = 4;
			this->Button_OutputFileSelect->Text = L"選択";
			this->Button_OutputFileSelect->UseVisualStyleBackColor = true;
			this->Button_OutputFileSelect->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// Combo_OutputLineSelect
			// 
			this->Combo_OutputLineSelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->Combo_OutputLineSelect->FormattingEnabled = true;
			this->Combo_OutputLineSelect->Location = System::Drawing::Point(81, 65);
			this->Combo_OutputLineSelect->Name = L"Combo_OutputLineSelect";
			this->Combo_OutputLineSelect->Size = System::Drawing::Size(445, 20);
			this->Combo_OutputLineSelect->TabIndex = 0;
			this->Combo_OutputLineSelect->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::Combo_OutputLineSelect_SelectedIndexChanged);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(267, 410);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"実行";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->Radio_HallTypeNone);
			this->groupBox4->Controls->Add(this->Radio_HallTypeKomaba);
			this->groupBox4->Controls->Add(this->Radio_HallTypeHongo);
			this->groupBox4->Location = System::Drawing::Point(140, 214);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(115, 101);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"建物の畳込み";
			// 
			// Radio_HallTypeNone
			// 
			this->Radio_HallTypeNone->AutoSize = true;
			this->Radio_HallTypeNone->Location = System::Drawing::Point(20, 60);
			this->Radio_HallTypeNone->Name = L"Radio_HallTypeNone";
			this->Radio_HallTypeNone->Size = System::Drawing::Size(44, 16);
			this->Radio_HallTypeNone->TabIndex = 4;
			this->Radio_HallTypeNone->TabStop = true;
			this->Radio_HallTypeNone->Text = L"無し";
			this->Radio_HallTypeNone->UseVisualStyleBackColor = true;
			this->Radio_HallTypeNone->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_HallTypeNone_CheckedChanged);
			// 
			// Radio_HallTypeKomaba
			// 
			this->Radio_HallTypeKomaba->AutoSize = true;
			this->Radio_HallTypeKomaba->Checked = true;
			this->Radio_HallTypeKomaba->Location = System::Drawing::Point(20, 18);
			this->Radio_HallTypeKomaba->Name = L"Radio_HallTypeKomaba";
			this->Radio_HallTypeKomaba->Size = System::Drawing::Size(59, 16);
			this->Radio_HallTypeKomaba->TabIndex = 1;
			this->Radio_HallTypeKomaba->TabStop = true;
			this->Radio_HallTypeKomaba->Text = L"駒場祭";
			this->Radio_HallTypeKomaba->UseVisualStyleBackColor = true;
			this->Radio_HallTypeKomaba->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_HallTypeKomaba_CheckedChanged);
			// 
			// Radio_HallTypeHongo
			// 
			this->Radio_HallTypeHongo->AutoSize = true;
			this->Radio_HallTypeHongo->Location = System::Drawing::Point(20, 38);
			this->Radio_HallTypeHongo->Name = L"Radio_HallTypeHongo";
			this->Radio_HallTypeHongo->Size = System::Drawing::Size(59, 16);
			this->Radio_HallTypeHongo->TabIndex = 3;
			this->Radio_HallTypeHongo->TabStop = true;
			this->Radio_HallTypeHongo->Text = L"五月祭";
			this->Radio_HallTypeHongo->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label3);
			this->groupBox5->Controls->Add(this->label2);
			this->groupBox5->Controls->Add(this->label1);
			this->groupBox5->Controls->Add(this->Combo_HostApiSelect);
			this->groupBox5->Controls->Add(this->Combo_InputLineSelect);
			this->groupBox5->Controls->Add(this->Combo_OutputLineSelect);
			this->groupBox5->Location = System::Drawing::Point(11, 12);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(571, 95);
			this->groupBox5->TabIndex = 9;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"デバイス";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 12);
			this->label3->TabIndex = 9;
			this->label3->Text = L"ホスト";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 12);
			this->label2->TabIndex = 8;
			this->label2->Text = L"ライン出力";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 12);
			this->label1->TabIndex = 7;
			this->label1->Text = L"ライン入力";
			// 
			// Combo_HostApiSelect
			// 
			this->Combo_HostApiSelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->Combo_HostApiSelect->FormattingEnabled = true;
			this->Combo_HostApiSelect->Location = System::Drawing::Point(81, 13);
			this->Combo_HostApiSelect->Name = L"Combo_HostApiSelect";
			this->Combo_HostApiSelect->Size = System::Drawing::Size(234, 20);
			this->Combo_HostApiSelect->TabIndex = 6;
			this->Combo_HostApiSelect->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::Combo_HostApiSelect_SelectedIndexChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(602, 437);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->Input);
			this->Name = L"MyForm";
			this->Text = L"ELS Concert Convolution GUI";
			this->Input->ResumeLayout(false);
			this->Input->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			if(nowConverting==true){
				MessageBox::Show(this,"変換中です。","エラー");
				return;
			}
			nowConverting=true;
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(STARTUPINFO));
			ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
			si.cb = sizeof(STARTUPINFO);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_SHOWNORMAL;

			stringstream ss;
			ss << "Convolution.exe";
			ss << " -inputFile \"" << marshal_as<string,System::String^>(this->Textbox_InputFileName->Text) << "\"";
			ss << " -inputLine " << currentInputDeviceId;
			ss << " -outputFile \"" << marshal_as<string,System::String^>(this->Textbox_OutputFileName->Text) << "\"";
			ss << " -outputLine " << currentOutputDeviceId;

			if(this->Radio_InputFromFile->Checked){
				ss << " -inputFromFile";
			}else{
				ss << " -inputFromLine";
			}

			if(this->Check_OutputToFile->Checked){
				ss << " -outputToFile";
			}
			if(this->Check_PlayAfterConvert->Checked){
				ss << " -outputToLine";
			}

			if(this->Radio_SpeakerSwitchBoth->Checked){
				ss << " -speakerSwitchBoth";
			}else if(this->Radio_SpeakerSwitchRight->Checked){
				ss << " -speakerSwitchRight";
			}else{
				ss << " -speakerSwitchLeft";
			}

			if(this->Radio_SpeakerConvolutionUse->Checked){
				ss << " -speakerConvolution";
			}else{
				ss << " -speakerNotConvolution";
			}

			if(this->Radio_HallTypeHongo->Checked){
				ss << " -hallHongo";
			}else if(this->Radio_HallTypeKomaba->Checked){
				ss << " -hallKomaba";
			}else{
				ss << " -hallNone";
			}
			cout << ss.str() << endl;
			if(CreateProcess(NULL,(LPSTR)ss.str().c_str(), NULL, NULL,FALSE, 0, NULL, NULL, &si, &pi)!=0){
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			}else{
				MessageBox::Show(this,"Convolution.exeが見つかりません。","エラー");
			}
			nowConverting=false;
		}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			OpenFileDialog^ dlg = gcnew OpenFileDialog;
			dlg->InitialDirectory=System::IO::Directory::GetCurrentDirectory();
			dlg->Filter = "音声ファイル(*.wav)|*.wav;";
			if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel){
				return;
			}else{
				this->Textbox_InputFileName->Text=dlg->FileName;
			}
		}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			SaveFileDialog^ dlg = gcnew SaveFileDialog;
			dlg->InitialDirectory=System::IO::Directory::GetCurrentDirectory();
			dlg->Filter = "音声ファイル(*.wav)|*.wav;";
			dlg->RestoreDirectory=true;
			if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel){
				return; 
			}else{
				this->Textbox_OutputFileName->Text=dlg->FileName;
			}
		}
	private: System::Void Combo_HostApiSelect_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			ResetLineComboBox();
		}
	private: System::Void Combo_InputLineSelect_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			ChangeLineInComboBox();
		}
	private: System::Void Combo_OutputLineSelect_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			ChangeLineOutComboBox();
		}
private: System::Void Radio_HallTypeNone_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(this->Radio_HallTypeNone->Checked==true){
				 this->Radio_SpeakerSwitchBoth->Checked=true;
				 this->Radio_SpeakerSwitchLeft->Enabled=false;
				 this->Radio_SpeakerSwitchRight->Enabled=false;
			 }
		 }
private: System::Void Radio_HallTypeKomaba_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(this->Radio_HallTypeKomaba->Checked==true){
				 this->Radio_SpeakerSwitchLeft->Enabled=true;
				 this->Radio_SpeakerSwitchRight->Enabled=true;
			 }
		 }
private: System::Void Check_OutputToFile_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(this->Check_OutputToFile->Checked==false){
				 this->Check_PlayAfterConvert->Checked=true;
			 }
		 }
private: System::Void Check_PlayAfterConvert_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(this->Check_PlayAfterConvert->Checked==false){
				 this->Check_OutputToFile->Checked=true;
			 }
		 }
};
}
