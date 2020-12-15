#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>
#include <sys/random.h>
#include <pthread.h>
#include <math.h>
/*Los archivos especiales de caracteres / dev / random y / dev / urandom 
 proporcionan una interfaz para la función aleatoria del kernel.
El archivo / dev / urandom tiene el número de dispositivo principal
1 y número de dispositivo menor 9.

El generador de números aleatorios recopila el ruido ambiental del dispositivo
controladores y otras fuentes en un grupo de entropía. El generador también
mantiene una estimación del número de bits de ruido en la reserva de entropía.       
A partir de esta reserva de entropía, se crean números aleatorios.*/

 unsigned long  aleatorios(){

	int randomSrc = open("/dev/urandom", O_RDONLY);
	//int randomSrc = rand();
	unsigned long seed[1];
	read(randomSrc , seed, 1* sizeof(long) );
	close(randomSrc);
	return *seed;
}

int main(){
	float tiempo=0;
	int numPuntos,poblaciones,iteraciones,tamPoblacion;
	printf("Numero de puntos: \n");
	scanf("%d",&numPuntos);
	float ys[numPuntos];
	float xs[numPuntos];
	float bmin;
	float Mmin;
	float limX;
	for(int uno = 0;uno<numPuntos;uno++){
		printf("x%d:",uno+1);
		scanf("%f",&xs[uno]);
		printf("y%d:",uno+1);
		scanf("%f",&ys[uno]);
		limX = limX +xs[uno];

	}
	limX = limX*limX;

	printf("Numero de poblaciones: \n");
	scanf("%d",&poblaciones);
	printf("Numero de iteraciones: \n");
	scanf("%d",&iteraciones);
	printf("Numero de aleatorios por poblacion: \n");
	scanf("%d",&tamPoblacion);
	

	
	float e=0 ;
	float m= 0;
	float b = 0;
	float a1[tamPoblacion];
	float a2[tamPoblacion];
	float zfinal=0;
	float z =0;
	float bfinal=0;
	float mfinal=0;


	

	for (int poblacion = 0; poblacion<poblaciones; poblacion++){
		for(int iteracion = 0; iteracion < iteraciones ;iteracion++){
			for(int llena=0;llena<tamPoblacion;llena++){
						a1[llena]= -100.00+((aleatorios() % 1000000) / 1000000.0f)*200.00;
						a2[llena]= (-limX)+((aleatorios() % 1000000 ) / 1000000.0f)*(limX+limX);
						tiempo+=0.001;
						if(tiempo>30000){
							printf("El tiempo expiro");
							return 1;
						}				
				}
			for(int al = 0;al<tamPoblacion;al++){
					m = a1[al];
					b = a2[al];

					for(int i =0; i<numPuntos;i++){
						e = e + fabs(( (m*xs[i]) + b - ys[i] ));
						tiempo+=0.001;
							if(tiempo>30000){
								printf("El tiempo expiro");
								return 1;
							}		
					}
					if(al ==0){
						z=e;
						bmin=b;
						Mmin=m;
					}

					
					if(e<z){
						
						z = e;
						bmin=b;
						Mmin=m;
						//e=0.00;
					}
					e=0;
				tiempo+=0.001;
				 
				if(tiempo>30000){
					printf("El tiempo expiro");
					return 1;
				}
			}
			if(iteracion==0){
				zfinal = z;
				bfinal = bmin;
				mfinal = Mmin;
			}
			if(z<zfinal){
				printf("nuevos minimos de iteracion :%d de la pobacion %d\n",iteracion,poblacion );
				printf("z : %f bmin %f Mmin %f\n",z,bmin,Mmin);
				zfinal = z;
				bfinal = bmin;
				mfinal = Mmin;

			}
			tiempo+=0.001;
			 
			if(tiempo>30000){
				printf("El tiempo expiro");
				return 1;
			}

	}
	printf("ajuste : f(x)=%f+%fx  con z %f en poblacion %d con %d habitantes  \n",bfinal,mfinal,zfinal,poblacion,tamPoblacion );
	tiempo=0;
	}
}


