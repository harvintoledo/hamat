using System;
using System.IO;

namespace TemplateCS.Template
{

    class clsAnalizador
    {
        private int ARQUITECTURA_8BITS = 8;
        private int ARQUITECTURA_16BITS = 16;
        private int ARQUITECTURA_32BITS = 32;
        private int TAM_PILA = 65535;
        private Memoria[] memoria;
        int modelo;
        int tam_modelo = 65536; // Se establece por defecto tama;o de programa small
        int[] registros = new int[8];
        int programLength = 0;
        int pc = 0;
        int sp = 0;
        int ds = 0;
        bool zf = false; // Flag de estado de cero, modificado despues de comparar dos numeros con CMP
        bool cf = false; // Flag de suma o resta, modificado despues de hacer una operacion de suma o resta
        bool bmModelo = false;
        bool bmDataSegment = false;
        bool bmCodeSegment = false;

        enum eInsrucciones
        {
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

        enum eTipoOperando
        {
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

        enum eTipoOperacion
        {
            OPERACION_SUMA,
            OPERACION_RESTA,
            OPERACION_DIVISION,
            OPERACION_MULIPLICACION
        };

        enum eCantidadOperandos
        {
            CO_UN_OPERANDO,
            CO_DOS_OPERANDO,
            CO_NINGUN_OPERANDO
        };

        enum eTipoError
        {
            TE_TODO_BIEN,
            TE_OPERANDO_DESTINO_NO_INMEDIATO,
            TE_OPERANDO_DESTINO_NO_REGISTRO,
            TE_OPERANDO_DESTINO_NO_MEMORIA,
            TE_OPERANDO_ORIGEN_NO_INMEDIATO,
            TE_OPERANDO_ORIGEN_NO_REGISTRO,
            TE_OPERANDO_ORIGEN_NO_MEMORIA
        };
        string[] pArchivoEntrada, pArchivoSalida;
        eTipoOperando emTipoOperando;
        eTipoOperacion emTipoOperacion;
        eInsrucciones emInstruccion;
        eTipoError emTipoError;
        int imValOrigen = 0, imValDestino = 0, imNumeroLinea;

        public void main() {
            char[] caracteres = new char[100];

            Console.WriteLine("Abriendo archivo con instrucciones");
            pArchivoEntrada = File.ReadAllLines("C:\\Users\\Potosme\\Desktop\\hamat\\ParaCompilador\\SalidasOcam\\prog.asm");
            //fopen("C:\\Users\\WESKER\\Documents\\QtProjects\\ControlDeVersiones\\ParaCompilador\\SalidasOcam\\prog.asm", "r");
            if (pArchivoEntrada == null) {
                Console.WriteLine("File error");
                Environment.Exit(0);
            }
            Console.Write("\nEl contenido del archivo de prueba es \n\n");
            ReservarMemoria();
            CargarMemoriaConIndiceYSinContenido();
            /*FileInputStream stream = new FileInputStream(pArchivoEntrada);
            BufferedReader reader = new BufferedReader(new InputStreamReader(stream), 1024);*/
            //string linea = null;
            foreach (string linea in pArchivoEntrada) {
                //fgets(caracteres, 100, pArchivoEntrada);
                Console.WriteLine(linea);
                EjecutarInstruccion(linea);
                imNumeroLinea++;
            }
            Console.Write("Probando compilador qt para Windows.");
            Console.Read();
        }

        void ReservarMemoria()
        {
            memoria = new Memoria[tam_modelo];
            //pila = new Stack<Integer>();
        }

        void CargarMemoriaConIndiceYSinContenido()
        {
            for (int i = 0; i < tam_modelo; i++)
            {
                memoria[i] = new Memoria();
                memoria[i].setContenido(0);
                memoria[i].setIndice(i);
            }
        }

        void EjecutarInstruccion(string instruccion)
        {
            string slInstruccion = instruccion;
            string slInstruccionAEjecutar;
            // Pasar cualquier instruccion a mayuscula
            slInstruccion = slInstruccion.ToLower();
            // Retirar blancos de instruccion (espacios,tabuladores, etc.)
            slInstruccion = slInstruccion.Trim();
            if (slInstruccion.Contains((";")))
            {
                // Ignorar instruccion
                return;
            }
            else if (slInstruccion.Contains(("mov")))
            {
                emInstruccion = eInsrucciones.MOV;
                Console.WriteLine("MOV\n");
                slInstruccionAEjecutar = slInstruccion.Replace("mov", "");
                Console.WriteLine("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
                else {
                    Console.WriteLine("Error instruccion vacia.");
                }
            }
            else if (slInstruccion.Contains(("add")))
            {
                emInstruccion = eInsrucciones.ADD;
                Console.Write("ADD\n");
                slInstruccionAEjecutar = slInstruccion.Replace("add", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("sub")))
            {
                emInstruccion = eInsrucciones.SUB;
                Console.Write("SUB\n");
                slInstruccionAEjecutar = slInstruccion.Replace("sub", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("div")))
            {
                emInstruccion = eInsrucciones.DIV;
                Console.Write("DIV\n");
                slInstruccionAEjecutar = slInstruccion.Replace("div", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("mul")))
            {
                emInstruccion = eInsrucciones.MUL;
                Console.Write("MUL\n");
                slInstruccionAEjecutar = slInstruccion.Replace("mul", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("and")))
            {
                emInstruccion = eInsrucciones.AND;
                Console.Write("AND\n");
                slInstruccionAEjecutar = slInstruccion.Replace("and", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("or")))
            {
                emInstruccion = eInsrucciones.OR;
                Console.Write("OR\n");
                slInstruccionAEjecutar = slInstruccion.Replace("or", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("xor")))
            {
                emInstruccion = eInsrucciones.XOR;
                Console.Write("XOR\n");
                slInstruccionAEjecutar = slInstruccion.Replace("xor", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("xnor")))
            {
                emInstruccion = eInsrucciones.MUL;
                Console.Write("XNOR\n");
                slInstruccionAEjecutar = slInstruccion.Replace("xnor", "");
                Console.Write("slInstruccionAEjecutar\n");
                string[] sllOperadorOperandos = slInstruccionAEjecutar.Split(',');
                string slDestino, slOrigen;
                if (sllOperadorOperandos.Length != 0)
                {
                    if (sllOperadorOperandos.Length != 2)
                    {
                        Console.Write("Error diferente de dos operandos.\n");
                        return;
                    }
                    else {
                        slDestino = sllOperadorOperandos[0];
                        slOrigen = sllOperadorOperandos[sllOperadorOperandos.Length - 1];
                        Verificar2Operandos(slDestino, slOrigen);
                    }
                }
            }
            else if (slInstruccion.Contains(("inc")))
            {
                string slDestino;
                emInstruccion = eInsrucciones.INC;
                Console.Write("INC\n");
                slDestino = slInstruccion.Replace("inc", "");
                Verificar1Operandos(slDestino);
            }
            else if (slInstruccion.Contains(("dec")))
            {
                string slDestino;
                emInstruccion = eInsrucciones.DEC;
                Console.Write("DEC\n");
                slDestino = slInstruccion.Replace("dec", "");
                Verificar1Operandos(slDestino);
            }
            //
            EvaluarInstruccion();
            for (int i = 0; i < 8; i++)
            {
                Console.Write("reg[{0}] = {1}\n", i, registros[i]);
            }
            Console.Write("memoria source: address:{0} content:{1}", imValOrigen, memoria[imValOrigen].getContenido());
            Console.Write("memoria dest: address:{0} content:{1}", imValDestino, memoria[imValDestino].getContenido());
        }

        void CompilarPrograma()
        {
        }

        void EvaluarInstruccion()
        {
            emTipoError = eTipoError.TE_TODO_BIEN;
            switch (emInstruccion)
            {
                case eInsrucciones.MOV:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] = registros[imValOrigen];
                            programLength += 2;
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] = imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] = memoria[imValOrigen].getContenido();
                            programLength += 3;
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            memoria[imValDestino].setContenido(registros[imValOrigen]);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.ADD:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] += registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] += imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] += memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido += registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.SUB:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] -= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] -= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] -= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido -= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }

                    break;
                case eInsrucciones.MUL:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] *= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] *= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] *= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido *= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.DIV:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] /= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] /= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] /= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido /= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.AND:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] &= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] &= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] &= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido &= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.OR:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] |= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] |= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] |= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido |= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);

                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.XOR:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] |= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] |= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] |= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido |= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido); ;
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.XNOR:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            registros[imValDestino] |= registros[imValOrigen];
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            registros[imValDestino] |= imValOrigen;
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            // Error
                            emTipoError = eTipoError.TE_OPERANDO_DESTINO_NO_INMEDIATO;
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            registros[imValDestino] |= memoria[imValOrigen].getContenido();
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido |= registros[imValOrigen];
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.INC:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO:
                            registros[imValDestino]++;
                            break;
                        case eTipoOperando.TO_MEMORIA:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido++;
                            memoria[imValDestino].setContenido(contenido);
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.DEC:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO:
                            registros[imValDestino]--;
                            break;
                        case eTipoOperando.TO_MEMORIA:
                            int contenido = memoria[imValDestino].getContenido();
                            contenido--;
                            memoria[imValDestino].setContenido(contenido);
                            ;
                            break;
                        default:
                            break;
                    }
                    break;
                case eInsrucciones.CMP:
                    switch (emTipoOperando)
                    {
                        case eTipoOperando.TO_REGISTRO_REGISTRO:
                            if (registros[imValDestino] == registros[imValOrigen])
                            {
                                zf = false;
                            }
                            else {
                                zf = true;
                            }
                            break;
                        case eTipoOperando.TO_REGISTRO_INMEDIATO:
                            if (registros[imValDestino] == imValOrigen)
                            {
                                zf = false;
                            }
                            else {
                                zf = true;
                            }
                            break;
                        case eTipoOperando.TO_INMEDIATO_INMEDIATO:
                            // Error el primer operando no puede ser un inmediato
                            break;
                        case eTipoOperando.TO_INMEDIATO_REGISTRO:
                            if (imValDestino == registros[imValOrigen])
                            {
                                zf = false;
                            }
                            else {
                                zf = true;
                            }
                            break;
                        case eTipoOperando.TO_REGISTRO_MEMORIA:
                            if (registros[imValDestino] == memoria[imValOrigen].getContenido())
                            {
                                zf = false;
                            }
                            else {
                                zf = true;
                            }
                            break;
                        case eTipoOperando.TO_MEMORIA_REGISTRO:
                            if (memoria[imValDestino].getContenido() == registros[imValOrigen])
                            {
                                zf = false;
                            }
                            else {
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

        void Verificar1Operandos(string spDestino)
        {
            int indd = 0;
            if (spDestino.Contains(("reg")))
            {
                Console.Write("reg\n");
                bool ok = true;
                indd = tryParseInt(spDestino.Replace("reg", ""), ok);
                Console.Write("{0}\n", indd);
                if (!ok)
                {
                    Console.Write("error en el primer operando.");
                }
                else {
                    emTipoOperando = eTipoOperando.TO_REGISTRO;
                }
            }
            else if (!spDestino.Contains(("[")))
            {
                Console.Write("mem\n");
                string[] sllDestino = spDestino.Split('[');
                string slDestino = sllDestino[1];
                bool ok = true;
                indd = tryParseInt(slDestino.Split(']')[0], ok);
                Console.Write("{0}\n", indd);
                if (!ok)
                {
                    Console.Write("error en operando.");
                }
                else {
                    emTipoOperando = eTipoOperando.TO_MEMORIA;
                }
            }
            imValDestino = indd;
        }
        private int tryParseInt(string num, bool ok)
        {
            int x = 0;
            try
            {
                x = int.Parse(num.Trim());
                ok = true;
            }
            catch (Exception ex)
            {
                ok = false;
                Console.WriteLine(ex.Message);
            }
            return x;
        }
        void Verificar2Operandos(string spDestino, string spOrigen)
        {
            int indo = 0, indd = 0;
            if (spDestino.Contains(("reg")) && spOrigen.Contains(("reg")))
            {
                Console.Write("reg reg\n");
                bool ok = true;
                indd = tryParseInt(spDestino.Replace("reg", ""), ok);
                Console.Write("{0}\n", indd);
                if (!ok)
                {
                    Console.Write("error en el primer operando.");
                }
                else {
                    indo = tryParseInt(spOrigen.Replace("reg", ""), ok);
                    if (!ok)
                    {
                        Console.Write("error en el segundo operando.");
                    }
                    else {
                        emTipoOperando = eTipoOperando.TO_REGISTRO_REGISTRO;
                    }
                }
            }
            else if (spDestino.Contains(("reg")) && !spOrigen.Contains(("reg")))
            {
                Console.Write("reg !reg\n");
                bool ok = true;
                indd = tryParseInt(spDestino.Replace("reg", ""), ok);
                if (!ok)
                {
                    Console.Write("error en el primer operando.");
                }
                else {
                    indo = tryParseInt(spOrigen, ok);
                    if (!ok)
                    {
                        Console.Write("error en el segundo operando.");
                    }
                    else {
                        emTipoOperando = eTipoOperando.TO_REGISTRO_INMEDIATO;
                    }
                }
            }
            else if (!spDestino.Contains(("reg")) && !spOrigen.Contains(("reg")))
            {
                Console.Write("!reg !reg\n");
                bool ok = true;
                if (spDestino.Contains(("[")))
                {
                    Console.Write("mem\n");
                    string[] sllDestino = spDestino.Split('[');
                    string slDestino = sllDestino[1];
                    indd = tryParseInt(slDestino.Split(']')[0], ok);
                    Console.Write("{0}\n", indd);
                    if (!ok)
                    {
                        Console.Write("error en operando.");
                    }
                    else {
                        emTipoOperando = eTipoOperando.TO_MEMORIA;
                    }
                }
                else {
                    indd = tryParseInt(spDestino, ok);
                    if (!ok)
                    {
                        Console.Write("error en operando.");
                    }
                    else {
                        emTipoOperando = eTipoOperando.TO_INMEDIATO;
                    }
                }
                if (!ok)
                {
                    Console.Write("error en el primer operando.");
                }
                else {
                    indo = tryParseInt(spOrigen, ok);
                    if (!ok)
                    {
                        Console.Write("error en el segundo operando.");
                    }
                    else {
                        emTipoOperando = eTipoOperando.TO_INMEDIATO_INMEDIATO;
                    }
                }
            }
            else if (!spDestino.Contains(("reg")) && spOrigen.Contains(("reg")))
            {
                Console.Write("reg !reg\n");
                bool ok = false;
                indd = tryParseInt(spDestino.Replace("reg", ""), ok);
                if (!ok)
                {
                    Console.Write("error en el primer operando.");
                }
                else {
                    indo = tryParseInt(spOrigen, ok);
                    if (!ok)
                    {
                        Console.Write("error en el segundo operando.");
                    }
                    else {
                        emTipoOperando = eTipoOperando.TO_REGISTRO_INMEDIATO;
                    }
                }
            }
            imValOrigen = indo;
            imValDestino = indd;
        }
    }

}

