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
    public partial class ND : Form
    {
        public SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        public SqlCommand cmd;
        public SqlCommand cmd2;
        public static SqlDataReader rd;
        public ND()
        {
            InitializeComponent();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ND_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string a, b, c, d;
            a = MSSV.Text;
            b = MAHP.Text;
            c = DIEM.Text;
            d = Login.MANHANVIEN;
            cmd = new SqlCommand("exec Nhap_Diem @MSSV,@MAHP,@DIEMTHI,@MANV", con);
            cmd2 = new SqlCommand("select MASV, MAHP, DIEMTHI from BANGDIEM " +
                                                "where MASV = @MSSV " +
                                                "and MAHP = @MAHP", con);
            cmd.Parameters.AddWithValue("@MSSV", a);
            cmd.Parameters.AddWithValue("@MAHP", b);
            cmd.Parameters.AddWithValue("@DIEMTHI", c);
            cmd.Parameters.AddWithValue("@MANV", d);

            cmd2.Parameters.AddWithValue("@MSSV", a);
            cmd2.Parameters.AddWithValue("@MAHP", b);
            cmd2.Parameters.AddWithValue("@DIEMTHI", c);
            cmd2.Parameters.AddWithValue("@MANV", d);

            SqlDataAdapter da = new SqlDataAdapter(cmd2);
            DataTable dt = new DataTable();
            da.Fill(dt);

            if (dt.Rows.Count > 0)
            {
                MessageBox.Show("Điểm học phần của sinh viên này đã tồn tại");
            }
            else
            {
                con.Open();
                MessageBox.Show("Thành công");
                rd = cmd.ExecuteReader();
                con.Close();
            }
        }

        private void MSSV_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
