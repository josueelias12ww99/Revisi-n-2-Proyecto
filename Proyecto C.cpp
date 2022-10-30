#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *archivo_resultado = "resultado.dat";
struct Palabra
{

	char palabras[50];
	char traduccion[50];
	char funcionalidad[1000];
};
void Crear();
void Leer();
void Actualizar();
void Borrar();
main()
{
	system("Color 80");
	int option, option2;
	char traduccion[100];
	do
	{
		if (option = 1)
		{
			do
			{
				cout << "************************************" << endl;
				cout << "---------Menu----------" <<endl;				
				cout << "1. Ingresar palabra." << endl;     
				cout << "2. Actualizar palabra." << endl;
				cout << "3. Eliminar palabra." << endl;
				cout << "4. Ver diccionario." << endl;
				cout << "************************************" << endl;
				cout << "Ingrese el numero de opcion o 0 para salir: ";
				cin >> option2;
				switch (option2)
				{
				case 1:
					Leer();
					Crear();
					system("pause");
					break;
				case 2:
					Leer();
					Actualizar();
					system("pause");
					break;
				case 3:
					Leer();
					Borrar();
					system("pause");
					break;
				case 4:
					Leer();
					system("pause");
					break;

				default:
					break;
				}
			} while (option2 != 0);
			return 0;
		}
		else
		{
			do
			{
				cout << "Bienvenido al sistema de traducciones!";
				cout << "Ingrese una palabra o exit para salir :" << endl;
				cin.getline(traduccion, 100);
				Palabra palabra;
				char *aux = "";
				FILE *archivo = fopen(nombre_archivo, "a+b");
				fread(&palabra, sizeof(Palabra), 1, archivo);
				int id = 0;
				do
				{
					if (palabra.traduccion == traduccion)
					{
						sscanf(palabra.traduccion, "%s", aux);
						FILE *archivo = fopen(archivo_resultado, "a+b");
						if (!archivo)
						{
							archivo = fopen(archivo_resultado, "w+b");
						}
						fflush(stdin);
						fwrite(&aux, sizeof(aux), 1, archivo);
						fclose(archivo);
					}
					fread(&palabra, sizeof(Palabra), 1, archivo);
					id += 1;
				} while (feof(archivo) == 0);
				fclose(archivo);
				if (aux == "")
				{
				}
				else
				{
					cout << "La palabra ingresada no existe en el diccionario, ingrese otra palabra o agreguela al diccionario.";
				}
			} while (traduccion != "exit");
		}
	} while (option != 0);
}
void Leer()
{
	system("cls");
	FILE *archivo = fopen(nombre_archivo, "rb");
	if (!archivo)
	{
		archivo = fopen(nombre_archivo, "w+b");
	}
	Palabra palabra;
	int id = 1;
	fread(&palabra, sizeof(Palabra), 1, archivo);
	do
	{
		cout << "************************************************" << endl;
		cout<< "ID:" << id <<endl;
		cout<< "Palabra:"<<palabra.palabras <<endl;
		cout<< "Traduccion:" <<palabra.traduccion <<endl;
		cout<< "Funcionalidad:" <<palabra.funcionalidad << endl;
		fread(&palabra, sizeof(Palabra), 1, archivo);
		id += 1;
	} while (feof(archivo) == 0);
	fclose(archivo);
}
void Crear()
{
	FILE *archivo = fopen(nombre_archivo, "a+b");
	char res;
	Palabra palabra;
	do
	{
		fflush(stdin);
		cout << "Ingrese Palabra:";
		cin.getline(palabra.palabras, 100);

		cout << "Ingrese Traduccion:";
		cin.getline(palabra.traduccion, 100);

		cout << "Ingrese Funcionalidad:";
		cin.getline(palabra.funcionalidad, 900);

		fwrite(&palabra, sizeof(Palabra), 1, archivo);
		cout << "Desea Ingresar otra palabra(s/n):";
		cin >> res;
	} while (res == 's' || res == 'S');
	fclose(archivo);
	Leer();
}
void Actualizar()
{

	FILE *archivo = fopen(nombre_archivo, "r+b");
	Palabra palabra;
	int id = 0;
	cout << "Ingrese el ID que desea Modificar:";
	cin >> id;
	fseek(archivo, id * sizeof(Palabra), SEEK_SET);

	cout << "Ingrese Palabra:";
	cin >> palabra.palabras;
	cin.ignore();

	cout << "Ingrese Traduccion:";
	cin >> palabra.traduccion;
	cin.ignore();

	cout << "Ingrese Funcionalidad:";
	cin.getline(palabra.funcionalidad, 900);

	fwrite(&palabra, sizeof(Palabra), 1, archivo);
	fclose(archivo);
	Leer();
}
void Borrar(){
	const char *nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b");
	FILE* archivo = fopen(nombre_archivo,"rb");
	Palabra palabra;
	int id=0,id_n=0;
	cout<<"Ingrese el ID que desea eliminar:";
	cin>>id;
	while(fread(&palabra,sizeof(Palabra),1,archivo)){
		if(id_n !=id){
			fwrite(&palabra,sizeof(Palabra),1,archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);
	
	archivo_temp = fopen(nombre_archivo_temp,"rb");
	archivo = fopen(nombre_archivo,"wb");
	while(fread(&palabra,sizeof(Palabra),1,archivo_temp)){
		fwrite(&palabra,sizeof(Palabra),1,archivo);
	}
	fclose(archivo);
	fclose(archivo_temp);
	Leer();
}

void CrearTraduccion(char semantica)
{
	FILE *archivo = fopen(archivo_resultado, "a+b");
	if (!archivo)
	{
		archivo = fopen(archivo_resultado, "w+b");
	}
	fflush(stdin);
	fwrite(&semantica, sizeof(semantica), 1, archivo);
	fclose(archivo);
}

void leerResultados()
{
	system("cls");
	FILE *archivo = fopen(archivo_resultado, "rb");

	char *p;
	fread(&p, sizeof(p), 1, archivo);
	cout << "******************************************************************************" << endl;
	cout << "RESULTADOS DE TRADUCCION";
	cout << "******************************************************************************" << endl;
	do
	{
		cout << p << endl;
		fread(&p, sizeof(p), 1, archivo);
	} while (feof(archivo) == 0);
	fclose(archivo);
}
