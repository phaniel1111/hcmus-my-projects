using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Xml;

namespace Nhom12_lab4
{
    internal class RSAEncryptor
    {
        private RSACryptoServiceProvider rsa;

        public RSAEncryptor()
        {
            rsa = new RSACryptoServiceProvider();
        }

        public byte[] Encrypt(string plainText)
        {
            byte[] plainBytes = Encoding.UTF8.GetBytes(plainText);
            byte[] encryptedBytes = rsa.Encrypt(plainBytes, false);
            return encryptedBytes;
        }

        public string Decrypt(byte[] encryptedBytes)
        {
            try
            {
                byte[] decryptedBytes = rsa.Decrypt(encryptedBytes, false);
                return Encoding.UTF8.GetString(decryptedBytes);
            }
            catch (CryptographicException ex)
            {
                // Xử lý lỗi ở đây (nếu cần)
                return "Encrypted"; // Hoặc trả về giá trị mặc định khác nếu giải mã không thành công
            }

        }
        public string GetPublicKey()
        {
            RSAParameters parameters = rsa.ExportParameters(true);
            string publicKey = Convert.ToBase64String(parameters.Modulus) + ";"+ Convert.ToBase64String(parameters.Exponent);
            return publicKey;
        }
        // Chua thuc hien duoc
        public void SetRSAParametersFromString(string keyString)
        {
            string[] parts = keyString.Split(';');

            // Chuyển Modulus và Exponent từ chuỗi sang kiểu số nguyên
            byte[] modulus = Convert.FromBase64String(parts[0]);
            byte[] exponent = Convert.FromBase64String(parts[1]);

            RSAParameters rsaParams = new RSAParameters();
            rsaParams.Modulus = modulus;
            rsaParams.Exponent = exponent;

            rsa.ImportParameters(rsaParams);
        }
        public void ExportKeyToFile()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "XML files (*.xml)|*.xml";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                ExportKey(saveFileDialog.FileName);
            }
        }
        public void ExportKey(string fileName)
        {
            RSAParameters parameters = rsa.ExportParameters(true);
            XmlDocument xmlDoc = new XmlDocument();
            XmlElement rootNode = xmlDoc.CreateElement("RSAKeyValue");
            xmlDoc.AppendChild(rootNode);

            XmlElement node;

            node = xmlDoc.CreateElement("Modulus");
            node.InnerText = Convert.ToBase64String(parameters.Modulus);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("Exponent");
            node.InnerText = Convert.ToBase64String(parameters.Exponent);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("P");
            node.InnerText = Convert.ToBase64String(parameters.P);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("Q");
            node.InnerText = Convert.ToBase64String(parameters.Q);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("DP");
            node.InnerText = Convert.ToBase64String(parameters.DP);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("DQ");
            node.InnerText = Convert.ToBase64String(parameters.DQ);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("InverseQ");
            node.InnerText = Convert.ToBase64String(parameters.InverseQ);
            rootNode.AppendChild(node);

            node = xmlDoc.CreateElement("D");
            node.InnerText = Convert.ToBase64String(parameters.D);
            rootNode.AppendChild(node);

            xmlDoc.Save(fileName);
        }
        public void ImportKeyFromFile()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "XML files (*.xml)|*.xml";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                ImportKey(openFileDialog.FileName);
            }
        }
        public void ImportKey(string fileName)
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(fileName);

            RSAParameters parameters = new RSAParameters();

            parameters.Modulus = Convert.FromBase64String(xmlDoc.SelectSingleNode("//Modulus").InnerText);
            parameters.Exponent = Convert.FromBase64String(xmlDoc.SelectSingleNode("//Exponent").InnerText);
            parameters.P = Convert.FromBase64String(xmlDoc.SelectSingleNode("//P").InnerText);
            parameters.Q = Convert.FromBase64String(xmlDoc.SelectSingleNode("//Q").InnerText);
            parameters.DP = Convert.FromBase64String(xmlDoc.SelectSingleNode("//DP").InnerText);
            parameters.DQ = Convert.FromBase64String(xmlDoc.SelectSingleNode("//DQ").InnerText);
            parameters.InverseQ = Convert.FromBase64String(xmlDoc.SelectSingleNode("//InverseQ").InnerText);
            parameters.D = Convert.FromBase64String(xmlDoc.SelectSingleNode("//D").InnerText);

            rsa.ImportParameters(parameters);
        }

    }
}



