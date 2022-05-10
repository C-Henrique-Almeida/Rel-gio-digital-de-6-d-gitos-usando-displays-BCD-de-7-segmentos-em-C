#include <p18f4520.h>
#pragma config OSC=INTIO67
#pragma config WDT=OFF


unsigned int contador_algorismo_segundos = 0;
unsigned int contador_dezena_segundos = 0;
unsigned int contador_algorismo_minutos = 0;
unsigned int contador_dezena_minutos = 0;
unsigned int contador_algorismo_horas = 0;
unsigned int contador_dezenas_horas = 0;

int hora_dezena_alarme;
int hora_algorismo_alarme;
int minutos_dezena_alarme;
int minutos_algorismo_alarme;
int alarme_ativado = 0;

int latb_atual;
int latc_atual;

void delay(){
unsigned long int i = 0;
	for(i;  i<13333; i++){
	}
}

void delayy(){
unsigned long int i = 0;
	for(i;  i<133330; i++){
	}
}
void atualiza_relogio(){ //FUNÇÃO PARA ATUALIZAR O RELOGIO (usada para atualiza após o alarme ser usado)	//function used for actualize the display of clock

		LATA = (contador_dezena_segundos<<4 | contador_algorismo_segundos);
		LATB = (contador_dezena_minutos<<4 | contador_algorismo_minutos);
		LATC = (contador_dezenas_horas<<4 | contador_algorismo_horas);
		delay();
}
void alarme(int contador_dezenas_horas, int contador_algorismo_horas, int contador_dezena_minutos, int contador_algorismo_minutos ){

hora_dezena_alarme = contador_dezenas_horas; 
hora_algorismo_alarme = contador_algorismo_horas;
minutos_dezena_alarme = contador_dezena_minutos; 
minutos_algorismo_alarme = contador_algorismo_minutos;

if(LATB == (minutos_dezena_alarme<<4 | 	minutos_algorismo_alarme) && LATC == (hora_dezena_alarme<<4 | hora_algorismo_alarme) ){
PORTDbits.RD3  = 1;
delayy();
PORTDbits.RD3  = 0;
alarme_ativado = 0; //DIZ QUE O ALARME TOCOU //speak that the alarm sounded 
 hora_dezena_alarme=0;
 hora_algorismo_alarme=0;
 minutos_dezena_alarme=0;
 minutos_algorismo_alarme=0;
}


}

void acrescenta_hora(){
if(PORTDbits.RD0 == 1){ 
delay();

	if(PORTDbits.RD0 == 1){ delay(); 
		if(PORTDbits.RD0 == 1){delay();
			if(PORTDbits.RD1  == 1){
					while(PORTDbits.RD1  == 1){  
						if (contador_algorismo_horas == 9){
						contador_dezenas_horas++; 	contador_algorismo_horas = -1;
						}else{contador_algorismo_horas++;LATC = (contador_dezenas_horas<<4 | contador_algorismo_horas); delay();		
								}
					}
			}else if(PORTDbits.RD2  == 1){	
					
					while(PORTDbits.RD2  == 1){  
						if (contador_algorismo_minutos == 9){
						contador_dezena_minutos++; 	contador_algorismo_minutos = -1;
						}else{contador_algorismo_minutos++;LATB = (contador_dezena_minutos<<4 | 	contador_algorismo_minutos); delay();		
								}
					}
			}
		}else if(PORTDbits.RD4 == 1){ delay();delay();
				if(PORTDbits.RD1  == 1){

							//SALVA OS PARAMETROS DE HORAS E MINUTOS - >>>>>>>>>>>> PODE APAGAR <<<<<<<<<<<
									latb_atual = LATB;
									latc_atual = LATC; 


						while(PORTDbits.RD1  == 1){ 
							if (hora_algorismo_alarme == 9){
							hora_dezena_alarme++; 	hora_algorismo_alarme = -1;
							}else{hora_algorismo_alarme++;
										
									LATC = (hora_dezena_alarme<<4 | hora_algorismo_alarme); delay();		
									}
						}
				}else if(PORTDbits.RD2  == 1){
							//SALVA OS PARAMETROS DE HORAS E MINUTOS - >>>>>>>>>>>> PODE APAGAR <<<<<<<<<<<
									latb_atual = LATB;
									latc_atual = LATC;	
						

										hora_dezena_alarme = contador_dezenas_horas; 
										hora_algorismo_alarme = contador_algorismo_horas;
										minutos_dezena_alarme = contador_dezena_minutos; 
										minutos_algorismo_alarme = contador_algorismo_minutos;
										

						while(PORTDbits.RD2  == 1){  
							if (minutos_algorismo_alarme == 9){
							minutos_dezena_alarme++; 	minutos_algorismo_alarme = -1;
							}else{minutos_algorismo_alarme++;
										
									LATB = (minutos_dezena_alarme<<4 | 	minutos_algorismo_alarme); delay();		
									}
						}
				} //alarme(hora_dezena_alarme, hora_algorismo_alarme, minutos_dezena_alarme, minutos_algorismo_alarme);//CHAMA ALARME 
				  alarme_ativado++; // INFORMA QUE ALARME FOI ATIVADO
								//RETORNA OS PARAMETROS DE HORAS E MINUTOS - >>>>>>>>>>>> PODE APAGAR <<<<<<<<<<<
									//LATB = latb_atual; 
									//LATC = latc_atual;
										atualiza_relogio();			
			}
	}
}
}


void contador(){
	contador_algorismo_segundos++;
	if (contador_algorismo_segundos >= 10){
		contador_dezena_segundos++;
		contador_algorismo_segundos = 0;
		if (contador_dezena_segundos >= 6){
			contador_algorismo_minutos++;
			contador_dezena_segundos = 0;
			if (contador_algorismo_minutos >= 10){
				contador_dezena_minutos++;
				contador_algorismo_minutos = 0;
				if (contador_dezena_minutos >= 6){
					contador_algorismo_horas++;
					contador_dezena_minutos = 0;
					if (contador_dezenas_horas == 2 && contador_algorismo_horas == 4){
							contador_algorismo_horas = 0;
							contador_dezenas_horas = 0;
					}
					if (contador_algorismo_horas >= 10){
						contador_dezenas_horas++;
						contador_algorismo_horas = 0;
					}
				}
			}
		}
	}
}


void relogio(){

		LATA = (contador_dezena_segundos<<4 | contador_algorismo_segundos);
		LATB = (contador_dezena_minutos<<4 | contador_algorismo_minutos);
		LATC = (contador_dezenas_horas<<4 | contador_algorismo_horas);
		contador();
		delay();
}


void main(){
	TRISA = 0; //DEFINIR SAIDA
	TRISB = 0; //DEFINIR SAIDA
	TRISC = 0; //DEFINIR SAIDA
	TRISDbits.RD0 = 1; //DEFINIR ENTRADA
	TRISDbits.RD1 = 1; //DEFINIR ENTRADA
	TRISDbits.RD2 = 1; //DEFINIR ENTRADA
	TRISDbits.RD3 = 0; //DEFINIR SAIDA
	TRISDbits.RD4 = 1; //DEFINIR ENTRADA
	
	while(1){
		relogio();
		acrescenta_hora();
		if(alarme_ativado == 1){
			alarme(hora_dezena_alarme, hora_algorismo_alarme, minutos_dezena_alarme, minutos_algorismo_alarme);
		}
	}

}