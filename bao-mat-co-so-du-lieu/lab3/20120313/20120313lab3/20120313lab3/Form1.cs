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

namespace lab2DS
{
    public partial class Form1 : Form
    {
        SqlConnection con = new SqlConnection("Data Source=KIETPHAN\\KIETPHAN;Initial Catalog=QLSV;Integrated Security=True;MultipleActiveResultSets=true");
        SqlCommand cmd1, cmd2;
        SqlDataReader rd1, rd2;

        public Form1()
        {
            InitializeComponent();
        }

        private void showPass_CheckedChanged(object sender, EventArgs e)
        {
            txtPass.PasswordChar = showPass.Checked ? '\0' : '*';
        }

        private void btnLogIn_Click(object sender, EventArgs e)
        {  
            string u, p;
            u = txtUser.Text;
            p = txtPass.Text;
            cmd1 = new SqlCommand("select * from sinhvien where tendn=@username and matkhau=HASHBYTES('MD5',@userpass)", con);
            cmd1.Parameters.AddWithValue("@username", u);
            cmd1.Parameters.AddWithValue("@userpass", p);

            cmd2 = new SqlCommand("select * from nhanvien where tendn=@username and matkhau=HASHBYTES('SHA1',@userpass)", con);
            cmd2.Parameters.AddWithValue("@username", u);
            cmd2.Parameters.AddWithValue("@userpass", p);

            con.Open();
            rd1 = cmd1.ExecuteReader();
            rd2 = cmd2.ExecuteReader();
            if (rd1.HasRows || rd2.HasRows)
            {
                MessageBox.Show("Đăng nhập thành công");
            }
            else
            {
                MessageBox.Show("tên đăng nhập và mật khẩu không hợp lệ!");
            }
            con.Close();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
