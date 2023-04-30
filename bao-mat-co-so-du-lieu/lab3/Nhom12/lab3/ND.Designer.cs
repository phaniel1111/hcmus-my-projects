namespace lab3
{
    partial class ND
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
            this.btnOut = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.MSSV = new System.Windows.Forms.TextBox();
            this.MAHP = new System.Windows.Forms.TextBox();
            this.DIEM = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnOut
            // 
            this.btnOut.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.btnOut.Location = new System.Drawing.Point(332, 381);
            this.btnOut.Name = "btnOut";
            this.btnOut.Size = new System.Drawing.Size(102, 35);
            this.btnOut.TabIndex = 12;
            this.btnOut.Text = "Thoát";
            this.btnOut.UseVisualStyleBackColor = true;
            this.btnOut.Click += new System.EventHandler(this.btnOut_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(209, 381);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(100, 35);
            this.button1.TabIndex = 13;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // MSSV
            // 
            this.MSSV.Location = new System.Drawing.Point(229, 100);
            this.MSSV.Name = "MSSV";
            this.MSSV.Size = new System.Drawing.Size(100, 22);
            this.MSSV.TabIndex = 14;
            this.MSSV.TextChanged += new System.EventHandler(this.MSSV_TextChanged);
            // 
            // MAHP
            // 
            this.MAHP.Location = new System.Drawing.Point(229, 217);
            this.MAHP.Name = "MAHP";
            this.MAHP.Size = new System.Drawing.Size(100, 22);
            this.MAHP.TabIndex = 15;
            // 
            // DIEM
            // 
            this.DIEM.Location = new System.Drawing.Point(501, 100);
            this.DIEM.Name = "DIEM";
            this.DIEM.Size = new System.Drawing.Size(100, 22);
            this.DIEM.TabIndex = 16;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(134, 106);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 16);
            this.label1.TabIndex = 17;
            this.label1.Text = "MSSV";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(134, 217);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 16);
            this.label2.TabIndex = 18;
            this.label2.Text = "MaHP";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(419, 106);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 16);
            this.label3.TabIndex = 19;
            this.label3.Text = "Điểm";
            // 
            // ND
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DIEM);
            this.Controls.Add(this.MAHP);
            this.Controls.Add(this.MSSV);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnOut);
            this.Name = "ND";
            this.Text = "Nhập điểm";
            this.Load += new System.EventHandler(this.ND_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOut;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox MSSV;
        private System.Windows.Forms.TextBox MAHP;
        private System.Windows.Forms.TextBox DIEM;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}