import os
import subprocess
import argparse
parser = argparse.ArgumentParser(description='Procesa los datos de muestras')
parser.add_argument('-m', dest='pathMuestras', nargs=1, required=True, help='path completo a archivos de muestra (ej /home/user/metodos/)')
parser.add_argument('-tp', dest='pathTP', nargs=1, required=True, help='path y nombre completo para ejecutar el tp, (ej /home/user/metodos/./metnumTP1)')
args = parser.parse_args()
pathMuestras = args.pathMuestras[0]
pathTP = args.pathTP[0]
if not os.path.exists(pathMuestras+"processedData/"): os.makedirs(pathMuestras+"processedData")
f = open(pathMuestras+"processedData/datosProcesados.txt", 'w')
for fileName in os.listdir(pathMuestras):
	if fileName.endswith(".txt"):
		f.write('Archivo: '+fileName+'\n')
		f.write('Metodo de Biseccion con a0=1, b0=50\n')
		output = subprocess.check_output(pathTP+" --muestra "+pathMuestras+fileName+" --metodo biseccion --a0 1 --b0 50", shell=True)
		output = output.split('\n', 3)
		for line in output:
			f.write(line+'\n')
		iteraciones = output[0].split(" = ",2)[1]
		sigma = output[1].split(" = ",2)[1]
		beta = output[2].split(" = ",2)[1]
		lambd = output[3].split(" = ",2)[1]
		#print("Sigma: "+sigma+" Beta: "+beta+" Lambda: "+lambd)
		f.write('\nMetodo de Newton con p0=5\n')
		output = subprocess.check_output(pathTP+" --muestra "+pathMuestras+fileName+" --metodo newton --p0 5", shell=True);
		output = output.split('\n', 3)
		for line in output:
			f.write(line+'\n')
		iteraciones = output[0].split(" = ",2)[1]
		sigma = output[1].split(" = ",2)[1]
		beta = output[2].split(" = ",2)[1]
		lambd = output[3].split(" = ",2)[1]
		#dibujo el de Newton
		subprocess.call("octave --eval 'dibujarHistyAjuste(leer_datos(\""+pathMuestras+fileName+"\"), "+sigma+","+beta+","+lambd+"); print -dsvg \""+pathMuestras+"processedData/"+fileName.strip(".txt")+".svg\"'", shell=True)
		f.write('\n')
f.close()
