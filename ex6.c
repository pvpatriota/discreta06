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
int menor(int A, int B);

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
                      line(img, /*xin*/eixoX[n],/*yin*/eixoY[n]+60,/*xfin*/eixoX[n],/*yfin*/eixoY[n]+100, makecol(255,128,0));
                      triangle(img,eixoX[n]+10,eixoY[n]+50,eixoX[n]-10,eixoY[n]+50,eixoX[n],eixoY[n]+30,makecol(14,5,170));   
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
            int points[8]={points[0]=eixoX[entrada[n][0]],points[1]=eixoY[entrada[n][0]],\
                points[2]=eixoX[entrada[n][0]]-60,points[3]=eixoY[entrada[n][0]]+120,points[4]= eixoX[entrada[n][0]]+60,\
                points[5]= eixoY[entrada[n][0]]+120,points[6]= eixoX[entrada[n][0]]+30,points[7]= eixoY[entrada[n][0]]};

                spline(img,points,makecol(0,254,0));
                alfa = alfabeto(parametro[1],entrada[n][1]);
                textprintf_ex(img, font,eixoX[entrada[n][0]],eixoY[entrada[n][0]]+80, makecol(0,255,255),-1,"%c",alfa);
                eixoX[entrada[n][2]] += 30;
                triangle(img,eixoX[entrada[n][2]]-5,eixoY[entrada[n][2]],\
                eixoX[entrada[n][2]]+5,eixoY[entrada[n][2]],\
                eixoX[entrada[n][2]],eixoY[entrada[n][2]]+10,makecol(14,5,170));

        }
        else 
        {          
            artificio[0] =((float)(eixoX[entrada[n][0]]- eixoX[entrada[n][2]])/2);
            artificio[1] =((float)(eixoY[entrada[n][0]]- eixoY[entrada[n][2]])/2);
            if(artificio[0]<0)
                artificio[0]*= (-1);
            if(artificio[1]<0)
                artificio[1]*= (-1);
            triangle(img,eixoX[entrada[n][2]]+20,eixoY[entrada[n][2]],\
            eixoX[entrada[n][2]]+30,eixoY[entrada[n][2]],\
            eixoX[entrada[n][2]]+25,eixoY[entrada[n][2]]+10,makecol(14,5,170));
            alfa = alfabeto(parametro[1],entrada[n][1]);
            if( eixoX[entrada[n][0]]==eixoX[entrada[n][2]] || eixoY[entrada[n][0]] == eixoY[entrada[n][2]])
            {
                if( eixoX[entrada[n][0]]==eixoX[entrada[n][2]] && eixoY[entrada[n][0]] < eixoY[entrada[n][2]])
                {
                    artificio[1]+=eixoY[entrada[n][0]];
                    artificio[0]=eixoX[entrada[n][0]];
                }
                if( eixoX[entrada[n][0]]==eixoX[entrada[n][2]] && eixoY[entrada[n][0]] > eixoY[entrada[n][2]])
                {
                    artificio[1]+=eixoY[entrada[n][2]];
                    artificio[0]=eixoX[entrada[n][0]];
                }
                if( eixoX[entrada[n][0]]> eixoX[entrada[n][2]] && eixoY[entrada[n][0]] == eixoY[entrada[n][2]])
                {
                    artificio[0]+=eixoX[entrada[n][2]];
                    artificio[1]=eixoY[entrada[n][0]];
                }
                if( eixoX[entrada[n][0]]< eixoX[entrada[n][2]] && eixoY[entrada[n][0]] == eixoY[entrada[n][2]])
                {
                    artificio[0]+=eixoX[entrada[n][0]];
                    artificio[1]=eixoY[entrada[n][0]];
                }
            }

        }
    }
    blit(img,screen,0,0,0,0,640,480); 

    while(!key[KEY_ESC]) 
    {}; 

    return 0;
}
END_OF_MAIN()

int EIXOX(int N1)
{
    if ( N1 == 0 )
        return (TAMANHO);
    if ( N1 == 1 )
        return (int)(XMAX-TAMANHO)/2;
    if ( N1 == 2 )
        return (XMAX-(2*TAMANHO));
    if ( N1 == 3 )
        return (int)(XMAX-TAMANHO)/2;               
    if (N1 == 4)
        return (int) ((XMAX-TAMANHO)/4);
    if (N1 == 5)
        return (int) ((XMAX-TAMANHO)/4);
    if (N1 == 6)
        return (int) ((3*(XMAX-TAMANHO))/4);
    if(N1 == 7)
        return (int) ((3*(XMAX-TAMANHO))/4);
    if(N1==8)
        return (int) ((XMAX-TAMANHO)/8);
    if(N1==9)
        return (int) ((XMAX-TAMANHO)/8);
    if(N1==10)
        return (int) (7*(XMAX-TAMANHO)/8);
    if(N1==11)
        return (int) (7*(XMAX-TAMANHO)/8);
}
int EIXOY(int N2)
{
    if ( N2 == 0 )
        return (int)((YMAX-TAMANHO)/2);
    if ( N2 == 1 )
        return (YMAX-(2*TAMANHO));
    if ( N2 == 2 )
        return (int)((YMAX-TAMANHO)/2);
    if ( N2 == 3 )
        return (TAMANHO);               
    if (N2 == 4)
        return (int)((XMAX-TAMANHO)/4);
    if (N2 == 5)
        return (int)(3*(XMAX-TAMANHO)/4);
    if (N2 == 6)
        return (int)(3*(XMAX-TAMANHO)/4);
    if (N2 == 7)
        return (int)((XMAX-TAMANHO)/4);
    if (N2 == 8)
        return (int)((XMAX-TAMANHO)/8);
    if (N2 == 9)
        return (int)(7*(XMAX-TAMANHO)/8);
    if (N2 == 10)
        return (int)(7*(XMAX-TAMANHO)/8);
    if (N2 == 11)
        return (int)((XMAX-TAMANHO)/8);
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

int menor(int A,int B)
{
        if(A<B)
               return A;
        if(B<A)
               return B;
}
