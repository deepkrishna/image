#include <stdlib.h>
#include <stdio.h>
#include "Util.c"


int main(int argc, char* argv[])
    {
    FILE* ifp;
    gray* graymap;
    int ich1, ich2, rows, cols, maxval=255, pgmraw;
    int i, j;



    /* Arguments */
    if ( argc != 2 ){
      printf("\nUsage: %s file \n", argv[0]);
      exit(0);
    }

    /* Opening */
    ifp = fopen(argv[1],"r");
    if (ifp == NULL) {
      printf("error in opening file %s\n", argv[1]);
      exit(1);
    }
    /*  Magic number reading */
    ich1 = getc( ifp );
    if ( ich1 == EOF )
        pm_erreur( "EOF / read error / magic number" );
    ich2 = getc( ifp );
    if ( ich2 == EOF )
        pm_erreur( "EOF /read error / magic number" );
    if(ich2 != '3' && ich2 != '6')
      pm_erreur(" wrong file type ");
    else
      if(ich2 == '3')
	pgmraw = 0;
      else pgmraw = 1;

    /* Reading image dimensions */
    cols = pm_getint( ifp );
    rows = pm_getint( ifp );
    maxval = pm_getint( ifp );
    int dim = 3;

    /* Memory allocation  */
    graymap = (gray *) malloc(cols * rows * sizeof(gray) * dim);

    /* Reading */

    for(i=0; i < rows; i++)
      for(j=0; j < cols * 3 ; j++)
	if(pgmraw)
	    {
	      graymap[i * cols + j] = pm_getrawbyte(ifp);
	    }
	  else
	    {
	      graymap[i * cols + j] = pm_getint(ifp);
	    }
	  
    /* Writing */
    dim = 3;
    if(pgmraw)
      printf("P2\n");
    else
      printf("P5\n");

    printf("%d %d \n", cols, rows);
    printf("%d \n",maxval);
    int skip = 3;
    for(i=0; i < rows; i++)
      for(j=0; j < cols * 3; j++)
	if (j % skip != 0)
	  {
	    
	  }
    
	else
	  {
	    if(pgmraw)
	      printf("%d ", graymap[i * cols + j]);
	    else
	      printf("%c",graymap[i * cols + j]);
	    /*putc(graymap[i * cols + j],stdout);*/
	  }

      /* Closing */
      fclose(ifp);
      return 0;
}
