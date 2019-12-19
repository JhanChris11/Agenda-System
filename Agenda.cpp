#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>/*la biblioteca estandar*/
#include<conio.h>
using namespace std;
const char DIR_ARCHIVO [] ="Contactos.txt";

/*
Ingresar contacto
Buscar contacto
Ver lista de contactos
Eliminar un contacto
Actualizar un contacto

*/


struct Contacto{
	
	char nombre[30];
	char apellido[45];
	int edad;
	char correo[45];
	
};
/******************Funciones del programa*****************/

void ingresarContacto(Contacto c);
Contacto leerContacto();
bool existeContacto (char nombre[],char apellido[]);
Contacto buscarContacto(char nombre[],char apellido[]);
void mostrarContacto(Contacto c);
void listarContacto();
void eliminarContacto(char nombre[],char apellido[]);
void actualizarContacto(char nombre[],char apellido[]);

/*********************************************************/


/********************Funciones del programa***************/
void menuIngresar();
void menuBuscar();
void menuListar();
void menuEliminar();
void menuActualizar();

/*********************************************************/
int main(){
/*
Ingresar contacto
Buscar contacto
Ver lista de contactos
Eliminar un contacto
Actualizar un contacto

*/
int op;
do{
	
system("cls");
cout<<"\t\t\t/************************************************/"<<endl;
cout<<"\t\t\t\t\tAGENDA "<<endl;
cout<<"\t\t\tIngresar contacto ..............[1]"<<endl;
cout<<"\t\t\tBuscar contacto ................[2]"<<endl;
cout<<"\t\t\tListado de contacto ............[3]"<<endl;
cout<<"\t\t\tEliminar contacto ..............[4]"<<endl;
cout<<"\t\t\tActualizar contacto ............[5]"<<endl;
cout<<"\t\t\tSalir...........................[6]"<<endl;
cout<<"\t\t\t/************************************************/"<<endl;	
cout<<"\t\t\tIngrese una opcion --> ";
cin>>op;
cin.ignore();
switch(op){
	case 1:system("cls");/*clean screen - limpiador de pantalla*/
	menuIngresar();
	break;
	case 2:
	menuBuscar();
	break;
	case 3:system("cls");
	menuListar();
	break;
	case 4:
	system("cls");	
	menuEliminar();
	break;
	case 5:
	system("cls");
	menuActualizar();
	break;
	case 6:break;
	default: cout<<"\t\tOpcion Incorrecta "<<endl;
}
}while(op!=6);
getch();
/*
	Contacto c=leerContacto();
	ingresarContacto(c);
*/
/*
	if(existeContacto("jhan","calderon")){
		Contacto c=buscarContacto("jhan","calderon");
		mostrarContacto(c);
	}
	else{
		cout<<"No se encontro a ese contacto "<<endl;
	}
*/
/*
listarContacto();
actualizarContacto("Jhan","Calderon")	;
cout<<"-----------------------------------------------"<<endl;
listarContacto();
*/
	return 0;

}
/*el operador or de bit es \*/
void ingresarContacto(Contacto c){
	ofstream salida;
	salida.open(DIR_ARCHIVO,ios::binary | ios::app);
	salida.write((char*) &c,sizeof(Contacto));
	salida.close();
}


Contacto leerContacto(){
	Contacto c;
	cout<<"\t\t\tNOMBRE   :";
	cin.getline(c.nombre,30);
	cout<<"\t\t\tAPELLIDO :";
	cin.getline(c.apellido,30);
	cout<<"\t\t\tEDAD     :";
	cin>>c.edad;
	cin.ignore();
	cout<<"\t\t\tCORREO   :";
	cin.getline(c.correo,45);

return c;	
}
bool existeContacto (char nombre[],char apellido[]){
	Contacto c;
	ifstream entrada;
	entrada.open(DIR_ARCHIVO,ios::binary);
	if(entrada.good()){
		/*cuantos bits va a leer*/
		/*strcmp ->string comparacion- comparacion de cadenas  */
		while(entrada.read((char*) &c,sizeof(Contacto))){
			if(strcmp(nombre,c.nombre)==0 && strcmp(apellido,c.apellido)==0 ){
				
				entrada.close();
				return true;
				
			}
		}
		entrada.close();
		return false;
	} 
	else{
		entrada.close();/*para prevenir*/
		return false;
	}
	
}
Contacto buscarContacto(char nombre[],char apellido[]){
	Contacto c;
	ifstream entrada;
	entrada.open(DIR_ARCHIVO,ios::binary);
	if(entrada.good()){
		/*cuantos bits va a leer*/
		/*strcmp ->string comparacion- comparacion de cadenas  */
		while(entrada.read((char*) &c,sizeof(Contacto))){
			if(strcmp(nombre,c.nombre)==0 && strcmp(apellido,c.apellido)==0 ){
				
				entrada.close();
				return c;
				
			}
		}
	} 	
}
void mostrarContacto(Contacto c){
	
	cout<<"\t\t\t  Nombre   :"<<c.nombre<<endl;
	cout<<"\t\t\t  Apellido :"<<c.apellido<<endl;
	cout<<"\t\t\t  Edad     :"<<c.edad<<endl;
	cout<<"\t\t\t  Correo   :"<<c.correo<<endl;
	cout<<endl;
	
}
void listarContacto(){
	ifstream entrada;
	entrada.open(DIR_ARCHIVO,ios::binary);
	Contacto c;/*el cual se va a leer todos los datos */
	if(entrada.good()){
	while(entrada.read((char*)&c,sizeof(Contacto))){
		mostrarContacto(c);
	}		
	}
else{
	cout<<"NO SE PUEDE LEER EL ARCHIVO "<<endl;
}
entrada.close();
}

void eliminarContacto(char nombre[],char apellido[]){

	ifstream entrada;
	ofstream temporal;
		
	entrada.open(DIR_ARCHIVO,ios::binary);
	temporal.open("temp.dat",ios::binary);
	Contacto c;
	if(entrada.good()){
	/*si es iguales es porque quiero eliminar osea que no quiero pasar, y si no son iguales es porque ira al temporal.dat*/
	
		while(entrada.read((char*) &c,sizeof(Contacto))){
		if(strcmp(nombre,c.nombre)!=0 || strcmp(apellido,c.apellido)!=0 ){
		temporal.write((char*)&c,sizeof(Contacto));
		}	
		}
	}
	/*Una vez que haya eliminado mi archivo original , voy a renombrar mi archivo temp.dat a mi archivo por lo cual se esta trabajando*/

	entrada.close();
	temporal.close();
	/*Yo no puedo renombrar un achivo sin antes de cerrarlo el archivo */
	remove(DIR_ARCHIVO);
	rename("temp.dat",DIR_ARCHIVO);
	
}
void actualizarContacto(char nombre[],char apellido[]){
	/*
	contacto.dat
	                          |
	REGISTRO1REGISTRO2REGISTRO3
	
	temp.dat
                                |
	REGISTRO1|REGISTRON|REGISTRO3
	*/
	
	
	ifstream entrada;
	ofstream temporal;
		
	entrada.open(DIR_ARCHIVO,ios::binary);
	temporal.open("temp.dat",ios::binary);
	Contacto c;
	if(entrada.good()){
	/*si es iguales es porque quiero eliminar osea que no quiero pasar, y si no son iguales es porque ira al temporal.dat*/
	
		while(entrada.read((char*) &c,sizeof(Contacto))){
		if(strcmp(nombre,c.nombre)==0 || strcmp(apellido,c.apellido)==0 ){
			Contacto actualizado=leerContacto();
		temporal.write((char*)&actualizado,sizeof(Contacto));
		}
		else {
		temporal.write((char*)&c,sizeof(Contacto));
		}	
		}
	}
	/*Una vez que haya eliminado mi archivo original , voy a renombrar mi archivo temp.dat a mi archivo por lo cual se esta trabajando*/

	entrada.close();
	temporal.close();
	/*Yo no puedo renombrar un achivo sin antes de cerrarlo el archivo */
	remove(DIR_ARCHIVO);
	rename("temp.dat",DIR_ARCHIVO);

}
/* Son metodos chiquitos */
void menuIngresar(){
	cout<<endl;
	cout<<"\t\t\t\t     INGRESAR NUEVO CONTACTO :"<<endl;
	Contacto nuevo=leerContacto();
	ingresarContacto(nuevo);
	/*en el caso que si quiero verificar si existe ese caso ya existente*/
/*
	if(existeContacto(nuevo.nombre,nuevo.apellido)){
		cout<<"NO SE PUEDO AGREGAR ";
	}
*/
	cout<<endl;
	cout<<"\t\t\tCONTACTO AGREGADO CON EXITO  "<<endl;
	getch();
}
void menuBuscar(){
	cout<<endl;
	cout<<"\t\t\t\t            BUSCAR CONTACTO  :"<<endl;
	char nombre[30],apellido[45];

	cout<<"\t\t\tINGRESE EL DATO DE BUSQUEDA    :"<<endl;
	cout<<"\t\t\tNOMBRE   :";
	cin.getline(nombre,30);
	cout<<"\t\t\tAPELLIDO :";
	cin.getline(apellido,45);
	if(existeContacto(nombre,apellido)){
		
		Contacto buscado=buscarContacto(nombre,apellido);
		mostrarContacto(buscado);
	}
	else{
	cout<<endl;
	cout<<"\t\t\tNO SE ENCUENTRA ESE CONTACTO   :"<<endl;
	}
	getch();
}
void menuListar(){
	cout<<endl;
	cout<<"\t\t\t\t   LISTA DE CONTACTOS    :"<<endl;
	cout<<endl;
	listarContacto();
	
	getch();/*obtener caracter*/
}
void menuEliminar(){
	cout<<endl;
	cout<<"\t\t\t\tELIMINAR CONTACTO   :"<<endl;
	char nombre[30],apellido[45];
	cout<<endl;
	cout<<"\t\t\tELIMINAR EL DATO DE BUSQUEDA   :"<<endl;
	cout<<"\t\t\tNOMBRE   :";
	cin.getline(nombre,30);
	cout<<"\t\t\tAPELLIDO :";
	cin.getline(apellido,45);

	if(existeContacto(nombre,apellido)){
	Contacto eliminar=buscarContacto(nombre,apellido);
	int opcion;
	cout<<"\t\t\tSeguro que desea eliminar el contacto ?"<<endl;	
	mostrarContacto(eliminar);

do{
		cout<<"\t\t\t SI [1]...... NO [2] :";
		cin>>opcion;
	switch(opcion){
		
		case 1:
		eliminarContacto(nombre,apellido);
		
		cout<<"\t\t\tCONTACTO ELIMINADO CORRECTAMENTE "<<endl;
		break;
		case 2:
		break;
		default:
		cout<<"\t\t\tOPCION INCORRECTA "<<endl;
	}
	}while(opcion!=1 && opcion!=2);
	}
	else{
		cout<<"\t\t\tNO EXISTE EL CONTACTO ";
	}
		getch();
}
void menuActualizar(){
	cout<<endl;
	cout<<"\t\t\t\tACTUALIZAR CONTACTO    :"<<endl;
	char nombre[30],apellido[45];
	cout<<endl;
	cout<<"\t\t\tINGRESE LOS DATOS DE MODIFICACION:"<<endl;
	cout<<"\t\t\tNOMBRE   :";
	cin.getline(nombre,30);
	cout<<"\t\t\tAPELLIDO :";
	cin.getline(apellido,45);

	if(existeContacto(nombre,apellido)){
	Contacto buscado=buscarContacto(nombre,apellido);
	cout<<endl;
	cout<<"\t\t\tREGISTRO A MODIFICAR :"<<endl;	
	mostrarContacto(buscado);
	actualizarContacto(nombre,apellido);
	cout<<endl;
	cout<<"\t\t\tSE ACTUALIZO EL REGISTRO "<<endl;

}
	else{
		cout<<endl;
		cout<<"\t\t\tNO EXISTE EL CONTACTO ";
	}
	getch();
}


