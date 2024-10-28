#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void extenso(char reais[],char centavos[], float num);
int main(void)
{
    char reais[50] = {"\0"};
    char centavos[50] = {"\0"};
    float entrada;

    printf("\n\n\n=========================== INICIO DO PROCESSO ============================\n\n\n");

    printf("ESCREVA UM NUMERO: ");
    scanf("%f", &entrada);

    while (entrada <= 9999.99 && entrada!=0)
        {
            extenso( reais, centavos, entrada);
            printf("\n%.2f: %s %s ", entrada, reais, centavos);
            printf("\n\n\nESCREVA UM NUMERO: ");
                scanf("%f", &entrada);
            memset(centavos, 0, 50);
            memset(reais, 0, 20);
        }
        printf("\n\n\n============================ PROCESSO FINALIZADO ============================\n\n\n");
    return 0;
}

void extenso(char reais[], char centavos[],float num)
{
    //MATRIZ DE CHAR PARA NOMEAR NUMEROS
    char unidades[][8]  = { "", " um", " dois", " tres", " quatro", " cinco", " seis", " sete", " oito", " nove" };
    char dez_vinte[][11] = { "", " onze", " doze", " treze", " quatorze", " quinze", " dezesseis", " dezessete", " dezoito", " dezenove" };
    char dezenas[][11]  = { "", " dez", " vinte", " trinta", " quarenta", " cinquenta", " sessenta", " setenta", " oitenta", " noventa" };
    char centenas[][14] = { "", " cento", " duzentos", " trezentos", " quatrocentos", " quinhentos", " seiscentos", " setecentos", " oitocentos", " novecentos" };

    int mil = (int) (num/1000); //milhares
    int cent = ((int)num % 1000)/100; // centenas
    int dez = ((int) num % 100 )/10; //dezenas
    int uni = (int)num % 10; //unidades
    int aux = ((num - (int)num)*100 + 0.5);// auxiliar para centavos
    int dec = aux / 10; //decimos
    int centesimo = aux % 10 ;// centesimos



    // REAIS
    if (mil > 0)
    {
        strcat(reais, unidades[mil]);
        strcat(reais, " mil");
        if(cent == 1 && dez ==0) strcat(reais," e");
        if(cent==0){
            if(dez > 0 || uni > 0 || dec > 0 || centesimo > 0) strcat(reais," e");
        if(cent ==0 && dez == 0 && uni == 0 )strcat(reais," reais");
        }
        }

    if (mil == 0 && cent == 1 && dez == 0 && uni == 0 ){ 
        strcat(reais, " cem");// cem
        strcat(reais," reais");
        if(dec>0 || centesimo>0) strcat(reais," e"); 
    }
    else if(cent >= 1){
        strcat(reais, centenas[cent]);
        if (dez > 0) strcat(reais," e");
        else if(dez == 0 && uni > 0) strcat(reais," e");
        else if(dez == 0 && uni == 0 ) strcat(reais," reais");
   
    }

    if(dez > 1){
        strcat(reais, dezenas[dez]);
        if (uni > 0) strcat(reais," e");
        else if(uni == 0) strcat(reais," reais");
        if( uni == 0 )
        if(dec > 0 || centesimo > 0) strcat(reais," e");
    }
     if (dez == 1 && uni == 0) {
        strcat(reais, dezenas[dez]);
        strcat(reais," reais");
        if(dec>0 || centesimo>0) strcat(reais," e");
    }
    if (dez == 1 && uni > 0) {
        strcat(reais, dez_vinte[uni]);
        strcat(reais," reais");
        if(dec>0 || centesimo>0) strcat(reais," e");
    }
    else if (uni >= 1){
        strcat(reais, unidades[uni]);
        if(uni == 1 && dez == 0 && cent == 0 && mil == 0)strcat(reais," real");
        else if (uni >= 1) strcat(reais," reais");
        if(dec>0 || centesimo>0) strcat(reais," e");
        }
      
    //CENTAVOS
    if (dec > 1){
        strcat(centavos, dezenas[dec]);
        if(centesimo > 0) strcat(centavos," e");
        else strcat(centavos," centavos");
    }
    if (dec == 1 && centesimo == 0){
        strcat(centavos, dezenas[dec]);
        strcat(centavos," centavos");
   
    }
    else if (dec == 1 && centesimo > 0) {
        strcat(centavos, dez_vinte[centesimo]);
        strcat(centavos," centavos");
    }
    else if (centesimo > 0){
        strcat(centavos, unidades[centesimo]);
        strcat(centavos," centavos");
    }
    if(dec==0 && centesimo==1)strcpy(centavos," um centavo");

}