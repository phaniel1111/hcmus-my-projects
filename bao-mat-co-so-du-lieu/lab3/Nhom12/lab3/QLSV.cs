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
    public partial class QLSV : Form
    {
        public SqlCommand cmd,cmd1;
        public static SqlDataReader rd;
        SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True;MultipleActiveResultSets=True");
        public QLSV()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            con.Open();
            string query = "select SV.MASV,SV.HOTEN,SV.NGAYSINH,SV.DIACHI,SV.MALOP from SINHVIEN as SV";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);
            dataGridView2.DataSource = table;
            con.Close();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void QLSV_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string a, b, c, d, e1, f;
            a = MSSV.Text;
            b = hoten.Text;
            c = ngaysinh.Text;
            d = diachi.Text;
            e1 = malop.Text;
            f = Login.MANHANVIEN;
            cmd1 = new SqlCommand("exec NHAN_VIEN_QL_SINH_VIEN @MANV, @MASV", con);
            cmd1.Parameters.AddWithValue("@MASV", a);
            cmd1.Parameters.AddWithValue("@MANV", f);

            cmd = new SqlCommand("exec CAP_NHAT_SINH_VIEN @MASV,@HOTEN,@NGAYSINH, @DIACHI,@MALOP", con);
            cmd.Parameters.AddWithValue("@MASV", a);
            cmd.Parameters.AddWithValue("@HOTEN", b);
            cmd.Parameters.AddWithValue("@NGAYSINH", c);
            cmd.Parameters.AddWithValue("@DIACHI", d);
            cmd.Parameters.AddWithValue("@MALOP", e1);
            con.Open();
            rd = cmd1.ExecuteReader();
            if (rd.HasRows)
            {
                rd = cmd.ExecuteReader();
                MessageBox.Show("Thay đổi thông tin thành công!");
            }
            else
            {
                MessageBox.Show("Nhân viên không quản lý sinh viên này!");
            }
            con.Close();

        }
    }
}
