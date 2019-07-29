# [ Semáforos como herramienta para sincronizar procesos independientes. ]
Los procesos normalmente no tienen datos compartidos (excepto los semáforos utilizados para la sincronización). Abra el archivo [S,s]ynchro[.java, .c] Para comprender este programa, también necesitará entender el archivo [S,s]emaphore[.java, .c]. En este programa, un proceso padre crea 2 procesos hijos A y B, y espera su finalización. Cada proceso secundario realiza 5 iteraciones. En cada iteración, sólo muestra su nombre y el número de iteración actual, y duerme durante un tiempo aleatorio (¡para que la salida sea fácil de visualizar!). 
Compilar y ejecutar el programa. 

- ¿Podría predecir la salida del programa antes de la ejecución? ¿Por qué?  Ajuste la duración de reposo de un proceso (o ambos procesos) para obtener un resultado diferente.
- ¿Podrías predecir esta salida? ¿Por qué? 


# [ Semáforos como herramienta de exclusión mutua entre procesos que comparten memoria. ]
Familiaricese con los archivos [A,a]ccount [.java, .c] para entender esta parte del laboratorio, también necesitará entender los semáforos y memoria compartida en los archivos [S,s]emaphore[.java, .c] y  [S,s]hared_memory[.java, .c]. En este conjunto de actividades de la parte no.2, un proceso padre crea un segmento de memoria compartida, adjunta el segmento en su espacio de direcciones y escribe 100000 en una variable en la memoria compartida antes de crear 2 procesos hijos A y B. Después de eso, el padre espera la terminación de los hijos y destruye el segmento de memoria compartida. Cada proceso secundario realiza 5 iteraciones. Cada proceso de iteración A agrega 200 a la variable compartida, y el proceso B agrega 300 a la variable compartida. Para ayudar a que aparezcan las condiciones de la carrera, ambos procesos duermen durante un período de tiempo aleatorio entre el momento en que leen la variable compartida y el momento en que escriben la variable compartida después de la modificación.
Compilar y ejecutar el programa. 
- ¿Podrías predecir la salida del programa antes de la ejecución? ¿Por qué? Ajuste la duración de reposo de un proceso (o ambos procesos) para obtener un resultado diferente. 
- ¿Podrías predecir esta salida? ¿Por qué?  

- Queremos agregar un nuevo proceso (asígnele el nombre C), que se comporta de la misma manera que los procesos A y B, excepto que incrementa la variable compartida solo en 90.
¿Cuántos semáforos necesita para asegurarse de que no se pierda ninguna modificación de la variable compartida? Modifique el programa para hacer que el padre cree el proceso C y use semáforos para asegurarse de que no se pierda ninguna modificación de la variable compartida.
