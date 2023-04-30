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

namespace Nhom12_lab4
{
    public partial class Diem : Form
    {
        SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        string commandType = "none";
        public SqlCommand cmd;
        int rd;
        RSAEncryptor XDiem = new RSAEncryptor();
        public Diem()
        {
            InitializeComponent();
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
            string t1, t2;
            t1 = masv.Text; 
            t2 = mahp.Text;
            // đọc khoá

            // mã
            Byte[] t3 = XDiem.Encrypt(diemsv.Text);
            // ghi
            cmd = new SqlCommand("SP_INS_PUBLIC_ENCRYPT_BANGDIEM @t1, @t2, @t3", con);
            cmd.Parameters.AddWithValue("@t1", t1);
            cmd.Parameters.AddWithValue("@t2", t2);
            cmd.Parameters.AddWithValue("@t3", t3);
            con.Open();
            rd = cmd.ExecuteNonQuery();
            if (rd > 0)
            {
                MessageBox.Show("Ghi/Lưu thành công.");
            }
            else
            {
                MessageBox.Show("Không thể ghi/lưu.");
            }
            con.Close();
            con.Open();
            string query = "exec SP_SEL_PUBLIC_ENCRYPT_BANGDIEM";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);

            DataColumn newColumn = new DataColumn("DIEM", typeof(string));
            table.Columns.Add(newColumn);
            for (int i = 0; i < table.Rows.Count; i++)
            {
                byte[] diemBytes = (byte[])table.Rows[i]["DIEMTHI"];
                table.Rows[i]["DIEM"] = XDiem.Decrypt(diemBytes);
            }
            if (table.Columns.Contains("DIEMTHI"))
            {
                table.Columns.Remove("DIEMTHI");
            }
            diemthi.DataSource = table;
            con.Close();
        }

        private void Diem_Load(object sender, EventArgs e)
        {
            XDiem = new RSAEncryptor();
            XDiem.ImportKeyFromFile();
            con.Open();
            string query = "exec SP_SEL_PUBLIC_ENCRYPT_BANGDIEM";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);

            DataColumn newColumn = new DataColumn("DIEM", typeof(string));
            table.Columns.Add(newColumn);
            for (int i = 0; i < table.Rows.Count; i++)
            {
                byte[] diemBytes = (byte[])table.Rows[i]["DIEMTHI"];
                table.Rows[i]["DIEM"] = XDiem.Decrypt(diemBytes);
            }
            if (table.Columns.Contains("DIEMTHI"))
            {
                table.Columns.Remove("DIEMTHI");
            }
            diemthi.DataSource = table;
            con.Close();
        }
    }
}
