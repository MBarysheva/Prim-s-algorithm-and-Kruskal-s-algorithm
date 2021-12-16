#pragma once

#include <fstream>
#include <msclr/marshal_cppstd.h>
#include <string>

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		Graphics^ gr;
		Pen^ pen, ^penScheduleKruskal, ^penSchedulePrim;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

  private: System::Windows::Forms::Button ^ button2;
  private: System::Windows::Forms::Label^ label3;

  private:
   System::Windows::Forms::Button ^ button3;

  private:


  private:
   System::Windows::Forms::Label ^ label4;



	public:
		MyForm(void)
		{
      //размеры и цвета
			InitializeComponent();
			this->gr = CreateGraphics();
			this->pen = gcnew Pen(Color::Black);
			this->penScheduleKruskal = gcnew Pen(Color::Yellow);
			this->penSchedulePrim = gcnew Pen(Color::Blue);
			this->penScheduleKruskal->Width = 1.0;
			this->penSchedulePrim->Width = 1.0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
			}
		}


	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
           this->label1 = (gcnew System::Windows::Forms::Label());
           this->label2 = (gcnew System::Windows::Forms::Label());
           this->label3 = (gcnew System::Windows::Forms::Label());
           this->label4 = (gcnew System::Windows::Forms::Label());
           this->button2 = (gcnew System::Windows::Forms::Button());
           this->button3 = (gcnew System::Windows::Forms::Button());
           this->SuspendLayout();
           //
           // label1
           //
           this->label1->AutoSize = true;
           this->label1->Location = System::Drawing::Point(700, 394);
           this->label1->Name = L"label1";
           this->label1->Size = System::Drawing::Size(72, 13);
           this->label1->TabIndex = 2;
           this->label1->Text = L"Число ребер";
           this->label1->Visible = false;
           this->label1->Click +=
               gcnew System::EventHandler(this, &MyForm::label1_Click);
           //
           // label2
           //
           this->label2->AutoSize = true;
           this->label2->Location = System::Drawing::Point(12, 39);
           this->label2->Name = L"label2";
           this->label2->Size = System::Drawing::Size(40, 13);
           this->label2->TabIndex = 3;
           this->label2->Text = L"Время";
           this->label2->Visible = false;
           this->label2->Click +=
               gcnew System::EventHandler(this, &MyForm::label2_Click);
           //
           // label3
           //
           this->label3->AutoSize = true;
           this->label3->Location = System::Drawing::Point(587, 373);
           this->label3->Name = L"label3";
           this->label3->Size = System::Drawing::Size(108, 13);
           this->label3->TabIndex = 5;
           this->label3->Text = L"Алгоритм Краскала";
           this->label3->Visible = false;
           this->label3->Click +=
               gcnew System::EventHandler(this, &MyForm::label3_Click);
           //
           // label4
           //
           this->label4->AutoSize = true;
           this->label4->Location = System::Drawing::Point(626, 34);
           this->label4->Name = L"label4";
           this->label4->Size = System::Drawing::Size(93, 13);
           this->label4->TabIndex = 7;
           this->label4->Text = L"Алгоритм Прима";
           this->label4->Visible = false;
           this->label4->Click +=
               gcnew System::EventHandler(this, &MyForm::label4_Click);
           //
           // button2
           //
           this->button2->Location = System::Drawing::Point(5, 5);
           this->button2->Name = L"button2";
           this->button2->Size = System::Drawing::Size(137, 23);
           this->button2->TabIndex = 8;
           this->button2->Text = L"Нарисовать систему координат";
           this->button2->UseVisualStyleBackColor = true;
           this->button2->Click +=
               gcnew System::EventHandler(this, &MyForm::button2_Click);
           //
           // button3
           //
           this->button3->Location = System::Drawing::Point(5, 34);
           this->button3->Name = L"button3";
           this->button3->Size = System::Drawing::Size(125, 23);
           this->button3->TabIndex = 9;
           this->button3->Text = L"Нарисовать график";
           this->button3->UseVisualStyleBackColor = true;
           this->button3->Click +=
               gcnew System::EventHandler(this, &MyForm::button3_Click);
           //
           // MyForm
           //
           this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
           this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
           this->BackColor = System::Drawing::SystemColors::Window;
           this->ClientSize = System::Drawing::Size(840, 528);
           this->Controls->Add(this->button3);
           this->Controls->Add(this->button2);
           this->Controls->Add(this->label4);
           this->Controls->Add(this->label3);
           this->Controls->Add(this->label2);
           this->Controls->Add(this->label1);
           this->Name = L"MyForm";
           this->StartPosition =
               System::Windows::Forms::FormStartPosition::CenterScreen;
           this->Text = L"Graphics";
           this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
           this->ResumeLayout(false);
           this->PerformLayout();
         }
#pragma endregion
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	button3->Visible = false;
  this->label4->Visible = true;
  this->label3->Visible = true;
	//get size graf
	std::ifstream fileKruskal("../KruskalTest.txt");
	std::ifstream filePrim("../PrimTest.txt");
	const int bufferLenght = 250;
	char bufferKruskal[bufferLenght], bufferPrim[bufferLenght];

	fileKruskal.getline(bufferKruskal, bufferLenght, '\n');
	filePrim.getline(bufferPrim, bufferLenght, '\n');

	std::string temporaryString;
	int number = 0, maxEdgeCount = 0, startEdgeCount = 0, stepEdgeCount = 1;
	for (int i = 0; bufferKruskal[i] != '\0'; i++)
	{
		if (bufferKruskal[i] == ' ')
		{
			int value = atoi(temporaryString.c_str());

			if (number == 1)
				maxEdgeCount = value;
			else if (number == 2)
				startEdgeCount = value;

			temporaryString.clear();
			number++;
		}
		else
		{
			temporaryString += bufferKruskal[i];
		}
	}
	stepEdgeCount = atoi(temporaryString.c_str());

	int countEdge = (maxEdgeCount - startEdgeCount) / stepEdgeCount;



	int stepX = 700 / countEdge, stepY = 10;
  //разграничение у графика, типа 0, 10, 20
	/*for (int i = 57; i < 745; i += stepX)
		gr->DrawLine(pen, i, 398, i, 402);

	for (int i = 390; i > 55; i -= stepY)
		gr->DrawLine(pen, 48, i, 52, i);

	this->pen->Width = 4.0;
	gr->DrawEllipse(pen, 48, 398, 4, 4);
  */
	gr->DrawLine(penScheduleKruskal, 785, 506, 815, 506);
	gr->DrawLine(penSchedulePrim, 785, 536, 815, 536);

	/*for (int i = 0; i < countEdge; i++)
	{
		dataGridView1->Rows->Add();
	}*/

	//drawing schedule
	int lastPointX = 50, lastPointKruskalY = 400, lastPointPrimY = 400, startPointY = 400, numberRow = 0;
	double timeKruskal, timePrim;
	int numberIter = startEdgeCount;
	while (!fileKruskal.eof() && !filePrim.eof())
	{
		fileKruskal.getline(bufferKruskal, bufferLenght, '\n');
		filePrim.getline(bufferPrim, bufferLenght, '\n');

		timeKruskal = atof(bufferKruskal);
		timePrim = atof(bufferPrim);

		/*this->dataGridView1->Rows[numberRow]->Cells[0]->Value = numberIter;
		this->dataGridView1->Rows[numberRow]->Cells[1]->Value = timeKruskal;
		this->dataGridView1->Rows[numberRow++]->Cells[2]->Value = timePrim;*/

		gr->DrawLine(penScheduleKruskal, lastPointX, lastPointKruskalY, lastPointX + stepX, startPointY - timeKruskal * 10.);
		gr->DrawLine(penSchedulePrim, lastPointX, lastPointPrimY, lastPointX + stepX, startPointY - timePrim * 10.);
		lastPointX += stepX;
    lastPointX = lastPointX-0.4 ;
		lastPointKruskalY = (startPointY - timeKruskal * 10.);
		lastPointPrimY = (startPointY - timePrim * 10.);

		numberIter += stepEdgeCount;
	}
}

private:
 System::Void label1_Click(System::Object ^ sender, System::EventArgs ^ e) {}

private:
 System::Void MyForm_Load(System::Object ^ sender, System::EventArgs ^ e) {}

private:
 System::Void label2_Click(System::Object ^ sender, System::EventArgs ^ e) {}

private:
 System::Void label3_Click(System::Object ^ sender, System::EventArgs ^ e) {}

private:
 System::Void label4_Click(System::Object ^ sender, System::EventArgs ^ e) {}

private:
private:
 System::Void button2_Click(System::Object ^ sender, System::EventArgs ^ e) {
            // drawing system coordinates

            this->gr->DrawLine(pen, 50, 400, 750, 400);
            this->gr->DrawLine(pen, 50, 400, 50, 50);
            this->gr->DrawLine(pen, 50, 50, 55, 55);
            this->gr->DrawLine(pen, 50, 50, 45, 55);
            this->gr->DrawLine(pen, 750, 400, 745, 395);
            this->gr->DrawLine(pen, 750, 400, 745, 405);
            button2->Visible = false;
            this->label1->Visible = true;
            this->label2->Visible = true;
          }

         };
         }
