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
using System.Security.Cryptography;
using static _20120313_lab4.AES;

namespace _20120313_lab4
{
    public partial class NVList : Form
    {
        SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSV;Integrated Security=True");
        string commandType = "none";
        public SqlCommand cmd;
        int rd;

        public NVList()
        {
            InitializeComponent();
        }

        private void NVList_Load(object sender, EventArgs e)
        {
            con.Open();
            string query = "exec SP_SEL_ENCRYPT_NHANVIEN";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);

            DataColumn newColumn = new DataColumn("LUONGNV", typeof(string));
            table.Columns.Add(newColumn);
            for (int i = 0; i < table.Rows.Count; i++)
            {
                byte[] luongBytes = (byte[])table.Rows[i]["LUONG"];
                table.Rows[i]["LUONGNV"] = AES.Decrypt(luongBytes, "20120313");
            }
            if (table.Columns.Contains("LUONG"))
            {
                table.Columns.Remove("LUONG");
            }
            tableNV.DataSource = table;
            con.Close();
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            Application.Exit();
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
            //
            if(commandType == "none")
                MessageBox.Show("Vui lòng chọn chức năng Thêm, Xoá hoặc Sửa");
            else
            {
                string t = "", t1, t2, t3 ,t4;
                t1 = textBox1.Text;
                t2 = textBox2.Text; 
                t3 = textBox3.Text; 
                t4 = textBox4.Text; 

                //SHA256
                SHA256 sha256 = SHA256.Create();
                Byte[] t6 = sha256.ComputeHash(Encoding.UTF8.GetBytes(textBox6.Text));
                Byte[] t5 = AES.Encrypt(textBox5.Text, "20120313");
                 
                if (commandType == "add")
                {
                    t = "exec SP_INS_ENCRYPT_NHANVIEN @t1, @t4, @t2, @t5, @t3 , @t6";
                }
                else if(commandType == "edit")
                {
                    t = "exec SP_UPD_ENCRYPT_NHANVIEN @t1, @t4, @t2, @t5, @t3 , @t6";
                }
                else if(commandType == "delete")
                {
                    t = "DELETE FROM NHANVIEN WHERE NHANVIEN.MANV = @t1";
                }
                cmd = new SqlCommand(t, con);
                cmd.Parameters.AddWithValue("@t1", t1);
                cmd.Parameters.AddWithValue("@t2", t2);
                cmd.Parameters.AddWithValue("@t3", t3);
                cmd.Parameters.AddWithValue("@t4", t4);
                cmd.Parameters.AddWithValue("@t5", t5);
                cmd.Parameters.AddWithValue("@t6", t6);
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
                string query = "exec SP_SEL_ENCRYPT_NHANVIEN";
                SqlDataAdapter da = new SqlDataAdapter(query, con);
                DataTable table = new DataTable();
                da.Fill(table);
                DataColumn newColumn = new DataColumn("LUONGNV", typeof(string));
                table.Columns.Add(newColumn);
                for (int i = 0; i < table.Rows.Count; i++)
                {
                    byte[] luongBytes = (byte[])table.Rows[i]["LUONG"];
                    table.Rows[i]["LUONGNV"] = AES.Decrypt(luongBytes, "20120313");
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
}
