/*
BACKTRACKING  algorytm z nawrotami
-------------
ogólny algorytm wyszukiwania wszystkich (lub kilku) rozwiązań niektórych problemów
obliczeniowych, który stopniowo generuje kandydatów na rozwiązanie jednak,
gdy stwierdzi, że znaleziony kandydat x nie może być poprawnym rozwiązaniem,
nawraca (ang. "backtracks") do punktu, gdzie może podjąć inną decyzje
związaną z jego budową
*/

#include "funkcje.h"

// zdefini stale N i M - wymiary  (na 10)
#define M 10
#define N 10

// glebokosc zanurzenia okretu
#define DEPTH_MIN 5

int** CreateMatrix( int nRow, int nCol );
void DeleteMatrix( int*** pTab, int nRow );
void PrintMatrix( int** pTab, int nRow, int nCol );

int main( int argc, char* argv[] )
{
	//argc
	if( argc != 2 )
	{
		printf( "Nieprawidlowe dane wejsciowe programu %s\n", argv[0] );
		return 1;
	}

	FILE* fin = NULL;

	/*if( ( fin = fopen( argv[1], "r" ) ) == NULL )
	{
		perror( "Problem z otwarciem pliku\n" );
		return 2;
	}*/
	// odczytac rozmiary macierzy
	//if( ( !fscanf( fin, "%i", &nRow ) ) || ( !fscanf( fin, "%i", &nCol ) ) )
	//{
	//	printf( "Zle dane w pliku" );
	//	return 3;
	//}
	//fclose( fin );
	//fin = NULL;

	// Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary)
	// wykorzystac funkcje z matrixa ale dodac parametr z drugim wymiarem
	// wyzerowac obie tablice 
	int** pMatIn = NULL;
	int** pMatRoot = NULL;
	pMatIn = CreateMatrix( M, N );
	pMatRoot = CreateMatrix( M, N );
	if( !pMatRoot || !pMatIn )
	{
		printf( "Blad alokacji." );
		return 4;
	}

	// wczytac dane glebokosci
	if( !setTab( argv[1], pMatIn, M, N ) )
	{
		perror( "Nie wczytano glebokosci" );
		return 5;
	}

	//wydruk kontrolny
	PrintMatrix( pMatIn, M, N );

	// Jezeli nie znaleziono drogi od (0,0) do (N,M)- funkcja rekur root
	if( !root( pMatIn, M, N, DEPTH_MIN, 0, 0, pMatRoot, M - 1, N - 1 ) )
		printf( "Set sails! No land 'ere.\n\n" );
	// jesli ok to wypisac trase
	else
	{
		printf( "Quit singing shanties lads! I see land to plunder!\n" );
		PrintMatrix( pMatRoot, M, N );
	}

	// zwolnic pamiec!!
	DeleteMatrix( &pMatIn, M );
	DeleteMatrix( &pMatRoot, M );

	return 0;
}

int** CreateMatrix( int nRow, int nCol )
{
	int** pTab = (int**)malloc( nRow * sizeof( int* ) );
	if( !pTab ) return NULL;
	memset( pTab, 0, nRow * sizeof( int* ) );

	*pTab = (int*)malloc( nRow * nCol * sizeof( int ) );
	if( !*pTab ) return NULL;
	memset( *pTab, 0, nRow * nCol * sizeof( int ) );

	int** v = pTab + 1;
	int* p = *pTab + nCol;
	for( int i = 1; i < nRow; i++, p += nCol )
	{
		*v++ = p;
	}

	return pTab;
}

void PrintMatrix( int** pTab, int nRow, int nCol )
{
	printf( " " );
	for( int i = 0; i < nRow; i++ )
	{
		int* p = *pTab++;
		for( int j = 0; j < nCol; j++ ) printf( "%2i ", *p++ );
		printf( "\n " );
	}
	printf( "\n" );
	return;
}

void DeleteMatrix( int*** pTab, int nRow )
{
	// usuwa macierz
	free( **pTab );
	free( *pTab );
	*pTab = NULL;
}