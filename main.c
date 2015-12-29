#include <stdio.h>
#include <stdlib.h>

int main()
{
int i=0,cont=0;
    for(i=0;i<16;i++)
    {
        printf("%d\n",i);

        cont++;
        if(cont == 4)
        {
          printf("\r\r\r\r\t");
          cont=0;
        }

    }


    return 0;
}
