#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#define MAXPARAMETROS 6 // Define o número máximo dos parâmetros
#define TAMANHO 40 // Define o diâmetro dos círculos
#define XMAX 600
#define YMAX 500
#define EMAX 6 // Define o número de entradas

int EIXOX(int N1);
int EIXOY(int N2);
int alfabeto(int a, int b);

int main(void)
{
    float artificio[2]; /* Para calular ponto medio entre dois status do automato */
    int entrada[EMAX][3],cor[3],parametro[6],alfa;
    /* 0= origem, 1= letra, 2= destino */

    parametro[0] = 5; // quantidade
    parametro[1] = 2; // alfabeto (a,b)
    parametro[2] = 0; // começo
    parametro[3] = 0; //fim
    parametro[4] = 3; //fim
    parametro[5] = 4; //fim 

    /* Entradas estáticas para testes, posteriormente serão removidas */

    entrada[0][0] =0; 
    entrada[0][1] =0;
    entrada[0][2] =1;
    entrada[1][0] =1;
    entrada[1][1] =0;
    entrada[1][2] =2;
    entrada[2][0] =1;
    entrada[2][1] =1;
    entrada[2][2] =3;
    entrada[3][0] =2;
    entrada[3][1] =1;
    entrada[3][2] =4;
    entrada[4][0] =3;
    entrada[4][1] =0;
    entrada[4][2] =1;
    entrada[5][0] =4;
    entrada[5][1] =0;
    entrada[5][2] =1;

    return 0;
}
