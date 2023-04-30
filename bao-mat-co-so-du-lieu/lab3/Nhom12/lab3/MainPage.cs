using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab3
{
    public partial class MainPage : Form
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            //this.Close();
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Login.role != "NV")
            { 
                button1.Enabled = false;
                MessageBox.Show("Chỉ có nhân viên mới có quyền truy cập");
            }
            else
            {
                QLLH t = new QLLH();
                t.Show();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Login.role != "NV")
            {
                button1.Enabled = false;
                MessageBox.Show("Chỉ có nhân viên mới có quyền truy cập");
            }
            else
            {
                QLSV t = new QLSV();
                t.Show();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (Login.role != "NV")
            {
                button1.Enabled = false;
                MessageBox.Show("Chỉ có nhân viên mới có quyền truy cập");
            }
            else
            {
                ND t = new ND();
                t.Show();
            }
        }

        private void MainPage_Load(object sender, EventArgs e)
        {

        }
    }
}
