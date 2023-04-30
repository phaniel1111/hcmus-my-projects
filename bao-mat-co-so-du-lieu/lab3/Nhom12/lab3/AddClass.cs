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

namespace lab3
{
    
    public partial class AddClass : Form
    {
        public SqlConnection con = new SqlConnection(@"Data Source=KIETPHAN\KIETPHAN;Initial Catalog=QLSVNhom;Integrated Security=True");
        public SqlCommand cmd;
        public AddClass()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string malop = textBox1.Text.ToString();
            string tenlop = textBox2.Text.ToString();
            string manv = textBox3.Text.ToString();
            con.Open();
            SqlCommand cmd = new SqlCommand("select count(*) from LOP where MALOP = '" + malop + "'", con);

            int check = (int)cmd.ExecuteScalar();
            if (check == 0)
            {
                try
                {
                    cmd = new SqlCommand("insert into LOP(MALOP, TENLOP, MANV) values ('" + malop + "','" + tenlop + "','" + manv + "') ", con);
                    int rowsAffected = cmd.ExecuteNonQuery();
                    MessageBox.Show("Thêm lớp thành công!");
                }
                catch (SqlException ex)
                {
                    MessageBox.Show("Lỗi khi thêm lớp: " + ex.Message);
                }
                finally
                {
                    textBox1.Clear();
                    textBox2.Clear();
                    textBox3.Clear();
                    con.Close();
                }
            }
            else
            {
                MessageBox.Show("Lớp này đã tồn tại");
                con.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string malop = textBox1.Text.ToString();
            string tenlop = textBox2.Text.ToString();
            string manv = textBox3.Text.ToString();
            con.Open();
            SqlCommand cmd = new SqlCommand("select count(*) from LOP where MALOP = '" + malop + "'and TENLOP = '" + tenlop + "'and MANV = '" + manv + "'", con);

            int check = (int)cmd.ExecuteScalar();
            if (check > 0)
            {
                cmd = new SqlCommand("exec SP_DELETE_CLASS '" + malop + "','" + tenlop + "','" + manv + "'", con);
                try
                {
                    cmd.ExecuteNonQuery();
                    MessageBox.Show("Xóa lớp thành công!");
                }
                catch (SqlException ex)
                {
                    MessageBox.Show("Lỗi khi xóa lớp: " + ex.Message);
                }
                finally
                {
                    textBox1.Clear();
                    textBox2.Clear();
                    textBox3.Clear();
                    con.Close();
                }
            }
            else
            {
                MessageBox.Show("Không tồn tại lớp này");
                con.Close();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
