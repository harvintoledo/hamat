package occam.arq3direcciones;

import java.util.Stack;

public class plantilla {

    /**
     * OF DF IF TF SF ZF AF PF CF
     */
    //Overflow flag
    private int OF;
    
    //Direction Flag
    private int DF;
    
    //Interrup Enable Flag
    private int IF;
    
    //Trap Flag
    private int TF;
    
    //Sign Flag
    private int SF;
    
    //Zero Flag
    private int ZF;
    
    //Adjust Flag
    private int AF;
    
    //Parity Flag
    private int PF;
    
    //Carry Flag
    private int CF;
    
    //Progrma Counter
    private int PC;
    
    //Registros
    private final int[] registro = new int[4];
    
    private Memoria[] olMemoria;
    
    private final Stack<Integer> olPila;

    public plantilla(int tam_pila, int tam_memoria) {
        olPila = new Stack<>();
        olPila.setSize(tam_pila);
        olMemoria = new Memoria[tam_memoria];
        for(int i = 0;i<tam_memoria;i++)
        {
            olMemoria[i].setIndice(i);
            olMemoria[i].setContenido(0);
        }
    }

}
