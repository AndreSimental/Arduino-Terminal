#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<iostream.h>

void inicializa(int port)
{
	asm{
		mov ah,00h
		mov al,11100011b
		mov dx,port
		int 14h
		 }
}
void envia(char car,int port)
{
	asm{
		mov ah,01h
		mov dx,port
		mov al,car
		int 14h
		 }
}

char lee(int port)
{
	char temp;
	asm{
		mov ah,02h
		mov dx,port
		int 14h
		mov temp,al
		 }
return temp;
}

unsigned char estado(int port)
{
	unsigned char temp;
	asm{
		mov ah,03h
		mov dx,port
		int 14h
		and ah,00000001b
		mov temp,ah
		 }
return temp;
}

void main(void)
{
	int puerto;
	char car;
	int opc;
	int edo;
	clrscr();
	cout<<"Dame numero de puerto:"<<endl;
	cin>>puerto;
	inicializa(puerto);
	clrscr();
	do{
	clrscr();
	cout<<"\t **** Proyecto final Lenguajes de interfaz ****"<<endl;
	cout<<"1.- Receptor"<<endl;
	cout<<"2.- Transmisor"<<endl;
	cout<<"3.- Salir"<<endl;
	cout<<endl;
	cout<<"Numero:  ";
	cin>>opc;


	switch(opc){
		case 1:
				clrscr();
				cout<<"\t *** Programa 1 Receptor ***"<<endl;

				envia('a', puerto);
eti0:

	do{
			edo = estado(puerto);
		}
	while((edo==0)&&(!kbhit()));
	if(kbhit()){envia('s',puerto);}
	if(edo==1)
	{
		car = lee(puerto);
		if(car==27)break;
		cout<<car;
		goto eti0;

		}
		break;
		case 2:
			clrscr();
			cout<<"\t ** Programa 2 Transmisor **"<<endl;
			cout<<endl;

			envia('b',puerto);
			eti1:
				car = getche();
				if(car==115){envia('s',puerto);break;}
				if(car==27)break;
				envia(car,puerto);
				goto eti1;

		case 3: break;

	} }while(opc!=3);

/*int puerto;
char car;
char cad0[]="Tecnologico$";
clrscr();
cout<<"Deme numero de puerto: ";
cin>>puerto;

	inicializa(puerto);

	for(int i=0;i<100;i++)
	{
	if(cad0[i]=='$')break;
	envia(cad0[i],puerto);
	}
eti0:
	car = getche();
	if(car==27)return;
	envia(car,puerto);
	goto eti0;*/
}

