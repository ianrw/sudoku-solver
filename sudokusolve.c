#include <stdio.h>
#include <stdlib.h>
#define L 9
#define T 3

/* Brute force algorithm to solve Sudoku puzzle.
   It finds a solution, if one can be found in under 10 000 000 attempts
   but it does not show it is the only possible solution.
   2013 May 28 & 2014 Oct 12 & 2015 May 13  Ian R Williams  */

int main(int argc, char *argv[])
{
  int i,j,k,m,n,r,c,rb,cb,v; /* r = row , c = column */
  int s[81],a[81];
  int move=0; /* move = number of attempted solution */
  char str[50]; /* to input rows of data */

  /* initialize arrays: s = starting values, a = current attempts */
	for (i=0; i<81; i++) 
	{
		s[i]=0;
		a[i]=1;
	}
	
  /* enter starting numbers of puzzle */
	printf("\nBrute force attempt to solve Sudoku puzzle");
	printf(" Ian R Williams, 2015 May 13");
	printf("\nEnter the starting numbers for the Sudoku puzzle in rows\n");
  printf("Press ENTER at the end of each row.\n");
  printf("  Enter a dot (.) where the number is not known.\n\n");
 
  i=0; j=0;
  while (i<81) 
  {
    r=i/9+1;
		printf("Row %d: ",r);
    gets(str); /* enter row of starting data */
    k=0; /* k will hold number of characters typed into string str */
    for (k=0; str[k]!='\0'; k++);
    m=0; /* to count valid characters up to 9 in for loop below */
    for(j=0; j<k; j++) {
      n=str[j]-'0';
      if (n>=0 && n<=9) {s[i]=n; i++; m++;};
      if (str[j]=='.') {s[i]=0; i++; m++;};
      if (m>=9) break;
    }
    /* fill in unspecified values of row if str is too short */
    while (m<9) {s[i]=0; i++; m++;};
    i=9*(r-1); /* reset i to start of row */
    printf("Row %d is now  |",r);
    for (j=0; j<9; j++) 
    {
      if (j==3 || j==6) {printf("|");};
      if (s[i]>0) {printf("%d", s[i]);};
      if (s[i]==0) {printf(".");};
      i++;
    } 
    printf("|\n");
  }

  do 
  { 
    /* print starting position to check input is correct */
    printf("\nThe starting position of the Sudoku puzzle is:\n");
	  for (i=0; i<81; i++) 
	  {		
		  if (i % L == 0) 
		  {
			  if (i % (3*L) == 0) {printf("\n|-----------------------------------|");}
			  else { printf("\n|           |           |           |");			}
		    printf("\n| ");
		  }
		  else 
		  {
			  if (i %3 == 0) {printf("| ");} 
			  else {printf("  ");}
		  }
		  if (s[i]==0) {printf(". ");}
		  else {printf("%d ",s[i]);}
		if ((i+1)%9 == 0) {printf("|");}
		}
	  printf("\n|-----------------------------------|\n");

    /* input 0 to continue (starting position is correct) or 1 to change */
    do 
    {
      printf("\nEnter 0 (zero) if the starting position is correct\n or 1-9 to change a row: ");
      gets(str);
      n=str[0]-'0';
    } while(n<0 || n>9);
    if (n>0  && n<=9) 
    {
      r=n;
      i=9*(r-1); 
      printf("Please reenter data for row %d: ",r);
      gets(str); /* enter row of starting data */
      k=0; /* k will hold number of characters typed into string str */
      for (k=0; str[k]!='\0'; k++);
      m=0; /* to count valid characters up to 9 in for loop below */
      for(j=0; j<k; j++) 
      {
        n=str[j]-'0';
        if (n>=0 && n<=9) {s[i]=n; i++; m++;};
        if (str[j]=='.') {s[i]=0; i++; m++;};
        if (m>=9) break;
      }
      /* fill in unspecified values of row if str is too short */
      while (m<9) {s[i]=0; i++; m++;};
      i=9*(r-1); /* reset i to start of row */
      printf("Row %d is now  |",r);
      for (j=0; j<9; j++) 
      {
        if (j==3 || j==6) {printf("|");};
        if (s[i]>0) {printf("%d", s[i]);};
        if (s[i]==0) {printf(".");};
        i++;
      }
      printf("|");
    }
  } while(n!=0);

  /* copy starting puzzle values s[] into current values a[] */
	for (i=0; i<81; i++) 
	{
		if (s[i]!=0) {a[i]=s[i];}
	}

  /* solve puzzle by trying different numbers and checking validity */
  /* v=0 if guessed value in square is still possible,
    v>0 if no longer possible,
    v=-1 if on a square containing an initial value	-- therefore unchangeable */
	for (i=0; i<81; i++) 
	{
	  do 
	  {
		  move++;
		  v=0;		
		  /* check if value in this square i was set at start, so cannot be changed */
		  if (s[i]>0) v=-1;
		  if (v==0) 
		  {
			  r=i/L; c=i%L;
			  /* check for matching value in same row. 
               Note that rows r are here indexed 0 to 8, NOT 1 to 9 */
			  for (j=0; j<L; j++) 
			  {
				  k=r*L+j;
				  if ((s[k]==a[i]) || ((k<i) && (a[k]==a[i]))) {v=1;}  /* match found */
			  }
		  }
		  if (v==0) 
		  {

			  /* check for matching value in same column 
           Note that columns c are here indexed 0 to 8, NOT 1 to 9 */
			  for (j=0; j<L; j++) 
			  {
				  k=j*L+c;
			   if ((s[k]==a[i]) || ((k<i) && (a[k]==a[i]))) {v=1;} /* match found */
			  }	
		  }
		  if (v==0)
		  {
			  /* check for matching value in same 3x3 block.
          Rows rb and columns cb take values 0, 3 or 6 */
			  rb=(r/T)*T; cb=(c/T)*T;
			  for (j=0; j<T; j++) 
			  {
				  for (k=0; k<T; k++) 
				  {
					  m=(rb+j)*L+cb+k;
					  if ((s[m]==a[i]) || ((m<i) && (a[m]==a[i]))) {v=1;}  /* match found */
				  }
			  }
		  }

		  /* if match found: increment the current value a[i] if a[i]<9 , or set a[i]=1 if a[i]=9 and step back */
		  if (v==1) 
		  {
			  if (a[i]<=L) {a[i]++;}
			  while (a[i]>L)
			  {
				  a[i]=1;
				  i--;
				  if (i<0) 
				  {
					  printf("\nFatal error: attempt to move back beyond first square.");
					  return 1;
				  }
				  while (s[i]>0) 
				  {
					  i--;
					  if (i<0) 
					  {
						  printf("\nFatal error: attempt to move left of first square.");
						  return 1;
					  }
				  }
				  a[i]++;	/* increment value in previous square and then go back to check this square's value <=9 */				
			  }
			  v=0;
			  i--;
		  }

      /*  print out current position every 1000 attempts */
	    if (move%1000==0) 
	    {  /*  printf("\nmove/1000=%d\n",move%1000); */
		    rb = i/L+1; cb = i%L+1;
		    printf("\nThe current position at move %d is:\n",move);
		    for (j=0; j<81; j++) 
		    {		
			    if (j%L == 0) 
			    {
				    if (j%(3*L) == 0) {printf("\n|-----------------------------------|");}
				    else {printf("\n|           |           |           |");}
				    printf("\n| ");
			    }
			    else 
			    {
				    if (j%3 == 0) {printf("| ");} 
				    else {printf("  ");}
			    }
			    if (a[j] == 0) {printf(". ");}
			    else {printf("%d ",a[j]);}
			    if ((j+1)%9 == 0) {printf("|");}
		    }
		    printf("\n|-----------------------------------|\n");
        /* give up after 10 000 000 attempts */
        if ((move >= 100000000)) 
        {
          printf("\nNo solution found in %d attempts\n",move); 
          return -1;
        }
	    }
	  } while (v==1);
	}

  /* print out valid solution  */
	rb=i/L+1;cb=i%L+1;
	printf("\nThe final position at move %d is:\n",move);
  for (j=0; j<81; j++) 
	{		
		if (j % L == 0) 
		{
			if (j % (3*L) == 0) {printf("\n|-----------------------------------|");}
			else {printf("\n|           |           |           |");			}
			printf("\n| ");
		}
		else 
		{
			if (j %3 == 0) {printf("| ");} 
			else {printf("  ");}
		}
		if (a[j]==0) {printf(". ");}
		else {printf("%d ",a[j]);}
		if ((j+1)%9 == 0) {printf("|");}
	}
	printf("\n|-----------------------------------|\n");
	return 0;
}

