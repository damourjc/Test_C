namespace BaccalaureatGUI
{
    partial class FormJeu
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtPrenom = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtObjet = new System.Windows.Forms.TextBox();
            this.txtAnimal = new System.Windows.Forms.TextBox();
            this.txtPays = new System.Windows.Forms.TextBox();
            this.txtVille = new System.Windows.Forms.TextBox();
            this.lblBienvenue = new System.Windows.Forms.Label();
            this.btnStart = new System.Windows.Forms.Button();
            this.lblLettre = new System.Windows.Forms.Label();
            this.BtnSend = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtPrenom
            // 
            this.txtPrenom.Location = new System.Drawing.Point(180, 356);
            this.txtPrenom.Name = "txtPrenom";
            this.txtPrenom.Size = new System.Drawing.Size(100, 20);
            this.txtPrenom.TabIndex = 24;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(832, 322);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(38, 13);
            this.label5.TabIndex = 23;
            this.label5.Text = "Objet :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(689, 322);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 13);
            this.label4.TabIndex = 22;
            this.label4.Text = "Animal :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(535, 322);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 21;
            this.label3.Text = "Pays :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(358, 322);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 20;
            this.label2.Text = "Ville :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(177, 322);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 13);
            this.label1.TabIndex = 19;
            this.label1.Text = "Prénom :";
            // 
            // txtObjet
            // 
            this.txtObjet.Location = new System.Drawing.Point(816, 356);
            this.txtObjet.Name = "txtObjet";
            this.txtObjet.Size = new System.Drawing.Size(100, 20);
            this.txtObjet.TabIndex = 18;
            // 
            // txtAnimal
            // 
            this.txtAnimal.Location = new System.Drawing.Point(672, 356);
            this.txtAnimal.Name = "txtAnimal";
            this.txtAnimal.Size = new System.Drawing.Size(100, 20);
            this.txtAnimal.TabIndex = 17;
            // 
            // txtPays
            // 
            this.txtPays.Location = new System.Drawing.Point(518, 356);
            this.txtPays.Name = "txtPays";
            this.txtPays.Size = new System.Drawing.Size(100, 20);
            this.txtPays.TabIndex = 16;
            // 
            // txtVille
            // 
            this.txtVille.Location = new System.Drawing.Point(339, 356);
            this.txtVille.Name = "txtVille";
            this.txtVille.Size = new System.Drawing.Size(100, 20);
            this.txtVille.TabIndex = 15;
            // 
            // lblBienvenue
            // 
            this.lblBienvenue.AutoSize = true;
            this.lblBienvenue.Location = new System.Drawing.Point(466, 55);
            this.lblBienvenue.Name = "lblBienvenue";
            this.lblBienvenue.Size = new System.Drawing.Size(55, 13);
            this.lblBienvenue.TabIndex = 27;
            this.lblBienvenue.Text = "Candidat :";
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(686, 125);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(85, 35);
            this.btnStart.TabIndex = 28;
            this.btnStart.Text = "start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.button1_Click);
            // 
            // lblLettre
            // 
            this.lblLettre.AutoSize = true;
            this.lblLettre.Location = new System.Drawing.Point(454, 147);
            this.lblLettre.Name = "lblLettre";
            this.lblLettre.Size = new System.Drawing.Size(71, 13);
            this.lblLettre.TabIndex = 29;
            this.lblLettre.Text = "La lettre est : ";
            this.lblLettre.Click += new System.EventHandler(this.label6_Click);
            // 
            // BtnSend
            // 
            this.BtnSend.Location = new System.Drawing.Point(527, 481);
            this.BtnSend.Name = "BtnSend";
            this.BtnSend.Size = new System.Drawing.Size(267, 70);
            this.BtnSend.TabIndex = 30;
            this.BtnSend.Text = "Envoyer";
            this.BtnSend.UseVisualStyleBackColor = true;
            this.BtnSend.Click += new System.EventHandler(this.BtnSend_Click_1);
            // 
            // FormJeu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1208, 651);
            this.Controls.Add(this.BtnSend);
            this.Controls.Add(this.lblLettre);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.lblBienvenue);
            this.Controls.Add(this.txtPrenom);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtObjet);
            this.Controls.Add(this.txtAnimal);
            this.Controls.Add(this.txtPays);
            this.Controls.Add(this.txtVille);
            this.Name = "FormJeu";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.FormJeu_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox txtPrenom;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtObjet;
        private System.Windows.Forms.TextBox txtAnimal;
        private System.Windows.Forms.TextBox txtPays;
        private System.Windows.Forms.TextBox txtVille;
        private System.Windows.Forms.Label lblBienvenue;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Label lblLettre;
        private System.Windows.Forms.Button BtnSend;
    }
}