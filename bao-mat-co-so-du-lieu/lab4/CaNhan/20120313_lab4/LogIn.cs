using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Xml.Linq;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;
using _20120313_lab4;
using System.Security.Cryptography;
using static System.Net.Mime.MediaTypeNames;
using System.IO;
using System.Collections;

namespace lab2DS
{
    public partial class LogIn : Form
    {
        public SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSV;Integrated Security=True");
        public SqlCommand cmd;
        public SqlDataReader rd;

        public LogIn()
        {
            InitializeComponent();
        }

        private void showPass_CheckedChanged(object sender, EventArgs e)
        {
            txtPass.PasswordChar = showPass.Checked ? '\0' : '*';
        }

        private void btnLogIn_Click(object sender, EventArgs e)
        {
            string u;
            u = txtUser.Text;
            // MD5
            MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
            Byte[] buffer1 = md5.ComputeHash(Encoding.UTF8.GetBytes(txtPass.Text));
            //SHA256
            SHA256 sha256 = SHA256.Create();
            Byte[] buffer2 = sha256.ComputeHash(Encoding.UTF8.GetBytes(txtPass.Text));

            cmd = new SqlCommand("SELECT NV.MANV, NV.TENDN FROM NHANVIEN AS NV where nv.TENDN = @username and NV.MATKHAU = @password", con);
            cmd.Parameters.AddWithValue("@username", u);
            cmd.Parameters.AddWithValue("@password", buffer2);

            con.Open();
            rd = cmd.ExecuteReader();
            if (rd.HasRows)
            {
                //MessageBox.Show("hợp lệ!");
                Hide();
                NVList form = new NVList();
                form.Show();
            }
            else
            {
                MessageBox.Show("tên đăng nhập và mật khẩu không hợp lệ!");
            }
            con.Close();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }
    }
}
