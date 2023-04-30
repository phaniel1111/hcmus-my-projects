using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab3
{

    public partial class Login : Form
    {
        public SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        public SqlCommand cmd;
        public static SqlDataReader rd;
        public static Login instance;
        public static string role;
        public static string MANHANVIEN;

        private void btnOut_Click(object sender, EventArgs e)
        {
            this.Close();
            instance = this;
        }

        private void showPass_CheckedChanged(object sender, EventArgs e)
        {
            txtPass.PasswordChar = showPass.Checked ? '\0' : '*';
        }

        public Login()
        {
            InitializeComponent();
        }

        private void btnLogIn_Click(object sender, EventArgs e)
        {
            string u, p;
            u = txtUser.Text;
            p = txtPass.Text;
            cmd = new SqlCommand("exec LOG_IN @username,@userpass", con);
            cmd.Parameters.AddWithValue("@username", u);
            cmd.Parameters.AddWithValue("@userpass", p);

            
            con.Open();
            rd = cmd.ExecuteReader();
            if (rd.HasRows)
            {
                while (rd.Read())
                {
                    role = rd["CHUCNANG"].ToString();
                    MANHANVIEN = rd["MANV"].ToString();
                }
                MessageBox.Show("Đăng nhập thành công");
                Hide();
                MainPage mp =  new MainPage();
                mp.Show();
                //dtv.Visible = true;
                //DataTable dt = new DataTable();
                //dt.Load(rd);
                //dtv.DataSource = dt;
            }
            else
            {
                MessageBox.Show("tên đăng nhập và mật khẩu không hợp lệ!");
            }
            con.Close();
        }

        private void Login_Load(object sender, EventArgs e)
        {

        }
    }
}
