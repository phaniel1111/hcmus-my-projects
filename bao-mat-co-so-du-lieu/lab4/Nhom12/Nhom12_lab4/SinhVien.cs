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
    public partial class SinhVien : Form
    {
        SqlConnection con = new SqlConnection(@"Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        public SinhVien()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            con.Open();
            string query = "select sv.MASV, sv.HOTEN, sv.NGAYSINH, sv.DIACHI, sv.MALOP from SINHVIEN sv";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);
            dataGridView1.DataSource = table;
            con.Close();
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string malop = textBox1.Text.ToString();
            con.Open();
            SqlCommand cmd = new SqlCommand();
            string query = "select sv.MASV, sv.HOTEN, sv.NGAYSINH, sv.DIACHI, sv.MALOP from SINHVIEN sv where sv.MALOP = '" + malop + "'";
            SqlDataAdapter da1 = new SqlDataAdapter(query, con);
            DataTable table1 = new DataTable();
            da1.Fill(table1);
            dataGridView1.DataSource = table1;
            con.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            button3.Enabled = true;
            AddStudent stu = new AddStudent();
            stu.Show();
        }
    }
}
