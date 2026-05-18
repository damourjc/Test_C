using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaccalaureatGUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnJouer_Click(object sender, EventArgs e)
        {
            string name = txtPrenom.Text;

            if (name == "")
            {
                MessageBox.Show("Veuillez entrer un nom !");
                return;
            }

            FormJeu jeu = new FormJeu(name);
            jeu.Show();

            this.Hide(); // cache la fenêtre d'accueil
        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
    }
}
