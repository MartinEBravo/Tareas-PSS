Instrucciones para probar sus soluciones

Sea <prob> el nombre de uno de los problemas de las preguntas 1 a 5.
El nombre <prob> puede ser p1, p2, p4, rotar o p5.  Note que no existe p4.

Programe la solución del problema <prob> en <prob.c>.

Compile con opciones de debugging y ejecute con: make test-<prog>-g

Compile y ejecute para valgrind con: make test-<prog>-vg
No tiene sentido probar con valgrind la p1.

Compile con opciones para optimización y ejecute p5 con: make test-p5-O

Puede lanzar un programa para ser depurado con valgrind y ddd con:
  make test-<prob>-vg-ddd

No hay nada que reprochar a sus soluciones si al ejecutar:

p1: make test-p1-g

p2: make test-p2-g ; make test-p2-vg

p3: make test-p3-g ; make test-p3-vg

rotar: make test-rotar-g ; make test-rotar-vg

p5: make test-p5-g ; make test-p5-vg

Todas esas ejecuciones deben terminar con un mensaje de felicitación.
Además las ejecuciones con valgrind deben reportar 0 errores y ningún
memory leak.

