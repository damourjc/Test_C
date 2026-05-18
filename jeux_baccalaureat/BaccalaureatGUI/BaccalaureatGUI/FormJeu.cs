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
    public partial class FormJeu : Form
    {
        Random random = new Random();

        private string name;

        private char lettreActuelle;

        public FormJeu(string prenomJoueur)
        {
            InitializeComponent();
            name = prenomJoueur;

            lblBienvenue.Text = "Candidat : " + name;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            lettreActuelle = (char)('A' + random.Next(0, 26));
            lblLettre.Text = "Lettre : " + lettreActuelle;
        }

        private void FormJeu_Load(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void BtnSend_Click_1(object sender, EventArgs e)
        {
            string prenom = txtPrenom.Text;
            string ville = txtVille.Text;
            string pays = txtPays.Text;
            string animal = txtAnimal.Text;
            string objet = txtObjet.Text;

            if (prenom == "" || ville == "" || pays == "" || animal == "" || objet == "")
            {
                MessageBox.Show("Veuillez remplir tous les champs !");
                return;
            }

            int score = 0;

            score += VerifierReponse("Prénom", prenom);
            score += VerifierReponse("Ville", ville);
            score += VerifierReponse("Pays", pays);
            score += VerifierReponse("Animal", animal);
            score += VerifierReponse("Objet", objet);

            // TEXTE FINAL
            string resultat =
                "Lettre : " + lettreActuelle + "\n\n" +
                "Réponses :\n" +
                "Prénom : " + prenom + "\n" +
                "Ville : " + ville + "\n" +
                "Pays : " + pays + "\n" +
                "Animal : " + animal + "\n" +
                "Objet : " + objet + "\n\n" +
                "Score : " + score + " / 10";

            // Ouvrir nouvelle fenêtre
            FormResultat formResultat = new FormResultat(resultat);
            formResultat.Show();
        }

        private int VerifierReponse(string categorie, string mot)
        {
            if (string.IsNullOrWhiteSpace(mot))
            {
                MessageBox.Show(categorie + " invalide (vide)");
                return 0;
            }

            if (char.ToUpper(mot[0]) == lettreActuelle)
            {
                if (mot.Length > 5)
                {
                    MessageBox.Show(categorie + " valide (+2 points)");
                    return 2;
                }
                else
                {
                    MessageBox.Show(categorie + " valide (+1 point)");
                    return 1;
                }
            }
            else
            {
                MessageBox.Show(categorie + " invalide");
                return 0;
            }
        }
    }
}
