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

    int n,eixoX[parametro[0]],eixoY[parametro[0]],tamanho = 50;

    FILE *arq= fopen("automato1.txt","r");
    fscanf(arq,"%d", &parametro[0]); //quantidade
    fscanf(arq,"%d", &parametro[1]); //alfabeto
    fscanf(arq,"%d", &parametro[2]); //começo
    fscanf(arq,"%d %d %d", &parametro[3], &parametro[4], &parametro[5]);//fim
    for(n=0;n<EMAX;n++)
    {
        fscanf(arq,"%d %d %d", &entrada[n][0],&entrada[n][1],&entrada[n][2]);
    }

    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,XMAX,YMAX,0,0);
    PALETTE pal;
    BITMAP *img = create_bitmap(XMAX,YMAX);

    for(n=0;n<parametro[0];n++)
    {                            
        eixoX[n] = EIXOX(n);
        eixoY[n] = EIXOY(n);
        if(n==parametro[2])
        {
            if((n!= parametro[3] && n!= parametro[4]) && n!= parametro[5])
            {
                circlefill(img, eixoX[n]/*eixox*/, eixoY[n]/*eixoy*/, TAMANHO/*tamanho*/, makecol(255,255,0));
                textprintf_ex(img, font, eixoX[n], eixoY[n]+10, makecol(0,0,255),-1,"q%d",n);
            }
            else
                if(((n==parametro[3] || n==parametro[4]) || n==parametro[5]))
                {
                    circlefill(img, eixoX[n]/*eixox*/, eixoY[n]/*eixoy*/, TAMANHO/*tamanho*/, makecol(255,255,0));
                    circle(img, eixoX[n]/*eixox*/, eixoY[n]/*eixoy*/, TAMANHO-7/*tamanho*/, makecol(0,0,0));
                    textprintf_ex(img, font, eixoX[n], eixoY[n]+10, makecol(0,0,255),-1,"q%d",n);                                        
                }
        }
        else
            if(((n==parametro[3] || n==parametro[4]) || n==parametro[5]))
            {
                circlefill(img, eixoX[n]/*eixox*/, eixoY[n]/*eixoy*/, TAMANHO/*tamanho*/, makecol(255,255,255));
                circle(img, eixoX[n]/*eixox*/, eixoY[n]/*eixoy*/, TAMANHO-7/*tamanho*/, makecol(0,0,0));
                textprintf_ex(img, font, eixoX[n], eixoY[n]+10, makecol(0,0,255),-1,"q%d",n);
            }
            else
            {
                circlefill(img,eixoX[n]/*eixox*/, eixoY[n]/*eixoy*/, TAMANHO/*tamanho*/, makecol(255,255,255));
                textprintf_ex(img, font, eixoX[n], eixoY[n]+10, makecol(0,0,255),-1,"q%d",n);
            }
    }
    for(n=0;n<EMAX;n++)
    {
        if(entrada[n][0] == entrada[n][2])//destino == saida
        {
            int points[8]={eixoX[entrada[n][0]],eixoY[entrada[n][0]],eixoX[entrada[n][0]]-60,eixoY[entrada[n][0]]+120,points[4]= eixoX[entrada[n][0]]+60,\
                points[5]= eixoY[entrada[n][0]]+120,points[6]= eixoX[entrada[n][0]]+30,points[7]= eixoY[entrada[n][0]]};

            spline(img,points,makecol(0,254,0));
            eixoX[entrada[n][2]] += 30;
            triangle(img,eixoX[entrada[n][2]]-5,eixoY[entrada[n][2]],\
                    eixoX[entrada[n][2]]+5,eixoY[entrada[n][2]],\
                    eixoX[entrada[n][2]],eixoY[entrada[n][2]]+10,makecol(14,5,170));
        }
        else 
        {          
            line(img, /*xin*/eixoX[entrada[n][0]],/*yin*/eixoY[entrada[n][0]],/*xfin*/eixoX[entrada[n][2]]+25,/*yfin*/eixoY[entrada[n][2]], makecol(0,254,0));
            triangle(img,eixoX[entrada[n][2]]+20,eixoY[entrada[n][2]],\
                    eixoX[entrada[n][2]]+30,eixoY[entrada[n][2]],\ 
                    eixoX[entrada[n][2]]+25,eixoY[entrada[n][2]]+10,makecol(14,5,170));
            alfa = alfabeto(parametro[1],entrada[n][1]);
            artificio[0] =(float)(eixoX[entrada[n][0]]- eixoX[entrada[n][2]])/2;
            artificio[1] =(float)(eixoY[entrada[n][0]]- eixoY[entrada[n][2]])/2;
            textprintf_ex(img, font, eixoX[(int)artificio[0]], eixoY[(int)artificio[1]], makecol(0,255,255),-1,"%c",alfa);
            textprintf_ex(img, font, eixoX[(int)(XMAX/2)], eixoY[(int)(YMAX/2)+n*10], makecol(0,255,255),-1,"atificio0 = %d artificio1 = %d",(int)artificio[0],(int)artificio[1]);

        }
    }   


return 0;

int alfabeto(int a, int b)
{
    int x=0;

    if( b>a || b==69)// se o alfabeto desejado não estiver no meu intervalo ou for igual a 'E'
        return 0;
    else
        while(x!=-1)
        {
            if( b == x )
                return (b+97);
            else
                x++;
        }
}
}
