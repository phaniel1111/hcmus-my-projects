using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.Collections;
using System.Data.SqlClient;

namespace Nhom12_lab4
{
    public partial class LogIn : Form
    {
        public SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        public SqlCommand cmd;
        public SqlDataReader rd;
        public static string manv;
        public LogIn()
        {
            InitializeComponent();
        }

        private void btnLogIn_Click(object sender, EventArgs e)
        {
            // SHA256
            SHA256 sha256 = SHA256.Create();
            Byte[] buffer = sha256.ComputeHash(Encoding.UTF8.GetBytes(txtPass.Text));

            cmd = new SqlCommand("EXEC SP_SEL_LOG_IN @username, @password", con);
            cmd.Parameters.AddWithValue("@username", txtUser.Text);
            cmd.Parameters.AddWithValue("@password", buffer);

            con.Open();
            rd = cmd.ExecuteReader();
            if (rd.HasRows)
            {
                while (rd.Read())
                {
                    manv = rd["MANV"].ToString();
                }
                Hide();
                MainPage form = new MainPage();
                form.Show();
            }
            else
            {
                MessageBox.Show("Tên đăng nhập và mật khẩu không hợp lệ!");
            }
            con.Close();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void showPass_CheckedChanged(object sender, EventArgs e)
        {
            txtPass.PasswordChar = showPass.Checked ? '\0' : '*';
        }
    }
}
