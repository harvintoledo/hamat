﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateCS.Template
{
    class Memoria
    {
        private int indice;
        private int contenido;
        public int getIndice()
        {
            return indice;
        }

        public void setIndice(int indice)
        {
            this.indice = indice;
        }

        public int getContenido()
        {
            return contenido;
        }

        public void setContenido(int contenido)
        {
            this.contenido = contenido;

        }
    }
}