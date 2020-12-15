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

	unsigned long seed[1];
	read(randomSrc , seed, 1* sizeof(long) );
	close(randomSrc);

	return *seed;
}

int main(){

	int numPuntos,poblaciones,iteraciones,tamPoblacion;
	printf("Numero de puntos: \n");
	scanf("%d",&numPuntos);
	float ys[numPuntos];
	float xs[numPuntos];
	float Kmin;
	float m;
	float anterior=0;
	for(int uno = 0;uno<numPuntos;uno++){
		printf("x%d:",uno+1);
		scanf("%f",&xs[uno]);
		printf("y%d:",uno+1);
		scanf("%f",&ys[uno]);
		if(ys[uno]>anterior)
			m = xs[uno];
		anterior=ys[uno];
		

	}
	

	
	printf("Numero de poblaciones: \n");
	scanf("%d",&poblaciones);
	printf("Numero de iteraciones: \n");
	scanf("%d",&iteraciones);
	printf("Numero de aleatorios por poblacion: \n");
	scanf("%d",&tamPoblacion);
	


	
	
	
	float e=0 ;
	float a1[tamPoblacion];
    float zfinal=0;
	float z =0;
	float kfinal;
	float k;
	float auxK,pot;


	

	for (int poblacion = 0; poblacion<poblaciones ;poblacion++){
		
		for(int iteracion = 0; iteracion < iteraciones ;iteracion++){
			for(int llena=0;llena<tamPoblacion;llena++){
						a1[llena]= ((aleatorios() % 1000000) / 1000000.0f)*5.00;
						
				}
			for(int al = 0;al<tamPoblacion;al++){
					k = a1[al];
					auxK=k;
				for(int i =0; i<numPuntos;i++){
					e = e + fabs( exp( (-auxK * pow(xs[i]-m,2)) ) - ys[i] );		
					}
					if(al == 0){
						z=e;	
						Kmin=k;
						}
					if(e<z){
						z = e;
						Kmin=k;
					}
					e=0;
				
			}
			if(iteracion==0){
				zfinal = z;
				kfinal = Kmin;	
			}
			if(z<zfinal){
				printf("nuevos minimos de iteracion :%d de la pobacion %d\n",iteracion,poblacion );
				printf("e : %f Kmin %f \n",z,Kmin);
				zfinal = z;
				kfinal = Kmin;	
			}
	}
	printf("ajuste : f(x)=  e^[-%f(x-%f)^2]  en poblacion %d con %d habitantes  \n",kfinal,m,poblacion,tamPoblacion );
		
	}
}