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

namespace Nhom12_lab4
{
    public partial class AddStudent : Form
    {
        public SqlConnection con = new SqlConnection(@"Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        public SqlCommand cmd, cmd1;
        public static SqlDataReader rd;
        public AddStudent()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string masv = textBox1.Text.ToString();
            string hoten = textBox2.Text.ToString();
            string ngsinh = textBox3.Text.ToString();
            string diachi = textBox4.Text.ToString();
            string malop = textBox5.Text.ToString();
            string check = LogIn.manv.ToString();
            cmd1 = new SqlCommand("exec SP_QL_SV @MANV, @MASV", con);
            cmd1.Parameters.AddWithValue("@MANV", check);
            cmd1.Parameters.AddWithValue("@MASV", masv);
            cmd = new SqlCommand("exec SP_UPDATE_SV @MASV,@HOTEN,@NGAYSINH, @DIACHI,@MALOP", con);
            cmd.Parameters.AddWithValue("@MASV", masv);
            cmd.Parameters.AddWithValue("@HOTEN", hoten);
            cmd.Parameters.AddWithValue("@NGAYSINH", ngsinh);
            cmd.Parameters.AddWithValue("@DIACHI", diachi);
            cmd.Parameters.AddWithValue("@MALOP", malop);
            con.Open();
            SqlDataAdapter da = new SqlDataAdapter(cmd1);
            DataTable dt = new DataTable();
            da.Fill(dt);

            if (dt.Rows.Count > 0)
            {
                
                MessageBox.Show("Sửa thông tin thành công!!");
                rd = cmd.ExecuteReader();
            }
            else
            {
                MessageBox.Show("Nhân viên không quản lý sinh viên này!!");
            }

            con.Close();

        }
    }
}
