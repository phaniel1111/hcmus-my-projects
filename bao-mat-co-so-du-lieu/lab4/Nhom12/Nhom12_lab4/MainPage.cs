using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Nhom12_lab4
{
    public partial class MainPage : Form
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            NhanVien form = new NhanVien();
            form.Show();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Lop form = new Lop();
            form.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SinhVien form = new SinhVien();
            form.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Diem form = new Diem();
            form.Show();
        }
    }
}
