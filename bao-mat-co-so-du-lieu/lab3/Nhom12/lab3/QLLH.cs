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
    public partial class QLLH : Form
    {
        SqlConnection con = new SqlConnection("Data Source=.;Initial Catalog=QLSVNhom;Integrated Security=True");
        public QLLH()
        {
            InitializeComponent();
        }
      
        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = true;
            AddClass a = new AddClass();
            a.Show();
            
        }

        private void btnOut_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void QLLH_Load(object sender, EventArgs e)
        {
            /*// TODO: This line of code loads data into the 'qLSVNhomDataSet2.LOP' table. You can move, or remove it, as needed.
            this.lOPTableAdapter1.Fill(this.qLSVNhomDataSet2.LOP);
            // TODO: This line of code loads data into the 'qLSVNhomDataSet1.LOP' table. You can move, or remove it, as needed.
            this.lOPTableAdapter.Fill(this.qLSVNhomDataSet1.LOP);*/

        }

        private void button2_Click(object sender, EventArgs e)
        {
            con.Open();
            string query = "select * from LOP";
            SqlDataAdapter da = new SqlDataAdapter(query, con);
            DataTable table = new DataTable();
            da.Fill(table);
            dataGridView2.DataSource = table;
            con.Close();
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
