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
    public partial class FormResultat : Form
    {

        private string resultat;

        public FormResultat(string resultat)
        {
            InitializeComponent();
            this.resultat = resultat;

            lblResultat.Text = resultat;
        }

        private void FormResultat_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
