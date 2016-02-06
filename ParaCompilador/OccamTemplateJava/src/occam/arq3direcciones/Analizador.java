/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package occam.arq3direcciones;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
/**
 *
 * @author Potosme
 */
public class Analizador {

    private final int ARQUITECTURA_8BITS = 8;
    private final int ARQUITECTURA_16BITS = 16;
    private final int ARQUITECTURA_32BITS = 32;
    private final int TAM_PILA = 65535;
    private Memoria[] memoria;
    int modelo;
    int tam_modelo = 65536; // Se establece por defecto tama;o de programa small
    int[] registros = new int[8];
    int programLength = 0;
    int pc = 0;
    int sp = 0;
    int ds = 0;
    boolean zf = false; // Flag de estado de cero, modificado despues de comparar dos numeros con CMP
    boolean cf = false; // Flag de suma o resta, modificado despues de hacer una operacion de suma o resta
    boolean bmModelo = false;
    boolean bmDataSegment = false;
    boolean bmCodeSegment = false;

    enum eInsrucciones {
        MOV,
        ADD,
        SUB,
        MUL,
        DIV,
        AND,
        OR,
        XOR,
        XNOR,
        INC,
        DEC,
        INT,
        PUSH,
        POP,
        JMP,
        JMPZ,
        JMPNZ,
        CMP
    };

    enum eTipoOperando {
        TO_REGISTRO_REGISTRO,
        TO_REGISTRO_INMEDIATO,
        TO_INMEDIATO_REGISTRO,
        TO_REGISTRO_MEMORIA,
        TO_MEMORIA_REGISTRO,
        TO_INMEDIATO_INMEDIATO,
        TO_REGISTRO,
        TO_MEMORIA,
        TO_INMEDIATO
    };

    enum eTipoOperacion {
        OPERACION_SUMA,
        OPERACION_RESTA,
        OPERACION_DIVISION,
        OPERACION_MULIPLICACION
    };

    enum eCantidadOperandos {
        CO_UN_OPERANDO,
        CO_DOS_OPERANDO,
        CO_NINGUN_OPERANDO
    };

    enum eTipoError {
        TE_TODO_BIEN,
        TE_OPERANDO_DESTINO_NO_INMEDIATO,
        TE_OPERANDO_DESTINO_NO_REGISTRO,
        TE_OPERANDO_DESTINO_NO_MEMORIA,
        TE_OPERANDO_ORIGEN_NO_INMEDIATO,
        TE_OPERANDO_ORIGEN_NO_REGISTRO,
        TE_OPERANDO_ORIGEN_NO_MEMORIA
    };
    File pArchivoEntrada, pArchivoSalida;
    eTipoOperando emTipoOperando;
    eTipoOperacion emTipoOperacion;
    eInsrucciones emInstruccion;
    eTipoError emTipoError;
    int imValOrigen = 0, imValDestino = 0, imNumeroLinea;

    public void main(String argv[]) throws FileNotFoundException, IOException {
        char[] caracteres = new char[100];
        System.out.println("Abriendo archivo con instrucciones");
        pArchivoEntrada = new File("C:\\Users\\Potosme\\Desktop\\hamat\\ParaCompilador\\SalidasOcam\\prog.asm");//fopen("C:\\Users\\WESKER\\Documents\\QtProjects\\ControlDeVersiones\\ParaCompilador\\SalidasOcam\\prog.asm", "r");
        if (pArchivoEntrada == null) {
            System.out.println("File error");
            System.exit(1);
        }
        System.out.print("\nEl contenido del archivo de prueba es \n\n");
        ReservarMemoria();
        CargarMemoriaConIndiceYSinContenido();
        FileInputStream stream = new FileInputStream(pArchivoEntrada);
        BufferedReader reader = new BufferedReader(new InputStreamReader(stream), 1024);
        String linea = null;
        while ((linea = reader.readLine()) != null) {
            //fgets(caracteres, 100, pArchivoEntrada);
            System.out.println(linea);
            EjecutarInstruccion(linea);
            imNumeroLinea++;
        }

        stream.close();
        System.out.print("Probando compilador qt para Windows.");
        System.in.read();
    }

    void ReservarMemoria() {
        memoria = new Memoria[tam_modelo];
        //pila = new Stack<Integer>();
    }

    void CargarMemoriaConIndiceYSinContenido() {
        for (int i = 0; i < tam_modelo; i++) {
            memoria[i] = new Memoria();
            memoria[i].setContenido(0);
            memoria[i].setIndice( i);
        }
    }

    void EjecutarInstruccion(String instruccion) {
    String slInstruccion = instruccion;
        String slInstruccionAEjecutar;
        // Pasar cualquier instruccion a mayuscula
        slInstruccion = slInstruccion.toLowerCase();
        // Retirar blancos de instruccion (espacios,tabuladores, etc.)
        slInstruccion = slInstruccion.trim();
        if (slInstruccion.contains((";"))) {
            // Ignorar instruccion
            return;
        } else if (slInstruccion.contains(("mov"))) {
            emInstruccion = eInsrucciones.MOV;
            System.out.println("MOV\n");
            slInstruccionAEjecutar = slInstruccion.replace("mov", "");
            System.out.println("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            } else {
                System.out.println("Error instruccion vacia.");
            }
        } else if (slInstruccion.contains(("add"))) {
            emInstruccion = eInsrucciones.ADD;
            System.out.print("ADD\n");
            slInstruccionAEjecutar = slInstruccion.replace("add", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("sub"))) {
            emInstruccion = eInsrucciones.SUB;
            System.out.print("SUB\n");
            slInstruccionAEjecutar = slInstruccion.replace("sub", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("div"))) {
            emInstruccion = eInsrucciones.DIV;
            System.out.print("DIV\n");
            slInstruccionAEjecutar = slInstruccion.replace("div", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("mul"))) {
            emInstruccion = eInsrucciones.MUL;
            System.out.print("MUL\n");
            slInstruccionAEjecutar = slInstruccion.replace("mul", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("and"))) {
            emInstruccion = eInsrucciones.AND;
            System.out.print("AND\n");
            slInstruccionAEjecutar = slInstruccion.replace("and", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("or"))) {
            emInstruccion = eInsrucciones.OR;
            System.out.print("OR\n");
            slInstruccionAEjecutar = slInstruccion.replace("or", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("xor"))) {
            emInstruccion = eInsrucciones.XOR;
            System.out.print("XOR\n");
            slInstruccionAEjecutar = slInstruccion.replace("xor", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("xnor"))) {
            emInstruccion = eInsrucciones.MUL;
            System.out.print("XNOR\n");
            slInstruccionAEjecutar = slInstruccion.replace("xnor", "");
            System.out.print("slInstruccionAEjecutar\n");
            String[] sllOperadorOperandos = slInstruccionAEjecutar.split(",");
            String slDestino, slOrigen;
            if (sllOperadorOperandos.length !=0) {
                if (sllOperadorOperandos.length != 2) {
                    System.out.print("Error diferente de dos operandos.\n");
                    return;
                } else {
                    slDestino = sllOperadorOperandos[0];
                    slOrigen = sllOperadorOperandos[sllOperadorOperandos.length-1];
                    Verificar2Operandos(slDestino, slOrigen);
                }
            }
        } else if (slInstruccion.contains(("inc"))) {
            String slDestino;
            emInstruccion = eInsrucciones.INC;
            System.out.print("INC\n");
            slDestino = slInstruccion.replace("inc", "");
            Verificar1Operandos(slDestino);
        } else if (slInstruccion.contains(("dec"))) {
            String slDestino;
            emInstruccion = eInsrucciones.DEC;
            System.out.print("DEC\n");
            slDestino = slInstruccion.replace("dec", "");
            Verificar1Operandos(slDestino);
        }
        //
        EvaluarInstruccion();
        for (int i = 0; i < 8; i++) {
            System.out.printf("reg[%d] = %d\n", i, registros[i]);
        }
        System.out.printf("memoria source: address:%d content:%d", imValOrigen, memoria[imValOrigen].getContenido());
        System.out.printf("memoria dest: address:%d content:%d", imValDestino, memoria[imValDestino].getContenido());
    }

    void CompilarPrograma() {
    }

    void EvaluarInstruccion() {
        emTipoError = eTipoError.TE_TODO_BIEN;
        switch (emInstruccion) {
            case MOV:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] = registros[imValOrigen];
                        programLength += 2;
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] = imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] = memoria[imValOrigen].getContenido();
                        programLength += 3;
                        break;
                    case TO_MEMORIA_REGISTRO:
                        memoria[imValDestino].setContenido(registros[imValOrigen]);
                        break;
                    default:
                        break;
                }
                break;
            case ADD:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] += registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] += imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] += memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido+= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                break;
            case SUB:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] -= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] -= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] -= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido -= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                
                break;
            case MUL:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] *= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] *= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] *= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido *= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                break;
            case DIV:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] /= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] /= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] /= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido  /= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                break;
            case AND:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] &= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] &= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] &= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido &= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                break;
            case OR:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] |= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] |= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] |= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido |= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        
                        break;
                    default:
                        break;
                }
                break;
            case XOR:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] |= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] |= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] |= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido |= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido); ;
                        break;
                    default:
                        break;
                }
                break;
            case XNOR:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        registros[imValDestino] |= registros[imValOrigen];
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        registros[imValDestino] |= imValOrigen;
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        // Error
                        emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                        break;
                    case TO_REGISTRO_MEMORIA:
                        registros[imValDestino] |= memoria[imValOrigen].getContenido();
                        break;
                    case TO_MEMORIA_REGISTRO:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido |= registros[imValOrigen];
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                break;
            case INC:
                switch (emTipoOperando) {
                    case TO_REGISTRO:
                        registros[imValDestino]++;
                        break;
                    case TO_MEMORIA:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido++;
                        memoria[imValDestino].setContenido(contenido);
                        break;
                    default:
                        break;
                }
                break;
            case DEC:
                switch (emTipoOperando) {
                    case TO_REGISTRO:
                        registros[imValDestino]--;
                        break;
                    case TO_MEMORIA:
                        int contenido = memoria[imValDestino].getContenido();
                        contenido--;
                        memoria[imValDestino].setContenido(contenido);
                        ;
                        break;
                    default:
                        break;
                }
                break;
            case CMP:
                switch (emTipoOperando) {
                    case TO_REGISTRO_REGISTRO:
                        if (registros[imValDestino] == registros[imValOrigen]) {
                            zf = false;
                        } else {
                            zf = true;
                        }
                        break;
                    case TO_REGISTRO_INMEDIATO:
                        if (registros[imValDestino] == imValOrigen) {
                            zf = false;
                        } else {
                            zf = true;
                        }
                        break;
                    case TO_INMEDIATO_INMEDIATO:
                        // Error el primer operando no puede ser un inmediato
                        break;
                    case TO_INMEDIATO_REGISTRO:
                        if (imValDestino == registros[imValOrigen]) {
                            zf = false;
                        } else {
                            zf = true;
                        }
                        break;
                    case TO_REGISTRO_MEMORIA:
                        if (registros[imValDestino] == memoria[imValOrigen].getContenido()) {
                            zf = false;
                        } else {
                            zf = true;
                        }
                        break;
                    case TO_MEMORIA_REGISTRO:
                        if (memoria[imValDestino].getContenido() == registros[imValOrigen]) {
                            zf = false;
                        } else {
                            zf = true;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    void Verificar1Operandos(String spDestino) {
        int indd=0;
        if (spDestino.contains(("reg"))) {
            System.out.print("reg\n");
            boolean ok=true;
            indd = tryParseInt(spDestino.replace("reg", ""),ok);
            System.out.printf("%d\n", indd);
            if (!ok) {
                System.out.print("error en el primer operando.");
            } else {
                emTipoOperando = emTipoOperando.TO_REGISTRO;
            }
        } else if (!spDestino.contains(("["))) {
            System.out.print("mem\n");
            String[] sllDestino = spDestino.split("[");
            String slDestino = sllDestino[1];
            boolean ok=true;
            indd = tryParseInt(slDestino.split("]")[0],ok);
            System.out.printf("%d\n", indd);
            if (!ok) {
                System.out.print("error en operando.");
            } else {
                emTipoOperando = emTipoOperando.TO_MEMORIA;
            }
        }
        imValDestino = indd;
    }
    private int tryParseInt(String num,boolean ok)
    {
        int x =0;
        try{
            x = Integer.parseInt(num.trim());
            ok = true;
        }
        catch(Exception ex)
        {
            ok = false;
        }
        return x;
    }
    void Verificar2Operandos(String spDestino, String spOrigen) {
        int indo = 0, indd = 0;
        if (spDestino.contains(("reg")) && spOrigen.contains(("reg"))) {
            System.out.print("reg reg\n");
            boolean ok=true;
            indd = tryParseInt(spDestino.replace("reg", ""), ok);
            System.out.printf("%d\n", indd);
            if (!ok) {
                System.out.print("error en el primer operando.");
            } else {
                indo = tryParseInt(spOrigen.replace("reg", ""), ok);
                if (!ok) {
                    System.out.print("error en el segundo operando.");
                } else {
                    emTipoOperando = emTipoOperando.TO_REGISTRO_REGISTRO;
                }
            }
        } else if (spDestino.contains(("reg")) && !spOrigen.contains(("reg"))) {
            System.out.print("reg !reg\n");
            boolean ok=true;
            indd = tryParseInt(spDestino.replace("reg", ""), ok);
            if (!ok) {
                System.out.print("error en el primer operando.");
            } else {
                indo = tryParseInt(spOrigen, ok);
                if (!ok) {
                    System.out.print("error en el segundo operando.");
                } else {
                    emTipoOperando = emTipoOperando.TO_REGISTRO_INMEDIATO;
                }
            }
        } else if (!spDestino.contains(("reg")) && !spOrigen.contains(("reg"))) {
            System.out.print("!reg !reg\n");
            boolean ok=true;
            if (spDestino.contains(("["))) {
                System.out.print("mem\n");
                String[] sllDestino = spDestino.split("[");
                String slDestino = sllDestino[1];
                indd = tryParseInt(slDestino.split("]")[0], ok);
                System.out.printf("%d\n", indd);
                if (!ok) {
                    System.out.print("error en operando.");
                } else {
                    emTipoOperando = emTipoOperando.TO_MEMORIA;
                }
            } else {
                indd = tryParseInt(spDestino,ok);
                if (!ok) {
                    System.out.print("error en operando.");
                } else {
                    emTipoOperando = emTipoOperando.TO_INMEDIATO;
                }
            }
            if (!ok) {
                System.out.print("error en el primer operando.");
            } else {
                indo = tryParseInt(spOrigen, ok);
                if (!ok) {
                    System.out.print("error en el segundo operando.");
                } else {
                    emTipoOperando = emTipoOperando.TO_INMEDIATO_INMEDIATO;
                }
            }
        } else if (!spDestino.contains(("reg")) && spOrigen.contains(("reg"))) {
            System.out.print("reg !reg\n");
            boolean ok=false;
            indd = tryParseInt(spDestino.replace("reg", ""), ok);
            if (!ok) {
                System.out.print("error en el primer operando.");
            } else {
                indo = tryParseInt(spOrigen, ok);
                if (!ok) {
                    System.out.print("error en el segundo operando.");
                } else {
                    emTipoOperando = emTipoOperando.TO_REGISTRO_INMEDIATO;
                }
            }
        }
        imValOrigen = indo;
        imValDestino = indd;
    }

    void ObtenerModelo() {
    }

}
