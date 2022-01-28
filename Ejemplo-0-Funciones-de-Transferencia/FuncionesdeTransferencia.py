

import matplotlib.pyplot as pp
import numpy as np

class FuncionesdeTransferencia:
    
    def __init__(self):
        print('Funciones de Transferencia RNA')
        self.tangencial = lambda beta,n: (1.0-np.exp(-beta*n))/(1.0+np.exp(-beta*n))
    
    def funcion_logistica(self,beta, n):
        r = 1.0/(np.exp(-beta*n))
        return r
    
    def dibujar_funcion(self, beta = 0.1, _min = -10, _max = 10):
        x = np.arange(_min,_max,0.1)
        #y = self.funcion_logistica(beta, x)
        y = self.tangencial(beta,x)
        
        pp.plot(x,y,color='blue',lw=1.3)
        pp.grid(True)
        pp.show()
    

if __name__=="__main__":
    funciones = FuncionesdeTransferencia()
    funciones.dibujar_funcion(beta = 0.7, _min = -2)
    
