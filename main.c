#include <stdio.h> /* Anadimos las bibliotecas de uso habitual en programacion cientifica. */
#include <stdlib.h>
#include <math.h>

#define n_iter 9    /* Indicamos el numero de iteraciones del bucle principal, que nos determinara el numero
                       de triangulos de nuestra figura. */

#define lado 1     /* Definimos el tamano del triangulo equilatero a generar. */

struct Triangulo{  /* Creamos una estructura con las coordenadas x e y de cada vertice del triangulo, un total de
                      seis variables. */
    float xa, ya;
    float xb, yb;
    float xc, yc;
};

int main(int argc, char**argv){
    
    int tam = pow(3, n_iter); /* Creamos una variable de tipo entero que contiene el numero total de triangulos de nuestra
                                 figura, que es tres elevado al numero de iteraciones, es decir, el numero de triangulos aumenta
                                 exponencialmente con base 3. Esto es facil de ver ya que cada uno de los triangulos de la figura 
                                 se divide en tres triangulos nuevos. */
    
    /* El tamano de la estructura sera por tanto igual a la variable "tam". */
    struct Triangulo trian[tam];
    /* Creamos una nueva estructura que se definira mas adelante. */
    struct Triangulo trian_antiguo[tam];
    
    int n, z,it, q, r, s, n_triangulos; /* Creamos diversas variables de tipo entero que se explican mas adelante. */
    
    /* Establecemos las condiciones inciales, generando un triangulo equilatero con un vertice en el punto (0,0) y los otros dos en el 
       punto correspondiente dependiendo de la longitud de lado escogida. */
    trian[0].xa = 0;     
    trian[0].ya = 0;
    trian[0].xb = lado;
    trian[0].yb = 0;
    trian[0].xc = lado * 0.5;
    trian[0].yc = lado * (sqrt(3)/2);
    
    for(it=1; it<=n_iter; it++){     /* Generamos un bucle con la variable "it" como contador, que va desde uno hasta el numero de
                                        iteraciones indicado. */
        n_triangulos = pow(3, it);
        
        for(z=0; z<pow(3,it-1); z++){   /* En cada iteracion de este bucle, se guarda el nuevo struct creado en el bucle anidado
                                           sobre el llamado "antiguo", para que en la siguiente iteracion se trabaje sobre este
                                           y no siempre sobre el primero. */
            trian_antiguo[z] = trian[z];
        }
        
        /* Aplicamos la transformacion a todos los trians existentes. */
        for(n=0; n<(n_triangulos)/3; n++){
            
            /* Estas tres variables de tipo entero indican cada uno de los subtriangulos generados en cada iteracion. */
            q = 3 * n;
            r = 3 * n + 1;
            s = 3 * n + 2;
            
            /* Tercer subtriangulo. Se mantiene constante el vertice superior, el resto se modifican, */
            trian[s].xa = (trian_antiguo[n].xa + trian_antiguo[n].xc) * 0.5;
            trian[s].ya = (trian_antiguo[n].ya + trian_antiguo[n].yc) * 0.5;
            trian[s].xb = (trian_antiguo[n].xb + trian_antiguo[n].xc) * 0.5;
            trian[s].yb = (trian_antiguo[n].yb + trian_antiguo[n].yc) * 0.5;
            trian[s].xc = trian_antiguo[n].xc;
            trian[s].yc = trian_antiguo[n].yc;
            
            /* Segundo subtriangulo. Se mantiene constante el vertice inferior derecho, el resto se modifican. */
            trian[r].xa = (trian_antiguo[n].xa + trian_antiguo[n].xb) * 0.5;
            trian[r].ya = (trian_antiguo[n].ya + trian_antiguo[n].yb) * 0.5;
            trian[r].xb = trian_antiguo[n].xb;
            trian[r].yb = trian_antiguo[n].yb;
            trian[r].xc = (trian_antiguo[n].xb + trian_antiguo[n].xc) * 0.5;
            trian[r].yc = (trian_antiguo[n].yb + trian_antiguo[n].yc) * 0.5;
            
            /* Primer subtriangulo. Se mantiene constante el vertice inferior izquierdo, el resto se modifican. */
            trian[q].xa = trian_antiguo[n].xa;
            trian[q].ya = trian_antiguo[n].ya;
            trian[q].xb = (trian_antiguo[n].xa + trian_antiguo[n].xb) * 0.5;
            trian[q].yb = (trian_antiguo[n].ya + trian_antiguo[n].yb) * 0.5;
            trian[q].xc = (trian_antiguo[n].xa + trian_antiguo[n].xc) * 0.5;
            trian[q].yc = (trian_antiguo[n].ya + trian_antiguo[n].yc) * 0.5;
        }
    }
    
    /* Mostramos en pantalla todos los puntos generados mediante este bucle. */
    for(n=0; n<tam; n++)
        printf("%f\t%f\t%f\t%f\t%f\t%f\n", trian[n].xa, trian[n].ya, trian[n].xb, trian[n].yb, trian[n].xc, trian[n].yc);
    
    FILE *fp;  /* Creamos un puntero a un dato tipo fichero y generamos nuestro archivo .dat. */
    
    int i;
    
    /* Abrimos e indicamos el path del fichero seguido del nombre que le otorgamos. */
    fp = fopen("/Users/jaime/Documents/Proyectos/Sierpinski/triangulos.dat", "w");
    
    /* Con este bucle y la funcion "fprintf" escribimos sobre el archivo .dat creado. */
    for(i=0; i<tam; i++){
        
        fprintf(fp, "%g\t%g\n%g\t%g\n%g\t%g\n%g\t%g\n\n", trian[i].xa, trian[i].ya, trian[i].xb, trian[i].yb, trian[i].xc,
                trian[i].yc, trian[i].xa,trian[i].ya);
        
            /* Indicamos que en el archivo .dat que se genere, todos los puntos se encuentren en dos columnas para
               poder graficarlos con la funcion plot de gnuplot (que solo permite tomar dos columnas de datos). Ademas
               de todos los puntos creados (xa, ya, xb, yb, xc, yc), repetimos al final las coordenadas del vertice
               A(xa, ya), para que se cierre completamente nuestro triangulo. */
    }
    
    fclose(fp);
    
    return 0;
}
