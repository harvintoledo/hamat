/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.occammaventemplate;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.FocusEvent;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;
import javax.swing.text.Caret;
import javax.swing.text.DefaultCaret;

/**
 *
 * @author Potosme
 */
public class Consola {

    private JTextArea _texto;
    private JFrame _marco;

    public Consola() {
        this._marco = new JFrame("");
        this._marco.setSize(640, 480);
        this._texto = new JTextArea();

        Caret caret = new DefaultCaret() {
            public void focusGained(FocusEvent e) {
                setVisible(true);
                setSelectionVisible(true);
            }
        };
        caret.setBlinkRate(UIManager.getInt("TextField.caretBlinkRate"));
        this._texto.setCaret(caret);
        this._texto.setCaretColor(Color.WHITE);

        this._texto.setSize(this._marco.getSize());

        this._marco.setLocationRelativeTo(null);
        this._texto.setFont(new Font("Console", Font.BOLD, 14));
        this._texto.setBackground(Color.BLACK);
        this._texto.setForeground(Color.WHITE);
        this._texto.setEditable(false);
        this._marco.setLayout(new GridLayout(1, 1));
        this._marco.add(_texto);
        this._marco.setVisible(true);
        this._marco.repaint();
    }

    public void printText(String texto) {
        this._texto.setText(this._texto.getText() + texto);
        focusText();
    }

    private void focusText() {
        this._texto.setCaretPosition(this._texto.getText().length() );
        this._texto.requestFocus();

    }

    public String scanText() {
        String retorno = JOptionPane.showInputDialog("");
        focusText();
        return retorno;
    }

    public void show() {
        this._marco.setVisible(true);
    }

    public void hide() {
        this._marco.setVisible(false);
    }
}
