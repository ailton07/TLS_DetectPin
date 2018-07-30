// TLS_Check_V2.cpp : Defines the entry point for the console application.
//

#include <windows.h> 
#include <stdio.h> 

#define _LIMIAR 3

VOID ErrorExit (LPSTR lpszMessage) 
{ 
	fprintf(stderr, "%s\n", lpszMessage); 
	ExitProcess(0); 
}

int count32tls()
{
	printf("\t== count32tls ==\n");
	int quantidade = 0;
	DWORD dwTlsIndex;
	LPVOID lpvData; 
	int value;

	for(dwTlsIndex = 0; dwTlsIndex < 32; dwTlsIndex++)
	{
		lpvData = TlsGetValue(dwTlsIndex);
		value = reinterpret_cast<int>(lpvData);

		printf("TLS[%d] = lpvData=%lx\n", dwTlsIndex, value);
		if(value != 0) {
			quantidade++;
			// printf("TLS[%d] = lpvData igual a zero\n", dwTlsIndex);
		}

	}
	return quantidade;
}

void write32tls()
{
	printf("\t== write32tls ==\n");
	int quantidade = 0;
	DWORD dwTlsIndex;
	LPVOID newValue; 
	int value;

	newValue = (LPVOID) LocalAlloc(LPTR, 256); 

	// O Pin utiliza as primeiras posi��es
	for(dwTlsIndex = 0; dwTlsIndex < 6; dwTlsIndex++)
	{
		value = reinterpret_cast<int>(TlsGetValue(dwTlsIndex));
		printf("TLS[%d] = lpvData=%lx\n", dwTlsIndex, value);

		if(value != 0) {
			if (! TlsSetValue(dwTlsIndex, newValue)) 
				ErrorExit("TlsSetValue error"); 
		}

	}

}

int main()
{
	int quantidade = 0;

	DWORD dwTlsIndex;

	// Metodo para causar o crash do Pin
	// write32tls();

	quantidade = count32tls();

	printf("Quantidade de slots do TLS ativos: %d\n", quantidade);

	if(quantidade > _LIMIAR)
		printf("PIN DETECTED\n");
	else
		printf("Pin not detected\n");

	system("pause");
	return 0;
}

