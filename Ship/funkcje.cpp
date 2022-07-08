
#include "funkcje.h"

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{
   // rekurencyja
   // tabl pRoot pamieta droge - numer ruchu pole przez ktore odwiedzono (plynie statek), 0 pole nie odwiedzone
   // wstawic do tablicy pRoot kolejny numer ruchu
   static int nr = 0;
   pRoot[y][x] = ++nr;

   //if( dotarto do portu ) return 1;
   if( ( x == x_dest ) && ( y == y_dest ) ) return 1;
      // zdefiniowac nowe wspolrzede
      int nx = x;
      int ny = y;
      // sprwadzic wszystkie mozliwosci ruchu
      for( int i = UP; i <= LEFT; i++ )
      {
         if( move( pTab, nRow, nCol, nDepth, i, x, y, &nx, &ny, pRoot ) )
         {
            if( root( pTab, nRow, nCol, nDepth, nx, ny, pRoot, x_dest, y_dest ) ) return 1;
         }
      }
   // jesli wracamy to ustawiamy w pRoot ze ruch byl zly
   pRoot[y][x] = 0;
   nr--;

   return 0;
}

int move(int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot)
{
   //wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
   switch( move )
   {
   case UP: *py = y - 1; *px = x; break;
   case RIGHT: *px = x + 1; *py = y; break;
   case DOWN: *py = y + 1; *px = x; break;
   case LEFT: *px = x - 1; *py = y; break;
   }
   //sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
   if( *px < 0 || *px > nCol || *py < 0 || *py > nRow )return 0;
   //a nastepnie sprawdzic warunek czy nie jest a plytko ">nDepth "
   if( pTab[*py][*px] <= nDepth ) return 0;
   //oraz czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot
   if( pRoot[*py][*px] != 0 ) return 0;
   return 1;
}

void clearRoot( int** pRoot, int nRow, int nCol )
{
   //zerowanie tablicy 2d
   memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
// sFile -  nazwa pliku wejsciowego - parametr main()
// pTab  - tablica glebokosci morza
// nRow, nCol wymiary tej tablicy
{
   FILE* file = NULL;
   if( ( file = fopen( sFile, "r" ) ) == NULL ) return 0;

   for( int i = 0; i < nRow; i++ )
   {
      int* pM = *pTab++;
      for( int j = 0; j < nCol; j++ )
      {
         if( !fscanf( file, "%d", pM++ ) ) return 0;
      }
   }
   fclose( file );
   return 1;
}