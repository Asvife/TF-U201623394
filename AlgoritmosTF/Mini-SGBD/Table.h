#pragma once
#include <list>
#include "Fila.h"
#include "rDato.h"
#include "MSG.h"

namespace MiniSGBD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Windows;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Resumen de Table
	/// </summary>


	public ref class Table : public System::Windows::Forms::Form
	{
		void Clear()
		{
			comboBox1->SelectedItem = "None";
			comboBox2->SelectedItem = "None";
			filter1 = "None";
			filter2 = "None";
			textBox1->Text = "";
			textBox2->Text = "";
			lblState->Text = "";
		}
		void ClearTable()
		{
			Clear();
			dataGridView1->Rows->Clear();
			dataGridView1->Columns->Clear();

		}
		void UpdateTree()
		{
			displayTree = rows[*currRow]->getCurrentTree();
			string filterData1 = "";
			MarshalString(textBox1->Text, filterData1);
			string filterData2 = "";
			MarshalString(textBox2->Text, filterData2);
			string name = "";
			if (dataGridView1->SortedColumn != nullptr)
				MarshalString(dataGridView1->SortedColumn->Name, name);
			else
				MarshalString(dataGridView1->Columns[0]->Name, name);
			if (filter1 != "None")
			{
				if (filter1 == "Mayor")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Greater(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter1 == "Menor")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Minor(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter1 == "Igual")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Equals(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter1 == "Empieza Con")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Starts(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter1 == "Termina Con")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Ends(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter1 == "Esta Contenido En")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Inside(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter1 == "No Esta Contenido En")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData1), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->NotInside(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
			}

			if (filter2 != "None")
			{
				if (filter2 == "Mayor")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Greater(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter2 == "Menor")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Minor(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter2 == "Igual")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Equals(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter2 == "Empieza Con")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Starts(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter2 == "Termina Con")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Ends(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter2 == "Esta Contenido En")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->Inside(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
				else if (filter2 == "No Esta Contenido En")
				{
					Dato* a = new Dato(vector<string>(rows[*currRow]->getTags().size(), filterData2), rows[*currRow]->getTags());
					vector<Dato*> dataVec = displayTree->NotInside(name, a);
					displayTree = rows[*currRow]->getCurrentTree()->VectortoBST(dataVec);
				}
			}
			if (filter1 == "None" && filter2 == "None")
			{
				displayTree = rows[*currRow]->getCurrentTree();
			}
			vector<Dato*> vec;
			displayTree->BSTtoVector(vec);
			Populate(vec);
		}
		void FilterColumns()
		{
			for each (DataGridViewColumn ^ Column in dataGridView1->Columns)
			{
				Column->Visible = true;
				Disponibles->Clear();
			}

			for each (auto Item in ColumnasFiltro->SelectedItems)
			{
				for each (DataGridViewColumn ^ Column in dataGridView1->Columns)
				{
					if (Item->ToString() == Column->Name)
					{
						Column->Visible = false;
						Disponibles->Add(Column->Name);
					}
				}
			}
		}
		void Populate(vector<Dato*> vec)
		{
			datos = VectoList(vec);

			ColumnasFiltro->Items->Clear();

			//Añadir Columnas
			dataGridView1->ColumnCount = Tags->Count;
			for (int i = 0; i < Tags->Count; i++)
			{
				dataGridView1->Columns[i]->Name = Tags[i];
				dataGridView1->Columns[i]->ReadOnly = true;
				ColumnasFiltro->Items->Add(Tags[i]);
			}


			//Añadir Filas
			dataGridView1->Rows->Clear();
			for (int j = 0; j < datos->Count; j++)
			{
				dataGridView1->Rows->Add();
				for (int i = 0; i < datos[j]->getData()->Count; i++)
				{
					dataGridView1->Rows[j]->Cells[i]->Value = datos[j]->getData()[i];
					dataGridView1->Rows[j]->Cells[i]->ReadOnly = true;

				}
				dataGridView1->Rows[j]->ReadOnly = true;
			}
		}

		void Init()
		{
			Tags->Clear();
			String^ str;
			for each (string ss in rows[*currRow]->getTags())
			{
				str = gcnew String(ss.c_str());
				Tags->Add(str);
			}
			displayTree = rows[*currRow]->getCurrentTree();
			Populate(rows[*currRow]->getCurrentVector());
		}

		void MarshalString(String^ s, string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		rDato^ DtoD(Dato* dato)
		{
			List<String^>^ list = gcnew List<String^>;
			String^ str;

			for each (string ss in dato->getData())
			{
				str = gcnew String(ss.c_str());
				list->Add(str);
			}

			rDato^ nDato = gcnew rDato(list);
			return nDato;
		}

		List<rDato^>^ VectoList(vector<Dato*> vec)
		{
			List<rDato^>^ lst = gcnew List<rDato^>;
			rDato^ dato;
			for each (Dato * var in vec)
			{
				dato = DtoD(var);
				lst->Add(dato);
			}
			return lst;
		}

	public:
		Table(void)
		{
			InitializeComponent();
			row = new Fila("Input/Data.txt");
			row2 = new Fila("Input/Data2.txt");
			row3 = new Fila("Input/Data3.txt");
			rows = new Fila * [4];
			rows[0] = row;
			rows[1] = row2;
			rows[2] = row3;
			rows[3] = rowCreated;
			currRow = new int(0);
			Tags = gcnew List<String^>();
			Disponibles = gcnew List<String^>();
			displayTree = rows[*currRow]->getCurrentTree();

		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Table()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:




	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;
		Fila* row;
		Fila* row2;
		Fila* row3;
		Fila* rowCreated;
		Fila** rows;
		List<rDato^>^ datos;
	private: System::Windows::Forms::Button^ Importar;

	private: System::Windows::Forms::Button^ Exportar;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ComboBox^ DataSets;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ComboBox^ comboBox2;
		   String^ filter1;
		   String^ filter2;
		   List<String^>^ Tags;
		   List<String^>^ Disponibles;
	private: System::Windows::Forms::TextBox^ textBox2;
		   AvlTree* displayTree;
	private: System::Windows::Forms::Button^ filtrarColumna;
	private: System::Windows::Forms::ListBox^ ColumnasFiltro;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBoxCol;
	private: System::Windows::Forms::TextBox^ textBoxRow;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ lblState;




		   int* currRow;
#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Método necesario para admitir el Diseñador. No se puede modificar
		   /// el contenido de este método con el editor de código.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->Importar = (gcnew System::Windows::Forms::Button());
			   this->Exportar = (gcnew System::Windows::Forms::Button());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->DataSets = (gcnew System::Windows::Forms::ComboBox());
			   this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			   this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->filtrarColumna = (gcnew System::Windows::Forms::Button());
			   this->ColumnasFiltro = (gcnew System::Windows::Forms::ListBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->textBoxCol = (gcnew System::Windows::Forms::TextBox());
			   this->textBoxRow = (gcnew System::Windows::Forms::TextBox());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->lblState = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // dataGridView1
			   // 
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Location = System::Drawing::Point(170, 110);
			   this->dataGridView1->Name = L"dataGridView1";
			   this->dataGridView1->Size = System::Drawing::Size(447, 258);
			   this->dataGridView1->TabIndex = 0;
			   this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Table::dataGridView1_CellContentClick);
			   this->dataGridView1->ColumnDisplayIndexChanged += gcnew System::Windows::Forms::DataGridViewColumnEventHandler(this, &Table::dataGridView1_ColumnDisplayIndexChanged);
			   this->dataGridView1->ColumnSortModeChanged += gcnew System::Windows::Forms::DataGridViewColumnEventHandler(this, &Table::dataGridView1_ColumnSortModeChanged);
			   this->dataGridView1->Sorted += gcnew System::EventHandler(this, &Table::dataGridView1_Sorted);
			   // 
			   // Importar
			   // 
			   this->Importar->Location = System::Drawing::Point(170, 374);
			   this->Importar->Name = L"Importar";
			   this->Importar->Size = System::Drawing::Size(75, 23);
			   this->Importar->TabIndex = 1;
			   this->Importar->Text = L"Importar";
			   this->Importar->UseVisualStyleBackColor = true;
			   this->Importar->Click += gcnew System::EventHandler(this, &Table::Importar_Click);
			   // 
			   // Exportar
			   // 
			   this->Exportar->Location = System::Drawing::Point(542, 374);
			   this->Exportar->Name = L"Exportar";
			   this->Exportar->Size = System::Drawing::Size(75, 23);
			   this->Exportar->TabIndex = 2;
			   this->Exportar->Text = L"Exportar";
			   this->Exportar->UseVisualStyleBackColor = true;
			   this->Exportar->Click += gcnew System::EventHandler(this, &Table::Exportar_Click);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(262, 34);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(265, 20);
			   this->textBox1->TabIndex = 4;
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(543, 81);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(75, 23);
			   this->button2->TabIndex = 5;
			   this->button2->Text = L"Filtrar";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Table::button2_Click);
			   // 
			   // DataSets
			   // 
			   this->DataSets->FormattingEnabled = true;
			   this->DataSets->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Data1", L"Data2", L"Data3" });
			   this->DataSets->Location = System::Drawing::Point(624, 127);
			   this->DataSets->Name = L"DataSets";
			   this->DataSets->Size = System::Drawing::Size(121, 21);
			   this->DataSets->TabIndex = 6;
			   this->DataSets->SelectedIndexChanged += gcnew System::EventHandler(this, &Table::DataSets_SelectedIndexChanged);
			   // 
			   // comboBox1
			   // 
			   this->comboBox1->FormattingEnabled = true;
			   this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				   L"None", L"Mayor", L"Menor", L"Igual", L"Empieza Con",
					   L"Termina Con", L"Esta Contenido En", L"No Esta Contenido En"
			   });
			   this->comboBox1->Location = System::Drawing::Point(171, 33);
			   this->comboBox1->Name = L"comboBox1";
			   this->comboBox1->Size = System::Drawing::Size(85, 21);
			   this->comboBox1->TabIndex = 7;
			   this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Table::comboBox1_SelectedIndexChanged);
			   // 
			   // comboBox2
			   // 
			   this->comboBox2->FormattingEnabled = true;
			   this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				   L"None", L"Mayor", L"Menor", L"Igual", L"Empieza Con",
					   L"Termina Con", L"Esta Contenido En", L"No Esta Contenido En"
			   });
			   this->comboBox2->Location = System::Drawing::Point(171, 83);
			   this->comboBox2->Name = L"comboBox2";
			   this->comboBox2->Size = System::Drawing::Size(85, 21);
			   this->comboBox2->TabIndex = 8;
			   this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Table::comboBox2_SelectedIndexChanged);
			   // 
			   // textBox2
			   // 
			   this->textBox2->Location = System::Drawing::Point(262, 84);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(265, 20);
			   this->textBox2->TabIndex = 9;
			   // 
			   // filtrarColumna
			   // 
			   this->filtrarColumna->Location = System::Drawing::Point(624, 347);
			   this->filtrarColumna->Name = L"filtrarColumna";
			   this->filtrarColumna->Size = System::Drawing::Size(121, 23);
			   this->filtrarColumna->TabIndex = 10;
			   this->filtrarColumna->Text = L"Filtrar Columna";
			   this->filtrarColumna->UseVisualStyleBackColor = true;
			   this->filtrarColumna->Click += gcnew System::EventHandler(this, &Table::filtrarColumna_Click);
			   // 
			   // ColumnasFiltro
			   // 
			   this->ColumnasFiltro->FormattingEnabled = true;
			   this->ColumnasFiltro->Location = System::Drawing::Point(624, 246);
			   this->ColumnasFiltro->Name = L"ColumnasFiltro";
			   this->ColumnasFiltro->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			   this->ColumnasFiltro->Size = System::Drawing::Size(120, 95);
			   this->ColumnasFiltro->TabIndex = 12;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(623, 110);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(51, 13);
			   this->label1->TabIndex = 13;
			   this->label1->Text = L"DataSets";
			   this->label1->Click += gcnew System::EventHandler(this, &Table::label1_Click);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(170, 17);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(35, 13);
			   this->label2->TabIndex = 14;
			   this->label2->Text = L"Filtro1";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(170, 67);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(35, 13);
			   this->label3->TabIndex = 15;
			   this->label3->Text = L"Filtro2";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(621, 230);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(81, 13);
			   this->label4->TabIndex = 16;
			   this->label4->Text = L"Filtrar Columnas";
			   // 
			   // button3
			   // 
			   this->button3->Location = System::Drawing::Point(28, 110);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(94, 23);
			   this->button3->TabIndex = 18;
			   this->button3->Text = L"CrearTabla";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &Table::button3_Click);
			   // 
			   // textBoxCol
			   // 
			   this->textBoxCol->Location = System::Drawing::Point(11, 152);
			   this->textBoxCol->Name = L"textBoxCol";
			   this->textBoxCol->Size = System::Drawing::Size(52, 20);
			   this->textBoxCol->TabIndex = 19;
			   // 
			   // textBoxRow
			   // 
			   this->textBoxRow->Location = System::Drawing::Point(93, 150);
			   this->textBoxRow->Name = L"textBoxRow";
			   this->textBoxRow->Size = System::Drawing::Size(52, 20);
			   this->textBoxRow->TabIndex = 20;
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(12, 136);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(53, 13);
			   this->label5->TabIndex = 21;
			   this->label5->Text = L"Columnas";
			   this->label5->Click += gcnew System::EventHandler(this, &Table::label5_Click);
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(94, 136);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(28, 13);
			   this->label6->TabIndex = 22;
			   this->label6->Text = L"Filas";
			   // 
			   // lblState
			   // 
			   this->lblState->AutoSize = true;
			   this->lblState->Location = System::Drawing::Point(343, 379);
			   this->lblState->Name = L"lblState";
			   this->lblState->Size = System::Drawing::Size(0, 13);
			   this->lblState->TabIndex = 23;
			   // 
			   // Table
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(768, 404);
			   this->Controls->Add(this->lblState);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->textBoxRow);
			   this->Controls->Add(this->textBoxCol);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->ColumnasFiltro);
			   this->Controls->Add(this->filtrarColumna);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->comboBox2);
			   this->Controls->Add(this->comboBox1);
			   this->Controls->Add(this->DataSets);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->Exportar);
			   this->Controls->Add(this->Importar);
			   this->Controls->Add(this->dataGridView1);
			   this->Name = L"Table";
			   this->Text = L"Table";
			   this->Load += gcnew System::EventHandler(this, &Table::Table_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void Table_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
	private: System::Void comboBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		filter2 = comboBox2->SelectedItem->ToString();
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		filter1 = comboBox1->SelectedItem->ToString();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		UpdateTree();
	}
	private: System::Void dataGridView1_ColumnSortModeChanged(System::Object^ sender, System::Windows::Forms::DataGridViewColumnEventArgs^ e) {

	}
	private: System::Void dataGridView1_ColumnDisplayIndexChanged(System::Object^ sender, System::Windows::Forms::DataGridViewColumnEventArgs^ e) {
		cout << e->Column->Index;
	}
	private: System::Void dataGridView1_Sorted(System::Object^ sender, System::EventArgs^ e) {
		Clear();
		int i = dataGridView1->SortedColumn->Index;
		rows[*currRow]->changeRow(i);
		UpdateTree();
	}
	private: System::Void Exportar_Click(System::Object^ sender, System::EventArgs^ e) {
		string str;
		vector<string> vec;
		for each (String ^ ss in Disponibles)
		{
			MarshalString(ss, str);
			vec.push_back(str);
		}

		displayTree->Write("Output/Data.txt", vec);
		lblState->Text = "Se exportó correctamente";
	}
	private: System::Void DataSets_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		*currRow = DataSets->SelectedIndex;
	}
	private: System::Void Importar_Click(System::Object^ sender, System::EventArgs^ e) {
		ClearTable();
		Init();
		lblState->Text = "Se importó correctamente";
	}
	private: System::Void filtrarColumna_Click(System::Object^ sender, System::EventArgs^ e) {
		FilterColumns();
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		int col = Int32::Parse(textBoxCol->Text);
		int row = Int32::Parse(textBoxRow->Text);
		if (col > 0 && row > 0)
		{
			*currRow = 3;
			vector<string> tags;
			vector<string> dataStrings;
			vector<Dato*> data;
			for (int i = 0; i < col; i++)
			{
				String^ str = "Columna " + (i + 1).ToString();
				MSG^ form = gcnew MSG(str);
				this->Hide();
				form->ShowDialog();
				this->Show();
				String^ ColString = form->textEntered;
				string strColString;
				MarshalString(ColString, strColString);
				tags.push_back(strColString);
			}
			Dato* nuevo;
			for (int i = 0; i < row; i++)
			{
				dataStrings.clear();
				for (int j = 0; j < col; j++)
				{
					String^ str = gcnew String(tags[j].c_str());
					MSG^ form = gcnew MSG(str);
					this->Hide();
					form->ShowDialog();
					this->Show();
					String^ ColString = form->textEntered;
					string strColString;
					MarshalString(ColString, strColString);
					dataStrings.push_back(strColString);
				}
				nuevo = new Dato(dataStrings, tags);
				data.push_back(nuevo);
			}
			rowCreated = new Fila();
			rowCreated->Init(data, tags);
			rows[3] = rowCreated;
			ClearTable();
			Init();
		}

	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}