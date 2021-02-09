#include<stdio.h>
#include<conio.h>
#include<math.h> //fmod
#include<stdlib.h>
#include<time.h>

void probarGeneradores(); //esto es de la primera tarea
double generadorNumeroAleatorio(); 
double generadorNumeroCajaNormal(int []); 
double generadorNumeroCajasPoisson(int []); 


int caja1[] = {6, 1, 7, 5, 3, 2, 3, 6, 4, 6, 4, 3, 4, 2, 7, 3, 5, 5, 2, 5, 2, 2, 3, 7, 3, 3, 3, 3, 3, 4}; 
int caja2[] = {1, 4, 7, 7, 4, 3, 6, 5, 6, 4, 7, 4, 3, 5, 4, 5, 5, 6, 8, 4, 4, 5, 3, 2, 3, 3, 6, 5, 6, 5};//143 
int LlegadaCliente[] ={3, 2, 4, 4, 1, 2, 3, 2, 4, 3, 2, 3, 2, 3, 3, 4, 4, 4, 4, 2, 2, 2, 3, 1, 3, 2, 3, 1, 3, 4};//81

int Reloj=0, delta=0, Tscaja1=0, Tscaja2=0, Tocaja1=0, Tocaja2=0, TAcumuladoCaja1=0, TAcumuladoCaja2=0, TAcumuladoLlegada=0, Tllegada, TCaja1, TCaja2, Tocio; 
int TSimulacion, filac1=0, filac2=0, clientestotales1=0, clientestotales2=0; 

int main(){
	//probarGeneradores(); 
	printf("¿Cuanto tiempo desea simular?(escriba la cantidad en minutos): \t"); scanf("%i", &TSimulacion); 
	do{
		if(TAcumuladoLlegada == 0){
			Tllegada = generadorNumeroCajaNormal(LlegadaCliente);
			TAcumuladoLlegada = Tllegada; 
			if(filac2<filac1){
				filac2 +=1; 
			}else{
				filac1 +=1; 
			}
		}
		
		if(TAcumuladoLlegada< TAcumuladoCaja1 && TAcumuladoLlegada < TAcumuladoCaja2){
			delta = TAcumuladoLlegada; 
		}else{
			if(TAcumuladoCaja2 < TAcumuladoCaja1){
				if(TAcumuladoCaja2==0){
					if(TAcumuladoLlegada < TAcumuladoCaja1 || TAcumuladoCaja1==0){
						delta = TAcumuladoLlegada; 
					}else{
						delta = TAcumuladoCaja1; 
					}
				}else{
					delta = TAcumuladoCaja2; 
				}
			}else{
				if(TAcumuladoCaja1==0){
					if(TAcumuladoLlegada < TAcumuladoCaja2 || TAcumuladoCaja2==0){
						delta = TAcumuladoLlegada; 
					}else{
						delta = TAcumuladoCaja2; 
					}
				}else{
					delta = TAcumuladoCaja1; 
				}			
				
			}
		}
		
		Reloj += delta; 
		
		TAcumuladoLlegada -= delta; 
		
		if(TAcumuladoCaja1 ==0 && filac1 > 0 ){
			clientestotales1 += 1; 
			TCaja1 = generadorNumeroCajasPoisson(caja1); 
			TAcumuladoCaja1 = TCaja1; 
			filac1 -= 1; 
		}
		
		if(TAcumuladoCaja2 ==0 && filac2 > 0 ){
			clientestotales2 += 1; 
			TCaja2 = generadorNumeroCajaNormal(caja2); 
			TAcumuladoCaja2 = TCaja2; 
			filac2 -= 1; 
		}
		
		if(filac1==0){
			Tocaja1 +=delta; 
		}else{
			TAcumuladoCaja1 -= delta; 
			Tscaja1 +=delta; 
		}
		
		if(filac2==0){
			Tocaja2 +=delta; 
		}else{
			TAcumuladoCaja2 -= delta; 
			Tscaja2 +=delta; 
		}
	
	 
	}while(Reloj<TSimulacion); 
	
	printf("\n\n"); 
	printf("Tiempo de servicio caja 1: %i\n ", Tscaja1); 
	printf("Tiempo de servicio caja 2: %i\n ", Tscaja2); 
	printf("Tiempo de ocio caja 1: %i\n ", Tocaja1);
	printf("Tiempo de ocio caja 2: %i\n ", Tocaja2);  
	printf("Numero total de clientes de la caja 1: %i\n ", clientestotales1);
	printf("Numero total de clientes de la caja 2 %i\n ", clientestotales2); 
	getch(); 
	return 0; 
}

double generadorNumeroAleatorio(){
	//Cantidad de iteraciones

	int n = rand() % 7; 
	
	//Semillas
	double a= 30, m=41, x=0, xaux=21; 
	//Valor aleatorio
	double R=0; 
	
	for(int i=0; i<n; i++){
		x= xaux; 
		R = fmod((a * x), m); 
		xaux = R; 
		R = R/(m-1); 
	}
	
	
	//printf("Prueba: %.4f y n: %d", R, n); 
	return R; 
}

double generadorNumeroCajaNormal(int caja[]){
	double media = 0, desv=0, potencia=2; 
	for(int i=0; i<30; i++){
		media = media+ caja[i]; 
	}
	
	media = media/30; 
	
	for(int i=0; i<30; i++){
		desv = desv + sqrt(pow((caja[i]-media), potencia)/(30-1)); 
	}
	
	desv = sqrt(desv/30); 
	//printf("%.4f", desv); 
	
	double SumR=0, normal=0, R; 
	
	for(int i=0; i <12; i++){
		R = generadorNumeroAleatorio(); 
		SumR = SumR + R; 
	}
	
	normal= media + desv*((SumR-6)); 
	

	
	//printf("%.0f,  ", normal); 
	
	return normal; 
	
}



double generadorNumeroCajasPoisson(int caja[] ){
	double lambda=0, consta, fact=1, Sum= 0, Pois=0, VP=0, e=2.71828, R; 
	for(int i=0; i<30; i++){
		lambda = lambda+ caja[i]; 
	}
	
	int var = rand() % (26 - 6)+6; 
	// 6 a 25; 
	lambda = lambda/var; 
		
	R = generadorNumeroAleatorio(); 
	
	consta = pow(e, -lambda); 
	
	for(int x=0; Sum<= R;  x++){
		if(x==0){
			Pois = consta * (pow(lambda, x)); 
			Sum = Sum + Pois; 
		}else{
			fact = fact*x; 
			Pois= (consta*(pow(lambda, x)));
			Sum = Sum+Pois; 
		}
		VP=x; 
	}
	if(VP==0){
		VP = VP+1; 
	}
	//printf("%.0f, ",VP ); 
	return VP; 		
}
