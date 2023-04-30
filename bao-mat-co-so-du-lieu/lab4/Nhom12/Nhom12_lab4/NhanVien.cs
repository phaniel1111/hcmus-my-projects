using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static Nhom12_lab4.RSAEncryptor;

namespace Nhom12_lab4
{
    public partial class NhanVien : Form
    {
        SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        string commandType = "none";
        public SqlCommand cmd;
        int rd;
        RSAEncryptor keyReader = new RSAEncryptor();
        public NhanVien()
        {
            InitializeComponent();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            commandType = "add";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            commandType = "delete";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            commandType = "edit";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            commandType = "none";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (commandType == "none")
                MessageBox.Show("Vui lòng chọn chức năng Thêm, Xoá hoặc Sửa");
            else
            {
                string t = "", t1, t2, t3, t5,t7;
                t1 = manv.Text;
                t2 = hoten.Text;
                t3 = email.Text;
                t5 = tendn.Text;
                
                if (commandType == "add")
                {
                    //Luong RSA
                    RSAEncryptor rsaEncryptor = new RSAEncryptor();
                    rsaEncryptor.ExportKeyToFile();
                    Byte[] t4 = rsaEncryptor.Encrypt(luong.Text);
                    //Dang thuc hien
                    // Mat Khau SHA
                    SHA256 sha256 = SHA256.Create();
                    Byte[] t6 = sha256.ComputeHash(Encoding.UTF8.GetBytes(matkhau.Text));
                    // PUblic key
                    t7 = rsaEncryptor.GetPublicKey();
                    t = "exec SP_INS_PUBLIC_ENCRYPT_NHANVIEN @t1, @t2, @t3, @t4, @t5, @t6, @t7";
                    cmd = new SqlCommand(t, con);
                    cmd.Parameters.AddWithValue("@t1", t1);
                    cmd.Parameters.AddWithValue("@t2", t2);
                    cmd.Parameters.AddWithValue("@t3", t3);
                    cmd.Parameters.AddWithValue("@t4", t4);
                    cmd.Parameters.AddWithValue("@t5", t5);
                    cmd.Parameters.AddWithValue("@t6", t6);
                    cmd.Parameters.AddWithValue("@t7", t7);
                }
                else if (commandType == "edit")
                {
                    //Lấy khoá public
                    RSAEncryptor temp = new RSAEncryptor();
                    temp.ImportKeyFromFile();

                    // ma
                    Byte[] t4 = temp.Encrypt(luong.Text);
                    //Dang thuc hien
                    // Mat Khau SHA
                    SHA256 sha256 = SHA256.Create();
                    Byte[] t6 = sha256.ComputeHash(Encoding.UTF8.GetBytes(matkhau.Text));
                    // PUblic key
                    

                    t = "exec SP_UPD_PUBLIC_ENCRYPT_NHANVIEN @t1, @t2, @t3, @t4, @t5, @t6";
                    cmd = new SqlCommand(t, con);
                    cmd.Parameters.AddWithValue("@t1", t1);
                    cmd.Parameters.AddWithValue("@t2", t2);
                    cmd.Parameters.AddWithValue("@t3", t3);
                    cmd.Parameters.AddWithValue("@t4", t4);
                    cmd.Parameters.AddWithValue("@t5", t5);
                    cmd.Parameters.AddWithValue("@t6", t6);
                }
                else if (commandType == "delete")
                {
                    t = "DELETE FROM NHANVIEN WHERE NHANVIEN.MANV = @t1";
                    cmd = new SqlCommand(t, con);
                    cmd.Parameters.AddWithValue("@t1", t1);
                }
                
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
                // in ra man hinh
                con.Open();
                string query = "exec SP_SEL_NHANVIEN";
                SqlDataAdapter da = new SqlDataAdapter(query, con);
                DataTable table = new DataTable();
                da.Fill(table);

                DataColumn newColumn = new DataColumn("LUONGNV", typeof(string));
                table.Columns.Add(newColumn);
                for (int i = 0; i < table.Rows.Count; i++)
                {
                    byte[] luongBytes = (byte[])table.Rows[i]["LUONG"];
                    table.Rows[i]["LUONGNV"] = keyReader.Decrypt(luongBytes);
                }
                if (table.Columns.Contains("LUONG"))
                {
                    table.Columns.Remove("LUONG");
                }
                tableNV.DataSource = table;
                con.Close();
            }
        }
        //Load data khi mo form
        private void NhanVien_Load(object sender, EventArgs e)
        {
            keyReader.ImportKeyFromFile();
            con.Open();
            string query = "exec SP_SEL_NHANVIEN";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);

            DataColumn newColumn = new DataColumn("LUONGNV", typeof(string));
            table.Columns.Add(newColumn);
            for (int i = 0; i < table.Rows.Count; i++)
            {
                byte[] luongBytes = (byte[])table.Rows[i]["LUONG"];
                table.Rows[i]["LUONGNV"] = keyReader.Decrypt(luongBytes);
            }
            if (table.Columns.Contains("LUONG"))
            {
                table.Columns.Remove("LUONG");
            }
            tableNV.DataSource = table;
            con.Close();
        }
        
    }
}
